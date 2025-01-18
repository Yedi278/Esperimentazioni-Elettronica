import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

os.chdir(os.path.dirname(__file__))

df = pd.read_csv('dati_2_raw.csv', sep=',', header=None)

data_buffer = df.to_numpy(dtype=np.float32)

nmeas = 4
buff_size = data_buffer.shape[1] // nmeas
shift_lim = 10

for shift in [shift_lim,]:
    meas = []
    for i in range(0, data_buffer.shape[0]):
        for j in range(nmeas):
            if(data_buffer[i, j*buff_size + shift] > 0.12):
                meas.append(data_buffer[i, j*buff_size + shift])
    # plt.hist(meas, bins=200, label=f'shift={shift}', alpha=0.5, color=(shift/shift_lim, 0, 1-shift/shift_lim))

plt.title('Spettro')
plt.hist(meas, bins=300, alpha=1, color='firebrick')
plt.xlim(0.12, .6)
plt.ylabel('Bin Count [n]')
plt.xlabel('Tensione [V]')
plt.savefig('Spettro_dati2.pdf', bbox_inches='tight', dpi=300)
plt.show()