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
/*
Función: buscarUno
Parámetros de Entrada: apuntador a void que almacena la estructura con los datos de los hilos
Valor de salida: no tiene
Descripción: Busca los unos en la matriz
*/

void *buscarUno(void *arg) {
    struct InfoHilos *datos = (struct InfoHilos *)arg;
    int contador = 0;

    for (int i = datos->inicio; i < datos->final; i++) {
        for (int j = 0; j < datos->columnas; j++) {
            if (datos->matriz[i][j] == 1) {
                contador++;
            }
        }
    }

    *(datos->contador) = contador;
    pthread_exit(NULL);
}

/*
Función: CheckParameters
Parámetros de Entrada: arreglo de apuntadores a char, que almacena los parametros de entrada
Valor de salida: no tiene
Descripción: Verifica la posicion de los parametros y los carga a sus respectivas variables globales
*/

void CheckParameters(char *parameters[]){
    int numC, numF, numH, porc;
    if(parameters[1][1] == 'f'){
        num_filas = atoi(parameters[2]);
    }
    else if(parameters[1][1] == 'c'){
        num_columnas = atoi(parameters[2]);
    }
    else if(parameters[1][1] == 'a'){
        strcpy(archivo, parameters[2]);
    }
    else if(parameters[1][1] == 'n'){
        num_hilos = atoi(parameters[2]);
    }
    else if(parameters[1][1] == 'p'){
        porcentaje = atoi(parameters[2]);
    }
    else{
        printf("Error: Argumento inválido. El programa debe invocarse de la siguiente forma:\n");
        printf("$ ./pdispersa -f [numero de filas] -c [numero de columnas] -a [ruta archivo] -n [numero de procesos] -p [porcentaje]\n");
        exit(1);
    }

    if(parameters[3][1] == 'f'){
        num_filas = atoi(parameters[4]);
    }
    else if(parameters[3][1] == 'c'){
        num_columnas = atoi(parameters[4]);
    }
    else if(parameters[3][1] == 'a'){
        strcpy(archivo, parameters[4]);
    }
    else if(parameters[3][1] == 'n'){
        num_hilos = atoi(parameters[4]);
    }
    else if(parameters[3][1] == 'p'){
        porcentaje = atoi(parameters[4]);
    }
    else{
        printf("Error: Argumento inválido. El programa debe invocarse de la siguiente forma:\n");
        printf("$ ./pdispersa -f [numero de filas] -c [numero de columnas] -a [ruta archivo] -n [numero de procesos] -p [porcentaje]\n");
        exit(1);
    }

    if(parameters[5][1] == 'f'){
        num_filas = atoi(parameters[6]);
    }
    else if(parameters[5][1] == 'c'){
        num_columnas = atoi(parameters[6]);
    }
    else if(parameters[5][1] == 'a'){
        strcpy(archivo, parameters[6]);
    }
    else if(parameters[5][1] == 'n'){
        num_hilos = atoi(parameters[6]);
    }
    else if(parameters[5][1] == 'p'){
        porcentaje = atoi(parameters[6]);
    }
    else{
        printf("Error: Argumento inválido. El programa debe invocarse de la siguiente forma:\n");
        printf("$ ./pdispersa -f [numero de filas] -c [numero de columnas] -a [ruta archivo] -n [numero de procesos] -p [porcentaje]\n");
        exit(1);
    }

    if(parameters[7][1] == 'f'){
        num_filas = atoi(parameters[8]);
    }
    else if(parameters[7][1] == 'c'){
        num_columnas = atoi(parameters[8]);
    }
    else if(parameters[7][1] == 'a'){
        strcpy(archivo, parameters[8]);
    }
    else if(parameters[7][1] == 'n'){
        num_hilos = atoi(parameters[8]);
    }
    else if(parameters[7][1] == 'p'){
        porcentaje = atoi(parameters[8]);
    }
    else{
        printf("Error: Argumento inválido. El programa debe invocarse de la siguiente forma:\n");
        printf("$ ./pdispersa -f [numero de filas] -c [numero de columnas] -a [ruta archivo] -n [numero de procesos] -p [porcentaje]\n");
        exit(1);
    }

    if(parameters[9][1] == 'f'){
        num_filas = atoi(parameters[10]);
    }
    else if(parameters[9][1] == 'c'){
        num_columnas = atoi(parameters[10]);
    }
    else if(parameters[9][1] == 'a'){
        strcpy(archivo, parameters[10]);
    }
    else if(parameters[9][1] == 'n'){
        num_hilos = atoi(parameters[10]);
    }
    else if(parameters[9][1] == 'p'){
        porcentaje = atoi(parameters[10]);
    }
    else{
        printf("Error: Argumento inválido. El programa debe invocarse de la siguiente forma:\n");
        printf("$ ./pdispersa -f [numero de filas] -c [numero de columnas] -a [ruta archivo] -n [numero de procesos] -p [porcentaje]\n");
        exit(1);
    }

    if(num_filas <= 0 || num_columnas <= 0 || num_hilos <= 0 || porcentaje <= 0 || porcentaje > 100 || num_hilos > num_filas){
        printf("Error: Argumento inválido. El programa debe invocarse de la siguiente forma:\n");
        printf("$ ./pdispersa -f [numero de filas] -c [numero de columnas] -a [ruta archivo] -n [numero de procesos] -p [porcentaje]\n");
        printf("Adicionalmente los valores de los argumentos deben ser positivos, y el porcentaje debe ser menor o igual a 100\n");
        exit(1);
    }
}
// Función para iniciar la medición del tiempo
void iniciar_tiempo(struct timeval *inicio) {
    gettimeofday(inicio, NULL);
}

// Función para detener la medición del tiempo y calcular la duración
double detener_tiempo(struct timeval *inicio) {
    struct timeval fin;
    gettimeofday(&fin, NULL);

    double segundos = (double)(fin.tv_sec - inicio->tv_sec) + (double)(fin.tv_usec - inicio->tv_usec) / 1000000.0;
    return segundos;
}
//funcion para cargar los datos
void cargaDatos(int** matriz, int filas, int columnas, FILE *file, bool *valido)
{
    for (int i = 0; i < filas; i++) {
        for (int j = 0; j < columnas; j++) {
            if(feof(file))
            {
              *valido = false;
              return;
            }
            fscanf(file, "%d", &matriz[i][j]);
        }
    }
    *valido = true;
}
//funcion para reservar matriz
/*int** reservarMatriz(int** matriz, int filas, int columnas)
{
       //reservo espacios de memoria para la matriz, esto mediante el uso de malloc (malloc reserva N bytes consecutivos en la memoria)
        matriz = (int **)malloc(filas * sizeof(int *));
        for (int i = 0; i < filas; i++)
            matriz[i] = (int *)malloc(columnas * sizeof(int));
        return matriz;
}*/
int** reservarMatriz(int** matriz, int filas, int columnas)
{
       //reservo espacios de memoria para la matriz, esto mediante el uso de malloc (malloc reserva N bytes consecutivos en la memoria)
        matriz = (int **)malloc(filas * sizeof(int *));
        for (int i = 0; i < filas; i++)
            matriz[i] = (int *)malloc(columnas * sizeof(int));
        return matriz;
}

// Función para liberar la memoria de la matriz
void liberarMatriz(int **matriz, int filas, int columnas)
{
 if (matriz != NULL) {
        //Se libera el espacio reservado
        for (int i = 0; i < filas; i++) {
            free(matriz[i]);
        }
        free(matriz);
    }

}
#endif
