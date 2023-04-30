#include <stdio.h>
#include <stdlib.h>
struct graf
{
    int n;
    int **mat;
    int *visitat;
    int *coada;
};
int nr = 0;
void cc(struct graf*g,int x, int *nr1);
void bf(struct graf *g,int x);
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
  //  g = insertedge(g,2,4);
    g = insertedge(g,4,5);
    //printf("aici e muchie %d %d\n",g->mat[1][2],g->mat[1][3]);
/*GRADUL UNUI NOD*/
int grad1 = grad(g,1);
//printf("gradul nodului 1: %d\n",grad1);
int grad2 = grad(g,2);
//printf("gradul nodului 2: %d\n",grad2);
int grad3 = grad(g,3);
//printf("gradul nodului 3: %d\n",grad3);
int grad4 = grad(g,4);
//printf("gradul nodului 4: %d\n",grad4);
int grad5 = grad(g,5);
//printf("gradul nodului 5: %d\n",grad5);
   // bf(g,1);
   ///cc(g,1);
   int nr1 = 0;
    for (int i=1; i<=g->n; i++){
        if (g->visitat[i] == 0){
            nr1++;
            cc(g,i, &nr1);
        }
    }
    printf("nr= %d",nr1);
    for (int i=1; i<=nr1; i++)
    {
        printf("i :%d \n",i);
        for (int j=1; j<=g->n;j++)
        if (g->visitat[j] == i)
        printf("j: %d ",j);
    }
    //df(g,1);
    return 0;
}
void cc(struct graf*g,int x, int *nr1)
{
     int k;
    g->visitat[x] = *nr1;
    printf("nr din cc: %d\n", *nr1);
    //printf("nr %d si nod  : %d\n",nr,x); //afisarea s-a face pe nodul pe care esti nu la urmatorul
    for (k=1; k<=g->n;k++){
          if (g->mat[x][k] == 1 && g->visitat[k] == 0){
        cc(g,k, nr1);
        
      }
    }
}
void bf(struct graf *g, int x)
{
    int p,u;
    p=1;
    u=1;
    g->coada[p] = x;
     g->visitat[x] = 1;
    while (p<=u)
    {
        x = g->coada[p];
        for (int i=1;i<=g->n; i++)
        if (g->visitat[i] == 0 && g->mat[x][i] == 1)
        {
            ++u;
            g->coada[u] = i;
            g->visitat[u] = 1;
        }
        p++;
    } 
    for (int i=1; i<=u; i++)
    printf("nodul e : %d\n",g->coada[i]);
}
struct graf *init(struct graf *g, int n)
{
    int i;
    g =malloc(sizeof(struct graf));
    g->n = n;
    g->visitat =(int*)calloc(n+1,sizeof(int));
    g->coada = (int *)calloc(n+1,sizeof(int));
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
    nr++;
    g->visitat[x] = 1;
    printf("nr %d si nod  : %d\n",nr,x); //afisarea s-a face pe nodul pe care esti nu la urmatorul
    for (k=1; k<=g->n;k++){
       // printf("vizitat : ");
       // for (int i=1; i<=g->n; i++)
         // printf("%d ",g->visitat[i]);
        //printf("\n");
          if (g->mat[x][k] == 1 && g->visitat[k] == 0){
        df(g,k);
        
      }
    }
}
