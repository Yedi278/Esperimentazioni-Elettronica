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

bin = 200
plt.figure(figsize=(8,6))
plt.title('BGO with 22Na')
plt.hist(lx, bins=bin, density=True, alpha=0.5, color='firebrick')
plt.hist(rx, bins=bin, density=True, alpha=0.5, color='steelblue')
plt.xlabel('Amplitude (V)')
plt.ylabel('Normalized counts')
plt.savefig('BGO_22Na_hist1.pdf', bbox_inches='tight', dpi=300)
plt.show()

plt.figure(figsize=(8,6))
plt.title('BGO with 22Na')
plt.subplot(2,1,1)
plt.hist(lx, bins=bin, density=True, alpha=0.5, color='firebrick', label='Left SiPm')
plt.ylabel('Normalized counts')
plt.legend()
plt.xlim(0.1, None)

plt.subplot(2,1,2)
plt.xlabel('Amplitude (V)')
plt.ylabel('Normalized counts')
plt.hist(rx, bins=bin, density=True, alpha=0.5, color='steelblue', label='Right SiPm')
plt.legend()
plt.xlim(0.1, None)
plt.savefig('BGO_22Na_hist2.pdf', bbox_inches='tight', dpi=300)
plt.show()