#include <stdio.h>
#include <stdlib.h>
#define INF 999
struct graf
{
    int n;
    int **mat;
    int **costuri;
};
void add_edge2(struct graf *g, int x, int y, int cost);
int print(struct graf *g, int dist[], int n) {
   printf("\n");
   for (int i = 1; i <= g->n; i++)
      printf("%d \t %d\n", i, dist[i]);
}
int minDistance(struct graf *g,int dist[], int viz[]) {
   int min = INF, min_index;
   int k;
   for ( k = 1; k <= g->n; k++)
   if (viz[k] == 0 && dist[k] <= min){
    min = dist[k];
     min_index = k;
   }
      
   return min_index;
}
void dijkstra(struct graf *g, int x) {
   int dist[20];
   int viz[20];
   int i;
   for (i = 1; i <= g->n; i++)
      {dist[i] = INF;
      viz[i] = 0;
      }
      dist[x] = 0;
      int c;
   for (c = 1; c <= g->n - 1; c++) {
      int u = minDistance(g,dist, viz);
      viz[u] = 1;
      int v;
      for (v = 1; v <= g->n; v++)
         if (!viz[v] && g->mat[u][v] != 0 && dist[u] != INF && dist[u] + g->mat[u][v] < dist[v]) 
         dist[v] = dist[u] + g->mat[u][v];
   }
   print(g,dist, g->n);
}
void FloydWarshall(struct graf *g);
void printg(struct graf *g);
struct graf *init();
struct graf *init1();
void add_edge(struct graf *g, int i, int j);
void del_edge(struct graf *g, int i, int j);
int in_degree(struct graf *g, int i);
int ext_degree(struct graf *g, int i);
int main()
{   FILE *f = fopen("ponderi.txt", "r");
struct graf *g1 = init1();
    int nr, m;
    fscanf(f,"%d %d\n", &nr, &m);
    printf("%d %d", nr, m);
    g1->n = nr;
    int cm= m;
    int x, y, cost;
    while (m != 0 && !feof(f))
    {   
        fscanf(f,"%d %d %d", &x,&y,&cost);
        printf("%d %d %d   ",x, y, cost);
        g1->mat[x][y] = cost;  
        m--;
    }
    int i, j;
    for (i=1; i<=g1->n; i++)
        for (j=1; j<= g1->n; j++){
              if (i == j)
                g1->mat[i][j] = 0;
               else{
                if ( g1->mat[i][j] == 0)
                    g1->mat[i][j] = INF;
               }
        }
    for (i=1; i<=g1->n; i++){
        for (j=1; j<= g1->n; j++)
            printf("%d ", g1->mat[i][j]);
        printf("\n");
        }   
    dijkstra(g1,1);
    struct graf *g = init();
    g->n = 6;
    add_edge(g,1,2);
    add_edge(g,2,1);
    add_edge(g,2,3);
    add_edge(g,5,6);
    add_edge(g,1,5);
   // del_edge(g,2,1);
    printg(g);
    FloydWarshall(g);
  struct graf *g3 = malloc(sizeof(struct graf));
  g3->mat = malloc(20*sizeof(int *));
    int i;
    for (i=0; i<=20; i++)
        g3->mat[i] = calloc(20,sizeof(int));
  g3->costuri = malloc(sizeof(int *));
   for (i=0; i<=20; i++)
    g3->costuri[i] = calloc(20,sizeof(int));
    return 0;
}
void add_edge2(struct graf *g, int x, int y, int cost)
{
  
}
struct graf *init1()
{
    struct graf *g = malloc(sizeof(struct graf));
    g->mat = malloc(20*sizeof(int *));
    int i;
    for (i=0; i<=20; i++)
        g->mat[i] = calloc(20,sizeof(int));
    return g;
}
void insertEdge (struct graf *g, int u, int v, int cost) {
g->mat[u][v] = cost;
}
void printg(struct graf *g)
{
    int i, j;
    for (i=1; i<=g->n; i++){
        for (j=1; j<=g->n; j++)
          printf("%d ", g->mat[i][j]);
        printf("\n");
    }
}
struct graf *init()
{
    struct graf *g = malloc(sizeof(struct graf));
    g->mat = malloc(10*sizeof(int *));
    for (int i = 0; i<=10; i++)
    g->mat[i] = calloc(10,sizeof(int));
    return g;
}
void add_edge(struct graf *g, int i, int j)
{
    g->mat[i][j] = 1;

}
void del_edge(struct graf *g, int i, int j)
{
    g->mat[i][j] = 0;

}
int in_degree(struct graf *g, int i) //pe coloana = inteior
{
    int grdint = 0;
    int j;
    for (j=1; j<=g->n; j++){
        grdint = grdint + g->mat[j][i];
    }
    return grdint;
}
int ext_degree(struct graf *g, int i) // pe linie = exterior
{
  int j;
  int gradext =0;
  for (j=1; j<=g->n; j++)
    gradext = gradext + g->mat[i][j];
    
}
void FloydWarshall(struct graf *g)
{
  int d[10][10];
  int i, j, k, c = 1;
  // initializarea matricei de distante cu inf sau 0 pe diagonala
  for (i = 1; i <= g->n; i++) {
    for (j = 1; j <= g->n; j++) {
        if(i==j) d[i][j] = 0;
        else {
            if(g->mat[i][j]==0){
                d[i][j] = INF;
            }
            else {
            d[i][j] = c; 
            c = c+1;
            }
        }
        //printf("%d %d %d %d\n", i,j, g->mat[i][j], cost);
    }
  }
 // dist[6][2]=200;

  // Actualizarea matricei de distante
  for (k = 1; k <= g->n; k++) {
    for (i = 1; i <= g->n; i++) {
      for (j = 1; j <= g->n; j++) {
        if (d[i][j] > d[i][k] + d[k][j]) {
        //printf("%d %d %d %d\n", i,j, dist[i][j], cost);
        //printf("%d %d %d %d\n", i,j, dist[i][j], cost);
          d[i][j] = d[i][k] + d[k][j];
        //printf("%d %d %d %d\n", i,j, dist[i][j], cost);

        }
      }
    }
  }
  printf("Matricea de distante:\n");
  for (i = 1; i <= g->n; i++) {
    for (j = 1; j <= g->n; j++) {
      if (d[i][j] == INF) {
        printf("INF ");
      } else {
        printf("%d ", d[i][j]);
      }
    }
    printf("\n");
  }
}