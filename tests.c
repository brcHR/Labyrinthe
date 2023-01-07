//
// Created by briac on 29/12/2022.
//
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include <windows.h>
#include "plateau.h"
#include "pion.h"
#include "cartestresors.h"
#include "Deroulement.h"
#include "affichage.h"

void tests(FILE *fichierlog){
    printf("TESTS\n");
    char liste[] = "AAAABBBBDDDJKSJLJQPPPPQSOJDEENCA";
    int c;
    int i,j,u,v;
    float J;
    t_case Case;
    t_case *pt_tuile = &Case;
    pt_tuile->ligne = 1;
    pt_tuile->colonne = 1;
    pt_tuile->forme = 'T';
    creation_type_case(pt_tuile);
    pt_tuile->fixe = 1;
    pt_tuile->tresor.un_tresor = 0;
    pt_tuile->tresor.num_tresor = 24;
    pt_tuile->start_finish = 1;
    pt_tuile->rotation = 0;
    pt_tuile->sortie_du_plateau.ligne = 1;
    pt_tuile->sortie_du_plateau.colonne = 1;

    for(i=0;i<360;i=i+90){
        for(j=0;j<360;j=j+90){
            t_case Case;
            t_case *pt_tuile = &Case;
            pt_tuile->ligne = 1;
            pt_tuile->colonne = 1;
            pt_tuile->forme = 'I';
            creation_type_case(pt_tuile);
            pt_tuile->fixe = 1;
            pt_tuile->tresor.un_tresor = 0;
            pt_tuile->tresor.num_tresor = 24;
            pt_tuile->start_finish = 1;
            pt_tuile->sortie_du_plateau.ligne = 1;
            pt_tuile->sortie_du_plateau.colonne = 1;
            pt_tuile->rotation = (float)i;
            J = (float)j;
            printf("Orientation ini :%f", pt_tuile->rotation);
            tourner(pt_tuile, J);
            printf("\tOrientation nouvelle :%f\n", pt_tuile->rotation);

            for(u=0;u<3;u++){
                for(v=0;v<3;v++){
                    printf("%c",pt_tuile->tableau[u][v]);
                }
                printf("\n");
            }
            printf("\n");
        }
    }

}

void testg(FILE *fichierlog){
    printf("TEST GENERATION PLATEAU\n\n");
    int i,j;
    t_case Labyrinthe[7][7], tuile_en_plus;
    t_case *pt_tuile_add = &tuile_en_plus;
    generation_plateau_debut(Labyrinthe,pt_tuile_add,fichierlog);

    printf("COORDONEES\n");

    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            printf("%d %d\t",Labyrinthe[i][j].ligne,Labyrinthe[i][j].colonne);
        }
        printf("\n");
    }
    printf("%d %d",tuile_en_plus.ligne,tuile_en_plus.colonne);
    printf("\n");

    printf("FORME\n");

    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            printf("%c\t",Labyrinthe[i][j].forme);
        }
        printf("\n");
    }
    printf("%c",tuile_en_plus.forme);
    printf("\n");

    printf("FIXE\n");

    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            printf("%d\t",Labyrinthe[i][j].fixe);
        }
        printf("\n");
    }
    printf("%d",tuile_en_plus.fixe);
    printf("\n");

    printf("ROTATION\n");

    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            printf("%f\t",Labyrinthe[i][j].rotation);
        }
        printf("\n");
    }
    printf("%f",tuile_en_plus.rotation);
    printf("\n");

    printf("TRESOR: UN NUM\n");

    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            printf("%d %d\t",Labyrinthe[i][j].tresor.un_tresor,Labyrinthe[i][j].tresor.num_tresor);
        }
        printf("\n");
    }
    printf("%d %d",tuile_en_plus.tresor.un_tresor,tuile_en_plus.tresor.num_tresor);
    printf("\n");

    printf("SORTIE PLATEAU COORD\n");

    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            printf("%d %d\t",Labyrinthe[i][j].sortie_du_plateau.ligne,Labyrinthe[i][j].sortie_du_plateau.colonne);
        }
        printf("\n");
    }
    printf("%d %d",tuile_en_plus.sortie_du_plateau.ligne,tuile_en_plus.sortie_du_plateau.colonne);
    printf("\n");

    printf("START FINISH\n");

    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            printf("%d\t",Labyrinthe[i][j].start_finish);
        }
        printf("\n");
    }
    printf("%d",tuile_en_plus.start_finish);
    printf("\n");


    printf("FIN TEST GENERATION PLATEAU\n\n");

}

void testd(FILE *fichierlog){
    int i,j;
    t_case Labyrinthe[7][7], tuile_en_plus;
    t_case *pt_tuile_add = &tuile_en_plus;
    t_coord coord;
    t_coord *pt_coord = &coord;
    t_pion pions[4];

    pt_coord->ligne =1;
    pt_coord->colonne =0;

    generation_plateau_debut(Labyrinthe,pt_tuile_add,fichierlog);

    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            printf("%d %d\t",Labyrinthe[i][j].ligne,Labyrinthe[i][j].colonne);
        }
        printf("\n");
    }
    printf("%d %d",tuile_en_plus.ligne,tuile_en_plus.colonne);
    printf("\n\n");

    deplacer_tuiles(Labyrinthe,pt_tuile_add,pt_coord,&pions[4],4, fichierlog);

    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            printf("%d %d\t",Labyrinthe[i][j].ligne,Labyrinthe[i][j].colonne);
        }
        printf("\n");
    }
    printf("%d %d",tuile_en_plus.ligne,tuile_en_plus.colonne);
    printf("\n\n");

    pt_coord->ligne = 5;
    pt_coord->colonne = 6;
    deplacer_tuiles(Labyrinthe,pt_tuile_add,pt_coord,&pions[4],4,fichierlog);

    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            printf("%d %d\t",Labyrinthe[i][j].ligne,Labyrinthe[i][j].colonne);
        }
        printf("\n");
    }
    printf("%d %d",tuile_en_plus.ligne,tuile_en_plus.colonne);
    printf("\n\n");

    pt_coord->ligne = 5;
    pt_coord->colonne = 0;
    deplacer_tuiles(Labyrinthe,pt_tuile_add,pt_coord,&pions[4],4,fichierlog);

    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            printf("%d %d\t",Labyrinthe[i][j].ligne,Labyrinthe[i][j].colonne);
        }
        printf("\n");
    }
    printf("%d %d",tuile_en_plus.ligne,tuile_en_plus.colonne);
    printf("\n");

}

void testDistrib(){
    int nbjoueurs;

    do {
        printf("saisissez le nombre de joueurs (entre 2 et 4)\n");
        fflush(stdin);
        scanf("%d",&nbjoueurs);
    } while (nbjoueurs<2 || nbjoueurs>4);

    t_pion pion1, pion2, pion3, pion4;
    t_pion pions[4];

    for (int i = 0; i < 12; ++i) {
        pion1.tresors[i].signe='0',pion2.tresors[i].signe='0',pion3.tresors[i].signe='0', pion4.tresors[i].signe='0';
    }
    for (int i = 0; i < 12; ++i) {
        pion1.tresors[i].decouvert=0,pion2.tresors[i].decouvert=0,pion3.tresors[i].decouvert=0,pion4.tresors[i].decouvert=0;
    }


    DistributionCartes(&nbjoueurs,&pions[4]);
    for (int i = 0; i < 12; ++i) {
        printf("%c , %c, %c\n",pion1.tresors[i].signe,pion2.tresors[i].signe,pion3.tresors[i].signe);
    }

    AffichageTresor(&pion1);

}

void testDeroulement(FILE *fichierlog){
    int nbjoueurs;
    t_case labyrinthe[7][7], tuile_en_plus;

    do {
        printf("saisissez le nombre de joueurs (entre 2 et 4)\n");
        fflush(stdin);
        scanf("%d",&nbjoueurs);
    } while (nbjoueurs<2 || nbjoueurs>4);

    t_pion pion1, pion2, pion3, pion4;
    t_pion pions[4];


    for (int i = 0; i < 12; ++i) {
        pion1.tresors[i].signe='0',pion2.tresors[i].signe='0',pion3.tresors[i].signe='0', pion4.tresors[i].signe='0';
    }
    for (int i = 0; i < 12; ++i) {
        pion1.tresors[i].decouvert=0,pion2.tresors[i].decouvert=0,pion3.tresors[i].decouvert=0,pion4.tresors[i].decouvert=0;
    }
    deroulementTour(&nbjoueurs,labyrinthe,&tuile_en_plus,&pions[4],fichierlog);

}

void testMenu(FILE *fichierlog){
    Menu(fichierlog);
}


void deplacement_valide_test(FILE *fichierlog){
    int i,j,z,w,ligne,colonne;
    t_pion joueur;
    t_case labyrinthe[7][7], tuile_en_plus;
    t_case Case;
    t_case *pt_tuile = &Case;

    joueur.position_pion = &labyrinthe[0][0];

    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(&labyrinthe[i][j] != joueur.position_pion){
                printf("0\t");
            }
            else{
                printf("1\t");
            }
        }
        printf("\n");
    }
    printf("\n");

    //deplacement à droite
    //Pas de murs dans les deux cases.
    labyrinthe[0][0].tableau[1][2] = '0';
    labyrinthe[0][1].tableau[1][0] = '0';
    ligne = 0;
    colonne = 1;

    deplacer_pion(labyrinthe,&joueur,colonne,ligne, fichierlog);
    printf("\n");
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(&labyrinthe[i][j] != joueur.position_pion){
                printf("0\t");
            }
            else{
                printf("1\t");
            }
        }
        printf("\n");
    }

    //murs dans les deux cases.
    labyrinthe[0][0].tableau[1][2] = '0';
    labyrinthe[0][1].tableau[1][0] = '0';
    labyrinthe[0][1].tableau[1][2] = '0';
    labyrinthe[0][2].tableau[1][0] = '0';
    labyrinthe[0][2].tableau[1][2] = '0';
    labyrinthe[0][3].tableau[1][0] = '0';
    labyrinthe[0][3].tableau[1][0] = '0';

    ligne = 0;
    colonne = 3;

    deplacer_pion(labyrinthe,&joueur,colonne,ligne, fichierlog);
    printf("\n");
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(&labyrinthe[i][j] != joueur.position_pion){
                printf("0\t");
            }
            else{
                printf("1\t");
            }
        }
        printf("\n");
    }

    labyrinthe[0][3].tableau[2][1] = '0';
    labyrinthe[1][3].tableau[0][1] = '0';


    ligne = 1;
    colonne = 3;

    deplacer_pion(labyrinthe,&joueur,colonne,ligne,fichierlog);
    printf("\n");
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(&labyrinthe[i][j] != joueur.position_pion){
                printf("0\t");
            }
            else{
                printf("1\t");
            }
        }
        printf("\n");
    }

    labyrinthe[0][3].tableau[2][1] = '0';
    labyrinthe[1][3].tableau[0][1] = '1';

    ligne = 0;
    colonne = 3;

    deplacer_pion(labyrinthe,&joueur,colonne,ligne,fichierlog);
    printf("\n");
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            if(&labyrinthe[i][j] != joueur.position_pion){
                printf("0\t");
            }
            else{
                printf("1\t");
            }
        }
        printf("\n");
    }
}

void testrecup_tresor(FILE *fichierlog){
    int i,j;
    t_case Labyrinthe[7][7], tuile_en_plus;
    t_case *pt_tuile_add = &tuile_en_plus;
    t_coord coord;
    t_pion pions[4];
    t_coord *pt_coord = &coord;
    int nb = 2;
    int* pt_nb = &nb;

    pions[0].coord_depart_arrivee.ligne=0;
    pions[0].coord_depart_arrivee.colonne=0;
    pions[0].position_pion = &Labyrinthe[0][0];
    pions[0].lig = pions[0].position_pion->ligne;
    pions[0].col = pions[0].position_pion->colonne;

    pions[1].coord_depart_arrivee.ligne=0;
    pions[1].coord_depart_arrivee.colonne=6;
    pions[1].position_pion = &Labyrinthe[0][6];
    pions[1].lig = pions[1].position_pion->ligne;
    pions[1].col = pions[1].position_pion->colonne;

    DistributionCartes(pt_nb,pions);

    generation_plateau_debut(Labyrinthe,pt_tuile_add,fichierlog);
    printf("\n");
    for(i=0;i<7;i++){
        for(j=0;j<7;j++){
            printf("%d %c\t",Labyrinthe[i][j].tresor.num_tresor,Labyrinthe[i][j].tresor.num_tresor+65);
        }
        printf("\n");
    }
    printf("%d %c",tuile_en_plus.tresor.num_tresor,tuile_en_plus.tresor.num_tresor+65);
    printf("\n");



}

void test_affichage(FILE *fichierlog){
    t_case plateauTest[7][7];
    t_case caseEnTropTest;
    t_pion pions[4];

    generation_plateau_debut(plateauTest, &caseEnTropTest,fichierlog);
    pions[0].coord_depart_arrivee.ligne=0;
    pions[0].coord_depart_arrivee.colonne=0;
    pions[0].position_pion = &plateauTest[0][0];
    pions[0].lig = 0; //pions[0].position_pion->ligne;
    pions[0].col = 0 ;//pions[0].position_pion->colonne;

    pions[1].coord_depart_arrivee.ligne=0;
    pions[1].coord_depart_arrivee.colonne=6;
    pions[1].position_pion = &plateauTest[0][6];
    pions[1].lig = 0; //pions[1].position_pion->ligne;
    pions[1].col = 6;//pions[1].position_pion->colonne;

    pions[2].position_pion = &plateauTest[6][0];
    pions[2].lig = 6;//pions[2].position_pion->ligne;
    pions[2].col = 0;//pions[2].position_pion->colonne;

    pions[3].position_pion = &plateauTest[6][6];
    pions[3].lig = 6;//pions[3].position_pion->ligne;
    pions[3].col = 6;//pions[3].position_pion->colonne;

    system("cls");
    affichageComplet(plateauTest,caseEnTropTest,&pions[4],4);
}