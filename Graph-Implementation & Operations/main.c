#include <stdio.h>
#include <stdlib.h>
#include "graph.h"
int main()
{
   // printf() displays the string inside quotation
   Graph *graph = graph_initialize();
   graph_load_file(graph,"load.txt");
   graph_print(graph);
   printf("%d\n",graph_has_path(graph,0,5));
   graph_output_dot(graph,"dot.txt");
   graph_save_file(graph,"save.txt");
}
