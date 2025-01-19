import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os

os.chdir(os.path.dirname(os.path.abspath(__file__)))

df = pd.read_csv('buio_raw.csv', header=None)

data_buffer = df.to_numpy(dtype=float)

lx_SiPm = []
rx_SiPm = []
shift = 50
for i in range(data_buffer.shape[0]):
    lx_SiPm.append(data_buffer[i,shift])
    rx_SiPm.append(data_buffer[i, 400+shift])

nbin = 100
plt.hist(lx_SiPm, bins=nbin, density=True)
plt.hist(rx_SiPm, bins=nbin, density=True)
plt.xlim((0,0.15))

plt.show()