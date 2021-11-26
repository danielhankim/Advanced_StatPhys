############################################################
#                                                          #
#   This is a python wrapper to simulate Ising             #
#   model, measure susceptibility, and calculate           #
#   average values and errors.                             #
#                                                          #
#   You only need to change the variable "CMD" which       #
#   determintes the type of program!!                      #
#                                                          #
############################################################
import os
import sys
import numpy as np


EXE1 = 'ising2d.out' 
EXE2 = 'bs.out' 
EXE3 = 'avg.out'

Tc = 2.269185
L_list = [8, 16, 32, 64, 128]
T_list = np.arange(1., 4.01, step = 0.05)
T_list = np.append(Tc, T_list)
T_list = np.sort(T_list)

for L in L_list:
    for T in T_list:
        # You have to choose what program you are goind to use !!!
        # Remove "#" in front of CMD to activate it

        #CMD = "./%s %d %f" %(EXE1, L, T) # Ising model Simulation
        #CMD = "./%s %d %f" %(EXE2, L, T) # Calculate Susceptibility
        CMD = "./%s %d %f %s" %(EXE3, L, T, 'mag') # Calculate average order parameter and error
        #CMD = "./%s %d %f %s" %(EXE3, L, T, 'sus') # Calculating average susceptibility and error
        print(CMD)
        os.system(CMD)

print("##### Simulation over #####")
