function covMat = getCovMat(x,sigma_f,lScale,mode)
    % This function returns the covariance matrix from the input vector x
    % and specified hyperparamter
    %
    % Author: Marco von Atzigen

    % Fill matrix
    K = zeros(size(x,2));
    for i = 1:size(x,2)
        for j = i:size(x,2)
            covvalue= SEcov(x(:,i),x(:,j),sigma_f,lScale,mode);
            K(j,i)=covvalue;
            K(i,j)=covvalue;

        end
    end
    
    % Return value
    covMat = K;
end

