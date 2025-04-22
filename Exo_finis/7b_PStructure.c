#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// Correction du prof :
    // Mise à NULL de certains pointeurs
    // utilisation des variables de comptage caserne et interv depuis la structure


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
    int nbEncoCaserne;
    caserne **ppCaserne;

}ville;

int main(void) {
    int nbEncoVille = 0;
    int tempo = 0;
    //int nbEncoCaserne = 0;
    //int nbEncoIntervention = 0;

    char encore;

    // Travail uniquement sur le moteur

    caserne **ppCaserneS = NULL;
    ville *pville;

    intervention **ppIntervS = NULL;


    nbEncoVille++;

    pville = (ville *) malloc(nbEncoVille * sizeof(ville));

    pville->ppCaserne = NULL;

    // Nombre de Caserne à 0
    pville->nbEncoCaserne = 0;

    do {

        pville->nbEncoCaserne++;

        pville->ppCaserne = (caserne **) realloc(pville->ppCaserne, pville->nbEncoCaserne * sizeof(caserne *));

        pville->ppCaserne[pville->nbEncoCaserne - 1] = (caserne *) malloc(sizeof(caserne));

        pville->ppCaserne[pville->nbEncoCaserne - 1] = NULL;

        // Nombre d'Intervention
        tempo = pville->ppCaserne[pville->nbEncoCaserne - 1]->nbInterv = 0;
        do {
            // Utilisation d'une var "tempo" de type int pour éviter que ça fasse des lignes trop longue
            tempo++;

            pville->ppCaserne[tempo - 1]->ppInterv = (intervention **) realloc(pville->ppCaserne[tempo]->ppInterv, tempo * sizeof(intervention *));

            pville->ppCaserne[tempo - 1]->ppInterv[tempo - 1] = (intervention *) malloc(sizeof(intervention));

        }while (1);

    }while (1);

    return 0;
}