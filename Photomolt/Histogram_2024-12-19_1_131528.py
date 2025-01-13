import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv('Esperimentazioni-Elettronica/Photomolt/Histogram_2024-12-19_1_131528.Wfm.csv')

plt.plot(data)
plt.show()
#45 , 52
#74 , 82
#105 , 112
#135 , 141
# 165 , 171
#195 , 200

farr = [45 , 74 , 105 , 135 , 165 , 195 , len(data)-2]
iarr = [0 , 52 , 82 , 112 , 141 , 171 , 200 , len(data)]

npdata = data.to_numpy()
steps = [npdata[i,0] for i in range(len(npdata))]

plt.stairs(steps)

vec = []
for i in range(len(steps)):

    for j in range(len(farr)):
        
        if i in range(iarr[j] , farr[j]):
            vec.append(steps[i])
            break
        if i in range(farr[j] , iarr[j+1]):
            vec.append(0)
            break
        
print(len(data))

plt.stairs(vec)


plt.show()
