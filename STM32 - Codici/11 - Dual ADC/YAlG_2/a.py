import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os

os.chdir(os.path.dirname(os.path.abspath(__file__)))

df = pd.read_csv('dati_YAlG_2.csv', header=None)

data_buffer = df.to_numpy(dtype=float)

lx_SiPm = []
rx_SiPm = []
shift = 50
for i in range(data_buffer.shape[1]):
    lx_SiPm.append(data_buffer[shift,i])
    rx_SiPm.append(data_buffer[400+shift,i])

nbin = 100
plt.hist(lx_SiPm, bins=nbin, density=True, alpha=0.5, color='firebrick', label='Left SiPm')
rx_SiPm = np.array(rx_SiPm) * np.std(lx_SiPm) / np.std(rx_SiPm) - np.mean(rx_SiPm) + np.mean(lx_SiPm)
plt.hist(rx_SiPm, bins=nbin, density=True, alpha=0.5, color='steelblue', label='Right SiPm')
plt.xlim((0,0.15))
plt.legend()
plt.title('YAlG with 22Na')
plt.xlabel('Amplitude (V)')
plt.ylabel('Normalized counts')
plt.savefig('YAlG2.pdf', bbox_inches='tight', dpi=300)
plt.show()

plt.subplot(2,1,1)
plt.hist(lx_SiPm, bins=nbin, density=True, alpha=0.5, color='firebrick', label='Left SiPm')
plt.xlim((0,0.15))
plt.ylabel('Normalized counts')
plt.legend()

plt.subplot(2,1,2)
plt.hist(rx_SiPm, bins=nbin, density=True, alpha=0.5, color='steelblue', label='Right SiPm')
plt.xlim((0,0.15))
plt.xlabel('Amplitude (V)')
plt.ylabel('Normalized counts')
plt.legend()

plt.savefig('YAlG2_2.pdf', bbox_inches='tight', dpi=300)
plt.show()