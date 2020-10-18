import time
from math import *
from bayes_opt import BayesianOptimization
from bayes_opt import UtilityFunction
from bayes_opt.logger import JSONLogger
from bayes_opt.event import Events
import numpy as np

# def black_box_function(x1, x2):
def black_box_function(x1, x2, x3, x4, x5):
    """Function with unknown internals we wish to maximize.

    This is just serving as an example, for all intents and
    purposes think of the internals of this function, i.e.: the process
    which generates its output values, as unknown.
    """

    # return function_discrete(x1, x2)
    return function_discrete(x1, x2, x3, x4, x5)


# def function_discrete(x1, x2):
def function_discrete(x1, x2, x3, x4, x5):
    # First 10 iterations as random search in the continuous space
    if i < 10:
        x1 = x1 - 2.4563
        x2 = x2 + 7.4325
        x3 = x3 - 4.4224
        x4 = x4 - 10.6642
        x5 = x5 + 12.2141

        result = -20*exp(-0.2*sqrt((1/5)*(x1**2+x2**2+x3**2+x4**2+x5**2)))-exp((1/5)*(cos(2*pi*x1)+cos(2*pi*x2)+cos(2*pi*x3)+cos(2*pi*x4)+cos(2*pi*x5)))+exp(1)+20
        return -result    

    # Get the discrete Parameters 
    elif (10 <= i < 25): # divide the parameter space into 10 discrete values 
        para_space = list(np.arange(-20, 21, 40/10))
    elif (25 <= i < 40): # divide the parameter space into 100 discrete values 
        para_space = list(np.arange(-100, 101, 200/100))
    elif (40 <= i < 55): # divide the parameter space into 1000 discrete values 
        para_space = list(np.arange(-100, 101, 200/1000))
    elif (55 <= i < 70): # divide the parameter space into 10000 discrete values 
        para_space = list(np.arange(-100, 101, 200/10000))
    elif (70 <= i < 85): # divide the parameter space into 100000 discrete values 
        para_space = list(np.arange(-100, 101, 200/100000))
    else: # (85 <= i < 110) just take the continuous value
        x1 = x1 - 2.4563
        x2 = x2 + 7.4325
        x3 = x3 - 4.4224
        x4 = x4 - 10.6642
        x5 = x5 + 12.2141

        result = -20*exp(-0.2*sqrt((1/5)*(x1**2+x2**2+x3**2+x4**2+x5**2)))-exp((1/5)*(cos(2*pi*x1)+cos(2*pi*x2)+cos(2*pi*x3)+cos(2*pi*x4)+cos(2*pi*x5)))+exp(1)+20
        return -result
                
    # Find the closest value of x1 and x2 in the parameter space
    x1 = min(para_space, key=lambda x:abs(x-x1))
    x2 = min(para_space, key=lambda x:abs(x-x2))
    x3 = min(para_space, key=lambda x:abs(x-x3))
    x4 = min(para_space, key=lambda x:abs(x-x4))
    x5 = min(para_space, key=lambda x:abs(x-x5))

    next_point_to_probe['x1'] = x1
    next_point_to_probe['x2'] = x2
    next_point_to_probe['x3'] = x3
    next_point_to_probe['x4'] = x4
    next_point_to_probe['x5'] = x5

    # E1: Rastrigin's function (shifted)
    # return -(20 + x1**2 + x2**2 - 10 * (cos(2*pi*x1) + cos(2*pi*x2)))

    # E2: Rastrigin's function (shifted)
    # return -(20 + (x1-2)**2 + (x2+2)**2 - 10 * (cos(2*pi*(x1-2)) + cos(2*pi*(x2+2))))
    
    # E3: SCHAFFER FUNCTION
    # return 0.5 + (sin(x1**2-x2**2)**2-0.5)/(1+0.001*(x1**2+x2**2))**2

    # E4: SCHAFFER FUNCTION (shifted)
    # return 0.5 - (sin((x1-2)**2-(x2+2)**2)**2-0.5)/(1+0.001*((x1-2)**2+(x2+2)**2))**2

    # E5: Ackley function (5-D)
    # result = -20*exp(-0.2*sqrt((1/5)*(x1**2+x2**2+x3**2+x4**2+x5**2)))-exp((1/5)*(cos(2*pi*x1)+cos(2*pi*x2)+cos(2*pi*x3)+cos(2*pi*x4)+cos(2*pi*x5)))+exp(1)+20
    # return -result
    
    # E6: Ackley function (5-D)
    # result = -20*exp(-0.2*sqrt((1/5)*(x1**2+x2**2+x3**2+x4**2+x5**2)))-exp((1/5)*(cos(2*pi*x1)+cos(2*pi*x2)+cos(2*pi*x3)+cos(2*pi*x4)+cos(2*pi*x5)))+exp(1)+20
    # return -result
    
    # E7: Shifted Ackley function (5-D) 
    # Expected optimum: 0 at (2.4563, -7.4325, 4.4224, 10.6642, -12.2141)    
    x1 = x1 - 2.4563
    x2 = x2 + 7.4325
    x3 = x3 - 4.4224
    x4 = x4 - 10.6642
    x5 = x5 + 12.2141

    result = -20*exp(-0.2*sqrt((1/5)*(x1**2+x2**2+x3**2+x4**2+x5**2)))-exp((1/5)*(cos(2*pi*x1)+cos(2*pi*x2)+cos(2*pi*x3)+cos(2*pi*x4)+cos(2*pi*x5)))+exp(1)+20
    return -result

if __name__ == "__main__":
    optimizer = BayesianOptimization(
        f=None,
        # pbounds={'x1': (-10, 10), 'x2': (-10, 10)},
        pbounds={'x1': (-20, 20), 'x2': (-20, 20), 'x3': (-20, 20), 'x4': (-20, 20), 'x5': (-20, 20)},
        verbose=2,
        random_state=1,
    )

    utility = UtilityFunction(kind="ucb", kappa=2.5, xi=0.0)

    file_name = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    # file_name = "AGP"
    logger = JSONLogger(path="./AGP/AGP_%s.json"%file_name)
    optimizer.subscribe(Events.OPTIMIZATION_STEP, logger)
    
    num_iter = 10 + 100; # First 10 iterations as random search in the continuous space

    # for i in range(num_iter):
    i = 0
    while i < num_iter:
        print("%dth iteration: " % i, end='')
        i += 1

        # Get back a suggestion for the next parameter combination the optimizer wants to probe.
        next_point_to_probe = optimizer.suggest(utility)
        print("next point to probe (continuous) is: ", next_point_to_probe)

        # Evaluate your function at the suggested point however/whenever you like.
        target = black_box_function(**next_point_to_probe)

        print("next_point_to_probe (AGP) is: ", next_point_to_probe)
        print("target = ", target)

        # If current set of parameters has already been explored, continue to next iteration
        if (optimizer.is_in(next_point_to_probe) == True):
            print("Parameters already exists!")
            i -= 1

        # Tell the optimizer what target value was observed.
        optimizer.register(
            params=next_point_to_probe,
            target=target,
        )

        # if all values are explored, break the loop
        # space_counter += 1
        # if (space_counter >= 5**len(list(np.arange(-20, 21, 40/10)))):
        #     break
    
    print("\nBest target and parameters: ")
    print(optimizer.max)
