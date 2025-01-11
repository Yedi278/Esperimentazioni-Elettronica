import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
import sys

# Read the data
data = pd.read_csv('hf.csv', delimiter=',', header=None)
res = 'Error'

#Find Resolution from metadta
with open('hf.metadata.csv', 'r') as f:
    lines = f.readlines()
    for i in lines:
        words = i.split(':')
        for j in range(len(words)):
            if words[j] == 'Resolution':
                res = float(words[j+1])
                print("Resolution: ", res)

data = data[0].to_numpy(dtype=np.float32)
time = np.linspace(0, len(data)*res, len(data))

# find local maximum of (x,y) data
def find_peaks(data, n=20):
    peaks = []
    for i in range(1, len(data)-1):
        try:
            if data[i] > data[i-n] and data[i] > data[i+n]:
                peaks.append(i)
        except:
            pass
    #group similar peaks
    i = 0
    while i < len(peaks)-1:
        if peaks[i+1] - peaks[i] < n:
            if data[peaks[i+1]] > data[peaks[i]]:
                peaks.pop(i)
            else:
                peaks.pop(i+1)
        else:
            i += 1
    return peaks

if len(sys.argv) > 1:
    peaks = find_peaks(data, int(sys.argv[1]))
else:
    peaks = find_peaks(data)
    
plt.scatter(time[peaks], data[peaks], color='red')
print("Number of peaks: ", len(peaks))

plt.plot(time, data)

freqs = []
for i in range(1, len(peaks)):
    freqs.append(1/(time[peaks[i]] - time[peaks[i-1]]))

print("Frequenza del segnale:\t",round(np.mean(freqs)/1e6, 4), "±", round(np.std(freqs)/1e6, 4), "MHz")
plt.show()