#!/usr/bin/env python3
# -*- coding: utf-8 -*-
"""
Created on Sat Jan 13 12:28:50 2018

@author: florian
"""
#%%


import matplotlib.figure
import matplotlib.pyplot as plt
from matplotlib.backends.backend_agg import FigureCanvasAgg as FigureCanvas
import itertools
import seaborn as sns
import pandas as pd

#%%

def load_data(filepath):
    raw = read_in(filepath)
    
    return process_lines(raw)


#%%
def read_in(filename):
    with open(filename) as f:
        raw = []
        for line in f.readlines():
            raw.append(line.strip())
            
    return raw
        
#%%

def process_lines(raw):        
    offset = 4
    cpu_index = 3
    name_index = 0
    
    processed_elements = []
    for line in raw[offset:]:
        elements = line.strip().split(',')
        name = elements[name_index].strip('"')
        cpu_time = elements[cpu_index]
        
        split_name = name.split('_')
        if(len(split_name) == 3):
            size = name.split('/')[1] + ('²')
            label = name.split('/')[0].split('_')[1]
            processed_elements.append((label,size,cpu_time))
    
    return processed_elements

#%%
    
def load_processed(filepath):
    processed = load_data(filepath)
    
    
    labels = []
    values = []
    for k, g in itertools.groupby(processed, lambda el: (el[0],el[1])):
        if k[0] == 'stratified':
            for el in g:    
                values.append(float(el[2]))
                labels.append(k[1])
            
    return values, labels

#%%

def draw_boxplots(fig, df):
        
    ax = fig.axes[0]
        
    ax = sns.boxplot(x="size", y="values", hue="omp", data=df, ax=ax, linewidth=1.0, fliersize=2.0)

    ax.get_yaxis().set_label_text("Time (ns)")    

    # ax.set_ylim(0, 3000000)
    ax.set_yscale('log')
    
    
def create_fig():
    fig = matplotlib.figure.Figure()
    FigureCanvas(fig)
    
    ax = fig.add_subplot(111)
    #ax.set_yscale('log')
    ax.set_title('Benchmarking times (stratified sampling)') 
    sns.despine(ax=ax)
    

    
    return fig
    
def save_fig(fig, filename):
    fig.savefig(filename)
   
    #%%
    
def flatten(list_of_lists):
    return [item for sublist in list_of_lists for item in sublist]
#%%
    
if __name__ == '__main__':
    pass
    
no_omp_proc = load_processed("./no_omp_result.csv")
omp_proc = load_processed("./omp_result.csv")

sns.set(context="talk", style="white")

fig = create_fig()

data = {"size": no_omp_proc[1] + omp_proc[1], 
        "values": no_omp_proc[0] + omp_proc[0],
        "omp": ["No"]*len(no_omp_proc[0]) + ["Yes"] * len(omp_proc[0])}

data2 = {"size": flatten(zip(no_omp_proc[1], omp_proc[1])), 
        "values": flatten(zip(no_omp_proc[0], omp_proc[0])),
        "omp": ["No"]*len(no_omp_proc[0])*2}

df = pd.DataFrame(data=data)     

#%%

values = flatten(zip(no_omp_proc[0], omp_proc[0]))
labels = flatten(zip(no_omp_proc[1], omp_proc[1]))

        
draw_boxplots(fig, df)

save_fig(fig, "bench.png")

    
