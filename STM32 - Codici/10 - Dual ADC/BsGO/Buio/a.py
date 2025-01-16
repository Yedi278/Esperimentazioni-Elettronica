import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

os.chdir(os.path.dirname(__file__))

df = pd.read_csv('buio_raw1.csv', header=None)
data = np.append(
    pd.read_csv('buio_raw1.csv', header=None).to_numpy(dtype=float),
    pd.read_csv('buio_raw2.csv', header=None).to_numpy(dtype=float),
    axis=0        
)
shift = 10
trigger = .15
lx, rx = [],[]
for i in range(data.shape[0]):
    if data[i, shift] > .1:
        lx.append(data[i, shift])
    if data[i, 400+shift] > .15:
        rx.append(data[i, 400+shift])

# for i in range(2,10):
#     plt.plot(data[i])
#     plt.vlines(shift, 0, data[i, shift], colors='red')
#     plt.vlines(400+shift, 0, data[i, 400+shift], colors='red')
#     plt.show()

plt.hist(lx, bins=500, density=True)
plt.hist(rx, bins=500, density=True)
plt.show()