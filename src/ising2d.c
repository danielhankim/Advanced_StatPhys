#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mt64.h"
#include "mt64.c"

#define N_ITER 50 /* # of simulation */
#define THERMALIZATION_T 20000
#define MEASURE_T 2000

double calc_m1(int*, int);
double calc_E1(int**, int*, int); /*not used for this time! */
int init_spin_values(int*, int);


int main(int argc, char *argv[])
{

 	init_genrand64((unsigned)time(NULL));
 	FILE *fp1, *fp2;
 	char m1_file[100],E1_file[100];
    int avg_t, steady_t, MCSS_max, N, spin_sum, abs_spin_sum, 
        target, MCSS, L, i, j, k, n, E_delta, tmp, s, iter;
    
    double m, m_abs, m1, m2, m4,
           Tc, J, flip_prob, flip_prob1, flip_prob2,
	       E1, E2, cv, rnd, t, u, chi;

	avg_t = MEASURE_T;
    steady_t = THERMALIZATION_T;
    MCSS_max = avg_t + steady_t;

	L = atof(argv[1]);
    t = atof(argv[2]);

	printf("L = %d\n", L);
	N = L*L;
	int **adj = (int **)malloc(sizeof(int *) *N);
	int *spin_config = (int *)malloc(sizeof(int)*N);
	//2D square lattice with PBC
	
    for(i = 0; i < N; i++){
		adj[i] = (int *)malloc(sizeof(int)*4);
	}
	for(i = 0; i < N; i++){
		adj[i][0] = i - 1;//left
		if(i % L == 0){adj[i][0] += L;}
		adj[i][1] = i + 1;//right
		if(adj[i][1] % L == 0){adj[i][1] += -L;}
		adj[i][2] = i -L;//up
		if(adj[i][2] <  0){adj[i][2] += L*L;}
		adj[i][3] = i + L;//down
		if(adj[i][3] > N-1){adj[i][3] += - L*L;}	
	}
	
    for(iter = 0; iter < N_ITER; iter++)
    {
        init_spin_values(spin_config, L);
		//s=0;
        sprintf(m1_file, "./data/mag/L%d/mag_%f.dat", L, t);
        //sprintf(E1_file, "./eng/L%d/e1/e1_%f.dat", L, t);
        
        fp1 = fopen(m1_file, "at");
        //fp2 = fopen(E1_file, "at");
        flip_prob1 = exp(-4./t);
        flip_prob2 = exp(-8./t);
        for(MCSS = 0; MCSS < MCSS_max; MCSS++){
            for(n = 0; n < N; n++){
                //metropolis algorithm
                //1. Choose a spin randomly
                target = (int)N*genrand64_real2();
                //2. calc energy difference
                tmp = 0;
                for(j=0; j < 4; j++){
                    tmp += spin_config[adj[target][j]];
                }
                E_delta = 2*spin_config[target]*tmp;

                if(E_delta <= 0){spin_config[target] = -spin_config[target];}
                else{
                    if(abs(tmp) == 2){
                        flip_prob = flip_prob1;
                    }
                    else{
                        flip_prob = flip_prob2;
                    }
                    rnd = genrand64_real2();
                    if(rnd < flip_prob){
                        spin_config[target] = -spin_config[target];
                    }
                }
            }

            //4.after cool down
            if(MCSS > steady_t-1){//if the system is thermalized enough

                m1 = calc_m1(spin_config, N);
                //E1 = calc_E1(adj, spin_config, N);
                fprintf(fp1, "%f\n", m1);
                //fprintf(fp2, "%f\n", E1);
            }
        }
        fclose(fp1);
        //fclose(fp2);
	}
	for(i = 0; i < N; i++) {free(adj[i]);}
	free(adj);
	free(spin_config);
	
	return 0;
}

double calc_m1(int* spin_config, int N)
{
	int i, tmp;
	double m;
	for(tmp=0,i = 0 ; i < N; i++)
    {
		tmp += spin_config[i];
	}
	m = fabs((double)tmp/(double)N);
	return m;
}


double calc_E1(int** adj, int* spin_config, int N)
{
	int i, j, tmp;
	double u;
	tmp = 0;
	for(i = 0; i < N; i++)
    {
		for(j = 0; j < 4; j++)
        {
			tmp += -spin_config[i]*spin_config[adj[i][j]];
		}
	}
	u = (double)tmp/(double)2;
	return u;
}

int init_spin_values(int* spin_config, int L)
{
    int N, i;
    N = L * L;
    for(i = 0; i < N; i++)
    {
	    spin_config[i] = 1;
    }
    return 0;
}
