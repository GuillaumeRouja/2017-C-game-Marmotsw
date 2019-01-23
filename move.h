/*
move.h
--------------

Guillaume Rouja for CS50 project

Started 11/09/2017
Completed 08/12/2017

Description : Prototypes for move.c
*/

#ifndef DEF_MOVE
#define DEF_MOVE

    void moveMarmotte(bool push,int speed,int map[][NB_BLOCS_HEIGHT], SDL_Rect *pos, int direction);
    void moveEagle(int map[][NB_BLOCS_HEIGHT], SDL_Rect *posE, SDL_Rect *posM);
    void moveObstacles(int *square1, int *square2);

#endif

