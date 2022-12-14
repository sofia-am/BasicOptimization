#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>
#include <unistd.h>

int XDIM = 10000;
int YDIM = 10000;

// We return the pointer
double **alloc_matrix(void) /* Allocate the array */
{
    /* Check if allocation succeeded. (check for NULL pointer) */
    int i; 
    double **array;
    array = calloc((size_t)((unsigned long)XDIM*sizeof(double *)), sizeof(double));
    for(i = 0 ; i < XDIM ; i++)
        array[i] = calloc((size_t)((unsigned long)YDIM*(int)sizeof(double)), sizeof(double));
/*
    for(j=0; j<XDIM; j++)
        for(k=0; k<YDIM; k++)
            memset(&array[k][j], j, sizeof(double));
*/
    return array;
}

void fill(double** arr) {
    int i = 0, j; 
    srand((unsigned)time(NULL));

    while(i < XDIM){
        j = 0;
        while(j < YDIM){
            arr[i][j] = (double)(rand() % 100);
            j++;
        }
        i++;
    }
}

void compute(double** arr, int kern[3][3]){
    double tmp_sum[9];
    double dato, accum;
    int i = 1, j, k, l;
    double num = 0.002;
    arr[0][0] = 0;
    while(i < XDIM-1){
        j = 1;
        while(j < YDIM-1){
            //printf("processing: %d - %d \n", i, j);
            k = l = 0;
            accum = 0;
            while(k < 3){
                l = 0;
                while(l < 3){
                    int x = i + (l-1);
                    int y = j + (k-1);
                    dato = arr[x][y];
                    tmp_sum[l*3+k] = (2*kern[l][k]*dato)*num + 1;
                    accum = accum + tmp_sum[l*3+k];
                    l++;
                }       
                k++;
            }               
            arr[i][j] = accum;
            j++;
        }
        i++;
    }    
}

void print(double** arr) {
    int i = 0, j;
    FILE *archivo;
    archivo = fopen("log2.txt", "w+");
    while(i < XDIM){
        j = 0;
        while(j < YDIM){
            fprintf(archivo, "array[%d][%d] = %f\t", i, j, arr[i][j]);
            j++;
        }
        i++;
    }
    fclose(archivo);
}

int main(void)
{
    double **arr;
    int kern[3][3] = {{0, -1, 0},{-1, 5, -1},{ 0, -1, 0}};

    arr = alloc_matrix();
    fill(arr);
    compute(arr, kern);
    print(arr);

    free(arr);
    return 0;
}