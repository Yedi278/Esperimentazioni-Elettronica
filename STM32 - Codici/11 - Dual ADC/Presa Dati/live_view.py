import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Load data

df = pd.read_csv('Presa Dati/dati_doppio_raw.csv', sep=',', header=None)
data = df[:].to_numpy(dtype=float).T
vals = np.zeros((data.shape[1],2))

for i in range(data.shape[1]):

    # plt.plot(data[:200,i], color='blue')
    # plt.plot(data[200:,i], color='red')
    vals[i,0] = data[:200,i][110]
    vals[i,1] = data[200:,i][110]
    # plt.pause(.1)
    # plt.cla()
    
# plt.show()

# plt.subplot(1,2,1)
plt.hist(vals[:,0], bins=100, color='blue', alpha=0.5, density=True)
# plt.subplot(1,2,2)
plt.hist(vals[:,1], bins=100, color='red', alpha=0.5, density=True)
plt.show()