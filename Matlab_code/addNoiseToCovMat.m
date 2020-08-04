function covMat = addNoiseToCovMat(K,noise)
    % This function adds measurement noise to the covariance matrix.
    %
    % Author: Marco von Atzigen
    
    for i = 1:length(noise)
        K(i,i) = K(i,i) + noise(i)^2;
    end
    
    % Return value
    covMat = K;
end