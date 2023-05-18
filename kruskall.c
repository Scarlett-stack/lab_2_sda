#include <stdio.h>
#include <stdlib.h>

struct muchie {
    int i, j, cost;
};

// vezi qsort
int compare(const void* a, const void* b) {
    struct muchie* muchieA = (struct muchie*) a;
    struct muchie* muchieB = (struct muchie*) b;
    return muchieA->cost - muchieB->cost;
}

int main() {
    int n , m , t[101];
    struct muchie x[101];
    scanf("%d %d", &n, &m);
    int i,j;
    for(i = 0 ; i < m ; ++i)
        scanf("%d %d %d", &x[i].i, &x[i].j, &x[i].cost);

    // Sort array x[] by cost field
    qsort(x, m, sizeof(struct muchie), compare);

    // retin padurea printr-un vector de tati
    for( i = 1 ; i <= n ; ++i)
        t[i] = i;

    // magie neagra: caut arborele de cost minim
    int S = 0; // costul total
    for(i = 0 ; i < m ; i ++)
        if(t[x[i].i] != t[x[i].j]) // fiecare extremitate/varf sunt din arbori diferiti 
        { //cu if asta evit cicluri pt ca daca e ciclu fac parte din acelasi subarbore in vectrul de tati
            S += x[i].cost;
            // 
            int ai = t[x[i].i]; //arborele lui i
            int aj = t[x[i].j];//arborele lui j
            for( j = 1 ; j <= n ; ++j)
                if(t[j] == aj)
                    t[j] = ai; //adaug la arborele de la j noul nod
        }
    printf("%d\n", S);
    return 0;
}
