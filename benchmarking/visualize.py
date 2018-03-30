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
from numpy import median

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
    
    
    times = []
    sizes = []
    time_per_element = []
    functions = []
    for k, g in itertools.groupby(processed, lambda el: (el[0],el[1])):
        for el in g:    
            times.append(float(el[2]))
            sizes.append(k[1])
            time_per_element.append(float(el[2]) / float(k[1][:-1]) ** 2)
            functions.append(k[0])
            
    return times, sizes, functions, time_per_element

#%%

def draw_boxplots(fig, df):
        
    ax = fig.axes[0]
        
    ax = sns.barplot(x="kernel size", y="time_per_element", hue="omp", data=df, ax=ax)

    ax.get_yaxis().set_label_text("Time (ns)")    

    # ax.set_ylim(0, 3000000)
    
    # ax.set_yscale('log')
    
    
def create_fig(function):
    fig = matplotlib.figure.Figure()
    FigureCanvas(fig)
    
    ax = fig.add_subplot(111)
   # ax.set_yscale('log')
    ax.set_title('Time per element ({})'.format(function)) 
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

data = {"kernel size": no_omp_proc[1] + omp_proc[1], 
        "times": no_omp_proc[0] + omp_proc[0],
        "functions": no_omp_proc[2] + omp_proc[2],
        "time_per_element": no_omp_proc[3] + omp_proc[3],
        "omp": ["No"]*len(no_omp_proc[0]) + ["Yes"] * len(omp_proc[0])}

df = pd.DataFrame(data=data)     

#%%

for function, group in df.groupby(['functions']):
    fig = create_fig(function)
    draw_boxplots(fig, group)
    save_fig(fig, "bench_{}.png".format(function))


    
