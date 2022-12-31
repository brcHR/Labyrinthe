//
// Created by Maxime Vennin on 30/12/2022.
//

#ifndef LABYRINTHE_DEROULEMENT_H
#define LABYRINTHE_DEROULEMENT_H

#include "pion.h"


/**
 * @brief Cette fonction sert à convertir le numéro de rangée saisi par le joueur en des coordonnées pour pouvoir effectuer le déplacement d'une rangée
 * @param num_rangee numéro de rangée saisi (voir page 13 du sujet)
 * @param coord_pousser coordonnées de la première case de la table de jeu qui va être poussée
 */
void conversion_num_rangee_coordonnees (int *num_rangee, t_coord *coord_pousser);


/**
 * @brief Cette fonction execute le déroulement d'un seul tour
 *
 * @param nbjoueurs le nombre de joueurs
 * @param pion... chacun des 4 pions
 */
void deroulementTour(int nbjoueurs, t_pion *pion1, t_pion *pion2, t_pion *pion3, t_pion *pion4);

#endif //LABYRINTHE_DEROULEMENT_H
