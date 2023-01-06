//
// Created by Maxime Vennin on 30/12/2022.
//

#include <stdio.h>
#include <windows.h>
#include "Deroulement.h"
#include "affichage.h"
#include "cartestresors.h"

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

int test_tresor(t_pion *Pion){
    int cartesatrouver=0;//compte le nombre de cartes restantes à trouver
    for (int i = 0; i < 12; ++i) {
        if (Pion->tresors[i].signe !='0'&& Pion->tresors[i].decouvert==0){
            ++cartesatrouver;
        }
    }
    if (cartesatrouver==0) return 0; // si le joueur n'a pas tous les tresors
    else {
        printf("Vous avez tous les tresors, retournez a votre case depart pour gagner\n");
        return 1;
    }
}


int deroulementTour(const int *nbjoueurs,t_case labyrinthe[7][7], t_case *tuile_en_plus, t_pion pions[4]) {
    char fin_tour;
    int i,j;
    generation_plateau_debut(labyrinthe, tuile_en_plus);

    int joueur_en_cours = 0;//1 à 4 , c'est le num du joueur entrain de jouer mais on part à 0 pour faciliter les boucles.
    int num_rangee, rotation;
    t_coord coord_pousser;//coordonnées de la case à pousser
    int ligne_arrivee, colonne_arrivee, var_boucle = 0;


    for (joueur_en_cours = 0; joueur_en_cours < *nbjoueurs; ++joueur_en_cours) {

        system("cls");
        affichageComplet(labyrinthe,*tuile_en_plus,pions,*nbjoueurs);
        printf("%s c'est a vous !",pions[joueur_en_cours].nom);
        AffichageTresor(&pions[joueur_en_cours]);

        //Rotation de la tuile en plus
        do {
            printf("%s saisissez 0, 90, 180, ou 270 pour faire pivoter la tuile a inserer vers la droite: ",pions[joueur_en_cours].nom);
            scanf("%d",&rotation);
            printf("\n");
            if (rotation == 20) return 2;//retour au menu à n'importe quel moment.
        }while(rotation!=0 && rotation != 90 && rotation != 180 && rotation != 270);
        tourner(tuile_en_plus,rotation);// tourner la tuile



    /*
     * ----DEPLACEMENT DE LA RANGEE----
     */
    affichageComplet(labyrinthe,*tuile_en_plus,pions,*nbjoueurs);
    AffichageTresor(&pions[joueur_en_cours]);
    do {
        printf("%s, saisissez le numero de la fleche sur laquelle vous voulez inserer la tuile en plus : ", pions[joueur_en_cours].nom);
        scanf("%d", &num_rangee);
        printf("\n");

        if (num_rangee == 20) { //retour au menu à n'importe quel moment.
            return 2;
        }
    } while (num_rangee < 1 || num_rangee > 12); //Vérification que la rangée existe.

    conversion_num_rangee_coordonnees(&num_rangee, &coord_pousser);
    //On déplace les tuiles.
    //On regarde si un pion est éjecté. Si il l'est, alors on le replace.
    for(i=0;i<*nbjoueurs;i++){
        if(
                (pions[i].lig == coord_pousser.ligne && (pions[i].col == coord_pousser.colonne-6 || pions[i].col == coord_pousser.colonne+6))
                ||
                (pions[i].col == coord_pousser.colonne && (pions[i].lig == coord_pousser.ligne-6 || pions[i].lig == coord_pousser.ligne+6))
        ){
            renvoyer_pion_debut_ligne(labyrinthe,&pions[i]);
        }
    }


    deplacer_tuiles(labyrinthe, tuile_en_plus, &coord_pousser);

    affichageComplet(labyrinthe,*tuile_en_plus,pions,*nbjoueurs);
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
                printf("%s, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                       pions[joueur_en_cours].nom);
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
                printf("%s, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6) : ",
                       pions[joueur_en_cours].nom);
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
            } else var_boucle = 1;
        } while (var_boucle == 0);



        /*
         * ----DEPLACEMENT DU PION----
         */
        deplacer_pion(labyrinthe, &pions[joueur_en_cours], colonne_arrivee, ligne_arrivee);
        affichageComplet(labyrinthe, *tuile_en_plus, pions, *nbjoueurs);
        AffichageTresor(&pions[joueur_en_cours]);

        do{
            printf("Avez fini votrez tour ? 'o' pour oui et 'n' pour non: ");scanf("%c",&fin_tour);
        }while(fin_tour!='o' && fin_tour!='n');

    }while(fin_tour!='o');
    }

    //Récupération d'un tresor
    recuperer_tresor(&pions[joueur_en_cours],&labyrinthe[pions[joueur_en_cours].position_pion->ligne][pions[joueur_en_cours].position_pion->colonne]);


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

void attribution_caracteristiques_joueurs(const int *nbjoueurs,t_pion pions[4], t_case labyrinthe[7][7]){ //initialise le nom et la position ini des pions
    int numJoueur,saisie,i;
    for (i = 0; i <*nbjoueurs ; ++i) {
        numJoueur=i+1; //attribution du nom
        printf("Joueur %d, saisissez votre nom : ",numJoueur);
        fflush(stdin);
        scanf("%s",pions[i].nom);
        printf("\n");

    }

    for(i=0;i<4;i++){
        pions[i].num_pion = i;
    }
    //initialisation des positions initiales des joueurs
    pions[0].coord_depart_arrivee.ligne=0;
    pions[0].lig=0;
    pions[0].coord_depart_arrivee.colonne=0;
    pions[0].col=0;
    pions[0].position_pion = &labyrinthe[0][0];

    pions[1].coord_depart_arrivee.ligne=0;
    pions[1].lig=0;
    pions[1].coord_depart_arrivee.colonne=6;
    pions[1].col=6;
    pions[1].position_pion = &labyrinthe[0][6];

    pions[2].coord_depart_arrivee.ligne=6;
    pions[2].lig=6;
    pions[2].coord_depart_arrivee.colonne=6;
    pions[2].col=6;
    pions[2].position_pion = &labyrinthe[6][6];

    pions[3].coord_depart_arrivee.ligne=6;
    pions[3].lig=6;
    pions[3].coord_depart_arrivee.colonne=0;
    pions[3].col=0;
    pions[3].position_pion = &labyrinthe[6][0];


    //Attribution des trésors à trouver par joueurs:
}

void Menu() {
    int choix, choix2, gagne = 0, tour = 0,i,j;

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

                attribution_caracteristiques_joueurs(&nbjoueurs,pions,labyrinthe);

                //initialisation de la partie distribution des cartes
                for(i=0;i<nbjoueurs;i++){
                    for(j=0;j<12;j++){
                        pions[i].tresors[j].signe = '0';
                        pions[i].tresors[j].decouvert = 0;
                    }
                }
                DistributionCartes(&nbjoueurs,pions);

                do {
                    printf("Saisissez 20 pour revenir au menu a tout moment.\n");//à chaque saisie de déroulement, le joueurs dois pouvoir revenir au menu
                    gagne = deroulementTour(&nbjoueurs, labyrinthe, &tuile_en_plus,pions);
                    // fonction affichage d'Aurel
                    ++tour;
                } while (gagne == 0);
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
                           "1. Modifier les couloirs en saisissant un chiffre de 1 à 12 qui correspond aux rangees montrees par les fleches. \n"
                           "La première fleche est tout a gauche de la premiere ligne, les suivantes sont dans le sens horaire.\n"
                           "2. Deplacer son pion en saisissant les coordonnees de la case de destination.\n"
                           "Quand vient son tour, le joueur doit essayer d’atteindre la case sur laquelle figure le tresor a chercher.\n"
                           "Pour cela, il modifie toujours d’abord le labyrinthe en inserant la plaque Couloir, puis deplace son pion.\n"
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
                           "Réalise par Hirou Briac, Francisco Baptiste, Craplet Aurelien et Vennin Maxime\n"
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