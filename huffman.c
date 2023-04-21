#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct list
{
    int info;
    char c;
    struct list *next;
};
struct nod
{
    char c;    // pt litera
    int frecv; // asta e campul pe care il bag la min heap
    struct nod *st;
    struct nod *dr;
};
struct data
{
    int frecv;
    char c;
};
int cmp(const void *a, const void *b)
{
    struct data *a1 = (struct data *)a;
    struct data *b1 = (struct data *)b;
    return a1->frecv - b1->frecv;
}
void Typer(struct list *c)
{
    printf("din typer ");
    struct list *c1 = c;
    while(c1 != NULL)
    {
        printf("%c %d\n",c1->c, c1->info);
        c1 = c1->next;
    }
}

struct list *create_list(struct data *queue, int size);
struct nod *newnode(char c, int frecv,int frecv2);
struct data *build_pqueue(int v[],int size);
struct nod *build_tree_huff(struct list *start,int size);
int main()
{
    char str[] = "AAAAAABBBCCDDDEEEEFFFFFFGGGGGGGGGGG";
    int baza = 0;
    int v[26] = {0};
    int i = 0;
    while (i < strlen(str))
    {
        v[str[i] - 65]++;
        i++;
    }
    int size = 0;
    for (int i = 0; i < 26; i++)
    {
        if (v[i] != 0){
            size++;
            baza = baza + v[i]; 
        }
           
        printf("%d ", v[i]);
    }
 struct nod *root = malloc(sizeof(struct nod));
 root->c = '#';
 root->frecv = baza;

struct data *queue = build_pqueue(v,size);
qsort(queue,size,sizeof(struct data),cmp);
 for (i = 0; i<size; i++)
 printf("\n%c %d",queue[i].c, queue[i].frecv);
 struct list *start = create_list(queue,size);
 Typer(start);
 root = build_tree_huff(start,size);
 printf("din root: %c %d\n", root->c, root->frecv);

    return 0;
}
struct data *build_pqueue(int v[],int size)
{
    // primesc vectorul de frecventa
    struct data *queue = malloc(size *sizeof(struct data));
    int i = 0;
    for (i = 0; i<size; i++){
        if (v[i] != 0){
        queue[i].frecv = v[i];
        queue[i].c = 'A' + i;
        printf("cine e c: %c\n",queue[i].c);
        }  
    }
    return queue;
    
}
struct nod *build_tree_huff(struct list *start,int size)
{
    struct nod *left, *right, *top;
    int i=0;
    while (size > 1){
        left = malloc(sizeof(struct nod));
        right = malloc(sizeof(struct nod));
        left->frecv = start->info;
        left->dr = NULL;
        left->st = NULL;
        start = start->next;
        size--;
        right->frecv = start->info;
        right->dr = NULL;
        right->st = NULL;
        size--;
        start = start->next;
        top = newnode('#',left->frecv, right->frecv);
        top->dr = right;
        top->st = left;
        //functie de instert in heap


    }
    return top;

}
struct nod *newnode(char c, int frecv1, int frecv2)
{
    struct nod *newn = malloc(sizeof(struct nod));
    newn->frecv = frecv1 + frecv2;
    newn->c = c;
    return newn;

}
struct list *create_list(struct data *queue, int size) //implementez coada ca o lista
{
   struct list *start = malloc(sizeof(struct list));
   struct list *aux,*final;
   int i=1;
   start->c = queue[0].c;
   start->info = queue[0].frecv;
   start->next = NULL;
   aux = start;
   int j;
   while (i<size){
    final = malloc(sizeof(struct list));
    if (final == NULL){
        perror("la final");
        return NULL;
    }
    else{
        final->info = queue[i].frecv;
        final->c = queue[i].c;
        final->next = NULL;
        aux->next = final;
        aux = final;
    }
    i++;

   }
   return start;
}