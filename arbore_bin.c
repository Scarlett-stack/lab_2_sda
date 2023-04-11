#include <stdio.h>
#include <stdlib.h>
struct nod
{
   int info;
   struct nod *dr, *st;
};
struct nod *init_tree();
struct nod *build_node(int a, struct nod *left_root, struct nod *right_root);
struct nod *insert_node(int a, struct nod *root);
void preordine(struct nod *root);
void inordine(struct nod *root);
void postordine(struct nod *root);
int medie_count(struct nod  *root, int *c);
void srd_un_fiu(struct nod *root,int *c);
int main()
{  
    struct nod *root = init_tree();
    root = build_node(10,NULL,NULL); // ATENTIE nodul radacina trb initializat altfel ai seg fault 
    root = insert_node(6,root);
    root = insert_node(15,root);
    root = insert_node(12,root);
    root = insert_node(17, root);
    root = insert_node(13, root);
    root = insert_node(2,root);
    root = insert_node(8, root);
    root = insert_node(7,root);
    preordine(root);
    printf("\n");
    postordine(root);
    printf("\n");
    inordine(root);
/*-------------CERINTA CU MEDIA ARITMETICA------------------------*/
int c = 0;
printf("cate noduri am : %d\n", medie_count(root,&c));
/*---------CERINTA CU UN FIU SRD---------------------------------*/
printf("srd : \n");
int r = 0;
srd_un_fiu(root, &r);
/*-----------CERINTA CU NU FRUNZE AU DOI FII--------------------*/

    return 0;
}
void srd_un_fiu(struct nod *root,int *c)
{
    if (root == NULL)
    return;
    srd_un_fiu(root->st, c); //schimba functia 1!!
    srd_un_fiu(root->dr,c);
    if (root->dr != NULL && root->st == NULL){
        *c = (*c) + 1;
        printf("info : %d rezultat: %d\n",root->info, *c);
}
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
void preordine(struct nod *root)
{
    if (root == NULL)
    return;
    printf(" %d ",root->info);
    preordine(root->st);
    preordine(root->dr);
}
void inordine(struct nod *root)
{
    if (root == NULL)
    return;
    inordine(root->st);
    printf(" %d ",root->info);
    inordine(root->dr);
}
void postordine(struct nod *root)
{
    if (root == NULL)
    return;
    postordine(root->st);
    postordine(root->dr);
    printf(" %d ",root->info);
}
int medie_count(struct nod  *root,int *c)
{
    if (root->dr != NULL && root->st != NULL){ //are doi fii daca nu se termina pe null
        int ma = (root->dr->info + root->st->info)/2; //calc ma
        printf("cine e root st dr : %d %d %d\n", root->info, root->dr->info,root->st->info);
        int c1 = medie_count(root->st,c);
        int c2 = medie_count(root->dr,c);
        *c = c2+ c1;
        if (root->info > ma){
            printf("root info ma :%d %d\n", root->info, ma);
            *c = *c + 1;
        }
    }
    else{
        *c = 0; // ajunge pe frunza -- contoorul se pune pe 0 
    }
    int x = (*c);
    printf("%d aici e x\n", x);
    return x;
}
