//
// Created by baptiste on 23/12/2022.
//

#ifndef LABYRINTHE_PIONS_H
#define LABYRINTHE_PIONS_H


#include "plateau.h"


// Structure contenant les différents trésors du jeu
typedef struct tresor{
    int num_tresor; // numéro trésor allant de 0 à 23
    // int nb_tresors; //24 trésors Sert à rien comme je déduis pas le nb de trésors du plateau après avoir récup ??
}t_tresor;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Structure contenant les informations sur un pion
typedef struct pion{
    t_case *position_pion; // Pointeur vers la case où le pion se trouve
    int num_pion; // Numéro du pion
    char nom[15]; // Nom du pion
    char couleur; // Couleur du pion
    int arrivee; // Variable booléenne indiquant si le pion a atteint sa destination
    int deja_deplace; // Variable booléenne indiquant si le pion a déjà été déplacé dans le tour en cours
    t_tresor tresor; // Structure trésor
    int nb_tresor_pion; // Nombre de trésors du pion
}t_pion;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// Fonction qui me permet de savoir si le déplacement du pion est possible
int sdeplacement_valide(t_case labyrinthe [7][7], t_pion *pion, int colonne_arrivee, int ligne_arrivee);
/*
 * Paramètres : pointeur sur la structure pion, les coordonnées de départ et d'arrivée && le plateau.
 * Retourne : 1 ou 0 suivant si le déplacement est valide ou non.
 */
#endif //LABYRINTHE_PIONS_H
