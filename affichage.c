//
// Created by Aurélien on 04/01/2023.
//
#include "affichage.h"
#include "plateau.h"
#include <windows.h>
#include <stdio.h>



//procedure pour placer le curseur a des coord données
void cooCurseur(int lig, int col){
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );
}

// affichage des case I en fonction de leur coord et de leur angle et tresor
void afficheCaseI(int lig, int col, int angle, int numTresor, int presTresor) {
    cooCurseur((3 * lig)+7, (9 * col)+1+col);           // on place le curseur sur le coin haut gauche de la case (case 3*9)
    if (presTresor == 1) {                                                      // condition joueur !!!!
        if (angle == 0 || angle == 180) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+1+col);
            printf("%c%c%c %c %c%c%c", 219, 219, 219, numTresor+65,219, 219, 219);//tresor
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);

        }
        else if (angle == 90 || angle == 270) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+6+col);   //a test
            printf("%c",numTresor+65);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
    }
    else if (presTresor == 0){
        if (angle == 0 || angle == 180) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+1+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219 ,219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 90 || angle == 270) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
    }
}

// affichage des case T en fonction de leur coord et de leur angle et tresor
void afficheCaseT(int lig, int col, int angle, int numTresor, int presTresor){
    cooCurseur((3 * lig)+7, (9 * col)+1+col);
    if (presTresor == 1) {
        if (angle == 0) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+5+col);
            printf("%c", numTresor+65);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 90) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+1+col);
            printf("    %c %c%c%c", numTresor+65, 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 180) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+5+col);
            printf("%c", numTresor+65);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 270) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+1+col);
            printf("%c%c%c %c", 219, 219, 219, numTresor+65);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
    }
    else if (presTresor == 0){
        if (angle == 0) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 90) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+1+col);
            printf("      %c%c%c", 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 180) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 270) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+1+col);
            printf("%c%c%c", 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
    }
}

// affichage des case L en fonction de leur coord et de leur angle et tresor
void afficheCaseL(int lig, int col, int angle, int numTresor, int presTresor){
    cooCurseur((3 * lig)+7, (9 * col)+1+col);
    if (presTresor == 1) {
        if (angle == 0) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+1+col);
            printf("%c%c%c %c", 219, 219, 219, numTresor+65);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 90) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+1+col);
            printf("%c%c%c %c", 219, 219, 219, numTresor+65);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 180) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+1+col);
            printf("    %c %c%c%c", numTresor+65, 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 270) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+1+col);
            printf("    %c %c%c%c", numTresor+65, 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
    }
    else if (presTresor == 0){
        if (angle == 0) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+1+col);
            printf("%c%c%c", 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 90) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+1+col);
            printf("%c%c%c", 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 180) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+1+col);
            printf("      %c%c%c", 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 270) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+8, (9 * col)+1+col);
            printf("      %c%c%c", 219, 219, 219);
            cooCurseur((3 * lig)+9, (9 * col)+1+col);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
    }
}

//affcihage des fleches autour du plateau
void afficheFleche(){
    cooCurseur(6, 15);
    printf("%c", 25);
    cooCurseur(6, 35);
    printf("%c", 25);
    cooCurseur(6, 55);
    printf("%c", 25);

    cooCurseur(11, 0);
    printf("%c", 62);
    cooCurseur(17, 0);
    printf("%c", 62);
    cooCurseur(23, 0);
    printf("%c", 62);

    cooCurseur(11, 71);
    printf("%c", 60);
    cooCurseur(17, 71);
    printf("%c", 60);
    cooCurseur(23, 71);
    printf("%c", 60);

    cooCurseur(28, 15);
    printf("%c", 24);
    cooCurseur(28, 35);
    printf("%c", 24);
    cooCurseur(28, 55);
    printf("%c", 24);
}

//affichage du tableau en entier
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
}


//affichage des pions
// ascii 3, 4, 5, 6
void affichePions(){

}