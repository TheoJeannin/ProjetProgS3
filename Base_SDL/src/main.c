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
    srand(time(NULL));
    Floor* Etage=createEmptyFloor(screen,1);
    statFloorHolder Stats;
    Stats.direction='S';
    Stats.pEast=80;
    Stats.pWest=10;
    Stats.pSouth=80;
    Stats.pNorth=0;
    Stats.pEmb=40;
    Room* Salle = createFloor(0,NULL,NULL,NULL,NULL,Stats,8,2,2);
    Etage->start=Salle;
    Player* player = createPlayer(screen,0,window_width/2,44,70);
    Ennemie_List* ennemies = createList_Ennemie();
    Salle->ennemies=ennemies;
    ajouterList_Ennemie(ennemies,1,2,2,0,1,200,200,50,50,"ressources/images/bat.png",screen);
    //ajouterList_Ennemie(ennemies,0,10,10,5,200,200,50,50,"ressources/images/bat.png",screen);
    //ajouterList_Ennemie(ennemies,0,10,10,5,200,100,50,50,"ressources/images/bat.png",screen);
    //ajouterList_Ennemie(ennemies,0,10,10,5,200,100,30,20,"ressources/images/arrow.png",screen);
    // Boucle principale
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
                            moveEntity(&(player->physic),Salle->tiles,0,-playerSpeed);
                            player->facing=4;
                        break;
                        case SDLK_q:
                            moveEntity(&(player->physic),Salle->tiles,-playerSpeed,0);
                            player->facing=2;
                        break;
                        case SDLK_s:
                            moveEntity(&(player->physic),Salle->tiles,0,playerSpeed);
                            player->facing=1;
                        break;
                        case SDLK_d:
                            moveEntity(&(player->physic),Salle->tiles,playerSpeed,0);
                            player->facing=3;
                        break;
                        case SDLK_ESCAPE:
                            terminer = true;
                        break;
                    }
            }
        if(((player->physic.x)>=window_width-(player->physic.w)-10)&&((player->facing)==3)){
            player->physic.x=3;
            Salle=Salle->west;
        }
        else if(((player->physic.x)<=0)&&((player->facing)==2)){
            player->physic.x=window_width-(player->physic.w)-10;
            Salle=Salle->east;
        }else if(((player->physic.y)>=window_height-(player->physic.h)-10)&&((player->facing)==1)){
            player->physic.y=0;
            Salle=Salle->south;
        }else if(((player->physic.y)<=0)&&((player->facing)==4)){
            player->physic.y=window_height-(player->physic.h)-10;
            Salle=Salle->north;
        }
        //moveMobTowardPlayer(player,Salle->ennemies->premier);
        walkTurnObstacle(Salle->tiles,Salle->ennemies->premier);
        printRoom(screen,Salle,Etage->tiles_sprites);
        printPlayer(screen,player);
        printEnnemies(screen,Salle->ennemies);
        SDL_RenderPresent(screen);
    }
    // Quitter SDL
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


