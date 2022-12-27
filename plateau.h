/**
 * @file plateau.h
 * @date 19 décembre 2022
 * @brief Gestion du plateau du labyrinthe
 * @author Briac
*/

#ifndef LABYRINTHE_PLATEAU_H
#define LABYRINTHE_PLATEAU_H


/**
 * @brief cette structure permet de modifier le tableau d'une case en sauvegardant l'emplacement de la case à faire tourner
 * avant qu'elle ne bouge.
 */
typedef struct sauvegarde_coordonees_mini_case_a_deplacer{
    int ligne1;
    int colonne1;
    int ligne2; //dans le L et I deux cases doivent bouger
    int colonne2;
}save_coord_mini_case;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief structure contenant toutes les informations sur une case.
 */
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

/**
 * @brief structure contenant toutes les informations sur un joueur.
 */
typedef struct joueur{
    char nom[15];
    char couleur;
    t_case *position; // pointe sur la case où se situe le joueur
}t_joueur;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Structure contenant simplement des coordonnées dans un tableau. Cela permet plus de lisibilité lors d'appels
 * contenant des coordonnées.
 */
typedef struct coordonnees_pour_faciliter_les_appels{
    int ligne;
    int colonne;
}t_coord;

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Cette fonction sert au changement de l'orientation des pièces du labyrinthe. Elle convertit les degrés en
 * radians.
 *
 * @param nb pointeur sur un nombre flottant.
 * @return un angle en radians.
 */
void deg_rad(float *nb);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Cette fonction sert au changement de l'orientation des pièces du labyrinthe. Elle convertit les radians en
 * degrés.
 *
 * @param nb pointeur sur un nombre flottant.
 * @return un angle en degrés.
 */
void rad_deg(float *nb);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Procédure permettant de supprimer la première occurrence d'un caractère dans une chaîne de caractères.
 *
 * @param chaine pointeur sur une chaîne de caractères.
 * @param lettre le caractère à supprimer.
 * @return chaîne avec une occurence en moins de lettre.
 */
void del_1_occ(char *chaine, char lettre);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Procédure copiant une structure case dans une autre.
 *
 * @param source pointeur sur une case source.
 * @param destination pointeur sur une case destination.
 * @return toutes les données de sources sont dans destination --> destination == source.
 */
void copy_case(t_case *source, t_case *destination);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Procédure créant les tuiles avec leur chemin.
 *
 * @param tuile pointeur sur une tuile du labyrinthe.
 * @return la case a maintenant un type (T, L ou I) et un tableau 3x3 représentant son chemin avec l'orientation.
 */
void creation_type_case(t_case* tuile);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Procédure modifie l'orientation d'une pièce. Cette fontion prend en paramètres le pointeur de la tuile à faire tourner et la nouvelle rotation qu'on souhaite lui appliquer.
 *
 * @param tuile pointeur sur la tuile du labyrinthe à faire tourner.
 * @param orientation flottant correspondant nouvelle rotation qu'on veut lui appliquer.
 * @return la case a maintenant une nouvelle orientation
 * @return un nouveau tableau 3x3.
 */
void tourner(t_case* tuile, float orientation);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Procédure crée le plateau de jeu avec la tuile additionnelle.
 *
 * @param labyrinthe tableau 7x7 composé de structures t_case.
 * @param tuile_add pointeur sur la tuile en trop du labyrinthe.
 * @return toutes les cases du labyrinthe ont leurs métadonnées remplies correctement.
 */
void generation_plateau_debut(t_case labyrinthe[7][7], t_case* tuile_add);

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Procédure permettant de déplacer une colonne ou une ligne.
 *
 * @param labyrinthe tableau 7x7 composé de structures t_case.
 * @param tuile_en_plus pointeur sur la tuile en trop du labyrinthe.
 * @param coord pointeur sur les coordonnées de la tuile en bout de ligne ou de colonne qui va se faire "pousser".
 * @return la colonne ou la ligne a bien coulissé. Nous avons donc la tuile en plus qui a changé.
 */
void deplacer_tuiles(t_case labyrinthe[7][7], t_case *tuile_en_plus, t_coord *coord);


#endif //LABYRINTHE_PLATEAU_H
