#include <stdio.h>
#include <string.h>
#include <limits.h>

#define MAXN 101

int dist[MAXN];
int visited[MAXN];
int graph[MAXN][MAXN];
int gateways[MAXN];
int n, m, c, g;

void dijkstra(int start) {
    dist[start] = 0;

    for (int count = 0; count < n - 1; count++) {
        int min = INT_MAX, min_index;
        for (int v = 1; v <= n; v++)
            if (!visited[v] && dist[v] <= min)
                min = dist[v], min_index = v;
        
        int u = min_index;
        visited[u] = 1;

        for (int v = 1; v <= n; v++)
            if (!visited[v] && graph[u][v] && dist[u] != INT_MAX && dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
}

int main() {
    memset(dist, INT_MAX, sizeof(dist));
    memset(graph, 0, sizeof(graph));
    
    scanf("%d %d %d", &n, &m, &c);
    for(int i = 0; i < m; i++) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        graph[u][v] = w;
        graph[v][u] = w;  // The graph is undirected
    }

    scanf("%d", &g);
    for(int i = 0; i < g; i++) {
        scanf("%d", &gateways[i]);
    }

    dijkstra(c);

    int min_dist = INT_MAX;
    int min_gateway = -1;
    for(int i = 0; i < g; i++) {
        if(dist[gateways[i]] < min_dist) {
            min_dist = dist[gateways[i]];
            min_gateway = gateways[i];
        }
    }

    printf("%d\n", min_gateway);

    return 0;
}
