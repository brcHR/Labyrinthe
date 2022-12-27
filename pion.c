//
// Created by baptiste on 23/12/2022.
//

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <stdbool.h>
#include "plateau.h"
#include "pion.h"

// Fonction qui me permet de savoir si le déplacement du pion est possible

int deplacement_valide(t_case labyrinthe [7][7], t_pion *pion, int colonne_arrivee, int ligne_arrivee){
    // On récupère les coordonnées de départ du pion
    int ligne_depart = pion->position_pion->ligne;
    int colonne_depart = pion->position_pion->colonne;

    // On vérifie si le pion a déjà été déplacé dans le tour en cours
    if(pion->deja_deplace == true){
        return false;
    }
    // On vérifie si le pion reste sur place
    if (ligne_depart == ligne_arrivee && colonne_depart == colonne_arrivee){
        pion->deja_deplace == true;
        return true;
    }
    // Si on sort du plateau de jeu, le déplacement n'est pas validé
    if(ligne_arrivee < 0 || ligne_arrivee > 6 || colonne_arrivee < 0 || colonne_arrivee > 6){
        return false;
    }
    return 0;

}



// Procédure qui permet de déplacer le pion

/* Fonction qui permettant de récupérer le trésor présent sur la case et qui renvoie le nombre de trésors du pion
 * (le nombre de trésors restant diminue) */

// Procédure qui renvoie le pion au début de la ligne s'il est sur une tuile qui sort du jeu