%% Tabula Rasa
clear all
close all
clc

%% Update Gaussian Process Model
% seed: 12345, 50*exp(-numel(xInd)/6)
% x = [1 1 1 1 1;3 4 11 11 20;3 7 11 21 1;1 1 1 21 21;1 7 1 1 21;3 7 11 1 9;...
%     3 1 1 16 6;1 7 11 21 15;1 1 11 10 1;3 7 1 12 13;3 1 11 1 21;1 7 1 21 1;...
%     1 7 1 15 1;1 1 1 21 1;1 1 4 21 1;3 1 3 21 1;1 2 3 21 1;1 1 4 20 1;...
%     1 1 4 21 2;1 1 5 21 1;1 1 3 21 1;1 2 4 21 1;2 1 4 21 1;1 1 4 20 2;...
%     1 2 2 21 1;1 2 1 21 1;3 1 2 21 2;1 2 2 20 1;3 2 2 21 1;2 1 1 21 2;...
%     1 3 1 21 1;1 2 1 20 1;2 1 2 21 2;2 1 1 20 2;3 2 1 20 1;1 1 1 20 2;...
%     2 2 2 21 1;3 1 2 21 1;1 1 1 20 1;1 1 1 21 2;1 2 1 19 1;2 1 1 21 1;...
%     3 7 11 19 2;2 7 11 20 2;2 7 11 19 2;3 1 1 21 1;1 7 11 20 2;...
%     2 7 1 21 2;2 7 1 20 1;2 6 1 20 2]';
% y = [0.3326,4.2319,1.5941,0.8195,0.1319,0.8267,4.0653,1.4823,0.9390,2.5160,...
%     0.8835,12.2024,10.6434,20.0654,23.2581,5.1302,13.9806,17.3120,19.7166,...
%     11.1697,11.9001,5.8921,4.8719,10.3084,31.7439,26.3487,4.40579,17.2500,...
%     3.2053,3.5363,18.1515,30.7334,4.7205,4.5429,3.2506,12.8536,4.4138,...
%     11.4584,24.6157,11.3089,10.3947,3.7516,1.0477,0.7613,0.7034,6.6910,...
%     0.7878,3.0320,3.4380];
% measurementNoise = [5.3574e-4,0.1014,0.0169,0.0014,4.2686e-5,0.0071,0.7501,...
%     0.0844,0.0110,0.2276,0.0070,0.4081,2.1443,4.4594,0.7515,0.5444,0.7661,...
%     0.7011,0.7256,0.4871,0.2859,0.3529,0.0174,0.3015,3.5136,2.5185,0.4642,...
%     1.5884,0.3046,0.0162,0.8519,3.2276,0.0208,0.0171,0.8831,0.6806,0.0246,...
%     1.6738,2.5983,0.8074,0.4512,0.0149,0.0078,0.0020,0.0023,1.4612,8.2350e-4,...
%     0.0342,0.0511];
x=ones(5,1);
procNoise = 10;
groups = [3 7 11 21 21];

% Set parameters
resolution = prod(groups);
explore_exploit = 1;

% Set start values
bestSigma = 1;
bestScale = 1;
mu = zeros(resolution,1);
s = procNoise*ones(resolution,1);
% x = [x,ones(5,1)];
PI = zeros(size(mu));

v = {};
for i = 1:length(groups)
    v{i} = 1:groups(i);
end
xtot = combvec(v{:});
% [~,index] = sort(xtot(1,:));
% xtot = xtot(:,index);

if isempty(x)
    xInd = 1;
    x = ones(5,1);
else
    [~,xInd] = ismember(x',xtot','rows');
    xInd(xInd==0) = [];
end

% Plot initial GP
plotGP(mu,s,xInd,y,PI,1);

% Iterate
for i = 1:15
    % Get input from user
    yAdd = input(sprintf('What is the measurement mean at [%0.0f,%0.0f,%0.0f,%0.0f,%0.0f]? ',...
        x(1,end),x(2,end),x(3,end),x(4,end),x(5,end)));
    y = [y yAdd];
    sigmaN = input('What is the measurement uncertainty? ');
    measurementNoise = [measurementNoise sigmaN];
    
    % Optimize hyperparameters
    [sigmaSE,lScale] = findHyperparams(x,y);
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
    K = getCovMat(x,sigmaSE,lScale);
    K = addNoiseToCovMat(K,measurementNoise);
    
    % Update GP
    k = zeros(1,size(x,2));
    for j = 1:resolution
        for l = 1:size(x,2)
            k(l) = SEcov(xtot(:,j),x(:,l),sigmaSE,lScale);
        end
        mu(j) = k/K*y';
        s(j) = SEcov(ones(5,1),ones(5,1),sigmaSE,lScale)-k/K*k';
    end
%     [PI,at] = getNextSample(mu,y,s,explore_exploit);
%     ee = 20*exp(-numel(xInd)/4);
%     [PI,at] = getNextSample(mu,y,s,20*exp(-numel(xInd)/4));
    ee = 50*exp(-numel(xInd)/6);
    [PI,at] = getNextSample(mu,xInd,y,s,ee);
    xInd = [xInd;at];
    xAdd = xtot(:,at);
    x = [x xAdd];
    
    % Plot updated GP
    plotGP(mu,s,xInd,y,PI,at);
end