#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mt64.c"
#include "mt64.h"

#define N_measure 10000 /* # of measurements */
#define N_sample 1000 /* size of the sampled data */

int read_double_1col(char*, double*);
int write_double_1col(char*, double*, int);
int count_num_1col_data(char*);
int init_1d_ary(double*, int);
double calc_susceptibility(double*, int, int, int);

int main(int argc, char *argv[])
{
        
    init_genrand64((unsigned)time(NULL));
    int L, num_data, num_sample, num_measure, i, j, k;
    double T, m, *chi_list, *mag_list;
    char *fn, *fn2;
    L = atoi(argv[1]);
    T = atof(argv[2]);
    num_sample = N_sample;
    num_measure = N_measure;
    fn = (char *)malloc(sizeof(char)*200);
    fn2 = (char *)malloc(sizeof(char)*200);
    sprintf(fn, "./data/mag/L%d/mag_%f.dat", L, T);
    sprintf(fn2, "./data/sus/L%d/sus_%f.dat", L, T);
    num_data = count_num_1col_data(fn);
    printf("data_count = %d\n", num_data);
    mag_list = (double *)malloc(sizeof(double)*num_data);
    chi_list = (double *)malloc(sizeof(double)*num_measure);    
    
    init_1d_ary(mag_list, num_data);
    init_1d_ary(chi_list, num_measure);
    read_double_1col(fn, mag_list);
    
    for(i = 0; i < num_measure; i++)
    {
        //printf("iter = %d\n", i);
        chi_list[i] = calc_susceptibility(mag_list, num_sample, num_data, L);
    }
    
    write_double_1col(fn2, chi_list, num_measure);

    free(fn); free(fn2); free(mag_list); free(chi_list);
    return 0;
}


int read_double_1col(char *fn, double *d_ary)
{
    FILE *fp;
    int i, tmp;
    double m;

    fp = fopen(fn, "r");
    if(fp == NULL)
    {
        printf("fail to open the file (*_*);; \n");
        return -1;
    }
    else
    {
        for(i=0; !feof(fp); i++)
        {
            m = fscanf(fp, "%lf\n", (d_ary+i));
        }
    }
    fclose(fp);
    return 0;
}

int write_double_1col(char *fn, double *ary, int max)
{
    FILE *fp;
    int i;

    fp = fopen(fn, "w");
    if(fp == NULL)
    {
        printf("fail to open the file (*_*);; \n");
        return -1;
    }
    else
    {
        for(i = 0; i < max; i++)
        {
            fprintf(fp, "%f\n", ary[i]);
        }
    }
    fclose(fp);
    return 0;
}


int count_num_1col_data(char *fn)
{
    FILE *fp;
    int n;
    double a;
    
    fp = fopen(fn, "r");
    if(fp == NULL)
    {
        printf("fail to open the file (*_*);; \n");
        return -1;
    }
    else
    {
        for(n = 0; !feof(fp); n++) 
        {
            fscanf(fp, "%lf\n", &a);
            //printf("a = %f\n", a);
        }
    }
    fclose(fp);
    return n;
}

int init_1d_ary(double *ary, int N)
{   
    int i;
    for(i = 0; i < N; i++) { ary[i] = 0.;}
    return 0;
}

double calc_susceptibility(double *mag_list, int num_sample, int num_data, int L)
{
    /*##################################################*/
    /*# Here, we calculate the susceptibility with the #*/
    /*# Bootstrap method in Newman's text book         #*/
    /*##################################################*/

    
    int i, j;
    double rnd, chi, m, m1, m2;
    m = 0.; m1 = 0.; m2 = 0.; 
    for(i = 0; i < num_sample; i++)
    {
        rnd = genrand64_real2();
        j = (int) (rnd * num_data);
        m = mag_list[j];
        m1 += m;
        m2 += m*m;
    }
    m1 = (double) m1 / num_sample;
    m2 = (double) m2 / num_sample;
    chi = (double) L * L * (m2 - m1*m1);
    return chi;
}
