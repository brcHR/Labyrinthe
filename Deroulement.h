/**
 * @file Deroulement.h
 * @date 30 decembre 2022
 * @brief Tout ce qui est relatif au deroulement d'une partie
 * @author Maxime
*/

#ifndef LABYRINTHE_DEROULEMENT_H
#define LABYRINTHE_DEROULEMENT_H

#include "pion.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Procédure permettant de déplacer une colonne ou une ligne.
 *
 * @param labyrinthe tableau 7x7 composé de structures t_case.
 * @param tuile_en_plus pointeur sur la tuile en trop du labyrinthe.
 * @param coord pointeur sur les coordonnées de la tuile en bout de ligne ou de colonne qui va se faire "pousser".
 * @param pions tableau des joueurs.
 * @param nbjoueurs nombre je joueurs dans la partie.
 * @param fichierlog fichier ouvert dans main() pour l'enregistrment des logs
 * @return la colonne ou la ligne a bien coulissé. Nous avons donc la tuile en plus qui a changé.
 */
int deplacer_tuiles(t_case labyrinthe[7][7], t_case *tuile_en_plus, t_coord *coord, t_pion pions[4], int nbjoueurs, FILE *fichierlog);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Cette fonction sert à convertir le numéro de rangée saisi par le joueur en des coordonnées pour pouvoir effectuer le déplacement d'une rangée
 * @param num_rangee numéro de rangée saisi (voir page 13 du sujet)
 * @param coord_pousser coordonnées de la première case de la table de jeu qui va être poussée
 */
void conversion_num_rangee_coordonnees (const int *num_rangee, t_coord *coord_pousser);


/**
 * @brief Cette fonction execute le déroulement d'un seul tour
 *
 * @param nbjoueurs le nombre de joueurs
 * @param pions chacun des 4 pions
 * @param labyrinthe plateau du labyrinthe
 * @param tuile_en_plus tuile supplémentaire en dehors du plateau
 * @param fichierlog fichier ouvert dans main() pour enregister les logs
 *
 * @return 1 si un joueur a gagné, 2 si un joueur veut retourner au menu ou 0 sinon.
 */
int deroulementTour(const int *nbjoueurs,t_case labyrinthe[7][7], t_case *tuile_en_plus, t_pion pions[4], FILE *fichierlog);

/**
 * @brief Cette fonction vérifie si tous les trésors ont été trouvés
 *
 * @param pions chacun des 4 pions
 *
 * @return 1 si le joueur a trouvé un trésor
 */
int test_tresor(t_pion *Pion);

/**
 * @brief Cette fonction execute le menu et initialise le plateau de jeu.
 * Le menu permet de lancer une nouvelle partie, d'affichr les règles du jeu, les crédits et de sortir du programme.
 * @param fichierlog fichier ouvert dans main() pour enregistrer les logs
 */
void Menu(FILE *fichierlog);

/**
 * @brief Cette fonction initialise le nom et la position initiale des joueurs
 *
 * @param nbjoueurs nombre de joueurs
 * @param pions tableau des pions
 *
 */
void attribution_caracteristiques_joueurs(const int *nbjoueurs,t_pion pions[4], t_case labyrinthe[7][7]);

#endif //LABYRINTHE_DEROULEMENT_H
