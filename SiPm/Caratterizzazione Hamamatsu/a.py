import numpy as np
import pandas as pd
import matplotlib.pyplot as plt
from iminuit import Minuit
from iminuit.cost import LeastSquares
from scipy import exp
import os

os.chdir(os.path.dirname(__file__))

df = pd.read_csv('Fotoni_termici_count.csv', sep=',')

# plt.scatter(df['OV[V]'], df['Time[ms]'])
# plt.show()

# plt.title('Dark Count Rate')
# plt.scatter(df['OV[V]'][6:], df['Time[ms]'][6:])
# plt.ylabel('Time[ms]')
# plt.xlabel('Overvoltage [V]')
# plt.savefig('SiPm_DCR.pdf', bbox_inches='tight')
# plt.show()

# LINEAR FIT

def linear(x, a, b):
    return a*x + b

sigma = 1

cost = LeastSquares(df['OV[V]'][5:], df['Time[ms]'][5:], sigma, linear)
m = Minuit(cost, a=1, b=0)
m.migrad()
m.hesse()

plt.figure(figsize=(10,5))
plt.subplot(122)
plt.title('Dark Count Rate intero range')
plt.scatter(df['OV[V]'][5:], df['Time[ms]'][5:])
plt.errorbar(df['OV[V]'][5:], linear(df['OV[V]'][5:], m.values['a'], m.values['b']), yerr=sigma, color='red', capsize=2)
plt.ylabel('Time[ms]')
plt.xlabel('Overvoltage [V]')

# exponential fit

def f_exp(x, a, b, c, t):
    return a*np.exp(b*(x+t)) + c
    
sigma = 10

cost = LeastSquares(df['OV[V]'][:], df['Time[ms]'][:], sigma, f_exp)
m = Minuit(cost, a=1e7, b=-2, c=500, t=-50)
m.migrad()
m.hesse()

plt.subplot(121)
plt.title('Dark Count Rate zona Lineare')
plt.scatter(df['OV[V]'], df['Time[ms]'])
plt.errorbar(df['OV[V]'][:], f_exp(df['OV[V]'][:], m.values['a'], m.values['b'], m.values['c'], m.values['t']), yerr=sigma, color='red', capsize=2)
plt.ylabel('Time[ms]')
plt.xlabel('Overvoltage [V]')
plt.savefig('SiPm_DCR.pdf', format='pdf', bbox_inches='tight', dpi=500)
plt.show()

print(40000/np.mean(df['Time[ms]'][5:]))
print(np.std(df['Time[ms]'][5:]))