%% Tabula Rasa
clear
close all

%% Update Gaussian Process Model
% Initialize problem

% Parameters: 
% v{1}: x0 - hopping height
% v{2}: x1 - gain kp for controlling pitch (Orange motors)
% v{3}: x2 - gain kv for controlling pitch (Orange motors)
% v{4}: x3 - gain kp for controlling roll (Yellow motors)
% v{5}: x4 - gain kv for controlling roll (Yellow motors)
% v{6}: x5 - The forward distance of the legs during flight phase

% Input
x = []; % column vector
% Output
y = [];

measurementNoise = [];

procNoise = 10;

% Set parameters
mode = 'Matern'; % Matérn kernel function

% Initialization
% Set start values
v = {};
v{1} = [25 50 75 100 125];   % x0 - hopping height
v{2} = [40 45 50 55 60];   % x1 - gain kp for controlling pitch (Orange motors)
v{3} = [00 05 10 15 20];   % x2 - gain kv for controlling pitch (Orange motors)
v{4} = [40 45 50 55 60];   % x3 - gain kp for controlling roll (Yellow motors)
v{5} = [00 05 10 15 20];   % x4 - gain kv for controlling roll (Yellow motors)

dimension = length(v); % 10
choice = length(v{1}); % 4
resolution = choice.^dimension; % 4.^10 = 1048576
xtot = combvec(v{:});   % combvec() generating the same order of combinations; 10*1048576 double

bestSigma = 1;
bestScale = 1;
mu = zeros(resolution,1); % 1048576 * 1
s = procNoise*ones(resolution,1);
PI = zeros(size(mu)); % Probability of Improvement (PI)

if isempty(x)
    xInd = 1;
	% x = [255 215 50 60 25 20 -90 -90 -90 -90]'; % The lowest bound of all parameters
   
    % RS
    % Choose randomly for the first evaluation
    for i = 1:dimension
        rng('shuffle'); % Provide seed for random generator according to current time
        randInd = randi([1, choice]); % Generate a random number in range [1, 4]
        xAdd = v{i}(randInd);
        x = [x', xAdd]';
    end
else
    [~,xInd] = ismember(x',xtot','rows');   % Ignoring the 0-1 sets returned by ismember(), just remember the index (Return the index of x in xtot)
    xInd(xInd==0) = []; % xInd == 0 means not been recorded
end

% Initiating the csv (For saving data)
time = datestr(now,30);
location = [time, '.csv'];
fid = fopen(location, 'a');
fprintf(fid, '%s, %s, %s, %s, %s, %s, %s\n',...
    'Iterations', 'x0', 'x1', 'x2', 'x3', 'x4','Fitness');
fclose(fid);

% Plot initial GP
% plotGP(mu,s,xInd,y,PI,1,time);

% Iterate (50 interations)
for i = 1:50
    % Get input from user (Do experiment and get the result yAdd)
    str = '%dth iteration:[%0.2f,%0.2f,%0.2f,%0.2f,%0.2f]? ';
    yAdd = input(sprintf(str,i,x(1,end),x(2,end),x(3,end),x(4,end),x(5,end)));
    y = [y yAdd];
    % sigmaN = input('What is the measurement uncertainty? ');
    sigmaN = 0.1;
    measurementNoise = [measurementNoise sigmaN];
    % Write it in the csv
    fid = fopen(location, 'a');
    fprintf(fid, '%d, %0.2f, %0.2f, %0.2f, %0.2f, %0.2f, %0.2f\n',...
    i,x(1,end),x(2,end),x(3,end),x(4,end),x(5,end), yAdd);
    fclose(fid);
    
       
    % Optimize hyperparameters (parameters in the kernel function)
    [sigmaSE,lScale] = findHyperparams(x,y,mode);
    if isinf(sigmaSE)
        sigmaSE = bestSigma; 
        lScale = bestScale;
    else
        bestSigma = sigmaSE;
        bestScale = lScale;
    end
    
    % Calculate covariance matrix
    K = getCovMat(x,sigmaSE,lScale,mode);
    K = addNoiseToCovMat(K,measurementNoise);
    
    % Update GP
    k = zeros(1,size(x,2));
    for j = 1:resolution
        for l = 1:size(x,2)
            k(l) = SEcov(xtot(:,j),x(:,l),sigmaSE,lScale,mode);
        end
        mu(j) = k/K*y';
        s(j) = SEcov(ones(5,1),ones(5,1),sigmaSE,lScale,mode)-k/K*k';
    end
    
    % Get next set of parameters
    ee = 50*exp(-numel(xInd)/6);
    [PI,at] = getNextSample(mu,xInd,y,s,ee);
    xInd = [xInd;at];
    xAdd = xtot(:,at);
    x = [x xAdd];
    
end