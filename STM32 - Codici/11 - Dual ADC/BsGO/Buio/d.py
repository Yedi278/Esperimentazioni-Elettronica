import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

os.chdir(os.path.dirname(os.path.realpath(__file__)))

df = pd.read_csv('buio_raw.csv', sep=',', header=None)

# print(df[0:5000])
a = df[0:5000]
b = df[5000:]

a.to_csv('buio_raw1.csv', sep=',', header=None, index=None)
b.to_csv('buio_raw2.csv', sep=',', header=None, index=None)