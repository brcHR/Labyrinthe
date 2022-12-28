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

int deplacement_valide(t_case labyrinthe [7][7], t_pion *pion, int colonne_arrivee, int ligne_arrivee){ // Parametre a modif je pense
    // On récupère les coordonnées de départ du pion
    int ligne_depart = pion->position_pion->ligne;
    int colonne_depart = pion->position_pion->colonne;

    // On vérifie si le pion a déjà été déplacé dans le tour en cours
    if(pion->deja_deplace == true){
        return false;
    }
    // On vérifie si le pion reste sur place
    else if (ligne_depart == ligne_arrivee && colonne_depart == colonne_arrivee){
        return true;
    }
    // Si on sort du plateau de jeu, le déplacement n'est pas validé
    else if(ligne_arrivee < 0 || ligne_arrivee > 6 || colonne_arrivee < 0 || colonne_arrivee > 6){
        return false;
    }
    // Vérifions si le déplacement passe par un mur
    else{
        for(int i=0;i<3;i++){
            for(int j=0;j<3;j++){
                t_case tuile;
                t_case *pt_tuile = &tuile;

                pt_tuile->ligne = i;
                pt_tuile->colonne = j;

                // Le pion veut traverser un mur
                pion->position_pion->tableau[i][j] = 0;   // ça le fait ???
                tuile.tableau[i][j] = 0; // ça il manque le lien avec position pion !!!

            }
        }
        return false;
    }
}
//les return pas sûr de moi mais dans la théorie on est bon



// Procédure qui permet de déplacer le pion

/* Fonction permettant de récupérer le trésor présent sur la tuile s'il y en a un
 * et donc son numéro, et qui renvoie le nombre de trésors possédé par le pion.*/

int recuperer_tresor(t_pion *pion, t_case *tuile, t_tresor tresor){ // Je vais rompich mais truc à changer
// Si la tuile contient un trésor
    if(tuile->num_tresor == 1){
// On récupère le trésor
        pion->tresor[tuile->tresor].nb_tresors++;
        pion->nb_tresor_pion++;
        tuile->nb_tresors--;
    }
// On renvoie le nombre de trésors possédés par le pion
    return pion->nb_tresor_pion;
}
// VOIR AVEC BRIBRI POUR METTRE STRUCT TRESOR DANS SA STRUCT CASE ( JE MODIFIE COMME JE PENSE QUE CA MARCHE


// Procédure qui renvoie le pion au début de la ligne s'il est sur une tuile qui sort du jeu
void renvoyer_pion_debut_ligne(t_pion *pion, t_case* labyrinthe[7][7]) {
    // On récupère les coordonnées du pion
    int ligne = pion->position_pion->ligne;
    int colonne = pion->position_pion->colonne;

    // On vérifie si la tuile sur laquelle se trouve le pion a été déplacée hors du jeu
    if (ligne < 0 || ligne > 6 || colonne < 0 || colonne > 6) {
        // Si c'est le cas, on renvoie le pion au début de la ligne
        pion->position_pion = labyrinthe[0][pion->position_pion->colonne];
        pion->position_pion->colonne = pion->position_pion->colonne;
    }
}
// PARAMETRE EN POINTEUR ? SINON JE METS "&" LIGNE 83