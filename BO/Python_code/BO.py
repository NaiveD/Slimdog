import time
from bayes_opt import BayesianOptimization
from bayes_opt import UtilityFunction
from bayes_opt.logger import JSONLogger
from bayes_opt.event import Events

def black_box_function():
    """Function with unknown internals we wish to maximize.

    This is just serving as an example, for all intents and
    purposes think of the internals of this function, i.e.: the process
    which generates its output values, as unknown.
    """
    fitness1 = float(input("What is the fitness? (1st run) "))
    fitness2 = float(input("What is the fitness? (2nd run) "))
    fitness3 = float(input("What is the fitness? (3rd run) "))

    fitness = (fitness1 + fitness2 + fitness3)/3;

    print("The average fitness is %f\n" % fitness)
    return fitness


optimizer = BayesianOptimization(
    f=None,
    pbounds={'x0': (60, 120), 'x1': (-1, 1), 'x2': (-1, 1), 'x3': (-1, 1), 'x4': (-1, 1)},
    verbose=2,
    random_state=1,
)


utility = UtilityFunction(kind="ucb", kappa=2.5, xi=0.0)


if __name__ == "__main__":
    file_name = time.strftime("%Y-%m-%d_%H:%M:%S", time.localtime())
    logger = JSONLogger(path="./data/%s.json"%file_name)
    optimizer.subscribe(Events.OPTIMIZATION_STEP, logger)
    
    num_iter = 30;
    for i in range(num_iter):
        print("%dth iteration: " % i)

        # Get back a suggestion for the next parameter combination the optimizer wants to probe.
        next_point_to_probe = optimizer.suggest(utility)
        print("next point to probe is: ", next_point_to_probe)

        # Evaluate your function at the suggested point however/whenever you like.
        target = black_box_function()

        # Tell the optimizer what target value was observed.
        optimizer.register(
            params=next_point_to_probe,
            target=target,
        )
    
    print("\nBest target and parameters: ")
    print(optimizer.max)
