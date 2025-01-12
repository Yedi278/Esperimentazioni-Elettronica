import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os

dir_path = os.path.dirname(os.path.realpath(__file__))
os.chdir(dir_path)

# Carico i dati
df_1 = pd.read_csv('Invertente/Dati_tot.csv', delimiter=',')
df_2 = pd.read_csv('Non-Invertente/Dati_tot.csv', delimiter=',')

plt.subplot(2,1,1)
plt.title('Dati Invertente e Non Invertente')
plt.plot(df_1['gain'],df_1['sin'], label='sin', marker='v', linestyle= '-', color='r', alpha=0.5)
plt.plot(df_1['gain'],df_1['quad'], label='quad', marker='v', linestyle= '-', color='g', alpha=0.5)
plt.plot(df_1['gain'],df_1['fft'], label='fft', marker='v', linestyle= '-', color='b', alpha=0.5)
plt.plot(df_2['gain'],df_2['sin'], marker='v', linestyle= '-', color='r', alpha=0.5)
plt.plot(df_2['gain'],df_2['quad'], marker='v', linestyle= '-', color='g', alpha=0.5)
plt.plot(df_2['gain'],df_2['fft'], marker='v', linestyle= '-', color='b', alpha=0.5)
plt.ylabel('Bandwidth (MHz)')
plt.xlabel('Gain (dB)')
plt.legend()
plt.subplot(2,1,2)
plt.plot(df_1['gain'],df_1['overshoot'], label='overshoot', marker='v')
plt.plot(df_2['gain'],df_2['overshoot'], label='overshoot', marker='v')

plt.ylabel('Overshoot (%)')
plt.xlabel('Gain (dB)')
plt.legend()
plt.savefig('Inv+Non-Inv.pdf', format='pdf', bbox_inches='tight')
plt.show()

#unisco tutte le misure
df = pd.concat([df_1, df_2], ignore_index=True)

BW = pd.concat([df_1['sin'], df_1['quad'], df_1['fft'], df_2['sin'], df_2['quad'], df_2['fft']], ignore_index=True)

print("Bandwidth: ", BW.mean(), " ± ", BW.std())
