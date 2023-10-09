#include <stdio.h>
#include <stdlib.h>

#include "ordenamiento.h"
#include "rtree.h"

// Función para imprimir un rectangulo
void printRect(Rect rect) {
    printf("(%i,%i,%i,%i)\n", rect.x1, rect.y1, rect.x2, rect.y2);
}

// Función para imprimir un arreglo de rectangulos, tamaño del arreglo n 
void printArrayOfRect(Rect *arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        Rect r = arr[i];
        printf("(%i,%i,%i,%i) ", r.x1, r.y1, r.x2, r.y2);
    }
    printf("]\n");
}

// Entrega 1 si los rectangulos se intersectan, 0 si no
int intersect(Rect r1, Rect r2) {
    if (r1.x2 < r2.x1 || r1.y2 < r2.y1 || r2.x2 < r1.x1 || r2.y2 < r1.y1) {
        return 0;
    } else {
        return 1;
    }
}

