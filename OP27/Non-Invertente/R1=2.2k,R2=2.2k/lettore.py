import numpy as np
import pandas as pd

def leggi_file(nome_file:str):
    # Legge il file e restituisce un DataFrame
    
    with open(nome_file+'.metadata.csv', 'r') as f:
        header = f.readlines()
        for i in header:
            index = i.find('Resolution:')
            if index != -1:
                resolution = i[index+11:-2]
                break

    data = pd.read_csv( filepath_or_buffer=nome_file+'.csv', sep=',', header=None)

    x = data.shape[0]
    time = np.linspace(0, x*float(resolution), x)

    return time, data

if __name__ == '__main__':

    import matplotlib.pyplot as plt
    import scienceplots
    plt.style.use(['grid','science','no-latex'])

    file_path = r'C:\Users\yehan\Documents\Uni\Esperimentazioni-Elettronica\OP27\Non-Invertente\R1=2k,R2=2k\Sinusoidi\BW'

    t_data, data = leggi_file(file_path)

    plt.figure(figsize=(10,8))
    plt.title('$R_1 = 2k\Omega, R_2 = 2k\Omega, \omega =  1Mhz$')
    plt.plot(t_data, data[0], label='ingresso')
    plt.plot(t_data, data[1], label='uscita')
    plt.legend()
    plt.xlabel('Time [s]')
    plt.ylabel('Voltage [V]')
    plt.show()