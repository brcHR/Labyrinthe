//
// Created by Maxime Vennin on 27/12/2022.
//

#ifndef LABYRINTHE_TRESORS_H
#define LABYRINTHE_TRESORS_H


typedef struct { //structure temporaire pour test à implémenter dans plateau.h
    char signe;
    int decouvert; // 1 s'il a été découvert,0 sinon
}t_tresor;

typedef struct {
    //t_case *position_pion; // Pointeur vers la case où le pion se trouve
    int num_pion;
    char nom[15];
    char couleur;
    int arrivee; // Variable booléenne indiquant si le pion a atteint sa destination
    int deja_deplace; // Variable booléenne indiquant si le pion a déjà été déplacé dans le tour en cours
    t_tresor tresors[12];// tableau stockant tous les tresors du joueur, les cases en trop sont des '0' et on en met 12 car on a au max 12 tresors par joueur
    int num_tresor_pion;//numéro du trésor en cours de recherche
}t_pion;

#endif //LABYRINTHE_TRESORS_H
