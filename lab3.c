#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <time.h>


int XDIM = 10000;
int YDIM = 10000;

// We return the pointer
u_int16_t **alloc_matrix(void) /* Allocate the array */
{
    /* Check if allocation succeeded. (check for NULL pointer) */
    int i; //j, k; 
    u_int16_t **array = calloc(XDIM*sizeof(u_int16_t *), sizeof(u_int16_t));

    for(i = 0 ; i < XDIM ; i++)
        array[i] = calloc(YDIM*sizeof(u_int16_t),  sizeof(u_int16_t));
 
    /*for(j=0; j<XDIM; j++)
        for(k=0; k<YDIM; k++)
            memset(&array[k][j], j, sizeof(u_int16_t));*/
    return array;
}

void fill(u_int16_t** arr) {
    int i, j;
    srand(time(NULL));
    for(i = 0 ; i < XDIM ; i++)
        for(j = 0 ; j < YDIM ; j++)
            arr[i][j] = (u_int16_t)(rand() % 100);
}

void compute(u_int16_t** arr, int kern[3][3]){
    u_int16_t tmp_sum[9];
    u_int16_t dato, accum;
    int i = 1, j = 1, k = 0, l = 0;
    //FILE *archivo;
    //archivo = fopen("log.txt", "a");
    arr[0][0] = 0;
    int num = 0.004;

    while(i < XDIM-1){
        while(j < YDIM-1){
            //fprintf(archivo, "processing: %d - %d \n", i, j);
            accum = 0;
            for(k = 0; k < 3; k++)
                for(l = 0; l < 3; l++){
                    int x = i + (l-1);
                    int y = j + (k-1);
                    dato = arr[x][y];
                    tmp_sum[l*3+k] = kern[l][k]*dato*num + 1;
                    accum = accum + tmp_sum[k*3+l];
                    arr[i][j] = accum;
                }  
            j++;  
        }
        i++;
    }    
}

void print(u_int16_t** arr, FILE* archivo) {
    int i, j;
    for(i = 0 ; i < XDIM ; i++)
        for(j = 0 ; j < YDIM ; j++)
            fprintf(archivo, "array[%d][%d] = %f\n", i, j, arr[i][j]);
}

int main(void)
{
    u_int16_t **arr;
    FILE *archivo;
    archivo = fopen("log.txt", "a");
    int kern[3][3] = {0, -1, 0, -1, 5, -1, 0, -1, 0};

    arr = alloc_matrix();
    fill(arr);
    compute(arr, kern);
    print(arr, archivo);

    return 0;
}
