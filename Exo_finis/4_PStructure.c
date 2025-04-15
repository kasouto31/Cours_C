#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {
    char nom[10];
    int id;

}interv;

typedef struct {
    int id;
    interv **ppinterv;
}casrn;


int main(void) {
    casrn inter_casrn;
    int enco = 0;
    int i = 0;
    char encore;

    inter_casrn.ppinterv = NULL;


    do {
        enco++;

        inter_casrn.ppinterv = (interv **) realloc(inter_casrn.ppinterv, enco*sizeof(inter_casrn.ppinterv[0]));
        if (!inter_casrn.ppinterv) {
            enco--;
            break;
        }

        inter_casrn.ppinterv[enco - 1] = (interv *) malloc(sizeof(interv));

        printf("\nPlease enter a number: ");
        gets(inter_casrn.ppinterv[enco - 1]->nom);

        printf("\nPlease enter an id: ");
        gets(inter_casrn.ppinterv[enco - 1]->id);


        printf("\nEncore ?");
        encore = getch();

    }while(encore == 'o' || encore == 'O');

    for(i = 0; i < enco; i++) {
        printf("\n%s", inter_casrn.ppinterv[i]->nom);
    }



    getch();
    return 0;
}