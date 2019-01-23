/*
main.c

------

Guillaume Rouja for CS50 project

Started 11/09/2017
Completed 08/12/2017

Description : menu of the game
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>

#include "constants.h"
#include "game.h"
#include "editor.h"

int main(int argc, char *argv[])
{
    SDL_Surface *screen = NULL, *menu = NULL; //Declaration of variables
    SDL_Rect positionMenu;
    SDL_Event event;
    bool choice = DEMO;
    int result = START;
    int mainLoop = 1;
    Mix_Music *music;


    if (SDL_Init(SDL_INIT_VIDEO) == -1) // start video, check for error
    {
        fprintf(stderr, "SDL start error");
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetIcon(IMG_Load("pic/marmdown.png"), NULL); // load icon

    screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE|SDL_DOUBLEBUF); // load screen according to defined constants
    if (screen == NULL) // check for error
    {
        fprintf(stderr, "can't load video: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_WM_SetCaption("Marmot Sleep-walker", NULL); // set caption

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == -1) //start audio
        printf("%s", Mix_GetError());

    menu = IMG_Load("pic/newtitlescreen.png"); // load menu picture

    Mix_VolumeMusic(MIX_MAX_VOLUME/2); // reduce music volume for sound effects to stand out

    music = Mix_LoadMUS("music/african_fun.mp3"); //Music is loaded

    Mix_PlayMusic(music, -1); //Music is played and repeated

    positionMenu.x = 0; // menu position is set
    positionMenu.y = 0;

    while (mainLoop) // main game options loop
    {
        SDL_WaitEvent(&event);
        switch(event.type)
        {
            case SDL_QUIT:
                mainLoop = 0; //exit game
                break;
            case SDL_KEYDOWN:
                switch(event.key.keysym.sym)
                {
                    case SDLK_ESCAPE: // exit game
                        mainLoop = 0;
                        break;
                    case SDLK_KP1: // guide
                        choice = DEMO;
                        result = GUIDE; // set result variable to guide and pass it to text display function
                        texts(screen,result,choice); //show guide text using dedicated text function and result variable
                        break;
                    case SDLK_KP2: // Demo
                        choice = DEMO;
                        play(screen,choice,music); //start play function in demo mode
                        music = Mix_LoadMUS("music/african_fun.mp3"); //change music
                        Mix_PlayMusic(music, -1);
                        break;
                    case SDLK_KP3: // Story mode
                        choice = STORY;
                        result = START;
                        texts(screen,result,choice);
                        play(screen,choice,music);
                        music= Mix_LoadMUS("music/african_fun.mp3"); //change music
                        Mix_PlayMusic(music, -1);
                        break;
                    case SDLK_KP4: // level editor
                        choice = DEMO;
                        editor(screen,choice);
                        break;
                    case SDLK_KP5: // Demo mode
                        choice = DEMO;
                        result = HINTS;
                        texts(screen,result,choice);
                        break;
                    case SDLK_1: //
                        choice = DEMO;
                        result = GUIDE;
                        texts(screen,result,choice);
                        break;
                    case SDLK_2: // Demo mode
                        choice = DEMO;
                        play(screen,choice,music);
                        music= Mix_LoadMUS("music/african_fun.mp3"); //Music is loaded
                        Mix_PlayMusic(music, -1);
                        break;
                    case SDLK_3: // Story mode
                        choice = STORY;
                        result = START;
                        texts(screen,result,choice);
                        play(screen,choice,music);
                        music= Mix_LoadMUS("music/african_fun.mp3"); //Music is loaded
                        Mix_PlayMusic(music, -1);
                        break;
                    case SDLK_4: // level editor
                        choice = DEMO;
                        editor(screen,choice);
                        break;
                    case SDLK_5: // Demo mode
                        choice = DEMO;
                        result = HINTS;
                        texts(screen,result,choice);
                        break;
                }
                break;
        }
        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 0, 0, 0)); // clear screen
        SDL_BlitSurface(menu, NULL, screen, &positionMenu); // paste menu
        SDL_Flip(screen); // show menu
    }
    SDL_FreeSurface(menu); // free memory

    Mix_FreeMusic(music); // free music pointer
    Mix_CloseAudio(); //Music API is closed
    SDL_Quit();

    return EXIT_SUCCESS;
}







