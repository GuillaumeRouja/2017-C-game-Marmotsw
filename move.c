/*
move.c
--------------

Guillaume Rouja for CS50 project

Started 11/09/2017
Completed 08/12/2017

Description : Handle the movements
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>

#include "constants.h"

void moveMarmotte(bool push,int speed,int map[][NB_BLOCS_HEIGHT], SDL_Rect *pos, int direction) //handle Marmot's movements in line with collected item
{
    if (speed == SLOW) //handle the speed
        SDL_Delay(SLOW);
    if (push)
        SDL_Delay(VERYSLOW);

    switch(direction) //handle the directions
    {
        case UP:
            if (pos->y - 1 < 0) // cannot go beyond the window
                break;
            if (map[pos->x][pos->y-1] == WALL) // If there is a wall, Marmot stops. Similar logic is applied to other directions.
                break;
            if (map[pos->x][pos->y-1] == OBSTACLE &&
                (pos->y - 2 < 0 || map[pos->x][pos->y - 2] == WALL || map[pos->x][pos->y - 2] == OBSTACLE || map[pos->x][pos->y - 2] == DOOR))
                break;
            moveObstacles(&map[pos->x][pos->y-1], &map[pos->x][pos->y-2]); // call a small function to move the obstacle.
            pos->y--; // Move up.
            break;

        case DOWN:
            if (pos->y + 1 >= NB_BLOCS_HEIGHT)
                break;
            if (map[pos->x][pos->y+1] == WALL)
                break;
            if  (map[pos->x][pos->y + 1] == OBSTACLE &&
                (pos->y + 2 >= NB_BLOCS_HEIGHT || map[pos->x][pos->y + 2] == WALL || map[pos->x][pos->y + 2] == OBSTACLE|| map[pos->x][pos->y + 2] == DOOR))
                break;
            moveObstacles(&map[pos->x][pos->y+1], &map[pos->x][pos->y+2]);
            pos->y++;
            break;

        case LEFT:
            if (pos->x - 1 <0)
                break;
            if (map [pos->x-1][pos->y] == WALL)
                break;
            if (map[pos->x - 1][pos->y] == OBSTACLE &&
                (pos->x - 2 < 0 || map[pos->x - 2][pos->y] == WALL || map[pos->x - 2][pos->y] == OBSTACLE || map[pos->x-2][pos->y] == DOOR))
                break;
            moveObstacles(&map[pos->x-1][pos->y], &map[pos->x-2][pos->y]);
            pos->x--;
            break;

        case RIGHT:
            if (pos->x + 1 >= NB_BLOCS_WIDTH)
                break;
            if (map [pos->x+1][pos->y] == WALL)
                break;
            if  (map[pos->x + 1][pos->y] == OBSTACLE &&
                (pos->x + 2 >= NB_BLOCS_WIDTH || map[pos->x + 2][pos->y] == WALL ||map[pos->x + 2][pos->y] == OBSTACLE || map[pos->x+2][pos->y] == DOOR))
                break;
            moveObstacles(&map[pos->x+1][pos->y], &map[pos->x+2][pos->y]);
            pos->x++;
            break;
    }
}

void moveEagle(int map[][NB_BLOCS_HEIGHT], SDL_Rect *posE, SDL_Rect *posM)//Handle automatic Eagle's movements
{
    if (abs(posE->y - posM->y) >= abs(posE->x - posM->x))    //choice between horizontal or vertical direction based on position of Marmot
    {
       if (posE->y >= posM->y) //once vertical/horizontal choice made -> choice between up versus down or left versus right
           posE->y--;
       else
           posE->y++;
    }
    else
    {
       if (posE->x >= posM->x)
          posE->x--;
       else
          posE->x++;
    }
}

void moveObstacles(int *square1, int *square2) // simple function to move obstacles
{
    if (*square1 == OBSTACLE)
    {
        *square2 = OBSTACLE;
        *square1 = VOID;
    }
}
