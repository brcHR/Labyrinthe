//
// Created by baptiste on 23/12/2022.
//
/**
 * @file pion.h
 * @date 23 décembre 2022
 * @brief Gestion du déplacement des pions et la récupération des trésors.
 * @author Baptiste
*/
#ifndef LABYRINTHE_PIONS_H
#define LABYRINTHE_PIONS_H

#include "plateau.h"



typedef struct { //structure temporaire pour test
    char signe;
    int decouvert; // 1 s'il a été découvert,0 sinon
    t_tresor tresor;
}t_tresor_sur_carte;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Structure contenant les informations sur un pion
 */

typedef struct pion{
    t_case *position_pion; // Pointeur vers la case où le pion se trouve
    int num_pion; // Numéro du pion
    char nom[15]; // Nom du pion
    t_coord coord_depart_arrivee;
    t_tresor_sur_carte tresors[12];// tableau stockant tous les tresors du joueur, les cases en trop sont des '0' et on en met 12 car on a au max 12 tresors par joueur
    int num_tresor_recherche;
    int nb_tresor_pion; // Nombre de trésors du pion
    int lig;
    int col;
}t_pion;


////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Cette fonction sert permet de savoir si le déplacement du pion est possible ou non.
 *
 * @param labyrinthe tableau 7x7 composé de structures t_case.
 * @param pion pointeur sur un pion du jeu auquel il faut vérifier si le déplacement est valide.
 * @param colonne_arrivee entier correspondant à la colonne d'arriver du déplacement du pion.
 * @param ligne_arrivee entier correspondant à la ligne d'arriver du déplacement du pion.
 *
 * @return Une valeur booléenne ( 0 ou 1 ) en fonction de si le mouvement est valide ou non.
 */

int deplacement_valide(t_case labyrinthe [7][7], t_pion *pion, int colonne_arrivee, int ligne_arrivee);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Cette procédure permet de déplacer le pion.
 *
 * @param labyrinthe tableau 7x7 composé de structures t_case.
 * @param pion pointeur sur un pion du jeu que l'on déplace sur le plateau du jeu.
 * @param colonne_arrivee entier correspondant à la colonne d'arriver du déplacement du pion.
 * @param ligne_arrivee entier correspondant à la ligne d'arriver du déplacement du pion.
 *
 * @return La nouvelle position du pion sur le plateau.
 */

void deplacer_pion(t_case labyrinthe [7][7], t_pion *pion, int colonne_arrivee, int ligne_arrivee);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief  Cette fonction permet de récupérer le trésor présent sur la tuile s'il y en a un, donc son numéro.
 * Elle renvoie le nombre de trésors possédé par le pion.
 *
 * @param pion pointeur sur un pion du jeu arrivant sur une case comprenant un trésor.
 * @param tuile tuile pointeur sur une tuile du labyrinthe.
 *
 * @return Le nombre de trésor possédé par le pion.
 */

int recuperer_tresor(t_pion *pion, t_case *tuile);

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Cette procédure permet de renvoyer le pion au début de la ligne s'il est sur une tuile qui sort du jeu.
 *
 * @param labyrinthe tableau 7x7 composé de structures t_case.
 * @param pion pointeur sur un pion du jeu que l'on renvoie au début d'une ligne s'il est expulsé en dehors du plateau.
 *
 * @return La nouvelle position du pion en début de ligne.
 */

void renvoyer_pion_debut_ligne(t_case labyrinthe[7][7],t_pion *pion);

#endif //LABYRINTHE_PIONS_H
