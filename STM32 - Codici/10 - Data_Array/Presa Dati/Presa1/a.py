import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

os.chdir(os.path.dirname(__file__))

df = pd.read_csv('dati_raw.csv', sep=',', header=None)

data_buffer = df.to_numpy(dtype=np.float32)

nmeas = 4
buff_size = data_buffer.shape[1] // nmeas
shift_lim = 20

# for shift in range(5, shift_lim, 2):
for shift in range(shift_lim, shift_lim+1):
    meas = []
    for i in range(0, data_buffer.shape[0]):
        for j in range(nmeas):
            meas.append(data_buffer[i, j*buff_size + shift])
    # plt.hist(meas, bins=300, label=f'shift={shift}', alpha=0.5, color=(shift/shift_lim, 0, 1-shift/shift_lim))

# plt.title('Spettro')
plt.hist(meas, bins=300, alpha=1, color='firebrick')
plt.xlim(0.1, 1.5)
# plt.ylabel('Bin Count [n]')
# plt.xlabel('Tensione [V]')
# plt.xticks(np.arange(0.1, 1.5, 0.1))
plt.xticks([])
plt.yticks([])

# plt.savefig('Spettro_dati1.pdf', bbox_inches='tight', dpi=300)
plt.savefig('Icon.png', bbox_inches='tight', dpi=1200)
plt.show()