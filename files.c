#include "ordenamiento.h"
#include "rtree.h"


void writeLeafs(char *file_name, Rect *array, int n, int M) {
     FILE *file = fopen(file_name, "wb");
     int leaf_child = -1;
     for (int i=0; i<n; i++) {
          fwrite(&array[i], sizeof(Rect), 1, file);
          fwrite(&leaf_child, sizeof(int), 1, file);
     }

     int null[] = {-2,-2,-2,-2,-2}; 
     int sobrantes = n%M; 
     for (int i=0; i<sobrantes; i++) {
          fwrite(&null, 5*sizeof(int), 1, file);
     }
     fclose(file);
}

void writeNodes(char *file_name, Rect *array, int n, int M, int offset) {
     FILE *file = fopen(file_name, "ab");
     int sobrantes = n%M;
     int techo = division_techo(n,M);
     Rect *padres = malloc(techo*sizeof(Rect));
     Rect *p = array; //puntero que recorre el arreglo de rectangulos

     if (techo==1) {
          return;
     }

     for (int i=0; i<n/M; i++) {
          Rect r[M];
          for (int j=0; j<M; j++) {
               r[j] = *p;
               p++;
          }
          padres[i] = MBR(r,M);
          fwrite(&padres[i], 4*sizeof(int), 1, file);
          fwrite(&offset, sizeof(int), 1, file);
          offset += M*5;
     }

     if (sobrantes) {
          Rect r[sobrantes];
          for (int j=0; j<sobrantes; j++) {
               r[j] = *p;
               p++;
          }
          padres[techo-1] = MBR(r,sobrantes);
          fwrite(&padres[techo-1], 4*sizeof(int), 1, file);
          fwrite(&offset, sizeof(int), 1, file);
          offset += M*5;
     }

     int null[] = {-2,-2,-2,-2,-2}; 
     for (int i=0; i<techo%M; i++) {
          fwrite(&null, 5*sizeof(int), 1, file);
     }

     fclose(file);

     writeNodes(file_name, padres, techo, M, offset);


}

void constructRTreeBin(char *file_name, Rect *array, int n, int M) {
     writeLeafs(file_name, array, n, M);
     writeNodes(file_name, array, n, M, 0);
}

void readFile(char *file_name) {
     FILE *file = fopen(file_name, "rb");
     int number;
     while (fread(&number, sizeof(int), 1, file) == 1) {
        printf("%i", number);
     } 
     printf("\n");
     fclose(file);
}

Rect *buscar(char *file_name, int M) {
     
}


