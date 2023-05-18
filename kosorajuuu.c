#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_SIZE 5
struct Graph *graph;
struct Graph *gr;
int stack[MAX_SIZE], top;
//lista pt noduri 
struct adj_list_node
{
    int dest;
    int weight;
    struct adj_list_node *next;
}; // structura pt lista adiacenta

struct adj_list
{
    struct adj_list_node *head;
}; // graful 

struct Graph
{
    int V;
    int *visited;
    struct adj_list *array;
};
struct adj_list_node *new_adj_list_node(int dest, int weight)
{
    struct adj_list_node *newNode = (struct adj_list_node *)malloc(sizeof(struct adj_list_node));
    newNode->dest = dest;
    newNode->weight = weight;
    newNode->next = NULL;
    return newNode;
} //fac graful
struct Graph *create_graph(int V)
{
    struct Graph *graph = (struct Graph *)malloc(sizeof(struct Graph));
    graph->V = V;
    graph->array = (struct adj_list *)malloc(V * sizeof(struct adj_list));
    int i;
    for (i = 0; i < V; ++i)
        graph->array[i].head = NULL;
    return graph;
} 
//adaug muchii 
void add_edge(struct Graph *graph, struct Graph *gr, int src, int dest, int weight)
{
    struct adj_list_node *newNode = new_adj_list_node(dest, weight);
    newNode->next = graph->array[src].head;
    graph->array[src].head = newNode;
    transpusa(gr, src, dest, weight);
}
 // printez graful
void print_graph(struct Graph *graph1)
{
    int v;
    for (v = 0; v < graph1->V; ++v)
    {
        struct adj_list_node *temp = graph1->array[v].head;
        while (temp)
        {
            printf("% d->%d % d \t", v, temp->dest, temp->weight);
            temp = temp->next;
        }
    }
} // umplem stiva cu cc 
void add_stiva(struct Graph *graph, int v, bool visited[], int *stack)
{
    visited[v] = true;
    int i = 0;
    struct adj_list_node *temp = graph->array[v].head;
    while (temp)
    {
        if (!visited[temp->dest])
        {
           add_stiva(graph, temp->dest, visited, stack);
        }
        temp = temp->next;
    }
    push(v);
}
 // dfs
void dfs(struct Graph *gr, int v, bool visited[])
{
    visited[v] = true;
    printf("% d", v);
    struct adj_list_node *temp = gr->array[v].head;
    while (temp)
    {
        if (!visited[temp->dest])
        {
            dfs(gr, temp->dest, visited);
        }
        temp = temp->next;
    }
} 
// adaug legaturile si de la transpusa
void transpusa(struct Graph *gr, int src, int dest, int weight)
{
    struct adj_list_node *newNode = new_adj_list_node(src, weight);
    newNode->next = gr->array[dest].head;
    gr->array[dest].head = newNode;
}
void cc_tare(struct Graph *graph, struct Graph *gr, int V)
{
    bool visited[V];
    for (int i = 0; i < V; i++)
        visited[i] = false;
    for (int i = 0; i < V; i++)
    {
        if (visited[i] == false)
        {
           add_stiva(graph, i, visited, stack);
        }
    }
    int count = 1;
    for (int i = 0; i < V; i++)
        visited[i] = false;
    while (top != -1)
    {
        int v = stack[top];
        pop();
        if (visited[v] == false)
        {
            printf("Componenta tare conexa % d: \n", count++);
            dfs_recursive(gr, v, visited);
            printf("\n");
        }
    }
}
// adaug la stiva
void push(int x)
{
    if (top >= MAX_SIZE - 1)
    {
        printf("\n depasesc stiva");
    }
    else
    {
        top++;
        stack[top] = x;
    }
} // Function to pop item to stack
void pop()
{
    if (top <= -1)
    {
        printf("\n nu am  stiva");
    }
    else
    {
        top--;
    }
}
int main()
{  
    top = -1;
    int v = 5;
    struct Graph *graph = create_graph(v);
    struct Graph *gr = create_graph(v);
    add_edge(graph, gr, 1, 0, 2);
    add_edge(graph, gr, 0, 2, 2);
    add_edge(graph, gr, 2, 1, 2);
    add_edge(graph, gr, 0, 3, 2);
    add_edge(graph, gr, 3, 4, 2);
    cc_tare(graph, gr, v);
    return 0;
}