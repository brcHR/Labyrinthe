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

int test_tresor(t_pion *Pion){
    int cartesatrouver=0;//compte le nombre de cartes restantes à trouver
    for (int i = 0; i < 12; ++i) {
        if (Pion->tresors[i].signe !='0'&& Pion->tresors[i].decouvert==0){
            ++cartesatrouver;
        }
    }
    if (cartesatrouver==0) return 0; // si le joueur n'a pas tous les tresors
    else {
        printf("Vous avez tous les trésors, retournez à votre case départ pour gagner\n");
        return 1;
    }
}


int deroulementTour(const int *nbjoueurs,t_case labyrinthe[7][7], t_case *tuile_en_plus, t_pion pions[4]) {

    generation_plateau_debut(labyrinthe, tuile_en_plus);

    int joueur_en_cours = 0;//1 à 4 , c'est le num du joueur entrain de jouer mais on part à 0 pour faciliter les boucles.
    int num_rangee;
    t_coord coord_pousser;//coordonnées de la case à pousser
    int ligne_arrivee, colonne_arrivee, var_boucle = 0;


    for (joueur_en_cours = 0; joueur_en_cours < *nbjoueurs; ++joueur_en_cours) {

    /*
     * ----DEPLACEMENT DE LA RANGEE----
     */

    do {
        printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser : ", joueur_en_cours);
        scanf("%d", &num_rangee);
        printf("\n");

        if (num_rangee == 20) { //retour au menu à n'importe quel moment.
            return 2;
        }
    } while (num_rangee < 1 || num_rangee > 12); //Vérification que la rangée existe.

    conversion_num_rangee_coordonnees(&num_rangee, &coord_pousser);
    //On déplace les tuiles.
    deplacer_tuiles(labyrinthe, tuile_en_plus, &coord_pousser);

    /*
     * ----DEPLACEMENT DU PION----
     */

    do {
        /*
         * CHOIX DE LA LIGNE.
         */
        do {
            printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                   joueur_en_cours);
            scanf("%d", &ligne_arrivee);
            printf("\n");

            if (ligne_arrivee == 20) {
                return 2;
            }
        } while (ligne_arrivee < 0 || ligne_arrivee > 6);
        /*
         * CHOIX DE LA COLONNE
         */
        do {
            printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                   joueur_en_cours);
            scanf("%d", &colonne_arrivee);
            printf("\n");

            if (colonne_arrivee == 20) {
                return 2;
            }
        } while (colonne_arrivee < 0 || colonne_arrivee > 6);

        //Vérification de la légalité du déplacement.
        if (deplacement_valide(labyrinthe, &pions[joueur_en_cours], colonne_arrivee, ligne_arrivee) == 0) {
            printf("deplacement impossible, veuillez ressayer\n");
            var_boucle = 0;
        } else var_boucle=1;
    } while (var_boucle == 0);

    /*
     * ----DEPLACEMENT DU PION----
     */
    deplacer_pion(labyrinthe, &pions[joueur_en_cours], colonne_arrivee, ligne_arrivee);
    }

    /*
     * ----DETECTION D'UNE VICTOIRE----
     */

    int gagne=0;
    for (int i = 0; i < 4; ++i) {
        if (pions[i].coord_depart_arrivee.ligne == pions[i].position_pion->ligne || pions[i].coord_depart_arrivee.colonne== pions[i].position_pion->colonne && test_tresor(&pions[i])==1) ++gagne;
    }
    if(gagne==0){
        return 0;
    } else return 1;
}

void attribution_caracteristiques_joueurs(int *nbjoueurs,t_pion pions[4]){
    int numJoueur,saisie;
    for (int i = 0; i <*nbjoueurs ; ++i) {
        numJoueur=i+1; //attribution du nom
        printf("Joueur %d, saisissez votre nom : ",numJoueur);
        fflush(stdin);
        scanf("%s",pions[i].nom);
        printf("\n");

        do {//attribution de la couleur
            printf("couleurs disponibles :\n"
                   "1 demander Aurel\n"
                   "Saisissez la couleur de votre pion : ");
            scanf("%d",saisie);
            printf("\n");
        } while (saisie<0 ||saisie>5); //TODO : demander à Aurel couleurs et max de couleurs

    }
    //initialisation des positions initiales des joueurs
    pions[1].coord_depart_arrivee.ligne=0;
    pions[1].coord_depart_arrivee.colonne=0;
    pions[2].coord_depart_arrivee.ligne=0;
    pions[2].coord_depart_arrivee.colonne=7;
    pions[3].coord_depart_arrivee.ligne=7;
    pions[3].coord_depart_arrivee.colonne=7;
    pions[4].coord_depart_arrivee.ligne=7;
    pions[4].coord_depart_arrivee.colonne=0;
}

void Menu() {
    int choix, choix2, gagne = 0, tour = 0,i,j;

    ///// copie de l'initialisation de test
    int nbjoueurs;
    t_case labyrinthe[7][7], tuile_en_plus;
    t_pion pions[4];
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
            case 1: //Nouvelle partie.
                //On choisit le nombre de joueurs.
                do {
                    printf("Saisissez le nombre de joueurs (entre 2 et 4) : ");
                    fflush(stdin);
                    scanf("%d", &nbjoueurs);
                    printf("\n");
                } while (nbjoueurs < 2 || nbjoueurs > 4);

                attribution_caracteristiques_joueurs(&nbjoueurs,pions); 

                //initialisation de la partie distribution des cartes
                for(i=0;i<nbjoueurs;i++){
                    for(j=0;j<12;j++){
                        pions[i].tresors[j].signe = '0';
                        pions[i].tresors[j].decouvert = 0;
                    }
                }

                do {
                    printf("Saisissez 20 pour revenir au menu à tout moment.\n");//à chaque saisie de déroulement, le joueurs dois pouvoir revenir au menu
                    gagne = deroulementTour(&nbjoueurs, labyrinthe, &tuile_en_plus,pions);
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
                           "1. Modifier les couloirs en saisissant un chiffre de 1 à 12 qui correspond aux rangées montrées par les flèches. \n"
                           "La première flèche est tout à gauche de la première ligne, les suivantes sont dans le sens horaire.\n"
                           "2. Déplacer son pion en saisissant les coordonnées de la case de destination.\n"
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