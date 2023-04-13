#include <stdio.h>
#include <stdlib.h>
struct nod
{
   int info;
   struct nod *dr;
   struct nod *st;
};
struct nod *inverse(struct nod *root);
struct nod *insert_node(int a, struct nod *root);
struct nod *init_tree();
struct nod *build_node(int a, struct nod *left_root, struct nod *right_root);
void preordine(struct nod *root);
struct nod *lca(struct nod *root, int val1,int val2);
int main()
{  
     struct nod *root = init_tree();
    root = build_node(8,NULL,NULL); // ATENTIE nodul radacina trb initializat altfel ai seg fault 
    root = insert_node(3,root);
    root = insert_node(10,root);
    root = insert_node(1,root);
    root = insert_node(6, root);
    root = insert_node(4, root);
    root = insert_node(7,root);
    root = insert_node(10, root);
    root = insert_node(14,root);
    root = insert_node(13,root);
    preordine(root);
    struct nod *l = malloc(sizeof(struct nod));
    l = lca(root,1,4);
    printf("cine suunt : %d\n", l->info);
    l = lca(root,13,14);
    printf("cine sunt %d\n",l->info);
    return 0;
}
struct nod *insert_node(int a, struct nod *root)
{
    if (root == NULL){
     root =build_node(a,NULL,NULL); //e doar radacina sau frunza  
     return root;
    }       
        if (a > root->info)
        root->dr = insert_node(a,root->dr);
        else//<=
        root->st = insert_node(a,root->st);
    return root;
}
struct nod *lca(struct nod *root, int val1,int val2)
{
    if (root == NULL)
    return NULL;
    if ((root->info > val1) && (root->info >val2))
       return lca(root->st,val1,val2);
    if ((root->info < val1) && (root->info <val2))
      return lca(root->dr,val1,val2);
     return root;
}
struct nod *init_tree()
{
    struct nod *root =(struct nod *)malloc(sizeof(struct nod));
    return root;
}
struct nod *build_node(int a, struct nod *left_root, struct nod *right_root)
{
    //fiind arbore binar ai nevoie de 2 directii -- de obicei aici vine null pe left si right ca faci radacinile subabrborilor
    struct nod *newn =(struct nod*)malloc(sizeof(struct nod));
    newn->dr = right_root;
    newn->st = left_root;
    newn->info = a;
    return newn;
}
void preordine(struct nod *root)
{
    if (root == NULL)
    return;
    printf(" %d ",root->info);
    preordine(root->st);
    preordine(root->dr);
}
struct nod *inverse(struct nod *root)
{
    struct nod *left = inverse(root->st);
    struct nod *right = inverse(root->dr);
    
}