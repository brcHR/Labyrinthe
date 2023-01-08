//
// Created by Maxime Vennin on 30/12/2022.
//

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include "Deroulement.h"
#include "affichage.h"
#include "cartestresors.h"

/*
 * Fonction permettant de déplacer les tuiles sur le plateau. Plus précisément, cette procédure déplace une ligne ou
 * une colonne.
 */

void deplacer_tuiles(t_case labyrinthe[7][7], t_case *tuile_en_plus, t_coord *coord, t_pion pions[4], int nbjoueurs,
                     FILE *fichierlog) {
    int i, j, test, pion_la;
    t_case tuile_a_sortir;
    t_case *pt_sortir = &tuile_a_sortir;


    //On remplit de données inutiles car c'est juste une 'tuile' de transition.
    pt_sortir->ligne = 7; //coordonnées impossibles
    pt_sortir->colonne = 7;
    pt_sortir->forme = 'W'; //Peu importe le type.
    //Modification du tableau de la case.
    creation_type_case(pt_sortir);
    pt_sortir->fixe = 0;
    pt_sortir->tresor.un_tresor = 0;
    pt_sortir->tresor.num_tresor = 25;
    pt_sortir->start_finish = 0;
    pt_sortir->sortie_du_plateau.ligne = 7;
    pt_sortir->sortie_du_plateau.colonne = 7;

    tourner(pt_sortir, 0);

    /* Pour déplacer les tuiles, il faut connaître le point d'entrée de la tuile en plus. Pour cela, on regarde où se
     * situe la tuile au début de la ligne ou colonne que l'on va pousser.
     * De plus, la position de la tuile est importante car ça détermine le mouvement de la ligne ou colonne.*/

    // On vérifie qu'on ne remette pas la tuile en plus là où elle a été sortie.
    if (
        //L'ancien déplacement était horizontal.
            (
                    coord->ligne == tuile_en_plus->sortie_du_plateau.ligne // Même ligne.
                    &&
                    (
                            coord->colonne ==
                            tuile_en_plus->sortie_du_plateau.colonne + 1 // Si sortie plateau colonne = -1
                            ||
                            coord->colonne ==
                            tuile_en_plus->sortie_du_plateau.colonne - 1 // Si sortie plateau colonne = 7
                    )
            )
            ||
            //L'ancien déplacement était vertical.
            (
                    coord->colonne == tuile_en_plus->sortie_du_plateau.colonne //Même colonne.
                    &&
                    (
                            coord->ligne == tuile_en_plus->sortie_du_plateau.ligne + 1 // Si sortie plateau ligne = -1
                            ||
                            coord->ligne == tuile_en_plus->sortie_du_plateau.ligne - 1 // Si sortie plateau ligne = 7

                    )
            )

            ) {
        printf("Vous ne pouvez pas remettre la tuile à l'endroit où elle est sortie.\n");
        fprintf(fichierlog, "la tuile a ete remise a l'endroit de sa sortie\n");
        fflush(fichierlog);
    }


        /*
         * ON DEPLACE LES RANGEES
         */

    else {
        /*
         * DEPLACEMENT VERTICAL
         */
        if (coord->ligne == 0) {
            fprintf(fichierlog, "Insertion en ligne 0\n");
            fflush(fichierlog);
            //On vérifie que la colonne à faire bouger n'est pas une colonne fixe.
            if (labyrinthe[coord->ligne][coord->colonne].fixe != 1) {

                /*
                 * VERS LE BAS
                 */
                fprintf(fichierlog, "Deplacement vers le bas\n");
                fflush(fichierlog);
                //La colonne se déplace vers le BAS. Pour plus de facilité, on commence par sortir la tuile du bas et on tire
                //la colonne.
                // on sort la tuile du bas
                copy_case(&labyrinthe[6][coord->colonne], pt_sortir);

                pt_sortir->sortie_du_plateau.ligne = 7; //On met une ligne impossible...
                pt_sortir->sortie_du_plateau.colonne = coord->colonne;//...mais on garde la colonne d'où elle sort.
                // on teste si un pion est présent sur la tuile qui vient de sortir, et on le positionne en 7
                for (pion_la = 0; pion_la < nbjoueurs; pion_la++) {
                    if (pions[pion_la].position_pion == &labyrinthe[6][coord->colonne]) {

                        //S'il y a un pion, alors on le fait pointer sur sa nouvelle case.
                        pions[pion_la].lig = 7;
                        pions[pion_la].col = coord->colonne;
                    }
                }

                //on itère sur les lignes pour décaler dans les cases déjà déplacées (on tire vers le bas).
                for (i = 5; i >= 0; i--) {

                    //On copie la case.
                    copy_case(&labyrinthe[i][coord->colonne], &labyrinthe[i + 1][coord->colonne]);

                    //On met à jour les coordonnées de sortie du placteau de la case.
                    labyrinthe[i + 1][coord->colonne].sortie_du_plateau.ligne = i + 1;
                    labyrinthe[i + 1][coord->colonne].sortie_du_plateau.colonne = coord->colonne;

                    //On vérifie pour tous les pions si ils sont sur la case qui a été bougée.
                    for (pion_la = 0; pion_la < nbjoueurs; pion_la++) {
                        if (pions[pion_la].position_pion == &labyrinthe[i][coord->colonne]) {

                            //S'il y a un pion, alors on le fait pointer sur sa nouvelle case.
                            pions[pion_la].position_pion = &labyrinthe[i + 1][coord->colonne];
                            pions[pion_la].lig = i + 1;
                            pions[pion_la].col = coord->colonne;
                        }
                    }
                }

                //Maintenant on intègre la tuile en trop qui pousse la colonne.
                copy_case(tuile_en_plus, &labyrinthe[0][coord->colonne]);

                //On met à jour les coordonnées de sortie du placteau de la case.
                labyrinthe[0][coord->colonne].sortie_du_plateau.ligne = 0;
                labyrinthe[0][coord->colonne].sortie_du_plateau.colonne = coord->colonne;

                ///ATTENTION, pt_sortir devient dorénavant la tuile en plus. Donc on modifie le pointage.
                copy_case(pt_sortir, tuile_en_plus);

            } else {
                printf("La colonne est fixe\n");
                fprintf(fichierlog, "Insertion sur une colonne fixe!\n");
                fflush(fichierlog);
            }

        } else if (coord->ligne == 6) {
            fprintf(fichierlog, "Insertion en ligne 6, decalage vers le haut\n");
            fflush(fichierlog);
            //On vérifie que la colonne à faire bouger n'est pas une colonne fixe.
            if (labyrinthe[coord->ligne][coord->colonne].fixe != 1) {

                /*
                 * VERS LE HAUT
                 */
                //La colonne se déplace vers le HAUT. Pour plus de facilité, on commence par sortir la tuile du haut et on tire
                //la colonne.
                // on sort la tuile du haut.
                //TODO meme pb que quand on deplace rangée : comment on dit que le pion doit toujours regarder sa tuile?
                copy_case(&labyrinthe[0][coord->colonne], pt_sortir);
                pt_sortir->sortie_du_plateau.ligne = -1; //On met une ligne impossible...
                pt_sortir->sortie_du_plateau.colonne = coord->colonne;//...mais on garde la colonne d'où elle sort.
                // on teste si un pion est présent sur la tuile qui vient de sortir, et on le positionne en -1
                for (pion_la = 0; pion_la < nbjoueurs; pion_la++) {
                    if (pions[pion_la].position_pion == &labyrinthe[0][coord->colonne]) {

                        //S'il y a un pion, alors on le fait pointer sur sa nouvelle case.
                        pions[pion_la].lig = -1;
                        pions[pion_la].col = coord->colonne;
                    }
                }

                //on itère sur les lignes pour décaler dans les cases déjà déplacées (on tire vers le haut).
                for (i = 0; i <= 5; i++) {
                    copy_case(&labyrinthe[i + 1][coord->colonne], &labyrinthe[i][coord->colonne]);

                    //On met à jour les coordonnées de sortie du placteau de la case.
                    labyrinthe[i][coord->colonne].sortie_du_plateau.ligne = i;
                    labyrinthe[i][coord->colonne].sortie_du_plateau.colonne = coord->colonne;

                    //On vérifie pour tous les pions si il sont sur la case qui a été bougée.
                    for (pion_la = 0; pion_la < nbjoueurs; pion_la++) {
                        if (pions[pion_la].position_pion == &labyrinthe[i + 1][coord->colonne]) {

                            //S'il y a un pion, alors on le fait pointer sur sa nouvelle case.
                            pions[pion_la].position_pion = &labyrinthe[i][coord->colonne];
                            pions[pion_la].lig = i;
                            pions[pion_la].col = coord->colonne;
                        }
                    }
                }

                //Maintenant on intègre la tuile en trop qui pousse la colonne.
                copy_case(tuile_en_plus, &labyrinthe[6][coord->colonne]);

                //On met à jour les coordonnées de sortie du placteau de la case.
                labyrinthe[6][coord->colonne].sortie_du_plateau.ligne = 6;
                labyrinthe[6][coord->colonne].sortie_du_plateau.colonne = coord->colonne;

                ///ATTENTION, pt_sortir devient dorénavant la tuile en plus. Donc on modifie le pointage.
                copy_case(pt_sortir, tuile_en_plus);
            } else {
                printf("La colonne est fixe\n");
                fprintf(fichierlog, "la colonne est fixe !!\n");
                fflush(fichierlog);

            }
        }

            /*
             * DEPLACEMENT HORIZONTAL
             */

        else {
            if (coord->colonne == 0) {
                fprintf(fichierlog, "Insertion en colonne 0\n");
                fflush(fichierlog);

                //On vérifie que la ligne à faire bouger n'est pas une colonne fixe.
                if (labyrinthe[coord->ligne][coord->colonne].fixe != 1) {

                    /*
                     * VERS LA DROITE
                     */
                    fprintf(fichierlog, "decalage vers la droite\n");
                    fflush(fichierlog);

                    //La ligne se déplace vers la droite. Pour plus de facilité, on commence par sortir la tuile tout à droite
                    // et on tire la ligne.
                    // On sort la tuile de droite.
                    copy_case(&labyrinthe[coord->ligne][6], pt_sortir);
                    pt_sortir->sortie_du_plateau.ligne = coord->ligne; //On garde la colonne d'où elle sort...
                    pt_sortir->sortie_du_plateau.colonne = 7;//...mais on met une ligne impossible.
                    // on teste si un pion est présent sur la tuile qui vient de sortir, et on le positionne en 7
                    for (pion_la = 0; pion_la < nbjoueurs; pion_la++) {
                        if (pions[pion_la].position_pion == &labyrinthe[coord->ligne][6]) {

                            //S'il y a un pion, alors on le fait pointer sur sa nouvelle case.
                            pions[pion_la].lig = coord->ligne;
                            pions[pion_la].col = 7;
                        }
                    }
                    //on itère sur les colonnes pour décaler dans les cases déjà déplacées (on tire vers la droite).
                    for (j = 5; j >= 0; j--) {
                        copy_case(&labyrinthe[coord->ligne][j], &labyrinthe[coord->ligne][j + 1]);

                        //On met à jour les coordonnées de sortie du placteau de la case.
                        labyrinthe[coord->ligne][j+1].sortie_du_plateau.ligne = coord->ligne;
                        labyrinthe[coord->ligne][j+1].sortie_du_plateau.colonne = j+1;

                        //On vérifie pour tous les pions si il sont sur la case qui a été bougée.
                        for (pion_la = 0; pion_la < nbjoueurs; pion_la++) {
                            if (pions[pion_la].position_pion == &labyrinthe[coord->ligne][j]) {

                                //S'il y a un pion, alors on le fait pointer sur sa nouvelle case.
                                pions[pion_la].position_pion = &labyrinthe[coord->ligne][j + 1];
                                pions[pion_la].lig = coord->ligne;
                                pions[pion_la].col = j + 1;
                            }
                        }
                    }

                    //Maintenant on intègre la tuile en trop qui pousse la colonne.
                    copy_case(tuile_en_plus, &labyrinthe[coord->ligne][0]);

                    //On met à jour les coordonnées de sortie du placteau de la case.
                    labyrinthe[coord->ligne][0].sortie_du_plateau.ligne = coord->ligne;
                    labyrinthe[coord->ligne][0].sortie_du_plateau.colonne = 0;

                    ///ATTENTION, pt_sortir devient dorénavant la tuile en plus. Donc on modifie le pointage.
                    copy_case(pt_sortir, tuile_en_plus);
                } else {
                    printf("La ligne est fixe\n");
                    fprintf(fichierlog, "la ligne est fixe !\n");
                    fflush(fichierlog);

                }
            } else if (coord->colonne == 6) {
                fprintf(fichierlog, "Insertion en colonne 6\n");
                fflush(fichierlog);
                //On vérifie que la ligne à faire bouger n'est pas une colonne fixe.
                if (labyrinthe[coord->ligne][coord->colonne].fixe != 1) {
                    fprintf(fichierlog, "la colonne n'est pas fixe\n");
                    fflush(fichierlog);

                    /*
                     * VERS LA GAUCHE
                     */

                    //La ligne se déplace vers la gauche. Pour plus de facilité, on commence par sortir la tuile tout à gauche
                    // et on tire la ligne.
                    // On sort la tuile de gauche.
                    copy_case(&labyrinthe[coord->ligne][0], pt_sortir);
                    pt_sortir->sortie_du_plateau.ligne = coord->ligne; //On garde la colonne d'où elle sort...
                    pt_sortir->sortie_du_plateau.colonne = -1;//...mais on met une ligne impossible.
                    // on teste si un pion est présent sur la tuile qui vient de sortir, et on le positionne en -1
                    for (pion_la = 0; pion_la < nbjoueurs; pion_la++) {
                        if (pions[pion_la].position_pion == &labyrinthe[coord->ligne][0]) {

                            //S'il y a un pion, alors on le fait pointer sur sa nouvelle case.
                            pions[pion_la].lig = coord->ligne;
                            pions[pion_la].col = -1;
                        }
                    }


                    //on itère sur les colonnes pour décaler dans les cases déjà déplacées (on tire vers la gauche).
                    for (j = 0; j <= 5; j++) {
                        copy_case(&labyrinthe[coord->ligne][j + 1],
                                  &labyrinthe[coord->ligne][j]);

                        //On met à jour les coordonnées de sortie du plateau de la case.
                        labyrinthe[coord->ligne][j].sortie_du_plateau.ligne = coord->ligne;
                        labyrinthe[coord->ligne][j].sortie_du_plateau.colonne = j;

                        //On vérifie pour tous les pions si il sont sur la case qui a été bougée.
                        for (pion_la = 0; pion_la < nbjoueurs; pion_la++) {
                            if (pions[pion_la].position_pion == &labyrinthe[coord->ligne][j + 1]) {

                                //S'il y a un pion, alors on le fait pointer sur sa nouvelle case.
                                pions[pion_la].position_pion = &labyrinthe[coord->ligne][j];
                                pions[pion_la].lig = coord->ligne;
                                pions[pion_la].col = j;
                            }
                        }
                    }

                    //Maintenant on intègre la tuile en trop qui pousse la colonne.
                    copy_case(tuile_en_plus, &labyrinthe[coord->ligne][6]);

                    //On met à jour les coordonnées de sortie du plateau de la case.
                    labyrinthe[coord->ligne][6].sortie_du_plateau.ligne = coord->ligne;
                    labyrinthe[coord->ligne][6].sortie_du_plateau.colonne = 6;

                    ///ATTENTION, pt_sortir devient dorénavant la tuile en plus. Donc on modifie le pointage.
                    copy_case(pt_sortir, tuile_en_plus);
                } else {
                    printf("La ligne est fixe\n");
                    fprintf(fichierlog, "la ligne demandee est fixe, pas de deplacement\n");
                    fflush(fichierlog);
                }
            }
        }

        //On regarde si un pion est éjecté. Si il l'est, alors on le replace.
        for (i = 0; i < nbjoueurs; i++) {
            if (
                    (pions[i].lig == coord->ligne &&
                     (pions[i].col == (coord->colonne - 7) || pions[i].col == (coord->colonne + 7)))
                    ||
                    (pions[i].col == coord->colonne &&
                     (pions[i].lig == (coord->ligne - 7) || pions[i].lig == (coord->ligne + 7)))
                    ) {

                fprintf(fichierlog, "\nDEBUG detection ejection\n");
                fprintf(fichierlog, "le joueur %s est ejecte. ", pions[i].nom);
                fprintf(fichierlog, "il est en %d,%d. la case sortante est en %d,%d\n",
                        pions[i].nom,
                        pions[i].lig, pions[i].col,
                        coord->ligne, coord->colonne);
                fprintf(fichierlog, "pions[i].lig = pions[%d].lig = %d\n",i,pions[i].lig);
                fprintf(fichierlog, "pions[i].col = %d\n",pions[i].col);
                fprintf(fichierlog, "coord->ligne = %d\n",coord->ligne);
                fprintf(fichierlog, "coord->colonne = %d\n",coord->colonne);
                if(pions[i].lig == coord->ligne){
                    fprintf(fichierlog, "pions[i].lig == coord->ligne \n");
                }
                if((pions[i].col == (coord->colonne - 6) || pions[i].col == (coord->colonne + 6))){
                    fprintf(fichierlog, "(pions[i].col == (coord->colonne - 6) || pions[i].col == (coord->colonne + 6)) \n");
                }
                if((pions[i].lig == coord->ligne &&
                    (pions[i].col == (coord->colonne - 6) || pions[i].col == (coord->colonne + 6)))){
                    fprintf(fichierlog, "(pions[i].lig == coord->ligne && (pions[i].col == (coord->colonne - 6) || pions[i].col == (coord->colonne + 6)))");
                }
                fprintf(fichierlog, "FIN DEBUG detection ejection\n\n");
                fflush(fichierlog);
                renvoyer_pion_debut_ligne(labyrinthe, tuile_en_plus, &pions[i], fichierlog);
            }
        }
    }
}


void conversion_num_rangee_coordonnees(const int *num_rangee,
                                       t_coord *coord_pousser) {//converti le numéro de rangée en des coordonnées pour pouvoir l'exploiter
    switch (*num_rangee) {
        case 1:// flèche en haut à gauche (rangée de flèches du haut)
            coord_pousser->ligne = 0;
            coord_pousser->colonne = 1;
            break;
        case 2:
            coord_pousser->ligne = 0;
            coord_pousser->colonne = 3;
            break;
        case 3:
            coord_pousser->ligne = 0;
            coord_pousser->colonne = 5;
            break;
        case 4:
            coord_pousser->ligne = 1;
            coord_pousser->colonne = 6;
            break;
        case 5:
            coord_pousser->ligne = 3;
            coord_pousser->colonne = 6;
            break;
        case 6:
            coord_pousser->ligne = 5;
            coord_pousser->colonne = 6;
            break;
        case 7:
            coord_pousser->ligne = 6;
            coord_pousser->colonne = 5;
            break;
        case 8:
            coord_pousser->ligne = 6;
            coord_pousser->colonne = 3;
            break;
        case 9:
            coord_pousser->ligne = 6;
            coord_pousser->colonne = 1;
            break;
        case 10:
            coord_pousser->ligne = 5;
            coord_pousser->colonne = 0;
            break;
        case 11:
            coord_pousser->ligne = 3;
            coord_pousser->colonne = 0;
            break;
        case 12:
            coord_pousser->ligne = 1;
            coord_pousser->colonne = 0;
            break;
    }
}

int test_tresor(t_pion *Pion) {
    int cartesatrouver = 0;//compte le nombre de cartes restantes à trouver
    for (int i = 0; i < 12; ++i) {
        if (Pion->tresors[i].signe != '0' && Pion->tresors[i].decouvert == 0) {
            ++cartesatrouver;
        }
    }
    if (cartesatrouver != 0) return 0; // si le joueur n'a pas tous les tresors
    else {
        return 1;
    }
}


int deroulementTour(const int *nbjoueurs, t_case labyrinthe[7][7], t_case *tuile_en_plus, t_pion pions[4],
                    FILE *fichierlog) {
    char fin_tour;
    int i, j;
    int gagne; //Variable pour détecter une victoire.


    int joueur_en_cours = 0;//1 à 4 , c'est le num du joueur entrain de jouer mais on part à 0 pour faciliter les boucles.
    int num_rangee, rotation;
    t_coord coord_pousser;//coordonnées de la case à pousser
    int ligne_arrivee, colonne_arrivee, var_boucle = 0;


    for (joueur_en_cours = 0; joueur_en_cours < *nbjoueurs; ++joueur_en_cours) {

        system("cls");
        affichageComplet(labyrinthe, *tuile_en_plus, pions, *nbjoueurs);
        printf("%s c'est a vous !\n", pions[joueur_en_cours].nom);
        AffichageTresor(&pions[joueur_en_cours]);

        //Rotation de la tuile en plus
        do {
            printf("%s saisissez 0, 90, 180, ou 270 pour faire pivoter la tuile a inserer vers la droite: ",
                   pions[joueur_en_cours].nom);
            fflush(stdin);
            scanf("%d", &rotation);
            printf("\n");
            if (rotation == 20) return 5;//retour au menu à n'importe quel moment.
        } while (rotation != 0 && rotation != 90 && rotation != 180 && rotation != 270);
        tourner(tuile_en_plus, rotation);// tourner la tuile



        /*
         * ----DEPLACEMENT DE LA RANGEE----
         */
        affichageComplet(labyrinthe, *tuile_en_plus, pions, *nbjoueurs);
        AffichageTresor(&pions[joueur_en_cours]);
        do {
            printf("%s, saisissez le numero de la fleche sur laquelle vous voulez inserer la tuile en plus : ",
                   pions[joueur_en_cours].nom);
            fflush(stdin);
            scanf("%d", &num_rangee);
            printf("\n");

            if (num_rangee == 20) { //retour au menu à n'importe quel moment.
                return 5;
            }
        } while (num_rangee < 1 || num_rangee > 12); //Vérification que la rangée existe.

        conversion_num_rangee_coordonnees(&num_rangee, &coord_pousser);
        //On déplace les tuiles.
        deplacer_tuiles(labyrinthe, tuile_en_plus, &coord_pousser, pions, *nbjoueurs, fichierlog);

        affichageComplet(labyrinthe, *tuile_en_plus, pions, *nbjoueurs);
        AffichageTresor(&pions[joueur_en_cours]);

        /*
         * ----DEPLACEMENT DU PION----
         */

        do {

            do {
                /*
                 * CHOIX DE LA LIGNE.
                 */
                do {
                    printf("---- %s, vous etes sur la ligne %d et la colonne %d ----\n\n",
                           pions[joueur_en_cours].nom, pions[joueur_en_cours].lig, pions[joueur_en_cours].col);
                    fprintf(fichierlog, "%s est sur la position %d,%d\n", pions[joueur_en_cours].nom,
                            pions[joueur_en_cours].lig, pions[joueur_en_cours].col);
                    fprintf(fichierlog, "%s est sur position_pion->sortie_du_plateau %d,%d\n", pions[joueur_en_cours].nom,
                            pions[joueur_en_cours].position_pion->sortie_du_plateau.ligne, pions[joueur_en_cours].position_pion->sortie_du_plateau.colonne);
                    fflush(fichierlog);
                    printf("%s, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 a 6) : ",
                           pions[joueur_en_cours].nom);
                    fflush(stdin);
                    scanf("%d", &ligne_arrivee);
                    printf("\n");

                    if (ligne_arrivee == 20) {
                        return 5;
                    }
                } while (ligne_arrivee < 0 || ligne_arrivee > 6);
                /*
                 * CHOIX DE LA COLONNE
                 */
                do {
                    printf("%s, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 a 6) : ",
                           pions[joueur_en_cours].nom);
                    fflush(stdin);
                    scanf("%d", &colonne_arrivee);
                    printf("\n");

                    if (colonne_arrivee == 20) {
                        return 5;
                    }
                } while (colonne_arrivee < 0 || colonne_arrivee > 6);

                //Vérification de la légalité du déplacement.
                if (deplacement_valide(labyrinthe, &pions[joueur_en_cours], colonne_arrivee, ligne_arrivee) == 0) {
                    printf("deplacement impossible, veuillez ressayer\n");
                    var_boucle = 0;
                } else var_boucle = 1;
            } while (var_boucle == 0);



            /*
             * ----DEPLACEMENT DU PION----
             */
            deplacer_pion(labyrinthe, &pions[joueur_en_cours], colonne_arrivee, ligne_arrivee, fichierlog);
            fprintf(fichierlog, "Apres deplacement %s est sur position_pion->sortie_du_plateau %d,%d\n", pions[joueur_en_cours].nom,
                    pions[joueur_en_cours].position_pion->sortie_du_plateau.ligne, pions[joueur_en_cours].position_pion->sortie_du_plateau.colonne);
            fflush(fichierlog);
            affichageComplet(labyrinthe, *tuile_en_plus, pions, *nbjoueurs);
            //Récupération d'un tresor
            recuperer_tresor(&pions[joueur_en_cours],
                             &labyrinthe[pions[joueur_en_cours].lig][pions[joueur_en_cours].col]);
            AffichageTresor(&pions[joueur_en_cours]);

            do {
                fflush(stdin);
                printf("Avez fini votre tour ? 'o' pour oui et 'n' pour non: ");
                fflush(stdin);
                scanf("%c", &fin_tour);

                if (fin_tour == 20) {
                    return 5;
                }
            } while (fin_tour != 'o' && fin_tour != 'n');
            printf("\n");
        } while (fin_tour != 'o');



        /*
         * ----DETECTION D'UNE VICTOIRE----
         */

        gagne = 0;
        if (
                pions[joueur_en_cours].coord_depart_arrivee.ligne == pions[joueur_en_cours].lig
                &&
                pions[joueur_en_cours].coord_depart_arrivee.colonne == pions[joueur_en_cours].col
                &&
                test_tresor(&pions[joueur_en_cours]) == 1
                ) {
            gagne = joueur_en_cours + 1;
            return gagne;
        }
    }
    return 0;
}

void attribution_caracteristiques_joueurs(const int *nbjoueurs, t_pion pions[4],
                                          t_case labyrinthe[7][7]) { //initialise le nom et la position ini des pions
    int numJoueur, saisie, i;
    for (i = 0; i < *nbjoueurs; ++i) {
        numJoueur = i + 1; //attribution du nom
        printf("Joueur %d, saisissez votre nom : ", numJoueur);
        fflush(stdin);
        scanf("%s", pions[i].nom);
        printf("\n");

    }

    for (i = 0; i < 4; i++) {
        pions[i].num_pion = i;
    }
    //initialisation des positions initiales des joueurs
    pions[0].coord_depart_arrivee.ligne = 0;
    pions[0].lig = 0;
    pions[0].coord_depart_arrivee.colonne = 0;
    pions[0].col = 0;
    pions[0].position_pion = &labyrinthe[0][0];

    pions[1].coord_depart_arrivee.ligne = 0;
    pions[1].lig = 0;
    pions[1].coord_depart_arrivee.colonne = 6;
    pions[1].col = 6;
    pions[1].position_pion = &labyrinthe[0][6];

    pions[2].coord_depart_arrivee.ligne = 6;
    pions[2].lig = 6;
    pions[2].coord_depart_arrivee.colonne = 6;
    pions[2].col = 6;
    pions[2].position_pion = &labyrinthe[6][6];

    pions[3].coord_depart_arrivee.ligne = 6;
    pions[3].lig = 6;
    pions[3].coord_depart_arrivee.colonne = 0;
    pions[3].col = 0;
    pions[3].position_pion = &labyrinthe[6][0];


    //Attribution des trésors à trouver par joueurs:
}

void Menu(FILE *fichierlog) {
    int choix, choix2, gagne = 0, tour = 0, i, j;
    fprintf(fichierlog, "Menu() - initialisation\n");
    fflush(fichierlog);
    ///// copie de l'initialisation de test
    int nbjoueurs;
    t_case labyrinthe[7][7], tuile_en_plus;
    t_pion pions[4];
    /////
    system("cls");      //efface la console
    do {
        do {
            printf("Menu : \n"
                   "1) Nouvelle partie\n"
                   "2) Afficher les regles\n"
                   "3) Afficher les credits\n"
                   "4) Quitter\n"
                   "Saisissez un chiffre pour naviguer dans le menu : ");
            fflush(stdin);
            scanf("%d", &choix);
            printf("\n");
        } while (choix < 1 || choix > 4);

        //On génère le plateau du Labyrinthe.
        generation_plateau_debut(labyrinthe, &tuile_en_plus, fichierlog);

        switch (choix) {
            case 1: //Nouvelle partie.
                //On choisit le nombre de joueurs.
                do {
                    printf("Saisissez le nombre de joueurs (entre 2 et 4) : ");
                    fflush(stdin);
                    scanf("%d", &nbjoueurs);
                    printf("\n");
                } while (nbjoueurs < 2 || nbjoueurs > 4);

                attribution_caracteristiques_joueurs(&nbjoueurs, pions, labyrinthe);

                //initialisation de la partie distribution des cartes
                for (i = 0; i < nbjoueurs; i++) {
                    pions[i].indice_tresor_recherche = 0;
                    for (j = 0; j < 12; j++) {
                        pions[i].tresors[j].signe = '0';
                        pions[i].tresors[j].decouvert = 0;
                    }
                }
                DistributionCartes(&nbjoueurs, pions);

                do {
                    printf("Saisissez 20 pour revenir au menu a tout moment.\n");//à chaque saisie de déroulement, le joueurs dois pouvoir revenir au menu
                    gagne = deroulementTour(&nbjoueurs, labyrinthe, &tuile_en_plus, pions, fichierlog);
                    // fonction affichage d'Aurel
                    ++tour;
                } while (gagne == 0);
                // ici l'un des joueurs a gagné
                if (gagne != 5) {
                    printf("!!!!  Bravo %s, vous avez gagne !!!!\n\n", pions[gagne - 1].nom);
                }
                break;
            case 2:
                do {
                    printf("But du jeu :\n"
                           "\n"
                           "Vous penetrez dans un labyrinthe enchante a la recherche de fabuleux tresors.\n"
                           "Chacun d’entre vous essaye de creeer des chemins pour atteindre le trésor qu’il convoite en faisant coulisser astucieusement les couloirs.\n"
                           "Le joueur qui aura trouve tous ses tresors et rejoint sa case depart le premier sera declare vainqueur.\n"
                           "\n"
                           "Deroulement de la partie :\n"
                           "\n"
                           "Chaque joueur commence par regarder le prochain tresor a chercher\n"
                           "Le dernier joueur a avoir participe a une chasse aux tresors entame la partie.\n"
                           "Le tour d’un joueur se decompose en deux etapes :\n"
                           "1. Modifier les couloirs en saisissant un chiffre de 1 a 12 qui correspond aux rangees montrees par les fleches. \n"
                           "La première fleche est tout a gauche de la premiere ligne, les suivantes sont dans le sens horaire.\n"
                           "2. Deplacer son pion en saisissant les coordonnees de la case de destination.\n"
                           "Quand vient son tour, le joueur doit essayer d’atteindre la case sur laquelle figure le tresor a chercher.\n"
                           "Pour cela, il modifie toujours d’abord le labyrinthe en inserant la plaque Couloir, puis deplace son pion.\n"
                           "\n"
                           "Source : Ravensburger.fr\n"
                           "\n"
                           "Pour revenir au menu, saisissez 1 : ");
                    fflush(stdin);
                    scanf("%d", &choix2);
                    printf("\n");
                } while (choix2 != 1);

                break;
            case 3:
                do {
                    printf("Credits :\n"
                           "Projet ECE Labyrinthe Ing 1 2022-2023\n"
                           "Realise par Hirou Briac, Francisco Baptiste, Craplet Aurelien et Vennin Maxime\n"
                           "\n"
                           "Pour revenir au menu, saisissez 1 : ");
                    fflush(stdin);
                    scanf("%d", &choix2);
                    printf("\n");
                } while (choix2 != 1);

                break;
            case 4:
                printf("Au revoir !");
                break;
        }
    } while (choix != 4);

}