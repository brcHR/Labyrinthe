//
// Created by Aurélien on 04/01/2023.
//
#include "affichage.h"
#include "plateau.h"
#include <windows.h>
#include <stdio.h>


// angle -> 0, 90, 180 ou 270
// numero tresor: 0 à 23


//procedure pour placer le curseur a des coord données
void cooCurseur(int lig, int col){
    COORD mycoord;
    mycoord.X = col;
    mycoord.Y = lig;
    SetConsoleCursorPosition( GetStdHandle( STD_OUTPUT_HANDLE ), mycoord );

}

// affichage des case I en fonction de leur coord et de leur angle et tresor
void afficheCaseI(int lig, int col, int angle, int numTresor, int presTresor) {
    cooCurseur((3 * lig)+1, (9 * col)+1);           // on place le curseur sur le coin haut gauche de la case (case 3*9)
    if (presTresor == 1) {
        if (angle == 0 || angle == 180) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+2, (9 * col)+1);
            printf("%c%c%c  %c%c%c%c", 219, 219, 219, numTresor+65,219, 219, 219);//tresor
            cooCurseur((3 * lig)+3, (9 * col)+1);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);

        }
        else if (angle == 90 || angle == 270) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+2, (9 * col)+6);   //a test
            printf("%c",numTresor+65);
            cooCurseur((3 * lig)+3, (9 * col)+1);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
    }
    else if (presTresor == 0){
        if (angle == 0 || angle == 180) {
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+2, (9 * col)+1);
            printf("%c%c%c   %c%c%c", 219, 219, 219 ,219, 219, 219);
            cooCurseur((3 * lig)+3, (9 * col)+1);
            printf("%c%c%c   %c%c%c", 219, 219, 219, 219, 219, 219);
        }
        else if (angle == 90 || angle == 270) {
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
            cooCurseur((3 * lig)+3, (9 * col)+1);
            printf("%c%c%c%c%c%c%c%c%c", 219, 219, 219, 219, 219, 219, 219, 219, 219);
        }
    }
}

// affichage des case T en fonction de leur coord et de leur angle et tresor
void afficheCaseT(int lig, int col, int angle, int numTresor, int presTresor){
    if (presTresor == 1) {
        if (angle == 0) {

        }
        else if (angle == 90) {

        }
        else if (angle == 180) {

        }
        else if (angle == 270) {

        }
    }
    else if (presTresor == 0){
        if (angle == 0) {

        }
        else if (angle == 90) {

        }
        else if (angle == 180) {

        }
        else if (angle == 270) {

        }
    }
}

// affichage des case L en fonction de leur coord et de leur angle et tresor
void afficheCaseL(int lig, int col, int angle, int numTresor, int presTresor){
    if (presTresor == 1) {
        if (angle == 0) {

        }
        else if (angle == 90) {

        }
        else if (angle == 180) {

        }
        else if (angle == 270) {

        }
    }
    else if (presTresor == 0){
        if (angle == 0) {

        }
        else if (angle == 90) {

        }
        else if (angle == 180) {

        }
        else if (angle == 270) {

        }
    }
}

//affcihage des fleches autour du plateau
void afficheFleche(){

}

//affichage du tableau en entier
void afficheTableau(t_case plateau[7][7]){
    for (int i = 0; i < 7; i ++){
        for (int j = 0; j < 7; j++){
            if (plateau[i][j].forme == 'I'){
                afficheCaseI(i, j, plateau[i][j].rotation, plateau[i][j].tresor.num_tresor , plateau[i][j].tresor.un_tresor);
            }

        }
    }
}


//affichage des pions
// ascii 3, 4, 5, 6
void affichePions(){

}