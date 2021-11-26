# Advanced_StatPhys

## Preliminaries
Before getting started with your simulation, please create the directories you need to save and read your data as follows:
```
project
│   README.md
|   figs
│   src
|   ...
└───data
      └───avg
      |     └───mag
      |     |    └───L128
      |     |    └───L64
      |     |    └───L32
      |     |    └───L16
      |     |    └───L8
      |     └───sus
      |          └───L128
      |          └───L64
      |          └───L32
      |          └───L16
      |          └───L8
      └───mag
      |    └───L128
      |    └───L64
      |    └───L32
      |    └───L16
      |    └───L8
      └───sus
           └───L128
           └───L64
           └───L32
           └───L16
           └───L8
```

## Introduction
This project is made up of mainly two parts: Simulating Ising model on 2D SQL & Finite-size scaling analysis.

The source code of the Ising model is made with C, and you can use it with the python3 wrapper, "run_single.py".
With "run_single.py", you can measure the magnetization (order parameter), susceptibility and calculate the 
average values and errors of them.
For extensive Monte Carlo simulations at $T_c \approx 2.269185$, you can use "run_at_TC.py"

The basic command line usage:
```
python3 run_single.py

python3 run_at_TC.py
```

## Modifying source codes
If you want to modify the source codes, you need to change the files in the directory "src".

#### ising2d.c
- N_ITER : the number of repeated simulations
- THERMALIZATION_T: the time we are waiting to reach the steady state
- MEASURE_T: the time we are measuring the magnetization after we reach the steady state

You can compile your new program as follows:
`gcc -O3 -o ising2d.out ising2d.c -lm`

#### bootstrap4sus.c
- N_measure : the number measurements you will make
- N_sample: the size of sampled data when you measure once

You can compile your new program as follows:
`gcc -O3 -o bs.out bootstrap4sus.c -lm`

#### make_avg.c
- Here, you have nothing to modify. This is just to calculate the mean and standard deviation values.

Anyway, you can compile your new program as follows:
`gcc -O3 -o avg.out make_avg.c -lm`

## Finite-size scaling analysis
You can measure the exponents and collapse the data in "FSS_analysis.ipynb".
All directories are prepared, and you only need to press enters.

## Basic workflow
1. Carry out measurements on magnetizations with "run_single.py" and "run_at_TC.py"
2. Carry out measurements on susceptibility with "run_single.py"
3. Calculate mean and error values of magnetization and susceptibility with "run_single.py".
4. Work on your finite-size scaling analysis with "FSS_analysis.ipynb".



## Good luck for your further projects :)
