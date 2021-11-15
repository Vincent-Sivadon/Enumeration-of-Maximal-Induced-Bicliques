#include <stdio.h>
#include <stdlib.h>

#include "adjlst.h"

//
int writeGraph(Graph* graph, const char *filename)
{
  FILE *fp = fopen(filename, "wb");
  if(!fp)
    return printf("Error : can't open %s\n", filename), 2;

  int N = graph->size;

  // Write number of vertices
  fprintf(fp, "%d\n", N);

  // FIll step by step
  int d;
  for(int i=0 ; i<N ; i++){
    for(int j=0 ; j<N ; j++){
      if(checkEdge(graph, i, j)) d=1;
      else d=0;
      fprintf(fp, "%d ", d);
    }
  }
  fclose(fp);
}

int main(int argc, char **argv)
{
  if(argc < 2)
    return printf("Usage : %s [filename]\n", argv[0]), 1;
  char* filename = argv[1];

  Graph* graph = genRandGraph(10);
  writeGraph(graph, filename);

  return 0;
}