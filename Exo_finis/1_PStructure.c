#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {
    char nom[9+1];
    int id;
    float pourcentage;
}interv;

typedef struct {
    char nom[9+1];
    interv *pInterv;
}casrn;

int main(void) {
    casrn inter_casrn;
    interv *pIntervS = NULL;

    int enco = 0;

    inter_casrn.pInterv = NULL; // important

    do {
        enco++;
        pIntervS = inter_casrn.pInterv;
                        // Transtipage ; A qui on alloue la mémoire ; La taille à allouer
        inter_casrn.pInterv = (interv *) realloc(inter_casrn.pInterv, sizeof(interv));

        if (!inter_casrn.pInterv) {
            inter_casrn.pInterv = pIntervS;
            break;
        }
        // On ne pourra entrer qu'une seule fois un nom etc
        gets(inter_casrn.pInterv->nom);
        printf("%s\n", inter_casrn.pInterv->nom);

    }while(1);
    getch();
    return 0;
}
