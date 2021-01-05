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
    int time = SDL_GetTicks();
    int delta = 0;
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
    screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //Initialisation Jeu
    srand(5);
    const Uint8* numkeys = SDL_GetKeyboardState(NULL);
    Floor* Etage=createFloor(screen,1);
    Player* player = createPlayer(screen,70,window_width/2,44,70);
    //Boucle principale
    while(!terminer){
        time = SDL_GetTicks();
        SDL_PollEvent( &evenements );
        if(numkeys[SDL_SCANCODE_W]){
            moveEntity(&(player->physic),Etage->cRoom->tiles,0,-player->speed);
            player->facing=4;
        }
        else if(numkeys[SDL_SCANCODE_A]){
            moveEntity(&(player->physic),Etage->cRoom->tiles,-player->speed,0);
            player->facing=2;
        }
        else if(numkeys[SDL_SCANCODE_S]){
            moveEntity(&(player->physic),Etage->cRoom->tiles,0,player->speed);
            player->facing=1;
        }
        else if(numkeys[SDL_SCANCODE_D]){
            moveEntity(&(player->physic),Etage->cRoom->tiles,player->speed,0);
            player->facing=3;
        }
        if(numkeys[SDL_SCANCODE_SPACE]){
            if(player->attacking==0){
                player->attacking=20;
            }
        }
        if(numkeys[SDL_SCANCODE_ESCAPE]){
                            terminer = true;
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
        delta=(time-SDL_GetTicks());
        if(18>delta){
            SDL_Delay(18-(time-SDL_GetTicks()));
        }
        else{
            SDL_Delay(18);
        }
    }
    freeFloor(Etage);
    freePlayer(player);
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(screen);
    SDL_Quit();
    return 0;
}


