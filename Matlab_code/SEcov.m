function covariance = SEcov(input1,input2,sigma_f,l,mode)
    % This function calculates the square exponential covariance of two
    % inputs. Either the squared exponential or the Matern kernels can be
    % chosen.
    % Author: Marco von Atzigen
    
    switch mode
        case 'SE'
            % Calculate covariance
            covariance = (sigma_f^2)*exp((-1/2)*((norm(input1-input2))/l)^2);

        case 'Matern'
            % Calculate covariance
            covariance = (sigma_f^2)*(1+sqrt(5*(norm((input1-input2)./l))^2)+(5/3)*...
                (norm((input1-input2)./l))^2)*exp(-sqrt(5*((norm((input1-input2)./l)))^2));
    end
end

