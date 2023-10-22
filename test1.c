#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ordenamiento.h"
#include "rtree.h"
#include "files.h"

int main() {

    // test intersect
    Rect r1 = {1,1,2,2};
    Rect r2 = {3,1,4,3};
    Rect r3 = {3,2,6,4};
    Rect r4 = {6,1,7,2};
    Rect r5 = {7,1,8,2};
    Rect r6 = {8,1,9,4};
    if (intersect(r2,r3) && !intersect(r1,r2)) {
        printf("Test interseccion de rectangulos aprobado.\n\n");
    }


    // test ordena rectangulos por coordenada x
    Rect *arr = Rset(4);
    Rect *arr_sort = sortByX(arr, 4);
    printf("Arreglo de rectangulos desordenados:\n");
    printArrayOfRect(arr,4);
    printf("Ordenado por coordenada x:\n");
    printArrayOfRect(arr_sort,4);
    printf("\n");

    // test ordena rectangulos por coordenada y
    Rect *arr_y = Rset(4);
    Rect *arr_sort_y = sortByY(arr_y, 4);
    printf("Arreglo de rectangulos desordenados:\n");
    printArrayOfRect(arr_y,4);
    printf("Ordenado por coordenada y:\n");
    printArrayOfRect(arr_sort_y,4);
    printf("\n");


    // test MBR
    Rect r[] = {r1,r2,r3};
    printf("El MBR de : ");
    printArrayOfRect(r,3);
    printf("es ");
    Rect mbr = MBR(r, 3);
    printRect(mbr);


    return 0;
}