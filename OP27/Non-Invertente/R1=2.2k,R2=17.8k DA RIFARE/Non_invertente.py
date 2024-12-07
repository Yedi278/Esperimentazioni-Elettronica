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
# R1 = 2.2kOhm R2 = 17.8kOhm
############################
R1 = 2.2e3
R2 = 17.8e3
gain = (R1+R2)/R1

# Sinusoidal

# path_hf = r"Sinusoidi\hf"
# path_lf = r"Sinusoidi\lf"
# t_sin_17k8_hf, sin_17k8_hf = leggi_file(path_hf)
# t_sin_17k8_lf, sin_17k8_lf = leggi_file(path_lf)
# t_sin_17k8_lf = np.array(t_sin_17k8_lf)/np.max(t_sin_17k8_lf)
# t_sin_17k8_hf = np.array(t_sin_17k8_hf)/np.max(t_sin_17k8_hf)

# plt.figure(figsize=(6,4))
# plt.plot(t_sin_17k8_lf, sin_17k8_lf[1]  * 1e3)
# plt.plot(t_sin_17k8_hf, sin_17k8_hf[1] * 1e3)

# plt.title("Onde Sinusoidali $R_1 = 2.2k\Omega, R_2 = 8.2k\Omega$")
# plt.legend(["Low Frequency", "-3dB Frequency"]) 
# plt.xlabel("Time normalized [1]")
# plt.ylabel("Voltage [mV]")
# plt.savefig("imgs/Sin_17k8.pdf")
# plt.show()
# plt.close()

# Square

path_qf = r"Quadra\qf"

t_sq_17k8, sq_17k8 = leggi_file(path_qf)

t_sq_17k8 *= 1e6
plt.figure(figsize=(6,4))
plt.plot(t_sq_17k8, sq_17k8 * 1e3)


min_line = np.max(sq_17k8[0] * 1e3 * gain)
plt.fill_between(t_sq_17k8, sq_17k8[1] * 1e3, min_line, where=(sq_17k8[1] *1e3 > min_line), color='lightblue', alpha=0.7, label='Area above min line')

# Customize the plot
plt.axhline(min_line, color='black', linestyle='--', label='Minimum Line (0V)')  # Plot the minimum line (baseline)
plt.title("Onda Quadra $R_1 = 2.2k\Omega, R_2 = 8.2k\Omega$")
plt.xlabel("Time [$\mu$s]")
plt.ylabel("Voltage [mV]")
plt.savefig("imgs/Square_17k8.pdf")
plt.show()
plt.close()

# FFT Math Mode

path_fft = r"FFT\fft"

t_fft_17k8, fft_17k8 = leggi_file(path_fft)

plt.figure(figsize=(6,4))
plt.plot(t_fft_17k8, fft_17k8)

# lf_cursor = np.max(fft_17k8[0:100])
# lf_cursor = -30
# plt.plot([np.min(t_fft_17k8), np.max(t_fft_17k8)], [lf_cursor, lf_cursor], label='Low Frequency Cursor')
# hf_cursor = lf_cursor - 3
# plt.plot([np.min(t_fft_17k8), np.max(t_fft_17k8)], [hf_cursor, hf_cursor], label='-3dB Frequency Cursor')

plt.legend()
plt.title("FFT $R_1 = 2.2k\Omega, R_2 = 8.2k\Omega$")
plt.xlabel("Frequency [Hz]")
plt.ylabel("Amplitude")
# plt.xscale("log")
plt.savefig("imgs/FFT_17k8.pdf")
plt.show()
plt.close()