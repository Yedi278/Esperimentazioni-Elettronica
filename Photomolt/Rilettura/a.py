import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import os

dir_path = os.path.dirname(os.path.realpath(__file__))
os.chdir(dir_path)

df = pd.read_csv('hist3.csv', header=None)

plt.hist(df[0], bins=200)
# plt.plot(df[0])
plt.show()