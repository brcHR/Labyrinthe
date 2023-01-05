//
// Created by Maxime Vennin on 27/12/2022.
//

#ifndef LABYRINTHE_CARTESTRESORS_H
#define LABYRINTHE_CARTESTRESORS_H

#include "pion.h"
#include "plateau.h"




/**
 * @brief Cette fonction est un affichage temporaire des infos sur le prochain :
 * trésor à chercher
 * le nombre de trésors à chercher
 * les cartes trouvées
 * Elle peut-être intéressante si on a besoin de ces informations
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
 * @param pions les 4pions
 *
 */
void DistributionCartes(const int *nbjoueurs, t_pion pions[4]);

/**
 * @brief Cette fonction sert à convertir le caractère d'une struct t_tresor_sur_carte en nb pour pouvoir le comparer
 *
 * @param tresorCarte un trésor carte qu'on veut convertir
 *
 * @return la valeur du trésor pour pouvoir le comparer
 */
int convertisseur_tresor_CaracVersNb(t_tresor_sur_carte *tresorCarte);

/**
 * @brief Cette fonction sert à convertir le nb d'une struct t_tresor en carac pour pouvoir l'afficher dans le Labyrinthe
 *
 * @param tresorenNB un trésor qu'on veut convertir en caractère
 *
 * @return le caractère du trésor pour pouvoir l'afficher
 */
char convertisseur_tresor_NbVersCarac(t_tresor *tresorenNB);

#endif //LABYRINTHE_CARTESTRESORS_H
