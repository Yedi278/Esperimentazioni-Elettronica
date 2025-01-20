import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import scipy.stats as stats
import os

os.chdir(os.path.dirname(os.path.abspath(__file__)))

df = pd.read_csv('dati_YAlG.csv', header=None)

data_buffer = df.to_numpy(dtype=float)

lx_SiPm = []
rx_SiPm = []
shift = 50
for i in range(data_buffer.shape[0]):
    lx_SiPm.append(data_buffer[i, shift])
    rx_SiPm.append(data_buffer[i, 400+shift])

nbin = 1000
plt.hist(lx_SiPm, bins=nbin, density=True, alpha=0.5, color='firebrick', label='Left SiPm')
rx_SiPm = np.array(rx_SiPm) * np.std(lx_SiPm) / np.std(rx_SiPm) - np.mean(rx_SiPm) + np.mean(lx_SiPm)
plt.hist(rx_SiPm, bins=nbin, density=True, alpha=0.5, color='steelblue', label='Right SiPm')
plt.xlim((0,0.15))
plt.legend()
plt.title('YAlG with 22Na')
plt.xlabel('Amplitude (V)')
plt.ylabel('Normalized counts')
plt.savefig('YAlG.pdf', bbox_inches='tight', dpi=300)
plt.show()