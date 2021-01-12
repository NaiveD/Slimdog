# Experiment (Dec. 23, Wed, Week16, Minimum Support)

## Experimental Setup

* Number of iterations: 50

  * For each iteration (each set of parameters), we perform 3 times, and take the average of the fitness value.

* Support Configuration

  * Ladder top to ground $h1 = 112\ cm$

  * Robot top to ground $h2 = 39\ cm$

  * Ladder top to robot top $d = h1 - h2 = 112 - 39 = 73\ cm$
    * Minimum support: constant $d = 73\ cm$ for all 50 iterations

![Height Config](Min-support.jpg)

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
What is the fitness? (1st run) 38.64
What is the fitness? (2nd run) 34.19
What is the fitness? (3rd run) 34.75
The average fitness is 35.860000

1th iteration: 
next point to probe is:  {'x0': 106.82538651938819, 'x1': 0.8973735648275183, 'x2': -0.5318671698003736, 'x3': 0.8657153995484621, 'x4': -0.48933793704676387}
What is the fitness? (1st run) 23.24
What is the fitness? (2nd run) 21.59
What is the fitness? (3rd run) 23.95
The average fitness is 22.926667

2th iteration: 
next point to probe is:  {'x0': 85.30595095960582, 'x1': 0.4650447232454091, 'x2': -0.9996062029947387, 'x3': -0.39330375218893593, 'x4': -0.7834221851878339}
What is the fitness? (1st run) 34.48
What is the fitness? (2nd run) 27.54
What is the fitness? (3rd run) 31.42
The average fitness is 31.146667

3th iteration: 
next point to probe is:  {'x0': 85.2010071102178, 'x1': 0.34113084714621467, 'x2': -0.5420320469557696, 'x3': -0.1703003820632667, 'x4': -0.7567483703973907}
What is the fitness? (1st run) 28.44
What is the fitness? (2nd run) 36.34
What is the fitness? (3rd run) 38.86
The average fitness is 34.546667

4th iteration: 
next point to probe is:  {'x0': 83.308652414564, 'x1': 0.8515044119531365, 'x2': 0.6975343604126887, 'x3': 0.17306789672384926, 'x4': -0.5612269735948754}
What is the fitness? (1st run) 30.72
What is the fitness? (2nd run) 28.55
What is the fitness? (3rd run) 30.03
The average fitness is 29.766667

5th iteration: 
next point to probe is:  {'x0': 85.00745853452163, 'x1': 0.21266324919413537, 'x2': -0.8247843577909169, 'x3': -0.1068218739841853, 'x4': -0.6909370611487489}
What is the fitness? (1st run) 37.99
What is the fitness? (2nd run) 34.89
What is the fitness? (3rd run) 37.76
The average fitness is 36.880000

6th iteration: 
next point to probe is:  {'x0': 74.03071157064987, 'x1': -0.725242105119827, 'x2': 0.7679230255244809, 'x3': -0.9882322265533063, 'x4': 0.4978138871647866}
What is the fitness? (1st run) 33.32
What is the fitness? (2nd run) 27.47
What is the fitness? (3rd run) 35.14
The average fitness is 31.976667

7th iteration: 
next point to probe is:  {'x0': 93.02663746099148, 'x1': -0.57189705179324, 'x2': 0.965333552839502, 'x3': -0.14728978038180074, 'x4': 0.6500978291753439}
What is the fitness? (1st run) 33.79
What is the fitness? (2nd run) 32.02
What is the fitness? (3rd run) 31.89
The average fitness is 32.566667

8th iteration: 
next point to probe is:  {'x0': 99.68042474891914, 'x1': 0.008494768818439136, 'x2': -0.4778550450712036, 'x3': 0.2446044225636672, 'x4': -0.18637985901492748}
What is the fitness? (1st run) 29.83
What is the fitness? (2nd run) 29.40
What is the fitness? (3rd run) 29.58
The average fitness is 29.603333

9th iteration: 
next point to probe is:  {'x0': 68.45056356546115, 'x1': -0.46632204777437103, 'x2': 0.7013022203015549, 'x3': -0.10200360458559943, 'x4': 0.4209869587500832}
What is the fitness? (1st run) 40.00
What is the fitness? (2nd run) 36.79
What is the fitness? (3rd run) 37.99
The average fitness is 38.260000

10th iteration: 
next point to probe is:  {'x0': 88.13493069686008, 'x1': -0.9246927037513233, 'x2': -0.7395515360262754, 'x3': 0.4113726141631062, 'x4': -0.06302832877537923}
What is the fitness? (1st run) 31.55
What is the fitness? (2nd run) 34.69
What is the fitness? (3rd run) 34.99
The average fitness is 33.743333

11th iteration: 
next point to probe is:  {'x0': 83.07588656660319, 'x1': 0.0645982191586254, 'x2': -0.9386055095027108, 'x3': -0.7327217159991928, 'x4': -0.8764417779435514}
What is the fitness? (1st run) 38.29
What is the fitness? (2nd run) 36.77
What is the fitness? (3rd run) 35.84
The average fitness is 36.966667

12th iteration: 
next point to probe is:  {'x0': 76.09560579901205, 'x1': 0.08080001122312575, 'x2': -0.09219381962894224, 'x3': 0.955303037629398, 'x4': -0.37202888577040016}
What is the fitness? (1st run) 37.19
What is the fitness? (2nd run) 38.38
What is the fitness? (3rd run) 38.77
The average fitness is 38.113333

13th iteration: 
next point to probe is:  {'x0': 70.11902377405904, 'x1': 0.500279382537751, 'x2': -0.6283315709551691, 'x3': -0.020072860235826884, 'x4': 0.433709174700843}
What is the fitness? (1st run) 38.42
What is the fitness? (2nd run) 36.03
What is the fitness? (3rd run) 37.13
The average fitness is 37.193333

14th iteration: 
next point to probe is:  {'x0': 99.94605761775449, 'x1': 0.05053679359388763, 'x2': -0.15731972650886528, 'x3': 0.1442385251120537, 'x4': -0.3528036212661656}
What is the fitness? (1st run) 25.61
What is the fitness? (2nd run) 28.09
What is the fitness? (3rd run) 27.26
The average fitness is 26.986667

15th iteration: 
next point to probe is:  {'x0': 91.8302447399155, 'x1': 0.15336876586056003, 'x2': 0.7640655635990077, 'x3': 0.674620572035054, 'x4': 0.46133293104911166}
What is the fitness? (1st run) 29.57
What is the fitness? (2nd run) 27.34
What is the fitness? (3rd run) 30.61
The average fitness is 29.173333

16th iteration: 
next point to probe is:  {'x0': 64.84935350847886, 'x1': -0.4668991173934085, 'x2': -0.04524253184372706, 'x3': 0.28476878424744734, 'x4': 0.8170287624184758}
What is the fitness? (1st run) 42.76
What is the fitness? (2nd run) 44.80
What is the fitness? (3rd run) 41.84
The average fitness is 43.133333

17th iteration: 
next point to probe is:  {'x0': 111.55031675517601, 'x1': -0.915608839865639, 'x2': -0.15702118151872302, 'x3': 0.9065208750508233, 'x4': -0.7519573164231701}
What is the fitness? (1st run) 29.07
What is the fitness? (2nd run) 30.95
What is the fitness? (3rd run) 29.76
The average fitness is 29.926667

18th iteration: 
next point to probe is:  {'x0': 68.48715731492717, 'x1': -0.4183846371714934, 'x2': 0.6703617167200571, 'x3': -0.15229801504924162, 'x4': 0.3670460299011643}
What is the fitness? (1st run) 41.75
What is the fitness? (2nd run) 40.48
What is the fitness? (3rd run) 39.07
The average fitness is 40.433333

19th iteration: 
next point to probe is:  {'x0': 69.81186896011442, 'x1': 0.19604640705337317, 'x2': -0.9053410224003442, 'x3': -0.88665639082144, 'x4': -0.24982297862240643}
What is the fitness? (1st run) 36.29
What is the fitness? (2nd run) 38.71
What is the fitness? (3rd run) 38.90
The average fitness is 37.966667

20th iteration: 
next point to probe is:  {'x0': 76.01141073228503, 'x1': 0.17332135615696576, 'x2': -0.29346039150622305, 'x3': 0.832385478618417, 'x4': -0.20543346055785117}
What is the fitness? (1st run) 40.18
What is the fitness? (2nd run) 37.29
What is the fitness? (3rd run) 39.12
The average fitness is 38.863333

21th iteration: 
next point to probe is:  {'x0': 62.81899407290316, 'x1': -0.513156605998544, 'x2': -0.0727497914906956, 'x3': -0.22608827210224747, 'x4': 0.9895745577982968}
What is the fitness? (1st run) 40.75
What is the fitness? (2nd run) 43.66
What is the fitness? (3rd run) 42.60
The average fitness is 42.336667

22th iteration: 
next point to probe is:  {'x0': 76.01845979239566, 'x1': 0.07852905313785485, 'x2': -0.2158545215533625, 'x3': 0.8744957874813286, 'x4': -0.15669500248831092}
What is the fitness? (1st run) 41.44
What is the fitness? (2nd run) 42.06
What is the fitness? (3rd run) 39.51
The average fitness is 41.003333

23th iteration: 
next point to probe is:  {'x0': 64.81829183101566, 'x1': -0.32407559528419205, 'x2': 0.2451782618371432, 'x3': 0.16936956745792964, 'x4': 0.8815271460450524}
What is the fitness? (1st run) 47.01
What is the fitness? (2nd run) 39.16
What is the fitness? (3rd run) 43.67
The average fitness is 43.280000

24th iteration: 
next point to probe is:  {'x0': 70.35131063570876, 'x1': -0.7835612516470698, 'x2': 0.5025154303067871, 'x3': 0.40223585354414326, 'x4': 0.955517262696225}
What is the fitness? (1st run) 40.86
What is the fitness? (2nd run) 38.99
What is the fitness? (3rd run) 37.13
The average fitness is 38.993333

25th iteration: 
next point to probe is:  {'x0': 64.83335996085512, 'x1': -0.3933703004736237, 'x2': 0.10427281393585368, 'x3': 0.22535801552561485, 'x4': 0.8502342302170663}
What is the fitness? (1st run) 44.21
What is the fitness? (2nd run) 42.48
What is the fitness? (3rd run) 42.09
The average fitness is 42.926667

26th iteration: 
next point to probe is:  {'x0': 105.91053177812881, 'x1': -0.35075103903099336, 'x2': 0.35173730154988947, 'x3': -0.25870914028840053, 'x4': 0.6672720003489232}
What is the fitness? (1st run) 25.59
What is the fitness? (2nd run) 24.86
What is the fitness? (3rd run) 25.43
The average fitness is 25.293333

27th iteration: 
next point to probe is:  {'x0': 65.05455527019825, 'x1': -0.14369893185936733, 'x2': -0.013153783086617077, 'x3': 0.22217695324799402, 'x4': 0.9740536409308613}
What is the fitness? (1st run) 44.54
What is the fitness? (2nd run) 40.59
What is the fitness? (3rd run) 43.39
The average fitness is 42.840000

28th iteration: 
next point to probe is:  {'x0': 65.17001511954422, 'x1': -0.23511872439485182, 'x2': -0.07472500640380408, 'x3': 0.14515743229315725, 'x4': 0.9278210622814782}
What is the fitness? (1st run) 42.12
What is the fitness? (2nd run) 44.83
What is the fitness? (3rd run) 42.33
The average fitness is 43.093333

29th iteration: 
next point to probe is:  {'x0': 107.20559802777174, 'x1': -0.8164244458125829, 'x2': 0.46582919183059013, 'x3': -0.276365713363536, 'x4': 0.31408236331094974}
What is the fitness? (1st run) 21.08
What is the fitness? (2nd run) 28.75
What is the fitness? (3rd run) 24.90
The average fitness is 24.910000

30th iteration: 
next point to probe is:  {'x0': 62.89948666951501, 'x1': -0.5079803293378782, 'x2': -0.06401874425899491, 'x3': -0.20972497812303198, 'x4': 0.9831228831162625}
What is the fitness? (1st run) 47.78
What is the fitness? (2nd run) 44.14
What is the fitness? (3rd run) 46.06
The average fitness is 45.993333

31th iteration: 
next point to probe is:  {'x0': 119.00707347361362, 'x1': -0.8240184151469649, 'x2': -0.8888308010576724, 'x3': -0.2769176590742326, 'x4': 0.9152861818356197}
What is the fitness? (1st run) 28.74
What is the fitness? (2nd run) 30.18
What is the fitness? (3rd run) 32.09
The average fitness is 30.336667

32th iteration: 
next point to probe is:  {'x0': 67.06929850321018, 'x1': 0.7200991220565067, 'x2': -0.5320557180789895, 'x3': 0.7890596459659902, 'x4': 0.38890414531519935}
What is the fitness? (1st run) 41.59
What is the fitness? (2nd run) 41.86
What is the fitness? (3rd run) 41.37
The average fitness is 41.606667

33th iteration: 
next point to probe is:  {'x0': 65.01193098982412, 'x1': -0.28868631661895583, 'x2': -0.0024598195498131132, 'x3': 0.19747747496358636, 'x4': 0.9020633205106997}
What is the fitness? (1st run) 46.68
What is the fitness? (2nd run) 42.59
What is the fitness? (3rd run) 44.96
The average fitness is 44.743333

34th iteration: 
next point to probe is:  {'x0': 64.96063912317736, 'x1': -0.33673593085204767, 'x2': -0.03080625466438135, 'x3': 0.23736601389629633, 'x4': 0.8797041899465836}
What is the fitness? (1st run) 46.13
What is the fitness? (2nd run) 44.16
What is the fitness? (3rd run) 42.23
The average fitness is 44.173333

35th iteration: 
next point to probe is:  {'x0': 65.00279961258391, 'x1': -0.2679567129304945, 'x2': 0.24555968194183064, 'x3': 0.227197184522828, 'x4': 0.9013712463865209}
What is the fitness? (1st run) 41.07
What is the fitness? (2nd run) 43.35
What is the fitness? (3rd run) 43.61
The average fitness is 42.676667

36th iteration: 
next point to probe is:  {'x0': 64.91137248555786, 'x1': -0.396908902978494, 'x2': -0.023155000142367932, 'x3': 0.08452502996263345, 'x4': 0.7022375377293095}
What is the fitness? (1st run) 46.26
What is the fitness? (2nd run) 45.05
What is the fitness? (3rd run) 45.81
The average fitness is 45.706667

37th iteration: 
next point to probe is:  {'x0': 106.74738492237212, 'x1': 0.05866423066271631, 'x2': 0.6376722770038428, 'x3': 0.785419864593399, 'x4': -0.3478523854659257}
What is the fitness? (1st run) 29.15
What is the fitness? (2nd run) 27.78
What is the fitness? (3rd run) 25.14
The average fitness is 27.356667

38th iteration: 
next point to probe is:  {'x0': 65.0008515695103, 'x1': -0.4945905281377747, 'x2': 0.24148377382928632, 'x3': 0.1944733408271333, 'x4': 0.7175023260784943}
What is the fitness? (1st run) 43.80
What is the fitness? (2nd run) 46.10
What is the fitness? (3rd run) 41.93
The average fitness is 43.943333

39th iteration: 
next point to probe is:  {'x0': 88.0622083192263, 'x1': 0.11140553475704373, 'x2': 0.38880362682748015, 'x3': -0.7135549175083746, 'x4': -0.029685690010696097}
What is the fitness? (1st run) 32.72
What is the fitness? (2nd run) 34.03
What is the fitness? (3rd run) 24.02
The average fitness is 30.256667

40th iteration: 
next point to probe is:  {'x0': 83.1753830441032, 'x1': -0.026086547325406384, 'x2': -0.9458450291663703, 'x3': -0.6600479837811051, 'x4': -0.9342144765555349}
What is the fitness? (1st run) 39.36
What is the fitness? (2nd run) 38.89
What is the fitness? (3rd run) 39.24
The average fitness is 39.163333

41th iteration: 
next point to probe is:  {'x0': 117.32220727256657, 'x1': 0.5362509042725299, 'x2': 0.020048450542422103, 'x3': 0.625447933982098, 'x4': 0.5373510131438792}
What is the fitness? (1st run) 34.05
What is the fitness? (2nd run) 34.62
What is the fitness? (3rd run) 33.31
The average fitness is 33.993333

42th iteration: 
next point to probe is:  {'x0': 109.72350856539927, 'x1': -0.26077033914687386, 'x2': 0.6050329373958958, 'x3': -0.10395125931671356, 'x4': -0.20753169466280164}
What is the fitness? (1st run) 27.16
What is the fitness? (2nd run) 30.03
What is the fitness? (3rd run) 31.62
The average fitness is 29.603333

43th iteration: 
next point to probe is:  {'x0': 64.81403083780694, 'x1': -0.26717253987733347, 'x2': 0.18982950561914103, 'x3': 0.2852050019143437, 'x4': 0.7102792535969307}
What is the fitness? (1st run) 39.74
What is the fitness? (2nd run) 43.01
What is the fitness? (3rd run) 37.08
The average fitness is 39.943333

44th iteration: 
next point to probe is:  {'x0': 62.58317984142769, 'x1': -0.8882398459838348, 'x2': 0.4036498429562305, 'x3': -0.04944381263450737, 'x4': 0.20933348999914014}
What is the fitness? (1st run) 38.49
What is the fitness? (2nd run) 36.73
What is the fitness? (3rd run) 38.56
The average fitness is 37.926667

45th iteration: 
next point to probe is:  {'x0': 65.04172342513198, 'x1': -0.34719126842122017, 'x2': 0.3897013598995396, 'x3': 0.14321730537592137, 'x4': 0.5889984568394395}
What is the fitness? (1st run) 42.54
What is the fitness? (2nd run) 38.81
What is the fitness? (3rd run) 40.38
The average fitness is 40.576667

46th iteration: 
next point to probe is:  {'x0': 65.05937236274708, 'x1': -0.5849125881120756, 'x2': 0.3661951007330375, 'x3': -0.15069801602163868, 'x4': 0.7896546043087167}
What is the fitness? (1st run) 35.20
What is the fitness? (2nd run) 39.10 
What is the fitness? (3rd run) 39.70
The average fitness is 38.000000

47th iteration: 
next point to probe is:  {'x0': 65.1749851195487, 'x1': -0.6240321330232019, 'x2': 0.12161617315110673, 'x3': 0.14787654975616338, 'x4': 0.7410267065302671}
What is the fitness? (1st run) 38.70
What is the fitness? (2nd run) 41.51
What is the fitness? (3rd run) 41.48
The average fitness is 40.563333

48th iteration: 
next point to probe is:  {'x0': 65.00526873654462, 'x1': -0.352610028401271, 'x2': -0.11862816231658169, 'x3': 0.08810782827403574, 'x4': 0.3692099921910639}
What is the fitness? (1st run) 38.87
What is the fitness? (2nd run) 41.37
What is the fitness? (3rd run) 41.70
The average fitness is 40.646667

49th iteration: 
next point to probe is:  {'x0': 62.986133251920585, 'x1': -0.5024400713675783, 'x2': -0.054575598121126924, 'x3': -0.19209075403728396, 'x4': 0.9761067899528005}
What is the fitness? (1st run) 39.39
What is the fitness? (2nd run) 34.21
What is the fitness? (3rd run) 37.31
The average fitness is 36.970000


Best target and parameters: 
{'target': 45.99333333333334, 'params': {'x0': 62.89948666951501, 'x1': -0.5079803293378782, 'x2': -0.06401874425899491, 'x3': -0.20972497812303198, 'x4': 0.9831228831162625}}

```
