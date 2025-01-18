import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

os.chdir(os.path.dirname(os.path.realpath(__file__)))

df = pd.read_csv('22Na_raw1.csv', sep=',', header=None)
df2 = pd.read_csv('22Na_raw2.csv', sep=',', header=None)

data1 = df.to_numpy(dtype=float)
data2 = df2.to_numpy(dtype=float)

data = np.append(data1, data2, axis=0)

lx, rx = [],[]

for i in range(data.shape[0]):
    if data[i,15] > 0.15:
        lx.append(data[i,15])
    if data[i, 400+15] > 0.15:
        rx.append(data[i, 400+15])

plt.hist(lx, bins=400, density=True)
plt.hist(rx, bins=400, density=True)
plt.show()