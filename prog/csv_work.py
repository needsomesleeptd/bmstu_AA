import pandas
import pandas as pd
import matplotlib.pyplot as plt
from matplotlib import lines
import numpy as np


def to_csv(df, name):
    df.to_csv(name, encoding='utf-8', index=False)
    print(df.columns)


def plot_graphs(df, x: str, y: list, xlabel, ylabel, legend: list, filename: str, y_scale=False, x_scale=False):
    line_styles = [i for i in lines.lineStyles.keys() if i != 'None']
    markers = list(lines.lineMarkers.keys())[1:]
    #    df.columns = df.columns.astype("string")
    # rint(df.columns)
    # print(x)
    style = [line_styles[i] + markers[i] for i in range(len(y))]
    plot = df.plot(x=x, y=y,
                   kind='line',
                   xlabel=xlabel,
                   ylabel=ylabel,
                   style=style,
                   grid=True)

    if y_scale:
        plot.set_yscale("log")
    if x_scale:
        plot.set_xscale("log")
    plt.legend(legend)
    plt.savefig(filename)
    plt.show()



def is_power_of_two(n):
    return ((n != 0) and (n & (n - 1) == 0)) or n == 96


def is_odd(n):
    return (n != 30)

name = "./parametrization_class1.txt"

# df_mem = pd.read_csv("memory_measure.csv")
df_time = pd.read_csv(name)
df_time.columns = ['alpha','k_eva','days','optim','delta']

#df_time = pandas.DataFrame(columns = ['alpha','k_eva','days','optim','delta'], data = table)

df_time = df_time[df_time['days'].apply(is_odd)]

print(len(df_time))
print(df_time.head())
to_csv(df_time,'modified_params.txt')
#df_time.plot(x='ind', y='cnt', kind='barh', color='skyblue', figsize=(20, 28),width = 0.6)
#plt.show()



