//
// Created by briac on 19/12/2022.
//
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "plateau.h"
#include "pion.h"

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
    }

    // On crée ensuite les formes, en enregistrant la position pour pouvoir la modifier.
    if(tuile->forme == 'T'){
        tuile->tableau[0][1] = '1';
        tuile->mini_case.ligne1 = 0;
        tuile->mini_case.colonne1 = 1;
    }
    else if(tuile->forme == 'L'){
        tuile->tableau[1][0] = '1';
        tuile->tableau[2][1] = '1';
        tuile->mini_case.ligne1 = 1;
        tuile->mini_case.colonne1 = 0;
        tuile->mini_case.ligne2 = 2;
        tuile->mini_case.colonne2 = 1;
    }
    else if(tuile->forme == 'I'){
        tuile->tableau[1][0] = '1';
        tuile->tableau[1][2] = '1';
        tuile->mini_case.ligne1 = 1;
        tuile->mini_case.colonne1 = 0;
        tuile->mini_case.ligne2 = 1;
        tuile->mini_case.colonne2 = 2;
    }
}


/*
 * Procédure permettant de copier une structure case dans une autre.
 */

void copy_case(t_case *source, t_case *destination){
    int i,j;
    destination->ligne = source->ligne;
    destination->colonne = source->colonne;
    destination->forme = source->forme;
    destination->fixe = source->fixe;
    destination->rotation = source->rotation;
    destination->mini_case = source->mini_case;
    destination->tresor.num_tresor = source->tresor.num_tresor;
    destination->tresor.un_tresor = source->tresor.un_tresor;
    destination->start_finish = source->start_finish;
    destination->sortie_du_plateau.ligne = source->sortie_du_plateau.ligne;
    destination->sortie_du_plateau.colonne = source->sortie_du_plateau.colonne;
    for(i=0;i<3;i++){
        for(j=0;j<3;j++){
            destination->tableau[i][j] = source->tableau[i][j];
        }
    }
}


/*
 * Procédure modifiant l'orientation des cases.
 */

void tourner(t_case* tuile, float orientation){
    //Création de toutes les variables que l'on va utiliser.
    t_coord coord_interm, coord_premiermur, coord_I_1, coord_I_2;
    float rota_ini, rota_new, angleT, angleL_l1, angleL_c1, angleL_l2, angleL_c2, rota_new_save;
    float *p_r_ini, *p_or, *p_new;
    float rota_deg;
    int i,j;
    rota_ini = tuile->rotation;

    //on convertit en radians la rotation que la case a actuellement
    rota_ini = deg_rad(rota_ini);
    //on convertit en radian la rotation que le joueur veut lui appliquer
    orientation = deg_rad(orientation);

    //Nous pouvons maintenant faire des modifications dans les métadonnées de la tuile.
    //Dans un premier temps, on veut la nouvelle valeur de la rotation.
    rota_new = (rota_ini) + (orientation); // on additionne la rotation de base avec celle que l'on veut appliquer
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
        // si on ne va pas sur la case d'ou l'on vient
        // alors on met notre case d'origine à 0
        if(
                (   coord_interm.ligne != tuile->mini_case.ligne1 ||
                    coord_interm.colonne != tuile->mini_case.colonne1
                )
           )
        {
            tuile->tableau[tuile->mini_case.ligne1][tuile->mini_case.colonne1] = '0';
        }
        coord_premiermur = coord_interm;

        // Deuxième case ( wagon ).
        angleL_l2 = rota_new_save + (M_PI/2);
        angleL_c2 = rota_new_save + M_PI;

        coord_interm.ligne = 1 + (int)sinf(angleL_l2);
        coord_interm.colonne = 1 + (int)sinf(angleL_c2);

        //Maintenant, on modifie le tableau de la case.
        tuile->tableau[coord_interm.ligne][coord_interm.colonne] = '1';
        // si on ne va pas sur la case d'ou l'on vient
        // et que le premier mur ne vient pas sur notre case d'origine
        // alors on met notre case d'origine à 0.
        if(
             (
                coord_interm.ligne != tuile->mini_case.ligne2 ||
                coord_interm.colonne != tuile->mini_case.colonne2
             ) &&
             (
                coord_premiermur.ligne != tuile->mini_case.ligne2 ||
                coord_premiermur.colonne != tuile->mini_case.colonne2
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

    else if(tuile->forme == 'I'){//&& ((int)tuile->rotation%180 == 0)
        if( (rota_deg == 90 || rota_deg == 270)  ){ //Le chemin change d'orientation que si on applique 90 ou 270 degrés.
            if(tuile->mini_case.colonne1 == 0){ //Si le I est à l'endroit.
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
            else{
                //on sauvegarde les valeurs.
                coord_I_1.ligne = tuile->mini_case.ligne1;
                coord_I_1.colonne = tuile->mini_case.colonne1;
                coord_I_2.ligne = tuile->mini_case.ligne2;
                coord_I_2.colonne = tuile->mini_case.colonne2;

                //on commence par remplir les minis cases avec les murs.
                tuile->tableau[1][0] = '1';
                tuile->tableau[1][2] = '1';
                //Puis on enlève les murs qui doivent disparaître.
                tuile->tableau[coord_I_1.ligne][coord_I_1.colonne] = '0';
                tuile->tableau[coord_I_2.ligne][coord_I_2.colonne] = '0';

                //On affecte les nouvelles coordonnées.
                tuile->mini_case.ligne1 = 1;
                tuile->mini_case.colonne1 = 0;
                tuile->mini_case.ligne2 = 1;
                tuile->mini_case.colonne2 = 2;
            }
        }
        else{
            creation_type_case(tuile);
        }
    }
}


/*
 * Nous créons le plateau de jeu
 */

void generation_plateau_debut(t_case labyrinthe[7][7], t_case* tuile_add, FILE * fichierlog){
    int i,j, alea;
    int tresors_tuile_fixe = 11; // 12 tresors sur tuiles fixes vont de 0 a 11
    int tresors_tuile_T = 17; // 6 tresors sur tuiles mobiles vont de 12 à 17
    int tresors_tuile_L = 23; // 6 tresors sur tuiles mobiles vont de 18 à 23
    char all_types[51]; //liste de tous les types.
    t_case *pt_tuile;
    // pour random sur les tresors a positionner sur les cases L
    int L_avec_tresors[16];
    int nb_tresors_mis;
    int num, num_L;

    srand(time(NULL));

    fprintf(fichierlog, "generation_plateau_debut()\n");
    fflush(fichierlog);
    //On met le bon nombre de chaque forme de case.
    for(i=0;i<50;i++){
        if(i<18){
            all_types[i] = 'T';
        }
        else if(i<39){
            all_types[i] = 'L';
        }
        else{
            all_types[i] = 'I';
        }
    }
    // on transforme le tableau en chaine de caractere pour la suite
    all_types[50] = '\0';


    // on tire au hasard les 6 tuiles L sur les 16 sur lesquelles mettre des trésors
    // on veut 6 nombres entre 1 et 16
    // on initialise le tableau a zero
    for(i=0;i<16;i++){
        L_avec_tresors[i] = 0;
    }
    nb_tresors_mis = 0;
    while(nb_tresors_mis < 6){
        // MIN + rand()(MAX-MIN+1)
        num = rand()%(16); // nombre entre 0 et 15
        if(L_avec_tresors[num] == 0){
            L_avec_tresors[num] = 1;
            nb_tresors_mis +=1;
        }
    }
    // on positionne le numero de L posé à Zero
    num_L = 0;

    /*Dans un premier temps, on place les tuiles fixes (qui ont des chemins particuliers et des orientations
     *particulières). Ensuite, on placera les autres en leur donnant une forme et une orientation de manière aléatoire.*/

    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            //On crée un pointeur sur la tuile à modifier.
            pt_tuile = &labyrinthe[i][j];

            //Toutes les tuiles auront des coordonnées donc on met ces deux lignes pour toutes les tuiles.
            pt_tuile->ligne = i;
            pt_tuile->colonne = j;
            //Les coordonnées de sortie nous importent peu maintenant mais on les remplit quand même.
            pt_tuile->sortie_du_plateau.ligne = i;
            pt_tuile->sortie_du_plateau.colonne = j;

            ///Plaçons les tuiles de départ et d'arrivée, a chaque angle du plateau
            if( (i == 0 || i == 6) && (j == 0 || j == 6) ){
                pt_tuile->forme = 'L';
                del_1_occ(all_types, pt_tuile->forme);
                //Modification du tableau de la case.
                creation_type_case(pt_tuile);
                pt_tuile->fixe = 1;
                pt_tuile->tresor.un_tresor = 0;
                pt_tuile->tresor.num_tresor = 25; // Pas de trésors.
                pt_tuile->start_finish = 1;
                pt_tuile->rotation =0;
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

            ///Ici, on s'occupe de toutes les autres tuiles FIXES - toutes les deux lignes et deux colonnes
            else if(j%2==0 && i%2==0){
                //Maintenant, on s'occupe des tuiles sur les bords du plateau.

                //Ce sont toutes les mêmes pièces à l'exception de leur orientation.
                pt_tuile->forme = 'T';
                del_1_occ(all_types, pt_tuile->forme);
                //Modification du tableau de la case.
                creation_type_case(pt_tuile);
                pt_tuile->fixe = 1;
                pt_tuile->tresor.un_tresor = 1;
                pt_tuile->tresor.num_tresor = tresors_tuile_fixe; //On met le numéro du trésor car ils sont tous uniques.
                tresors_tuile_fixe -= 1;
                pt_tuile->start_finish = 0;
                pt_tuile->rotation =0;

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

                //On choisit un type au hasard.
                // Ici, alea est l'indice du type à affecter.
                alea = rand()%(strlen(all_types));
                pt_tuile->forme = all_types[alea];
                del_1_occ(all_types, pt_tuile->forme);

                //Modification du tableau de la case.
                creation_type_case(pt_tuile);
                pt_tuile->fixe = 0;

                //On détermine si elle a un trésor ou non.
                if(pt_tuile->forme == 'I'){ //Chemin en forme de I.
                    pt_tuile->tresor.un_tresor = 0;
                    pt_tuile->tresor.num_tresor = 25;
                }
                else if(pt_tuile->forme == 'T'){ //Chemin en forme de T.
                    if(tresors_tuile_T > 11) {
                        pt_tuile->tresor.un_tresor = 1;
                        pt_tuile->tresor.num_tresor = tresors_tuile_T;
                        tresors_tuile_T -= 1;
                    }
                    else{
                        pt_tuile->tresor.un_tresor = 0;
                        pt_tuile->tresor.num_tresor = 25;
                    }
                }
                else{ //Chemin en forme de L.
                    num_L += 1;
                    if(tresors_tuile_L > 17 && L_avec_tresors[num_L] == 1) {
                        pt_tuile->tresor.un_tresor = 1;
                        pt_tuile->tresor.num_tresor = tresors_tuile_L;
                        tresors_tuile_L -= 1;
                    }
                    else{
                        pt_tuile->tresor.un_tresor = 0;
                        pt_tuile->tresor.num_tresor = 25;
                    }
                }

                pt_tuile->start_finish = 0;

                //Modification de l'orientation.
                pt_tuile->rotation =0;
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
    tuile_add->ligne = 7; //coordonnées impossibles
    tuile_add->colonne = 7;
    tuile_add->sortie_du_plateau.ligne = 7;
    tuile_add->sortie_du_plateau.colonne = 7;
    tuile_add->forme = all_types[0];
    del_1_occ(all_types, tuile_add->forme);
    //Modification du tableau de la case.
    creation_type_case(tuile_add);
    tuile_add->fixe = 0;
    if(tuile_add->forme == 'L' && tresors_tuile_L > 17){
        tuile_add->tresor.un_tresor = 1;
        tuile_add->tresor.num_tresor = tresors_tuile_L;
        tresors_tuile_L -= 1;
    }else if(tuile_add->forme == 'T'){
        tuile_add->tresor.un_tresor = 1;
        tuile_add->tresor.num_tresor = tresors_tuile_T;
        tresors_tuile_T -= 1;
    }else{
        tuile_add->tresor.un_tresor = 0;
        tuile_add->tresor.num_tresor = 25;
    }
    tuile_add->start_finish = 0;

    //Modification de l'orientation.
    //On la met à l'endroit car cette pièce va être tournée avant d'être jouée, donc l'orientation importe peu.
    tuile_add->rotation =0;
    tourner(tuile_add, 0);
}















