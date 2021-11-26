#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include "mt64.c"
#include "mt64.h"

int read_double_1col(char*, double*);
int write_double_3col(char*, double, double, double);
int count_num_1col_data(char*);
int init_1d_ary(double*, int);
double calc_mean(double*, int);
double calc_err(double*, int, double);

int main(int argc, char *argv[])
{
        
    init_genrand64((unsigned)time(NULL));
    int L, num_data, num_sample, num_measure, i, j, k;
    double T, mean, err, *data_list;
    char *fn, *fn2, *tag;
    L = atoi(argv[1]);
    T = atof(argv[2]);
    tag = argv[3];
    fn = (char *)malloc(sizeof(char)*200);
    fn2 = (char *)malloc(sizeof(char)*200);
    printf("%s\n", tag);
    sprintf(fn, "./data/%s/L%d/%s_%f.dat",tag, L, tag, T);
    sprintf(fn2, "./data/avg/%s/L%d/avg_%s.dat",tag, L, tag);
    num_data = count_num_1col_data(fn);
    printf("data_count = %d\n", num_data);
    data_list = (double *)malloc(sizeof(double)*num_data);
    
    init_1d_ary(data_list, num_data);
    read_double_1col(fn, data_list);
    mean = calc_mean(data_list, num_data);
    err = calc_err(data_list, num_data, mean); 
    
    write_double_3col(fn2, T, mean, err);

    free(fn); free(fn2); free(data_list);
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
        printf("1818181818 fail to open the file (*_*);; \n");
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

int write_double_3col(char *fn, double T, double mean, double err)
{
    FILE *fp;

    fp = fopen(fn, "a");
    if(fp == NULL)
    {
        printf("1818181818 fail to open the file (*_*);; \n");
        return -1;
    }
    else
    {
        fprintf(fp, "%f;%lf;%lf\n", T, mean, err);
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
        printf("1818181818 fail to open the file (*_*);; \n");
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

double calc_mean(double *ary, int N)
{
    int i;
    double mean;
    for(mean = 0., i = 0; i < N; i++)
    {
        mean += ary[i];
    }
    mean = mean / (double) N;
    return mean;
}

double calc_err(double *ary, int N, double mean)
{
    int i;
    double base, var, err;
    for (var = 0, err = 0., i = 0; i < N; i++)
    {   
        base = (ary[i] - mean);
        var += pow(base, 2.0);
    } 
    err = sqrt(var / (double) (N-1));
    return err;
}

