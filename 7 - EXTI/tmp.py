import numpy as np
import matplotlib.pyplot as plt

def generate_gaussian_function(mean, variance, x):
    return (1 / np.sqrt(2 * np.pi * variance)) * np.exp(-((x - mean) ** 2) / (2 * variance))

x = np.arange(0, 500, 1)
y = 20*generate_gaussian_function(200, 1000, x)

# square wave
y_2 =  np.where(x < 120, 0, np.max(y))

plt.plot(x, y, label='Analog Signal')
plt.plot(x, y_2, label='Digital Signal')
plt.xlabel('Time')
plt.ylabel('Amplitude')
plt.legend()
plt.savefig('GPIO_EXTI_analogue_digital.pdf')
plt.show()
