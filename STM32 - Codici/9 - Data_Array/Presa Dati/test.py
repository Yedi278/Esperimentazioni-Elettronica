import numpy as np
import matplotlib.pyplot as plt
import pandas as pd

df = pd.read_csv('Presa Dati/dati_long.csv', sep=',', header=None, )

# Plot the data
data = df[:].to_numpy(dtype=float)
data = data.T
print(data, data.shape)

plt.hist(data, bins=1000, density=True)
plt.title('Photon Histogram')
plt.ylabel('Bin Counts')
plt.xlabel('Amplitude [V]')
plt.savefig('Data_Array_Photon_Histogram.png')
plt.show()

df = pd.read_csv('Presa Dati/data_buffer.csv', sep=',', header=None)
data_2 = df[:].to_numpy(dtype=float)
print(len(data_2[0]))

for i in range(3000):
    plt.plot(range(100), data_2[i][:100], color='purple', alpha=0.01)
    
plt.title('Persistance View')
plt.ylabel('Amplitude [V]')
plt.xlabel('Time [200ns]')
plt.savefig('Data_Array_Persistance_View.png')
plt.show()