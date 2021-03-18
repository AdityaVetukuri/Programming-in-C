#include "graph.h"
#include <stdio.h>
#include <stdlib.h>

// Implementation of prototypes specified in graph.h

// Initialization Functions

// Used to intitalise the graph and allocate assigned memory
Graph *graph_initialize(){
 int i,j;
 Graph *graph = NULL;
  graph = (Graph*)malloc(sizeof(Graph));  //allocating memory using malloc
  if(graph == NULL){
    return NULL;
  }
  for(i=0;i<MAX_VERTICES;i++){
    for(j=0;j<MAX_VERTICES;j++){
      graph->adj_matrix[i][j]=0;    //setting adj_matrix intially to 0
    }
  }
  for(i=0;i<MAX_VERTICES;i++){
    graph->visited[i]=-1;    // visited used for checking vertex is present in graph and also in bfs for graph_has_path
  }                         // [-1 --> not in graph] [0 --> present in graph but not visited] [1 --> visited]
  return graph;
}

// Vertex Operations

int graph_add_vertex(Graph *graph, int v1){
  if(v1<0 || v1>=MAX_VERTICES){
    return -1;    //checking the bounds of the vertex to be added
  }
  if(graph->visited[v1]==-1){
    graph->visited[v1]=0;
  }
  return 0;
}
int graph_contains_vertex(Graph *graph, int v1){
  if(v1<0 || v1>=MAX_VERTICES){
    return -1;    //checking the bounds of the vertex to be added
  }
  if(graph->visited[v1]!=-1){
    return 1;
  }
  return 0;
}
int graph_remove_vertex(Graph *graph, int v1){
  if(v1<0 || v1>=MAX_VERTICES){
    return -1;    //checking the bounds of the vertex to be added
  }
  if(graph->visited[v1]==0){
    graph->visited[v1]=-1;
  }
  return 0;
}
int graph_add_edge(Graph *graph, int v1, int v2, int wt){
  if(v1<0 || v1>=MAX_VERTICES){
    return -1;
  }
  if(v2<0 || v2>=MAX_VERTICES){
    return -1;
  }
  graph->adj_matrix[v1][v2]=wt;
  return 0;
}

// Edge Operations

int graph_contains_edge(Graph *graph, int v1, int v2){
  if(v1<0 || v1>=MAX_VERTICES){
    return -1;    //checking the bounds of the vertex v1
  }
  if(v2<0 || v2>=MAX_VERTICES){
    return -1;    //checking the bounds of the vertex v2
  }
  if(graph->adj_matrix[v1][v2]!=0){
    return 1;
  }
  return 0;
}
int graph_remove_edge(Graph *graph, int v1, int v2){
  if(v1<0 || v1>=MAX_VERTICES){
    return -1;    //checking the bounds of the vertex v1
  }
  if(v2<0 || v2>=MAX_VERTICES){
    return -1;    //checking the bounds of the vertex v2
  }
  graph->adj_matrix[v1][v2]=0;
  return 0;
}

// Graph Metrics Operations
int graph_num_vertices(Graph *graph){
  int num_vetices=0,i;
  for(i=0;i<MAX_VERTICES;i++){    //traversing the vsisted array to find number of vertices
    if(graph->visited[i]!=-1){
      num_vetices++;
    }
  }
  return num_vetices;
}
int graph_num_edges(Graph *graph){
  int num_edges=0,i,j;
  for(i =0;i<MAX_VERTICES;i++){   //traversing the adj_matrix arrray to find the number of edges
    for(j=0;j<MAX_VERTICES;j++){
      if(graph->adj_matrix[i][j]!=0){
        num_edges++;
      }
    }
  }
  return num_edges;
}
int graph_total_weight(Graph *graph){
  int total_weight=0,i,j;
  for(i =0;i<MAX_VERTICES;i++){   //traversing and adding the values of adj_matrix array to find the total graph weight
    for(j=0;j<MAX_VERTICES;j++){
      total_weight+=graph->adj_matrix[i][j];
    }
  }
  return total_weight;
}

// Vertex Metrics Operations

int graph_get_degree(Graph *graph, int v1){
  int degree =0,i;
  for(i=0;i<MAX_VERTICES;i++){    //traversing adj_matrix to find the out degree of the vertex
    if(graph->adj_matrix[v1][i]!=0){
      degree++;
    }
    if(graph->adj_matrix[i][v1]!=0){  //traversing adj_matrix to find the in degree of the vertex
      degree++;
    }
  }
  return degree;
}
int graph_get_edge_weight(Graph *graph, int v1, int v2){
  if(graph->adj_matrix[v1][v2]!=0){
    return graph->adj_matrix[v1][v2];   //returning the edge weight if present
  }
  return -1;    //returning -1 in case of no edge
}
int graph_is_neighbor(Graph *graph, int v1, int v2){
  if(graph->adj_matrix[v1][v2]!=0 || graph->adj_matrix[v2][v1]!=0){   //checking both in edge and edge to predict neighbor
    return 1;
  }
  return 0;
}
int *graph_get_predecessors(Graph *graph, int v1){
   int *pred = malloc((MAX_VERTICES+1) * sizeof(int));    //allocating size of MAX_VERTICES+1 integers to store predecessors
   int num_pred = 0,i;
   for(i=0;i<MAX_VERTICES;i++){
     if(graph->adj_matrix[i][v1]!=0){   //checking adj_matrix to find predcessors and adding them to the pred array
       pred[num_pred]=i;
       num_pred++;
     }
   }
   pred[num_pred]=-1;   //adding -1 at the end to denote end of the array
   return pred;
}
int *graph_get_successors(Graph *graph, int v1){
  int *succ = malloc((MAX_VERTICES+1) * sizeof(int));   //allocating size of MAX_VERTICES+1 integers to store successsors
  int num_succ = 0,i;
  for(i=0;i<MAX_VERTICES;i++){
    if(graph->adj_matrix[v1][i]!=0){    //checking adj_matrix to find predcessors and adding them to the succ array
      succ[num_succ]=i;
      num_succ++;
    }
  }
  succ[num_succ]=-1;    //adding -1 at the end to denote end of the array
  return succ;
}

// Graph Path Operations

int graph_has_path(Graph *graph, int v1, int v2){
  int i;
  graph->visited[v1]=1;
  if(v1 == v2) return 1;
  for(i=0;i<MAX_VERTICES;i++){    // using BFS(Breadth first search) to find if there is path form v1 to v3
    if(graph->visited[i]==0 && graph->adj_matrix[v1][i]!=0){
      if(graph_has_path(graph,i,v2)==1){
        return 1;
      }
    }
  }
  return 0;
}

// Input/Output Operations

void graph_print(Graph *graph){
  int weight = 0,i,j;
  printf("printing the graph :--\n");
  for(i=0;i<MAX_VERTICES;i++){
    if(graph_contains_vertex(graph,i)==1){    //printing the vertices in the graph using graph_contains_vertex function
      printf("vertex %d;\n",i);
    }
    for(j=0;j<MAX_VERTICES;j++){    //printing edges using graph_get_edge_weight function
      weight = graph_get_edge_weight(graph,i,j);
      if(weight!=-1){
        printf("edge from %d to %d with weight %d\n",i,j,weight);
      }
    }
  }
}
void graph_output_dot(Graph *graph, char *filename){
  FILE *fptr;
  int weight = 0,i,j;
  fptr = fopen(filename, "w");    //opening the file in write graph_remove_edge
  if(fptr == NULL){     //returning in case error in opening the file
    return;
  }
  fprintf(fptr, "digraph {\n");
  for(i=0;i<MAX_VERTICES;i++){
    if(graph_contains_vertex(graph,i)==1){    //writing the vertices in the graph using graph_contains_vertex function
      fprintf(fptr, "%d;\n",i);
    }
    for(j=0;j<MAX_VERTICES;j++){    //writing edges using graph_get_edge_weight function
      weight = graph_get_edge_weight(graph,i,j);
      if(weight!=-1){
        fprintf(fptr, "%d -> %d [label = %d];\n",i,j,weight);
      }
    }
  }
  fprintf(fptr, "}");
  fclose(fptr);   //closing the file
}
int graph_load_file(Graph *graph, char *filename){
   FILE *fptr;
   char ch;
   int temp=0;
   int v1 = -1 ;
   int v2 = -1;
   int curr = 0;
   //each line is either of the following formats
   //vertex v ---> single vertex addition
   //vertex v1,vertex v2,weight w  --> adding edge from v1 to v2 with weight w

   fptr = fopen(filename, "r");   //opening the file in read mode
   if (fptr == NULL)
   {
      return -1;
   }
   ch = fgetc(fptr);    //traversing each character in the file
   while (ch != EOF)    //ending the traversal of reaching the end of file
   {
      if(ch == '\n')    // checking for new line character to add the vertices and edges in the line
      {
         if(curr == 0){   //checking if the line does not contains , which means to only add the vertex stored in temp
           graph_add_vertex(graph,temp);
         }
         else{      //adding both the vertices and edge in case line contains a ,
           graph_add_vertex(graph,v1);
           graph_add_vertex(graph,v2);
           graph_add_edge(graph,v1,v2,temp);
         }
         curr=0;    // intitalising parameteres for new line
         temp=0;
         v1=-1;
         v2=-1;
      }
      else if(ch == ',')
      {
        curr = 1;   //setting curr parametere to 1 when a , is found
        if(v1==-1){
          v1=temp;    //if v1 is not set the temp value stored is given to v1
        }
        else{
          v2=temp;   //if v1 is set then the temp is given to v2
        }
        temp=0;   //re-intitalising temp to 0
      }
      else
      {
        temp = temp*10 + (ch - '0');    // if char is a number it is stored in temp and interated until a , or \n is encountered
      }
      ch = fgetc(fptr);   //moving to next character
   }
   fclose(fptr);    //closing the file
   return 0;
}
int graph_save_file(Graph *graph, char *filename){
  FILE *fptr;
  int weight = 0,i,j;
  fptr = fopen(filename, "w");    //opening the file in write mode
  if(fptr == NULL){     //returning in case error in opening the file
    return -1;
  }
  for(i=0;i<MAX_VERTICES;i++){
    if(graph_contains_vertex(graph,i)==1){    //writing the vertices in the graph using graph_contains_vertex function
      fprintf(fptr, "%d\n",i);
    }
    for(j=0;j<MAX_VERTICES;j++){    //writing edges using graph_get_edge_weight function
      weight = graph_get_edge_weight(graph,i,j);
      if(weight!=-1){
        fprintf(fptr, "%d,%d,%d\n",i,j,weight);
      }
    }
  }
  fclose(fptr);   //closing the file
  return 0;
}
