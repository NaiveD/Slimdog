# Experiment (Dec. 23, Wed, Week16, Reducing Support)

## Experimental Setup

* Number of iterations: 50

  * For each iteration (each set of parameters), we perform 3 times, and take the average of the fitness value.

* Support Configuration

  * Ladder top to ground $h1 = 112\ cm$

  * Robot top to ground $h2 = (48\rightarrow 45\rightarrow 42 \rightarrow 39)\ cm$

  * Ladder top to robot top $d = h1 - h2 = 112 - (48 \rightarrow 45\rightarrow 42\rightarrow 39) = (64\rightarrow67\rightarrow 70\rightarrow 73)\ cm$
    * Reducing support, the robot relies on itself more through iterations:
      * For iteration 1-10: $d = 64\ cm$
      * For iteration 11-20: $d = 67\ cm$
      * For iteration 21-30: $d = 70\ cm$
      * For iteration 31-50: $d = 73\ cm$ (minimum support)

## Optimization algorithm

Basic continuous Bayesian Optimization

```shell
$ cd BO/Python_code
$ python3 BO.py
```

## Results

Best target and parameters:
