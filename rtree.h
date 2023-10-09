#include <stdio.h>
#include <stdlib.h>

// Estructura de un rectangulo son dos pares de puntos (x1,y1) y (x2,y2)
typedef struct {
    int x1, y1, x2, y2;
    double xm, ym;  // centro del rectangulo
} Rect;

// Estructura que representa un nodo del Rtree
typedef struct node {
    Rect *rect;
    struct node *child;
} Node;

// estructura para almacenar un Rtree
typedef struct {
    Node *root;
} RTree;

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