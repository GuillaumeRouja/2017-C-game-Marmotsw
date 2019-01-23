/*
levels.h

------

Guillaume Rouja for CS50 project

Started 11/09/2017
Completed 08/12/2017

Description : prototypes for levels.c

*/
#ifndef DEF_LEVELS
#define DEF_LEVELS

#include <stdbool.h>

    int loadLevels(int level[][NB_BLOCS_HEIGHT], int levelNumber, bool choice);
    int saveLevels(int level[][NB_BLOCS_HEIGHT]);


#endif
