#include "ordenamiento.h"
#include "rtree.h"


void writeLeafs(char *file_name, Rect *array, int n, int M) {
     FILE *file = fopen(file_name, "wb");
     Rect *p = array;
     long null = -1;
     // escribe rectangulos
     for (int i=0; i<n/M; i++) {
          fwrite(p, sizeof(Rect), M, file); 
          p+=M;
          // direcciones a los hijos de una hoja son -1 (para representar que no existe)
          for (int j=0; j<M; j++) {
               fwrite(&null, sizeof(long), 1, file);
          }
     }

     // rellena los que falte con -1 para completar el bloque de tamaño M
     if (n%M) {
          fwrite(p, sizeof(Rect), n%M, file); 
          for (int i=0; i< 2*(M-n%M); i++) {
               fwrite(&null, sizeof(long), 1, file);
          }
          for (int j=0; j<M; j++) {
               fwrite(&null, sizeof(long), 1, file);
          }
     }

     fclose(file);
}

void writeNodes(char *file_name, Rect *array, int n, int M, long offset) {
     FILE *file = fopen(file_name, "ab");
     int sobrantes = n%M;
     int techo = division_techo(n,M);
     Rect *padres = malloc(techo*sizeof(Rect));
     Rect *p = array; //puntero que recorre el arreglo de rectangulos
     Rect *pp = padres;
     long null = -1;

     if (techo==1) {
          return;
     }

     // Generar padres mediante MBR
     for (int i=0; i<n/M; i++) {
          Rect r[M];
          for (int j=0; j<M; j++) {
               r[j] = *p;
               p++;
          }
          padres[i] = MBR(r,M);
     }

     if (sobrantes) {
          Rect r[sobrantes];
          for (int j=0; j<sobrantes; j++) {
               r[j] = *p;
               p++;
          }
          padres[techo-1] = MBR(r,sobrantes);
     }

     // Escribir padres
     for (int i=0; i<techo/M; i++) {
          fwrite(pp, sizeof(Rect), M, file); 
          pp+=M;
          for (int j=0; j<M; j++) {
               fwrite(&offset, sizeof(long), 1, file);
               offset += 6*M;
          }
     }

     if (techo%M) {
          fwrite(pp, sizeof(Rect), n%M, file); 
          for (int i=0; i< 2*(M-techo%M); i++) {
               fwrite(&null, sizeof(long), 1, file);
          }
          for (int i=0; i<techo%M; i++) {
               fwrite(&offset, sizeof(long), 1, file);
               offset += 6*M;
          }
          for (int i=0; i<(M-techo%M); i++) {
               fwrite(&null, sizeof(long), 1, file);
          }
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
     int entero;
     while (fread(&entero, sizeof(int), 1, file) == 1) {
          printf("%d,", entero);
     }
     printf("\n");
     fclose(file);
}

void buscar_recursivo(FILE *file, int M, Res *res, Rect C, long pos) {
     fseek(file,pos,SEEK_SET);
     
     Rect rectangulos[M];
     long childs[M];
     fread(&rectangulos, M*sizeof(Rect), 1, file);
     fread(&childs, M*sizeof(long), 1, file);
     //printArrayOfRect(rectangulos, M);
     //printArrayOfLong(childs, M);
     res->accesos++;

     for (int i=0; i<M; i++) {
          if (childs[0]==-1) {
               if (intersect(rectangulos[i],C)) {
                    res->array[res->n] = rectangulos[i];
                    res->n++;
               } 
          }
          else {
               if (intersect(rectangulos[i],C)) {
                    buscar_recursivo(file, M, res, C, childs[i]*sizeof(int)); 
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
     
     // posiciona el puntero en la raiz
     fseek(file,0,SEEK_END);
     long size_file = ftell(file);
     long position_root = size_file - 6*sizeof(int)*M;
     buscar_recursivo(file, M, res, C, position_root);
     fclose(file);

     return res;
}




