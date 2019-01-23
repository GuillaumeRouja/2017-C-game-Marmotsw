/*
info.c
--------------

Guillaume Rouja for CS50 project

Started 11/09/2017
Completed 08/12/2017

Description : Functions to handle the info window on the game screen
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_ttf.h>

#include "constants.h"
#include "screens.h"

SDL_Surface* levelnb(int levelNumber)
{
    SDL_Surface *text = NULL;
    char message[10] = {0};
    TTF_Font *police = NULL; //police choice
    SDL_Color blackColor = {0, 0, 0}; //character color choice

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Error in starting TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE); //check for error
    }

    police = TTF_OpenFont("calibri.ttf", 30); // load the police

    sprintf(message,"Level %d ",levelNumber); // Show level number
    text = TTF_RenderText_Blended(police, message, blackColor);

    TTF_CloseFont(police);
    TTF_Quit();

    return text;
}

SDL_Surface* livesnb(int lives)
{
    SDL_Surface *text = NULL;
    char message[12] = {0};
    TTF_Font *police = NULL;
    SDL_Color blackColor = {0, 0, 0};

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Error in starting TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    police = TTF_OpenFont("calibri.ttf", 30);

    sprintf(message,"x  %d",lives); //Show number of lives
    text = TTF_RenderText_Blended(police, message, blackColor);

    TTF_CloseFont(police);
    TTF_Quit();

    return text;
}

SDL_Surface* Timer(int timer)
{
    SDL_Surface *text = NULL;
    char message[20] = {0};
    TTF_Font *police = NULL;
    SDL_Color blackColor = {0, 0, 0};

    if(TTF_Init() == -1)
    {
        fprintf(stderr, "Error in starting TTF_Init : %s\n", TTF_GetError());
        exit(EXIT_FAILURE);
    }

    police = TTF_OpenFont("calibri.ttf", 30);

    sprintf(message,": %d",timer/1000); //Show timer
    text = TTF_RenderText_Solid(police, message, blackColor);

    TTF_CloseFont(police);
    TTF_Quit();

    return text;
}


