#include <stdio.h>
#include <stdlib.h>

#include "ordenamiento.h"
#include "rtree.h"

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
