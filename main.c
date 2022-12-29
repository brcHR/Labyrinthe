#include <stdio.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "plateau.h"
#include "tests.h"

int main(int argc, char **argv)
{
    if(argc > 1){
        if(strcmp(argv[1],"-test") == 0){
            tests();
       }
    }

    return 0;
}
