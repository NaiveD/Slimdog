# Experiment 9

## Test Function

Modified SCHWEFEL FUNCTION (5-D)

Expected optimum: 100 at `(420.9687, 420.9687, 420.9687, 420.9687, 420.9687)`

```python
# E9: Modified SCHWEFEL FUNCTION (5-D)
# Expected optimum: 100 at (420.9687, 420.9687, 420.9687, 420.9687, 420.9687)

# Dimension 5
d = 5
fx = 418.9829 * d - (x1 * sin((abs(x1))**0.5) + x2 * sin((abs(x2))**0.5) + x3 * sin((abs(x3))**0.5) + x4 * sin((abs(x4))**0.5) + x5 * sin((abs(x5)**0.5)))
fx = -fx

# fx = fx * 10 + 100 # Scale and shift
fx = fx + 100
return fx
```

## Experiment Setup

* Parameter space: (-500, 500)^5
* Number of iterations: 30 RS + 300

## Results

### Continuous

```json
Best target and parameters:
{'target': -412.76852411954405, 'params': {'x1': 193.4419953976007, 'x2': 433.99632984394987, 'x3': -312.84747631290253, 'x4': 426.7328141949512, 'x5': -295.4438848129465}}
```

### Discrete

#### Setup1: para_space = list(np.arange(-500, 501, 1000/10)) # S1

```json
Best target and parameters:
{'target': -169.02399854474447, 'params': {'x1': 400.0, 'x2': 400.0, 'x3': 400.0, 'x4': 400.0, 'x5': 400.0}}
```

#### Setup3: para_space = list(np.arange(-500, 501, 1000/1000)) # S3

```json
Best target and parameters:
{'target': -438.63467030001357, 'params': {'x1': 210.0, 'x2': 406.0, 'x3': -307.0, 'x4': 404.0, 'x5': -292.0}}
```

#### Setup5: para_space = list(np.arange(-500, 501, 1000/100000)) # S5

```json
Best target and parameters:
{'target': -403.96486437464773, 'params': {'x1': 192.71999999936997, 'x2': 428.47999999915555, 'x3': -312.05000000017094, 'x4': 423.2299999991603, 'x5': -291.4300000001897}}
```

### AGP

#### Setup1

```python
def set_sparseness(i, num_iter):
    interval = (num_iter - 30) / 6

    if (i < 30 + interval):
        return 10
    elif (i < 30 + 2*interval):
        return 100
    elif (i < 30 + 3*interval):
        return 1000
    elif (i < 30 + 4*interval):
        return 10000
    elif (i < 30 + 5*interval):
        return 100000
    else:
        return None
```

```json
Best target and parameters:
{'target': -354.4214879635597, 'params': {'x1': 204.43999999935932, 'x2': 419.67999999916356, 'x3': -301.94000000018013, 'x4': 420.65999999916266, 'x5': -301.68000000018037}}
```

#### Setup2

```python
def set_sparseness(i, num_iter):
    interval = (num_iter - 30) / 4

    if (i < 30):
        return None
    elif (i < 30 + interval):
        return 10
    elif (i < 30 + 2*interval):
        return 1000
    elif (i < 30 + 3*interval):
        return 100000
    else:
        return None
```

```json
Best target and parameters:
{'target': 32.805140876700534, 'params': {'x1': 426.05999999915775, 'x2': 435.4599999991492, 'x3': 434.1599999991504, 'x4': 409.9399999991724, 'x5': 422.9299999991606}}
```
