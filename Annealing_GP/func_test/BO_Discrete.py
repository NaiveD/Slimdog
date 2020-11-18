import time
from math import *
from bayes_opt import BayesianOptimization
from bayes_opt import UtilityFunction
from bayes_opt.logger import JSONLogger
from bayes_opt.event import Events
import numpy as np

# pbounds={'x1': (-1+88, 1+88), 'x2': (-1+0.1324, 1+0.1324), 'x3': (-1-0.4233, 1-0.4233), 'x4': (-1+0.8023, 1+0.8023), 'x5': (-1-0.6352, 1-0.6352)},
x1_low = -1.5+88
x1_high = 1.5+88
x2_low = -1.5+0.1324
x2_high = 1.5+0.1324
x3_low = -1.5-0.4233
x3_high = 1.5-0.4233
x4_low = -1.5+0.8023
x4_high = 1.5+0.8023
x5_low = -1.5-0.6352
x5_high = 1.5-0.6352


# def black_box_function(x1, x2):
def black_box_function(x1, x2, x3, x4, x5):
    # return function_discrete(x1, x2)
    return function_discrete(x1, x2, x3, x4, x5)


# def function_discrete(x1, x2):
def function_discrete(x1, x2, x3, x4, x5):
    # First 3 iterations as random search in the continuous space
    if i < 4:
        # E12
        return E12_func(x1, x2, x3, x4, x5)

    # Get the discrete Parameters 
    # Divide the parameter space into 10/100/1000/10000/100000 discrete values 
    interval = 1000

    para_space1 = get_para_space(x1_low, x1_high, interval)
    para_space2 = get_para_space(x2_low, x2_high, interval)
    para_space3 = get_para_space(x3_low, x3_high, interval)
    para_space4 = get_para_space(x4_low, x4_high, interval)
    para_space5 = get_para_space(x5_low, x5_high, interval)
        
    # Find the closest value of x1 and x2 in the parameter space
    x1 = min(para_space1, key=lambda x:abs(x-x1))
    x2 = min(para_space2, key=lambda x:abs(x-x2))
    x3 = min(para_space3, key=lambda x:abs(x-x3))
    x4 = min(para_space4, key=lambda x:abs(x-x4))
    x5 = min(para_space5, key=lambda x:abs(x-x5))

    next_point_to_probe['x1'] = x1
    next_point_to_probe['x2'] = x2
    next_point_to_probe['x3'] = x3
    next_point_to_probe['x4'] = x4
    next_point_to_probe['x5'] = x5

    # E12
    return E12_func(x1, x2, x3, x4, x5)

    
def E11_func(x1, x2, x3, x4, x5):
    # E11: Shifted Happy Cat Function (5-D)
    # Expected optimum: 100 at `(88, 0.1324, -0.4233, 0.8012, -0.6352)`

    # Dimension 5
    d = 5

    # Shift the parameters
    x1 = x1 - 1 - 88
    x2 = x2 - 1 - 0.1324
    x3 = x3 - 1 + 0.4233
    x4 = x4 - 1 - 0.8012
    x5 = x5 - 1 + 0.6352

    alpha = 1/8

    xx = x1*x1 + x2*x2 + x3*x3 + x4*x4 + x5*x5

    fx = ((xx-d)**2)**alpha + 1/d * (1/2 * xx + x1 + x2 + x3 + x4 + x5) + 1/2
    fx = -fx
    fx = fx * 10 + 100

    return fx


def E12_func(x1, x2, x3, x4, x5):
    # E12: Xin-She Yang N. 3 Function (5-D)
    # Expected optimum: 100 at `(88, 0.1324, -0.4233, 0.8012, -0.6352)`
    # Shift the parameters
    x1 = x1 - 0 - 88
    x2 = x2 - 0 - 0.1324
    x3 = x3 - 0 + 0.4233
    x4 = x4 - 0 - 0.8012
    x5 = x5 - 0 + 0.6352

    m = 5
    beta = 15

    fx = exp(-((x1/beta)**(2*m) +(x2/beta)**(2*m) + (x3/beta)**(2*m) + (x4/beta)**(2*m) +  (x5/beta)**(2*m))) - 2 * exp(-(x1**2+x2**2+x3**2+x4**2+x5**2)) * (cos(x1))**2 * (cos(x2))**2 * (cos(x3))**2 * (cos(x4))**2 * (cos(x5))**2
    fx = -fx
    fx = fx * 100

    return fx


def get_para_space(lower, upper, interval):
    return list(np.arange(lower, upper+1, (upper-lower)/interval))


if __name__ == "__main__":
    optimizer = BayesianOptimization(
        f=None,
        # pbounds={'x1': (-10, 10), 'x2': (-10, 10)},
        # pbounds={'x1': (-2+1+88, 2+1+88), 'x2': (-2+1+0.1324, 2+1+0.1324), 'x3': (-2+1-0.4233, 2+1-0.4233), 'x4': (-2+1+0.8023, 2+1+0.8023), 'x5': (-2+1-0.6352, 2+1-0.6352)},
        # pbounds={'x1': (-2*pi+88, 2*pi+88), 'x2': (-2*pi+0.1324, 2*pi+0.1324), 'x3': (-2*pi-0.4233, 2*pi-0.4233), 'x4': (-2*pi+0.8023, 2*pi+0.8023), 'x5': (-2*pi-0.6352, 2*pi-0.6352)},
        pbounds={'x1': (x1_low, x1_high), 'x2': (x2_low, x2_high), 'x3': (x3_low, x3_high), 'x4': (x4_low, x4_high), 'x5': (x5_low, x5_high)},
        verbose=2,
        random_state=1,
    )

    utility = UtilityFunction(kind="ucb", kappa=2.5, xi=0.0)

    file_name = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    # file_name = "Discrete"
    logger = JSONLogger(path="./Discrete/Discrete_%s.json"%file_name)
    optimizer.subscribe(Events.OPTIMIZATION_STEP, logger)
        
    num_iter = 3 + 100; # First 20 iterations as random search in the continuous space
    
    # for i in range(num_iter):
    i = 0
    while i < num_iter:
        print("%dth iteration: " % (i+1), end='')
        i += 1
        
        # Get back a suggestion for the next parameter combination the optimizer wants to probe.
        next_point_to_probe = optimizer.suggest(utility)
        print("next point to probe (continuous) is: ", next_point_to_probe)

        # Evaluate your function at the suggested point however/whenever you like.
        target = black_box_function(**next_point_to_probe)

        print("next_point_to_probe (discrete) is: ", next_point_to_probe)
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

