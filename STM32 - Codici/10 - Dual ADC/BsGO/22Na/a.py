import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import os

os.chdir(os.path.dirname(os.path.realpath(__file__)))

df = pd.read_csv('22Na_raw1.csv', sep=',', header=None)
df2 = pd.read_csv('22Na_raw2.csv', sep=',', header=None)