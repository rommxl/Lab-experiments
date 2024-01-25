from math import exp as e
import numpy as np

def identity(x):
    return x

def binary_step(x):
    if(x>=0):
        return 1
    return 0

def bipolar_step(x):
    if(x>=0):
        return 1
    return -1

def binary_sigmoid(x):
    val = 1/(1+(e(x*-1)))
    return val

def bipolar_sigmoid(x):
    val = (1-e(x * -1))/(1+e(x * -1))
    return val

def ramp(x):
    if(x >= 1):
        return 1
    elif (0 <= x <= 1):
        return x
    return 0

def relu(x):
    return max(0,x)

def main():
    n = int(input("Enter number of input: "))
    x = []
    w = []
    yin = 0
    for i  in range(n):
        xn = float(input("Enter value of x{}: ".format(i+1)))
        wn = float(input("Enter weight of x{}: ".format(i+1)))
        x.append(xn)
        w.append(wn)
    x = np.array(x)
    w = np.array(w)

    for i in range(len(x)):
        yin = yin + (x[i]*w[i])
    
    print("Identity: {}".format(identity(yin)))
    print("Binary step: {}".format(binary_step(yin)))
    print("Bipolar step: {}".format(bipolar_step(yin)))
    print("Binary sigmoid: {}".format(binary_sigmoid(yin)))
    print("Bipolar sigmoid: {}".format(bipolar_sigmoid(yin)))
    print("Ramp: {}".format(ramp(yin)))
    print("ReLu: {}".format(relu(yin)))

if __name__ == '__main__':
    main()