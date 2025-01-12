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
plt.plot(df_1['gain'],df_1['sin'], label='sin', marker='v')
plt.plot(df_1['gain'],df_1['quad'], label='quad', marker='v')
plt.plot(df_1['gain'],df_1['fft'], label='fft', marker='v')
plt.plot(df_2['gain'],df_2['sin'], label='sin', marker='v')
plt.plot(df_2['gain'],df_2['quad'], label='quad', marker='v')
plt.plot(df_2['gain'],df_2['fft'], label='fft', marker='v')
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

# Calcolo la media
mean_1 = df_1.mean()
mean_2 = df_2.mean()
print('Media:')
print(mean_1)
print(mean_2)
print((mean_1['sin']+mean_1['quad']+mean_1['fft']+mean_2['sin']+mean_2['quad']+mean_2['fft'])/6)