import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv('/Users/ibolde/coding/Esperimentazioni-Elettronica/Photomolt/pippo.Wfm.csv')

data = data[:250:]

plt.plot(data)
plt.show()