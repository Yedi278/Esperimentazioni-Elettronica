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

df = pd.read_csv(file_name+'.csv', sep=',', header=None, )

data = df[:].to_numpy(dtype=float).T

plt.hist(data, bins=len(data)//100, density=True)
plt.title('Photon Histogram')
plt.ylabel('Bin Counts')
plt.xlabel('Amplitude [V]')
# plt.savefig('Data_Array_Photon_Histogram.png')
plt.show()

if(raw_data == 'n'):
    sys.exit(0)

df = pd.read_csv(file_name+'_raw.csv', sep=',', header=None)
data_2 = df[:].to_numpy(dtype=float)

x_data = []
y_data = []

for i in range(3000):
        plt.plot(range(100), data_2[i][0:100], color='purple', alpha=0.01)

plt.title('Persistance View')
plt.ylabel('Amplitude [V]')
plt.xlabel('Time [200ns]')
# plt.savefig('Data_Array_Persistance_View.png')
plt.show()