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
void cargaDatos(FILE *arch, int **matriz, int filas, int columnas);

// Función para contar los 0's en una sección de la matriz
int contarZeros(int **matriz, recorrido rango, int columnas);
