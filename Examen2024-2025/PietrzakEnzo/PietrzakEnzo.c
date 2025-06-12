// Examen 2025 PAP Pietrzak Enzo

#include <stdio.h>
#include <stdlib.h>
#include <conio.h>

typedef struct {
    char noc[15+1];
    int indP;
    int indA;
    char date[10+1];
    int *cons;
}Rel;

typedef struct {
    char nor[5+1];
    char rue[25+1];
    int cp;
    int nbRel;
    Rel *pTRel;
}Adr;

typedef struct {
    char id[15+1];
    int nbemp;
    float *consoM;
    int nbAdr;
    Adr **ppTAdr;
}SocGaz;

int introadr(Adr ***pppTAdr, int *pnbAdr);
int introrel(Rel **ppTRel, int *pnbRel);
void recapall(SocGaz *SG);
void statconso(const SocGaz *SG);
void freemem(SocGaz **SG);


int main(void)
{
    SocGaz *SG = NULL;
    SG = (SocGaz *) malloc(sizeof(SocGaz));
    // Sécurisation memoire
    if (!SG) {
        return 1;
    }
    SG->ppTAdr = NULL;

    SG->consoM = (float *) malloc(sizeof(float));

    printf("\t\t\t==> Introduction des parametres de la societe");
    printf("\n\t -> Identifiant : ");
    gets(SG->id);
    printf("\n\t -> Nombre d'employes : ");
    scanf("%d", &SG->nbemp); getchar();

    // Appel de la fonction introAdr
    introadr(&SG->ppTAdr, &SG->nbAdr);

    // Calcul des stats avec maj dans structure
    statconso(SG);

    recapall(SG);

    freemem(&SG);

    getch();
    return 0;
}

int introadr(Adr ***pppTAdr, int *pnbAdr) {
    Adr **ppTAdrS = NULL;
    char encoAdr;
    *pnbAdr = 0;

    do {
        // realloc + secu
        ppTAdrS = *pppTAdr;
        (*pnbAdr)++;        // Incrémentation du nombre d'adresse (tailel du tableau)
        *pppTAdr = (Adr **) realloc(*pppTAdr, *pnbAdr * sizeof(Adr *));
        if (!(*pppTAdr)) {
            (*pnbAdr)--;
            *pppTAdr = ppTAdrS;
            printf("\n\t introadr : ERREUR REALLOC");
            getch();
            return 1;
        }

        //malloc + secu
        (*pppTAdr)[*pnbAdr - 1] = (Adr *) malloc(sizeof(Adr));
        if (!(*pppTAdr)[*pnbAdr - 1]) {
            (*pnbAdr)--;
            printf("\n\t introadr : ERREUR MALLOC");
            getch();
            return 2;
        }
        printf("\n\n\t\t\t ==> Introdution des lieux de releves");
        printf("\n\t\t => Adresse No %d", *pnbAdr); // verifier si pnbAdr à 0 avant
        printf("\n\t -> rue : ");
        gets((*pppTAdr)[*pnbAdr - 1]->rue);
        printf("\n\t -> No : ");
        gets((*pppTAdr)[*pnbAdr - 1]->nor);
        printf("\n\t -> cp : ");
        scanf("%d", &(*pppTAdr)[*pnbAdr - 1]->cp); getchar();

        // Initialisation du nombre de relevé et sécurisation du pointeur pTRel pour chaque élément du tableau
        (*pppTAdr)[*pnbAdr - 1]->nbRel = 0;
        (*pppTAdr)[*pnbAdr - 1]->pTRel = NULL;

        introrel(&(*pppTAdr)[*pnbAdr - 1]->pTRel, &(*pppTAdr)[*pnbAdr - 1]->nbRel);
        printf("\n\tEncore une Adresse ? (o/n)");
        encoAdr = getche();
    }while(encoAdr == 'O' || encoAdr == 'o');



    return 0;
}

int introrel(Rel **ppTRel, int *pnbRel) {
    Rel *pTRelS = NULL;
    char encoRel;

    do {
        // Alloc mem + secu
        pTRelS = *ppTRel;
        (*pnbRel)++;
        *ppTRel = (Rel *) realloc(*ppTRel, *pnbRel * sizeof(Rel));

        if (!(*ppTRel)) {
            *ppTRel = pTRelS;       // sauvegarde du pp
            (*pnbRel)--;                // Décrémentation du nombre de relevé
            printf("\n\t* introrel : ERREUR REALLOC");
            return 3;
        }

        (*ppTRel)[*pnbRel - 1].cons = NULL;
        (*ppTRel)[*pnbRel - 1].cons = (int *) malloc(sizeof(int));
        if (!(*ppTRel)[*pnbRel - 1].cons) {
            printf("\n\t* introrel : ERREUR MALLOC CONS");
            return 4;
        }
        *(*ppTRel)[*pnbRel - 1].cons = 0;


        // phase d'encodage des relevés
        printf("\n\n\t\t\t ==> Introduction des releves");
        printf("\n\t\t => Releve numero %d", *pnbRel);
        printf("\n\t =>Date : ");
        gets((*ppTRel)[*pnbRel - 1].date);
        printf("\n\t -> Numero compteur : ");
        gets((*ppTRel)[*pnbRel - 1].noc);
        printf("\n\t -> Index precedent : ");
        scanf("%d", &(*ppTRel)[*pnbRel - 1].indP); getchar();
        printf("\n\t -> Index actuel : ");
        scanf("%d", &(*ppTRel)[*pnbRel - 1].indA); getchar();


        if ((*ppTRel)[*pnbRel - 1].indP > (*ppTRel)[*pnbRel - 1].indA) {

            printf("\nERREUR - La consommation ne peut etre negative\n");

            do {
                printf("\n\t -> Index precedent : ");
                scanf("%d", &(*ppTRel)[*pnbRel - 1].indP); getchar();
                printf("\n\t -> Index actuel : ");
                scanf("%d", &(*ppTRel)[*pnbRel - 1].indA); getchar();
            }while((*ppTRel)[*pnbRel - 1].indP > (*ppTRel)[*pnbRel - 1].indA);
        }


        printf("\n\tEncore un releve ? (o/n)");
        encoRel = getche();

    }while(encoRel == 'O' || encoRel == 'o');


    return 0;
}

void statconso(const SocGaz *SG) {
    int totalConso = 0;
    int totalRel = 0;

    for (int x = 0; x < SG->nbAdr; x++) {
        for (int y = 0; y < SG->ppTAdr[x]->nbRel; y++) {
            int diff = SG->ppTAdr[x]->pTRel[y].indA - SG->ppTAdr[x]->pTRel[y].indP;
            *SG->ppTAdr[x]->pTRel[y].cons = diff;
            totalConso += diff;
            totalRel++;
        }
    }
    if (totalRel > 0)
        *SG->consoM = (float) totalConso / totalRel;
    else
        *SG->consoM = 0;

}

void recapall(SocGaz *SG) {

    system("cls"); // Pour que ça soit plus propre et lisible

    printf("\n\t\t ==> Parametres du fournisseur\n");
    printf("\n\t -> Identifiant : %s", SG->id);
    printf("\n\t -> Nombre d'employes : %d", SG->nbemp);
    printf("\n\t -> Nombre total d'adresses gerees : %d", SG->nbAdr);
    printf("\n\t -> Consommation moyenne par compteur : %.2f", *SG->consoM);  // Faire la maj depuis la fonction "statconso"

    // Affichage des adresses puis ses releves etc
    printf("\n\t\t ==> Liste des releves\n");

    for (int i = 0; i < SG->nbAdr; i++) {
        printf("\n\t -> Adresse No %d\n", i);
        printf("\n\t -> rue : %s", SG->ppTAdr[i]->rue);
        printf("\n\t -> No : %s", SG->ppTAdr[i]->nor);
        printf("\n\t -> cp : %d", SG->ppTAdr[i]->cp);

        for (int j = 0; j < SG->ppTAdr[i]->nbRel; j++) {
            printf("\n\t\t* Releve No %d/%d\n", j, SG->ppTAdr[i]->nbRel);
            printf("\n\t\t\t* Date : %s", SG->ppTAdr[i]->pTRel[j].date);
            printf("\n\t\t\t* Index precedent : %d", SG->ppTAdr[i]->pTRel[j].indP);
            printf("\n\t\t\t* Index actuel : %d", SG->ppTAdr[i]->pTRel[j].indA);
        }
    }
    printf("\n\nAppuyez sur une touche pour continuer...");
    getch();

}

void freemem(SocGaz **ppSG) {
    for (int x = 0; x < (*ppSG)->nbAdr; x++){
        for (int y = 0; y < (*ppSG)->ppTAdr[x]->nbRel; y++) {
            free((*ppSG)->ppTAdr[x]->pTRel[y].cons);
            (*ppSG)->ppTAdr[x]->pTRel[y].cons = NULL;
        }
        free((*ppSG)->ppTAdr[x]->pTRel);
        (*ppSG)->ppTAdr[x]->pTRel = NULL;

        free((*ppSG)->ppTAdr[x]);
        (*ppSG)->ppTAdr[x] = NULL;
    }
    free((*ppSG)->ppTAdr);
    (*ppSG)->ppTAdr = NULL;

    free((*ppSG)->consoM);
    (*ppSG)->consoM = NULL;

    free(*ppSG);
    *ppSG = NULL;
}

