=====================================================================================================================================
Proyecto Matrix Sparse realizado de manera modular

Integrantes: Jorge Eduardo Torrado Forero y Juan Diego Pérez Duarte

Profesor: John Corredor Franco

Fecha: Octubre 24 de 2023

=====================================================================================================================================

El presente proyecto contiene 2 carpetas denominadas:

	ProyectoOS-entrega01-procesos: Esta carpeta tiene el proyecto matrix sparse implementado con modularidad y procesos

	ProyectoOS-entrega01-hilos: Esta carpeta tiene el proyecto matrix sparse implementado con modularidad e hilos


=====================================================================================================================================


Para ejecutar el presente proyecto favor seguir los siguientes pasos:

	1. Descargue o clone el repositorio a su computador local

	2. Ingrese a la carpeta o repositorio que descargó en el paso anterior, via consola de comandos (En sistema operativo Linux o Ubuntu, por favor)

	3. Ingrese por medio de la consola de comandos a la carpeta que desea correr (ya sea la carpeta ProyectoOS-entrega01-procesos o bien la carpeta ProyectoOS-entrega01-hilos)

	4. En consola de comandos ejecute el comando "make"  (sin comillas por favor)

	5. Al realizar el 4to paso, si usted ha hecho todo correctamente le deberá aparecer un archivo ejecutable llamado "principal" en la carpeta donde está parado actualmente

	6. Ejecute el archivo ejecutable de la siguiente manera:
	./principal -f <numero de filas> -c <numero de columnas> -a <nombre archivo> -p <porcentaje de ceros> -n <numero de procesos/hilos que usted desea que el programa cree>




Favor reemplazar del comando anterior:


	<numero de filas> por un número entero mayor a 0 que representa la cantidad de filas que desea leer del archivo

	<numero de columnas> por un número entero que representa la cantidad de columnas que desea leer del archivo

	<nombre archivo> por el nombre del archivo de texto que contiene la matriz a leer, recuerde incluir la extensión .txt

	<porcentaje de ceros> por un número decimal entre 0 y 100, que representa el procentaje de ceros que usted como usuario desea establecer para identificar si la matriz es dispersa o no

	<numero de procesos/hilos que usted desea que el programa cree> por un número entero mayor a 0 que representa la cantidad de proceso o hilos que usted desea que el programa cree
=====================================================================================================================================
