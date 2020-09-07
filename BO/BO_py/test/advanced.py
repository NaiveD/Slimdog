from bayes_opt import  BayesianOptimization
#建议、评估
#定义一个函数，边界并实例化一个对象
def black_box_function(x,y):
    return -x ** 2 - (y - 1) ** 2 + 1

optimizer = BayesianOptimization(
    f=None,
    pbounds={'x':(-2,2),'y':(-3,3)},
    verbose=2,
    random_state=1,)

from bayes_opt import UtilityFunction
utility = UtilityFunction(kind="ucb",kappa=2.5,xi=0.0)



next_point_to_probe = optimizer.suggest(utility)
print("Next point to probe is:", next_point_to_probe)

target = black_box_function(**next_point_to_probe)
print("Found the target value to be:", target)

optimizer.register(params=next_point_to_probe,target=target)



#最大化循环
for _ in range(5):
    next_point = optimizer.suggest(utility)
    target = black_box_function(**next_point)
    optimizer.register(params=next_point,target=target)
    print(next_point,target)
print(optimizer.max)