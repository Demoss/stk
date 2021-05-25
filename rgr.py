import keyboard
import time
from scipy.stats import t, f
import os.path
import pickle


def excludeMistakes(y):
    y3 = y.copy()
    for i in range(len(y)):
        y2 = y.copy()
        y2.pop(i)
        Mi = sum(y2)/len(y2)
        Si2 = 0.0
        for k in y2:
            Si2 += (k - Mi)**2
        Si2 /= len(y2) - 1
        Si = Si2**0.5
        tp = abs((y[i] - Mi)/Si)
        tt = t.ppf((1 + 0.95)/2, len(y2)-1)
        if tp > tt:
            y3.remove(y[i])
    y = y3.copy()
    return y


def calcMS2(y):
    M = sum(y)/len(y)
    S2 = 0.0
    for j in y:
        S2 += (j - M)**2
    S2 /= len(y) - 1
    tt = t.ppf((1 + 0.95)/2, len(y)-1)
    dt = S2*tt
    print("dt: {}".format(dt))
    return M, S2


def isUniform(S2et, S2exp, n):
    Smax = max(S2et, S2exp)
    Smin = min(S2et, S2exp)
    Fp = Smax/Smin
    Ft = f.isf(0.05, n-1, n-1)
    if Fp > Ft:
        return False
    else:
        return True


def equalDistribCenters(Met, S2et, Mexp , S2exp, n, p):
    S = ((S2et**2 + S2exp**2)*(n-1)/(2*n - 1))**0.5
    tp = abs(Met - Mexp)/(S*((2/n)**0.5))
    tt = t.ppf((2 - p)/2, n-1)
    if tp > tt:
        return False
    else:
        return True


print("1 - LogIn")
print("2 - Learning")
answ = input("Enter mode: ")
if answ == "1":
    y = []
    p = float(input("Enter p: "))
    print("Enter your passphrase")
    while True:
            a = keyboard.read_event()
            if a.name == "enter":
                a = keyboard.read_event()
                break
            elif a.event_type == "down":
                ti = time.time()
                b = keyboard.read_event()
                while not b.event_type == "up":
                    b = keyboard.read_event()
                y.append(time.time() - ti)
    with open("params", 'rb') as file:
        params = pickle.load(file)
    y = excludeMistakes(y)
    M, S2 = calcMS2(y)
    positive = 0
    print("M: {}".format(M))
    print("S2: {}".format(S2))
    for [Met, S2et] in params:
        print("M etalon: {}".format(Met))
        print("S2 etalon: {}".format(S2et))
        if isUniform(S2et, S2, len(y)):
            if equalDistribCenters(Met, S2et, M, S2, len(y), p):
                positive += 1
    Probability = positive/len(params)
    if Probability > 0.6:
        print("Success! You are logged in!")
        params.append([M, S2])
        with open("params", 'wb') as file:
            pickle.dump(params, file)
    else:
        print("Unauthorized user!!!")
elif answ == "2":
    y = []
    print("Enter your passphrase")
    while True:
            a = keyboard.read_event()
            if a.name == "enter":
                a = keyboard.read_event()
                break
            elif a.event_type == "down":
                ti = time.time()
                b = keyboard.read_event()
                while not b.event_type == "up":
                    b = keyboard.read_event()
                y.append(time.time() - ti)
    y = excludeMistakes(y)
    M, S2 = calcMS2(y)
    if os.path.exists("params"):
        with open("params", 'rb') as file:
            params = pickle.load(file)
        params.append([M, S2])
        with open("params", 'wb') as file:
            pickle.dump(params, file)
    else:
        with open("params", 'wb') as file:
            params = [[M, S2]]
            pickle.dump(params, file)
    print("M: {}".format(M))
    print("S2: {}".format(S2))
else:
    print("Please choose one of modes listed above")

