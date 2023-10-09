#include <stdio.h>
#include <stdlib.h>

#include "ordenamiento.h"

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

// Generador de entero aleatorio en el rango [min, max]
int randInt(int min, int max) {
    return (rand() % (max - min + 1)) + min;
}

// Genera el conjunto R de rectángulos 
Rect *Rset(int n) {
    Rect *res = malloc(n * sizeof(Rect));
    for(int i=0; i<n; i++) {
        int x1 = randInt(0, 500000-100);
        int x2 = x1 + randInt(0, 100);
        double xm = (x1+x2)/2.0;
        int y1 = randInt(0, 500000-100);
        double ym = (x1+x2)/2.0;
        int y2 = y1 + randInt(0, 100);

        Rect r = {x1,y1,x2,y2,xm,ym};
        res[i] = r;
    }

    return res;
}


// Genera el conjunto Q de 100 rectangulos 
Rect *Qset() {
    Rect *res = malloc(100 * sizeof(Rect));
    for(int i=0; i<100; i++) {
        int x1 = randInt(0, 500000-100000);
        int x2 = x1 + randInt(0, 100000);
        double xm = (x1+x2)/2.0;
        int y1 = randInt(0, 500000-100000);
        int y2 = y1 + randInt(0, 100000);
        double ym = (y1+y2)/2.0;

        Rect r = {x1,y1,x2,y2,xm,ym};
        res[i] = r;
    }

    return res;
}

// Entrega 1 si los rectangulos se intersectan, 0 si no
int intersect(Rect r1, Rect r2) {
    if (r1.x2 < r2.x1 || r1.y2 < r2.y1 || r2.x2 < r1.x1 || r2.y2 < r1.y1) {
        return 0;
    } else {
        return 1;
    }
}

Rect *sortByX(Rect *arr, int n) {

    // Creamos un arreglo con las coordenadas x del centro de los rectangulos
    double *x = malloc(n*sizeof(double));
    for (int i=0; i<n; i++) {
        x[i] = arr[i].xm;
    }

    // Creamos un arreglo con los indices
    int *id = malloc(n*sizeof(int));
    for (int i=0; i<n; i++) {
        id[i] = i;
    }

    // ordenamos, esto va a dejar en el arreglo id las permutaciones que se hicieron
    quicksort(x, id, 0, n-1);

    // ordenamos los rectangulos usando las permutaciones
    Rect *res = malloc(n*sizeof(Rect));
    for (int i=0; i<n; i++) {
        res[i] = arr[id[i]];
    }

    return res;
}


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