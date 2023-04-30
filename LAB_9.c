#include <stdio.h>
#include <stdlib.h>
struct graf
{
    int n;
    int **mat;
};
struct graf *init();
void add_edge(struct graf *g, int i, int j);
void del_edge(struct graf *g, int i, int j);
int in_degree(struct graf *g, int i);
int ext_degree(struct graf *g, int i);
int main()
{   

    return 0;
}
struct graf *init()
{
    struct graf *g = malloc(sizeof(struct graf));
    g->mat = malloc(10*sizeof(int *));
    for (int i = 0; i<=10; i++)
    g->mat[i] = malloc(10*sizeof(int));
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
int in_degree(struct graf *g, int i)
{
    
}