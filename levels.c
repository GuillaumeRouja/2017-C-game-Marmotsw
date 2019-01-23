/*
levels.c

------

Guillaume Rouja for CS50 project

Started 11/09/2017
Completed 08/12/2017


Description : Loading and saving functions
*/
#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constants.h"
#include "levels.h"
#include <stdbool.h>


int loadLevels(int level[][NB_BLOCS_HEIGHT], int levelNumber, bool choice)
{
    FILE* file = NULL;
    char lineFile[NB_BLOCS_WIDTH * NB_BLOCS_HEIGHT + 1] = {0};
    int i = 0, j = 0, k = 0;
    char *position = NULL;

    if (choice == DEMO)
    {
        file = fopen("level.lvl", "r"); // level.lvl contains a lign of numbers corresponding to the items to load
        if (file == NULL) //opening test
            return 0;
        fgets(lineFile, NB_BLOCS_WIDTH * NB_BLOCS_HEIGHT + 1, file); // reads the line in the file
    }
    else
    {
        file = fopen("storylevels.lvl", "r"); //same as level.lvl with this time a succession of lines
        if (file == NULL)
            return 0;
        for (k = 0; k < levelNumber; k++) // Read level 1, then level 2, etc.
        {
            position = strchr(lineFile, '\n'); // Each level is written on 1 line so we need to replace the "jump line" sign with a "finish character sequence" sign in order to make each level line readable.
            if (position != NULL)
                *position = '\0';
            fgets(lineFile, NB_BLOCS_WIDTH * NB_BLOCS_HEIGHT + 2, file);
        }
    }

    for (i = 0 ; i < NB_BLOCS_HEIGHT ; i++) // letters are converted into numbers to fill the map
    {
        for (j = 0 ; j < NB_BLOCS_WIDTH ; j++)
            {
            switch (lineFile[(i * NB_BLOCS_WIDTH) + j])
            {
                case '0':
                    level[j][i] = 0;
                    break;
                case '1':
                    level[j][i] = 1;
                    break;
                case '2':
                    level[j][i] = 2;
                    break;
                case '3':
                    level[j][i] = 3;
                    break;
                case '4':
                    level[j][i] = 4;
                    break;
                case '5':
                    level[j][i] = 5;
                    break;
                case '6':
                    level[j][i] = 6;
                    break;
                case '7':
                    level[j][i] = 7;
                    break;
                case '8':
                    level[j][i] = 8;
                    break;
                case '9':
                    level[j][i] = 9;
                    break;
            }
        }
    }
    fclose(file);
    return 1;
}

int saveLevels(int level[][NB_BLOCS_HEIGHT])
{
    FILE* file = NULL;
    int i = 0, j = 0;

    file = fopen ("level.lvl","w");
    if (file == NULL)
        return 0;

    for (i = 0 ; i < NB_BLOCS_HEIGHT ; i++)
    {
        for (j = 0 ; j < NB_BLOCS_WIDTH ; j++)
        {
            fprintf(file,"%d",level[j][i]); // A succession of numbers is written in the level.lvl file to materialize each item
        }
    }
    fclose(file);
    return 1;
}

