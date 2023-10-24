#ifndef MODULO_H
#define MODULO_H
#include <stdio.h>

//struct que se usará para decirle a cada proceso, a usted le corresponde mirar desde la casilla x1, y1 hasta la casilla x2, y2
typedef struct
{
    int fInicial; 	//fila inicial
    int cInicial;	//columna inicial
    int fFinal;	//fila final
    int cFinal;	//columna final
}recorrido;

//imprimeMatriz muestra por pantalla al usuario la matriz que se extrajo del archivo
void imprimeMatriz(int **matriz, int filas, int columnas);
// Función para el cargue de datos
void cargaDatos(FILE *arch, int **matriz, int filas, int columnas, bool *valido);
// Función para contar los 0's en una sección de la matriz
int contarZeros(int **matriz, recorrido rango, int columnas);
// Función para iniciar la medición del tiempo
void iniciar_tiempo(struct timeval *inicio);
// Función para detener la medición del tiempo y calcular la duración
double detener_tiempo(struct timeval *inicio);
//funcion de reserva de matriz
int** reservarMatriz(int **matriz, int filas, int columnas);
//funcion que libera memoria
void freeMemory(int **matriz,int filas,int *pipe1);
//funcion que comprueba datos
void comprobarDatos(int argc, char* argv[], bool* hayFilas, bool* hayColumnas, bool*hayArchivo, bool* hayPorcentaje, bool*hayNProcesos, int* filas, int* columnas, float* porcentaje, int* nProcesos, char** nombreArchivo);
//funcion que distribuye los trabajos
void asignarTrabajos(recorrido* p1, recorrido* p2, int filas, int columnas, int trabajoProcesos);
#include "modulo.hxx"
#endif
