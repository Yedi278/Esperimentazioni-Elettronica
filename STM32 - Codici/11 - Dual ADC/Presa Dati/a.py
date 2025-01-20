import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
from scipy import stats
import os
import sys

os.chdir(os.path.dirname(os.path.abspath(__file__)))

df = pd.read_csv('dati_doppio_raw.csv', sep=',', decimal='.')
data = df.to_numpy(dtype=np.float32)

shift = 50


p_lx, p_rx = [], []
for i in range(data.shape[0]):
    p_lx.append(data[i, shift])
    p_rx.append(data[i, data.shape[1]//2 + shift])

p_rx = np.array(p_rx)
p_lx = np.array(p_lx)

bin = 100

plt.title('Spettro Doppio SiPm')
plt.hist(p_lx, bins=bin, alpha=0.5, label='Lx SiPm', color='firebrick', density=True)

p_rx_new = p_rx * np.std(p_lx) / np.std(p_rx)
plt.hist(p_rx_new - np.median(p_rx_new) + np.median(p_lx), bins=bin, alpha=0.5, label='Rx SiPm', color='steelblue', density=True)

plt.legend()
plt.xlabel('Tensione [V]')
# plt.savefig('spettro_doppio_sipm_mod.pdf', bbox_inches='tight', dpi=100)
plt.show()

# plt.subplot(2, 1, 1)
# plt.title('Spettro Doppio SiPm')
# plt.hist(p_lx, bins=bin, alpha=0.5, label='Lx SiPm', color='firebrick', density=True)
# plt.legend()
# plt.subplot(2, 1, 2)
# plt.hist(p_rx, bins=bin, alpha=0.5, label='Rx SiPm', color='steelblue', density=True)
# plt.legend()
# plt.xlabel('Tensione [V]')
# plt.savefig('spettro_doppio_sipm_2.pdf', bbox_inches='tight', dpi=100)
# plt.show()


