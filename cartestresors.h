//
// Created by Maxime Vennin on 27/12/2022.
//

#ifndef LABYRINTHE_TRESORS_H
#define LABYRINTHE_TRESORS_H

#include "pion.h"
#include "cartestresors.h"

typedef struct { //structure temporaire pour test
    char signe;
    int decouvert; // 1 s'il a été découvert,0 sinon
}t_tresor_sur_carte;


/**
 * @brief Cette fonction est un affichage temporaire des infos sur le prochain trésor à chercher, le nombre de trésors à chercher et les cartes trouvées
 */
void AffichageTresor(t_pion *Pion);//clairement pas sûr


/**
 * @brief Cette fonction sert à savoir si on a déjà utilisé un signe dans un autre pion
 *
 * @param pionVerif le pion dont on vérifie le signe
 * @param pionun un des 4 pions (on inclue simplement les 4 pions sans importance d'ordre)
 * @param piondeux un des 4 pions
 * @param piontrois un des 4 pions
 *
 * @return Une valeur entière, si elle est supérieure à 0 c'est qu'il y a une répétition de signe.
 */
int verifunique(t_pion *pionVerif, t_pion *pionun, t_pion *piondeux, t_pion *piontrois, const int *iteration);

/**
 * @brief Cette fonction sert à distribuer les cartes en fonction du nombre de joueurs et de façon à ce qu'il n'y ait que 24 cartes uniques de distribuées
 *
 * @param nbjoueurs le nombre de joueurs
 * @param pion1 un des 4 pions
 * @param pion2 un des 4 pions
 * @param pion3 un des 4 pions
 * @param pion4 un des 4 pions
 *
 */
void DistributionCartes(const int *nbjoueurs, t_pion *pion1, t_pion *pion2, t_pion *pion3, t_pion *pion4);


#endif //LABYRINTHE_TRESORS_H
