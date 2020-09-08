function [bestSigma, bestScale] = findHyperparams(x,f,mode)
%x=[];
%f=[];
%mode='SE';
    % This function maximizes the marginal likelihood in order to optimize
    % the hyperparameters. It samples broadly first and then refines the
    % search.
    %
    % Author: Marco von Atzigen
    
    maxIter = 100;
    
    % Clear warnings
    lastwarn('');
    margLikMax = -inf;
    
    % Loop through sigma and lScale
    for sigma_f = 1:1:maxIter
        for lScale = 1:1:maxIter
            try
                % Get covariance Matrix and calculate log marginal
                % likelihood
                K = getCovMat(x,sigma_f,lScale,mode);
                margLik = -0.5*f/K*f'-0.5*log(det(K))-abs(x)/2*log(2*pi);
                [~,id] = lastwarn;
                % Prepare and thow error if warning detected
                if strcmp(id,'MATLAB:nearlySingularMatrix')
                    errorstruct.message = '';
                    errorstruct.identifier = 'MATLAB:nearlySingularMatrix';
                    error(errorstruct);
                end
            % Catch warning
            catch warn
                if strcmp(warn.identifier,'MATLAB:nearlySingularMatrix');
                    bestSigma = inf;
                    bestScale = inf;
                    disp('Close to singularity! Leave hyperparamter unchanged.')
                    break;
                end
            end
            % Compare likelihoods
            if margLik > margLikMax
                margLikMax = margLik;
                bestSigma = sigma_f;
                bestScale = lScale;
            end
        end
    end
    sigmaCounter = bestSigma;
    scaleCounter = bestScale;
    
    margLikMax = -inf;
    % Loop through sigma and lScale
    for sigma_f = sigmaCounter-0.99:0.1:sigmaCounter+1
        for lScale = scaleCounter-0.99:0.1:scaleCounter+1
            try
                % Get covariance Matrix and calculate log marginal
                % likelihood
                K = getCovMat(x,sigma_f,lScale);
                margLik = -0.5*f/K*f'-0.5*log(det(K))-abs(x)/2*log(2*pi);
                [~,id] = lastwarn;
                % Prepare and thow error if warning detected
                if strcmp(id,'MATLAB:nearlySingularMatrix')
                    errorstruct.message = '';
                    errorstruct.identifier = 'MATLAB:nearlySingularMatrix';
                    error(errorstruct);
                end
            % Catch warning
            catch warn
                if strcmp(warn.identifier,'MATLAB:nearlySingularMatrix');
                    bestSigma = inf;
                    bestScale = inf;
                    disp('Close to singularity! Leave hyperparamter unchanged.')
                    break;
                end
            end
            % Compare likelihoods
            if margLik > margLikMax
                margLikMax = margLik;
                bestSigma = sigma_f;
                bestScale = lScale;
            end
        end
    end
end