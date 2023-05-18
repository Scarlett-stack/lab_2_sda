// Bellman Ford Algorithm in C

#include <stdio.h>
#include <stdlib.h>

#define INFINIT 99999

//struct for the edges of the graph
struct Edge {
  int u;  //start
  int v;  //finish
  int w;  //cost
};

struct Graph {
  int V;      
  int E;      
  struct Edge *edge;  //vector de muchii
};

void bellmanford(struct Graph *g, int source);
void display(int arr[], int size);

int main(void) {
  //fac graf
  struct Graph *g = (struct Graph *)malloc(sizeof(struct Graph));
  g->V = 4;  
  g->E = 5;  

  //init vect muchii
  g->edge = (struct Edge *)malloc(g->E * sizeof(struct Edge));


  //initializez ca nam ce face
  g->edge[0].u = 0;
  g->edge[0].v = 1;
  g->edge[0].w = 5;

  
  g->edge[1].u = 0;
  g->edge[1].v = 2;
  g->edge[1].w = 4;


  g->edge[2].u = 1;
  g->edge[2].v = 3;
  g->edge[2].w = 3;


  g->edge[3].u = 2;
  g->edge[3].v = 1;
  g->edge[3].w = 6;


  g->edge[4].u = 3;
  g->edge[4].v = 2;
  g->edge[4].w = 2;

  bellmanford(g, 0);  //0 --indicele de start

  return 0;
}

void bellmanford(struct Graph *g, int source) {

  int i, j, u, v, w;

  //noduri totale
  int tV = g->V;

  //muchii totale
  int tE = g->E;
  
  //vector de distante = total noduri
  int d[tV];

  
  //predecesorii 
  int p[tV];

  //initialeziez dist si predecesorl
  for (i = 0; i < tV; i++) {
    d[i] = INFINIT;
    p[i] = 0;
  }

  //primul nod e marcat
  d[source] = 0;

  //
  for (i = 1; i <= tV - 1; i++) {
    for (j = 0; j < tE; j++) {
      u = g->edge[j].u;
      v = g->edge[j].v;
      w = g->edge[j].w;

      if (d[u] != INFINIT && d[v] > d[u] + w) {
        d[v] = d[u] + w;
        p[v] = u;
      }
    }
  }

  //cautam ciclu negativ
  //daca modofc in distante rez ca apare un cilcu negativ
  //adica nu mai gaseste minime 
  for (i = 0; i < tE; i++) {
    u = g->edge[i].u;
    v = g->edge[i].v;
    w = g->edge[i].w;
    if (d[u] != INFINIT && d[v] > d[u] + w) {
      printf("ciclu negativ!\n");
      return;
    }
  }

  //nu am gasit ciclu negativ
  //avem cale
  printf("distante: ");
  display(d, tV);
  printf("predecesori: ");
  display(p, tV);
}

void display(int arr[], int size) {
  int i;
  for (i = 0; i < size; i++) {
    printf("%d ", arr[i]);
  }
  printf("\n");
}