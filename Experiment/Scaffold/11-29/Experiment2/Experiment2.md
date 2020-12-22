# Experiment 2

## Experimental Setup

Number of iterations: 30 (10+10+10)

Ladder top to ground: 112 cm

Robot top to ground: 47 cm - 44 cm - 39 cm (high to low)

Ladder top to robot top (d): 65 cm - 68 cm - 73 cm (each for 10 iterations, increasing d)

Angle adjustment: +/- 10 degrees

## Optimization algorithm

Basic continuous Bayesian Optimization

```shell
$ cd BO/Python_code
$ python3 BO.py
```

## Results

Best target and parameters: 

27th iteration: 

{'target': 49.28, 'params': {'x0': 62.83261259247719, 'x1': -0.7489911231879385, 'x2': -0.0028128377528728876, 'x3': 0.04002888698939344, 'x4': 0.751573418757282}}