#include <stdio.h>
#include <stdlib.h>

int particionar(double *a, int *id, int imin, int imax);

void intercambiar(double *a, int *id, int i, int j) {
    double a_aux = a[i];
    int id_aux = id[i];
    a[i] = a[j];
    id[i] = id[j];
    a[j] = a_aux;
    id[j] = id_aux;
}

void quicksort(double *a, int *id, int imin, int imax) {
    if (imin>=imax)
        return;
    int k= particionar(a, id, imin, imax);
    quicksort(a, id, imin, k-1);
    quicksort(a, id, k+1, imax);
}

int particionar(double *a, int *id, int imin, int imax) {
    int ipiv= imin;
    int k= imin;
    int j= k+1;
    while (j<=imax) {
      if (a[j]<a[ipiv] ) {
        k= k+1;
        intercambiar(a, id, k, j);
      }
      j= j+1;
    }
    intercambiar(a, id, k, ipiv);
    return k;
  }

void printDoubleArray(double *x, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%f ", x[i]);
    }
    printf("]\n");
}

void printIntArray(int *x, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        printf("%i ", x[i]);
    }
    printf("]\n");
}