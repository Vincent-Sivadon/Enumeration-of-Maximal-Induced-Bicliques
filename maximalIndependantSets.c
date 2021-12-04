#include "adjlst.h"



typedef struct {
  size_t *vertices;
  size_t size;
  size_t reserved_size;
} dyn_array;


void init_dynarray(dyn_array* a, size_t size) {
  if (!a)
    exit(1); // Erreur
  a->vertices = malloc(sizeof(size_t) * size);
  a->reserved_size = size;
}

void free_dynarray(dyn_array* a, size_t size) {
  if (!a)
    exit(1); // Erreur
  free(a->vertices);
  a->vertices = NULL;
  a->reserved_size = 0;
  a->size = 0;
}

void append_dynarray(dyn_array* a, int elem) {
  if (!a)
    exit(1); // Erreur
  if (a->size >= a->reserved_size)
  {
    a->vertices = realloc(a->vertices, sizeof(size_t) * (a->reserved_size + 1) * 2);
    a->reserved_size = (a->reserved_size + 1) * 2;
  }
  a->vertices[a->size] = elem;
}




dyn_array independantSets(Graph* graph){
    int N = sizeof(graph);
    int v = sizeof(N * sizeof(Vertex*)); // sizeof adjlst
    dyn_array set; 
    init_dynarray(&set, 1);
    dyn_array* set_ptr = malloc(sizeof(dyn_array) * N);
    for (int i = 0; i < N; i++){
        for (int j = 0; j<v;j++){
            if (!checkEdge(graph, i,j)){
                for (size_t k = 0; k < N; k++) {
                    init_dynarray(&set_ptr[i], v); 
                }
            }
        }
    }
    return set;

}



int main(){
    Graph* graph = genRandGraph(10);
    independantSets(graph);
}













