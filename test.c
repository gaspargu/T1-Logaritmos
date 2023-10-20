#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ordenamiento.h"
#include "rtree.h"
#include "files.h"

int main() {
    // ejemplo 1
    Rect r[5] = {{1,1,2,2}, {3,1,4,3}, {3,2,6,4}, {6,1,7,2}, {7,1,8,2}}; 
    constructRTreeBin("archivo",r,5,2);
    readFile("archivo");

    return 0;
}