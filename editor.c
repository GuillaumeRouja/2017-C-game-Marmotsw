/*
editor.c

------

Guillaume Rouja for CS50 project

Started 11/09/2017
Completed 08/12/2017


Description : level editor
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>

#include "constants.h"
#include "editor.h"

#include <stdbool.h>

void editor(SDL_Surface* screen,bool choice)
{
    //declaration of variables and initializations similar to game.c
    SDL_Surface *wall = NULL,*door = NULL,*shoes= NULL,*slippers= NULL, *obstacle = NULL,*trap = NULL,*superMarmotte = NULL, *marmotte = NULL, *eagle = NULL;
    SDL_Rect position;
    SDL_Event event;
    int mainLoop = 1;
    int onleftclick = 0, onrightclick = 0;
    int currentObject = WALL;
    int i = 0, j = 0;
    int map[NB_BLOCS_WIDTH][NB_BLOCS_HEIGHT] = {0};

    wall = IMG_Load("pic/freebricks1.jpg");
    door = IMG_Load("pic/freedoor.png");
    marmotte = IMG_Load("pic/marmdown.png");
    eagle = IMG_Load("pic/eagledown.png");
    shoes = IMG_Load("pic/freeshoes.png");
    slippers = IMG_Load("pic/freeslippers.png");
    obstacle = IMG_Load("pic/freebed.png");
    trap = IMG_Load ("pic/freetrap.png");
    superMarmotte = IMG_Load("pic/freespower.png");

    screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    if (!loadLevels(map))
         exit(EXIT_FAILURE);

    while (mainLoop)
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                mainLoop = 0;
                break;
            case SDL_MOUSEBUTTONDOWN:
                if (event.button.button == SDL_BUTTON_LEFT)
                {
                    map[event.button.x / SIZE_BLOC][event.button.y / SIZE_BLOC] = currentObject; // current object is placed where we click
                    onleftclick = 1; // Remembers which button is pressed
                }
                else if (event.button.button == SDL_BUTTON_RIGHT)
                {
                    map[event.button.x / SIZE_BLOC][event.button.y / SIZE_BLOC] = VOID; // Right click to erase an object
                    onrightclick = 1;
                }
                break;
            case SDL_MOUSEBUTTONUP: // Boolean is set to 0 when button is released
                if (event.button.button == SDL_BUTTON_LEFT)
                    onleftclick = 0;
                else if (event.button.button == SDL_BUTTON_RIGHT)
                    onrightclick = 0;
                break;
            case SDL_MOUSEMOTION:
                if (onleftclick) // If the button is not released the selected object is copied without having to click again.
                {
                    map[event.button.x / SIZE_BLOC][event.button.y / SIZE_BLOC] = currentObject;
                }
                else if (onrightclick)
                {
                    map[event.button.x / SIZE_BLOC][event.button.y / SIZE_BLOC] = VOID;
                }
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym) // item selection
                {
                    case SDLK_ESCAPE:
                        mainLoop = 0;
                        break;
                    case SDLK_s:
                        saveLevels(map);
                        break;
                    case SDLK_c:
                        loadLevels(map);
                        break;
                    case SDLK_KP0:
                        currentObject = WALL;
                        break;
                    case SDLK_KP1:
                        currentObject = DOOR;
                        break;
                    case SDLK_KP2:
                        currentObject = SHOES;
                        break;
                    case SDLK_KP3:
                        currentObject = SLIPPERS;
                        break;
                    case SDLK_KP4:
                        currentObject = OBSTACLE;
                        break;
                    case SDLK_KP5:
                        currentObject = TRAP;
                        break;
                    case SDLK_KP6:
                        currentObject = SUPERM;
                        break;
                    case SDLK_KP7:
                        currentObject = MARMOTTE;
                        break;
                    case SDLK_KP8:
                        currentObject = EAGLE;
                        break;
                    case SDLK_0:
                        currentObject = WALL;
                        break;
                    case SDLK_1:
                        currentObject = DOOR;
                        break;
                    case SDLK_2:
                        currentObject = SHOES;
                        break;
                    case SDLK_3:
                        currentObject = SLIPPERS;
                        break;
                    case SDLK_4:
                        currentObject = OBSTACLE;
                        break;
                    case SDLK_5:
                        currentObject = TRAP;
                        break;
                    case SDLK_6:
                        currentObject = SUPERM;
                        break;
                    case SDLK_7:
                        currentObject = MARMOTTE;
                        break;
                    case SDLK_8:
                        currentObject = EAGLE;
                        break;
                }
                break;
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

        for (i = 0 ; i < NB_BLOCS_WIDTH; i++) // items are placed on the map
        {
            for (j = 0 ; j < NB_BLOCS_HEIGHT ; j++)
            {
                position.x = i * SIZE_BLOC;
                position.y = j * SIZE_BLOC;
                switch(map[i][j])
                {
                    case WALL:
                        SDL_BlitSurface(wall, NULL, screen, &position);
                        break;
                    case DOOR:
                        SDL_BlitSurface(door, NULL, screen, &position);
                        break;
                    case SHOES:
                        SDL_BlitSurface(shoes, NULL, screen, &position);
                        break;
                    case SLIPPERS:
                        SDL_BlitSurface(slippers, NULL, screen, &position);
                        break;
                    case OBSTACLE:
                        SDL_BlitSurface(obstacle, NULL, screen, &position);
                        break;
                    case TRAP:
                        SDL_BlitSurface(trap, NULL, screen, &position);
                        break;
                    case SUPERM:
                        SDL_BlitSurface(superMarmotte, NULL, screen, &position);
                        break;
                    case MARMOTTE:
                        SDL_BlitSurface(marmotte, NULL, screen, &position);
                        break;
                    case EAGLE:
                        SDL_BlitSurface(eagle, NULL, screen, &position);
                        break;
                }
            }
        }
        SDL_Flip(screen);
    }
    //Memory is set free
    SDL_FreeSurface(wall);
    SDL_FreeSurface(door);
    SDL_FreeSurface(shoes);
    SDL_FreeSurface(slippers);
    SDL_FreeSurface(obstacle);
    SDL_FreeSurface(trap);
    SDL_FreeSurface(superMarmotte);
    SDL_FreeSurface(marmotte);
    SDL_FreeSurface(eagle);

}



