import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os

os.chdir(os.path.dirname(__file__))

df = pd.read_csv('hist_3.csv', header=None)

plt.hist(df[0], bins=100)
plt.show()