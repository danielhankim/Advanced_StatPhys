############################################################
#                                                          #
#   This is a specialed python wrapper to simulate Ising   #
#   model at the critical temperature Tc!!!                #
#                                                          # 
#   You only need to change the variable "ITER" which      #
#   determintes the time of repeated simulation!!          #
#                                                          #
############################################################


import os
import sys
import numpy as np

EXE = 'ising2d.out'
Tc = 2.269185
L_list = [8, 16, 32, 64, 128]
ITER = 10

for i in range(ITER):
    print("Iteration: %d/%d" %(i+1, ITER))
    for L in L_list:
        command = "./%s %d %f" %(EXE, L, T)
        print(command)
        os.system(command)

print("##### Simulation over #####")
