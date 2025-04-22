#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Prochaine étape faire l'encodage des casernes (7_PStructure)

typedef struct {
    char date[10+1];
    int nbAMb, nbInc, nbDes, nbIterv;

}intervention;

typedef struct {
    char id[16+1];
    char loc[26+1];
    int nbAff, anciv, nbInterv;
    intervention **ppInterv;

}caserne;

typedef struct {
    char nom[20+1];
    caserne **ppCaserne;

}ville;

int main(void) {
    int nbEncoVille = 0;
    int nbEncoCaserne = 0;
    int nbEncoIntervention = 0;

    char encore;

    // Travail uniquement sur le moteur

    caserne **ppCaserneS = NULL;
    ville *pville;

    intervention **ppIntervS = NULL;
    caserne *pcaserne;

    nbEncoVille++;

    pville = (ville *) malloc(nbEncoVille * sizeof(ville));

    pville->ppCaserne = NULL;

    do {
        nbEncoCaserne++;

        pville->ppCaserne = (caserne **) realloc(pville->ppCaserne, nbEncoCaserne * sizeof(caserne *));

        pville->ppCaserne[nbEncoCaserne - 1] = (caserne *) malloc(sizeof(caserne));

        do {
            nbEncoIntervention++;

            pville->ppCaserne[nbEncoCaserne - 1]->ppInterv = (intervention **) realloc(pville->ppCaserne[nbEncoCaserne]->ppInterv, nbEncoIntervention * sizeof(intervention *));

            pville->ppCaserne[nbEncoCaserne - 1]->ppInterv[nbEncoIntervention - 1] = (intervention *) malloc(sizeof(intervention));

        }while (1);

    }while (1);

    return 0;
}