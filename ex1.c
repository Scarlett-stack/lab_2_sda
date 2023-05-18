#include <stdlib.h>
#include <stdio.h>
#define INF 99999
struct graf {
    int n;
    int **mat;
    int cost[100][100];
};
void afisare_cost(struct graf *g) {
    int i,j;
        for(i = 0; i < g->n; i++) {
            for(j = 0; j < g->n; j++) {
                printf("%d ", g->cost[i][j]);
        }
    }
}
void add_edge(struct graf *g, int i, int j)
{
    g->mat[i][j] = 1;

}
struct graf *init()
{
    struct graf *g = malloc(sizeof(struct graf));
    g->mat = malloc(10*sizeof(int *));
    for (int i = 0; i<=10; i++)
    g->mat[i] = calloc(10,sizeof(int));
    return g;
}
void add_edge2( int x, int y,struct graf *g, int cost)
{
  g->mat[x][y] = cost;
  g->mat[y][x] = cost;
}
int poarta(struct graf *g, int c, int porti[], int nrporti) {
    int i, j, min_distance = 99999, min = -1;
    for (i = 0; i < nrporti; i++) {
        j = porti[i];
        if (g->cost[j][c] < min_distance) {
            min_distance = g->cost[j][c];
            min = j;
        }
    }
    return min;
}
void floyd_warshall(struct graf *g)
{
  int d[10][10];
  int i, j, k, c = 1;
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
    }
  }

  // Actualizez matrice de distante
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
void dijkstra(int start, int end, int dist[], int prev[], int visited[], struct graf *g, int *distanta, int cale[]) {
    // initializare
    int i, min_dist, current, j;
    for (i = 0; i < g->n; i++) {
        dist[i] = INF;
        prev[i] = -1;
        visited[i] = 0;
    }
    dist[start] = 0;

    // parcurgere
    for (i = 0; i < g->n-1; i++) {
        min_dist = INF; current = -1;
        // selectare nod cu distanta minima
        for (j = 0; j < g->n; j++) {
            if (!visited[j] && dist[j] < min_dist) {
                min_dist = dist[j];
                current = j;
            }
        }
        if (current == -1) {
            break;
        }
        visited[current] = 1;
        // actualiz distantele
        for (j = 0; j < g->n; j++) {
            if (g->mat[current][j] && !visited[j]) {
                int alt_dist = dist[current] + g->mat[current][j];
                if (alt_dist < dist[j]) {
                    dist[j] = alt_dist;
                    prev[j] = current;
                }
            }
        }
    }

    // afisare cale
    if (dist[end] == INF) {
        *distanta = INF;
        //printf("Nu exista cale intre nodurile %d si %d.\n", start, end);
    } else {
        *distanta = dist[end];
       // printf("Lungimea minima a drumului dintre nodurile %d si %d este %d.\n", start, end, dist[end]);
       // printf("Calea este: ");
        int path[100], path_len = 0;
        int current = end;
        while (current != start) {
            path[path_len++] = current;
            current = prev[current];
        }
        path[path_len++] = start;
        for (int i = path_len-1; i >= 0; i--) {
            cale[i]=path[i];
        }
    }
}
void gasesc_nod(int p,struct graf *g) { //gasese de la p la q drumul par min
    int d[100], prev[100], visited[100];
    int q, i, nr = 0;
    int path[100], len, nod[100];
    for (q = 0; q < g->n; q++) {
        if (q != p) {
            dijkstra(p, q, d, prev, visited, g, &len, path);
            if (len % 2 == 0 && len != INF) {
                nod[nr] = q;
                nr++;
            }
        }
    }
    printf("%d\n", nr);
    for (i = 0; i < nr; i++) {
        printf("%d ", nod[i]);
    }
}
void afisare_graf(struct graf *g);
int main() {
    int i, j;
    int n = 7, m = 8, nrporti = 2, C = 1, porti[100];
    porti[0] = 2;
    porti[1] = 4;
    struct graf *g = init(7);
    add_edge2(1, 0, g, 4);
    add_edge2(0, 4, g, 1);
    add_edge2(0, 6, g, 2);
    add_edge2(2, 1, g, 9);
    add_edge2(1, 3, g, 2);
    add_edge2(1, 5, g, 2);
    add_edge2(1, 6, g, 1);
    add_edge2(4, 5, g, 7);
    afisare_graf(g);
    printf("\n");
    floyd_warshall(g);
    afisare_cost(g);
    printf("\n");
    printf("poarta cu dist min: %d\n", poarta(g, C, porti, nrporti));
    int p = 1;
    int n1 = 7, m1 = 10;
   struct graf *g1 = init(7);
    add_edge( g1,0,1);
    add_edge( g1,1,2);
    add_edge( g1,1,4);
    add_edge( g1,2,3);
    add_edge(g1,2, 5 );
    add_edge( g1,3, 6);
    add_edge( g1,4, 0);
    add_edge( g1,4, 2);
    add_edge( g1,4, 3);
    add_edge( g1,5, 4);
    //afisare_graf(g);
    gasesc_nod(p, g1);
    return 0;
}
void afisare_graf(struct graf *g)
{
    int i,j;
    for (i=0; i<g->n; i++)
     for (j=0; j<g->n; j++)
       if (g->mat[i][j]==1)
         printf("%d %d\n", i,j);
}