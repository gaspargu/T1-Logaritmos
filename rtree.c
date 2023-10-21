#include <stdio.h>
#include <stdlib.h>

#include "ordenamiento.h"
#include "rtree.h"

// División techo 
int division_techo(int x, int y) {
    return x/y + (x % y != 0);
}

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

// Función para imprimir un arreglo de rectangulos, tamaño del arreglo n 
void printArrayOfLong(long *arr, int n) {
    printf("[");
    for (int i = 0; i < n; i++) {
        long l = arr[i];
        printf("%ld,", l);
    }
    printf("]\n");
}

// Entrega 1 si los rectangulos se intersectan, 0 si no
int intersect(Rect r1, Rect r2) {
    if (r1.x2 < r2.x1 || r1.x1 > r2.x2 || r1.y2 < r2.y1 || r1.y1 > r2.y2) {
        return 0;
    } else {
        return 1;
    }
}

Rect *sortByX(Rect *arr, int n) {

    // Creamos un arreglo con las coordenadas x del centro de los rectangulos
    double *x = malloc(n*sizeof(double));
    for (int i=0; i<n; i++) {
        x[i] = (arr[i].x1 + arr[i].x2)/2.0;
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
        int y1 = randInt(0, 500000-100);
        int y2 = y1 + randInt(0, 100);

        Rect r = {x1,y1,x2,y2};
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
        int y1 = randInt(0, 500000-100000);
        int y2 = y1 + randInt(0, 100000);

        Rect r = {x1,y1,x2,y2};
        res[i] = r;
    }

    return res;
}

// Recibe un arreglo de tamaño n (de rectangulos) y devuelve el MBR que los encapsula
Rect MBR(Rect *array, int n) {
    Rect mbr = {500000,500000,0,0};
    for (int i=0; i<n; i++) {
        if (array[i].x1 < mbr.x1)
            mbr.x1 = array[i].x1;
        if (array[i].y1 < mbr.y1)
            mbr.y1 = array[i].y1;
        if (array[i].x2 > mbr.x2)
            mbr.x2 = array[i].x2;
        if (array[i].y2 > mbr.y2)
            mbr.y2 = array[i].y2;
    }

    return mbr;
}

// crea el RTree a partir de un nodo que tiene como claves a todos los n rectangulos 
// termina formando un RTree con nodos de a lo más M claves
// La funcion se debe llamar con el argumento start=1 (necesario para la recursion)
Node *createRTree(Node *node, int n, int M, int start) { 
    int techo = division_techo(n,M); //numero de nodos 
    int keys_of_last_node = n%M;
    // Caso base: el numero n de rectangulos es menor o igual a M (nodo raíz)
    if (techo == 1) { 
        return node;
    } 

    // Caso recursivo
    else { 
        Rect *p = node->keys; // puntero que recorre el arreglo de rectangulos
        
        Node **q = node->childs; // puntero que recorre el arreglo de hijos
        Node *nodo_padre = malloc(sizeof(Node));
        nodo_padre->num_keys = techo;
        Rect *keys = malloc(techo*sizeof(Rect)); 
        Node **childs = malloc(techo*sizeof(Node *));

        // itera para separar descoponer el nodo en n/M nodos cada uno con M claves y M hijos
        for (int i=0; i<(n/M); i++) {
            Node *n = malloc(sizeof(Node));
            n->num_keys = M;
            Rect *keys_child = malloc(M*sizeof(Rect));
            n->childs = malloc(M*sizeof(Node *));
          
    
            for (int j=0; j<M; j++) {
            keys_child[j] = *p;
            p++;
            if (start) {
                n->childs[j] = NULL;
            } else {
                n->childs[j] = *q;
                q++;                
            }
          }

          n->keys = keys_child;
          keys[i] = MBR(n->keys, n->num_keys);

          childs[i] = n;
        }

        // caso en que la división n/M no es entera se crea el ultimo nodo con menos de M claves
        if (keys_of_last_node) {
            Node *n = malloc(sizeof(Node));
            n->num_keys = keys_of_last_node;
            Rect *keys_child = malloc(keys_of_last_node*sizeof(Rect));

            n->childs = malloc(keys_of_last_node*sizeof(Node *));

            for (int j=0; j<keys_of_last_node; j++) {
                keys_child[j] = *p;
                p++;
                if (start) {
                    n->childs[j] = NULL;
                } else {
                    n->childs[j] = *q;
                    q++;
                }
            }

            n->keys = keys_child;
            keys[techo-1] = MBR(n->keys, n->num_keys);
            childs[techo-1] = n;
        }


        nodo_padre->keys = keys;
        nodo_padre->childs = childs;

        // terminado de crear este nivel del árbol, seguimos la recursión hasta llegar a la raíz
        return createRTree(nodo_padre, techo, M, 0);  
    }
}


// Imprime el RTree
// Notacion: 
// () RECTANGULO
// [] ARREGLO DE RECTANGULOS
// Un nodo se ve así: [clave1, clave2, ...] {hijo1, hijo2, ... }  (las claves son rectangulos)
void printRTree(Node *node) {
    if (node==NULL) {
        printf("NULL");    
    } else {
        printf("[");
        int num_keys = node->num_keys;
        Rect *keys = node->keys;
        Node **childs = node->childs;
        
        for (int i=0; i < num_keys; i++) {
             Rect r = keys[i];
             printf("(%i,%i,%i,%i) ", r.x1, r.y1, r.x2, r.y2);
        }
    printf("] {");
        for (int i=0; i < num_keys; i++) {
             Node *n = childs[i];
             printRTree(n);
             printf(" ");
        }
        printf("}");
    }
}



