#include <stdio.h>
#include <stdlib.h>
struct graf
{
    int n;
    int **mat;
    int *visitat;
};
void df(struct graf *g,int x);
int grad(struct graf *g, int x);
struct graf *sterge(struct graf *g,int x,int y);
struct graf *init(struct graf *g, int n);
struct graf *insertedge(struct graf *g, int x, int y); //inre ce noduri 
int main()
{  
    struct graf *g = init(g,5);
    /*---INSERT-------*/
    g = insertedge(g,1,2);
    g = insertedge(g,1,3);
    g = insertedge(g,2,3);
    g = insertedge(g,2,4);
    g = insertedge(g,4,5);
    printf("aici e muchie %d %d\n",g->mat[1][2],g->mat[1][3]);
/*GRADUL UNUI NOD*/
int grad1 = grad(g,1);
printf("gradul nodului 1: %d\n",grad1);
int grad2 = grad(g,2);
printf("gradul nodului 2: %d\n",grad2);
int grad3 = grad(g,3);
printf("gradul nodului 3: %d\n",grad3);
int grad4 = grad(g,4);
printf("gradul nodului 4: %d\n",grad4);
int grad5 = grad(g,5);
printf("gradul nodului 5: %d\n",grad5);
    df(g,1);
    return 0;
}
struct graf *init(struct graf *g, int n)
{
    int i;
    g = malloc(sizeof(struct graf));
    g->n = n;
    g->visitat = calloc(n+1,sizeof(int));
    g->mat = malloc((n+1)* sizeof(int *));
    for (i=1; i<=n+1; i++)
    g->mat[i] = calloc((n+1), sizeof(int));
    return g;

}
struct graf *insertedge(struct graf *g, int x, int y)
{
    g->mat[x][y] = 1;
    g->mat[y][x] = 1;
    return g;
}
struct graf *sterge(struct graf *g,int x,int y)
{
    g->mat[x][y] = 0;
    return g;
}
int grad(struct graf *g, int x)
{
    int i,grd=0;
    for (i=0; i<=g->n; i++)
    if (g->mat[x][i] == 1)
    grd++;
    return grd;
}
void df(struct graf *g,int x)
{
    int k;
    g->visitat[x] = 1;
    for (k=1; k<=g->n;k++){ 
        printf("vizitat : ");
        for (int i=1; i<=g->n; i++)
          printf("%d ",g->visitat[i]);
        printf("\n");
          if (g->mat[x][k] == 1 && g->visitat[k] == 0){
        df(g,k);
        printf("nod : %d\n",x);
      }
    }      
}