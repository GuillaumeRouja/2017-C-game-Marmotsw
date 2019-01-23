/*
game.c

------

Guillaume Rouja for CS50 project

Started 11/09/2017
Completed 08/12/2017


Description : functions of the game
*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <stdbool.h>


#include "constants.h"
#include "game.h"

void play(SDL_Surface* screen, bool choice, Mix_Music* music)
{

    SDL_Surface *marmotte[4] = {NULL},*sMarmotte[4] = {NULL}, *eagle[4] = {NULL}; //Declaration of variables
    SDL_Surface *wall = NULL,*door = NULL,*shoes = NULL, *slippers = NULL,*obstacle = NULL, *trap=NULL, *superMarmotte=NULL, *currentMarmotte = NULL, *currentEagle = NULL;
    SDL_Surface *info = NULL, *hourglass =NULL;
    SDL_Rect position = {NULL}, positionPlayer = {NULL},positionEagle = {NULL};
    SDL_Event event;

    int mainLoop = 1, i = 0, j = 0;
    int map[NB_BLOCS_WIDTH][NB_BLOCS_HEIGHT] = {0};
    int previousTimeEagle = 2000, currentTimeEagle = 0;
    int previousTimeClock = 2000, currentTimeClock = 0;
    int result = GAMEON;
    int lives = LIVES;
    int levelNumber = 1;
    int speed = NORMAL;
    int timer = SETTIME;

    bool superM = false;
    bool push = false;

    Mix_AllocateChannels(3); //channel allocation for sound effects

    Mix_Chunk *sound;
    Mix_Chunk *stime;

    marmotte[UP] = IMG_Load("pic/marmup.png"); //Data loading
    marmotte[DOWN] = IMG_Load("pic/marmdown.png");
    marmotte[LEFT] = IMG_Load("pic/marmleft.png");
    marmotte[RIGHT] = IMG_Load("pic/marmright.png");
    sMarmotte[UP] = IMG_Load("pic/smarmup.png");
    sMarmotte[DOWN] = IMG_Load("pic/smarmdown.png");
    sMarmotte[LEFT] = IMG_Load("pic/smarmleft.png");
    sMarmotte[RIGHT] = IMG_Load("pic/smarmright.png");
    eagle [UP] = IMG_Load("pic/eagleup.png");
    eagle [DOWN] = IMG_Load("pic/eagledown.png");
    eagle [LEFT] = IMG_Load("pic/eagleleft.png");
    eagle [RIGHT] = IMG_Load("pic/eagleright.png");

    wall = IMG_Load("pic/freebricks1.jpg");
    door = IMG_Load("pic/freedoor.png");
    shoes = IMG_Load("pic/freeshoes.png");
    slippers = IMG_Load("pic/freeslippers.png");
    obstacle = IMG_Load("pic/freebed.png");
    trap = IMG_Load ("pic/freetrap.png");
    superMarmotte = IMG_Load("pic/freespower.png");
    info = IMG_Load ("pic/info.png");
    hourglass = IMG_Load ("pic/hourglass.png");

    currentMarmotte = marmotte[DOWN]; // set the position of Marmot & eagle
    currentEagle = eagle[DOWN];

    SDL_SetColorKey(eagle[UP], SDL_SRCCOLORKEY, SDL_MapRGB(eagle[UP]->format, 255, 255, 255)); //Eagle is flying over the surfaces so it has to be set transparent
    SDL_SetColorKey(eagle[DOWN], SDL_SRCCOLORKEY, SDL_MapRGB(eagle[DOWN]->format, 255, 255, 255));
    SDL_SetColorKey(eagle[LEFT], SDL_SRCCOLORKEY, SDL_MapRGB(eagle[LEFT]->format, 255, 255, 255));
    SDL_SetColorKey(eagle[RIGHT], SDL_SRCCOLORKEY, SDL_MapRGB(eagle[UP]->format, 255, 255, 255));

    if (choice == STORY)
        screen = SDL_SetVideoMode(WINDOW_WIDTH+INFO_COLUMN, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF); //Screen is extended to show info column

    if (!loadLevels(map,levelNumber,choice))//load the level
         exit(EXIT_FAILURE);

    for (i = 0 ; i < NB_BLOCS_WIDTH ; i++)//find the initial positions of Marmot & Eagle
    {
        for (j = 0 ; j < NB_BLOCS_HEIGHT ; j++)
        {
            if (map[i][j] == MARMOTTE)
            {
                positionPlayer.x = i;
                positionPlayer.y = j;
                map[i][j] = VOID;
            }
            if (map[i][j] == EAGLE)
            {
               positionEagle.x = i;
               positionEagle.y = j;
               map[i][j] = VOID;
            }
        }
    }

    SDL_EnableKeyRepeat(NORMAL, NORMAL);// Allows to keep pressing a key to move the marmot

    while (mainLoop) // main loop
    {
        if(SDL_PollEvent(&event))
        {
            switch(event.type)
            {
                case SDL_QUIT:
                    screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                    mainLoop = 0;
                    break;
                case SDL_KEYDOWN:
                    switch(event.key.keysym.sym)
                    {
                        case SDLK_ESCAPE: //quit the level and set the screen to its initial size
                            screen = SDL_SetVideoMode(WINDOW_WIDTH, WINDOW_HEIGHT, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
                            mainLoop = 0;
                            break;
                        case SDLK_UP:
                            if  (map[positionPlayer.x][positionPlayer.y-1] == DOOR)
                                currentMarmotte = marmotte[UP]; // aspect of Marmot is back to default at the end of the level
                            if  (map[positionPlayer.x][positionPlayer.y-1]== OBSTACLE)
                            {
                                if (!superM)
                                {
                                    push = true; // this tracker allows to introduce an extra difficulty when pushing a bed in the move function
                                    sound = Mix_LoadWAV("music/movebed.wav"); //Selection of the sound level for moving the bed
                                    Mix_PlayChannel(1, sound, 0); //play sound effect once
                                }
                                else
                                {
                                    sound = Mix_LoadWAV("music/smovebed3.wav"); //another sound is selected for superMarmot
                                    Mix_PlayChannel(1, sound, 0);
                                }
                            }
                            else
                                push = false;
                            if  (map[positionPlayer.x][positionPlayer.y-1] == SUPERM || superM == true)
                                currentMarmotte = sMarmotte[UP]; // aspect of Marmot adapts to superMarmot powers
                            else if (superM == false)
                                currentMarmotte = marmotte[UP]; // aspect of Marmot is adapted to the direction
                            moveMarmotte(push,speed,map, &positionPlayer, UP); //Finally Marmot is allowed to move using the moveMarmotte function
                            break;
                        case SDLK_DOWN:
                            if  (map[positionPlayer.x][positionPlayer.y+1] == DOOR)
                                currentMarmotte = marmotte[DOWN];
                            if  (map[positionPlayer.x][positionPlayer.y+1] == OBSTACLE)
                            {
                                if (!superM)
                                {
                                    push = true;
                                    sound = Mix_LoadWAV("music/movebed.wav");
                                    Mix_PlayChannel(1, sound, 0);
                                }
                                else
                                {
                                    sound = Mix_LoadWAV("music/smovebed3.wav");
                                    Mix_PlayChannel(1, sound, 0);
                                }
                            }
                            else
                                push = false;
                            if  (map[positionPlayer.x][positionPlayer.y+1] == SUPERM || superM == true)
                                currentMarmotte = sMarmotte[DOWN];
                            else if (superM == false)
                                currentMarmotte = marmotte[DOWN];
                            moveMarmotte(push,speed,map, &positionPlayer, DOWN);
                            break;
                        case SDLK_RIGHT:
                            if  (map[positionPlayer.x+1][positionPlayer.y] == DOOR)
                                currentMarmotte = marmotte[RIGHT];
                            if  (map[positionPlayer.x+1][positionPlayer.y] == OBSTACLE)
                            {
                                if (!superM)
                                {
                                    push = true;
                                    sound = Mix_LoadWAV("music/movebed.wav");
                                    Mix_PlayChannel(1, sound, 0);
                                }
                                else
                                {
                                    sound = Mix_LoadWAV("music/smovebed3.wav");
                                    Mix_PlayChannel(1, sound, 0);
                                }
                            }
                            else
                                push = false;
                            if  (map[positionPlayer.x+1][positionPlayer.y] == SUPERM || superM == true)
                                currentMarmotte = sMarmotte[RIGHT];
                            else if (superM == false)
                                currentMarmotte = marmotte[RIGHT];
                            moveMarmotte(push,speed,map, &positionPlayer, RIGHT);
                            break;
                        case SDLK_LEFT:
                            if  (map[positionPlayer.x-1][positionPlayer.y] == DOOR)
                                currentMarmotte = marmotte[LEFT];
                            if  (map[positionPlayer.x-1][positionPlayer.y] == OBSTACLE)
                            {
                                if (!superM)
                                {
                                    push = true;
                                    sound = Mix_LoadWAV("music/movebed.wav");
                                    Mix_PlayChannel(1, sound, 0);
                                }
                                else
                                {
                                    sound = Mix_LoadWAV("music/smovebed3.wav");
                                    Mix_PlayChannel(1, sound, 0);
                                }
                            }
                            else
                                push = false;
                            if  (map[positionPlayer.x-1][positionPlayer.y] == SUPERM || superM == true)
                                currentMarmotte = sMarmotte[LEFT];
                            else if (superM == false)
                                currentMarmotte = marmotte[LEFT];
                            moveMarmotte(push,speed,map, &positionPlayer, LEFT);
                            break;
                    }
                    break;
            }
        }
        currentTimeEagle = SDL_GetTicks();

        if (currentTimeEagle - previousTimeEagle > SPEED) //allows to move Eagle at a set speed
        {
            position.x = positionEagle.x;
            position.y = positionEagle.y;

            moveEagle(map, &positionEagle, &positionPlayer); //dedicated function to move Eagle

            if (position.x > positionEagle.x) // aspect of Eagle is adapted to the direction
                currentEagle = eagle[LEFT];
            if (position.x < positionEagle.x)
                currentEagle = eagle[RIGHT];
            if (position.y > positionEagle.y)
                currentEagle = eagle[UP];
            if (position.y < positionEagle.y)
                currentEagle = eagle[DOWN];

            previousTimeEagle = currentTimeEagle;
        }

        if (map[positionPlayer.x][positionPlayer.y] == SHOES) //speed increases with shoes
        {
            if (superM) //Super Marmot is not affected by this item
            {
                sound = Mix_LoadWAV("music/magicwand.wav");
                Mix_PlayChannel(1, sound, 0);
                map[positionPlayer.x][positionPlayer.y] = VOID;
            }
            else
            {
                sound = Mix_LoadWAV("music/superfast.wav"); // dedicated sound
                Mix_PlayChannel(1, sound, 0);
                speed = FAST; // speed set to fast
                SDL_EnableKeyRepeat(FAST, FAST); //Key repetition also set to fast
                map[positionPlayer.x][positionPlayer.y] = VOID; //empty space once the object is collected
            }
        }

        if (map[positionPlayer.x][positionPlayer.y] == SLIPPERS) //Slippers decrease speed
        {
            if (superM)
            {
                sound = Mix_LoadWAV("music/magicwand.wav");
                Mix_PlayChannel(1, sound, 0);
                map[positionPlayer.x][positionPlayer.y] = VOID;
            }
            else
            {
               sound = Mix_LoadWAV("music/slippers.wav");
               Mix_PlayChannel(1, sound, 0);
               speed = SLOW;
               SDL_EnableKeyRepeat(SLOW, SLOW);
               map[positionPlayer.x][positionPlayer.y] = VOID;
            }
        }

        if (map[positionPlayer.x][positionPlayer.y] == SUPERM) //SuperMarmot is super fast
        {
            sound = Mix_LoadWAV("music/magicwand.wav");
            Mix_PlayChannel(1, sound, 0);
            speed = VERYFAST;
            superM = true;
            SDL_EnableKeyRepeat(VERYFAST, VERYFAST);
            map[positionPlayer.x][positionPlayer.y] = VOID;
        }

        if  (map[positionPlayer.x][positionPlayer.y] == TRAP)
        {
            if (superM)
            {
                sound = Mix_LoadWAV("music/strap1.wav");
                Mix_PlayChannel(1, sound, 0);
                map[positionPlayer.x][positionPlayer.y] = VOID;
            }
            else
            {
                sound = Mix_LoadWAV("music/trap.wav");
                Mix_PlayChannel(1, sound, 0);
                result = LOSTRAP; // Lost status when falling in a trap
            }
        }

        if (positionPlayer.x == positionEagle.x & positionPlayer.y == positionEagle.y)
        {
            sound = Mix_LoadWAV("music/caught3.wav");
            Mix_PlayChannel(1, sound, 0);
            result = LOSTEAGLE; // Another lost status when being eaten
        }

        if (map[positionPlayer.x][positionPlayer.y] == DOOR)
        {
            sound = Mix_LoadWAV("music/door2.wav");
            Mix_PlayChannel(1, sound, 0);
            Mix_HaltChannel(2); // Timer is stopped
            result = WON; //Game is won when Marmot reaches the door
        }

        if (result !=GAMEON)//What happens when the game is won or lost?
        {
            SDL_EnableKeyRepeat(NORMAL, NORMAL); //Most variables are set to default
            superM = false, speed = NORMAL;
            previousTimeEagle = 2000, currentTimeEagle = 0, previousTimeClock = 2000, currentTimeClock = 0;
            if (currentMarmotte = sMarmotte[UP])
                currentMarmotte = marmotte[UP];

            if (choice == DEMO)
            {
                Mix_PauseMusic();
                texts(screen,result,choice); //text function displays the result
                mainLoop = 0;
            }
            else
            {
                if (result == LOSTIME|| result == LOSTEAGLE|| result == LOSTRAP)
                {
                    Mix_HaltChannel(2);// Timer is stopped
                    lives = lives-1; // Losing removes 1 life
                    texts(screen,result,choice);
                    if (lives <0)
                    {
                        result = FINALLOST;
                        Mix_PauseMusic();
                        sound = Mix_LoadWAV("music/lose.wav");
                        Mix_PlayChannel(1, sound, 0);
                        texts(screen,result,choice);
                        mainLoop = 0;
                    }
                }
                if (result == WON)
                {
                   if (timer > SETTIME/2)
                        lives = lives+1; // life bonus if level finished early

                   levelNumber = levelNumber +1; //move to next level

                   if (levelNumber==5)
                   {
                       music= Mix_LoadMUS("music/in-search-of-asia.mp3"); //Music changes at certain levels
                       Mix_PlayMusic(music, -1);
                   }
                   if (levelNumber==8)
                   {
                       music= Mix_LoadMUS("music/advanced.mp3");
                       Mix_PlayMusic(music, -1);
                   }
                   if (levelNumber==11)
                   {
                       music= Mix_LoadMUS("music/end.mp3");
                       Mix_PlayMusic(music, -1);
                   }
                   if (levelNumber > NBLEVELS) // Game is finished and credits are displayed
                   {
                       result = FINALWON;
                       music= Mix_LoadMUS("music/endstory.mp3");
                       Mix_PlayMusic(music, -1);
                       texts(screen,result,choice);
                       result = THANKS;
                       texts(screen,result,choice);
                       levelNumber=1;
                       mainLoop = 0;
                   }
                }
                timer = SETTIME;
                result = GAMEON;

                if (!loadLevels(map,levelNumber,choice))//load level
                    exit(EXIT_FAILURE);

                for (i = 0 ; i < NB_BLOCS_WIDTH ; i++)// find the initial positions of Marmot & Eagle
                {
                    for (j = 0 ; j < NB_BLOCS_HEIGHT ; j++)
                    {
                        if (map[i][j] == MARMOTTE)
                        {
                            positionPlayer.x = i;
                            positionPlayer.y = j;
                            map[i][j] = VOID;
                        }
                        if (map[i][j] == EAGLE)
                        {
                            positionEagle.x = i;
                            positionEagle.y = j;
                            map[i][j] = VOID;
                        }
                    }
                }
            }
        }

        SDL_FillRect(screen, NULL, SDL_MapRGB(screen->format, 255, 255, 255));

        //Display some info with the help of dedicated functions placed in info.c
        position.x = WINDOW_WIDTH;
        position.y = 0;
        SDL_BlitSurface(info, NULL, screen, &position);// display info column

        position.x = WINDOW_WIDTH + 55;
        position.y = 60;
        SDL_BlitSurface(levelnb(levelNumber), NULL, screen, &position);//level number in info column

        position.x = WINDOW_WIDTH + 40;
        position.y = 190;
        SDL_BlitSurface(marmotte[RIGHT], NULL, screen, &position);
        position.x = WINDOW_WIDTH + 90;
        position.y = 195;
        SDL_BlitSurface(livesnb(lives), NULL, screen, &position);//lives

        position.x = WINDOW_WIDTH + 85;
        position.y = 330;
        if (superM)
            SDL_BlitSurface(superMarmotte, NULL, screen, &position);
        if (speed==SLOW)
            SDL_BlitSurface(slippers, NULL, screen, &position);
        if (speed==FAST)
            SDL_BlitSurface(shoes, NULL, screen, &position);//current item

        position.x = WINDOW_WIDTH + 58;
        position.y = 450;
        currentTimeClock = SDL_GetTicks();
        SDL_BlitSurface(hourglass, NULL, screen, &position);
        position.x = WINDOW_WIDTH + 102;
        position.y = 457;
        SDL_BlitSurface(Timer(timer), NULL, screen, &position); //timer
        if (((currentTimeClock - previousTimeClock > 1000))&&(choice==STORY)) //time,music,countdown all connected in the below
        {
            timer-=1000;
            if ((levelNumber ==1)&&(timer>SETTIME-1200))
            {
                music = Mix_LoadMUS("music/begin.mp3"); //Start the music when timer starts
                Mix_PlayMusic(music, -1);
            }
            if (timer<5500)
            {
                if (timer>4400)
                {
                    stime = Mix_LoadWAV("music/countdown.wav");//Countdown starts approx. 5 sec before the end.
                    Mix_PlayChannel(2, stime, 0); //This sound effect uses a different channel in order not to hit another sound effect
                }
                if (timer <0 && choice == STORY)
                {
                    Mix_HaltChannel(-1);
                    result = LOSTIME; // time's up!
                }
            }
            previousTimeClock = currentTimeClock;
        }

        for (i = 0 ; i < NB_BLOCS_WIDTH ; i++)
        {
            for (j = 0 ; j < NB_BLOCS_HEIGHT ; j++)
            {
                position.x = i * SIZE_BLOC;
                position.y = j * SIZE_BLOC;
                switch(map[i][j]) //the objects are placed on the screen
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
                }
            }
        }

        position.x = positionPlayer.x * SIZE_BLOC;
        position.y = positionPlayer.y * SIZE_BLOC;
        SDL_BlitSurface(currentMarmotte, NULL, screen, &position); // Marmot is placed on the screen

        position.x = positionEagle.x * SIZE_BLOC;
        position.y = positionEagle.y * SIZE_BLOC;
        SDL_BlitSurface(currentEagle, NULL, screen, &position); //Eagle is placed on the screen

        SDL_Flip(screen);

    } // End of main loop

    SDL_EnableKeyRepeat(0, 0); // key repeat is switched off

    SDL_FreeSurface(wall); // loaded surfaces are set free
    SDL_FreeSurface(door);
    SDL_FreeSurface(shoes);
    SDL_FreeSurface(slippers);
    SDL_FreeSurface(obstacle);
    SDL_FreeSurface(trap);
    SDL_FreeSurface(superMarmotte);
    SDL_FreeSurface(currentMarmotte);
    SDL_FreeSurface(currentEagle);
    SDL_FreeSurface(hourglass);
    SDL_FreeSurface(info);

    SDL_FreeSurface(levelnb(levelNumber)); //text is set free
    SDL_FreeSurface(livesnb(lives));
    SDL_FreeSurface(Timer(timer));

    for (i = 0 ; i < 4 ; i++) // Loaded characters are set free
        SDL_FreeSurface(marmotte[i]);
    for (i = 0 ; i < 4 ; i++)
        SDL_FreeSurface(sMarmotte[i]);
    for (i = 0 ; i < 4 ; i++)
        SDL_FreeSurface(eagle[i]);

    Mix_FreeChunk(sound);//Last loaded sound effect is set free
    Mix_FreeChunk(stime);
    Mix_FreeMusic(music);//music is set free
}










