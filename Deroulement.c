//
// Created by Maxime Vennin on 30/12/2022.
//

#include <stdio.h>
#include "Deroulement.h"

void conversion_num_rangee_coordonnees (int *num_rangee, t_coord *coord_pousser){//converti le numéro de rangée en des coordonnées
    switch (*num_rangee) {
        case 1:// flèche en haut à gauche (rangée de flèches du haut)
            coord_pousser->ligne=0;
            coord_pousser->colonne=1;
            break;
        case 2:
            coord_pousser->ligne=0;
            coord_pousser->colonne=3;
            break;
        case 3:
            coord_pousser->ligne=0;
            coord_pousser->colonne=5;
            break;
        case 4:
            coord_pousser->ligne=1;
            coord_pousser->colonne=6;
            break;
        case 5:
            coord_pousser->ligne=3;
            coord_pousser->colonne=6;
            break;
        case 6:
            coord_pousser->ligne=5;
            coord_pousser->colonne=6;
            break;
        case 7:
            coord_pousser->ligne=6;
            coord_pousser->colonne=5;
            break;
        case 8:
            coord_pousser->ligne=6;
            coord_pousser->colonne=3;
            break;
        case 9:
            coord_pousser->ligne=6;
            coord_pousser->colonne=1;
            break;
        case 10:
            coord_pousser->ligne=5;
            coord_pousser->colonne=0;
            break;
        case 11:
            coord_pousser->ligne=3;
            coord_pousser->colonne=0;
            break;
        case 12:
            coord_pousser->ligne=1;
            coord_pousser->colonne=0;
            break;
    }
}


void deroulementTour(int nbjoueurs, t_pion *pion1, t_pion *pion2, t_pion *pion3, t_pion *pion4){
    t_case labyrinthe[7][7], tuile_en_plus;
    generation_plateau_debut(labyrinthe,&tuile_en_plus);

    int joueur_en_cours=1;//1 à 4 , c'est le num du joueur entrain de jouer
    int num_rangee;
    t_coord coord_pousser;//coordonnées de la case à pousser

    int ligne_arrivee, colonne_arrivee;

    switch (nbjoueurs) {
        case 2:
            do {//saisie de la rangée à déplacer par le joueur 1
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser\n",joueur_en_cours);//voir page 13 du sujet
                scanf("%d",&num_rangee);
            } while (num_rangee<1||num_rangee>12);
            conversion_num_rangee_coordonnees(&num_rangee,&coord_pousser);
            deplacer_tuiles(labyrinthe,&tuile_en_plus,&coord_pousser);

            do {//déplacement du pion 1
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&ligne_arrivee);
                } while (ligne_arrivee<0 || ligne_arrivee>6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&colonne_arrivee);
                } while (colonne_arrivee<0 || colonne_arrivee>6);
                if(deplacement_valide(labyrinthe,pion1,colonne_arrivee,ligne_arrivee)==0){
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe,pion1,colonne_arrivee,ligne_arrivee)==0);
            deplacer_pion(labyrinthe,pion1,colonne_arrivee,ligne_arrivee);

            //////joueur 2
            ++joueur_en_cours;

            do {
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser\n",joueur_en_cours);//voir page 13 du sujet
                scanf("%d",&num_rangee);
            } while (num_rangee<1||num_rangee>12);
            conversion_num_rangee_coordonnees(&num_rangee,&coord_pousser);
            deplacer_tuiles(labyrinthe,&tuile_en_plus,&coord_pousser);

            do {
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&ligne_arrivee);
                } while (ligne_arrivee<0 || ligne_arrivee>6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&colonne_arrivee);
                } while (colonne_arrivee<0 || colonne_arrivee>6);
                if(deplacement_valide(labyrinthe,pion2,colonne_arrivee,ligne_arrivee)==0){
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe,pion2,colonne_arrivee,ligne_arrivee)==0);
            deplacer_pion(labyrinthe,pion2,colonne_arrivee,ligne_arrivee);
        case 3:
            do {//saisie de la rangée à déplacer par le joueur 1
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser\n",joueur_en_cours);//voir page 13 du sujet
                scanf("%d",&num_rangee);
            } while (num_rangee<1||num_rangee>12);
            conversion_num_rangee_coordonnees(&num_rangee,&coord_pousser);
            deplacer_tuiles(labyrinthe,&tuile_en_plus,&coord_pousser);

            do {//déplacement du pion 1
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&ligne_arrivee);
                } while (ligne_arrivee<0 || ligne_arrivee>6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&colonne_arrivee);
                } while (colonne_arrivee<0 || colonne_arrivee>6);
                if(deplacement_valide(labyrinthe,pion1,colonne_arrivee,ligne_arrivee)==0){
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe,pion1,colonne_arrivee,ligne_arrivee)==0);
            deplacer_pion(labyrinthe,pion1,colonne_arrivee,ligne_arrivee);

            //////joueur 2
            ++joueur_en_cours;

            do {
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser\n",joueur_en_cours);//voir page 13 du sujet
                scanf("%d",&num_rangee);
            } while (num_rangee<1||num_rangee>12);
            conversion_num_rangee_coordonnees(&num_rangee,&coord_pousser);
            deplacer_tuiles(labyrinthe,&tuile_en_plus,&coord_pousser);

            do {
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&ligne_arrivee);
                } while (ligne_arrivee<0 || ligne_arrivee>6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&colonne_arrivee);
                } while (colonne_arrivee<0 || colonne_arrivee>6);
                if(deplacement_valide(labyrinthe,pion2,colonne_arrivee,ligne_arrivee)==0){
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe,pion2,colonne_arrivee,ligne_arrivee)==0);
            deplacer_pion(labyrinthe,pion2,colonne_arrivee,ligne_arrivee);


            //////joueur 3
            ++joueur_en_cours;

            do {
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser\n",joueur_en_cours);//voir page 13 du sujet
                scanf("%d",&num_rangee);
            } while (num_rangee<1||num_rangee>12);
            conversion_num_rangee_coordonnees(&num_rangee,&coord_pousser);
            deplacer_tuiles(labyrinthe,&tuile_en_plus,&coord_pousser);

            do {
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&ligne_arrivee);
                } while (ligne_arrivee<0 || ligne_arrivee>6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&colonne_arrivee);
                } while (colonne_arrivee<0 || colonne_arrivee>6);
                if(deplacement_valide(labyrinthe,pion3,colonne_arrivee,ligne_arrivee)==0){
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe,pion3,colonne_arrivee,ligne_arrivee)==0);
            deplacer_pion(labyrinthe,pion3,colonne_arrivee,ligne_arrivee);
            break;
        case 4:
            do {//saisie de la rangée à déplacer par le joueur 1
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser\n",joueur_en_cours);//voir page 13 du sujet
                scanf("%d",&num_rangee);
            } while (num_rangee<1||num_rangee>12);
            conversion_num_rangee_coordonnees(&num_rangee,&coord_pousser);
            deplacer_tuiles(labyrinthe,&tuile_en_plus,&coord_pousser);

            do {//déplacement du pion 1
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&ligne_arrivee);
                } while (ligne_arrivee<0 || ligne_arrivee>6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&colonne_arrivee);
                } while (colonne_arrivee<0 || colonne_arrivee>6);
                if(deplacement_valide(labyrinthe,pion1,colonne_arrivee,ligne_arrivee)==0){
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe,pion1,colonne_arrivee,ligne_arrivee)==0);
            deplacer_pion(labyrinthe,pion1,colonne_arrivee,ligne_arrivee);

            //////joueur 2
            ++joueur_en_cours;

            do {
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser\n",joueur_en_cours);//voir page 13 du sujet
                scanf("%d",&num_rangee);
            } while (num_rangee<1||num_rangee>12);
            conversion_num_rangee_coordonnees(&num_rangee,&coord_pousser);
            deplacer_tuiles(labyrinthe,&tuile_en_plus,&coord_pousser);

            do {
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&ligne_arrivee);
                } while (ligne_arrivee<0 || ligne_arrivee>6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&colonne_arrivee);
                } while (colonne_arrivee<0 || colonne_arrivee>6);
                if(deplacement_valide(labyrinthe,pion2,colonne_arrivee,ligne_arrivee)==0){
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe,pion2,colonne_arrivee,ligne_arrivee)==0);
            deplacer_pion(labyrinthe,pion2,colonne_arrivee,ligne_arrivee);


            //////joueur 3
            ++joueur_en_cours;

            do {
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser\n",joueur_en_cours);//voir page 13 du sujet
                scanf("%d",&num_rangee);
            } while (num_rangee<1||num_rangee>12);
            conversion_num_rangee_coordonnees(&num_rangee,&coord_pousser);
            deplacer_tuiles(labyrinthe,&tuile_en_plus,&coord_pousser);

            do {
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&ligne_arrivee);
                } while (ligne_arrivee<0 || ligne_arrivee>6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&colonne_arrivee);
                } while (colonne_arrivee<0 || colonne_arrivee>6);
                if(deplacement_valide(labyrinthe,pion3,colonne_arrivee,ligne_arrivee)==0){
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe,pion3,colonne_arrivee,ligne_arrivee)==0);
            deplacer_pion(labyrinthe,pion3,colonne_arrivee,ligne_arrivee);


            //////joueur 4
            ++joueur_en_cours;

            do {
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser\n",joueur_en_cours);//voir page 13 du sujet
                scanf("%d",&num_rangee);
            } while (num_rangee<1||num_rangee>12);
            conversion_num_rangee_coordonnees(&num_rangee,&coord_pousser);
            deplacer_tuiles(labyrinthe,&tuile_en_plus,&coord_pousser);

            do {
                do {
                    printf("Joueur %d, saisissez la ligne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&ligne_arrivee);
                } while (ligne_arrivee<0 || ligne_arrivee>6);
                do {
                    printf("Joueur %d, saisissez la colonne sur laquelle vous voulez vous deplacer (de 0 à 6)\n",joueur_en_cours);
                    scanf("%d",&colonne_arrivee);
                } while (colonne_arrivee<0 || colonne_arrivee>6);
                if(deplacement_valide(labyrinthe,pion4,colonne_arrivee,ligne_arrivee)==0){
                    printf("deplacement impossible, veuillez ressayer\n");
                }
            } while (deplacement_valide(labyrinthe,pion4,colonne_arrivee,ligne_arrivee)==0);
            deplacer_pion(labyrinthe,pion4,colonne_arrivee,ligne_arrivee);
            break;
    }


}