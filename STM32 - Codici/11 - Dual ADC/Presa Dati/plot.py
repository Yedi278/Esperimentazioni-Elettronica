import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import seaborn as sns
import sys

# Usage:
# python Plotter.py <file_name> <raw_data>
# raw_data is optional and is set to 'n' by default
# Example:
# > python Plotter.py data y

if len(sys.argv) < 2:
    print("Usage: python test.py <file_name> where file_name is the name of the file without the extension")
    print("Example: python test.py data")
    sys.exit(1)
file_name = sys.argv[1]

raw_data = 'n'
if len(sys.argv) > 2:
    raw_data = sys.argv[2]

print("File name entered is:\t",file_name)

############################################
#               Plot the data              #
############################################

df = pd.read_csv(file_name+'_1.csv', sep=',', header=None, )
df_2 = pd.read_csv(file_name+'_2.csv', sep=',', header=None, )
data = df[:].to_numpy(dtype=float).T
data_2 = df_2[:].to_numpy(dtype=float).T


plt.subplots(1,2, figsize=(10,5))
plt.title('Photon Histogram')

plt.subplot(1,2,1)
plt.hist(data, bins=70, density=True, color='b', alpha=0.8, label='Data Left SiPM')
plt.ylabel('Bin Counts')
plt.xlabel('Amplitude [V]')
plt.legend()

plt.subplot(1,2,2)
plt.hist(data_2, bins=70, density=True, color='r', alpha=0.8, label='Data Right SiPM')
plt.ylabel('Bin Counts')
plt.xlabel('Amplitude [V]')
plt.legend()

# plt.savefig('Data_Array_Photon_Histogram.png')
plt.show()