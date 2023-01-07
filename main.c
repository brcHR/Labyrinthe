#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "plateau.h"
#include "Deroulement.h"
#include "tests.h"

int main(int argc, char **argv)
{
    FILE * fichierlog = NULL;

    fichierlog = fopen("log.txt","a");
    fprintf(fichierlog,"DEBUT D'ENREGISTREMENT\n");
    fflush(fichierlog);

    /*
     * Mettez les fonctions que vous voulez tester ici. Ne vous occupez pas des if.
     */
    //testDeroulement();
    //testMenu();
    //Menu();
    //testrecup_tresor(fichierlog);
    //testDistrib();
    //test_affichage();
    //deplacement_valide_test();
    //Ne vous occupez pas de ca.
    if(argc > 1){
        if(strcmp(argv[1],"-test") == 0){
            tests(fichierlog);
       }
        else if(strcmp(argv[1],"-testd") == 0){
            testd(fichierlog);
        }
        else if(strcmp(argv[1],"-testg") == 0){
            testg(fichierlog);
        }
        else if(strcmp(argv[1],"-jeu") == 0){
            Menu(fichierlog);
        }
    }
    fclose(fichierlog);
    return 0;
}
