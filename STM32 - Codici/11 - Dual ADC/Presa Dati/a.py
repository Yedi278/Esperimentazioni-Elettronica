import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

os.chdir(os.path.dirname(os.path.abspath(__file__)))

df = pd.read_csv('dati_doppio_raw.csv', sep=',', decimal='.')
data = df.to_numpy(dtype=np.float32)

lx = []
rx = []
p_lx, p_rx = [], []
for i in range(data.shape[0]):
    lx.append(data[i, :data.shape[1]//2])
    rx.append(data[i, data.shape[1]//2:])
    p_lx.append(data[i, 15])
    p_rx.append(data[i, data.shape[1]//2 + 15])

plt.title('Spettro Doppio SiPm')
plt.hist(p_lx, bins=60, alpha=0.5, label='Lx SiPm', color='firebrick', density=True)
plt.hist(p_rx, bins=60, alpha=0.5, label='Rx SiPm', color='steelblue', density=True)
plt.legend()
plt.xlabel('Tensione [V]')
plt.savefig('spettro_doppio_sipm.pdf', bbox_inches='tight', dpi=100)
plt.show()


plt.subplot(2, 1, 1)
plt.title('Spettro Doppio SiPm')
plt.hist(p_lx, bins=60, alpha=0.5, label='Lx SiPm', color='firebrick', density=True)
plt.legend()
plt.subplot(2, 1, 2)
plt.hist(p_rx, bins=60, alpha=0.5, label='Rx SiPm', color='steelblue', density=True)
plt.legend()
plt.xlabel('Tensione [V]')
plt.savefig('spettro_doppio_sipm_2.pdf', bbox_inches='tight', dpi=100)
plt.show()


