import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

os.chdir(os.path.dirname(__file__))

df = pd.read_csv('buio_1.csv', header=None)

plt.hist(df.to_numpy(dtype=float).T, bins=2000)
plt.xlim(0.07, .2)
plt.show()