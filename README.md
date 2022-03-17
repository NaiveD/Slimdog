# Slimdog Project

## Publication
**Keyan Zhai**, Chu'an Li, and Andre Rosendo. "Scaffolded Learning of In-place Trotting Gait for a Quadruped Robot with Bayesian Optimization." 16th International Conference on Intelligent Autonomous Systems ([IAS-16](https://www.ias-16.com/)) [[arXiv](https://arxiv.org/abs/2101.09961)][[Demo](https://keyanzhai.cool/2020/11/19/Slimdog/)]



## Run Experiments

1. Get the parameters by running

```shell
$ cd BO/Python_code
$ python3 BO.py
```

2. Set the parameters and run `main/main.ino` in Arduino.

3. Run strain_gauge program. Switch on the button when the prompt shows.

4. Get results from the strain gage as the fitness.

5. Input fitness to `BO.py`, ge next set of parameters, repeat from step 2.
