#include <stdio.h>
#include <stdlib.h>
#define inf 9999
int main()
{
    int **cost = malloc(100*sizeof(int *));
    for (int i=0; i<=100; i++)
     cost[i] = malloc(sizeof(int));
    int s[50]={0};
    int n, i,j,k,lin,col,c,m, min;
     printf("da n nr de noduri si muchii m:\n");
     scanf("%d %d", &n, &m);
     for (i=1; i<=n; i++)
      for (j=1; j<=n; j++)
       if (i == j)
        cost[i][j] = 0;
       else
          cost[i][j] = cost[j][i] = inf;
        int cnt =0;
    s[1] = 1;
    while (cnt < m)
    {   scanf("%d %d %d", &i, &j, &c);
        cost[i][j] = cost[j][i] = c;
        cnt++;
    }
    for (k=1; k<=n-1; k++)
    {
        min = inf;
        for (i=1; i<=n; i++)
          for (j=1; j<=n; j++)
            if (s[i] == 1 && s[j]==0 && min>cost[i][j]) //se agata de arborele precedent?
            {
                min = cost[i][j];
                lin = i;
                col = j;
            }
            printf("linie: %d ,coloana %d , min %d\n", lin, col,min);
            s[col] = 1;
    }
    
}
