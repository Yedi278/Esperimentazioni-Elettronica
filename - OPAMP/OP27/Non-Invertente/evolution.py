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

        print(i)
        
        tmp_dir = current_dir+f'\{i}'
        os.chdir(current_dir+f'\{i}')

        print(os.getcwd())
        path_hf = r"Sinusoidi\hf"
        path_lf = r"Sinusoidi\lf"
        t_sin_hf, sin_hf = leggi_file(path_hf)
        t_sin_lf, sin_lf = leggi_file(path_lf)

        sin.append([t_sin_hf,sin_hf,t_sin_lf,sin_lf])

        path_qf = r"Quadra\qf"

        t_sq, sq = leggi_file(path_qf)

        t_sq = t_sq / np.max(t_sq)

        