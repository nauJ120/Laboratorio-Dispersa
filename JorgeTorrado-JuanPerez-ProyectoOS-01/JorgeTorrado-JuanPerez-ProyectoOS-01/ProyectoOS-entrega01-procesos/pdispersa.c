/*
=====================================================================
Primer Proyecto Sistemas Operativos Sección de Procesos

Nombres:     	Jorge Eduardo Torrado Forero, Juan Diego Pérez Duarte

Profesor:   	John Corredor Franco

Institución:    Javeriana Bogotá

Fecha:        	Octubre 1 del 2023
======================================================================
*/

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <math.h>
#include "pdispersa.h"
#define ARCH1 "archivo1.txt"
#define ARCH2 "archivo2.txt"

int main(int argc, char *argv[])
{
    //declaro las variables respectivas que se emplean a lo largo de este programa
    int **matriz;
    int *pipe1 = (int*) malloc(2*sizeof(int));
    bool hayFilas = false;
    bool hayColumnas = false;
    bool hayArchivo = false;
    bool hayNProcesos = false;
    bool hayPorcentaje = false;
    int pid1;
    int pid2;
    recorrido p1;
    p1.fInicial = 0;
    p1.cInicial = 0;
    p1.fFinal = 0;
    p1.cFinal = -1;
    recorrido p2;
    p2.fInicial = 0;
    p2.cInicial = 0;
    p2.fFinal = 0;
    p2.cFinal = -1;
    char *nombreArchivo;
    char archivo1[] = "sumaP1.txt";
    char archivo2[] = "sumaP2.txt";
    int filas;
    int columnas;
    float porcentaje;
    int total;
    int trabajoProcesos;
    int nPorcentaje;
    int contador = 0;
    int nProcesos;
    int auxNProcesos = 0;
    FILE *arch;
    FILE *arch1;
    FILE *arch2;
    //si no me ingresa la cantidad adecuada de parámetros por consola, mato el programa e informo al usuario que le faltaron parámetros
    if (argc != 11)
    {
        printf("\nError, solo se aceptan 10 parametros de entrada, ni mas ni menos, intente de nuevo\n\nEjemplo de sintaxis para ejecutar el comando:\n\n./ejecutable -f cantidad_de_filas -c cantidad_de_columnas -n numero_de_procesos -a nombre_archivo -p porcentaje(numero de 0 a 100)\n\n");
        return -1;
    }
    //leo los argumentos que el usuario pasa por consola para extraer de estos los datos relevantes como filas, columnas, nombre del archivo, porcentaje de 0's, etc
    for (int i = 1; i < argc; i++)
    {
        if (argv[i][0] == '-')
        {
            if (strstr(argv[i], "-f") != NULL)
            {
                if (i + 1 < argc)
                    filas = atoi(argv[i + 1]);
                if(filas >= 0)
                  hayFilas = true;
            }
            if (strstr(argv[i], "-c") != NULL)
            {
                if (i + 1 < argc)
                    columnas = atoi(argv[i + 1]);
                if(columnas >= 0)
                  hayColumnas = true;
            }
            if (strstr(argv[i], "-a") != NULL)
            {
                if (i + 1 < argc)
                    nombreArchivo = argv[i + 1];
                hayArchivo = true;
            }
            if (strstr(argv[i], "-n") != NULL)
            {
                if (i + 1 < argc)
                    nProcesos = atoi(argv[i + 1]);
            }
            if (strstr(argv[i], "-p") != NULL)
            {
                if (i + 1 < argc)
                    porcentaje = atof(argv[i + 1]) / 100;
                if (porcentaje >= 0 && porcentaje <= 1)
                    hayPorcentaje = true;
            }
        }
    }
    if(nProcesos <= (filas*columnas) && nProcesos > 0)
      hayNProcesos = true;
      //si las banderas booleanas son true, significa que el usuario ha ingresado todos los datos necesarios de manera correcta
    if (hayFilas && hayColumnas && hayArchivo && hayNProcesos && hayPorcentaje)
    {
       //reservo espacios de memoria para la matriz, esto mediante el uso de malloc (malloc reserva N bytes consecutivos en la memoria)
        matriz = (int **)malloc(filas * sizeof(int *));
        for (int i = 0; i < filas; i++)
            matriz[i] = (int *)malloc(columnas * sizeof(int));

        arch = fopen(nombreArchivo, "r");

        trabajoProcesos = ((filas * columnas) / nProcesos) + 1;
        //si no se puede abrir el archivo, mato el programa y notifico de esto al usuario
        if (arch == NULL)
        {
            printf("\nError al intentar abrir el archivo, verifique que el nombre y/o ruta sean adecuados e intente de nuevo\n\n");
            return -1;
        }
        //si el programa llega hasta esta línea, significa que hay archivo, por ende lo leo al invocar la función cargaDatos
        cargaDatos(arch, matriz, filas, columnas);
        fclose(arch);
        //le muestro al usuario la matriz que se extrajo, con el fin de que el usuario pueda hacer un mejor seguimiento de lo que se realiza en el programa
        printf("\n\nEsta es la matriz que se extrajo del archivo:\n\n");
        imprimeMatriz(matriz, filas, columnas);

        //Se crean los respectivos procesos siempre y cuando aun no llegue al nProcesos
        while(auxNProcesos < nProcesos)
        {
            //asigno valores a las structs de tipo recorrido p1 y p2
            p1.fInicial = p2.fFinal;
            p1.cInicial = p2.cFinal+1;
            if(p1.cInicial >= columnas)
            {
                p1.fInicial+= p1.cInicial/columnas;
                p1.cInicial = p1.cInicial%columnas;
            }
            p1.fFinal = p1.fInicial + trabajoProcesos / columnas;
            p1.cFinal = p1.cInicial + trabajoProcesos % columnas;
            if(p1.cFinal >= columnas)
            {
                p1.fFinal+= p1.cFinal/columnas;
                p1.cFinal = p1.cFinal%columnas;
            }
            if(p1.fFinal >= filas)
            {
               p1.fFinal = filas-1;
               p1.cFinal = columnas-1;
            }

            //p2 arranca desde donde p1 dejó
            p2.cInicial = p1.cFinal+1;
            p2.fInicial = p1.fFinal;
            if(p2.cInicial >= columnas)
            {
                p2.fInicial+= p2.cInicial/columnas;
                p2.cInicial = p2.cInicial%columnas;
            }
            p2.fFinal = p2.fInicial + trabajoProcesos / columnas;
            p2.cFinal = p2.cInicial + trabajoProcesos % columnas;
            if(p2.cFinal >= columnas)
            {
                p2.fFinal+= p2.cFinal/columnas;
                p2.cFinal = p2.cFinal%columnas;
            }
            if(p2.fFinal >= filas)
            {
               p2.fFinal = filas-1;
               p2.cFinal = columnas-1;
            }
            //creo el pipe
            pipe(pipe1);
            // Crear proceso hijo
            pid1 = fork();

            if (pid1 == 0)
            {
                //bandera
                int bandera = 1;
                // Proceso hijo
                int count = contarZeros(matriz, p1, columnas);
                if(count >= 255)
                {
                    //abro el archivo y escribo en él
                    arch1 = fopen(archivo1, "w");
                    fwrite(&count,sizeof(int),1, arch1);
                    fclose(arch1);
                    //count se vuelve 255
                    count = 255;
                }
                close(pipe1[0]);
                write(pipe1[1],&bandera,sizeof(int));
                close(pipe1[1]);
                exit(count);
            }
            else if (pid1 > 0)
            {
                pid2 = fork();

                if (pid2 == 0)
                {
                    int bandera;
                    close(pipe1[1]);
                    read(pipe1[0], &bandera, sizeof(int));
                    close(pipe1[0]);
                    int count = 0;
                    if(auxNProcesos + bandera < nProcesos)
                    {
                        count = contarZeros(matriz, p2, columnas);
                        if(count >= 255)
                        {
                            //abro el archivo y escribo en él
                            arch2 = fopen(archivo2, "w");
                            fwrite(&count,sizeof(int),1, arch2);
                            fclose(arch2);
                            //count se vuelve 255
                            count = 255;
                        }
                    }
                    exit(count);
                }
                else if (pid2 > 0)
                {
                    // Proceso padre
                    int status1, status2;
                    int resultadoParcial;
                    int sumaP1;
                    int sumaP2;
                    auxNProcesos+=2;
                    waitpid(pid1, &status1, 0);
                    waitpid(pid2, &status2, 0);

                    sumaP1 = WEXITSTATUS(status1);
                    sumaP2 = WEXITSTATUS(status2);
                    if(sumaP1 == 255)
                    {
                        arch1 = fopen(archivo1, "r");
                        fread(&sumaP1, sizeof(int),1, arch1);
                        fclose(arch1);
                    }
                    if(sumaP2 == 255)
                    {
                        arch2 = fopen(archivo2, "r");
                        fread(&sumaP2, sizeof(int),1, arch2);
                        fclose(arch2);
                    }
                    resultadoParcial = sumaP1 + sumaP2;

                    contador += resultadoParcial;
                }
                else
                {
                    perror("Error en fork");
                    exit(1);
                }
            }
            else
            {
                perror("Error en fork");
                exit(1);
            }
        }
        //ya tengo la cantidad de 0's que hay en la matriz, ahora divido esto en la cantidad de casillas de la matriz (filas * columnas) para hallar el porcentaje de 0's y comparar con el parámetro porcentaje
        total = filas * columnas;
        float resultadoPorcentaje = (float)contador / total;

        printf("\n\nEl porcentaje de 0's en la matriz dada es: %.2f por ciento\n", resultadoPorcentaje * 100);

        //comparo con el parámetro porcentaje y le digo al usuario si la matriz es o no dispersa de acuerdo a sus condiciones
        if(resultadoPorcentaje >= porcentaje)
        {
           printf("\n\nPor ende, la matriz es dispersa de acuerdo a las condiciones impuestas\n\n");
        }
        else
        {
            printf("\n\nPor ende, la matriz no es dispersa de acuerdo a las condiciones impuestas\n\n");
        }
    }
    else
    {
    //este else se ejecuta si almenos 1 bandera booleana esta mal, lo que indica que el usuario ha ingresado mal los parámetros, por ende mato el programa y notifico de esto al usuario
        printf("\nError en los argumentos de entrada, verifique y vuelva a intentarlo.\nPosdata: recuerde que el porcentaje debe estar entre 0 y 100 y el numero de procesos debe ser mayor a 0 y menor o igual al numero total de casillas de la matriz\n\n");
    }

    return 0;
}
//imprimeMatriz muestra por pantalla al usuario la matriz que se extrajo del archivo
void imprimeMatriz(int **matriz, int filas, int columnas)
{
   for(int i = 0; i < filas; i++)
   {
    for(int j = 0; j < columnas; j++)
    {
        printf("%d ",matriz[i][j]);
    }
    printf("\n\n");
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
  
