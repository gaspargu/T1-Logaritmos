#include <stdio.h>
#include <stdlib.h>

// Estructura de un rectangulo son dos pares de puntos (x1,y1) y (x2,y2)
typedef struct {
    int x1, y1, x2, y2;
} Rect;

// Estructura que representa un nodo del Rtree
typedef struct node {
    int num_keys;  // numero de claves (e hijos) del nodo
    Rect *keys;
    struct node **childs;
} Node;

// estructura para almacenar un Rtree
typedef struct {
    Node *root;
} RTree;

int division_techo(int x, int y);
void printRect(Rect rect);
void printArrayOfRect(Rect *arr, int n);
int intersect(Rect r1, Rect r2);
Rect *sortByX(Rect *arr, int n);
int randInt(int min, int max);
Rect *Rset(int n);
Rect *Qset();
Rect MBR(Rect *array, int n);
Node *createRTree(Node *node, int n, int M, int primera);
void printRTree(Node *node);


