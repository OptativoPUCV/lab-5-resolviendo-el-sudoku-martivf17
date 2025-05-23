#include <stdio.h>
#include <stdlib.h>
#include "list.h"


typedef struct{
   int sudo[9][9];
}Node;

Node* createNode(){
  Node* n=(Node*) malloc(sizeof(Node));
  return n;
}

Node* copy(Node* n){
    Node* new=(Node*) malloc(sizeof(Node));
    *new = *n;
    return new;
}

Node* read_file (char* file_name){
  Node* n = createNode();
  FILE* file = fopen (file_name, "r");
  int i,j;
  for(i=0;i<9;i++){
       for(j=0;j<9;j++){
          if(!fscanf (file, "%d", &n->sudo[i][j]))
            printf("failed to read data!");
       }
  }

  fclose (file);
  return n;
}

void print_node(Node* n){
    int i,j;
    for(i=0;i<9;i++){
       for(j=0;j<9;j++)
          printf("%d ", n->sudo[i][j]);
       printf("\n");
    }
    printf("\n");
}

int is_valid(Node* n){
  int i, j;

  for (i = 0; i < 9; i++){
    int vistos[10] = {0};

    for(j = 0; j < 9; j++){
      int valor = n ->sudo[i][j];
      if(valor != 0){
        if (vistos[valor]) return 0;
        vistos[valor] = 1;
      }
    }
  }

  for(j = 0; j < 9; j++)
  {
    int vistos[10] = {0};

    for(i = 0; i < 9; i++){

      int valor = n->sudo[i][j];
      if(valor != 0){
        if (vistos[valor]) return 0;
        vistos[valor] = 1;
      }
    }
  }

  for(int k = 0; k < 9; k++){
    int vistos[10] = {0};

    for(int p=0;p<9;p++){
        int i=3*(k/3) + (p/3) ;
        int j=3*(k%3) + (p%3) ;
        int valor = n->sudo[i][j];
        if(valor != 0) {
          if (vistos[valor]) return 0;
          vistos[valor] = 1;
        }
    }
  }
  return 1;
}


List* get_adj_nodes(Node* n){
    List* list = createList();
    int fil = -1, col = -1;

    for (int i = 0; i < 9 && fil == -1; i++) {
        for (int j = 0; j < 9 && col == -1; j++) {
            if (n->sudo[i][j] == 0) {
                fil = i;
                col = j;
            }
        }
    }
    if (fil == -1  || col == -1){
      return list;
    }
    for (int val = 1; val <= 9; val++) {
        Node* new_nodo = copy(n);
        new_nodo->sudo[fil][col] = val;

        if (is_valid(new_nodo)){
          pushBack(list, new_nodo);
        }
        else{
          free(new_nodo);
        }
    }
    return list;
}


int is_final(Node* n){
  for(int i = 0; i < 9; i++)
  {
    for(int j = 0; j < 9; j++)
    {
        if(n->sudo[i][j] == 0){
          return 0;
        }
    }
  }
    return 1;
}

Node* DFS(Node* initial, int* cont){

  Stack* pila = createStack();
  push(pila, initial);

  while(!is_empty(pila)) {

    Node* n = top(pila);
    pop(pila);

    (*cont)++;

    if(is_final(n)){
      return n;
    }
    
    List* adj = get_adj_nodes(n);
    Node* aux = first(adj);
    while(aux != NULL){
      push(pila, aux);
      aux = next(adj);
    }
    free(n);
  }
  return NULL;
}



/*
int main( int argc, char *argv[] ){

  Node* initial= read_file("s12a.txt");;

  int cont=0;
  Node* final = DFS(initial, &cont);
  printf("iterations:%d\n",cont);
  print_node(final);

  return 0;
}*/