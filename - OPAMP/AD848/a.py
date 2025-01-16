import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

os.chdir(os.path.dirname(__file__))

df_inv = pd.read_csv('Invertente/dati.csv', sep=',')
df_ni = pd.read_csv('Non-Invertente/dati.csv', sep=',')

plt.subplot(2,1,1)
plt.title('Bandwith of AD848')
plt.plot(df_inv['Gain'],df_inv['BW'], marker='v', label='Invertente')
plt.plot(df_ni['Gain'],df_ni['BW'], marker='v', label='Non Invertente')
plt.ylabel('Bandwidth [Mhz]')
plt.legend()

plt.subplot(2,1,2)
plt.title('Overshoot')
plt.plot(df_inv['Gain'],df_inv['overshoot'], marker='v', label='Invertente')
plt.plot(df_ni['Gain'],df_ni['overshoot'], marker='v', label='Non Invertente')
plt.ylabel('Overshoot [%]')
plt.xlabel('Gain [1]')
plt.savefig('AD848_dati_tot.pdf', format='pdf', bbox_inches='tight')
plt.show()

bw = np.append(df_inv['BW'].to_numpy(dtype=float), df_ni['BW'].to_numpy(dtype=float))
print("Bandwith for AD848: ",np.mean(bw),'±', np.std(bw))