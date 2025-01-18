import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

os.chdir(os.path.dirname(__file__))

df = pd.read_csv('dati_luce_raw.csv', sep=',', header=None)

data_buffer = df.to_numpy(dtype=np.float32)

image = np.zeros((400, 400), dtype=np.float32)
max_value = np.max(data_buffer)
min_value = np.min(data_buffer)

def map(value):
    return int((value/(max_value) - min_value) * 800)


for m in range(4):
    for i in range(0, image.shape[0]):
        for j in range(0, image.shape[1]):
            if (data_buffer[i, 400*m + j] > .11):
                    
                index = (map(data_buffer[i, 400*m + j]) - 1) % image.shape[1]
                image[j, index]  += 1

image = image / np.max(image) *10


plt.imshow( np.flip(image.T, 0), cmap='hot')
plt.colorbar()
plt.title('Segnali con luce')
plt.xlabel('Time')
plt.yticks([])
plt.savefig('persistance3.pdf', format='pdf', bbox_inches='tight', dpi=500)
plt.show()