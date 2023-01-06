//
// Created by Maxime Vennin on 27/12/2022.
//
#include "cartestresors.h"
#include "pion.h"
#include "plateau.h"

#include <stdio.h>
#include <time.h>
#include <stdlib.h>

//TODO: faire une correspondance entre les numeros des tresors et leur symboles dans l'affichage

void AffichageTresor(t_pion *Pion){ // affichage d'informations
    char tresorcherche;

    int cartesatrouver=0;//compte le nombre de cartes restantes à trouver
    for (int i = 0; i < 12; ++i) {
        if (Pion->tresors[i].signe !='0'&& Pion->tresors[i].decouvert==0){
            ++cartesatrouver;
        }
    }
    if (cartesatrouver==0){// si le joueur n'a pas tous les tresors on affiche les infos
        printf("cartes a trouver : %d\n",cartesatrouver);
        for (int i = 0; i < 12; ++i) {//affiche le prochain tresor à chercher
            if (Pion->tresors[i].signe!='0'&&Pion->tresors[i].decouvert==0){
                printf("le prochain tresor a trouver est : %c\n",Pion->tresors[i].signe);
                Pion->num_tresor_recherche= convertisseur_tresor_CaracVersNb(&Pion->tresors[i]);// enregistre le tresor à chercher dans la struct
                break;
            }
        }
        printf("Les tresors deja trouves sont : ");
        for (int i = 0; i < 12; ++i) {// affiche les tresors deja trouves
            if (Pion->tresors[i].signe!='0'&&Pion->tresors[i].decouvert==1){
                printf("%c, ",Pion->tresors[i].signe);
            }
            printf("\n");
        }
    }
    else {//si le pion a tous les trésors afficher retour à case départ pour gagner
        printf("Vous avez tous les trésors, retournez à votre case départ pour gagner\n");
    }


}

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

void DistributionCartes(const int *nbjoueurs, t_pion pions[4]){ //distribue les tresors de struct pion
    //TODO: peut etre faire du random avec dell_1_occ. Sinon rien compris aux fonctions. Rendre ce code lisible.
    srand(time(NULL));
    switch (*nbjoueurs) {
        case 2:// 2 joueurs avec chacun 12 cartes trésor
            for (int i = 0; i < 12; ++i) {
                do {
                    pions[0].tresors[i].signe= 65+rand()%24;
                } while (verifunique(&pions[0],&pions[1],&pions[2],&pions[3],&i)>0);
            }
            for (int i = 0; i < 12; ++i) {
                do {
                    pions[1].tresors[i].signe = 65+rand()%24;
                } while (verifunique(&pions[1],&pions[1],&pions[2],&pions[3],&i)>0);
            }
            break;
        case 3:// 3 joueurs avec chacun 8 cartes trésor
            for (int i = 0; i < 8; ++i) {
                do {
                    pions[0].tresors[i].signe= 65+rand()%24;
                } while (verifunique(&pions[0],&pions[1],&pions[2],&pions[3],&i)>0);
            }
            for (int i = 0; i < 8; ++i) {
                do {
                    pions[1].tresors[i].signe = 65+rand()%24;
                } while (verifunique(&pions[1],&pions[1],&pions[2],&pions[3],&i)>0);
            }
            for (int i = 0; i < 8; ++i) {
                do {
                    pions[2].tresors[i].signe= 65+rand()%24;
                } while (verifunique(&pions[2],&pions[1],&pions[0],&pions[3],&i)>0);
            }
            break;
        case 4:// 4 joueurs avec chacun 6 cartes trésor
            for (int i = 0; i < 6; ++i) {
                do {
                    pions[0].tresors[i].signe= 65+rand()%24;
                } while (verifunique(&pions[0],&pions[1],&pions[2],&pions[3],&i)>0);
            }
            for (int i = 0; i < 6; ++i) {
                do {
                    pions[1].tresors[i].signe = 65+rand()%24;
                } while (verifunique(&pions[1],&pions[1],&pions[2],&pions[3],&i)>0);
            }
            for (int i = 0; i < 6; ++i) {
                do {
                    pions[2].tresors[i].signe= 65+rand()%24;
                } while (verifunique(&pions[2],&pions[1],&pions[0],&pions[3],&i)>0);
            }
            for (int i = 0; i < 6; ++i) {
                do {
                    pions[3].tresors[i].signe= 65+rand()%24;
                } while (verifunique(&pions[3],&pions[1],&pions[0],&pions[2],&i)>0);
            }
            break;
    }
}

int convertisseur_tresor_CaracVersNb(t_tresor_sur_carte *tresorCarte){
    int tresorConverti;
    tresorConverti=(int) tresorCarte->signe-65;
    return tresorConverti;
}

char convertisseur_tresor_NbVersCarac(t_tresor *tresorenNB){
    char tresorConverti;
    tresorConverti= (char) tresorenNB->num_tresor+65;
    return tresorConverti;
}

///////à mettre dans le futur main ou dans le test

/*int main(){
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
    for (int i = 0; i < 12; ++i) {
        pion1.tresors[i].decouvert=0,pion2.tresors[i].decouvert=0,pion3.tresors[i].decouvert=0,pion4.tresors[i].decouvert=0;
    }


    DistributionCartes(&nbjoueurs,&pion1,&pion2,&pion3,&pion4);
    for (int i = 0; i < 12; ++i) {
        printf("%c , %c, %c\n",pion1.tresors[i].signe,pion2.tresors[i].signe,pion3.tresors[i].signe);
    }

    AffichageTresor(&pion1);

    return 0;
}
*/
