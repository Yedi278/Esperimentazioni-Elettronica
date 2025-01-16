import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

os.chdir(os.path.dirname(__file__))

df_inv = pd.read_csv('Invertente/dati.csv', sep=',')
df_ni = pd.read_csv('Non-Invertente/dati.csv', sep=',')

plt.scatter(df_inv['Gain'],df_inv['BW'])
plt.scatter(df_ni['Gain'],df_ni['BW'])
plt.show()
print(df_inv,df_ni)