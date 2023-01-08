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
            if ((i == 0 || i == 2 || i == 4 || i == 6) && (j == 0 || j == 2 || j == 4 || j == 6)){
                couleurCurseur(8, 0);
            }
            if (i == 0 && j == 0){
                couleurCurseur(12, 0);
            }
            if (i == 0 && j == 6){
                couleurCurseur(14, 0);
            }
            if (i == 6 && j == 6){
                couleurCurseur(2, 0);
            }
            if (i == 6 && j == 0){
                couleurCurseur(9, 0);
            }
            if (plateau[i][j].forme == 'I'){
                afficheCaseI(i, j, plateau[i][j].rotation, plateau[i][j].tresor.num_tresor , plateau[i][j].tresor.un_tresor);
            }
            else if(plateau[i][j].forme == 'T'){
                afficheCaseT(i, j, plateau[i][j].rotation, plateau[i][j].tresor.num_tresor , plateau[i][j].tresor.un_tresor);
            }
            else if(plateau[i][j].forme == 'L'){
                afficheCaseL(i, j, plateau[i][j].rotation, plateau[i][j].tresor.num_tresor , plateau[i][j].tresor.un_tresor);
            }
            couleurCurseur(15, 0);
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
void affichePions(t_pion pion[4], int nbJoueur){
    int lig, col;
    //test pour voir si il y a plusieur pions sur la meme case
    if ((pion[0].lig == pion[1].lig && pion[0].col == pion[1].col) || (pion[0].lig == pion[2].lig && pion[0].col == pion[2].col) || (pion[0].lig == pion[3].lig && pion[0].col == pion[3].col) || (pion[1].lig == pion[2].lig && pion[1].col == pion[2].col) || (pion[1].lig == pion[3].lig && pion[1].col == pion[3].col) || (pion[2].lig == pion[3].lig && pion[2].col == pion[3].col)){
        for (int i = 0; i < nbJoueur; i++) {
            lig = pion[i].lig;
            col = pion[i].col;
            cooCurseur((3 * lig) + 8, (9 * col) + 6 + col + i);
            if (pion[i].num_pion == 0) {
                couleurCurseur(12, 0);
            } else if (pion[i].num_pion == 1) {
                couleurCurseur(14, 0);
            } else if (pion[i].num_pion == 2) {
                couleurCurseur(2, 0);
            } else if (pion[i].num_pion == 3) {
                couleurCurseur(9, 0);
            }
            printf("%c", pion[i].num_pion + 3);
            couleurCurseur(15, 0);
        }
    }
    else {
        for (int i = 0; i < nbJoueur; i++) {
            lig = pion[i].lig;
            col = pion[i].col;
            cooCurseur((3 * lig) + 8, (9 * col) + 7 + col);
            if (pion[i].num_pion == 0) {
                couleurCurseur(12, 0);
            } else if (pion[i].num_pion == 1) {
                couleurCurseur(14, 0);
            } else if (pion[i].num_pion == 2) {
                couleurCurseur(2, 0);
            } else if (pion[i].num_pion == 3) {
                couleurCurseur(9, 0);
            }
            printf("%c", pion[i].num_pion + 3);
            couleurCurseur(15, 0);
        }
    }
}

//test
void testPions(t_pion pions[4]){
    for (int i = 0; i < 4; i++){
        pions[i].num_pion = i;
        //pions[i].lig = i;
        //pions[i].col = i;
    }
    /*
    pions[0].lig=0;
    pions[0].col=0;
    pions[1].lig=0;
    pions[1].col=6;
    pions[2].lig=6;
    pions[2].col=6;
    pions[3].lig=6;
    pions[3].col=0;
     */
    pions[0].lig=0;
    pions[0].col=0;
    pions[1].lig=0;
    pions[1].col=0;
    pions[2].lig=0;
    pions[2].col=0;
    pions[3].lig=0;
    pions[3].col=0;
}

// tout l'affichage principal du jeu
void affichageComplet(t_case plateau[7][7], t_case caseEnPlus, t_pion pions[4], int nbJoueur){
    system("cls");
    afficheLabyrinthe(plateau);
    afficheCaseEnPlus(caseEnPlus);
    affichePions(pions, nbJoueur);
    cooCurseur(30, 0);
}

//affichage du logo
void afficheLogo(int lig, int col) {
    system("cls");
    // L
    couleurCurseur(12, 0);

    cooCurseur(lig, col + 1);
    printf("%c%c%c%c", 201, 205, 205, 187);
    cooCurseur(lig + 1, col + 1);
    printf("%c  %c", 186, 186);
    cooCurseur(lig + 2, col + 1);
    printf("%c  %c", 186, 186);
    cooCurseur(lig + 3, col + 1);
    printf("%c  %c%c%c%c", 186, 200, 205, 205, 187);
    cooCurseur(lig + 4, col + 1);
    printf("%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 188);
    // A
    couleurCurseur(14, 0);

    cooCurseur(lig, col + 8);
    printf("%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 205, 187);
    cooCurseur(lig + 1, col + 8);
    printf("%c %c%c%c%c %c", 186, 201, 205, 205, 187, 186);
    cooCurseur(lig + 2, col + 8);
    printf("%c %c%c%c%c %c", 186, 200, 205, 205, 188, 186);
    cooCurseur(lig + 3, col + 8);
    printf("%c %c%c%c%c %c", 186, 201, 205, 205, 187, 186);
    cooCurseur(lig + 4, col + 8);
    printf("%c%c%c  %c%c%c", 200, 205, 188, 200, 205, 188);
    // B
    couleurCurseur(2, 0);

    cooCurseur(lig, col + 16);
    printf("%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 187);
    cooCurseur(lig + 1, col + 16);
    printf("%c     %c", 186, 186);
    cooCurseur(lig + 2, col + 16);
    printf("%c   %c%c%c%c", 186, 205, 205, 202, 187);
    cooCurseur(lig + 3, col + 16);
    printf("%c      %c", 186, 186);
    cooCurseur(lig + 4, col + 16);
    printf("%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 188);
    // Y
    couleurCurseur(9, 0);

    cooCurseur(lig, col + 24);
    printf("%c%c%c  %c%c%c", 201, 205, 187, 201, 205, 187);
    cooCurseur(lig + 1, col + 24);
    printf("%c %c%c%c%c %c", 186, 200, 205, 205, 188, 186);
    cooCurseur(lig + 2, col + 24);
    printf("%c%c%c  %c%c%c", 200, 205, 187, 201, 205, 188);
    cooCurseur(lig + 3, col + 24);
    printf("  %c  %c", 186, 186);
    cooCurseur(lig + 4, col + 24);
    printf("  %c%c%c%c", 200, 205, 205, 188);
    // R
    couleurCurseur(12, 0);

    cooCurseur(lig, col + 32);
    printf("%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 205, 187);
    cooCurseur(lig + 1, col + 32);
    printf("%c      %c", 186, 186);
    cooCurseur(lig + 2, col + 32);
    printf("%c   %c%c%c%c", 186, 205, 205, 203, 188);
    cooCurseur(lig + 3, col + 32);
    printf("%c %c%c%c %c", 186, 201, 205, 187, 186);
    cooCurseur(lig + 4, col + 32);
    printf("%c%c%c %c%c%c", 200, 205, 188, 200, 205, 188);
    // I
    couleurCurseur(14, 0);

    cooCurseur(lig, col + 40);
    printf("%c%c%c%c", 201, 205, 205, 187);
    cooCurseur(lig + 1, col + 40);
    printf("%c  %c", 186, 186);
    cooCurseur(lig + 2, col + 40);
    printf("%c  %c", 186, 186);
    cooCurseur(lig + 3, col + 40);
    printf("%c  %c", 186, 186);
    cooCurseur(lig + 4, col + 40);
    printf("%c%c%c%c", 200, 205, 205, 188);
    // N
    couleurCurseur(2, 0);

    cooCurseur(lig, col + 44);
    printf("%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 187, 201, 205, 187);
    cooCurseur(lig + 1, col + 44);
    printf("%c   %c%c %c", 186, 186, 186, 186);
    cooCurseur(lig + 2, col + 44);
    printf("%c %c%c%c%c %c", 186, 201, 187, 200, 188, 186);
    cooCurseur(lig + 3, col + 44);
    printf("%c %c%c   %c", 186, 186, 186, 186);
    cooCurseur(lig + 4, col + 44);
    printf("%c%c%c%c%c%c%c%c", 200, 205, 188, 200, 205, 205, 205, 188);
    // T
    couleurCurseur(9, 0);

    cooCurseur(lig, col + 52);
    printf("%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 205, 187);
    cooCurseur(lig + 1, col + 52);
    printf("%c%c%c  %c%c%c", 200, 205, 187, 201, 205, 188);
    cooCurseur(lig + 2, col + 52);
    printf("  %c  %c", 186, 186);
    cooCurseur(lig + 3, col + 52);
    printf("  %c  %c", 186, 186);
    cooCurseur(lig + 4, col + 52);
    printf("  %c%c%c%c", 200, 205, 205, 188);
    // H
    couleurCurseur(12, 0);

    cooCurseur(lig, col + 60);
    printf("%c%c%c  %c%c%c", 201, 205, 187, 201, 205, 187);
    cooCurseur(lig + 1, col + 60);
    printf("%c %c%c%c%c %c", 186, 200, 205, 205, 188, 186);
    cooCurseur(lig + 2, col + 60);
    printf("%c %c%c%c%c %c", 186, 201, 205, 205, 187, 186);
    cooCurseur(lig + 3, col + 60);
    printf("%c %c  %c %c", 186, 186, 186, 186);
    cooCurseur(lig + 4, col + 60);
    printf("%c%c%c  %c%c%c", 200, 205, 188, 200, 205, 188);
    // E
    couleurCurseur(14, 0);

    cooCurseur(lig, col + 68);
    printf("%c%c%c%c%c%c%c%c", 201, 205, 205, 205, 205, 205, 205, 187);
    cooCurseur(lig + 1, col + 68);
    printf("%c  %c%c%c%c%c", 186, 201, 205, 205, 205, 188);
    cooCurseur(lig + 2, col + 68);
    printf("%c  %c%c%c", 186, 204, 205, 205);
    cooCurseur(lig + 3, col + 68);
    printf("%c  %c%c%c%c%c", 186, 200, 205, 205, 205, 187);
    cooCurseur(lig + 4, col + 68);
    printf("%c%c%c%c%c%c%c%c", 200, 205, 205, 205, 205, 205, 205, 188);

    cooCurseur(lig+6, col+1);
}