#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

// réparation
typedef struct {
    char idgsm[10+1];
    char dateR[10+1];
    int prix;

}rep;

// téléphone
typedef struct {
    int cmarq;
    char mod[15+1];

}gsm;

// information de la prod
typedef struct {
    char idprod[15+1];
    char loc[15+1];
    int *prixT;
    float *prixM;
    int nbrep;
    rep **ppTrep;
    int nbgsm;
    gsm *pTgsm;

}prodgsm;

int introG(gsm **ppTgsm, int *pnbgsm);
int introR(rep ***pppTrep, int *pnbrep );
void libere(prodgsm **ppfab);
void stat(prodgsm *pfab); // Calcule et mets à jours la structure
void recap(prodgsm *pfab); // Affichage du récapitulatif des données entrées

int main() {
    // var error
    int eG = 0, eR = 0;
    char encoreGSM, encoreREP;

    prodgsm *pfab = NULL;

    pfab = (prodgsm *) malloc(sizeof(prodgsm));

    pfab->nbgsm = 0;
    pfab->nbrep = 0;
    pfab->pTgsm = NULL;
    pfab->ppTrep = NULL;

    // intro producteur
    printf("\n Introduction des parametres du producteur");
    printf("\n\n\t Identifiant du producteur : ");
    gets(pfab->idprod);
    printf("\n\n\t Localisation du producteur : ");
    gets(pfab->loc);

    do { // encodage des GSM
        eG = introG(&pfab->pTgsm, &pfab->nbgsm);
        if (eG == 0) {
            printf("\n\n Introduction des modeles de GSM");
            printf("\n * Encodage du modele No : %d", pfab->nbgsm);
            printf("\n\t\t ==> Code de la marque du GSM : ");
            scanf("%d",&pfab->pTgsm[pfab->nbgsm - 1].cmarq); getchar();
            printf("\n\n\t\t ==> Modele du GSM ");
            gets(pfab->pTgsm[pfab->nbgsm - 1].mod);
            printf("\n\n\t\t\t Un appareil (O/N) ? ");
            encoreGSM = getch();
        }
        else {
            printf("\n\n Memory Error");
        }


    }while (encoreGSM == 'O' || encoreGSM == 'o');
    do {// encodage des REP

        eR = introR(&pfab->ppTrep, &pfab->nbrep);
        if (eR == 0) {
            printf("\n\n Introduction des reparations");
            printf("\n * Encodage de la reparation No : %d", pfab->nbrep);
            printf("\n\t\t ==> Identifiant du GSM : ");
            gets(pfab->ppTrep[pfab->nbrep - 1]->idgsm);
            printf("\n\n\t\t ==> Date de traitement de la reparation : ");
            gets(pfab->ppTrep[pfab->nbrep - 1]->dateR);
            printf("\n\n\t\t ==> Montant de la reparation : ");
            scanf("%d",&pfab->ppTrep[pfab->nbrep - 1]->prix); getchar();
            printf("\n\n\t\t\t Une autre reparation  (O/N) ? ");
            encoreREP = getch();
        }
        else if (eR == 1) {
            printf("\n\n\n Erreur No : %d - Erreur memoire pointeur de pointeur", eR);
            getch();
            break;
        }
        else {
            printf("\n\n\n Erreur No : %d - Erreur memoire pointeur", eR);
            getch();
            break;
        }


    }while (encoreREP == 'O' || encoreREP == 'o');

    pfab->prixT = (int *)malloc(sizeof(int));
    pfab->prixM = (float *)malloc(sizeof(float));
    *(pfab->prixT) = 0;  // très important !

    stat(pfab);

    // Afficahge des stats et du récapitulatif
    recap(pfab);

    libere(&pfab);

    free(pfab);
    pfab = NULL;

    getch();
    return 0;
}


int introG(gsm **ppTgsm, int *pnbgsm ) {
    (*pnbgsm)++;

    *ppTgsm = (gsm *) realloc(*ppTgsm, *pnbgsm * sizeof(gsm));
    if (*ppTgsm == NULL) {
        return 1;
    }
    return 0;
}


int introR(rep ***pppTrep, int *pnbrep) {
    rep **ppTrepS = NULL;
    ppTrepS = *pppTrep; // Sauvegarde pointeur

    (*pnbrep)++;    // incrémentation nouvelle rep

    *pppTrep = (rep **) realloc(*pppTrep, *pnbrep * sizeof(rep *));
    if (!*pppTrep) {
        *pppTrep = ppTrepS;
        return 1;
    }

    (*pppTrep)[*pnbrep - 1] = (rep *) malloc(sizeof(rep));
    if (!(*pppTrep)[*pnbrep - 1]) return 2;

    return 0;
}

// Calcule des stats pour mises à jours de prixT et prixM dans la structure prodgsm
void stat(prodgsm *pfab) {
    for (int x = 0; x < pfab->nbrep; x++) {
        *pfab->prixT += pfab->ppTrep[x]->prix;
    }
    *(pfab->prixM) = (float)(*(pfab->prixT)); // pfab->nbgsm;
    *(pfab->prixM) =(*(pfab->prixM) / (float)(pfab->nbrep));
    printf("Nombre de gsm : %d", pfab->nbgsm);
    printf("Nombre de reparation : %d", pfab->nbrep);

}

void recap(prodgsm *pfab) {
    system("cls");
    printf("\t\t RECAPITULATIF \n");
    printf("\n* Identifint du producteur : %s ", pfab->idprod);
    printf("\n* Localisation du producteur : %s ", pfab->loc);
    printf("\n* Montant total des reparations : %d ", *(pfab->prixT));
    printf("\n* Montant moyen d'une reparation  : %.2f ", *(pfab->prixM));

    printf("\t\t\n\n Recapitulatif des GSM produits\n");
    for (int i = 0; i < pfab->nbgsm; i++) {
        printf("\n Modele No %d", i + 1);
        printf("\t\t\n ==> Code-Marque : %d", pfab->pTgsm[i].cmarq);
        printf("\t\t\n ==> Modele : %s", pfab->pTgsm[i].mod);
    }

    printf("\t\t\n\n Recapitulatif REPARATIONS\n");
    for (int i = 0; i < pfab->nbrep; i++) {
        printf("\n* Reparation No %d", i + 1);
        printf("\t\t\n Identifiant du GSM : %s", pfab->ppTrep[i]->idgsm);
        printf("\t\t\n Date de traitement : %s", pfab->ppTrep[i]->dateR);
        printf("\t\t\n Montant : %d", pfab->ppTrep[i]->prix);
    }
}


void libere(prodgsm **ppfab) {
     for (int i = 0; i < (*ppfab)->nbrep; i++) {
         free((*ppfab)->ppTrep[i]);
         // (*ppfab)->ppTrep[i] = NULL;
     }
    free((*ppfab)->ppTrep);
    // (*ppfab)->ppTrep = NULL;

    free((*ppfab)->pTgsm);
    // (*ppfab)->pTgsm = NULL;

    // *ppfab = NULL;

}
