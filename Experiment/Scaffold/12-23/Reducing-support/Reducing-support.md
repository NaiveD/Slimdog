# Experiment (Dec. 23, Wed, Week16, Reducing Support)

## Experimental Setup

* Number of iterations: 50

  * For each iteration (each set of parameters), we perform 3 times, and take the average of the fitness value.

* Support Configuration

  * Ladder top to ground $h1 = 112\ cm$

  * Robot top to ground $h2 = (47.5\rightarrow 45\rightarrow 42 \rightarrow 39)\ cm$

  * Ladder top to robot top $d = h1 - h2 = 112 - (47.5 \rightarrow 45\rightarrow 42\rightarrow 39) = (64\rightarrow67\rightarrow 70\rightarrow 73)\ cm$
    * Reducing support, the robot relies on itself more through iterations:
      * For iteration 0-9: $d = 64.5\ cm$, $h2 = 47.5\ cm$
      * For iteration 10-19: $d = 67\ cm$, $h2 = 45\ cm$
      * For iteration 20-29: $d = 70\ cm$, $h2 = 42\ cm$
      * For iteration 30-49: $d = 73\ cm$, $h2 = 39\ cm$ (minimum support)

## Optimization algorithm

Basic continuous Bayesian Optimization

```shell
$ cd BO/Python_code
$ python3 BO.py
```

## Results

```shell
0th iteration: 
next point to probe is:  {'x0': 85.02132028215445, 'x1': 0.4406489868843162, 'x2': -0.9997712503653102, 'x3': -0.39533485473632046, 'x4': -0.7064882183657739}
What is the fitness? (1st run) 1.02
What is the fitness? (2nd run) 0.94
What is the fitness? (3rd run) 5.64
The average fitness is 2.533333

1th iteration: 
next point to probe is:  {'x0': 106.82538651938819, 'x1': 0.8973735648275183, 'x2': -0.5318671698003736, 'x3': 0.8657153995484621, 'x4': -0.48933793704676387}
What is the fitness? (1st run) 2.53
What is the fitness? (2nd run) 6.41
What is the fitness? (3rd run) 4.30
The average fitness is 4.413333

2th iteration: 
next point to probe is:  {'x0': 108.1220553622872, 'x1': 0.7744172742959027, 'x2': -0.6830173351238996, 'x3': 0.8136973675518334, 'x4': -0.2497150969024086}
What is the fitness? (1st run) 5.23
What is the fitness? (2nd run) 6.12
What is the fitness? (3rd run) 9.35
The average fitness is 6.900000

3th iteration: 
next point to probe is:  {'x0': 104.17072819664224, 'x1': 0.38092067299502586, 'x2': -0.808271098028885, 'x3': 0.3492493805771042, 'x4': 0.3037531309479118}
What is the fitness? (1st run) 9.39
What is the fitness? (2nd run) 8.37
What is the fitness? (3rd run) 11.67
The average fitness is 9.810000

4th iteration: 
next point to probe is:  {'x0': 104.16024745192172, 'x1': 0.590761061665946, 'x2': -0.6968259457741413, 'x3': 0.03606378843980651, 'x4': 0.29279630083411634}
What is the fitness? (1st run) 9.59
What is the fitness? (2nd run) 9.91
What is the fitness? (3rd run) 8.62
The average fitness is 9.373333

5th iteration: 
next point to probe is:  {'x0': 103.77282387321374, 'x1': 0.3111210749826888, 'x2': -0.8458254038123396, 'x3': 0.2588818240623115, 'x4': 0.4233795072576008}
What is the fitness? (1st run) 6.51
What is the fitness? (2nd run) 7.28
What is the fitness? (3rd run) 9.41
The average fitness is 7.733333

6th iteration: 
next point to probe is:  {'x0': 74.03071157064987, 'x1': -0.725242105119827, 'x2': 0.7679230255244809, 'x3': -0.9882322265533063, 'x4': 0.4978138871647866}
What is the fitness? (1st run) 6.81
What is the fitness? (2nd run) 9.43
What is the fitness? (3rd run) 7.75
The average fitness is 7.996667

7th iteration: 
next point to probe is:  {'x0': 93.02663746099148, 'x1': -0.57189705179324, 'x2': 0.965333552839502, 'x3': -0.14728978038180074, 'x4': 0.6500978291753439}
What is the fitness? (1st run) 9.57
What is the fitness? (2nd run) 9.38
What is the fitness? (3rd run) 11.37
The average fitness is 10.106667

8th iteration: 
next point to probe is:  {'x0': 99.68042474891914, 'x1': 0.008494768818439136, 'x2': -0.4778550450712036, 'x3': 0.2446044225636672, 'x4': -0.18637985901492748}
What is the fitness? (1st run) 7.24
What is the fitness? (2nd run) 7.90
What is the fitness? (3rd run) 8.43
The average fitness is 7.856667

9th iteration: 
next point to probe is:  {'x0': 68.45056356546115, 'x1': -0.46632204777437103, 'x2': 0.7013022203015549, 'x3': -0.10200360458559943, 'x4': 0.4209869587500832}
What is the fitness? (1st run) 9.16
What is the fitness? (2nd run) 7.90
What is the fitness? (3rd run) 9.99
The average fitness is 9.016667

10th iteration: 
next point to probe is:  {'x0': 88.13493069686008, 'x1': -0.9246927037513233, 'x2': -0.7395515360262754, 'x3': 0.4113726141631062, 'x4': -0.06302832877537923}
What is the fitness? (1st run) 9.55
What is the fitness? (2nd run) 13.72
What is the fitness? (3rd run) 12.20
The average fitness is 11.823333

11th iteration: 
next point to probe is:  {'x0': 83.07588656660319, 'x1': 0.0645982191586254, 'x2': -0.9386055095027108, 'x3': -0.7327217159991928, 'x4': -0.8764417779435514}
What is the fitness? (1st run) 10.22
What is the fitness? (2nd run) 10.59
What is the fitness? (3rd run) 10.53
The average fitness is 10.446667

12th iteration: 
next point to probe is:  {'x0': 76.09560579901205, 'x1': 0.08080001122312575, 'x2': -0.09219381962894224, 'x3': 0.955303037629398, 'x4': -0.37202888577040016}
What is the fitness? (1st run) 11.91
What is the fitness? (2nd run) 9.25
What is the fitness? (3rd run) 13.17
The average fitness is 11.443333

13th iteration: 
next point to probe is:  {'x0': 70.11902377405904, 'x1': 0.500279382537751, 'x2': -0.6283315709551691, 'x3': -0.020072860235826884, 'x4': 0.433709174700843}
What is the fitness? (1st run) 14.71
What is the fitness? (2nd run) 13.63
What is the fitness? (3rd run) 14.70
The average fitness is 14.346667

14th iteration: 
next point to probe is:  {'x0': 99.94605761775449, 'x1': 0.05053679359388763, 'x2': -0.15731972650886528, 'x3': 0.1442385251120537, 'x4': -0.3528036212661656}
What is the fitness? (1st run) 5.71
What is the fitness? (2nd run) 10.70
What is the fitness? (3rd run) 6.49
The average fitness is 7.633333

15th iteration: 
next point to probe is:  {'x0': 91.8302447399155, 'x1': 0.15336876586056003, 'x2': 0.7640655635990077, 'x3': 0.674620572035054, 'x4': 0.46133293104911166}
What is the fitness? (1st run) 8.13
What is the fitness? (2nd run) 8.88
What is the fitness? (3rd run) 14.04
The average fitness is 10.350000

16th iteration: 
next point to probe is:  {'x0': 70.17488053954823, 'x1': 0.4731997051353415, 'x2': -0.6120092106600817, 'x3': -0.03792599324589992, 'x4': 0.5087095639617244}
What is the fitness? (1st run) 14.66
What is the fitness? (2nd run) 10.08
What is the fitness? (3rd run) 9.15
The average fitness is 11.296667

17th iteration: 
next point to probe is:  {'x0': 111.55031675517601, 'x1': -0.915608839865639, 'x2': -0.15702118151872302, 'x3': 0.9065208750508233, 'x4': -0.7519573164231701}
What is the fitness? (1st run) 7.70
What is the fitness? (2nd run) 8.56
What is the fitness? (3rd run) 9.10
The average fitness is 8.453333

18th iteration: 
next point to probe is:  {'x0': 68.86416397024067, 'x1': 0.18988084963738405, 'x2': 0.34298604230885976, 'x3': -0.8950761732976524, 'x4': -0.42286396166520324}
What is the fitness? (1st run) 9.67
What is the fitness? (2nd run) 9.50
What is the fitness? (3rd run) 11.78
The average fitness is 10.316667

19th iteration: 
next point to probe is:  {'x0': 69.81186896011442, 'x1': 0.19604640705337317, 'x2': -0.9053410224003442, 'x3': -0.88665639082144, 'x4': -0.24982297862240643}
What is the fitness? (1st run) 12.77
What is the fitness? (2nd run) 11.41
What is the fitness? (3rd run) 11.77
The average fitness is 11.983333

20th iteration: 
next point to probe is:  {'x0': 91.85821709806903, 'x1': 0.24124018730451513, 'x2': 0.6619198895966556, 'x3': 0.6747143569818126, 'x4': 0.2626042834554434}
What is the fitness? (1st run) 17.57
What is the fitness? (2nd run) 19.45
What is the fitness? (3rd run) 20.50
The average fitness is 19.173333

21th iteration: 
next point to probe is:  {'x0': 62.81899407290316, 'x1': -0.513156605998544, 'x2': -0.0727497914906956, 'x3': -0.22608827210224747, 'x4': 0.9895745577982968}
What is the fitness? (1st run) 21.84
What is the fitness? (2nd run) 23.95
What is the fitness? (3rd run) 20.71
The average fitness is 22.166667

22th iteration: 
next point to probe is:  {'x0': 103.42202441182269, 'x1': 0.3331621051241094, 'x2': 0.1636461864729899, 'x3': -0.937556526875374, 'x4': 0.6080637057110279}
What is the fitness? (1st run) 16.10
What is the fitness? (2nd run) 18.77
What is the fitness? (3rd run) 18.30
The average fitness is 17.723333

23th iteration: 
next point to probe is:  {'x0': 70.03805609176338, 'x1': 0.2999173377241007, 'x2': -0.612497819970955, 'x3': 0.1701804661929518, 'x4': 0.47285916012563334}
What is the fitness? (1st run) 25.30
What is the fitness? (2nd run) 17.53
What is the fitness? (3rd run) 16.80
The average fitness is 19.876667

24th iteration: 
next point to probe is:  {'x0': 70.35131063570876, 'x1': -0.7835612516470698, 'x2': 0.5025154303067871, 'x3': 0.40223585354414326, 'x4': 0.955517262696225}
What is the fitness? (1st run) 22.08
What is the fitness? (2nd run) 19.14
What is the fitness? (3rd run) 19.34
The average fitness is 20.186667

25th iteration: 
next point to probe is:  {'x0': 118.79981045084175, 'x1': 0.45832253784656474, 'x2': -0.09937634829186126, 'x3': 0.5414690727669105, 'x4': -0.49691241260652963}
What is the fitness? (1st run) 13.15
What is the fitness? (2nd run) 14.80
What is the fitness? (3rd run) 14.66
The average fitness is 14.203333

26th iteration: 
next point to probe is:  {'x0': 105.91053177812881, 'x1': -0.35075103903099336, 'x2': 0.35173730154988947, 'x3': -0.25870914028840053, 'x4': 0.6672720003489232}
What is the fitness? (1st run) 15.14
What is the fitness? (2nd run) 20.70
What is the fitness? (3rd run) 17.00
The average fitness is 17.613333

27th iteration: 
next point to probe is:  {'x0': 92.96200627066958, 'x1': -0.8187867781742606, 'x2': 0.38443566165047294, 'x3': -0.6914197099299473, 'x4': -0.7534664123416328}
What is the fitness? (1st run) 16.89
What is the fitness? (2nd run) 21.44
What is the fitness? (3rd run) 20.11
The average fitness is 19.480000

28th iteration: 
next point to probe is:  {'x0': 111.0622416552942, 'x1': -0.046787588853941964, 'x2': 0.5393780174815419, 'x3': -0.5765265944151181, 'x4': -0.5269534196301493}
What is the fitness? (1st run) 13.75
What is the fitness? (2nd run) 17.41
What is the fitness? (3rd run) 14.62
The average fitness is 15.260000

29th iteration: 
next point to probe is:  {'x0': 107.20559802777174, 'x1': -0.8164244458125829, 'x2': 0.46582919183059013, 'x3': -0.276365713363536, 'x4': 0.31408236331094974}
What is the fitness? (1st run) 15.98
What is the fitness? (2nd run) 14.76
What is the fitness? (3rd run) 15.35
The average fitness is 15.363333

30th iteration: 
next point to probe is:  {'x0': 115.37190420310309, 'x1': 0.875283424068217, 'x2': -0.9628512430988487, 'x3': -0.8437275627984526, 'x4': 0.5519317647794066}
What is the fitness? (1st run) 17.89
What is the fitness? (2nd run) 19.06
What is the fitness? (3rd run) 19.70
The average fitness is 18.883333

31th iteration: 
next point to probe is:  {'x0': 119.00707347361362, 'x1': -0.8240184151469649, 'x2': -0.8888308010576724, 'x3': -0.2769176590742326, 'x4': 0.9152861818356197}
What is the fitness? (1st run) 16.09
What is the fitness? (2nd run) 21.15
What is the fitness? (3rd run) 23.45
The average fitness is 20.230000

32th iteration: 
next point to probe is:  {'x0': 67.06929850321018, 'x1': 0.7200991220565067, 'x2': -0.5320557180789895, 'x3': 0.7890596459659902, 'x4': 0.38890414531519935}
What is the fitness? (1st run) 30.61
What is the fitness? (2nd run) 33.32
What is the fitness? (3rd run) 31.35
The average fitness is 31.760000

33th iteration: 
next point to probe is:  {'x0': 117.91612587017914, 'x1': -0.9424528026450176, 'x2': 0.14746053087472566, 'x3': 0.1570524940926048, 'x4': 0.19527967356042386}
What is the fitness? (1st run) 22.34
What is the fitness? (2nd run) 23.74
What is the fitness? (3rd run) 21.10
The average fitness is 22.393333

34th iteration: 
next point to probe is:  {'x0': 110.27826965352921, 'x1': 0.44071174763579224, 'x2': -0.9772861215855091, 'x3': -0.7481307811930815, 'x4': 0.2809440337975131}
What is the fitness? (1st run) 25.06
What is the fitness? (2nd run) 23.17
What is the fitness? (3rd run) 26.98
The average fitness is 25.070000

35th iteration: 
next point to probe is:  {'x0': 62.13836041971747, 'x1': 0.8878408631599841, 'x2': 0.4736241042014937, 'x3': -0.6743356223527865, 'x4': -0.8064751225701972}
What is the fitness? (1st run) 26.78
What is the fitness? (2nd run) 22.70
What is the fitness? (3rd run) 26.87
The average fitness is 25.450000

36th iteration: 
next point to probe is:  {'x0': 90.99713301853085, 'x1': 0.1526343519647928, 'x2': 0.9688429304719679, 'x3': 0.65314950902827, 'x4': -0.2507378587174771}
What is the fitness? (1st run) 21.94
What is the fitness? (2nd run) 19.94
What is the fitness? (3rd run) 21.89
The average fitness is 21.256667

37th iteration: 
next point to probe is:  {'x0': 106.74738492237212, 'x1': 0.05866423066271631, 'x2': 0.6376722770038428, 'x3': 0.785419864593399, 'x4': -0.3478523854659257}
What is the fitness? (1st run) 18.21
What is the fitness? (2nd run) 21.39
What is the fitness? (3rd run) 16.45
The average fitness is 18.683333

38th iteration: 
next point to probe is:  {'x0': 105.4527121920853, 'x1': -0.10087791381799494, 'x2': 0.6902425381865303, 'x3': 0.13084837746630473, 'x4': 0.359846738615049}
What is the fitness? (1st run) 28.13
What is the fitness? (2nd run) 22.69
What is the fitness? (3rd run) 23.92
The average fitness is 24.913333

39th iteration: 
next point to probe is:  {'x0': 88.0622083192263, 'x1': 0.11140553475704373, 'x2': 0.38880362682748015, 'x3': -0.7135549175083746, 'x4': -0.029685690010696097}
What is the fitness? (1st run) 25.38
What is the fitness? (2nd run) 22.04
What is the fitness? (3rd run) 19.34
The average fitness is 22.253333

40th iteration: 
next point to probe is:  {'x0': 69.74180648654269, 'x1': -0.8996832099400265, 'x2': 0.27558925943031265, 'x3': 0.00691807984602133, 'x4': 0.6195289481705322}
What is the fitness? (1st run) 34.48
What is the fitness? (2nd run) 33.10
What is the fitness? (3rd run) 31.40
The average fitness is 32.993333

41th iteration: 
next point to probe is:  {'x0': 117.32220727256657, 'x1': 0.5362509042725299, 'x2': 0.020048450542422103, 'x3': 0.625447933982098, 'x4': 0.5373510131438792}
What is the fitness? (1st run) 27.85
What is the fitness? (2nd run) 23.27
What is the fitness? (3rd run) 21.21
The average fitness is 24.110000

42th iteration: 
next point to probe is:  {'x0': 109.72350856539927, 'x1': -0.26077033914687386, 'x2': 0.6050329373958958, 'x3': -0.10395125931671356, 'x4': -0.20753169466280164}
What is the fitness? (1st run) 26.88
What is the fitness? (2nd run) 26.30
What is the fitness? (3rd run) 25.79
The average fitness is 26.323333

43th iteration: 
next point to probe is:  {'x0': 109.8331530982003, 'x1': -0.05619842129637864, 'x2': 0.5079937384425768, 'x3': -0.16791802324815408, 'x4': -0.30314941577495635}
What is the fitness? (1st run) 27.98
What is the fitness? (2nd run) 26.31
What is the fitness? (3rd run) 26.14
The average fitness is 26.810000

44th iteration: 
next point to probe is:  {'x0': 62.58317984142769, 'x1': -0.8882398459838348, 'x2': 0.4036498429562305, 'x3': -0.04944381263450737, 'x4': 0.20933348999914014}
What is the fitness? (1st run) 36.27
What is the fitness? (2nd run) 37.80
What is the fitness? (3rd run) 33.48
The average fitness is 35.850000

45th iteration: 
next point to probe is:  {'x0': 88.41283831069791, 'x1': 0.2563250789369165, 'x2': 0.17635707172751447, 'x3': -0.5956872113855285, 'x4': -0.8025387168007658}
What is the fitness? (1st run) 31.08
What is the fitness? (2nd run) 31.42
What is the fitness? (3rd run) 32.39
The average fitness is 31.630000

46th iteration: 
next point to probe is:  {'x0': 69.93857257672197, 'x1': -0.7934991297110072, 'x2': 0.3231617966472158, 'x3': -0.10621736215557931, 'x4': 0.4321245773368185}
What is the fitness? (1st run) 33.11
What is the fitness? (2nd run) 32.19
What is the fitness? (3rd run) 32.72
The average fitness is 32.673333

47th iteration: 
next point to probe is:  {'x0': 69.83930142293194, 'x1': -0.8487820746680905, 'x2': 0.2991394217327279, 'x3': -0.04412767266466124, 'x4': 0.5328399927677787}
What is the fitness? (1st run) 33.86
What is the fitness? (2nd run) 32.17
What is the fitness? (3rd run) 33.07
The average fitness is 33.033333

48th iteration: 
next point to probe is:  {'x0': 88.39343290626174, 'x1': 0.24838262082012977, 'x2': 0.18818542012627737, 'x3': -0.6022953021359698, 'x4': -0.7597892579428869}
What is the fitness? (1st run) 35.66
What is the fitness? (2nd run) 34.95
What is the fitness? (3rd run) 33.50
The average fitness is 34.703333

49th iteration: 
next point to probe is:  {'x0': 88.3657778138557, 'x1': 0.23706142321770032, 'x2': 0.20504048650263007, 'x3': -0.6117103652137053, 'x4': -0.698864695297828}
What is the fitness? (1st run) 32.64
What is the fitness? (2nd run) 30.08
What is the fitness? (3rd run) 29.00
The average fitness is 30.573333


Best target and parameters: 
{'target': 35.849999999999994, 'params': {'x0': 62.58317984142769, 'x1': -0.8882398459838348, 'x2': 0.4036498429562305, 'x3': -0.04944381263450737, 'x4': 0.20933348999914014}}

```
