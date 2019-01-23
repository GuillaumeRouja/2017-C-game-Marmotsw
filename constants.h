/*
constants.h

------

Guillaume Rouja for CS50 project

Started 11/09/2017
Completed 08/12/2017


Description : constants of the game.
*/


#ifndef DEF_CONSTANTS
#define DEF_CONSTANTS


    #define SIZE_BLOC         40 // size of a bloc in pixels
    #define NB_BLOCS_WIDTH    21
    #define NB_BLOCS_INFO      5

    #define NB_BLOCS_HEIGHT   13

    #define WINDOW_WIDTH      SIZE_BLOC * NB_BLOCS_WIDTH

    #define INFO_COLUMN       SIZE_BLOC * NB_BLOCS_INFO

    #define WINDOW_HEIGHT     SIZE_BLOC * NB_BLOCS_HEIGHT

    #define NBLEVELS          12

    #define LIVES             3

    #define SPEED             600 //Eagle speed

    #define SETTIME           30000 // level time

    #define VERYFAST          50 //Marmot speed
    #define FAST              70
    #define NORMAL            100
    #define SLOW              200
    #define VERYSLOW          400


    enum {UP, DOWN, LEFT, RIGHT};

    enum {VOID, WALL, DOOR,SHOES,SLIPPERS,OBSTACLE,TRAP,SUPERM,MARMOTTE,EAGLE}; // to make the code easier to read

    enum {THANKS,HINTS,GUIDE,START,GAMEON,LOSTIME,LOSTRAP,LOSTEAGLE,FINALLOST, WON,FINALWON};

    enum {DEMO,STORY};

#endif
