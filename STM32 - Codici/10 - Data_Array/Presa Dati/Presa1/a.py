import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

os.chdir(os.path.dirname(__file__))

df = pd.read_csv('dati_raw.csv', sep=',', header=None)

data_buffer = df.to_numpy(dtype=np.float32)

nmeas = 4
buff_size = data_buffer.shape[1] // nmeas
shift_lim = 40

for shift in range(5, shift_lim, 2):
    meas = []
    for i in range(0, data_buffer.shape[0]):
        for j in range(nmeas):
            meas.append(data_buffer[i, j*buff_size + shift])
    plt.hist(meas, bins=200, label=f'shift={shift}', alpha=0.5, color=(shift/shift_lim, 0, 1-shift/shift_lim))

plt.xlim(0, 2)
plt.legend()
plt.show()