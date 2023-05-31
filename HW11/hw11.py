import time
from ulab import numpy as np
from ulab import utils



t = np.linspace(0,100,1024)
y = np.zeros(len(t))

f1, f2, f3 = (1, 2, 4)
for f in [f1, f2, f3]:
    y += np.sin(2 * np.pi * f * t)

Y = utils.spectrogram(y)[0:len(y)//2]

R = 2**3
Y = np.mean(Y.reshape((len(Y)//R, R)), axis=1)

for y in Y:
    print("("+str(y)+",)")
    time.sleep(0.01)
