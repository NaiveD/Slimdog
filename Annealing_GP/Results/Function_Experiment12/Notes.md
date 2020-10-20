# Experiment 12

## Test Function

**Xin-She Yang N. 3 Function (5D):** <http://benchmarkfcns.xyz/benchmarkfcns/xinsheyangn3fcn.html>

Expected optimum: 100 at `(88, 0.1324, -0.4233, 0.8012, -0.6352)`

```python
def E12_func(x1, x2, x3, x4, x5):
    # E12: Xin-She Yang N. 3 Function (5-D)
    # Expected optimum: 100 at `(88, 0.1324, -0.4233, 0.8012, -0.6352)`
    # Shift the parameters
    x1 = x1 - 0 - 88
    x2 = x2 - 0 - 0.1324
    x3 = x3 - 0 + 0.4233
    x4 = x4 - 0 - 0.8012
    x5 = x5 - 0 + 0.6352

    m = 5
    beta = 15

    fx = exp(-((x1/beta)**(2*m) +(x2/beta)**(2*m) + (x3/beta)**(2*m) + (x4/beta)**(2*m) +  (x5/beta)**(2*m))) - 2 * exp(-(x1**2+x2**2+x3**2+x4**2+x5**2)) * (cos(x1))**2 * (cos(x2))**2 * (cos(x3))**2 * (cos(x4))**2 * (cos(x5))**2
    fx = -fx
    fx = fx * 100

    return fx
```

## Experiment Setup

* Parameter space 1: `pbounds={'x1': (-2*pi+88, 2*pi+88), 'x2': (-2*pi+0.1324, 2*pi+0.1324), 'x3': (-2*pi-0.4233, 2*pi-0.4233), 'x4': (-2*pi+0.8023, 2*pi+0.8023), 'x5': (-2*pi-0.6352, 2*pi-0.6352)},`
* Number of iterations: 3 RS + 300, 3RS + 50
* Parameter space 2: `pbounds={'x1': (-1+88, 1+88), 'x2': (-1+0.1324, 1+0.1324), 'x3': (-1-0.4233, 1-0.4233), 'x4': (-1+0.8023, 1+0.8023), 'x5': (-1-0.6352, 1-0.6352)},`
* Number of iterations: 3 RS + 100

## Results

### Continuous

* Parameter Space 1

* 3 RS + 300

```json
Best target and parameters: 
{'target': -99.91685662518272, 'params': {'x1': 81.7168146928204, 'x2': -6.150785307179587, 'x3': -6.7064853071795865, 'x4': 7.085485307179586, 'x5': -6.918385307179586}}
```

* 3 RS + 50

```json
Best target and parameters: 
{'target': -99.91685662518272, 'params': {'x1': 81.7168146928204, 'x2': -6.150785307179587, 'x3': -6.7064853071795865, 'x4': 7.085485307179586, 'x5': -6.918385307179586}}
```

* Parameter Space 2
  
 3 RS + 100

```json
Best target and parameters: 
{'target': 99.99119586554299, 'params': {'x1': 87.99997971579963, 'x2': 0.13498460486346725, 'x3': -0.41948569786388606, 'x4': 0.8006809133853552, 'x5': -0.6359154395694298}}
```

### Discrete

#### Setup1: para_space = list(np.arange(-500, 501, 1000/10)) # S1

* 3 RS + 300

```json
Best target and parameters: 
{'target': -99.91685662518272, 'params': {'x1': 81.7168146928204, 'x2': 6.415585307179586, 'x3': -6.7064853071795865, 'x4': 7.085485307179586, 'x5': 5.647985307179586}}
```

* 3 RS + 50

```json
Best target and parameters: 
{'target': -99.91685662518272, 'params': {'x1': 81.7168146928204, 'x2': 6.415585307179586, 'x3': -6.7064853071795865, 'x4': 7.085485307179586, 'x5': 5.647985307179586}}
```

#### Setup3: para_space = list(np.arange(-500, 501, 1000/1000)) # S3

* Parameter Space 1

* 3 RS + 300

```json
Best target and parameters: 
{'target': -99.91685662518253, 'params': {'x1': 94.2831853071859, 'x2': -6.150785307179587, 'x3': 5.859885307179693, 'x4': 7.085485307179693, 'x5': 5.647985307179693}}
```

* 3 RS + 50

```json
Best target and parameters: 
{'target': -99.91685662518253, 'params': {'x1': 94.2831853071859, 'x2': -6.150785307179587, 'x3': 5.859885307179693, 'x4': 7.085485307179693, 'x5': 5.647985307179693}}
```

* Parameter Space2

* 3 RS + 100

```json
Best target and parameters: 
{'target': 99.9959160389487, 'params': {'x1': 88.00000000000006, 'x2': 0.1323999999999459, 'x3': -0.4203000000000543, 'x4': 0.8023000000000013, 'x5': -0.6351999999999434}}
```


#### Setup5: para_space = list(np.arange(-500, 501, 1000/100000)) # S5

* 3 RS + 300

```json
Best target and parameters: 
{'target': -99.91685662518249, 'params': {'x1': 81.7168146928204, 'x2': 6.415585307182357, 'x3': -6.7064853071795865, 'x4': 7.085485307182357, 'x5': 5.647985307182357}}
```

* 3 RS + 50

```json
Best target and parameters: 
{'target': -99.91685662518249, 'params': {'x1': 81.7168146928204, 'x2': 6.415585307182357, 'x3': -6.7064853071795865, 'x4': 7.085485307182357, 'x5': 5.647985307182357}}
```

### AGP

#### Setup1

```python
# S1
def set_sparseness(i, num_iter):
    interval = 3
    base = 3  # base. base**2, base**3, base**4...

    iter_interval = (num_iter - 3) / interval
    
    if (i >= num_iter-interval):
        return None
    else:
        return base**((i-3) // iter_interval)
```

* Parameter Space1

* 3 RS + 300

```json
Best target and parameters: 
{'target': -99.91685662518253, 'params': {'x1': 94.2831853071859, 'x2': 6.415585307179692, 'x3': 5.859885307179693, 'x4': 7.085485307179693, 'x5': -6.918385307179586}}
```

* 3 RS + 50

```json
Best target and parameters: 
{'target': -99.91685662518101, 'params': {'x1': 94.28318530712906, 'x2': 6.415585307217884, 'x3': -6.7064853071795865, 'x4': 7.085485307217884, 'x5': 5.647985307217884}}
```

* Parameter Space2

* 3 RS + 100

```json
Best target and parameters: 
{'target': 99.98807768924733, 'params': {'x1': 87.99943267141155, 'x2': 0.13139620692504048, 'x3': -0.4276622549408249, 'x4': 0.8002952527517636, 'x5': -0.6322624277448817}}
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

* 3 RS + 300

```json
Best target and parameters: 
{'target': -99.91685662517968, 'params': {'x1': 81.7168146928204, 'x2': 6.415585307217884, 'x3': -6.7064853071795865, 'x4': 7.085485307217884, 'x5': 5.647985307217884}}
```

* 3 RS + 50

```json
Best target and parameters: 
{'target': -99.9168566251827, 'params': {'x1': 81.7168146928204, 'x2': 6.415585307179692, 'x3': -6.7064853071795865, 'x4': 7.085485307179693, 'x5': 5.647985307179693}}
```

#### Setup3

```python
def set_sparseness(i, num_iter):
    interval = (num_iter - 3) / 10

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
    elif (i < 3 + 6*interval):
        return 320
    elif (i < 3 + 7*interval):
        return 640
    elif (i < 3 + 8*interval):
        return 1280
    elif (i < 3 + 9*interval):
        return 2560
    else:
        return None
```

##### Parameter Space 1

* 3 RS + 300

```json
Best target and parameters: 
{'target': -99.9168566251827, 'params': {'x1': 81.7168146928204, 'x2': 6.415585307179657, 'x3': 5.859885307179657, 'x4': 7.085485307179657, 'x5': 5.647985307179657}}
```

* 3 RS + 50

```json
Best target and parameters: 
{'target': -99.91685662518272, 'params': {'x1': 94.28318530717965, 'x2': -6.150785307179587, 'x3': 5.859885307179586, 'x4': 7.085485307179586, 'x5': 5.647985307179586}}
```

##### Parameter Space 2


### Thoughts

AGP's advantage: it can explore more in the first few iterations, which means it can have a better prior when doing exploitations afterwards.
Therefore, I think AGP will be better for a unimodal function with an extremely large parameter space. AGP is not better than continuous/discrete BO in the
case of a function with many local optima.

Try **Xin-She Yang N. 3 Function:** <http://benchmarkfcns.xyz/benchmarkfcns/xinsheyangn3fcn.html>
