import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

os.chdir(os.path.dirname(__file__))

df = pd.read_csv('dati_BsGO_22Na.csv', header=None)
data = np.array(df)

shift = 10
trigger = .15
lx, rx = [],[]
for i in range(data.shape[0]):
    # if data[i, shift] > .1:
        lx.append(data[i, shift])
    # if data[i, 400+shift] > .15:
        rx.append(data[i, 400+shift])

print(data.shape)

bin = 200
plt.subplot(2,1,1)
plt.hist(lx, bins=bin, density=True, alpha=0.5, color='firebrick', label='Left SiPm')
plt.xlim(0.1, 1)
plt.legend()
plt.title('BGO dark count')
plt.ylabel('Normalized counts')

plt.subplot(2,1,2)
plt.hist(rx, bins=bin, density=True, alpha=0.5, color='steelblue', label='Right SiPm')
plt.xlim(0.1, 1)
plt.legend()
plt.title('BGO dark count')
plt.ylabel('Normalized counts')

plt.xlabel('Amplitude (V)')
plt.savefig('BGO_dark_count.pdf', bbox_inches='tight', dpi=300)
plt.show()