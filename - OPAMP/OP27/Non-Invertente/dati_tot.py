import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os

dir_path = os.path.dirname(os.path.realpath(__file__))
os.chdir(dir_path)
# Carico i dati
df = pd.read_csv('Dati_tot.csv', delimiter=',')

plt.subplot(2,1,1)
plt.title('Dati totali')
plt.plot(df['gain'],df['sin'], label='sin', marker='v')
plt.plot(df['gain'],df['quad'], label='quad', marker='v')
plt.plot(df['gain'],df['fft'], label='fft', marker='v')
plt.ylabel('Bandwidth (MHz)')
plt.xlabel('Gain (dB)')
plt.legend()
plt.subplot(2,1,2)
plt.plot(df['gain'],df['overshoot'], label='overshoot', marker='v')
plt.ylabel('Overshoot (%)')
plt.xlabel('Gain (dB)')
plt.legend()
plt.savefig('OP27_Non_Invert_Dati_tot.pdf', format='pdf', bbox_inches='tight')
plt.show()

# Calcolo la media
mean = df.mean()
print('Media:')
print(mean)

print((mean['sin']+mean['quad']+mean['fft'])/3)