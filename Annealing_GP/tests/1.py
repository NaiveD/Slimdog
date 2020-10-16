from bayes_opt import BayesianOptimization
from bayes_opt import UtilityFunction


# Let's start by definying our function, bounds, and instanciating an optimization object.
def black_box_function(x, y):
    return function_discrete(x, y)

def function_discrete(x, y):
    x = int(x)
    y = int(y)
    next_point_to_probe['x'] = x
    next_point_to_probe['y'] = y
    return -x ** 2 - (y - 1) ** 2 + 1


optimizer = BayesianOptimization(
    f=None,
    pbounds={'x': (-2, 2), 'y': (-3, 3)},
    verbose=2,
    random_state=1,
)

utility = UtilityFunction(kind="ucb", kappa=2.5, xi=0.0)

next_point_to_probe = optimizer.suggest(utility)
print("Next point to probe is:", next_point_to_probe)

target = black_box_function(**next_point_to_probe)
print("Next point (discrete) to probe is:", next_point_to_probe)
print("Found the target value to be:", target)

optimizer.register(
    params=next_point_to_probe,
    target=target,
)