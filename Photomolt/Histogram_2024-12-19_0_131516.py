import pandas as pd
import numpy as np
import matplotlib.pyplot as plt

data = pd.read_csv('/Users/ibolde/coding/Esperimentazioni-Elettronica/Photomolt/Histogram_2024-12-19_0_131516.Wfm.csv')


#45 , 52
#74 , 82
#105 , 112
#135 , 141
# 165 , 171
#195 , 200

fine_arr = [45 , 74 , 105 , 135 , 165 , 195 , len(data)-2]
inizio_arr = [0 , 52 , 82 , 112 , 141 , 171 , 200 , len(data)]

npdata = data.to_numpy()
full_curve = [npdata[i,0] for i in range(len(npdata))]

plt.stairs(full_curve)



noise = []
for i in range(len(full_curve)):

    for j in range(len(fine_arr)):
        
        if i in range(inizio_arr[j] , fine_arr[j]):
            noise.append(full_curve[i])
            break
        if i in range(fine_arr[j] , inizio_arr[j+1]):
            noise.append(0)
            break
        
print(len(data))

plt.stairs(noise)


plt.show()
