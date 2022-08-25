# Laboratorio III: Optimización
### Estudiante:   Amallo, Sofía 

En el script **exe.sh** se encuentran los comandos para compilar, ejecutar y escribir en una archivo los resultados de gprof.
```
$ gcc -Wall -pedantic -Werror -Wextra -Wconversion -std=gnu11 -pg -no-pie -fno-builtin lab3.c -o lab3
$ ./lab3
$ gprof lab3 gmon.out > gprof_analysis.txt
```

Se ejecutó el programa sin modificaciones, compilando el programa con los flags: 
`-pg -no-pie -fno-builtin` donde:
- `-pg` le indica al compilador que inserte el código del que va a hacer uso la herramienta gprof para hacer el perfilado.
- `-no-pie` le indica al compilador que no ingrese código "position independent" porque eso modifica el proceso de creación de gprof
- `-fno-builtin` le dice al compilador que no optimice el código reemplazando algunas de nuestras funciones por funciones integradas o con funciones in-line

En resumen, le indicamos al compilador que no realice optimizaciones sobre nuestro código.
### 1era Iteración:
Los resultados obtenidos fueron los siguientes:
```
   %      cumulative   self            self     total           
  time     seconds   seconds  calls   s/call   s/call  name    
 86.63      19.21     19.21      1    19.21    19.21   compute
 12.21      21.91      2.71      1     2.71     2.71   print
  1.27      22.20      0.28      1     0.28     0.28   fill
  0.54      22.32      0.12      1     0.12     0.12   alloc_matrix
```

![](2022-04-17-17-01-49.png#center)

- total time %:  porcentaje de tiempo de ejecución que pasó en esta funcion y todos sus hijos.
- self time %: es el porcentaje de tiempo de ejecución que transcurrió en esta funcion solamente
- total calls: el total de veces que esta función fue llamada (incluyendo llamadas recursivas)

### 2da Iteración:

Se reemplazaron los print por fprint, para almacenarlos en una archivo de texto y evitar la impresión por pantalla.

Resultados: 
```
   %    cumulative   self            self     total           
  time   seconds   seconds  calls   s/call   s/call  name    
 91.33     12.84    12.84      1    12.84    12.84   compute
  5.73     13.65     0.81      1     0.81     0.81   print
  2.51     14.00     0.35      1     0.35     0.35   fill
  1.07     14.15     0.15      1     0.15     0.15   alloc_matrix
```

Reducción: **32,6%**

### 3ra Iteración:
Eliminé la línea `if(i >= 1 && j >=1 && i < XDIM-1 && j <YDIM-1)` cambiándole los argumentos a los for, para que i empiece de 1 y vaya hasta XDIM-1, lo mismo para j.

```
Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls   s/call   s/call  name    
 86.75      7.90     7.90        1     7.90     7.90  compute
  8.85      8.71     0.81        1     0.81     0.81  fill
  4.31      9.10     0.39        1     0.39     0.39  print
  0.00      9.10     0.00        1     0.00     0.00  alloc_matrix
```

Se reemplazaron los `for` por ciclos `while`, y se eliminó el siguiente fragmento:
```c
accum = 0;
for(k = 0; k < 3; k++)
    for(l = 0; l < 3; l++)
        accum = accum + tmp_sum[k*3+l]; 
```
ya que se podía incluir dentro de otro ciclo que recorría el arreglo `tmp_sum`.

Con esta optimización se logró una reducción del: **59,23%** 

### Ultima Iteración:
Se eliminaron algunos ciclos for de las funciones `print` y `fill`.
```
Each sample counts as 0.01 seconds.
  %   cumulative   self              self     total           
 time   seconds   seconds    calls   s/call   s/call  name    
 84.36      7.11     7.11        1     7.11     7.11  compute
  8.13      7.80     0.68        1     0.68     0.68  fill
  8.01      8.47     0.67        1     0.67     0.67  print
  0.00      8.47     0.00        1     0.00     0.00  alloc_matrix
```
## El tiempo de ejecución se redujo en un total de: 62,05%

Cabe destacar que hubieron más de 3 iteraciones, pero con pocos cambios significativos. 

