#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "plateau.h"
#include "tests.h"

int main(int argc, char **argv)
{
    tests();
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
