import time
from bayes_opt import BayesianOptimization
from bayes_opt import UtilityFunction
from bayes_opt.logger import JSONLogger
from bayes_opt.event import Events

def black_box_function(x, y):
    """Function with unknown internals we wish to maximize.

    This is just serving as an example, for all intents and
    purposes think of the internals of this function, i.e.: the process
    which generates its output values, as unknown.
    """
    return -x ** 2 - (y - 1) ** 2 + 1

optimizer = BayesianOptimization(
    f=None,
    pbounds={'x': (-20, 20), 'y': (-20, 20)},
    verbose=2,
    random_state=1,
)

utility = UtilityFunction(kind="ucb", kappa=2.5, xi=0.0)

def main():
    file_name = time.strftime("%Y-%m-%d %H:%M:%S", time.localtime())
    logger = JSONLogger(path="./%s.json"%file_name)
    optimizer.subscribe(Events.OPTIMIZATION_STEP, logger)
    
    num_iter = 50;
    for i in range(num_iter):
        print("%dth iteration: " % i, end='')

        # Get back a suggestion for the next parameter combination the optimizer wants to probe.
        next_point_to_probe = optimizer.suggest(utility)
        print("next point to probe is: ", next_point_to_probe)

        # Evaluate your function at the suggested point however/whenever you like.
        target = black_box_function(**next_point_to_probe)

        # Tell the optimizer what target value was observed.
        optimizer.register(
            params=next_point_to_probe,
            target=target,
        )
    
    print("\nBest target and parameters: ")
    print(optimizer.max)

if __name__ == "__main__":
	main()
