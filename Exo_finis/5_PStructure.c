#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {
    char nom[10];
    char id[10];

}interv;

typedef struct {
    char id[10];
    interv **ppinterv;

}casrn;


int main(void) {
    casrn inter_casrn;
    int enco = 0;
    int i = 0;
    char encore;

    interv **ppintervS = NULL;
    //interv *pintervS = NULL;    // Inutile car on ne risque pas de perdre nos données avec un malloc

    inter_casrn.ppinterv = NULL;

    do {
        enco++;

        // Lors de la création du tableau de pointeurs
        //ppintervS = inter_casrn.ppinterv; // Non nécessaire

        inter_casrn.ppinterv = (interv **) realloc(inter_casrn.ppinterv, enco * sizeof(interv*));   // taille d'un pointeur vers interv
        if (!inter_casrn.ppinterv) {
            inter_casrn.ppinterv = ppintervS;   // Retour arrière en cas d'erreur
            enco--;
            break;
        }


        ppintervS = inter_casrn.ppinterv;
        // On arrive dans le tableau de pointeurs
        inter_casrn.ppinterv[enco - 1] = (interv *) malloc(sizeof(interv));
        if (!inter_casrn.ppinterv[enco - 1]) {
            //inter_casrn.ppinterv[enco - 1] = pintervS;
            enco--;
            break;
        }


        printf("\nIntervention %d:\n ", enco);
        printf("\n Entrez un nom : ");
        scanf("%s", &inter_casrn.ppinterv[enco - 1]->nom); getchar();

        printf("\n Entrez un id : ");
        scanf("%s", &inter_casrn.ppinterv[enco - 1]->id); getchar();


        printf("\nEncore ?");
        encore = getch();

    }while(encore == 'o' || encore == 'O');

    printf("\n\n\t =====[Sommaire]===== :");

    for(i = 0; i < enco; i++) {
        printf("\n\t %s", inter_casrn.ppinterv[i]->nom);
        printf("\n\t %s\n", inter_casrn.ppinterv[i]->id);
    }

    // Libération de la mémoire :
    for (i = 0; i < enco; i++) {
        free(inter_casrn.ppinterv[i]);
        inter_casrn.ppinterv[i] = NULL;
    }
    free(inter_casrn.ppinterv);
    inter_casrn.ppinterv = NULL;

    getch();
    return 0;
}