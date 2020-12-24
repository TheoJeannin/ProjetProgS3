#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include "structures.h"
#include "logique.h"
#include "affichage.h"

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
    screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //Initialisation Jeu
    Floor* Etage=createEmptyFloor(screen,1);
    Room* Salle = createRightRooms(1,NULL,NULL,NULL,NULL);
    Etage->start=Salle;
    Player* player = createPlayer(screen,100,400,50,50);
    Ennemie_List* ennemies = createList_Ennemie();
    ajouterList_Ennemie(ennemies,1,10,10,5,100,100,50,50,"ressources/images/bat.png",screen);
    ajouterList_Ennemie(ennemies,0,10,10,5,500,200,50,50,"ressources/images/bat.png",screen);
    ajouterList_Ennemie(ennemies,0,10,10,5,200,200,50,50,"ressources/images/bat.png",screen);
    ajouterList_Ennemie(ennemies,0,10,10,5,200,100,50,50,"ressources/images/bat.png",screen);
    ajouterList_Ennemie(ennemies,0,10,10,5,200,100,30,20,"ressources/images/arrow.png",screen);

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
        if((player->physic.x)>=window_width-(player->physic.w)-10){
            player->physic.x=1;
            Salle=Salle->west;
        }
        else if((player->physic.x)<=0){
            player->physic.x=window_width-(player->physic.w)-11;
            Salle=Salle->east;
        }
        printRoom(screen,Salle,Etage->tiles_sprites);
        printPlayer(screen,player);
        //printEntity(screen,&Ennemies->premier->e);
        printEnnemies(screen,ennemies);
        SDL_RenderPresent(screen);
    }
    // Quitter SDL
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


