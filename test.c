#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ordenamiento.h"
#include "rtree.h"

int main() {

    // test intersect
    Rect r1 = {1,1,2,2};
    Rect r2 = {3,1,4,3};
    Rect r3 = {3,2,6,4};
    Rect r4 = {6,1,7,2};
    Rect r5 = {7,1,8,2};
    Rect r6 = {8,1,9,4};
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

    // test MBR
    Rect r[] = {r1,r2,r3};
    Rect mbr = MBR(r, 3);
    printRect(mbr);

    // test crear RTree
    Node *n=malloc(sizeof(Node));
    n->num_keys = 6;
    Rect rectangle_array[] = {r1,r2,r3,r4,r5,r6};
    n->keys = malloc(6 * sizeof(Rect));
    memcpy(n->keys, rectangle_array, 6 * sizeof(Rect));
    n->childs = malloc(6 * sizeof(Node *));
    for (int i=0; i<6; i++) {
        n->childs[i] = NULL;
    }
    Node *n_rtree = createRTree(n, n->num_keys, 2, 1);

    printRTree(n_rtree);

    return 0;
}