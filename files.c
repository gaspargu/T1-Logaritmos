#include "ordenamiento.h"
#include "rtree.h"


void writeLeafs(char *file_name, Rect *array, int n, int M) {
     FILE *file = fopen(file_name, "wb");

     // escribe rectangulos
     for (int i=0; i<n; i++) {
          fwrite(&array[i], sizeof(Rect), 1, file);
     }

     int null_rect[] = {-1,-1,-1,-1};
     int sobrantes = n%M; 
     for (int i=0; i<sobrantes; i++) {
          fwrite(&null_rect, sizeof(Rect), 1, file);
     }

     // escribe la direccion de sus hijos, como son las hojas no existen, la direccion es -1
     long null = -1;
     for (int i=0; i<n+sobrantes; i++) {
          fwrite(&null, sizeof(long), 1, file);
     }

     fclose(file);
}

void writeNodes(char *file_name, Rect *array, int n, int M, long offset) {
     FILE *file = fopen(file_name, "ab");
     int sobrantes = n%M;
     int techo = division_techo(n,M);
     Rect *padres = malloc(techo*sizeof(Rect));
     Rect *p = array; //puntero que recorre el arreglo de rectangulos

     if (techo==1) {
          return;
     }

     // Escribo rectangulos
     for (int i=0; i<n/M; i++) {
          Rect r[M];
          for (int j=0; j<M; j++) {
               r[j] = *p;
               p++;
          }
          padres[i] = MBR(r,M);
          fwrite(&padres[i], 4*sizeof(int), 1, file);
     }

     if (sobrantes) {
          Rect r[sobrantes];
          for (int j=0; j<sobrantes; j++) {
               r[j] = *p;
               p++;
          }
          padres[techo-1] = MBR(r,sobrantes);
          fwrite(&padres[techo-1], 4*sizeof(int), 1, file);
     }

     // rectangulos de relleno
     int null_rect[] = {-1,-1,-1,-1}; 
     for (int i=0; i<techo%M; i++) {
          fwrite(&null_rect, 4*sizeof(int), 1, file);
     }

     // Escribo direcciones hijos
     for (int i=0; i<n/M; i++) {
          fwrite(&offset, 2*sizeof(int), 1, file);
          offset += 4*M;
     }

     if (sobrantes) {
          fwrite(&offset, 2*sizeof(int), 1, file);
          offset += 4*M;
     }

     long null = -1;
     for (int i=0; i<techo%M; i++) {
          fwrite(&null, 2*sizeof(int), 1, file);
     }

     offset += 2*techo*M; // desplaza el offset lo que se ocupo con las direcciones

     fclose(file);

     writeNodes(file_name, padres, techo, M, offset);


}

void constructRTreeBin(char *file_name, Rect *array, int n, int M) {
     writeLeafs(file_name, array, n, M);
     writeNodes(file_name, array, n, M, 0);
}

void readFile(char *file_name) {
     FILE *file = fopen(file_name, "rb");
    int entero;
    while (fread(&entero, sizeof(int), 1, file) == 1) {
        printf("%d,", entero);
    }
    printf("\n");
    fclose(file);
}

void buscar_recursivo(FILE *file, int M, Rect *p, Res *res, Rect C, long pos) {

     fseek(file,pos,SEEK_SET);
     Rect r;
     long child;
     for (int i=0; i<M; i++) {
          fread(&r, 4*sizeof(int), 1, file);
          fread(&child, 2*sizeof(int), 1, file);
          printRect(r);
          if (intersect(r,C)) {
               if (child == -1) {
                    printRect(r);
                    *p = r;
                    p++;  
                    res->n = res->n;

               } else {
                    buscar_recursivo(file, M, p, res, C, child*sizeof(int));
               }
          }
     }
}

Res *buscar(char *file_name, int n, int M, Rect C) {
     FILE *file = fopen(file_name, "rb");

     Res *res = malloc(sizeof(Res));
     res->array = malloc(n*sizeof(Rect));
     res->n = 0;
     res->accesos = 0;
     
     Rect *p = res->array;  // puntero que rellenara con los resultados
     // posiciona el puntero en la raiz
     fseek(file,0,SEEK_END);
     long size_file = ftell(file);
     long position_root = size_file - 6*sizeof(int)*M;

     buscar_recursivo(file, M, p, res, C, position_root);

     return res;
}




