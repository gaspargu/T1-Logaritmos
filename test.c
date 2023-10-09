#include <stdio.h>
#include <stdlib.h>

#include "ordenamiento.h"
#include "rtree.h"

int main() {

    // test intersect
    Rect r1 = {1,1,3,3};
    Rect r2 = {2,2,5,5};
    Rect r3 = {6,2,8,5};
    if (intersect(r1,r2) && !intersect(r3,r2)) {
        printf("Test intersect aprobado\n");
    }

    // test quicksort
    double a[] = {2,1.0,3.0,2.3,1.1,9.,10.};
    int id[] = {0,1,2,3,4,5,6};

    printf("Arreglo sin ordenar: ");
    printDoubleArray(a, 7);
    printf("Indices del arreglo sin ordenar: ");
    printIntArray(id, 7);
    quicksort(a,id,0,6);
    printf("Arreglo ordenado: ");
    printDoubleArray(a, 7);
    printf("Indices del arreglo ordenado: ");
    printIntArray(id, 7);

    // test ordena rectangulos por coordenada x
    Rect *arr = Rset(4);
    Rect *arr_sort = sortByX(arr, 4);
    printArrayOfRect(arr,4);
    printArrayOfRect(arr_sort,4);
    
    return 0;
}