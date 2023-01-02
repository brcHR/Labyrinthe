#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "plateau.h"
#include "tests.h"

int main(int argc, char **argv)
{
    /*
     * Mettez les fonctions que vous voulez tester ici. Ne vous occupez pas des if.
     */
    //testDeroulement();
    testMenu();

    //Ne vous occupez pas de ca.
    if(argc > 1){
        if(strcmp(argv[1],"-test") == 0){
            tests();
       }
        else if(strcmp(argv[1],"-testd") == 0){
            testd();
        }
        else if(strcmp(argv[1],"-testg") == 0){
            testg();
        }
    }
    return 0;
}
