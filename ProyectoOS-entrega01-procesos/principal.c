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
#include <sys/time.h>
#include "modulo.h"
#define ARCH1 "archivo1.txt"
#define ARCH2 "archivo2.txt"

int main(int argc, char *argv[])
{
    struct timeval inicio;
    iniciar_tiempo(&inicio);
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
    comprobarDatos(argc, argv, &hayFilas, &hayColumnas, &hayArchivo, &hayPorcentaje, &hayNProcesos, &filas, &columnas, &porcentaje, &nProcesos, &nombreArchivo);
      //si las banderas booleanas son true, significa que el usuario ha ingresado todos los datos necesarios de manera correcta
    if (hayFilas && hayColumnas && hayArchivo && hayNProcesos && hayPorcentaje)
    {
       matriz = reservarMatriz(matriz, filas, columnas);

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
        imprimeMatriz(matriz, filas, columnas);

        //Se crean los respectivos procesos siempre y cuando aun no llegue al nProcesos
        while(auxNProcesos < nProcesos)
        {
            //asigno valores a las structs de tipo recorrido p1 y p2
            asignarTrabajos(&p1, &p2, filas, columnas, trabajoProcesos);
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
    freeMemory(matriz,filas,pipe1);
    detener_tiempo(&inicio);
    return 0;
}

  
