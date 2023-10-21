#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ordenamiento.h"
#include "rtree.h"
#include "files.h"

int main() {
    // ejemplo 1
    Rect r[6] = {{1,1,2,2}, {3,1,4,3}, {3,2,6,4}, {6,1,7,2}, {7,1,8,2}, {8,1,9,4}}; 
    constructRTreeBin("archivo",r,6,2);
    readFile("archivo");
    Rect C = {1,1,6,3};
    Res *res;
    res = buscar("archivo", 6, 2, C);
    printArrayOfRect(res->array, res->n);
    return 0;
}