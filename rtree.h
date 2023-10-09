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

void printRect(Rect rect);
void printArrayOfRect(Rect *arr, int n);
int intersect(Rect r1, Rect r2);
Rect *sortByX(Rect *arr, int n);
int randInt(int min, int max);
Rect *Rset(int n);
Rect *Qset();



