#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct stiva_node
{
    int info;
    char cc;
    struct stiva_node *next;
};
struct coada
{
    int chestie;
    struct coada *next;
};
void pop2(struct stiva_node *s);
char top2(struct stiva_node *s);
void push2(struct stiva_node *s, char c);
struct coada *functie(struct coada *santi);
struct coada *init_q(struct coada *santi);
int last(struct coada *santinela);
int first(struct coada *santinela);
void deq(struct coada *santinela);
void enq(struct coada *santinela, int elem);
void push(struct stiva_node **p, int n);
void pop(struct stiva_node **p);
int top(struct stiva_node *p);
int is_empty(struct stiva_node *p);
void TyperC(struct coada *c);
int empty(struct coada *santinela);
int paranteze(struct stiva_node *santinela, char s[]);
int matchy(char c, char d);
int main()
{
    struct stiva_node *n = malloc(sizeof(struct stiva_node));
    n->next = NULL;
    n->info = 0;
    push(&n, 1); // aici e push
    push(&n, 2);
    printf("dupa push : %d %d %d\n", n->info, n->next->info, n->next->next->info);
    pop(&n);               // aici e pop
    printf("aici e top :%d ", top(n)); // aici e top
    printf("\n");
    struct stiva_node *s = n;
    while (s != NULL)
    {
        printf("typer : %d ", s->info);
        s = s->next;
    }
    int q = is_empty(n);
    printf("eu sunt q: %d \n", q);

    /*---------------------------------------COADA---------------------------*/
    struct coada *santinela_coada = malloc(sizeof(struct coada));
    santinela_coada->next = NULL;
    enq(santinela_coada, 12);
    enq(santinela_coada, 13);
    TyperC(santinela_coada->next);
    deq(santinela_coada->next);
    TyperC(santinela_coada->next);
    enq(santinela_coada, 14);
    enq(santinela_coada, 15);
    enq(santinela_coada, 16);
    printf("ce am in first :%d\n", first(santinela_coada));
    printf("ce am in last : %d\n", last(santinela_coada));
    printf("sunt vid : %d\n", empty(santinela_coada));
    /*--------------------------EX 4-------------------------------------------*/
    struct coada *santi = functie(santinela_coada);
    printf("ce am coada cu pare: \n");
    TyperC(santi->next);
    /*-----------------------PARANTEZE-------------------------------------------*/
    struct stiva_node *alta_sant = malloc(sizeof(struct stiva_node));
    alta_sant->next = NULL;
    char str[100]="({})[";
    printf("aici e sirul %s", str);
    int z=paranteze(alta_sant,str);
    if (z == 1)
    printf("DA");
    else{
       printf("NU");  
       printf(" %d ",z);
    }
    //{{}}[[({})]]  [[{(}}]][()]
}
int matchy(char c, char d)
{
    if (c == '(' && d == ')')
        return 1;
    else if (c == '[' && d == ']')
        return 1;
    else if (c == '{' && d == '}')
        return 1;
    else
        return -1;
}
void push2(struct stiva_node *s, char c)
{
    if (s->next == NULL)
    {
        s->next = malloc(sizeof(struct stiva_node));
        s->next->next = NULL;
        s->next->cc = c;
    }
    else
    {
        struct stiva_node *newn = malloc(sizeof(struct stiva_node));
        newn->cc = c;
        newn->next = s->next;
        s->next = newn;
    }
}
int paranteze(struct stiva_node *santinela, char s[])
{   printf("\n%c\n",s[0]);
    int i=0;
    struct stiva_node *c;
    santinela->next = NULL;
    while (s[i] != '\0')
    {
        if (strchr("[({", s[i])) // open bracket
            push2(santinela, s[i]);
        if (strchr(")]}", s[i])) // closing bracket
        {                        // daca stiva e goala evident nu am paantezele complete
            if (is_empty(santinela->next) == 1) 
                return 9;
            else
            {
                char x = top2(santinela->next); //selectez primul elemnt din stiva (paranteza inchisa)
                printf("x si s[i]: %c %c\n",x,s[i]); //verificare
                if (matchy(x, s[i]) == 1) //daca e cuplu inhcis-deschis
                    pop2(santinela); //afara din stiva trec la urmatorul elemnt din stiva
                else
                    return 8; //altfel nu sunt matchy si se incheie programul
            }
        }
       /* printf("stiva din parenteze: \n");
        c = santinela->next;
        while(c!=NULL){
            printf(" %c ",c->cc);
            c =c->next;
        }
        printf("\n");*/
        i++;
    }
    if (santinela->next == NULL) //daca am epuizat stiva inseamna ca toae au fost matchy
        return 1;
    else
        return 7; //altfel nu , doar sa terminat de parcurs
}
void pop2(struct stiva_node *s)
{
    struct stiva_node *c = s->next;
    s->next = s->next->next;
    free(c);
}
char top2(struct stiva_node *s)
{
    if (s != NULL)
        return s->cc;
    else
        return 'x';
}
void push(struct stiva_node **p, int n)
{
    struct stiva_node *c = malloc(sizeof(struct stiva_node));
    c->next = *p;
    c->info = n;
    *p = c;
}
void pop(struct stiva_node **p)
{
    if (*p == NULL)
        perror("pisici");
    struct stiva_node *tmp = *p;
    (*p) = (*p)->next;
}
int top(struct stiva_node *p)
{
    return p->info;
}
int is_empty(struct stiva_node *p)
{
    if (p == NULL)
        return 1;
    return -1;
}
void enq(struct coada *santinela, int elem)
{
    if (santinela->next == NULL)
    {
        santinela->next = malloc(sizeof(struct coada));
        santinela->next->chestie = elem;
        santinela->next->next = NULL;
        // printf("din function : %d\n",h->chestie);
    }
    else
    {
        struct coada *newn = malloc(sizeof(struct coada));
        newn->chestie = elem;
        newn->next = NULL;
        struct coada *c = santinela->next;
        while (c->next != NULL)
            c = c->next;
        c->next = newn;
    }
}
void TyperC(struct coada *c)
{
    while (c != NULL)
    {
        printf("din typerC: %d\n", c->chestie);
        c = c->next;
    }
}
void deq(struct coada *santinela)
{
    struct coada *tmp = santinela->next;
    santinela->next = santinela->next->next;
    free(tmp);
}
int first(struct coada *santinela)
{
    if (santinela->next != NULL)
        return santinela->next->chestie;
    return -1;
}
int last(struct coada *santinela)
{
    struct coada *c = santinela->next;
    if (santinela->next == NULL)
        return -1;
    else
    {
        while (c->next != NULL)
        {
            c = c->next;
        }
        return c->chestie;
    }
}
int empty(struct coada *santinela)
{
    if (santinela->next == NULL)
        return 1;
    return -1;
}
struct coada *init_q(struct coada *santi)
{
    santi = malloc(sizeof(struct coada));
    santi->next = NULL;
    return santi;
}
struct coada *functie(struct coada *santi)
{
    struct coada *sant_cpar;
    sant_cpar = init_q(sant_cpar);
    while (empty(santi) != 1)
    {
        if (first(santi) != -1)
        {
            if (first(santi) % 2 == 0)
            {
                enq(sant_cpar, first(santi));
                deq(santi);
            }
            else
                deq(santi);
        }
    }
    return sant_cpar;
}