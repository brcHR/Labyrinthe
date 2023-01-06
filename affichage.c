//
// Created by Aurélien on 04/01/2023.
//
#include "affichage.h"
#include "plateau.h"
#include <windows.h>
#include <stdio.h>
#include "pion.h"


//procedure pour placer le curseur a des coord données
void cooCurseur(int lig, int col){
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

//procedure pour changer la couleur du texte sur cmd
void couleurCurseur(int texte,int fond){
    HANDLE H=GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(H,fond*16+texte);
}

// affichage des case I en fonction de leur coord et de leur angle et tresor
void afficheCaseI(int lig, int col, int angle, int numTresor, int presTresor) {
    cooCurseur((3 * lig)+7, (9 * col)+3+col);           // on place le curseur sur le coin haut gauche de la case (case 3*9)
    if (presTresor == 1) {
        if (angle == 0 || angle == 180) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+3+col);
            printf("%c%c%c %c %c%c%c", 219, 219, 219, numTresor+65,219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);

        }
        else if (angle == 90 || angle == 270) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+8+col);
            printf("%c",numTresor+65);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
    }
    else if (presTresor == 0){
        if (angle == 0 || angle == 180) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+3+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219 ,219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 90 || angle == 270) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
    }
}

// affichage des case T en fonction de leur coord et de leur angle et tresor
void afficheCaseT(int lig, int col, int angle, int numTresor, int presTresor){
    cooCurseur((3 * lig)+7, (9 * col)+3+col);
    if (presTresor == 1) {
        if (angle == 0) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+7+col);
            printf("%c", numTresor+65);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 90) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+3+col);
            printf("    %c %c%c%c", numTresor+65, 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 180) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+7+col);
            printf("%c", numTresor+65);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 270) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+3+col);
            printf("%c%c%c %c", 219, 219, 219, numTresor+65);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
    }
    else if (presTresor == 0){
        if (angle == 0) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 90) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+3+col);
            printf("      %c%c%c", 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 180) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 270) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+3+col);
            printf("%c%c%c", 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
    }
}

// affichage des case L en fonction de leur coord et de leur angle et tresor
void afficheCaseL(int lig, int col, int angle, int numTresor, int presTresor){
    cooCurseur((3 * lig)+7, (9 * col)+3+col);
    if (presTresor == 1) {
        if (angle == 0) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+3+col);
            printf("%c%c%c %c", 219, 219, 219, numTresor+65);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 90) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+3+col);
            printf("%c%c%c %c", 219, 219, 219, numTresor+65);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 180) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+3+col);
            printf("    %c %c%c%c", numTresor+65, 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 270) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+3+col);
            printf("    %c %c%c%c", numTresor+65, 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
    }
    else if (presTresor == 0){
        if (angle == 0) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+3+col);
            printf("%c%c%c", 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 90) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+3+col);
            printf("%c%c%c", 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 180) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+3+col);
            printf("      %c%c%c", 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 270) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+3+col);
            printf("      %c%c%c", 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+3+col);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
    }
}

//affcihage des fleches autour du plateau
void afficheFleche(){
    //fleche du haut
    cooCurseur(6, 17);
    printf("%c1", 25);
    cooCurseur(6, 37);
    printf("%c2", 25);
    cooCurseur(6, 57);
    printf("%c3", 25);
    //fleche de gauche
    cooCurseur(10, 0);
    printf("  %c\n12%c\n  %c", 62, 62, 62);
    cooCurseur(16, 0);
    printf("  %c\n11%c\n  %c", 62, 62, 62);
    cooCurseur(22, 0);
    printf("  %c\n10%c\n  %c", 62, 62, 62);
    //fleche de droite
    cooCurseur(10, 73);
    printf("%c", 60);
    cooCurseur(11, 73);
    printf("%c4", 60);
    cooCurseur(12, 73);
    printf("%c", 60);
    cooCurseur(16, 73);
    printf("%c", 60);
    cooCurseur(17, 73);
    printf("%c5", 60);
    cooCurseur(18, 73);
    printf("%c", 60);
    cooCurseur(22, 73);
    printf("%c", 60);
    cooCurseur(23, 73);
    printf("%c6", 60);
    cooCurseur(24, 73);
    printf("%c", 60);
    //fleche du bas
    cooCurseur(28, 17);
    printf("%c9", 24);
    cooCurseur(28, 37);
    printf("%c8", 24);
    cooCurseur(28, 57);
    printf("%c7", 24);
}

//affichage du tableau en entier + appelle afficheFleche
void afficheLabyrinthe(t_case plateau[7][7]){
    for (int i = 0; i < 7; i ++){
        for (int j = 0; j < 7; j++){
            if (plateau[i][j].forme == 'I'){
                afficheCaseI(i, j, plateau[i][j].rotation, plateau[i][j].tresor.num_tresor , plateau[i][j].tresor.un_tresor);
            }
            else if(plateau[i][j].forme == 'T'){
                afficheCaseT(i, j, plateau[i][j].rotation, plateau[i][j].tresor.num_tresor , plateau[i][j].tresor.un_tresor);
            }
            else if(plateau[i][j].forme == 'L'){
                afficheCaseL(i, j, plateau[i][j].rotation, plateau[i][j].tresor.num_tresor , plateau[i][j].tresor.un_tresor);
            }

        }
    }
    afficheFleche();
}

// affichage de la case en plus
void afficheCaseEnPlus(t_case caseEnPlus){
    cooCurseur(15,85);
    printf("Case supplementaire :");
    if (caseEnPlus.forme == 'I'){
        afficheCaseI(3, 9, caseEnPlus.rotation, caseEnPlus.tresor.num_tresor , caseEnPlus.tresor.un_tresor);
    }
    else if(caseEnPlus.forme == 'T'){
        afficheCaseT(3, 9, caseEnPlus.rotation, caseEnPlus.tresor.num_tresor , caseEnPlus.tresor.un_tresor);
    }
    else if(caseEnPlus.forme == 'L'){
        afficheCaseL(3, 9, caseEnPlus.rotation, caseEnPlus.tresor.num_tresor , caseEnPlus.tresor.un_tresor);
    }
}

//couleur j1 = rouge   j2 = jaune  j3 = vert   j4 = bleu
//affichage des pions
// ascii 3, 4, 5, 6         3 : ♥    4 : ♦    5 : ♣    6 : ♠    rouge jaune vert bleu
// 2:vert   9:bleu  12:rouge    14:jaune    15 blanc    0:noir

// affiche les pions
void affichePions(t_pion pion[4]){
    int lig, col;
    /*
    pions[0].coord_depart_arrivee.ligne=0;
    pions[0].coord_depart_arrivee.colonne=0;
    pions[1].coord_depart_arrivee.ligne=0;
    pions[1].coord_depart_arrivee.colonne=7;
    pions[2].coord_depart_arrivee.ligne=7;
    pions[2].coord_depart_arrivee.colonne=7;
    pions[3].coord_depart_arrivee.ligne=7;
    pions[3].coord_depart_arrivee.colonne=0;
    */
    for (int i = 0; i < 4; i++){
        //lig = pion[i].lig;
        //col = pion[i].col;
        lig = pion[i].position_pion->ligne;
        col = pion[i].position_pion->colonne;
        cooCurseur((3 * lig)+8, (9 * col)+7+col);
        if (pion[i].num_pion == 0){
            couleurCurseur(12, 0);
        }
        else if (pion[i].num_pion == 1){
            couleurCurseur(14, 0);
        }
        else if (pion[i].num_pion == 2){
            couleurCurseur(2, 0);
        }
        else if (pion[i].num_pion == 3){
            couleurCurseur(9, 0);
        }
        printf("%c", pion[i].num_pion+3);
        couleurCurseur(15, 0);
    }
    //pion->position_pion->ligne
    //test :
    //cooCurseur((3 * lig)+7, (9 * col)+1+col);
    /*
     * pour le centre des cases : cooCurseur((3 * lig)+8, (9 * col)+7+col);     !!!
    cooCurseur(8, 5);
    couleurCurseur(12, 0);
    printf("%c", 3);
    couleurCurseur(15,0);
    */
}

//test
void testPions(t_pion pions[4]){
    for (int i = 0; i < 4; i++){
        pions[i].num_pion = i;
        //pions[i].lig = i;
        //pions[i].col = i;
    }
    pions[0].lig=0;
    pions[0].col=0;
    pions[1].lig=0;
    pions[1].col=6;
    pions[2].lig=6;
    pions[2].col=6;
    pions[3].lig=6;
    pions[3].col=0;
}

// tout l'affichage principal du jeu
void affichageComplet(t_case plateau[7][7], t_case caseEnPlus, t_pion pions[4]){
    system("cls");
    afficheLabyrinthe(plateau);
    afficheCaseEnPlus(caseEnPlus);
    affichePions(pions);
    cooCurseur(30, 0);
}