#include <stdio.h>
#include <stdlib.h>
struct graf
{
    int n;
    int **mat;
};
void df(struct graf g,int x,int *visit);
int grad(struct graf g, int x);
struct graf sterge(struct graf g,int x,int y);
struct graf init(struct graf g, int n);
struct graf insertedge(struct graf g, int x, int y); //inre ce noduri 
int main()
{  
    struct graf g = init(g,10);
    g = insertedge(g,1,2);
    g = insertedge(g,1,3);
    g = insertedge(g,2,3);
    g = insertedge(g,4,5);
    printf("aici e muchie %d\n",g.mat[1][2]);
    int *v = calloc(50,sizeof(int));
    df(g,1,v);
    return 0;
}
struct graf init(struct graf g, int n)
{
    int i;
    g.n = n;
    g.mat = malloc((n+1)* sizeof(int *));
    for (i=1; i<=n+1; i++)
    g.mat[i] = calloc((n+1), sizeof(int));
    return g;

}
struct graf insertedge(struct graf g, int x, int y)
{
    g.mat[x][y] = 1;
    return g;
}
struct graf sterge(struct graf g,int x,int y)
{
    g.mat[x][y] = 0;
    return g;
}
int grad(struct graf g, int x)
{
    int i,grd=0;
    for (i=0; i<=g.n; i++)
    if (g.mat[x][i] == 1)
    grd++;
    return grd;
}
void df(struct graf g,int x, int *visit)
{
    int k;
    visit[x] = 1;
    for (k=1; k<=g.n;k++)
      if (g.mat[x][k] == 1 && visit[k] == 0){
        printf("nod : %d\n",x);
        df(g,k,visit);
      }
        
}