import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os

os.chdir(os.path.dirname(__file__))

df = pd.read_csv('hist_1.csv', header=None)

plt.plot(df[0])
plt.show()