//
// Created by Maxime Vennin on 30/12/2022.
//

#include <stdio.h>
#include "Deroulement.h"

void deroulementTour(int nbjoueurs){
    t_case labyrinthe[7][7], tuile_add;
    generation_plateau_debut(labyrinthe,&tuile_add);

    int joueur_en_cours=1;//1 à 4 , c'est le num du joueur entrain de jouer
    int num_rangee;
    t_coord coord_pousser;//coordonnées de la case à pousser


    switch (nbjoueurs) {
        case 2:
            do {
                printf("Joueur %d, saisissez le numéro de la rangée que vous voulez faire glisser\n");//voir page 13 du sujet
                scanf("%d",&num_rangee);
            } while (num_rangee<1||num_rangee>12);
            switch (num_rangee) {
                case 1:// flèche en haut à gauche (rangée de flèches du haut)
                    coord_pousser.ligne=0;
                    coord_pousser.colonne=1;
                    break;
            }
    }


}