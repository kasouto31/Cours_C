/*
* Fonctionnel, juste la fonction stat qui n'est pas faite
*/


#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {
    int nod;
    char datrdv[10+1];
    char timrdv[5+1];
}rdv;

typedef struct {
    char nom[15+1];
    char datdip[10+1];
    int nbrdv;
    rdv **ppTrdv;
}avo;

typedef struct {
    char idcab[15+1];
    char adcab[15+1];
    int nbav;           // Contient le nombre d'avocat
    float nbrdvM;
    avo *pTavo;
}cab;

int intrordv(rdv ***pppTrdv, int *pnbrdv);
void lib(cab **cabav);
void recap(cab *cabav);

int main(void) {
    char encoAvo, encoRdv;

    cab *cabav = NULL;
    avo *pTavoS = NULL; // Ponteur de sauvegarde pTavo

    cabav = (cab *) malloc(sizeof(cab));    // Ne pas oublier la sécu
    if (!cabav) {
        printf("\n\n Erreur allocation");
        return 1;
    }

    cabav->nbav = 0;
    cabav->pTavo = NULL;

    // Introduire les infos du cabinet
    printf("\t\tIntroduction du cabinet\n");
    printf("\n* Introduction de l'identifiant du cabinet : ");
    gets(cabav->idcab);
    printf("\n* Introduction de l'adresse du cabinet : ");
    gets(cabav->adcab);

    do {
        // Entrer les avocats
        cabav->nbav++;
        pTavoS = cabav->pTavo;
            // ne pas oublier de faire un pointeur de sécu
        cabav->pTavo = (avo *) realloc(cabav->pTavo, cabav->nbav * sizeof(avo));
        if (!cabav->pTavo) {
            printf("\n\n Erreur allocation");
            cabav->pTavo = pTavoS;
            cabav->nbav--;
            return 1;
        }
        // Sécuriser les pp dans chaque realloc
        cabav->pTavo[cabav->nbav - 1].ppTrdv = NULL;
        cabav->pTavo[cabav->nbav - 1].nbrdv = 0;

        printf("\n\n\t\t* Introduction des Avocats");
        printf("\n\n* Introduction du nom de l'avocat : ");
        gets(cabav->pTavo[cabav->nbav - 1].nom);
        printf("\n\n* Introduction de la date du diplome de lavocat : ");
        gets(cabav->pTavo[cabav->nbav - 1].datdip);

        // Mise à NULL pour chaque pp de chaque realloc
        printf("Voulez vous encore encoder un avocat ? O/N : ");
        encoAvo = getche();

    }while (encoAvo == 'O' || encoAvo == 'o');

    for (int i = 0; i < cabav->nbav; i++) {
        do {
            intrordv(&cabav->pTavo[i].ppTrdv, &cabav->pTavo[i].nbrdv);

            printf("\n\n\t Introduction des rendez-vous de l'avocat n %d", i + 1);
            printf("\n\n* Introduction du numero de dossier : ");
            scanf("%d",&cabav->pTavo[i].ppTrdv[cabav->pTavo[i].nbrdv - 1]->nod); getchar();
            printf("\n\n* Introduction des date du rendez-vous : ");
            gets(cabav->pTavo[i].ppTrdv[cabav->pTavo[i].nbrdv - 1]->datrdv);
            printf("\n\n* Introduction de l'heure du rendez-vous : ");
            gets(cabav->pTavo[i].ppTrdv[cabav->pTavo[i].nbrdv - 1]->timrdv);

            printf("\nVoulez-vous encore encoder un rendez-vous ? O/N : ");
            encoRdv = getche();
        }while (encoRdv == 'O' || encoRdv == 'o');
    }


    recap(cabav);

    lib(&cabav);

    getch();
    return 0;
}

int intrordv(rdv ***pppTrdv, int *pnbrdv) {
    rdv **ppTrdvS = NULL;       // Pointeur de sécu
    ppTrdvS = *pppTrdv;

    (*pnbrdv)++;

    *pppTrdv = (rdv **) realloc(*pppTrdv,*pnbrdv * sizeof(rdv *));
    if (!*pppTrdv) {
        printf("\n\n Erreur allocation realloc rdv");
        *pppTrdv = ppTrdvS;
        (*pnbrdv)--;
        return 1;
    }

    (*pppTrdv)[*pnbrdv - 1] = (rdv *) malloc(sizeof(rdv));
    if (!(*pppTrdv)[*pnbrdv - 1]) {
        printf("\n\n Erreur allocation");
        return 2;
    }
        // DEBUG
    // printf("intrordv : Aucun probleme memoire dectecter !");
    return 0;
}

void lib(cab **cabav) {
    for (int x = 0; x < (*cabav)->nbav; x++) {
        for (int y = 0; y < (*cabav)->pTavo[x].nbrdv; y++) {
            free((*cabav)->pTavo[x].ppTrdv[y]);
            (*cabav)->pTavo[x].ppTrdv[y] = NULL;
        }
        free((*cabav)->pTavo[x].ppTrdv);
        (*cabav)->pTavo[x].ppTrdv = NULL;
    }
    free((*cabav)->pTavo);
    (*cabav)->pTavo = NULL;

    free(*cabav);
    *cabav = NULL;
}

void recap(cab *cabav) {
    system("cls");
    printf("\t\t====== RECAPITULATIF ======\n\n");
    printf("* Identifiant du cabinet : %s\n", cabav->idcab);
    printf("* Adresse du cabinet      : %s\n", cabav->adcab);

    for (int x = 0; x < cabav->nbav; x++) {
        printf("\n--------------------------------------------------\n");
        printf("Avocat numero : %d\n", x + 1);
        printf("Nom de l'avocat       : %s\n", cabav->pTavo[x].nom);
        printf("Date du diplome       : %s\n", cabav->pTavo[x].datdip);

        for (int y = 0; y < cabav->pTavo[x].nbrdv; y++) {
            printf("\n  → Rendez-vous No %d :\n", y + 1);
            printf("    Numero de dossier : %d\n", cabav->pTavo[x].ppTrdv[y]->nod);
            printf("    Date du RDV       : %s\n", cabav->pTavo[x].ppTrdv[y]->datrdv);
            printf("    Heure du RDV      : %s\n", cabav->pTavo[x].ppTrdv[y]->timrdv);
        }
    }
    printf("\n==================================================\n");
}
