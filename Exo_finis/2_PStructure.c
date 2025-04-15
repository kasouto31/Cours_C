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

    char encore;
    int enco = 0;

    inter_casrn.pInterv = NULL; // important

    do {
        enco++;
        pIntervS = inter_casrn.pInterv;

        inter_casrn.pInterv = (interv *) realloc(inter_casrn.pInterv, enco * sizeof(interv));
        if (!inter_casrn.pInterv) {
            enco--;
            inter_casrn.pInterv = pIntervS;
            break;
        }
        // Dans ce programme nous pouvons entrer plusieurs fois les informations souhaités cependant un simple realloc à ses limites
        // Au bout d'un moment nous aurons donc un légé gros problème de mémoire
        printf("\nEntrer nom interv %d : ", enco);
        gets(inter_casrn.pInterv[enco - 1].nom);

        printf("\n\n Encore ? o/n");
        scanf("%c", &encore); getchar();

        // printf("%s\n", inter_casrn.pInterv->nom);

    }while(encore == 'o' || encore == 'O');

    for (int i = 0; i < enco; i++) {
        printf("%s\n\n", inter_casrn.pInterv[i].nom);
    }

    free(inter_casrn.pInterv);
    inter_casrn.pInterv = NULL;

    getch();
    return 0;
}