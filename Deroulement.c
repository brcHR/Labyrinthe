//
// Created by Maxime Vennin on 30/12/2022.
//

#include <stdio.h>
#include "Deroulement.h"

void conversion_num_rangee_coordonnees(const int *num_rangee,
                                       t_coord *coord_pousser) {//converti le numéro de rangée en des coordonnées
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


int deroulementTour(const int *nbjoueurs, t_pion *pion1, t_pion *pion2, t_pion *pion3, t_pion *pion4,
                    t_case labyrinthe[7][7], t_case *tuile_en_plus) {
    generation_plateau_debut(labyrinthe, tuile_en_plus);

    int joueur_en_cours = 1;//1 à 4 , c'est le num du joueur entrain de jouer
    int num_rangee;
    t_coord coord_pousser;//coordonnées de la case à pousser

    int ligne_arrivee, colonne_arrivee;

    switch (*nbjoueurs) {
        case 2:
            do {//saisie de la rangée à déplacer par le joueur 1
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser : ",
                       joueur_en_cours);//voir page 13 du sujet
                scanf("%d", &num_rangee);
                printf("\n");
                if (num_rangee == 20)return 2;
            } while (num_rangee < 1 || num_rangee > 12);
            conversion_num_rangee_coordonnees(&num_rangee, &coord_pousser);
            deplacer_tuiles(labyrinthe, tuile_en_plus, &coord_pousser);

            do {//déplacement du pion 1
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &ligne_arrivee);
                    printf("\n");
                } while (ligne_arrivee < 0 || ligne_arrivee > 6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &colonne_arrivee);
                    printf("\n");
                } while (colonne_arrivee < 0 || colonne_arrivee > 6);
                if (deplacement_valide(labyrinthe, pion1, colonne_arrivee, ligne_arrivee) == 0) {
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe, pion1, colonne_arrivee, ligne_arrivee) == 0);
            deplacer_pion(labyrinthe, pion1, colonne_arrivee, ligne_arrivee);

            //////joueur 2
            ++joueur_en_cours;

            do {
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser : ",
                       joueur_en_cours);//voir page 13 du sujet
                scanf("%d", &num_rangee);
                printf("\n");
                if (num_rangee == 20)return 2;
            } while (num_rangee < 1 || num_rangee > 12);
            conversion_num_rangee_coordonnees(&num_rangee, &coord_pousser);
            deplacer_tuiles(labyrinthe, tuile_en_plus, &coord_pousser);

            do {
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &ligne_arrivee);
                    printf("\n");
                } while (ligne_arrivee < 0 || ligne_arrivee > 6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &colonne_arrivee);
                    printf("\n");
                } while (colonne_arrivee < 0 || colonne_arrivee > 6);
                if (deplacement_valide(labyrinthe, pion2, colonne_arrivee, ligne_arrivee) == 0) {
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe, pion2, colonne_arrivee, ligne_arrivee) == 0);
            deplacer_pion(labyrinthe, pion2, colonne_arrivee, ligne_arrivee);
        case 3:
            do {//saisie de la rangée à déplacer par le joueur 1
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser : ",
                       joueur_en_cours);//voir page 13 du sujet
                scanf("%d", &num_rangee);
                printf("\n");
                if (num_rangee == 20)return 2;
            } while (num_rangee < 1 || num_rangee > 12);
            conversion_num_rangee_coordonnees(&num_rangee, &coord_pousser);
            deplacer_tuiles(labyrinthe, tuile_en_plus, &coord_pousser);

            do {//déplacement du pion 1
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &ligne_arrivee);
                    printf("\n");
                } while (ligne_arrivee < 0 || ligne_arrivee > 6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &colonne_arrivee);
                    printf("\n");
                } while (colonne_arrivee < 0 || colonne_arrivee > 6);
                if (deplacement_valide(labyrinthe, pion1, colonne_arrivee, ligne_arrivee) == 0) {
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe, pion1, colonne_arrivee, ligne_arrivee) == 0);
            deplacer_pion(labyrinthe, pion1, colonne_arrivee, ligne_arrivee);

            //////joueur 2
            ++joueur_en_cours;

            do {
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser : ",
                       joueur_en_cours);//voir page 13 du sujet
                scanf("%d", &num_rangee);
                printf("\n");
                if (num_rangee == 20)return 2;
            } while (num_rangee < 1 || num_rangee > 12);
            conversion_num_rangee_coordonnees(&num_rangee, &coord_pousser);
            deplacer_tuiles(labyrinthe, tuile_en_plus, &coord_pousser);

            do {
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &ligne_arrivee);
                    printf("\n");
                } while (ligne_arrivee < 0 || ligne_arrivee > 6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &colonne_arrivee);
                    printf("\n");
                } while (colonne_arrivee < 0 || colonne_arrivee > 6);
                if (deplacement_valide(labyrinthe, pion2, colonne_arrivee, ligne_arrivee) == 0) {
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe, pion2, colonne_arrivee, ligne_arrivee) == 0);
            deplacer_pion(labyrinthe, pion2, colonne_arrivee, ligne_arrivee);


            //////joueur 3
            ++joueur_en_cours;

            do {
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser : ",
                       joueur_en_cours);//voir page 13 du sujet
                scanf("%d", &num_rangee);
                printf("\n");
                if (&num_rangee == 20)return 2;
            } while (num_rangee < 1 || num_rangee > 12);
            conversion_num_rangee_coordonnees(&num_rangee, &coord_pousser);
            deplacer_tuiles(labyrinthe, tuile_en_plus, &coord_pousser);

            do {
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &ligne_arrivee);
                    printf("\n");
                } while (ligne_arrivee < 0 || ligne_arrivee > 6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &colonne_arrivee);
                    printf("\n");
                } while (colonne_arrivee < 0 || colonne_arrivee > 6);
                if (deplacement_valide(labyrinthe, pion3, colonne_arrivee, ligne_arrivee) == 0) {
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe, pion3, colonne_arrivee, ligne_arrivee) == 0);
            deplacer_pion(labyrinthe, pion3, colonne_arrivee, ligne_arrivee);
            break;
        case 4:
            do {//saisie de la rangée à déplacer par le joueur 1
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser : ",
                       joueur_en_cours);//voir page 13 du sujet
                scanf("%d", &num_rangee);
                printf("\n");
                if (&num_rangee == 20)return 2;
            } while (num_rangee < 1 || num_rangee > 12);
            conversion_num_rangee_coordonnees(&num_rangee, &coord_pousser);
            deplacer_tuiles(labyrinthe, tuile_en_plus, &coord_pousser);

            do {//déplacement du pion 1
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &ligne_arrivee);
                    printf("\n");
                } while (ligne_arrivee < 0 || ligne_arrivee > 6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &colonne_arrivee);
                    printf("\n");
                } while (colonne_arrivee < 0 || colonne_arrivee > 6);
                if (deplacement_valide(labyrinthe, pion1, colonne_arrivee, ligne_arrivee) == 0) {
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe, pion1, colonne_arrivee, ligne_arrivee) == 0);
            deplacer_pion(labyrinthe, pion1, colonne_arrivee, ligne_arrivee);

            //////joueur 2
            ++joueur_en_cours;

            do {
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser : ",
                       joueur_en_cours);//voir page 13 du sujet
                scanf("%d", &num_rangee);
                printf("\n");
            } while (num_rangee < 1 || num_rangee > 12);
            conversion_num_rangee_coordonnees(&num_rangee, &coord_pousser);
            deplacer_tuiles(labyrinthe, tuile_en_plus, &coord_pousser);

            do {
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &ligne_arrivee);
                    printf("\n");
                } while (ligne_arrivee < 0 || ligne_arrivee > 6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &colonne_arrivee);
                    printf("\n");
                } while (colonne_arrivee < 0 || colonne_arrivee > 6);
                if (deplacement_valide(labyrinthe, pion2, colonne_arrivee, ligne_arrivee) == 0) {
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe, pion2, colonne_arrivee, ligne_arrivee) == 0);
            deplacer_pion(labyrinthe, pion2, colonne_arrivee, ligne_arrivee);


            //////joueur 3
            ++joueur_en_cours;

            do {
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser : ",
                       joueur_en_cours);//voir page 13 du sujet
                scanf("%d", &num_rangee);
                printf("\n");
            } while (num_rangee < 1 || num_rangee > 12);
            conversion_num_rangee_coordonnees(&num_rangee, &coord_pousser);
            deplacer_tuiles(labyrinthe, tuile_en_plus, &coord_pousser);

            do {
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &ligne_arrivee);
                    printf("\n");
                } while (ligne_arrivee < 0 || ligne_arrivee > 6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &colonne_arrivee);
                    printf("\n");
                } while (colonne_arrivee < 0 || colonne_arrivee > 6);
                if (deplacement_valide(labyrinthe, pion3, colonne_arrivee, ligne_arrivee) == 0) {
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe, pion3, colonne_arrivee, ligne_arrivee) == 0);
            deplacer_pion(labyrinthe, pion3, colonne_arrivee, ligne_arrivee);


            //////joueur 4
            ++joueur_en_cours;

            do {
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser : ",
                       joueur_en_cours);//voir page 13 du sujet
                scanf("%d", &num_rangee);
                printf("\n");
            } while (num_rangee < 1 || num_rangee > 12);
            conversion_num_rangee_coordonnees(&num_rangee, &coord_pousser);
            deplacer_tuiles(labyrinthe, tuile_en_plus, &coord_pousser);

            do {
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &ligne_arrivee);
                    printf("\n");
                } while (ligne_arrivee < 0 || ligne_arrivee > 6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                           joueur_en_cours);
                    scanf("%d", &colonne_arrivee);
                    printf("\n");
                } while (colonne_arrivee < 0 || colonne_arrivee > 6);
                if (deplacement_valide(labyrinthe, pion4, colonne_arrivee, ligne_arrivee) == 0) {
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe, pion4, colonne_arrivee, ligne_arrivee) == 0);
            deplacer_pion(labyrinthe, pion4, colonne_arrivee, ligne_arrivee);
            break;
    }

    // si un joueur a gagné return 1 sinon 0. Je suis pas sûr que c'est ça pour arrivée finale
    if (pion1->arrivee == 1 || pion2->arrivee == 1 || pion3->arrivee == 1 || pion4->arrivee == 1) {
        return 1;
    } else return 0;
}


void Menu() {
    int choix, choix2, gagne = 0, tour = 0;

    ///// copie de l'initialisation de test
    int nbjoueurs;
    t_case labyrinthe[7][7], tuile_en_plus;
    t_pion pion1, pion2, pion3, pion4;
    /////

    do {
        do {
            printf("Menu : \n"
                   "1) Nouvelle partie\n"
                   "2) Afficher les règles\n"
                   "3) Afficher les crédits\n"
                   "4) Quitter\n"
                   "Saisissez un chiffre pour naviguer dans le menu : ");
            scanf("%d", &choix);
            printf("\n");
        } while (choix < 1 || choix > 4);
        switch (choix) {
            case 1:
                //initialisation de la partie distribution des cartes
                for (int i = 0; i < 12; ++i) {
                    pion1.tresors[i].signe = '0', pion2.tresors[i].signe = '0', pion3.tresors[i].signe = '0', pion4.tresors[i].signe = '0';
                }
                for (int i = 0; i < 12; ++i) {
                    pion1.tresors[i].decouvert = 0, pion2.tresors[i].decouvert = 0, pion3.tresors[i].decouvert = 0, pion4.tresors[i].decouvert = 0;
                }

                do {
                    printf("Saisissez le nombre de joueurs (entre 2 et 4) : ");
                    fflush(stdin);
                    scanf("%d", &nbjoueurs);
                    printf("\n");
                } while (nbjoueurs < 2 || nbjoueurs > 4);


                do {
                    printf("Saisissez 20 pour revenir au menu à tout moment.\n");//à chaque saisie de déroulement, le joueurs dois pouvoir revenir au menu
                    gagne = deroulementTour(&nbjoueurs, &pion1, &pion2, &pion3, &pion4, labyrinthe, &tuile_en_plus);
                    // fonction affichage d'Aurel
                    ++tour;
                } while (gagne == 0);
                break;
            case 2:
                do {
                    printf("But du jeu :\n"
                           "Vous pénétrez dans un labyrinthe enchanté à la recherche de fabuleux trésors.\n"
                           "Chacun d’entre vous essaye de créer des chemins pour atteindre le trésor qu’il convoite en faisant coulisser astucieusement les couloirs.\n"
                           "Le joueur qui aura trouvé tous ses trésors et rejoint sa case départ le premier sera déclaré vainqueur.\n"
                           "\n"
                           "Déroulement de la partie :\n"
                           "Chaque joueur commence par regarder le prochain trésor à chercher\n"
                           "Le dernier joueur à avoir participé à une chasse aux trésors entame la partie.\n"
                           "Le tour d’un joueur se décompose en deux étapes :\n"
                           "1. Modifier les couloirs \n"
                           "2. Déplacer son pion \n"
                           "Quand vient son tour, le joueur doit essayer d’atteindre la case sur laquelle figure le trésor à chercher.\n"
                           "Pour cela, il modifie toujours d’abord le labyrinthe en insérant la plaque Couloir, puis déplace son pion.\n"
                           "\n"
                           "Source : Ravensburger.fr\n"
                           "\n"
                           "Pour revenir au menu, saisissez 1 : ");
                    scanf("%d", &choix2);
                    printf("\n");
                } while (choix2 != 1);

                break;
            case 3:
                do {
                    printf("Credits :\n"
                           "Projet ECE Labyrinthe Ing 1 2022-2023\n"
                           "Réalisé par Hirou Briac, Francisco Baptiste, Craplet Aurélien et Vennin Maxime\n"
                           "\n"
                           "Pour revenir au menu, saisissez 1 : ");
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