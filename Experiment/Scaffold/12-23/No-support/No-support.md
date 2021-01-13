# Experiment (Dec. 23, Wed, Week16, No Support)

## Experimental Setup

* Number of iterations: 10

  * For each iteration (each set of parameters), we perform 3 times, and take the average of the fitness value.

* Support Configuration

  * Ladder top to ground $h1 = 112\ cm$

  * Robot top to ground $h2 = 32.5\ cm$
    * No support, constant $h2 = 32.5\ cm$ for iteration 1-10):
      * For iteration 1-10: $h2 = 32.5\ cm$

## Optimization algorithm

Basic continuous Bayesian Optimization

```shell
$ cd BO/Python_code
$ python3 BO.py
```

## Data & Results

```shell

0th iteration: 
next point to probe is:  {'x0': 85.02132028215445, 'x1': 0.4406489868843162, 'x2': -0.9997712503653102, 'x3': -0.39533485473632046, 'x4': -0.7064882183657739}
What is the fitness? (1st run) 64.05
What is the fitness? (2nd run) 64.37 
What is the fitness? (3rd run) 63.98
The average fitness is 64.133333

1th iteration: 
next point to probe is:  {'x0': 106.82538651938819, 'x1': 0.8973735648275183, 'x2': -0.5318671698003736, 'x3': 0.8657153995484621, 'x4': -0.48933793704676387}
What is the fitness? (1st run) 55.43
What is the fitness? (2nd run) 54.30
What is the fitness? (3rd run) 56.08
The average fitness is 55.270000

2th iteration: 
next point to probe is:  {'x0': 84.64390908396452, 'x1': 0.38764499479855913, 'x2': -1.0, 'x3': -0.43502881032985535, 'x4': -0.8879119625115148}
What is the fitness? (1st run) 55.67
What is the fitness? (2nd run) 53.87
What is the fitness? (3rd run) 62.98
The average fitness is 57.506667

3th iteration: 
next point to probe is:  {'x0': 104.17072819664224, 'x1': 0.38092067299502586, 'x2': -0.808271098028885, 'x3': 0.3492493805771042, 'x4': 0.3037531309479118}
What is the fitness? (1st run) 58.45
What is the fitness? (2nd run) 57.98
What is the fitness? (3rd run) 50.17
The average fitness is 55.533333

4th iteration: 
next point to probe is:  {'x0': 83.308652414564, 'x1': 0.8515044119531365, 'x2': 0.6975343604126887, 'x3': 0.17306789672384926, 'x4': -0.5612269735948754}
What is the fitness? (1st run) 66.10
What is the fitness? (2nd run) 65.24
What is the fitness? (3rd run) 70.73
The average fitness is 67.356667

5th iteration: 
next point to probe is:  {'x0': 64.85397105174661, 'x1': 0.6999355264582188, 'x2': 0.6025626494953895, 'x3': 0.37580747689057836, 'x4': 0.5120282427405647}
What is the fitness? (1st run) 69.51
What is the fitness? (2nd run) 58.71
What is the fitness? (3rd run) 71.26
The average fitness is 66.493333

6th iteration: 
next point to probe is:  {'x0': 74.03071157064987, 'x1': -0.725242105119827, 'x2': 0.7679230255244809, 'x3': -0.9882322265533063, 'x4': 0.4978138871647866}
What is the fitness? (1st run) 72.83
What is the fitness? (2nd run) 72.16
What is the fitness? (3rd run) 72.37
The average fitness is 72.453333

7th iteration: 
next point to probe is:  {'x0': 93.02663746099148, 'x1': -0.57189705179324, 'x2': 0.965333552839502, 'x3': -0.14728978038180074, 'x4': 0.6500978291753439}
What is the fitness? (1st run) 55.28
What is the fitness? (2nd run) 59.30
What is the fitness? (3rd run) 60.48
The average fitness is 58.353333

8th iteration: 
next point to probe is:  {'x0': 99.68042474891914, 'x1': 0.008494768818439136, 'x2': -0.4778550450712036, 'x3': 0.2446044225636672, 'x4': -0.18637985901492748}
What is the fitness? (1st run) 60.61
What is the fitness? (2nd run) 59.78
What is the fitness? (3rd run) 62.39
The average fitness is 60.926667

9th iteration: 
next point to probe is:  {'x0': 68.45056356546115, 'x1': -0.46632204777437103, 'x2': 0.7013022203015549, 'x3': -0.10200360458559943, 'x4': 0.4209869587500832}
What is the fitness? (1st run) 73.02
What is the fitness? (2nd run) 73.58
What is the fitness? (3rd run) 70.42
The average fitness is 72.340000

```
