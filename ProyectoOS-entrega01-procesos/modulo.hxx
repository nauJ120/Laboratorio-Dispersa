#ifndef MODULO_HXX
#define MODULO_HXX

#include "modulo.h"
//imprimeMatriz muestra por pantalla al usuario la matriz que se extrajo del archivo
void imprimeMatriz(int **matriz, int filas, int columnas)
{
   if(filas < 10 && columnas < 10)
   {
        printf("\n\nEsta es la matriz que se extrajo del archivo:\n\n"); 
        for(int i = 0; i < filas; i++)
        {
            for(int j = 0; j < columnas; j++)
            {
                printf("%d ",matriz[i][j]);
            }
            printf("\n\n");
        }
   }
}

// Función para el cargue de datos
void cargaDatos(FILE *arch, int **matriz, int filas, int columnas)
{
    for (int i = 0; i < filas; i++)
    {
        for (int j = 0; j < columnas; j++)
        {
            fscanf(arch, "%d", &matriz[i][j]);
        }
    }
}

// Función para contar los 0's en una sección de la matriz
int contarZeros(int **matriz, recorrido rango, int columnas)
{
    int count = 0;
    for (int i = rango.fInicial; i <= rango.fFinal; i++)
    {
        int j = rango.cInicial;
        if(i != rango.fInicial)
        {
            j = 0;
        }
        for (j; j < columnas; j++)
        {
            if (matriz[i][j] == 0)
            {
                count++;
            }
            //si el proceso se encuentra en la posicion x2, y2 significa que ya ha terminado su tarea
            if(j == rango.cFinal && i == rango.fFinal)
            {
                return count;
            }
        }
    }
    return count;
}
// Función para iniciar la medición del tiempo
void iniciar_tiempo(struct timeval *inicio) {
    gettimeofday(inicio, NULL);
}

// Función para detener la medición del tiempo y calcular la duración
void detener_tiempo(struct timeval *inicio) {
    struct timeval fin;
    gettimeofday(&fin, NULL);

    double segundos = (double)(fin.tv_sec - inicio->tv_sec) + (double)(fin.tv_usec - inicio->tv_usec) / 1000000.0;
    printf("\n\nEl tiempo de ejecucion del programa es: %.4f segundos\n\n", segundos);
}
int** reservarMatriz(int** matriz, int filas, int columnas)
{
       //reservo espacios de memoria para la matriz, esto mediante el uso de malloc (malloc reserva N bytes consecutivos en la memoria)
        matriz = (int **)malloc(filas * sizeof(int *));
        for (int i = 0; i < filas; i++)
            matriz[i] = (int *)malloc(columnas * sizeof(int));
        return matriz;
}
void freeMemory(int **matriz,int filas,int *pipe1) {
    if (matriz != NULL) {
        //Se libera el espacio reservado
        for (int i = 0; i < filas; i++) {
            free(matriz[i]);
        }
        free(matriz);
    }

    if (pipe1 != NULL) {
        free(pipe1);
    }
}
//comprobacion
void comprobarDatos(int argc, char* argv[], bool* hayFilas, bool* hayColumnas, bool*hayArchivo, bool* hayPorcentaje, bool*hayNProcesos, int* filas, int* columnas, float* porcentaje, int* nProcesos, char** nombreArchivo)
{
  //leo los argumentos que el usuario pasa por consola para extraer de estos los datos relevantes como filas, columnas, nombre del archivo, porcentaje de 0's, etc
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (strstr(argv[i], "-f") != NULL)
            {
                if (i + 1 < argc)
                    *filas = atoi(argv[i + 1]);
                if(*filas >= 0)
                  *hayFilas = true;
            }
            if (strstr(argv[i], "-c") != NULL)
            {
                if (i + 1 < argc)
                    *columnas = atoi(argv[i + 1]);
                if(*columnas >= 0)
                  *hayColumnas = true;
            }
            if (strstr(argv[i], "-a") != NULL)
            {
                if (i + 1 < argc)
                    *nombreArchivo = argv[i + 1];
                *hayArchivo = true;
            }
            if (strstr(argv[i], "-n") != NULL)
            {
                if (i + 1 < argc)
                    *nProcesos = atoi(argv[i + 1]);
            }
            if (strstr(argv[i], "-p") != NULL)
            {
                if (i + 1 < argc)
                    *porcentaje = atof(argv[i + 1]) / 100;
                if (*porcentaje >= 0 && *porcentaje <= 1)
                    *hayPorcentaje = true;
            }
        }
    }
    if(*nProcesos <= ((*filas)*(*columnas)) && *nProcesos > 0)
      *hayNProcesos = true;
}
//funcion que asigna los trabajos
void asignarTrabajos(recorrido* p1, recorrido* p2, int filas, int columnas, int trabajoProcesos)
{
            p1->fInicial = p2->fFinal;
            p1->cInicial = p2->cFinal+1;
            if(p1->cInicial >= columnas)
            {
                p1->fInicial+= p1->cInicial/columnas;
                p1->cInicial = p1->cInicial%columnas;
            }
            p1->fFinal = p1->fInicial + trabajoProcesos / columnas;
            p1->cFinal = p1->cInicial + trabajoProcesos % columnas;
            if(p1->cFinal >= columnas)
            {
                p1->fFinal+= p1->cFinal/columnas;
                p1->cFinal = p1->cFinal%columnas;
            }
            if(p1->fFinal >= filas)
            {
               p1->fFinal = filas-1;
               p1->cFinal = columnas-1;
            }

            //p2 arranca desde donde p1 dejó
            p2->cInicial = p1->cFinal+1;
            p2->fInicial = p1->fFinal;
            if(p2->cInicial >= columnas)
            {
                p2->fInicial+= p2->cInicial/columnas;
                p2->cInicial = p2->cInicial%columnas;
            }
            p2->fFinal = p2->fInicial + trabajoProcesos / columnas;
            p2->cFinal = p2->cInicial + trabajoProcesos % columnas;
            if(p2->cFinal >= columnas)
            {
                p2->fFinal+= p2->cFinal/columnas;
                p2->cFinal = p2->cFinal%columnas;
            }
            if(p2->fFinal >= filas)
            {
               p2->fFinal = filas-1;
               p2->cFinal = columnas-1;
            }
}

#endif
