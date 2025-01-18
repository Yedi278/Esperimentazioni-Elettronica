import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

os.chdir(os.path.dirname(os.path.realpath(__file__)))


buio = pd.read_csv('dati.csv', delimiter=',', header=None)
luce = pd.read_csv('dati_led.csv', delimiter=',', header=None)

buio = np.array(buio[:], dtype=float)
luce = np.array(luce, dtype=float)

bin_val, bin_edges = np.histogram(buio.T, bins=1000, density=False)
bin_val_2, bin_edges_2 = np.histogram(luce.T, bins=bin_edges, density=False)

plt.hist(buio.T, density=False, bins=1000)
plt.show()
plt.hist(luce.T, density=False, bins=1000)
plt.show()