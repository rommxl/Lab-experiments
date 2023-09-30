import numpy as np
def linear_convolution(x, h):
    m = len(x)
    n = len(h)
    l = m + n - 1
    y = np.zeros(l)
    for i in range(l):
        y[i] = 0
        for k in range(m):
            if i - k >= 0 and i - k < n:
                y[i] += x[k] * h[i - k]

    return y

x = list(map(float, input('Enter the input sequence x(n): ').split()))
h = list(map(float, input('Enter the impulse response h(n): ').split()))
y = linear_convolution(x, h)
print('The linear convolution of x(n) and h(n) is: ', y)
print('The length of the linear convolution is: ', len(y))
