//
// Created by baptiste on 23/12/2022.
//

#ifndef LABYRINTHE_PIONS_H
#define LABYRINTHE_PIONS_H


#include "plateau.h"


// Structure contenant les différents trésors du jeu
typedef struct tresor{
    char t_1, t_2, t_3, t_4, t_5, t_6, t_7, t_8, t_9, t_10, t_11, t_12, t_13, t_14, t_15, t_16, t_17, t_18, t_19, t_20, t_21, t_22, t_23_, t_24;
    int nb_tresors;
}t_tresor;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Structure contenant les informations sur un pion
typedef struct pion{
    t_case *position_pion; // Pointeur vers la case où le pion se trouve
    int num_pion;
    char nom[15];
    char couleur;
    int arrivee; // Variable booléenne indiquant si le pion a atteint sa destination
    int deja_deplace; // Variable booléenne indiquant si le pion a déjà été déplacé dans le tour en cours
    t_tresor tresor;
    int nb_tresor_pion;
}t_pion;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui me permet de savoir si le déplacement du pion est possible
int sdeplacement_valide(t_case labyrinthe [7][7], t_pion *pion, int colonne_arrivee, int ligne_arrivee);
/*
 * Paramètres : pointeur sur la structure pion, les coordonnées de départ et d'arrivée && le plateau.
 * Retourne : 1 ou 0 suivant si le déplacement est valide ou non.
 */
#endif //LABYRINTHE_PIONS_H
