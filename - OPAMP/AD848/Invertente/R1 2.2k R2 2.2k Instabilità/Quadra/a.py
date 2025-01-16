import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

os.chdir(os.path.dirname(__file__))

df = pd.read_csv('qf.csv', header=None)

plt.title('Risposta a Onda Quadra Gain Basso')
plt.plot(df[0]*1e9, df[1]*1e3, label='segnale ingresso')
plt.plot(df[0]*1e9, df[2]*1e3, label='risposta AD848')
plt.ylabel('Amplitude [mV]')
plt.xlabel('time [ns]')
plt.savefig('Inv_low_gain.pdf', bbox_inches='tight')
plt.show()