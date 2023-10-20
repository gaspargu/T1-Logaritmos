void writeLeafs(char *file_name, Rect *array, int n, int M);
void writeNodes(char *file_name, Rect *array, int n, int M, long offset);
void readFile(char *file_name);
void constructRTreeBin(char *file_name, Rect *array, int n, int M);
Res *buscar(char *file_name, int n, int M, Rect C);
void buscar_recursivo(FILE *file, int M, Rect *p, Res *res, Rect C, long pos);
