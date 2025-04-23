#include <conio.h>
#include <stdlib.h>
#include <stdio.h>

// Suite de 6_PStructure.c ou dans cet exo nous devons utiliser des fonctions
// On m'a fait remarqué que je n'avais pas mis '*' la ou il le fallait ce qui a causé ma perte :(

typedef struct {
    char date[11];
    int nbAmb, nbInc, nbDes, nbInterv;

}Intervention;

typedef struct {
    char id[16];
    char loc[26];
    int nbAff, anciv;
    int nbIntervTab;
    Intervention **ppInterv;

}Caserne;

int AllocInterv(Intervention ***pppInterv, int *pnbInterv);

void IntroInterv(Intervention *pInterv);

void FreeAll(Caserne **pplib);

int main() {
    int nbEncoCaserne = 0;
    Caserne *pcaserne = NULL;

    nbEncoCaserne++;
    pcaserne = (Caserne *) malloc(nbEncoCaserne * sizeof(Caserne));

    pcaserne->nbIntervTab = 0;
    pcaserne->ppInterv = NULL;


    //pcaserne->nbIntervTab++;

    AllocInterv(&(pcaserne->ppInterv), &pcaserne->nbIntervTab);

    //getch();

    IntroInterv(pcaserne->ppInterv[0]);

    FreeAll(&(pcaserne));



   // free(pcaserne);
    pcaserne = NULL;

    getch();
    return 0;

}


int AllocInterv(Intervention ***pppInterv, int *pnbInterv) {

    (*pnbInterv)++;

    *pppInterv = realloc(*pppInterv, *pnbInterv * sizeof(Intervention *));

    (*pppInterv)[*pnbInterv - 1] = malloc(sizeof(Intervention));

    return 1;
}

// trouver erreur de pourquoi tout casser

void IntroInterv(Intervention *pInterv) {
    char encore;
    

    do {
        scanf("%d", &pInterv->nbInterv); getchar();
        scanf("%d", &pInterv->nbAmb); getchar();
        scanf("%d", &pInterv->nbDes); getchar();
        scanf("%d", &pInterv->nbInterv); getchar();

        encore = getch();

    } while (encore == 'O' || encore == 'o');
}

void FreeAll(Caserne **pplib) {
    for (int x = 0; x < (*pplib)->nbIntervTab; x++) {
        free((*pplib)->ppInterv[x]);
        (*pplib)->ppInterv[x] = NULL;
    }
    free((*pplib)->ppInterv);
    free((*pplib)->ppInterv = NULL);

    free((*pplib));
    *pplib = NULL;
}