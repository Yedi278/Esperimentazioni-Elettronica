import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os

os.chdir(os.path.dirname(__file__))

df_buio = pd.read_csv('dati_buio_raw.csv', sep=',', decimal='.', header=0)
data_buio = df_buio.to_numpy(dtype=float)

df_luce = pd.read_csv('dati_luce_raw.csv', sep=',', decimal='.', header=0)
data_luce = df_luce.to_numpy(dtype=float)

buio, luce = [], []
measures = 4

for i in range(0, df_buio.shape[0]):
    for j in range(measures):
        buio.append(data_buio[i, 400*j])


for i in range(0, df_luce.shape[0]):
    for j in range(measures):
        luce.append(data_luce[i, 400*j])

plt.hist(buio, bins=100)
plt.show()
plt.hist(luce, bins=100)
plt.show()

