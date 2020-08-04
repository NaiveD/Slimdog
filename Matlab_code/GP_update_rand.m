%% Tabula Rasa
clear all
close all

%% Update Gaussian Process Model
% Initialize problem
x = [];
y = [];
measurementNoise = [];

procNoise = 10;

% Set parameters
%{
searchrange=[
	0 2;	% x1-x4    
    0 2;	% x5-x8
	0 2;	% a1, a2
    0 2;	% a3, a4
    0 2;	% a5, a8
    0 2 	% a6, a7
	];
%}
%groups = searchrange(:,2) - searchrange(:,1);
%resolution = prod(groups);
%explore_exploit = 1;
mode = 'Matern';        % 马特恩协方差函数

% Set start values
v = {};
v{1} = [255 295 305 345];   % x1-x4
v{2} = [215 255 295 305];   % x5-x8
v{3} = [50 55 60 65];   % a1, a4
v{4} = [60 65 70 75];   % a2, a3
v{5} = [25 30 35 40];   % a5, a8
v{6} = [20 25 30 35];   % a6, a7
v{7} = [-90 0 90 180];  % r1, r4
v{8} = [-90 0 90 180];  % r2, r3
v{9} = [-90 0 90 180];  % r5, r7
v{10} = [-90 0 90 180]; % r6, r8

dimension = length(v);
choice = length(v{1});
resolution = choice.^dimension;
xtot = combvec(v{:});   % combvec() generating the same order of combinations
% [~,index] = sort(xtot(1,:));
% xtot = xtot(:,index);

bestSigma = 1;
bestScale = 1;
mu = zeros(resolution,1);
s = procNoise*ones(resolution,1);
PI = zeros(size(mu));

if isempty(x)
    xInd = 1;
	% x = [255 215 50 60 25 20 -90 -90 -90 -90]'; % The lowest bound of all parameters
   
    % Choose randomly for the first evaluation
    for i = 1:dimension
        rng('shuffle');
        randInd = randi([1, choice]);
        xAdd = v{i}(randInd);
        x = [x', xAdd]';
    end
else
    [~,xInd] = ismember(x',xtot','rows');   % Ignoring the 0-1 sets returned by ismember(), just remember the index
    xInd(xInd==0) = []; % xInd == 0 means not been recorded
end

% Initiating the csv
time = datestr(now,30);
location = [time, '.csv'];
fid = fopen(location, 'a');
fprintf(fid, '%s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s, %s\n',...
    'Iterations', 'x1-x4', 'x5-x8', 'a1/a4', 'a2/a3', 'a5/a8',...
    'a6/a7', 'r1/r4', 'r2/r3', 'r5/r7', 'r6/r8', 'Fitness');
fclose(fid);

% Plot initial GP
%plotGP(mu,s,xInd,y,PI,1,time);

% Iterate
for i = 1:50
    % Get input from user
    str = '%dth iteration:[%0.0f,%0.0f,%0.0f,%0.0f,%0.0f,%0.0f,%0.0f,%0.0f,%0.0f,%0.0f]? ';
    yAdd = input(sprintf(str,i,x(1,end),x(2,end),x(3,end),x(4,end),x(5,end),...
        x(6,end),x(7,end),x(8,end),x(9,end),x(10,end)));
    y = [y yAdd];
    sigmaN = input('What is the measurement uncertainty? ');
    measurementNoise = [measurementNoise sigmaN];
    % Write it in the csv
    fid = fopen(location, 'a');
    fprintf(fid, '%d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d, %d\n',...
    i,x(1,end),x(2,end),x(3,end),x(4,end),x(5,end),...
    x(6,end),x(7,end),x(8,end),x(9,end),x(10,end), yAdd);
    fclose(fid);
    
       
    % Optimize hyperparameters
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
        s(j) = SEcov(ones(10,1),ones(10,1),sigmaSE,lScale,mode)-k/K*k';
    end
    
    % Get next set of parameters
    ee = 50*exp(-numel(xInd)/6);
    [PI,at] = getNextSample(mu,xInd,y,s,ee);
    xInd = [xInd;at];
    xAdd = xtot(:,at);
    x = [x xAdd];
    
    % Plot updated GP
%     plotGP(mu,s,xInd,y,PI,at,i,time);
end