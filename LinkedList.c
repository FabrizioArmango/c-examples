#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
/*
	12/05/15
	Fabrizio Armango
*/

/// Dichiarazione struttura
typedef struct list{
    int num;
    char lettera;
    struct list* next;
} lista;

/// Dichiarazione funzioni
lista *crea_lista(lista *L);
char assegna_lettera(int n);
int lunghezza_lista(lista *L);
void stampa_lista(lista *L);
int occorrenze_di(int n, lista* L);
void stampa_caratteri_inversi(lista *L);
void verifica_pari(lista* L, int n);
void massimi_lista(int **num, char **lettera, lista *L);
lista *copia_lista(lista *L);
lista *lista_per_scalare(lista *L, int n);
void concatena(lista** L, lista* M);
lista *nuova_coda (lista *list, int new);
void isDecrescente(lista *L);

int main () {
    int o;
    int max_num = 0;
    int *m = &max_num;
    char *c;
    lista *L, *M;

    L = crea_lista(L);
    printf("La lista ha %d elementi.\n",lunghezza_lista(L));

    printf("Stampa la lista L\n");
    stampa_lista(L);

    ///Conto occorrenze
    printf("Inserisci il numero da ricercare per contarne le occorrenze\n");
    scanf("%d", &o);
    printf("Il numero %d si presenta %d volte\n", o, occorrenze_di(o, L));

    printf("Stampa lista inversa \n");
    stampa_caratteri_inversi(L);

    verifica_pari(L, 0);

    massimi_lista(&m, &c, L);
    printf("I puntatori al massimo carattere e numero puntano rispettivamente a: %d, %c\n", *m, *c);

    M = copia_lista(L);

    printf("Stampa la lista M copiata da L\n");
    stampa_lista(M);

    L = lista_per_scalare(L, 3);

    printf("Stampa la lista L dopo averla moltiplicata per 3\n");
    stampa_lista(L);

    concatena(&L, M);

    printf("Stampa la lista L dopo averla concatenata ad M\n");

    stampa_lista(L);

    isDecrescente(M);

    return 0;
}


lista *crea_lista(lista *L){
    int x = 0;
        printf("Inserisci l'elemento nella lista (0 per terminare): \n\t>");
        scanf("%d", &x);
        if (x > 0) {
            L = (lista*) malloc (sizeof(lista));
            L->num = x;
            L->lettera = assegna_lettera(x);
            printf("\n [%d] -> %c\n\n", x, L->lettera);
            L->next = crea_lista(L->next);
        }   else
            L = NULL;
        return L;
}

char assegna_lettera(int n) {
    return 'a' + ((n-1)%26);
}

int lunghezza_lista(lista* L)   {
    if (L != NULL)
        return 1+ lunghezza_lista(L->next);
    else
        return 0;
}

void stampa_lista(lista *L){
    if (L!= NULL){
        printf("%d - %c -> \n", L->num, L->lettera);
        stampa_lista(L->next);
    }   else
        printf("NULL;\n");
}

int occorrenze_di(int n, lista* L) {
    if (L != NULL)  {
        if (L->num == n)
            return 1 + occorrenze_di (n, L->next);
        else
            return 0 + occorrenze_di (n, L->next);
    }
    return 0;
}

void stampa_caratteri_inversi(lista *L){
    if (L!= NULL){    	
        stampa_caratteri_inversi(L->next);        
        printf("%d - %c -> \n", L->num, L->lettera);
    }   else
        printf("NULL;\n");
}

void verifica_pari(lista *L, int n){
    if (L != NULL){
        if (L->num%2 == 0)
            verifica_pari(L->next, n+1);
        else
            printf("La lista contiene almeno un elemento che non e' pari\n");
    }   else    {
        printf("La lista contiene %d elementi che sono tutti pari\n", n);
    }
}

void massimi_lista(int **num, char **lettera, lista *L)    {
    if (L != NULL)  {
        if(**num < L->num)   {
            *num = &(L->num);
            *lettera = &(L->lettera);
        }
        massimi_lista(num, lettera, L->next);
    }
}

lista *copia_lista(lista *L)    {
    lista *M;
    if (L != NULL)  {
        M = (lista*) malloc (sizeof(lista));
        M->num = L->num;
        M->lettera = L->lettera;
        M->next = copia_lista(L->next);
        //printf("< print to debug >\n");
        //stampa_lista(M);
        return M;
    }
    M = NULL;
    return M;
}

lista *lista_per_scalare(lista *L, int n)    {
    if (L != NULL)  {
        L->num = (L->num) * n;
        L->lettera = assegna_lettera(L->num);
        L->next = lista_per_scalare(L->next, n);
        return L;
    }
    L = NULL;
    return L;
}

void concatena(lista** L, lista *M)  {
    while (M!=NULL){
        *L = nuova_coda (*L, M->num);
        M = M->next;
    }
}


lista *nuova_coda (lista *list, int new)   {
    //lista *coda;
    lista *ultimo;
    lista *testa = list;//(lista *)malloc(sizeof(lista));
    ultimo =  (lista *)malloc(sizeof(lista));
    ultimo->next = NULL;
    ultimo->num = new;
    ultimo->lettera = assegna_lettera(new);
    while (list->next!= NULL)
        list = list->next;
    list->next = ultimo;
    return testa;
}

//  ## Stabilire se la lista L è decrescente (o non crescente).

void isDecrescente(lista *L){
    lista* next = L->next;
    if (L!=NULL)    {
        if(next!= NULL && L->num > next->num)
            isDecrescente(L->next);
        else {
            if (next == NULL)
                printf("La lista e' decrescente");
            else
                printf("La lista e' non decrescente");
        }
    }
}
