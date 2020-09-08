%% Tabula Rasa
clear all
close all
clc

%% Update Gaussian Process Model
% seed: 12345, 50*exp(-numel(xInd)/6)

groups = [10 10 10]; % Maximum values for each integer variable
parameter_count=length(groups);
procNoise = 1e12; %variance

%x=ceil(groups'.*rand(parameter_count,1)); %Choose random sample
x=[8;10;4];
y=[];
measurementNoise=[];
sample_count=0;

%% Set parameters
resolution = prod(groups);
explore_exploit = 1;

%% Set start values
bestSigma = 1;
bestScale = 1;
mu = zeros(resolution,1);
s = procNoise*ones(resolution,1);
PI = zeros(size(mu));

%% Create array with all possible states
v = {};
for i = 1:parameter_count
    v{i} = 1:groups(i);
end
xtot = combvec(v{:});
% [~,index] = sort(xtot(1,:));
% xtot = xtot(:,index);

if isempty(x)
    xInd = 1;
    x = ones(parameter_count,1);
else
    [~,xInd] = ismember(x',xtot','rows'); %find positions of existing samples
    xInd(xInd==0) = []; %retain positions only
end

%% Plot initial GP
plotGP(mu,s,xInd,y,PI,1);
drawnow

%% Iterate
for i = 1:15
    % Update sample
%     x1=x(1,end);
%     x2=x(2,end);
%     x3=x(3,end);
%     ynew=100*(x2-x1^2)^2+(x1-1)^2+100*(x3-x2^2)^2+(x2-1)^2;
%     y = [y -ynew]
%     sigmaN=0;
    measurementNoise = [measurementNoise sigmaN];
    sample_count=sample_count+1;
    
    % Optimize hyperparameters
    [sigmaSE,lScale] = findHyperparams(x,y,'SE');
    if isinf(sigmaSE)
        sigmaSE = bestSigma;
        lScale = bestScale;
    else
        bestSigma = sigmaSE;
        bestScale = lScale;
    end
    bestSigma
    bestScale
    
    % Calculate covariance matrix
    K = getCovMat(x,sigmaSE,lScale,'SE');
    K = addNoiseToCovMat(K,measurementNoise);
    
    % Update GP
    k = zeros(1,sample_count);
    for j = 1:resolution
        for l = 1:sample_count
            k(l) = SEcov(xtot(:,j),x(:,l),sigmaSE,lScale,'SE');
        end
        mu(j) = k/K*y';
        s(j) = SEcov(ones(5,1),ones(5,1),sigmaSE,lScale,'SE')-k/K*k';
    end
%     [PI,at] = getNextSample(mu,y,s,explore_exploit);
%     ee = 20*exp(-numel(xInd)/4);
%     [PI,at] = getNextSample(mu,y,s,20*exp(-numel(xInd)/4));
    ee = 50*exp(-numel(xInd)/6);
    [PI,at] = getNextSample(mu,xInd,y,s,ee);
    xInd = [xInd;at];
    xAdd = xtot(:,at)
    x = [x xAdd];
    
    % Plot updated GP
    plotGP(mu,s,xInd,y,PI,at);
    drawnow
    
end