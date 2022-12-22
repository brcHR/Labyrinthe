//
// Created by briac on 19/12/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <malloc.h>
#include <string.h>
#include "plateau.h"

/*
 * Fonction convertissant des degrés en radians
 */

void deg_rad(float *nb){
    if( *nb == 0 ){
        *nb = 0;
    }
    else if( *nb == 90 ){
        *nb = M_PI/2;
    }
    else if( *nb == 180 ){
        *nb = M_PI;
    }
    else{
        *nb = (3*M_PI)/2;
    }
}


/*
 * Fonction convertissant des radians en degrés
 */

void rad_deg(float *nb){
    if( *nb == 0 ){
        *nb = 0;
    }
    else if( *nb == M_PI/2 ){
        *nb = 90;
    }
    else if( *nb == M_PI ){
        *nb = 180;
    }
    else{
        *nb = 270;
    }
}


/*
 * Procédure qui trouve la première occurrence d'un élément dans une chaine de caractères et la supprime.
 */

void del_1_occ(char *chaine, char lettre){
    int taille = strlen(chaine);
    int i = 0;

    while(i<taille && chaine[i] != lettre){
        i++;
    }

    while(i<taille){
        chaine[i] = chaine[i+1];
        i++;
    }
}


/*
 * Nous créons les chemins de base présents sur les tuiles.
 */

void creation_type_case(t_case* tuile){
    int i,j;

    // on fait la forme de base : une tuile avec comme chemin une croix
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            if(i && j != 1){
                tuile->tableau[i][j] = 1; // coins
            }
            else{
                tuile->tableau[i][j] = 0;
            }
        }
    }

    // On crée ensuite les formes, en enregistrant la position pour pouvoir la modifier.
    if(tuile->forme == 'T'){
        tuile->tableau[0][1] = 1;
        tuile->mini_case.ligne1 = 0;
        tuile->mini_case.colonne1 = 1;
    }
    if(tuile->forme == 'L'){
        tuile->tableau[1][0] = 1;
        tuile->tableau[2][1] = 1;
        tuile->mini_case.ligne1 = 1;
        tuile->mini_case.colonne1 = 0;
        tuile->mini_case.ligne2 = 2;
        tuile->mini_case.colonne2 = 1;
    }
    if(tuile->forme == 'I'){
        tuile->tableau[1][0] = 1;
        tuile->tableau[1][2] = 1;
        tuile->mini_case.ligne1 = 1;
        tuile->mini_case.colonne1 = 0;
        tuile->mini_case.ligne2 = 1;
        tuile->mini_case.colonne2 = 2;
    }
}


/*
 * Procédure modifiant l'orientation des cases
 */

void tourner(t_case* tuile, float orientation){
    int ligne, colonne, ligneI_l1, colonneI_c1, ligneI_l2, colonneI_c2;
    float rota_ini, rota_new, angleT, angleL_l2, angleL_c2, rota_new_save;
    float *p_r_ini, *p_or, *p_new;

    rota_ini = tuile->rotation;

    //on crée des pointeurs pour modifier leur valeur dans des procédures
    p_r_ini = &rota_ini;
    p_or = &orientation;
    p_new = &rota_new;

    //on convertit en radians la rotation que la case a actuellement
    deg_rad(p_r_ini);
    //on convertit en radian la rotation que le joueur veut lui appliquer
    deg_rad(p_or);

    //Nous pouvons maintenant faire des modifications dans les métadonnées de la tuile.
    //Dans un premier temps, on veut la nouvelle valeur de la rotation.
    rota_new = (*p_r_ini) + (*p_or); // on additionne la rotation de base avec celle que l'on veut appliquer
    if( rota_new >= 360 ){ //Si on dépasse 360, alors on enlève 360 pour obtenir une rotation correcte.
        rota_new = rota_new - 360;
    }
    rota_new_save = *p_new; //on sauvegarde la rotation en radians pour faire tourner les pièces.
    rad_deg(p_new);//on remet en degrés
    tuile->rotation = rota_new; //on met à jour la rotation de la pièce par rapport à sa position de base

    //Modifions le tableau de la tuile avec la nouvelle rotation.
    /* Forme de T.
     * Pour comprendre le code suivant, il faut dessiner un T dans une matrice 3x3. On remarque que si on veut faire
     * tourner le T dans le sens des aiguilles d'une montre, on doit déplacer le 0 dans la case [0][1] dans la case
     * [1][2] et ainsi de suite.
     * Pour comprendre l'utilisation des sinus, il faut faire des graphiques*/

    if(tuile->forme == 'T'){
        angleT = rota_new_save + (M_PI/2); //on manipule des radians avec les sinus
        colonne = 1 + sinf(rota_new_save);
        ligne = 1 + (sinf(angleT));

        //Maintenant, on modifie le tableau de la case.
        tuile->tableau[ligne][colonne] = 1; //on met le mur.
        tuile->tableau[tuile->mini_case.ligne1][tuile->mini_case.colonne1] = 0; //On enlève le mur sur l'ancien passage.

        //On change la valeur de la ligne et de la colonne dans la structure de sauvegarde.
        tuile->mini_case.ligne1 = ligne;
        tuile->mini_case.ligne1 = colonne;
    }

    /*Forme de L.
     * Pour les chemins en forme de L, il faut faire comme pour les chemins en T. Sauf que la position de départ des
     * deux cases à faire bouger sont différentes.
     * Il faut donc faire un graphique des valeurs des coordonnées des cases en fonction de la rotation (de la position
     * dans la matrice [3][3]).*/

    else if(tuile->forme == 'L'){
        // faire le graphique pour comprendre
        angleL_c2 = rota_new_save + (M_PI/2);
        angleL_l2 = rota_new_save + M_PI;

        ligne = 1 + sinf(angleL_l2);
        colonne = 1 + sinf(angleL_c2);

        //Maintenant, on modifie le tableau de la case.
        tuile->tableau[ligne][colonne] = 1;
        tuile->tableau[tuile->mini_case.ligne1][tuile->mini_case.colonne1] = 0;

        //Comme les deux cases se suivent en tournant, il suffit juste de mettre un zéro sur l'ancienne localisation de
        //la case du bas et de donner l'ancienne valeur de la case du haut à celle du bas.
        tuile->mini_case.ligne1 = tuile->mini_case.ligne2;
        tuile->mini_case.colonne1 = tuile->mini_case.colonne2;
        tuile->mini_case.ligne2 = ligne;
        tuile->mini_case.colonne2 = colonne;
    }

    /* Forme de I.
     * Les explications sont les mêmes que pour les deux autres formes.*/

    else if(tuile->forme == 'I'){
        if( rota_new == 90 || rota_new == 270 ){ //Le chemin change d'orientation que si on applique 90 ou 270 degrés.
            if(tuile->mini_case.colonne1 == 0){
                //on sauvegarde les valeurs.
                ligneI_l1 = tuile->mini_case.ligne1;
                colonneI_c1 = tuile->mini_case.colonne1;
                ligneI_l2 = tuile->mini_case.ligne2;
                colonneI_c2 = tuile->mini_case.colonne2;

                //on commence par remplir les minis cases avec les murs.
                tuile->tableau[0][1] = 1;
                tuile->tableau[2][1] = 1;
                //Puis on enlève les murs qui doivent disparaître.
                tuile->tableau[ligneI_l1][colonneI_c1] = 0;
                tuile->tableau[ligneI_l2][colonneI_c2] = 0;

                //On affecte les nouvelles coordonnées.
                tuile->mini_case.ligne1 = 0;
                tuile->mini_case.colonne1 = 1;
                tuile->mini_case.ligne2 = 2;
                tuile->mini_case.colonne2 = 1;
            }
        }
    }
}


/*
 * Nous créons le plateau de jeu
 */

void generation_plateau_debut(t_case labyrinthe[7][7], t_case* tuile_add){
    int i,j, alea;
    float rota;
    int tresors = 24;
    char all_types[50]; //liste de tous les types.
    t_case *pt_tuile;

    srand(time(NULL));

    //On met le bon nombre de chaque forme de case.
    for(i=0;i<50;i++){
        if(i<18){
            all_types[i] = 'T';
        }
        else if(i<38){
            all_types[i] = 'L';
        }
        else{
            all_types[i] = 'I';
        }
    }

    /*Dans un premier temps, on place les tuiles fixes (qui ont des chemins particuliers et des orientations
     *particulières). Ensuite, on placera les autres en leur donnant une forme et une orientation de manière aléatoire.*/

    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            //On crée un pointeur sur la tuile à modifier.
            pt_tuile = &labyrinthe[i][j];

            ///Plaçons les tuiles de départ et d'arrivée.
            if( (i == 0 || i == 6) && (j == 0 || j == 6) ){
                pt_tuile->ligne = i;
                pt_tuile->colonne = j;
                pt_tuile->forme = 'L';
                del_1_occ(all_types, pt_tuile->forme);
                //Modification du tableau de la case.
                creation_type_case(pt_tuile);
                pt_tuile->fixe = 1;
                pt_tuile->tresor = 0;
                pt_tuile->start_finish = 1;
                //Modifions l'orientation de ces quatre pièces.
                if( i==0 && j==0 ){
                    tourner(pt_tuile, 90);
                }
                else if( i==0 && j==6 ){
                    tourner(pt_tuile, 180);
                }
                else if( i==6 && j==0 ){
                    tourner(pt_tuile, 0);
                }
                else{
                    tourner(pt_tuile, 270);
                }
            }

            ///Ici, on s'occupe de toutes les autres tuiles FIXES.
            else if(j%2==0){
                //Maintenant, on s'occupe des tuiles sur les bords du plateau.

                //Si la tuile est sur le bord droit du plateau.
                if( (i==2 || i==4) && j==0 ){
                    pt_tuile->ligne = i;
                    pt_tuile->colonne = j;
                    pt_tuile->forme = 'T';
                    del_1_occ(all_types, pt_tuile->forme);
                    //Modification du tableau de la case.
                    creation_type_case(pt_tuile);
                    pt_tuile->fixe = 1;
                    pt_tuile->tresor = 1;
                    tresors -= 1;
                    pt_tuile->start_finish = 0;
                    //Modification de l'orientation.
                    tourner(pt_tuile, 270);
                }

                //Si la tuile est sur le bord gauche du plateau.
                else if( (i==2 || i==4) && j==6 ){
                    pt_tuile->ligne = i;
                    pt_tuile->colonne = j;
                    pt_tuile->forme = 'T';
                    del_1_occ(all_types, pt_tuile->forme);
                    //Modification du tableau de la case.
                    creation_type_case(pt_tuile);
                    pt_tuile->fixe = 1;
                    pt_tuile->tresor = 1;
                    tresors -= 1;
                    pt_tuile->start_finish = 0;
                    //Modification de l'orientation.
                    tourner(pt_tuile, 90);
                }

                //Nous avons fini de placer les tuiles fixes sur les bords à droite et à gauche. Maintenant,
                //plaçons les tuiles fixes sur les bords haut et bas.

                //Si la tuile est sur le bord du haut du plateau.
                else if( i==0 && (j==2 || j==4) ){
                    pt_tuile->ligne = i;
                    pt_tuile->colonne = j;
                    pt_tuile->forme = 'T';
                    del_1_occ(all_types, pt_tuile->forme);
                    //Modification du tableau de la case.
                    creation_type_case(pt_tuile);
                    pt_tuile->fixe = 1;
                    pt_tuile->tresor = 1;
                    tresors -= 1;
                    pt_tuile->start_finish = 0;
                    //Modification de l'orientation.
                    tourner(pt_tuile, 0);
                }

                //Si la tuile est sur le bord du bas du plateau.
                else if( i==6 && (j==2 || j==4) ){
                    pt_tuile->ligne = i;
                    pt_tuile->colonne = j;
                    pt_tuile->forme = 'T';
                    del_1_occ(all_types, pt_tuile->forme);
                    //Modification du tableau de la case.
                    creation_type_case(pt_tuile);
                    pt_tuile->fixe = 1;
                    pt_tuile->tresor = 1;
                    tresors -= 1;
                    pt_tuile->start_finish = 0;
                    //Modification de l'orientation.
                    tourner(pt_tuile, 180);
                }

                //Nous avons fini de placer toutes les tuiles fixes qui sont sur les bords du plateau. Nous allons
                //maintenant placer les tuiles fixes au centre du plateau.

                //Les quatre tuiles sont les mêmes à leur rotation près.
                if(i==2 && j==2){
                    pt_tuile->ligne = i;
                    pt_tuile->colonne = j;
                    pt_tuile->forme = 'T';
                    del_1_occ(all_types, pt_tuile->forme);
                    //Modification du tableau de la case.
                    creation_type_case(pt_tuile);
                    pt_tuile->fixe = 1;
                    pt_tuile->tresor = 1;
                    tresors -= 1;
                    pt_tuile->start_finish = 0;
                    //Modification de l'orientation.
                    tourner(pt_tuile, 270);
                }

                else if(i==2 && j==4){
                    pt_tuile->ligne = i;
                    pt_tuile->colonne = j;
                    pt_tuile->forme = 'T';
                    del_1_occ(all_types, pt_tuile->forme);
                    //Modification du tableau de la case.
                    creation_type_case(pt_tuile);
                    pt_tuile->fixe = 1;
                    pt_tuile->tresor = 1;
                    tresors -= 1;
                    pt_tuile->start_finish = 0;
                    //Modification de l'orientation.
                    tourner(pt_tuile, 0);
                }

                else if(i==4 && j==2){
                    pt_tuile->ligne = i;
                    pt_tuile->colonne = j;
                    pt_tuile->forme = 'T';
                    del_1_occ(all_types, pt_tuile->forme);
                    //Modification du tableau de la case.
                    creation_type_case(pt_tuile);
                    pt_tuile->fixe = 1;
                    pt_tuile->tresor = 1;
                    tresors -= 1;
                    pt_tuile->start_finish = 0;
                    //Modification de l'orientation.
                    tourner(pt_tuile, 180);
                }

                else if(i==4 && j==4){
                    pt_tuile->ligne = i;
                    pt_tuile->colonne = j;
                    pt_tuile->forme = 'T';
                    del_1_occ(all_types, pt_tuile->forme);
                    //Modification du tableau de la case.
                    creation_type_case(pt_tuile);
                    pt_tuile->fixe = 1;
                    pt_tuile->tresor = 1;
                    tresors -= 1;
                    pt_tuile->start_finish = 0;
                    //Modification de l'orientation.
                    tourner(pt_tuile, 90);
                }
            }

            ///Maintenant, nous allons créer toutes les autres tuiles qui sont mobiles.
            //Nous allons affecter toutes les caractéristiques de façon aléatoire.
            pt_tuile->ligne = i;
            pt_tuile->colonne = j;

            alea = rand()%(strlen(all_types) +1); //On choisit un type au hasard. Ici, alea est l'indice du type à
            //affecter.
            pt_tuile->forme = all_types[alea];
            del_1_occ(all_types, pt_tuile->forme);

            //Modification du tableau de la case.
            creation_type_case(pt_tuile);
            pt_tuile->fixe = 0;

            //On détermine si elle a un trésor ou non.
            if(pt_tuile->forme == 'I'){
                pt_tuile->tresor = 0;
            }
            else if(pt_tuile->forme == 'T'){
                pt_tuile->tresor = 1;
                tresors -= 1;
            }
            else{
                if(tresors!=0){
                    pt_tuile->tresor = 1;
                    tresors -= 1;
                }
                else{
                    pt_tuile->tresor = 0;
                }
            }

            pt_tuile->start_finish = 0;

            //Modification de l'orientation.
            alea = rand()%(3 +1);
            if(alea == 0){
                tourner(pt_tuile, 0);
            }
            else if(alea == 1){
                tourner(pt_tuile, 90);
            }
            else if(alea == 2){
                tourner(pt_tuile, 180);
            }
            else{
                tourner(pt_tuile, 270);
            }
        }
    }
    ///Maintenant que tout le plateau a des tuiles, nous pouvons mainteant créer la tuile en plus.
    pt_tuile->ligne = 7; //coordonnées impossibles
    pt_tuile->colonne = 7;
    pt_tuile->forme = all_types[0];
    del_1_occ(all_types, pt_tuile->forme);
    //Modification du tableau de la case.
    creation_type_case(pt_tuile);
    pt_tuile->fixe = 0;
    if(tresors!=0){
        pt_tuile->tresor = 1;
        tresors -= 1;
    }
    else{
        pt_tuile->tresor = 0;
    }
    pt_tuile->start_finish = 0;

    //Modification de l'orientation.
    //On la met à l'endroit car cette pièce va être tournée avant d'être jouée.
    tourner(pt_tuile, 0);
}


/*
 * Fonction permettant de déplacer les tuiles sur le plateau. Plus précisément, cette procédure déplace une ligne ou
 * une colonne.
 */

void deplacer_tuiles(t_case labyrinthe[7][7], t_case *tuile_en_plus, int ligne, int colonne){
    int i, j;
    t_case tuile_a_sortir;

    /* Pour déplacer les tuiles, il faut connaître le point d'entrée de la tuile en plus. Pour cela, on regarde où se
     * situe la tuile au début de la ligne ou colonne que l'on va pousser.
     * De plus, la position de la tuile est importante car ça détermine le mouvement de la ligne ou colonne.*/

    if(ligne==0){
        //La colonne se déplace vers le BAS. Pour plus de facilité, on commence par sortir la tuile du bas et on tire
        //la colonne.

        // on sort la tuile du bas
        tuile_a_sortir = labyrinthe[6][colonne];

        //on itère sur les lignes pour décaler dans les cases déjà déplacées
        for(i=6;i>0;i--){
            labyrinthe[i][colonne];


        } //


    }
    else if(ligne==6){


    }
    else{
        if(colonne == 0){


        }
        else if(colonne == 6){


        }
    }
}












