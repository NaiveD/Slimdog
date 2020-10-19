# Experiment 10

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
* Number of iterations: 3 RS + 300

## Results

### Continuous

3 RS + 300

```json
Best target and parameters: 
{'target': -412.76852411954405, 'params': {'x1': 193.4419953976007, 'x2': 433.99632984394987, 'x3': -312.84747631290253, 'x4': 426.7328141949512, 'x5': -295.4438848129465}}
```

3 RS + 50

```json
Best target and parameters: 
{'target': -592.2379567625226, 'params': {'x1': 211.48546978905725, 'x2': 456.8095551752897, 'x3': -317.5501777835976, 'x4': 437.56269095465404, 'x5': -292.1039317105284}}
```

### Discrete

#### Setup1: para_space = list(np.arange(-500, 501, 1000/10)) # S1

3 RS + 300

```json
Best target and parameters: 
{'target': -610.6789930861171, 'params': {'x1': -100.0, 'x2': -300.0, 'x3': 400.0, 'x4': 400.0, 'x5': -300.0}}
```

#### Setup3: para_space = list(np.arange(-500, 501, 1000/1000)) # S3

#### Setup4: para_space = list(np.arange(-500, 501, 1000/10000)) # S3

#### Setup5: para_space = list(np.arange(-500, 501, 1000/100000)) # S5

3 RS + 300

```json
Best target and parameters: 
{'target': -381.26766817397333, 'params': {'x1': 197.38999999936573, 'x2': 431.6299999991527, 'x3': -304.290000000178, 'x4': 427.47999999915646, 'x5': -298.5700000001832}}
```

3 RS + 50

```json
Best target and parameters: 
{'target': -560.5069062984267, 'params': {'x1': 211.11999999935324, 'x2': 454.0599999991323, 'x3': -317.8200000001657, 'x4': 434.18999999915036, 'x5': -291.3000000001898}}
```


### AGP

#### Setup1

```python
def set_sparseness(i, num_iter):
    interval = (num_iter - 3) / 6

    if (i < 3 + interval):
        return 10
    elif (i < 3 + 2*interval):
        return 100
    elif (i < 3 + 3*interval):
        return 1000
    elif (i < 3 + 4*interval):
        return 10000
    elif (i < 3 + 5*interval):
        return 100000
    else:
        return None
```

3 RS + 300

```json
Best target and parameters: 
{'target': -139.13267883539243, 'params': {'x1': 419.03649681009256, 'x2': 418.8265947972211, 'x3': -302.7053027172134, 'x4': 419.4003118646444, 'x5': -305.17846075882477}}
```

3 RS + 50

```json
Best target and parameters: 
{'target': -736.1494887966353, 'params': {'x1': 223.977817679415, 'x2': 405.5967788770961, 'x3': -306.21475380755413, 'x4': 421.321124182397, 'x5': -157.92751923555286}}
```

#### Setup2

```python
def set_sparseness(i, num_iter):
    interval = (num_iter - 3) / 4

    if (i < 3):
        return None
    elif (i < 3 + interval):
        return 10
    elif (i < 3 + 2*interval):
        return 1000
    elif (i < 3 + 3*interval):
        return 100000
    else:
        return None
```

3 RS + 300

```json
Best target and parameters: 
{'target': -315.0907116255664, 'params': {'x1': 420.6947119815532, 'x2': 420.0325567502746, 'x3': -300.9473869971323, 'x4': 420.3034780431317, 'x5': -124.17667290363293}}
```

#### Setup3

```python
def set_sparseness(i, num_iter):
    interval = (num_iter - 3) / 6

    if (i < 3 + interval):
        return 10
    elif (i < 3 + 2*interval):
        return 20
    elif (i < 3 + 3*interval):
        return 40
    elif (i < 3 + 4*interval):
        return 80
    elif (i < 3 + 5*interval):
        return 160
    else:
        return None
```

3 RS + 300

```json
Best target and parameters: 
{'target': -138.314558559332, 'params': {'x1': 419.8661600747861, 'x2': 421.4366872709218, 'x3': -301.2958492315889, 'x4': 418.0669438129873, 'x5': -302.3301021999627}}
```

3 RS + 50

```json
Best target and parameters: 
{'target': -764.1096146476903, 'params': {'x1': -324.3126552079803, 'x2': 399.7081302754615, 'x3': -250.91804689910666, 'x4': 406.6394889787071, 'x5': 208.70583139782403}}
```