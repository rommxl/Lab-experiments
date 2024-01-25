import numpy as np

def circular_convolution(x, h):
    m = len(x)
    n = len(h)

    if m!=n:
        print('The length of the sequences must be equal')
        return
    
    y = np.zeros(m)
    for i in range(m):
        for k in range(n):
            y[i] += x[k] * h[(i - k) % m]

    return y

x = list(map(float, input('Enter the input sequence x(n): ').split()))
h = list(map(float, input('Enter the impulse response h(n): ').split()))
y = circular_convolution(x, h)
print('The circular convolution of x(n) and h(n) is: ', y)
print('The length of the circular convolution is: ', len(y))
