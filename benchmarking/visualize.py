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
            size = name.split('/')[1]
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
            values.append([float(el[2]) for el in g])
            labels.append(k[1])
            
    return values, labels

#%%

def draw_boxplots(fig, values, labels, even=True):
    positions = range(1, (2*len(labels)+1), 2)
    if(even):
        positions = [pos+.6 for pos in positions]
        
    ax = fig.axes[0]
        
    ax.boxplot(values,
               labels=labels,
               positions=positions)    
    
    ax.set_xticklabels( labels, rotation=45 )
    ax.set_xlim(left=-1, right = 2*len(labels)+2+1, auto=False)
    ax.set_ylim(0, 3000000)
    
    
def create_fig(N):
    fig = matplotlib.figure.Figure()
    FigureCanvas(fig)
    
    ax = fig.add_subplot(111)
    ax.set_title('Benchmarking times (n_rooks)')    
    #ax.set_yscale('log')
    
    
    ax.set_xlim(left=-1, right = 2*N+2+1, auto=False)
    
    return fig
    
def save_fig(fig, filename):
    fig.savefig(filename)
    
#%%
    
if __name__ == '__main__':
    pass
    
no_omp_proc = load_processed("/home/florian/Uni/ACPP_Dev/glkernel/benchmarking/no_omp_result.csv")
omp_proc = load_processed("/home/florian/Uni/ACPP_Dev/glkernel/benchmarking/omp_result.csv")

fig = create_fig(len(no_omp_proc[0]))        
        
draw_boxplots(fig, no_omp_proc[0], [el + "no_omp" for el in no_omp_proc[1]], even=False)
draw_boxplots(fig, omp_proc[0], omp_proc[1], even=True)

save_fig(fig, "bench.png")

    
