/*
Screens.c
--------------

Guillaume Rouja for CS50 project

Started 11/09/2017
Completed 08/12/2017

Description : Handle the screens appearing throughout the game
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <stdbool.h>

#include "constants.h"
#include "screens.h"

void texts(SDL_Surface *screen,int result,bool choice)
{
    SDL_Surface *text = NULL;
    SDL_Rect positionText;
    int mainloop =1;
    SDL_Event event;

    positionText.x=0;
    positionText.y=0;

    screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);

    switch(result)
    {
        case GUIDE:
            text=IMG_Load("pic/guide.jpg"); //For a given result a different screen is loaded
            break;
        case HINTS:
            text=IMG_Load("pic/hints.jpg");
            break;
        case START:
            text=IMG_Load("pic/introscreen.png");
            break;
        case LOSTEAGLE:
            text=IMG_Load("pic/claws.jpg");
            break;
        case LOSTIME:
            text=IMG_Load("pic/timesup.png");
            break;
        case LOSTRAP:
            text=IMG_Load("pic/trap.jpg");
            break;
        case WON:
            text=IMG_Load("pic/winscreen.jpg");
            break;
        case FINALWON:
            text=IMG_Load("pic/storyend.png");
            break;
        case THANKS:
            text=IMG_Load("pic/thanks.jpg");
            break;
        case FINALLOST:
            text=IMG_Load("pic/gameover.jpg");
            break;
    }

    while (mainloop)
    {
        if(SDL_PollEvent(&event))
        {
            switch (event.type)
            {
                case SDL_QUIT:
                    mainloop = 0;
                    break;
                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                            if (choice == STORY&& result != FINALLOST && result!= THANKS)
                                screen = SDL_SetVideoMode(WINDOW_WIDTH+INFO_COLUMN, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //in that case the game continues and info column has to be added back
                            mainloop = 0;
                            break;
                    }
                    break;
            }
        }
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));
        SDL_BlitSurface(text,NULL,screen,&positionText);
        SDL_Flip(screen);
    }
    SDL_FreeSurface(text);

    return EXIT_SUCCESS;
}

