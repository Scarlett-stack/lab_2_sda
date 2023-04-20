#include <stdio.h>
#include <stdlib.h>
#define COUNT 10
struct nod
{
    int info;
    struct nod *dr;
    struct nod *st;
};
void print2DUtil(struct nod *root, int space)
{
    // Base case
    if (root == NULL)
        return;

    // Increase distance between levels
    space += COUNT;

    // Process right child first
    print2DUtil(root->dr, space);

    // Print current node after space
    // count
    printf("\n");
    for (int i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->info);

    // Process left child
    print2DUtil(root->st, space);
}
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
  void heapify(int v[], int n, int i) {
    // cautam max dintre root, stanga si dreapta 
    int max = i;
    int st= 2 * i + 1;
    int dr = 2 * i + 2;
  
    if (st < n && v[st] > v[max])
      max = st;
  
    if (dr < n && v[dr] > v[max])
      max = dr;
    if (max != i) //max nu e pe root continuam
    {
      swap(&v[i], &v[max]);
      heapify(v, n, max);
    }
  }
void heapSort(int a[], int n) {
    // facem max heapul
    int i;
    for (i = n / 2 - 1; i >= 0; i--)
      heapify(a, n, i);
  
    for (i = n - 1; i >= 0; i--) {
      swap(&a[0], &a[i]);
      heapify(a, i, 0);
    }
  }
int nr_nod_peste_nivel_tot(struct nod *root, int niv_curent, int n);
int nr_nod_peste_nivel(struct nod *root, int niv, int n);
float procent(struct nod *root, int n);
void inverse(struct nod *root);
struct nod *insert_node(int a, struct nod *root);
struct nod *init_tree();
struct nod *build_node(int a, struct nod *left_root, struct nod *right_root);
void preordine(struct nod *root);
struct nod *lca(struct nod *root, int val1, int val2);
int main()
{   int v[] = {1, 12, 9, 5, 6, 10};
    int n = 6;
    heapSort(v, n);
    for (int i = 0; i < n; ++i)
      printf("%d ", v[i]);
    printf("\n");
    struct nod *root = init_tree();
    root = build_node(8, NULL, NULL); // ATENTIE nodul radacina trb initializat altfel ai seg fault
    root = insert_node(3, root);
    root = insert_node(10, root);
    root = insert_node(1, root);
    root = insert_node(6, root);
    root = insert_node(4, root);
    root = insert_node(7, root);
    root = insert_node(10, root);
    root = insert_node(14, root);
    root = insert_node(13, root);
    preordine(root);
    struct nod *l = malloc(sizeof(struct nod));
    l = lca(root, 1, 4);
    printf("cine suunt : %d\n", l->info);
    l = lca(root, 13, 14);
    printf("cine sunt %d\n", l->info);
    print2DUtil(root, 0);
    inverse(root);
    printf("-----------------------------");
    print2DUtil(root, 0);
    int s = 2;
    int cnt = 0;
    //int q = nr_nod_peste_nivel_tot(root, 0, 1);
   // printf("din main aici e q: %d\n", q);
   // cnt = nr_nod_peste_nivel(root, 0, n);
   //printf("cnr :%d\n", cnt);
    printf("procent : %f\n", procent(root, s));
    return 0;
}
int nr_nod_peste_nivel_tot(struct nod *root, int niv_curent, int n)
{
    if (root == NULL)
        return 0;
    if (niv_curent == n)
        return 1;
    return nr_nod_peste_nivel_tot(root->st, niv_curent + 1, n) + nr_nod_peste_nivel_tot(root->dr, niv_curent + 1, n);
}
int nr_nod_peste_nivel(struct nod *root, int niv, int n)
{
    if (root == NULL)
        return 0;
    if (niv == n && root->info % 2 == 0)
        return 1;
    return nr_nod_peste_nivel(root->st, niv + 1, n) + nr_nod_peste_nivel(root->dr, niv + 1, n);
}
float procent(struct nod *root, int n)
{
    if (root == NULL)
        return 0.0;
    int total = nr_nod_peste_nivel_tot(root, 0, n);
    int pare = nr_nod_peste_nivel(root, 0, n);
    //printf("total %d\n", total);
    return (pare * 100 / total); // baga *100 in paranteze ca altfel da 0 suparatul asta pe viata
}
struct nod *insert_node(int a, struct nod *root)
{
    if (root == NULL)
    {
        root = build_node(a, NULL, NULL); // e doar radacina sau frunza
        return root;
    }
    if (a > root->info)
        root->dr = insert_node(a, root->dr);
    else //<=
        root->st = insert_node(a, root->st);
    return root;
}
struct nod *lca(struct nod *root, int val1, int val2)
{
    if (root == NULL)
        return NULL;
    if ((root->info > val1) && (root->info > val2))
        return lca(root->st, val1, val2);
    if ((root->info < val1) && (root->info < val2))
        return lca(root->dr, val1, val2);
    return root;
}
struct nod *init_tree()
{
    struct nod *root = (struct nod *)malloc(sizeof(struct nod));
    return root;
}
struct nod *build_node(int a, struct nod *left_root, struct nod *right_root)
{
    // fiind arbore binar ai nevoie de 2 directii -- de obicei aici vine null pe left si right ca faci radacinile subabrborilor
    struct nod *newn = (struct nod *)malloc(sizeof(struct nod));
    newn->dr = right_root;
    newn->st = left_root;
    newn->info = a;
    return newn;
}
void preordine(struct nod *root)
{
    if (root == NULL)
        return;
    printf(" %d ", root->info);
    preordine(root->st);
    preordine(root->dr);
}
void inverse(struct nod *root)
{
    if (root == NULL)
        return;
    // facem o simpla interschimbare
    struct nod *aux = root->st;
    root->st = root->dr;
    root->dr = aux;

    inverse(root->st);
    inverse(root->dr);
}