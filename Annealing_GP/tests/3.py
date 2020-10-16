def func1(x, y):
    return func1_disc(x, y)

def func1_disc(x, y):
    if (i < 10):
        print("cnm")
    x = int(x)
    y = int(y)
    nextparam['x'] = x
    nextparam['y'] = y
    return int((x**2 + y**2)**0.5)


# print(func1(**nextparam))
# print(nextparam)

for i in range(50):
    nextparam = {'x': 3.133, 'y': 4.221}
    print("i = ", i)
    result = func1(**nextparam)
    print("result = ", result)