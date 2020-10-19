import time
from math import *
from bayes_opt import BayesianOptimization
from bayes_opt import UtilityFunction
from bayes_opt.logger import JSONLogger
from bayes_opt.event import Events
import numpy as np

# def black_box_function(x1, x2):
def black_box_function(x1, x2, x3, x4, x5):
    # return function_discrete(x1, x2)
    return function_AGP(x1, x2, x3, x4, x5)


# def function_AGP(x1, x2):
def function_AGP(x1, x2, x3, x4, x5):
    # First 3 iterations as random search in the continuous space
    if i < 3:
        # E11
        return E11_func(x1, x2, x3, x4, x5)

    interval = set_sparseness(i, num_iter)
    if (interval != None):
        para_space1 = get_para_space(-2+1+88, 2+1+88, interval)
        para_space2 = get_para_space(-2+1+0.1324, 2+1+0.1324, interval)
        para_space3 = get_para_space(-2+1-0.4233, 2+1-0.4233, interval)
        para_space4 = get_para_space(-2+1+0.8023, 2+1+0.8023, interval)
        para_space5 = get_para_space(-2+1-0.6352, 2+1-0.6352, interval)

    else: # Last few iterations: continuous
        # E11
        return E11_func(x1, x2, x3, x4, x5)
                
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

    # E11
    return E11_func(x1, x2, x3, x4, x5)

# S3
def set_sparseness(i, num_iter):
    interval = (num_iter - 3) / 6

    if (i < 3 + interval):
        return 10
    elif (i < 3 + 2*interval):
        return 20
    elif (i < 3 + 3*interval):
        return 40
    elif (i < 3 + 4*interval):
        return 80
    elif (i < 3 + 5*interval):
        return 160
    else:
        return None


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


def get_para_space(lower, upper, interval):
    return list(np.arange(lower, upper+1, (upper-lower)/interval))


if __name__ == "__main__":
    optimizer = BayesianOptimization(
        f=None,
        # pbounds={'x1': (-10, 10), 'x2': (-10, 10)},
        pbounds={'x1': (-2+1+88, 2+1+88), 'x2': (-2+1+0.1324, 2+1+0.1324), 'x3': (-2+1-0.4233, 2+1-0.4233), 'x4': (-2+1+0.8023, 2+1+0.8023), 'x5': (-2+1-0.6352, 2+1-0.6352)},
        verbose=2,
        random_state=1,
    )

    utility = UtilityFunction(kind="ucb", kappa=2.5, xi=0.0)

    file_name = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    # file_name = "AGP"
    logger = JSONLogger(path="./AGP/AGP_%s.json"%file_name)
    optimizer.subscribe(Events.OPTIMIZATION_STEP, logger)
    
    num_iter = 3 + 300; # First 20 iterations as random search in the continuous space

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
