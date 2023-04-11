#include <stdio.h>
#include <stdlib.h>
 struct nod{
int info;
struct nod *st,*dr;
};
struct nod *init()
{
     struct nod *newn = malloc(sizeof(struct nod));
     newn->st = NULL;
     newn->dr = NULL;
     return newn;
}
struct nod *build(int a, struct nod *lt, struct nod *rt)
{
    struct nod *t = malloc(sizeof(struct nod));
    t->info = a;
    t->st = lt;
    t->dr = rt;
    return t;

}
struct nod *insert (int a, struct nod *root)
{
    if (root == NULL)
     root = build(a,NULL,NULL);
    else{
        if (a < root->info)
         root->st = insert(a,root->st);
        else //e mai mareee
        root->dr = insert(a,root->dr);
    }
    return root;
}
void RSD_postordine(struct nod *root)
{
    if (root == NULL)
      return; 
    printf(" %d ",root->info);
   // RSD_postordine(root);
    RSD_postordine(root->st);
    RSD_postordine(root->dr);
}
void SRD_inordine(struct nod *root)
{
    
}
int main()
{    
    
    struct nod *start = NULL;
    start =insert(10,start);
    start = insert(6,start);
    start = insert(2,start);
    start = insert(9,start);
    start = insert(7,start);
    start = insert(15,start);
    start = insert(12,start);
    start = insert(17,start);
    start = insert(13,start);
    RSD_postordine(start);
    printf("eu : %d %d %d",start->info,start->dr->info,start->st->info);

    
    return 0;
}