//
// Created by briac on 19/12/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "plateau.h"

/*
 * Fonction convertissant des degrés en radians
 */

float deg_rad(float deg){
    float rad;
    if( deg >= 360 ){ //Si on dépasse 360, alors on enlève 360 pour obtenir une rotation correcte.
        deg = deg - 360;
    }
    if( deg == 0 ){
        rad = 0;
    }
    else if( deg == 90 ){
        rad = M_PI/2;
    }
    else if( deg == 180 ){
        rad = M_PI;
    }
    else{
        rad = (3*M_PI)/2;
    }
    return rad;
}


/*
 * Fonction convertissant des radians en degrés
 */

float rad_deg(float rad){
    float deg;
    if( rad < 1 ){
        deg = 0;
    }
    else if( rad>1 && rad<2){ //Intervalle dans lequel se situe PI/2.
        deg = 90;
    }
    else if( rad>3 && rad<4 ){
        deg = 180;
    }
    else if(rad>4 && rad<5){
        deg = 270;
    }
    else if(rad >= 2*M_PI ){ //Si on dépasse 2PI, alors on enlève 2PI pour obtenir une rotation correcte.
            rad = rad - 2*M_PI;
            deg = rad_deg(rad);
    }

    return deg;
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
 * Procédure permettant de copier une structure case dans une autre.
 */

void copy_case(t_case *source, t_case *destination){
    int i,j;
    destination->forme = source->forme;
    destination->fixe = source->fixe;
    destination->rotation = source->rotation;
    destination->mini_case = source->mini_case;
    destination->tresor = source->tresor;
    destination->start_finish = source->start_finish;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            destination->tableau[i][j] = source->tableau[i][j];
        }
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
            if(i != 1 && j != 1){
                tuile->tableau[i][j] = '1'; // coins
            }
            else{
                tuile->tableau[i][j] = '0';
            }
        }
        printf("\n");
    }

    // On crée ensuite les formes, en enregistrant la position pour pouvoir la modifier.
    if(tuile->forme == 'T'){
        tuile->tableau[0][1] = '1';
        tuile->mini_case.ligne1 = 0;
        tuile->mini_case.colonne1 = 1;
    }
    if(tuile->forme == 'L'){
        tuile->tableau[1][0] = '1';
        tuile->tableau[2][1] = '1';
        tuile->mini_case.ligne1 = 1;
        tuile->mini_case.colonne1 = 0;
        tuile->mini_case.ligne2 = 2;
        tuile->mini_case.colonne2 = 1;
    }
    if(tuile->forme == 'I'){
        tuile->tableau[1][0] = '1';
        tuile->tableau[1][2] = '1';
        tuile->mini_case.ligne1 = 1;
        tuile->mini_case.colonne1 = 0;
        tuile->mini_case.ligne2 = 1;
        tuile->mini_case.colonne2 = 2;
    }
}


/*
 * Procédure modifiant l'orientation des cases.
 */

void tourner(t_case* tuile, float orientation){
    //Création de toutes les variables que l'on va utiliser.
    t_coord coord_interm, coord_I_1, coord_I_2;
    float rota_ini, rota_new, angleT, angleL_l1, angleL_c1, angleL_l2, angleL_c2, rota_new_save;
    float *p_r_ini, *p_or, *p_new;
    float rota_deg;
    int i,j;
    rota_ini = tuile->rotation;

    //on crée des pointeurs pour modifier leur valeur dans des procédures
    p_r_ini = &rota_ini;
    p_or = &orientation;
    p_new = &rota_new;

    //on convertit en radians la rotation que la case a actuellement
    *p_r_ini = deg_rad(*p_r_ini);
    //on convertit en radian la rotation que le joueur veut lui appliquer
    *p_or = deg_rad(*p_or);

    //Nous pouvons maintenant faire des modifications dans les métadonnées de la tuile.
    //Dans un premier temps, on veut la nouvelle valeur de la rotation.
    rota_new = (*p_r_ini) + (*p_or); // on additionne la rotation de base avec celle que l'on veut appliquer
    rota_deg = rad_deg(rota_new);
    rota_new_save = deg_rad(rota_deg); //on sauvegarde la rotation en radians pour faire tourner les pièces.
    tuile->rotation = rota_deg; //on met à jour la rotation de la pièce par rapport à sa position de base

    //Modifions le tableau de la tuile avec la nouvelle rotation.
    /* Forme de T.
     * Pour comprendre le code suivant, il faut dessiner un T dans une matrice 3x3. On remarque que si on veut faire
     * tourner le T dans le sens des aiguilles d'une montre, on doit déplacer le 0 dans la case [0][1] dans la case
     * [1][2] et ainsi de suite.
     * Pour comprendre l'utilisation des sinus, il faut faire des graphiques*/

    if(tuile->forme == 'T'){
        angleT = rota_new_save - (M_PI/2); //on manipule des radians avec les sinus
        coord_interm.ligne = 1 + (int)sinf(angleT);
        coord_interm.colonne = 1 + (int)sinf(rota_new_save);


        //Maintenant, on modifie le tableau de la case.
        tuile->tableau[coord_interm.ligne][coord_interm.colonne] = '1'; //on met le mur.
        //On enlève le mur sur l'ancien passage, sauf si c'est le point d'ou l'on vient
        if(coord_interm.ligne != tuile->mini_case.ligne1 || coord_interm.colonne != tuile->mini_case.colonne1){
            tuile->tableau[tuile->mini_case.ligne1][tuile->mini_case.colonne1] = '0';
        }

        //On change la valeur de la ligne et de la colonne dans la structure de sauvegarde.
        tuile->mini_case.ligne1 = coord_interm.ligne;
        tuile->mini_case.colonne1 = coord_interm.colonne;
    }

    /*Forme de L.
     * Pour les chemins en forme de L, il faut faire comme pour les chemins en T. Sauf que la position de départ des
     * deux cases à faire bouger sont différentes.
     * Il faut donc faire un graphique des valeurs des coordonnées des cases en fonction de la rotation (de la position
     * dans la matrice [3][3]).*/

    else if(tuile->forme == 'L'){
        // faire le graphique pour comprendre
        // Première case ( locomotive ).
        angleL_l1 = rota_new_save + M_PI;
        angleL_c1 = rota_new_save - (M_PI/2);

        coord_interm.ligne = 1 + (int)sinf(angleL_l1);
        coord_interm.colonne = 1 + (int)sinf(angleL_c1);

        //Maintenant, on modifie le tableau de la case.
        tuile->tableau[coord_interm.ligne][coord_interm.colonne] = '1';
        // si on ne va pas sur la case d'ou l'on vient, ni sur la case d'ou vient le second mur
        // alors on met notre case d'origine à 0
        if(
                (   coord_interm.ligne != tuile->mini_case.ligne1 ||
                    coord_interm.colonne != tuile->mini_case.colonne1
                ) &&
                (   coord_interm.ligne != tuile->mini_case.ligne2 ||
                    coord_interm.colonne != tuile->mini_case.colonne2
                )
           )
        {
            tuile->tableau[tuile->mini_case.ligne1][tuile->mini_case.colonne1] = '0';
        }


        // Deuxième case ( wagon ).
        angleL_l2 = rota_new_save + (M_PI/2);
        angleL_c2 = rota_new_save + M_PI;

        coord_interm.ligne = 1 + (int)sinf(angleL_l2);
        coord_interm.colonne = 1 + (int)sinf(angleL_c2);

        //Maintenant, on modifie le tableau de la case.
        tuile->tableau[coord_interm.ligne][coord_interm.colonne] = '1';
        // si on ne va pas sur la case d'ou l'on vient, ni sur la case d'ou vient le premier mur
        // alors on met notre case d'origine à 0.
        if(
                (   coord_interm.ligne != tuile->mini_case.ligne1 ||
                    coord_interm.colonne != tuile->mini_case.colonne1
                ) &&
                (   coord_interm.ligne != tuile->mini_case.ligne2 ||
                    coord_interm.colonne != tuile->mini_case.colonne2
                )
                )
        {
            tuile->tableau[tuile->mini_case.ligne2][tuile->mini_case.colonne2] = '0';
        }


        //On modifie les savegardes.
        tuile->mini_case.ligne2 = tuile->mini_case.ligne1;
        tuile->mini_case.colonne2 = tuile->mini_case.colonne1;
        tuile->mini_case.ligne1 = coord_interm.ligne;
        tuile->mini_case.colonne1 = coord_interm.colonne;
    }

    /* Forme de I.
     * Les explications sont les mêmes que pour les deux autres formes.*/

    else if(tuile->forme == 'I'){
        if( rota_new == 90 || rota_new == 270 ){ //Le chemin change d'orientation que si on applique 90 ou 270 degrés.
            if(tuile->mini_case.colonne1 == 0){
                //on sauvegarde les valeurs.
                coord_I_1.ligne = tuile->mini_case.ligne1;
                coord_I_1.colonne = tuile->mini_case.colonne1;
                coord_I_2.ligne = tuile->mini_case.ligne2;
                coord_I_2.colonne = tuile->mini_case.colonne2;

                //on commence par remplir les minis cases avec les murs.
                tuile->tableau[0][1] = '1';
                tuile->tableau[2][1] = '1';
                //Puis on enlève les murs qui doivent disparaître.
                tuile->tableau[coord_I_1.ligne][coord_I_1.colonne] = '0';
                tuile->tableau[coord_I_2.ligne][coord_I_2.colonne] = '0';

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

            //Toutes les tuiles auront des coordonnées donc on met ces deux lignes pour toutes les tuiles.
            pt_tuile->ligne = i;
            pt_tuile->colonne = j;

            ///Plaçons les tuiles de départ et d'arrivée.
            if( (i == 0 || i == 6) && (j == 0 || j == 6) ){
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

                //Ce sont toutes les mêmes pièces à l'exception de leur orientation.
                pt_tuile->forme = 'T';
                del_1_occ(all_types, pt_tuile->forme);
                //Modification du tableau de la case.
                creation_type_case(pt_tuile);
                pt_tuile->fixe = 1;
                pt_tuile->tresor = 1;
                pt_tuile->num_tresor = tresors; //On met le numéro du trésor car ils sont tous uniques.
                tresors -= 1;
                pt_tuile->start_finish = 0;

                //Modification de l'orientation.
                //Si la tuile est sur le bord droit du plateau.
                if( (i==2 || i==4) && j==0 ){
                    tourner(pt_tuile, 270);
                }
                //Si la tuile est sur le bord gauche du plateau.
                else if( (i==2 || i==4) && j==6 ){
                    tourner(pt_tuile, 90);
                }
                //Nous avons fini de placer les tuiles fixes sur les bords à droite et à gauche. Maintenant,
                //plaçons les tuiles fixes sur les bords haut et bas.

                //Si la tuile est sur le bord du haut du plateau.
                else if( i==0 && (j==2 || j==4) ){
                    tourner(pt_tuile, 0);
                }
                //Si la tuile est sur le bord du bas du plateau.
                else if( i==6 && (j==2 || j==4) ){
                    tourner(pt_tuile, 180);
                }

                //Nous avons fini de placer toutes les tuiles fixes qui sont sur les bords du plateau. Nous allons
                //maintenant placer les tuiles fixes au centre du plateau.

                //Les quatre tuiles sont les mêmes à leur rotation près.
                if(i==2 && j==2){
                    tourner(pt_tuile, 270);
                }
                else if(i==2 && j==4){
                    tourner(pt_tuile, 0);
                }
                else if(i==4 && j==2){
                    tourner(pt_tuile, 180);
                }
                else if(i==4 && j==4){
                    tourner(pt_tuile, 90);
                }
            }

            ///Maintenant, nous allons créer toutes les autres tuiles qui sont mobiles.
            else{
                //Nous allons affecter toutes les caractéristiques de façon aléatoire.

                alea = rand()%(strlen(all_types) +1); //On choisit un type au hasard. Ici, alea est l'indice du type à
                //affecter.
                pt_tuile->forme = all_types[alea];
                del_1_occ(all_types, pt_tuile->forme);

                //Modification du tableau de la case.
                creation_type_case(pt_tuile);
                pt_tuile->fixe = 0;

                //On détermine si elle a un trésor ou non.
                if(pt_tuile->forme == 'I'){ //Chemin en forme de I.
                    pt_tuile->tresor = 0;
                }
                else if(pt_tuile->forme == 'T'){ //Chemin en forme de T.
                    pt_tuile->tresor = 1;
                    pt_tuile->num_tresor = tresors;
                    tresors -= 1;
                }
                else{ //Chemin en forme de L.
                    if(tresors!=0){
                        pt_tuile->tresor = 1;
                        pt_tuile->num_tresor = tresors;
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
    }
    ///Maintenant que tout le plateau a des tuiles, nous pouvons maintenant créer la tuile en plus.
    pt_tuile->ligne = 7; //coordonnées impossibles
    pt_tuile->colonne = 7;
    pt_tuile->forme = all_types[0];
    del_1_occ(all_types, pt_tuile->forme);
    //Modification du tableau de la case.
    creation_type_case(pt_tuile);
    pt_tuile->fixe = 0;
    if(tresors!=0){
        pt_tuile->tresor = 1;
        pt_tuile->num_tresor = tresors;
        tresors -= 1;
    }
    else{
        pt_tuile->tresor = 0;
    }
    pt_tuile->start_finish = 0;

    //Modification de l'orientation.
    //On la met à l'endroit car cette pièce va être tournée avant d'être jouée, donc l'orientation importe peu.
    tourner(pt_tuile, 0);
}


/*
 * Fonction permettant de déplacer les tuiles sur le plateau. Plus précisément, cette procédure déplace une ligne ou
 * une colonne.
 */

void deplacer_tuiles(t_case labyrinthe[7][7], t_case *tuile_en_plus, t_coord *coord){
    int i, j;
    t_case tuile_a_sortir;
    t_case *pt_sortir = &tuile_a_sortir;

    //On remplit de données inutiles car c'est juste une 'tuile' de transition.
    pt_sortir->ligne = 7; //coordonnées impossibles
    pt_sortir->colonne = 7;
    pt_sortir->forme = 'W'; //Peu importe le type.
    //Modification du tableau de la case.
    creation_type_case(pt_sortir);
    pt_sortir->fixe = 0;
    pt_sortir->tresor = 0;
    pt_sortir->start_finish = 0;
    tourner(pt_sortir, 0);

    /* Pour déplacer les tuiles, il faut connaître le point d'entrée de la tuile en plus. Pour cela, on regarde où se
     * situe la tuile au début de la ligne ou colonne que l'on va pousser.
     * De plus, la position de la tuile est importante car ça détermine le mouvement de la ligne ou colonne.*/

    if(coord->ligne==0){
        //La colonne se déplace vers le BAS. Pour plus de facilité, on commence par sortir la tuile du bas et on tire
        //la colonne.
        // on sort la tuile du bas
        copy_case(&labyrinthe[6][coord->colonne], pt_sortir);

        //on itère sur les lignes pour décaler dans les cases déjà déplacées (on tire vers le bas).
        for(i=5;i>=0;i--){
            copy_case(&labyrinthe[i][coord->colonne], &labyrinthe[i+1][coord->colonne]);
        }

        //Maintenant on intègre la tuile en trop qui pousse la colonne.
        copy_case(tuile_en_plus, &labyrinthe[0][coord->colonne]);

        ///ATTENTION, pt_sortir devient dorénavant la tuile en plus. Donc on modifie le pointage.
        copy_case(pt_sortir,tuile_en_plus);
    }
    else if(coord->ligne==6){
        //La colonne se déplace vers le HAUT. Pour plus de facilité, on commence par sortir la tuile du haut et on tire
        //la colonne.
        // on sort la tuile du haut.
        copy_case(&labyrinthe[0][coord->colonne], pt_sortir);

        //on itère sur les lignes pour décaler dans les cases déjà déplacées (on tire vers le haut).
        for(i=0;i<=5;i++){
            copy_case(&labyrinthe[i+1][coord->colonne], &labyrinthe[i][coord->colonne]);
        }

        //Maintenant on intègre la tuile en trop qui pousse la colonne.
        copy_case(tuile_en_plus, &labyrinthe[6][coord->colonne]);

        ///ATTENTION, pt_sortir devient dorénavant la tuile en plus. Donc on modifie le pointage.
        copy_case(pt_sortir,tuile_en_plus);
    }
    else{
        if(coord->colonne == 0){
            //La ligne se déplace vers la droite. Pour plus de facilité, on commence par sortir la tuile tout à droite
            // et on tire la ligne.
            // On sort la tuile de droite.
            copy_case(&labyrinthe[coord->ligne][6], pt_sortir);

            //on itère sur les lignes pour décaler dans les cases déjà déplacées (on tire vers la droite).
            for(j=5;j>=0;j--){
                copy_case(&labyrinthe[coord->ligne][j], &labyrinthe[coord->ligne][j+1]);
            }

            //Maintenant on intègre la tuile en trop qui pousse la colonne.
            copy_case(tuile_en_plus, &labyrinthe[coord->ligne][0]);

            ///ATTENTION, pt_sortir devient dorénavant la tuile en plus. Donc on modifie le pointage.
            copy_case(pt_sortir,tuile_en_plus);
        }
        else if(coord->colonne == 6){
            //La ligne se déplace vers la gauche. Pour plus de facilité, on commence par sortir la tuile tout à gauche
            // et on tire la ligne.
            // On sort la tuile de gauche.
            copy_case(&labyrinthe[coord->ligne][0], pt_sortir);

            //on itère sur les lignes pour décaler dans les cases déjà déplacées (on tire vers la gauche).
            for(j=0;j<=5;j++){
                copy_case(&labyrinthe[coord->ligne][j+1], &labyrinthe[coord->ligne][j]);
            }

            //Maintenant on intègre la tuile en trop qui pousse la colonne.
            copy_case(tuile_en_plus, &labyrinthe[coord->ligne][6]);

            ///ATTENTION, pt_sortir devient dorénavant la tuile en plus. Donc on modifie le pointage.
            copy_case(pt_sortir,tuile_en_plus);
        }
    }
}












