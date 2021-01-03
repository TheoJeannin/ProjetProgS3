#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include "structures.h"
#include "logique.h"
#include "affichage.h"
#include <time.h>
int main(int argc, char *argv[])
    {
    SDL_Window* window;
    SDL_Event evenements;
    SDL_Renderer* screen;
    bool terminer = false;
    //Initialisation SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());

        SDL_Quit();
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("Projet Base", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_RESIZABLE);
    if(window == NULL)
    {
        printf("Erreur de la creation d’une window: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
    //Initialisation Jeu
    srand(8);
    Floor* Etage=createFloor(screen,1);
    Player* player = createPlayer(screen,0,window_width/2,44,70);
    //Boucle principale
    while(!terminer){
        SDL_PollEvent( &evenements );
            switch(evenements.type)
            {
                case SDL_QUIT:
                terminer = true;
                break;
                case SDL_KEYDOWN:
                    switch(evenements.key.keysym.sym)
                    {
                        case SDLK_z:
                            moveEntity(&(player->physic),Etage->cRoom->tiles,0,-playerSpeed);
                            player->facing=4;
                        break;
                        case SDLK_q:
                            moveEntity(&(player->physic),Etage->cRoom->tiles,-playerSpeed,0);
                            player->facing=2;
                        break;
                        case SDLK_s:
                            moveEntity(&(player->physic),Etage->cRoom->tiles,0,playerSpeed);
                            player->facing=1;
                        break;
                        case SDLK_d:
                            moveEntity(&(player->physic),Etage->cRoom->tiles,playerSpeed,0);
                            player->facing=3;
                        break;
                        case SDLK_ESCAPE:
                            terminer = true;
                        case SDLK_SPACE:
                        if(player->attacking==0){
                            player->attacking=30;
                        }
                        break;
                    }
            }
        travelRoom(player,Etage);
        if(player->attacking!=0){
            attackPlayer(player,Etage->cRoom->ennemies,Etage->cRoom->tiles);
        }
        ennemiesCollideWithPlayer(Etage->cRoom->ennemies,player);
        moveEnnemies(Etage->cRoom->ennemies,player,Etage->cRoom->tiles);
        printRoom(screen,Etage->cRoom,Etage->tiles_sprites);
        printPlayer(screen,player);
        printEnnemies(screen,Etage->cRoom->ennemies,Etage->entity_sprites);
        SDL_RenderPresent(screen);
    }
    freeFloor(Etage);
    freePlayer(player);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(screen);
    SDL_Quit();
    return 0;
}


