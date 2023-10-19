#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ordenamiento.h"
#include "rtree.h"
#include "files.h"

int main() {
    // ejemplo 1
    Rect r[5] = {{1,1,2,2}, {3,1,4,3}, {3,2,6,4}, {6,1,7,2}, {7,1,8,2}}; 
    constructRTreeBin("hola", r, 5, 2);
    readFile("hola");

    //ejemplo 2
    Rect r2[6] = {{1,1,2,2}, {3,1,4,3}, {3,2,6,4}, {6,1,7,2}, {7,1,8,2}, {8,1,9,4}}; 
    constructRTreeBin("hola", r2, 6, 2);
    readFile("hola");


    return 0;
}