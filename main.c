#include <conio.h>
#include <stdlib.h>

typedef struct {
<<<<<<< HEAD
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
=======
    char date[10+1];
    int nbAMb, nbInc, nbDes, nbIterv;

}intervention;

typedef struct {
    char id[16+1];
    char loc[26+1];
    int nbAff, anciv, nbInterv;
    intervention **ppInterv;
>>>>>>> 6bd7da163576df185a7330683bc90ff15c378e4b

}caserne;

<<<<<<< HEAD
    pcaserne->nbIntervTab++;
    AllocInterv(&(pcaserne->ppInterv), &pcaserne->nbIntervTab);
    //getch();

    FreeAll(&(pcaserne));

    free(pcaserne);
    pcaserne = NULL;
=======
int main(void) {
    int nbEncoCaserne = 0;
    int nbEncoIntervention = 0;

    char encore;

    intervention **ppIntervS = NULL; // PPointeur de sécu
    caserne *pcaserne;    // Alias structure caserne

    nbEncoCaserne++;    // je prépare déjà pour la suite

    // malloc
    pcaserne = (caserne *) malloc(nbEncoCaserne * sizeof(caserne));
    if (!pcaserne) {
        return -1;
    }

    pcaserne->ppInterv = NULL;

    // Accès des interventions et gestion mémoire
    do {

        // Partie des interventions
        nbEncoIntervention++;

        // realloc
        pcaserne->ppInterv = (intervention **) realloc(pcaserne->ppInterv, nbEncoIntervention * sizeof(intervention *));
        if (!pcaserne->ppInterv) {
            nbEncoIntervention--;
            pcaserne->ppInterv = ppIntervS;

            printf("Out of memory\n");
            break;
        }

        // actualis ation ppointeur de sécu
        ppIntervS = pcaserne->ppInterv;

        // malloc
        pcaserne->ppInterv[nbEncoIntervention - 1] = (intervention *) malloc(sizeof(intervention));
        if (!pcaserne->ppInterv[nbEncoIntervention - 1]) {
            nbEncoIntervention--;
            break;
        }

        printf("\n===[Intervention %d]===\n ", nbEncoIntervention);

        printf("\n Entrez une date : ");
        scanf("%s", &pcaserne->ppInterv[nbEncoIntervention - 1]->date); getchar();

        printf("\n Entrer un nombre d'Amb : ");
        scanf("%d", &pcaserne->ppInterv[nbEncoIntervention - 1]->nbAMb); getchar();

        printf("\n Entrez un nombre d'Inc : ");
        scanf("%d", &pcaserne->ppInterv[nbEncoIntervention - 1]->nbInc); getchar();

        printf("\n Entrez un nombre de Des : ");
        scanf("%d", &pcaserne->ppInterv[nbEncoIntervention - 1]->nbDes); getchar();

        printf("\nEncore ?\n");
        encore = getch();

    }while (encore == 'o' || encore == 'O');

    for (int i = 0; i < nbEncoCaserne; i++) {
        printf("\n\n\t===[Caserne %d]===", nbEncoCaserne);
    }

>>>>>>> 6bd7da163576df185a7330683bc90ff15c378e4b

    // partie affichage Intervention
    for (int x = 0; x < nbEncoIntervention; x++) {
        printf("\n\n\t===[Interventions %d]===", nbEncoIntervention);

        printf("\n Date : %s",pcaserne->ppInterv[x]->date);
        printf("\n Amb : %d",pcaserne->ppInterv[x]->nbAMb);
        printf("\n Inc : %d",pcaserne->ppInterv[x]->nbInc);
        printf("\n Des : %d",pcaserne->ppInterv[x]->nbDes);
    }

    getch();    // Attente frappe utilisateur avant fermeture

    // Libération mémoire
    for (int x = 0; x < nbEncoIntervention; x++) {
        free(pcaserne->ppInterv[x]);
        pcaserne->ppInterv[x] = NULL;
    }

    free(pcaserne->ppInterv);
    pcaserne->ppInterv = NULL;

    free(pcaserne);
    pcaserne = NULL;

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