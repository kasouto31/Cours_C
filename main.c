#include <conio.h>
#include <stdlib.h>

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

int AllocInterv(Intervention ***pppInterv, int *nbInterv);

void FreeAll(Caserne **pplib);

int main() {
    int nbEncoCaserne = 0;
    nbEncoCaserne++;
    Caserne *pcaserne;

    pcaserne = (Caserne *) malloc(nbEncoCaserne * sizeof(Caserne));

    pcaserne->nbIntervTab = 0;
    pcaserne->ppInterv = NULL;


    pcaserne->nbIntervTab++;
    AllocInterv(&(pcaserne->ppInterv), &pcaserne->nbIntervTab);
    //getch();

    FreeAll(&(pcaserne));

    free(pcaserne);
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

void FreeAll(Caserne **pplib) {
    for (int x = 0; x < (*pplib)->nbIntervTab; x++) {
        free((*pplib)->ppInterv);
        (*pplib)->ppInterv = NULL;
    }
    free((*pplib));
    *pplib = NULL;
}