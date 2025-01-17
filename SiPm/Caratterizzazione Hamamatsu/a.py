import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os

os.chdir(os.path.dirname(__file__))

df = pd.read_csv('Fotoni_termici_count.csv', sep=',')

plt.scatter(df['OV[V]'][6:], df['Time[ms]'][6:])
plt.show()

plt.scatter(df['OV[V]'], df['Time[ms]'])
plt.show()