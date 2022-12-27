//
// Created by briac on 19/12/2022.
//

#ifndef LABYRINTHE_PLATEAU_H
#define LABYRINTHE_PLATEAU_H


/* Cette structure permet de modifier le tableau d'une case en sauvegardant l'emplacement de la case à faire tourner
 * avant qu'elle ne bouge.*/
typedef struct sauvegarde_coordonees_mini_case_a_deplacer{
    int ligne1;
    int colonne1;
    int ligne2; //dans le L et I deux cases doivent bouger
    int colonne2;
}save_coord_mini_case;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// structure contenant toutes les informations sur une case
typedef struct Case{
    int ligne;
    int colonne;
    char forme;
    int fixe;
    float rotation;
    char tableau[3][3];
    save_coord_mini_case mini_case;
    int tresor;
    int start_finish;
}t_case;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// structure contenant toutes les informations sur un joueur
typedef struct joueur{
    char nom[15];
    char couleur;
    t_case *position; // pointe sur la case où se situe le joueur
}t_joueur;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/*Structure contenant simplement des coordonnées dans un tableau. Cela permet plus de lisibilité lors d'appels
 *contenant des coordonnées.*/
typedef struct coordonnees_pour_faciliter_les_appels{
    int ligne;
    int colonne;
}t_coord;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//ces deux fonctions servent au changement de l'orientation des pièces du labyrinthe
void deg_rad(float *nb); //convertit les degrés en radians
void rad_deg(float *nb); //convertit les radians en degrés
/*
 * Paramètres : pointeur sur un nombre flottant.
 * Retourne : conversion en radians ou conversion en degrés.
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Procédure permettant de supprimer la première occurrence d'un caractère dans une chaîne de caractères.
void del_1_occ(char *chaine, char lettre);
/*
 * Paramètres : pointeur sur une chaine de caractères && le caractère à supprimer.
 * Retourne : la chaine avec une occurrence en moins de lettre.
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Procédure copiant une structure case dans une autre.
void copy_case(t_case *source, t_case *destination);
/*
 * Paramètres : pointeur sur une case source && pointeur sur une case destination.
 * Retourne : toutes les données de sources sont dans destination --> destination == source.
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// La procédure suivante crée les tuiles avec leur chemin.
void creation_type_case(t_case* tuile);
/*
 * Paramètres : pointeur sur une tuile du labyrinthe.
 * Retourne : la case a maintenant un type (T, L ou I) et un tableau 3x3 représentant son chemin avec l'orientation.
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// La procédure suivante modifie l'orientation d'une pièce. Cette fontion prend en paramètres le pointeur de la tuile
// à faire tourner et la nouvelle rotation qu'on souhaite lui appliquer.
void tourner(t_case* tuile, float orientation);
/*
 * Paramètres : pointeur sur la tuile du labyrinthe à faire tourner && la nouvelle rotation qu'on veut lui appliquer.
 * Retourne : la case a maintenant une nouvelle orientation && un nouveau tableau 3x3.
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//La procédure suivante crée le plateau de jeu avec la tuile additionnelle.
void generation_plateau_debut(t_case labyrinthe[7][7], t_case* tuile_add);
/*
 * Paramètres : un tableau 7x7 composé de structures t_case && pointeur sur la tuile en trop du labyrinthe.
 * Retourne : toutes les cases du labyrinthe ont leurs métadonnées remplies correctement.
 */

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//Cette procédure permet de déplacer une colonne ou une ligne.
void deplacer_tuiles(t_case labyrinthe[7][7], t_case *tuile_en_plus, t_coord *coord);
/*
 * Paramètres : le tableau du plateau && pointeur sur la tuile en plus du labyrinthe && les coordonnées de la tuile en
 * bout de ligne ou de colonne qui va se faire "pousser".
 * Retourne : la colonne ou la ligne a bien coulissé. Nous avons donc la tuile en plus qui a changé.
 */


#endif //LABYRINTHE_PLATEAU_H
