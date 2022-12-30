//
// Created by Maxime Vennin on 27/12/2022.
//
#include "cartestresors.h"
#include <stdio.h>

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

typedef struct { //structure temporaire pour test
    char signe;
    int decouvert; // 1 s'il a été découvert,0 sinon
}t_tresor;

typedef struct {
    //t_case *position_pion; // Pointeur vers la case où le pion se trouve
    int num_pion;
    char nom[15];
    char couleur;
    int arrivee; // Variable booléenne indiquant si le pion a atteint sa destination
    int deja_deplace; // Variable booléenne indiquant si le pion a déjà été déplacé dans le tour en cours
    t_tresor tresors[12];// tableau stockant tous les tresors du joueur, les cases en trop sont des '0' et on en met 12 car on a au max 12 tresors par joueur
    int num_tresor_pion;//numéro du trésor en cours de recherche
}t_pion;

int verifunique(t_pion *pionVerif, t_pion *pionun, t_pion *piondeux, t_pion *piontrois, const int *iteration){ //En para : le signe du pion dont on vérifie que le signe est diff des autres puis les autres pions.
    int reccurence=0;
    for (int i = 0; i < 12; ++i) {//vérifie dans les tableaux de tous les autres pions
        for (int j = 0; j < 12; ++j) {
            if (pionVerif->tresors[*iteration].signe == pionun->tresors[i].signe || pionVerif->tresors[*iteration].signe == piondeux->tresors[i].signe || pionVerif->tresors[*iteration].signe == piontrois->tresors[i].signe){
                ++reccurence;
            }
        }

    }
    for (int i = 0; i < *iteration; ++i) {//vérifie dans le pion à vérifier si on a pas déjà le même signe de trésor
        if (pionVerif->tresors[*iteration].signe == pionVerif->tresors[i].signe){
            ++reccurence;
        }
    }
    return reccurence;
}

void DistributionCartes(const int *nbjoueurs, t_pion *pion1, t_pion *pion2, t_pion *pion3, t_pion *pion4){
    srand(time(NULL));
    switch (*nbjoueurs) {
        case 2:// 2 joueurs avec chacun 12 cartes trésor
            for (int i = 0; i < 12; ++i) {
                do {
                    pion1->tresors[i].signe= 65+rand()%24;
                } while (verifunique(pion1,pion2,pion3,pion4,&i)>0);
            }
            for (int i = 0; i < 12; ++i) {
                do {
                    pion2->tresors[i].signe = 65+rand()%24;
                } while (verifunique(pion2,pion1,pion3,pion4,&i)>0);
            }
            break;
        case 3:// 3 joueurs avec chacun 8 cartes trésor
            for (int i = 0; i < 8; ++i) {
                do {
                    pion1->tresors[i].signe= 65+rand()%24;
                } while (verifunique(pion1,pion2,pion3,pion4,&i)>0);
            }
            for (int i = 0; i < 8; ++i) {
                do {
                    pion2->tresors[i].signe= 65+rand()%24;
                } while (verifunique(pion2,pion1,pion3,pion4,&i)>0);
            }
            for (int i = 0; i < 8; ++i) {
                do {
                    pion3->tresors[i].signe= 65+rand()%24;
                } while (verifunique(pion3,pion2,pion1,pion4,&i)>0);
            }
            break;
        case 4:// 4 joueurs avec chacun 6 cartes trésor
            for (int i = 0; i < 6; ++i) {
                do {
                    pion1->tresors[i].signe= 65+rand()%24;
                } while (verifunique(pion1,pion2,pion3,pion4,&i)>0);
            }
            for (int i = 0; i < 6; ++i) {
                do {
                    pion2->tresors[i].signe= 65+rand()%24;
                } while (verifunique(pion2,pion1,pion3,pion4,&i)>0);
            }
            for (int i = 0; i < 6; ++i) {
                do {
                    pion3->tresors[i].signe= 65+rand()%24;
                } while (verifunique(pion3,pion2,pion1,pion4,&i)>0);
            }
            for (int i = 0; i < 6; ++i) {
                do {
                    pion4->tresors[i].signe= 65+rand()%24;
                } while (verifunique(pion4,pion2,pion3,pion1,&i)>0);
            }
            break;
    }
}



///// Dans le futur main

int main(){
    int nbjoueurs;

    do {
        printf("saisissez le nombre de joueurs (entre 2 et 4)\n");
        fflush(stdin);
        scanf("%d",&nbjoueurs);
    } while (nbjoueurs<2 || nbjoueurs>4);

    t_pion pion1, pion2, pion3, pion4;

    for (int i = 0; i < 12; ++i) {
        pion1.tresors[i].signe='0',pion2.tresors[i].signe='0',pion3.tresors[i].signe='0', pion4.tresors[i].signe='0';
    }

    DistributionCartes(&nbjoueurs,&pion1,&pion2,&pion3,&pion4);
    for (int i = 0; i < 12; ++i) {
        printf("%c , %c, %c\n",pion1.tresors[i].signe,pion2.tresors[i].signe,pion3.tresors[i].signe);
    }

    return 0;
}