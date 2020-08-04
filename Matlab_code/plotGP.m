function [] = plotGP(mu,s,x,y,PI,at)
    % This function plots the measured data and the Gaussian Process
    % representation.
    % Author: Marco von Atzigen
    
    % Calculate boundaries
    f = [mu+sqrt(s);zeros(size(mu))];
    t = 1:length(mu);
    
    % Plot
    if isempty(findall(0,'Type','Figure'))
        figure(1)
    end
    clf
    subplot(2,1,1)
    hold on
    fi = fill([t';flip(t',1)],f,[0 114 189]/255);
    set(fi,'FaceAlpha',0.5);
    plot(t', mu)
    if length(y) > 1
        plot(x(1:end-1), y, '+', 'LineWidth', 1)
    end
    plot([x(end) x(end)],[-200 400],'k:')
    hold off
    grid on
    title('Bayesian Optimization')
    ylabel('Fitness')
    %axis([0 length(mu) -1.1*max(mu+sqrt(s)) 1.1*max(mu+sqrt(s))])
    axis([0 length(mu) -200 400])

    subplot(2,1,2)
    hold on
    plot(PI/max(PI))
    plot(at,PI(at)/max(PI),'ro')
    hold off
    xlim([0 length(mu)])
    %ylim([0 1.1])
    grid on
    xlabel('Input Space')
    ylabel('Acquisition Function')
end