/*
=====================================================================
Primer Proyecto Sistemas Operativos Sección de Hilos

Nombres:     	Jorge Eduardo Torrado Forero, Juan Diego Pérez Duarte

Profesor:   	John Corredor Franco

Institución:    Javeriana Bogotá

Fecha:        	Octubre 1 del 2023
======================================================================
*/


#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <math.h>
#include <sys/wait.h>
#include <sys/time.h>
#include <stdbool.h>
#include "modulo.h"

/*
Función: main
Parámetros de Entrada: numero de parametros y parametros de entrada (argv)
Valor de salida: retorna 0 si el programa se ejecuta correctamente
Descripción: Verifica que los parametros de entrada sean correctos, y llama a la función que carga los parametros,
lee el archivo y crea la matriz "dispersa".
*/

int main(int argc, char *argv[]) {
    struct timeval tiempoInicio;
    bool valido;
    int unos = 0, numero, filasPorHilo, residuo, inicio, final, porcentajeSparse;
    double cerosTotales;

    if(argc != 11){
        printf("Error: Numero de argumentos inválidos. El programa debe invocarse de la siguiente forma:\n");
        printf("$ ./pdispersa -f [numero de filas] -c [numero de columnas] -a [ruta archivo] -n [numero de procesos] -p [porcentaje]\n");
        exit(1);
    }
    CheckParameters(argv);

    FILE *file = fopen(archivo, "r");
    if (file == NULL) {
        perror("Error al abrir el archivo.\n");
        return 1;
    }

    int **matrix = reservarMatriz(matrix, num_filas, num_columnas);
    cargaDatos(matrix, num_filas, num_columnas, file, &valido);
    fclose(file);
    if(!valido)
    {
       printf("\n\nError, usted ha ingresado una dimension de filas y/o columnas mayor a la de la matriz del archivo, intente de nuevo con dimensiones menores por favor\nrecuerde que las filas y columnas que usted ingresa por consola deben ser iguales o menores a las dimensiones reales de la matriz almacenada en el archivo txt\n\n");
          return -1;
    }
    //imprimeMatriz muestra por pantalla al usuario la matriz que se extrajo del archivo
    imprimeMatriz(matrix, num_filas, num_columnas);

    pthread_t hilos[num_hilos];
    struct InfoHilos datosHilos[num_hilos];
    int contadorHilos[num_hilos];
    iniciar_tiempo(&tiempoInicio);
    if (num_filas >= num_columnas){
        filasPorHilo = num_filas / num_hilos;
        residuo = num_filas % num_hilos;
        inicio = 0;

        for (int i = 0; i < num_hilos; i++) {
            final = inicio + filasPorHilo + (i < residuo ? 1 : 0);

            datosHilos[i].inicio = inicio;
            datosHilos[i].final = final;
            datosHilos[i].matriz = matrix;
            datosHilos[i].columnas = num_columnas;
            datosHilos[i].contador = &contadorHilos[i];

            pthread_create(&hilos[i], NULL, buscarUno, (void *)&datosHilos[i]);

            inicio = final;
        }

        for (int i = 0; i < num_hilos; i++) {
            pthread_join(hilos[i], NULL);
        }
        for (int i = 0; i < num_hilos; i++) {
            unos += contadorHilos[i];
        }

        cerosTotales = (double)(num_columnas * num_filas) - unos;
        porcentajeSparse = ((cerosTotales / (num_columnas * num_filas)) * 100);
        numero = (int) cerosTotales;

        if (porcentajeSparse >= porcentaje) {
            printf("La matriz tiene un total de %d ceros (%d%%), por lo tanto se considera dispersa\n", numero, porcentajeSparse);
        } 

        else {
            printf("La matriz tiene un total de %d ceros (%d%%), por lo tanto no se considera dispersa\n", numero, porcentajeSparse);
        }
    }

    else if (num_filas < num_columnas){
        filasPorHilo = num_filas / num_hilos;
        residuo = num_filas % num_hilos;
        inicio = 0;

        for (int i = 0; i < num_hilos; i++) {
            final = inicio + filasPorHilo + (i < residuo ? 1 : 0);

            datosHilos[i].inicio = inicio;
            datosHilos[i].final = final;
            datosHilos[i].matriz = matrix;
            datosHilos[i].columnas = num_columnas;
            datosHilos[i].contador = &contadorHilos[i];

            pthread_create(&hilos[i], NULL, buscarUno, (void *)&datosHilos[i]);

            inicio = final;
        }

  
        for (int i = 0; i < num_hilos; i++) {
            pthread_join(hilos[i], NULL);
        }
            for (int i = 0; i < num_hilos; i++) {
            unos += contadorHilos[i];
        }


        cerosTotales = (double)(num_columnas * num_filas) - unos;
        porcentajeSparse = ((cerosTotales / (num_columnas * num_filas)) * 100);
        numero = (int) cerosTotales;

        if (porcentajeSparse >= porcentaje) {
            printf("La matriz tiene un total de %d ceros (%d%%), por lo tanto se considera dispersa\n", numero, porcentajeSparse);
        }

        else {
            printf("La matriz tiene un total de %d ceros (%d%%), por lo tanto no se considera dispersa\n", numero, porcentajeSparse);
        }
    }
  printf("\nLos hilos se demoraron %.7f segundos en realizar el analisis de la matriz\n", detener_tiempo(&tiempoInicio));  
  liberarMatriz(matrix, num_filas, num_columnas);
  
  return 0;
}
