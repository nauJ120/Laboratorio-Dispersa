#ifndef MODULO_H
#define MODULO_H

/* Módulo para la lectura de una matriz y calcular si es una matriz sparse*/

/*
Archivo: hdispersa.h
Realizado por: Jorge Eduardo Torrado Forero y Juan Diego Pérez Duarte
Fecha última modificación: 11/09/2023
*/

static int num_filas, num_columnas, num_hilos, porcentaje;
static char archivo[100];

struct InfoHilos {
    int inicio;
    int final;
    int **matriz;
    int columnas;
    int *contador;
};

void *buscarUno(void *arg);
void CheckParameters(char *parameters[]);
// Función para iniciar la medición del tiempo
void iniciar_tiempo(struct timeval *inicio);
// Función para detener la medición del tiempo
void detener_tiempo(struct timeval *inicio);
//funcion de imprimir matriz
void imprimeMatriz(int **matriz, int filas, int columnas);
//funcion para cargar datos a la matriz
void cargaDatos(int **matriz, int filas,int columnas, FILE* file);
//funcion para reservar matriz
int** reservarMatriz(int** matriz, int filas, int columnas);
//función para liberar la matriz
void liberarMatriz(int **matriz, int filas, int columnas);
#include "modulo.hxx"
#endif
