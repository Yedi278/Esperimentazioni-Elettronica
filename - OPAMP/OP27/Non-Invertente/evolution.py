import numpy as np
from lettore import *
import matplotlib.pyplot as plt
import scienceplots
plt.style.use(['grid','science','no-latex'])
import os

current_file_path = os.path.abspath(__file__)
current_dir = os.path.dirname(current_file_path)
os.chdir(current_dir)

sin = []
sqr = []
fft = []

lista_misure = os.listdir()

for i in lista_misure:
    if not os.path.isfile(i) and str(i)[0] != '_':

        tmp_dir = current_dir+f'\{i}'
        os.chdir(current_dir+f'\{i}')

        # print(os.getcwd())

        path_qf = r"Quadra\qf"
        t_sq, sq = leggi_file(path_qf)


        t_sq = t_sq / 4e-10
        sq = sq[1] - np.min(sq[1])
        sq = sq / np.max(sq)

        sqr.append((t_sq,sq, i))

plt.subplot(1,1,1)

for i in sqr:
    plt.plot(i[0], i[1], label=i[2])

plt.legend()
plt.show()