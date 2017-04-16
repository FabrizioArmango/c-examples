//#########################################
//                                        #
//               Rubrica                  #
//                                 v0.45  #
//#########################################
//#########################################
// 02/05/15
// Fabrizio Armango
//###################

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* <<<<<<<<<<< Definizione di strutture     */
typedef struct {
        char via[30];
        char citta[20];
        char cap[10];
} address;

typedef struct {
    int	    giorno;
    int     mese;
    int 	anno;
} date;


typedef struct {
   char     cognome[30];
   char     nome[30];
   char     telefono[30];
   char     cellulare[30];
   address  indirizzo;
   date     data;
} persona;
/* >>>>>>>>>>>  */


/* <<<<<<<<<<< Definizione di funzioni     */
persona* init_rubrica();
void NuovaPersona(persona* pt, int numPersone, int c);
void CompilaPersona(persona* who);
void clearConsole(void);
void alert(char* err);
void printPersona(persona* who);
void OrdinaRubrica(persona* what, int num);
void Ricerca(char input[], char* r, persona* rubrica, int numPersone);
void SaveFile(char input[], persona* rubrica, int numPersone);
//int ReadFile(char input[], persona* p);
int ReadFile(char input[], persona* p, int numPersone, int* init);
void StampaRubrica(persona* what, int numPersone);
/* >>>>>>>>>>>  */

void headerf()   {
    int i = 0;
    printf("\n");
    for(i=0; i<80; i++)
        printf("-");
}
void header()   {
    int i = 0;
    for(i=0; i<40; i++)
        printf("- ");
}

int menu()    {
    int i;
    int flag = 0;
    headerf();
    printf("\n< \t MENU RUBRICA \t \t \t \n\t Seleziona un'operazione \t >\n");
    headerf();

    char * operazioni[8];
    operazioni[0] = "Inizializzazione rubrica (inserimento due persone)";
    operazioni[1] = "Ordinamento delle persone inserite dove la prima \n \t\tchiave dell'ordinamento e' il cognome e la seconda e' il nome";
    operazioni[2] = "Inserimento di una nuova persona";
    operazioni[2] = "Inserimento di una nuova persona";
    operazioni[3] = "Ricerca di una persona per cognome";
    operazioni[4] = "Ricerca di una persona per citta'";
    operazioni[5] = "Ricerca di una persona il cui CAP contiene una sequenza \n \t\tdi cifre inserite dall'utente \n \t\t(ad es. i CAP che iniziano con 90).";
    operazioni[6] = "Visualizzazione dell'intera rubrica ordinata";
    operazioni[7] = "Salva Rubrica su file";
    operazioni[8] = "Apri Rubrica da file";
    for (i=0; i < 9; i++){
        printf("\n  [%d]\t %s \n", i+1, operazioni[i]);
        if (i!= 8)
            header();
    }
    headerf();
        printf("    > ");
        scanf("%d", &flag);
        if (flag == 1 || flag == 2 || flag == 3 || flag == 4 || flag == 5 || flag == 6 || flag == 7 || flag == 8 || flag == 9){

        }
            //flag = 1;
        else
            flag = 0;
    return flag;
}

int main (void) {

    persona* rubrica;
    int numPersone = 0;
    int i = 0;
    int scelta;
    int init = 0;

    char input[50];
    selection_menu:

    scelta = menu();

    if (scelta==9){
        //Scrivi su file
        alert("Inserisci il nome del file da cui caricare la rubrica (nomefile.txt)");
        printf("\n\n\n \t > ");
        fflush(stdin);
        gets(input);
        init = ReadFile(input, rubrica, numPersone, &init);
        goto selection_menu;
    }

    if (init == 1){
        if (scelta == 1)    {
            alert("Hai gia' inizializzato la rubrica.");
        }   else if (scelta==2)  {
            clearConsole();
            printf("\t \t < Elenco in ordine alfabetico per cognome e nome. >");
            OrdinaRubrica(rubrica, numPersone);
            header();
        }   else if (scelta==3)  {
            alert("Inserisci nuova persona.");
            //printf("\n\n\n \t >");
            NuovaPersona(rubrica, numPersone++, 1);
            header();
        }   else if (scelta==4){
            alert("Inserisci il cognome per la ricerca.");
            printf("\n\n\n \t >");
            fflush(stdin);
            gets(input);
            Ricerca(input,"cognome",rubrica,numPersone);
        }   else if (scelta==5){
            alert("Inserisci la citta' per la ricerca.");
            printf("\n\n\n \t >");
            fflush(stdin);
            gets(input);
            Ricerca(input,"citta",rubrica,numPersone);
        }   else if (scelta==6){
            alert("Inserisci il CAP per la ricerca.");
            printf("\n\n\n \t >");
            fflush(stdin);
            gets(input);
            Ricerca(input,"cap",rubrica,numPersone);
        }   else if (scelta==7){
            StampaRubrica(rubrica, numPersone);
        }   else if (scelta==8){
            //Scrivi su file
            alert("Come vuoi salvare il file? (nomefile.txt)");
            printf("\n\n\n \t > ");
            fflush(stdin);
            gets(input);

            SaveFile(input, rubrica, numPersone);
        }   else {
            alert("Il numero inserito non e' valido. Riprova");
        }
    }   else    {

        if (scelta == 1)    {
            clearConsole();
            rubrica = init_rubrica(&init);
            for(i=0; i<2; i++){
                printf("\n\t\t< Compila i campi della Persona %d >\n\n",i+1);
                CompilaPersona(&rubrica[i]);
                header();
            }
            numPersone = 2;
        }   else if (scelta == 0)   {
            alert("Il numero inserito non e' valido. Riprova");
        }   else
            alert("Devi prima inizializzare la rubrica.");

    }

    goto selection_menu;
    return 0;
}

int ReadFile(char input[], persona* p, int numPersone, int* init) {
    int i;
    FILE* fp;
    //persona* p = (persona*)malloc(sizeof(persona));
    int idx = 0;
    //int nPers = 0;
    int nTot = 0;
    int fine = 0;
    char cache[50];
    char* temp = p;

    persona* pTemp;
    //p = (persona*)malloc(sizeof(persona)*1);
    //0 = cognome
    //1 = nome
    //2 = data
    //3 = telefono
    //4 = cellulare
    //5 = indirizzo

    fp = fopen(input,"rb"); // read mode

    if( fp == NULL )    {
        perror("Error while opening the file.\n");
        header();
      return 0;
    }   else  {
        if (*init == 1) {
            printf("Gia' inizializzata\n");
        }   else    {
            printf("Nuova inizializzazione\n");
            p = init_rubrica(init);
        }

        pTemp = (persona* ) malloc(sizeof(persona));
        while (fread(pTemp,sizeof(persona),1,fp)>0)    {
            NuovaPersona(p, ++numPersone, 0);
            p[numPersone]=*pTemp;
        }


        StampaRubrica(p, numPersone);
        fclose(fp);
        header();
        return 1;
    }
}

void SaveFile(char input[], persona* rubrica, int numPersone) {
    FILE* fp;
    int i=0;

    clearConsole();

    headerf();
    printf("Salvataggio di: %s\n", input);
    headerf();
    fp = fopen(input, "ab");

    //for (i; i<numPersone; i++){
        fwrite(rubrica,sizeof(persona),numPersone,fp);
    //}

    fclose(fp);

    printf("\n");
    header();
    system("pause");
}

void Ricerca(char input[], char* r, persona* rubrica, int numPersone)  {

    int i=0;
    char *str1;

    clearConsole();
    headerf();
    printf("Ricerca per %s:\t%s\n", r, input);
    headerf();

    if (r == "citta")
        str1 = rubrica[i].indirizzo.citta;

    else if (r == "cognome")
        str1 = rubrica[i].cognome;

    else if (r == "cap")
        str1 = rubrica[i].indirizzo.cap;

    for (i; i<numPersone; i++)
        if ((str1, input)== 0)
            printPersona(&rubrica[i]);

    printf("\n");
    header();
    system("pause");
}

void clearConsole(void) {
    int i=0;
    for(i; i<27; i++)
        printf("\n");
}

void alert(char* err)   {
    clearConsole();
    printf("\t<\t!\t> %s \n\n\n\n", err);
    system("pause");
}

void printPersona(persona* who){
    printf("\n\n\n\t Cognome:\t%s \n",who->cognome);
    printf("\t Nome:\t\t%s \n",who->nome);
    printf("\t Nato il:\t%d/%d/%d \n",who->data.giorno, who->data.mese, who->data.anno);
    printf("\t Via: \t\t%s \n",who->indirizzo.via);
    printf("\t Citta: \t%s \n",who->indirizzo.citta);
    printf("\t CAP: \t\t%s \n",who->indirizzo.cap);
    printf("\t Telefono: \t%s \n",who->telefono);
    printf("\t Cellulare: \t%s \n",who->cellulare);
}

void OrdinaRubrica(persona* what, int num)    {

    persona t;
    int i=0;
    int j=0;

    for (i=1; i<num; i++)
        for (j=1; j<num; j++)
             if (strcmp(what[j - 1].cognome, what[j].cognome) > 0) {
                    if (strcmp(what[j - 1].nome, what[j].nome) > 0) {
                        t = what[j - 1];
                        what[j - 1] = what[j];
                        what[j] = t;
                    }
            }

    printf("\n\n");
    printf("Numero di persone inserite: %d", num);

    StampaRubrica(what, num);
    for (i=0; i<num; i++)
        printPersona(&what[i]);
}

void StampaRubrica(persona* what, int numPersone){
    int i;
    for (i=0; i<numPersone; i++)
        printPersona(&what[i]);

    system("pause");
}

void NuovaPersona(persona* pt, int numPersone, int c){
    pt = (persona*) realloc (pt,sizeof(persona)*(numPersone+1));
    if (c == 1){
        headerf();
        printf("Compila i campi per il nuovo inserimento.\n");
        headerf();
        printf("\t\t\t\t\t\t <\tAggiunte: %d\t>", numPersone);
        CompilaPersona(&pt[numPersone]);
    }

}

void CompilaPersona(persona* who)   {
    fflush(stdin);

    printf("\n > Cognome: ");
    gets(who->cognome);


    printf("\n > Nome: ");
    gets(who->nome);

    printf("\n > Data di nascita ");
    printf("\n \t - GG/MM/AA: ");
    scanf("%d/%d/%d", &who->data.giorno, &who->data.mese, &who->data.anno);
    fflush(stdin);

    printf("\n > Telefono: ");
    gets(who->telefono);

    printf("\n > Cellulare: ");
    gets(who->cellulare);

    printf("\n > Indirizzo \n \t > Via: ");
    gets(who->indirizzo.via);

    printf("\n \t > Citta': ");
    gets(who->indirizzo.citta);

    printf("\n \t > CAP: ");
    gets(who->indirizzo.cap);

}

persona* init_rubrica(int* init)  {
    persona* pt;
    // prende lo spazio nell'heap per la dimensione di un array di 2 persona
    pt = (persona*)malloc(sizeof(persona)*2);
    *init = 1;
    return pt;
}
