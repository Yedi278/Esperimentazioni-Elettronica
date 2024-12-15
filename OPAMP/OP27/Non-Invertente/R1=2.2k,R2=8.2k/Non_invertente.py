import numpy as np
from lettore import *
import matplotlib.pyplot as plt
import scienceplots
plt.style.use(['grid','science','no-latex'])
import os

current_file_path = os.path.abspath(__file__)
current_dir = os.path.dirname(current_file_path)
os.chdir(current_dir)

############################
# R1 = 2.2kOhm R2 = 8.2kOhm
############################
R1 = 2.2e3
R2 = 8.2e3
gain = (R1+R2)/R1

# Sinusoidal

path_hf = r"Sinusoidi\hf"
path_lf = r"Sinusoidi\lf"
t_sin_8k2_hf, sin_8k2_hf = leggi_file(path_hf)
t_sin_8k2_lf, sin_8k2_lf = leggi_file(path_lf)
t_sin_8k2_lf = np.array(t_sin_8k2_lf)/np.max(t_sin_8k2_lf)
t_sin_8k2_hf = np.array(t_sin_8k2_hf)/np.max(t_sin_8k2_hf)

plt.figure(figsize=(6,4))
plt.plot(t_sin_8k2_lf, sin_8k2_lf[1]  * 1e3)
plt.plot(t_sin_8k2_hf, sin_8k2_hf[1] * 1e3)

plt.title("Onde Sinusoidali $R_1 = 2.2k\Omega, R_2 = 8.2k\Omega$")
plt.legend(["Low Frequency", "-3dB Frequency"]) 
plt.xlabel("Time normalized [1]")
plt.ylabel("Voltage [mV]")
plt.savefig("imgs/Sin_8k2.pdf")
plt.show()
plt.close()

# Square

path_qf = r"Quadra\qf"

t_sq_8k2, sq_8k2 = leggi_file(path_qf)

t_sq_8k2 *= 1e6
plt.figure(figsize=(6,4))
plt.plot(t_sq_8k2, sq_8k2 * 1e3)


min_line = np.max(sq_8k2[0] * 1e3 * gain)
plt.fill_between(t_sq_8k2, sq_8k2[1] * 1e3, min_line, where=(sq_8k2[1] *1e3 > min_line), color='lightblue', alpha=0.7, label='Area above min line')

# Customize the plot
plt.axhline(min_line, color='black', linestyle='--', label='Minimum Line (0V)')  # Plot the minimum line (baseline)
plt.title("Onda Quadra $R_1 = 2.2k\Omega, R_2 = 8.2k\Omega$")
plt.xlabel("Time [$\mu$s]")
plt.ylabel("Voltage [mV]")
plt.savefig("imgs/Square_8k2.pdf")
plt.show()
plt.close()

# FFT Math Mode

path_fft = r"FFT\fft"

t_fft_8k2, fft_8k2 = leggi_file(path_fft)

plt.figure(figsize=(6,4))
plt.plot(t_fft_8k2, fft_8k2)

lf_cursor = np.max(fft_8k2[0:100])
plt.plot([np.min(t_fft_8k2), np.max(t_fft_8k2)], [lf_cursor, lf_cursor], label='Low Frequency Cursor')
hf_cursor = lf_cursor - 3
plt.plot([np.min(t_fft_8k2), np.max(t_fft_8k2)], [hf_cursor, hf_cursor], label='-3dB Frequency Cursor')

plt.legend()
plt.title("FFT $R_1 = 2.2k\Omega, R_2 = 8.2k\Omega$")
plt.xlabel("Frequency [Hz]")
plt.ylabel("Amplitude")
plt.xscale("log")
plt.savefig("imgs/FFT_8k2.pdf")
plt.show()
plt.close()