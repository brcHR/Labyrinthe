//
// Created by briac on 29/12/2022.
//
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "plateau.h"
#include "pion.h"

void tests(){
    printf("TESTS\n");
    char liste[] = "AAAABBBBDDDJKSJLJQPPPPQSOJDEENCA";
    int c;
    int i,j,u,v;
    float J;
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
    pt_tuile->rotation = 0;
    pt_tuile->sortie_du_plateau.ligne = 1;
    pt_tuile->sortie_du_plateau.colonne = 1;

    for(i=0;i<360;i=i+90){
        for(j=0;j<360;j=j+90){
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