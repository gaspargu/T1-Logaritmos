# T1-Logaritmos

Para compilar y ejecutar los tests:

Este test comprueba que se crea un rtree en el archivo bineario, luego comprueba si funciona buscar en él.
Compilar: gcc -o test ordenamiento.c rtree.c test.c files.c -lm
Ejecutar: ./test

Este test comprueba funciones de ordenamiento, de interseccion de rectangulos y la que encuentra el MBR.
Compliar test1: gcc -o test1 ordenamiento.c rtree.c test1.c files.c -lm
Ejecutar: ./test1