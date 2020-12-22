# Experiment 1

## Experimental Setup

Number of iterations: 30

Ladder top to ground: 112 cm

Robot top to ground: 39 cm

Ladder top to robot top (d): 112 - 39 = 73 cm (constant for all 30 iterations)

Angle adjustment: +/- 10 degrees

## Optimization algorithm

Basic continuous Bayesian Optimization

```shell
$ cd BO/Python_code
$ python3 BO.py
```

## Results

Best target and parameters: 

21th iteration: 

{"target": 47.97, "params": {"x0": 62.81899407290316, "x1": -0.513156605998544, "x2": -0.0727497914906956, "x3": -0.22608827210224747, "x4": 0.9895745577982968}, "datetime": {"datetime": "2020-11-29 16:04:26", "elapsed": 1532.032768, "delta": 93.901487}}
