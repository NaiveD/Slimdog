function [PI,nextSample] = getNextSample(mu,xInd,y,s,epsilon)
    % This function returns the maximum probability of improvement. Doing
    % this the algorithm suggest where to sample the cost function next.
    % 
    % Author: Marco von Atzigen
    
    %rng(12345);
    
    % Calculate and maximize probability of improvement
    PI = 0.5*(1+erf((mu-max(y)-epsilon)./(sqrt(2*s))));
    
    % If epsilon too big, PI gets zero.
    % Maximize argument instead (ok, since CDF monotonous increasing)
    if ~any(PI > 0)
        PI = (mu-max(y)-epsilon)./(sqrt(2*s));
    end

    % Find max
    valid = false;
    while ~valid
        maxVal = max(PI);
        idx = find(PI == maxVal);
        if numel(idx) > 1
            randChoice = randi([1 numel(idx)],1);
        else
            randChoice = 1;
        end    
        nextSample = idx(randChoice);

        % Skip next sample if it was seen before
        if ismember(nextSample,xInd)
            PI(idx(randChoice)) = [];
            disp('Skipped!')
        else
            valid = true;
        end
    end
end