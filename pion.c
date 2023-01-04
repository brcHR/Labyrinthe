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

int deplacement_valide(t_case labyrinthe[7][7], t_pion *pion, int colonne_arrivee, int ligne_arrivee) {
    int ligne_depart,colonne_depart,ligne_plateau,colonne_plateau;
    int i,j;

    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(&labyrinthe[i][j] == pion->position_pion){
                // On récupère les coordonnées de départ du pion
                ligne_depart = i;
                colonne_depart = j;
                break;
            }
        }
    }


    // On vérifie si le pion reste sur place
    if (ligne_depart == ligne_arrivee && colonne_depart == colonne_arrivee) {
        return true; //Déplacement valide même si le pion bouge pas.
    }
        // Si on sort du plateau de jeu, le déplacement n'est pas validé
    else if (ligne_arrivee < 0 || ligne_arrivee > 6 || colonne_arrivee < 0 || colonne_arrivee > 6) {
        return false;
    }

        //Le pion se déplace sur une case qui existe dans le labyrinthe.
    else {
        //Maintenant, nous devons vérifier que le pion se déplace uniquement sur une ligne ou sur une colonne.
        /* Un pion ne peut pas, lors d'un déplacement horizontal, changer de ligne.
         * Un pion ne peut pas, lors d'un déplacement vertical, changer de colonne.
         * Afin de se déplacer sur tout le plateau, on demandera au joueur de se déplacer tant qu'il veut.*/
        if ((ligne_depart != ligne_arrivee) && (colonne_depart != colonne_arrivee)) {
            return false;
        }
        else { //Le déplacement est "légal".
            //Si on rencontre un mur lors du déplacement, on arrête de bouger le pion et on dit au joueur qu'on a pas
            // pu aller jusqu'au bout.

            /*
             * DEPLACEMENT SUR UNE LIGNE
             */

            if(ligne_depart == ligne_arrivee){
                //On cherche si on déplace le pion vers la gauche ou vers la droite
                /*
                 * ----VERS LA DROITE----
                 */
                if(colonne_depart<colonne_arrivee){
                    //On boucle sur les colonnes pour se déplacer.
                    for( colonne_plateau=colonne_depart ; colonne_plateau<colonne_arrivee ; colonne_plateau++ ){
                        //Comme on se déplace vers la DROITE, on regarde s'il y a un mur sur le coté droit de la tuile.
                        //et on regarde sur le coté gauche de la tuile juste à côté.
                        if(labyrinthe[ligne_arrivee][colonne_plateau].tableau[1][2] == 1
                            || labyrinthe[ligne_arrivee][colonne_plateau+1].tableau[1][0] == 1){

                            return false;
                        }
                    }
                    return true; //Le déplacement est valide.
                }
                /*
                 * ----VERS LA GAUCHE----
                 */
                else{
                    //On boucle sur les colonnes pour se déplacer.
                    for( colonne_plateau=colonne_depart ; colonne_plateau>colonne_arrivee ; colonne_plateau-- ){
                        //Comme on se déplace vers la GAUCHE, on regarde s'il y a un mur sur le coté gauche de la tuile.
                        //et on regarde sur le coté droit de la tuile juste à côté.
                        if(labyrinthe[ligne_arrivee][colonne_plateau].tableau[1][0] == 1
                           || labyrinthe[ligne_arrivee][colonne_plateau-1].tableau[1][2] == 1){

                            return false;
                        }
                    }
                    return true; //Le déplacement est valide.
                }
            }

            /*
             * DEPLACEMENT SUR UNE COLONNE
             */

            else{
                //On cherche si on se déplace vers le haut ou vers le bas.
                /*
                 * ----VERS LE BAS----
                 */
                if(ligne_depart<ligne_arrivee){
                    //On boucle sur les lignes.
                    for( ligne_plateau=ligne_depart ; ligne_plateau<ligne_arrivee ; ligne_plateau++ ){
                        //Comme on va vers le BAS, on regarde si y'a un mur en bas de la case
                        //et au dessus de la case en juste en dessous.
                        if(labyrinthe[ligne_plateau][colonne_arrivee].tableau[2][1] == 1
                            || labyrinthe[ligne_plateau+1][colonne_arrivee].tableau[0][1] == 1){

                            return false;
                        }
                    }
                    return true;
                }
                /*
                 * ----VERS LE HAUT----
                 */
                else{
                    //On boucle sur les lignes.
                    for( ligne_plateau=ligne_depart ; ligne_plateau>ligne_arrivee ; ligne_plateau-- ){
                        //Comme on va vers le HAUT, on regarde si y'a un mur en haut de la case
                        //et en dessous de la case en juste au dessus.
                        if(labyrinthe[ligne_plateau][colonne_arrivee].tableau[0][1] == 1
                           || labyrinthe[ligne_plateau-1][colonne_arrivee].tableau[2][1] == 1){

                            return false;
                        }
                    }
                    return true;
                }
            }
        }
    }
}




// Procédure qui permet de déplacer le pion
void deplacer_pion(t_case labyrinthe[7][7], t_pion *pion, int colonne_arrivee, int ligne_arrivee){
    // On vérifie si le mouvement est valide avec la fonction "deplacement_valide".
    if (deplacement_valide(labyrinthe, pion, colonne_arrivee, ligne_arrivee) == true){
        // Met à jour les coordonnées du pion
        pion->position_pion = &labyrinthe[ligne_arrivee][colonne_arrivee];
    }
    else{
        printf("Déplacement impossible");
    }
    //TODO faire en sorte de dire que le déplacement n'a pas fonctionné.
}

/* Fonction permettant de récupérer le trésor présent sur la tuile s'il y en a un
 * et donc son numéro, et qui renvoie le nombre de trésors possédé par le pion.*/

int recuperer_tresor(t_pion *pion, t_case *tuile, t_tresor tresor){ // Je vais rompich mais truc à changer
// Si la tuile contient un trésor
    if(tuile->tresor.un_tresor == 1){
    }
    // Si le trésor récupéré est le bon trésor
        if (tuile->tresor.num_tresor == pion->num_tresor_recherche) {
            // Alors on récupère le trésor
            pion->nb_tresor_pion += 1;
            tuile->tresor.un_tresor = 0;
            // On ajoute le numéro du trésor récupéré dans le tableau tresors de la structure t_pion
            pion->tresors[pion->nb_tresor_pion - 1].tresor.num_tresor = tuile->tresor.num_tresor;
        }
// On renvoie le nombre de trésors possédés par le pion
    return pion->nb_tresor_pion;
}

// Procédure qui renvoie le pion au début de la ligne s'il est sur une tuile qui sort du jeu
void renvoyer_pion_debut_ligne(t_case* labyrinthe[7][7],t_pion *pion){
    // On récupère les coordonnées du pion
    int ligne = pion->position_pion->ligne;
    int colonne = pion->position_pion->colonne;

    // On vérifie si la tuile sur laquelle se trouve le pion a été déplacée hors du jeu
    if (ligne < 0 || ligne > 6 || colonne < 0 || colonne > 6) {
        // Si c'est le cas, on renvoie le pion au début de la ligne
        pion->position_pion->ligne = pion->position_pion->ligne;
        pion->position_pion = labyrinthe[pion->position_pion->colonne][0];
    }
}