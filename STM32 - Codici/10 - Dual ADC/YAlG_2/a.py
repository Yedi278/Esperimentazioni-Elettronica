import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

df = pd.read_csv('dati_YAlG_2.csv', header=None)

data_buffer = df.to_numpy(dtype=float).T

lx_SiPm = []
rx_SiPm = []
shift = 50
for i in range(data_buffer.shape[1]):
    lx_SiPm.append(data_buffer[shift,i])
    rx_SiPm.append(data_buffer[400+shift,i])

nbin = 500
plt.hist(lx_SiPm, bins=nbin, density=True)
plt.hist(rx_SiPm, bins=nbin, density=True)
plt.xlim((0,0.15))

plt.show()
# plt.close()

# plt.plot(data_buffer[:400,3])
# plt.vlines(shift, 0, 1, colors='red')
# plt.show()