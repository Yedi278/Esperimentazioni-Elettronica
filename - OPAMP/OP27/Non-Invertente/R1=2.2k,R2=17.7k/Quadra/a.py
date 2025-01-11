import numpy as np
import pandas as pd
import matplotlib.pyplot as plt

# Read the data
data = pd.read_csv('qf.csv', delimiter=',', header=None)
res = 'Error'

#Find Resolution from metadta
with open('qf.metadata.csv', 'r') as f:
    lines = f.readlines()
    for i in lines:
        words = i.split(':')
        for j in range(len(words)):
            if words[j] == 'Resolution':
                res = float(words[j+1])
                print("Resolution: ", res)

data = data[0].to_numpy(dtype=np.float32)
time = np.linspace(0, len(data)*res, len(data))

plt.plot(time, data)
plt.show()