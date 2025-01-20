import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os

dir_path = os.path.dirname(os.path.realpath(__file__))
os.chdir(dir_path)

marker_size = 3
line_width = 0.7
font_size = 8


# Carico i dati
df_1 = pd.read_csv('Invertente/Dati_tot.csv', delimiter=',')
df_2 = pd.read_csv('Non-Invertente/Dati_tot.csv', delimiter=',')

plt.subplot(2,2,1)
plt.title('Dati Invertente')
plt.plot(df_1['gain'],df_1['sin'], label='sin', marker='v', linestyle= '-', color='r', alpha=0.5 , markersize=marker_size , linewidth= line_width)
plt.plot(df_1['gain'],df_1['quad'], label='quad', marker='v', linestyle= '-', color='g', alpha=0.5 ,markersize=marker_size , linewidth= line_width)
plt.plot(df_1['gain'],df_1['fft'], label='fft', marker='v', linestyle= '-', color='b', alpha=0.5, markersize=marker_size , linewidth= line_width)
plt.ylabel('Bandwidth (MHz)')
plt.xlabel('Gain (dB)')
plt.legend( fontsize = font_size)

plt.subplot(2,2,2)
plt.title('Dati Non-Invertente')
plt.plot(df_2['gain'],df_2['sin'],label = 'sin', marker='v', linestyle= '-', color='r', alpha=0.5, markersize=marker_size , linewidth= line_width)
plt.plot(df_2['gain'],df_2['quad'], label = 'quad',marker='v', linestyle= '-', color='g', alpha=0.5, markersize=marker_size , linewidth= line_width)
plt.plot(df_2['gain'],df_2['fft'], label = 'fft',marker='v', linestyle= '-', color='b', alpha=0.5, markersize=marker_size , linewidth= line_width)
plt.ylabel('Bandwidth (MHz)')
plt.xlabel('Gain (dB)')
plt.legend(fontsize = font_size)

plt.subplot(2,2,3)
plt.plot(df_1['gain'],df_1['overshoot'], label='invertente', marker='v', markersize=marker_size , linewidth= line_width)
plt.ylabel('Overshoot (%)')
plt.xlabel('Gain (dB)')
plt.legend(fontsize = font_size)

plt.subplot(2,2,4)
plt.plot(df_2['gain'],df_2['overshoot'], label='non invertente', marker='v', markersize=marker_size, linewidth= line_width)

plt.ylabel('Overshoot (%)')
plt.xlabel('Gain (dB)')
plt.legend(fontsize = font_size)
plt.subplots_adjust(hspace=0.4 , wspace=0.4)
plt.savefig('Inv+Non-Inv.pdf', format='pdf')

plt.show()

#unisco tutte le misure
df = pd.concat([df_1, df_2], ignore_index=True)

BW = pd.concat([df_1['sin'], df_1['quad'], df_1['fft'], df_2['sin'], df_2['quad'], df_2['fft']], ignore_index=True)

print("Bandwidth: ", BW.mean(), " ± ", BW.std())
