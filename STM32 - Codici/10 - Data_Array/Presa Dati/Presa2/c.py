import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

os.chdir(os.path.dirname(__file__))

df = pd.read_csv('dati_2_raw.csv', sep=',', header=None)

data_buffer = df.to_numpy(dtype=np.float32)

plt.title('Esempio Campionamento Micro')
plt.plot(np.arange(0, 0.2*200, 0.2) ,data_buffer[10, :200])
plt.vlines(0.2*15, 0, data_buffer[10, 15], colors='r', linestyles='dashed', label='Campionamento dopo 3ms')
plt.xlabel('Time [ms]')
plt.ylabel('Amplitude [V]')
plt.legend()
plt.savefig('Campionamento.pdf', format='pdf', bbox_inches='tight', dpi=500)
plt.show()