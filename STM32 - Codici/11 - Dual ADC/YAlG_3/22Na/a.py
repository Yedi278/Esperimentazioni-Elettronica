import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os, sys

os.chdir(os.path.dirname(os.path.abspath(__file__)))

df = pd.read_csv('22Na_raw.csv', header=None)

data_buffer = df.to_numpy(dtype=float)

lx_SiPm = []
rx_SiPm = []
shift = 0

plt.plot(data_buffer[0,:])
plt.vlines(shift, 0, data_buffer[0, shift], colors='r')
plt.vlines(400+shift, 0, data_buffer[0, 400+shift], colors='r')
plt.show()

sys.exit()

for i in range(data_buffer.shape[0]):
    lx_SiPm.append(data_buffer[i, shift])
    rx_SiPm.append(data_buffer[i, 400+shift])

rx_new = (np.array(rx_SiPm) * np.std(lx_SiPm) / np.std(rx_SiPm)) - np.min(rx_SiPm) + np.min(lx_SiPm)

nbin = 1000
plt.hist(lx_SiPm, bins=nbin, density=True, alpha=0.5, color='firebrick', label='Left SiPm')
plt.hist(rx_new, bins=nbin, density=True, alpha=0.5, color='steelblue', label='Right SiPm')
plt.xlim((np.min(lx_SiPm), .25))
plt.title('YAlG with 22Na')
plt.xlabel('Amplitude (V)')
plt.ylabel('Normalized counts')
plt.legend()
plt.savefig('YAlG3.pdf', bbox_inches='tight', dpi=300)
plt.show()

sys.exit()

plt.subplot(2,1,1)
plt.hist(lx_SiPm, bins=nbin, density=True, alpha=0.5, color='firebrick', label='Left SiPm')
plt.xlim((0,0.15))
plt.ylabel('Normalized counts')
plt.legend()

plt.subplot(2,1,2)
plt.hist(rx_SiPm-np.median(rx_SiPm)+np.median(lx_SiPm), bins=nbin, density=True, alpha=0.5, color='steelblue', label='Right SiPm')
plt.xlim((0,0.15))
plt.xlabel('Amplitude (V)')
plt.ylabel('Normalized counts')
plt.legend()

plt.savefig('YAlG3_2.pdf', bbox_inches='tight', dpi=300)
plt.show()