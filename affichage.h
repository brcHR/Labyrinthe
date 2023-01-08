/**
 * @file affichage.h
 * @date 04 janvier 2023
 * @brief Affichage du jeu
 * @author Aurélien
*/

#ifndef LABYRINTHE_AFFICHAGE_H
#define LABYRINTHE_AFFICHAGE_H

#include "plateau.h"
#include "pion.h"

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief cette procedure affiche le labyrinthe, les fleches et les pions
 * @param plateau plateau de jeu
 * @param caseEnPlus tuile en plus
 * @param pions tableau contenant tous les joueurs
 * @param nbJoueur nombre de joueur
 * @return Un affichage du futur.
 */
void affichageComplet(t_case plateau[7][7], t_case caseEnPlus, t_pion pions[4], int nbJoueur);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief cette procedure affiche un logo "labyrinthe" en couleur
 * @param lig coordonne du logo
 * @param col coordonne du logo
 * @return un logo
 */
void afficheLogo(int lig, int col);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief cette procedure permet de placer le curseur a des coordonnées données
 * @param lig ligne
 * @param col col
 */
void cooCurseur(int lig, int col);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////




#endif //LABYRINTHE_AFFICHAGE_H
