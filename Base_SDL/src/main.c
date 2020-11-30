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
    Floor* Salle = createEmptyFloor(screen,1);
    Entity* Player = createEntity(screen,"ressources/images/base_sprite.png",50,50,50,50);
    printFloor(screen,Salle);
    printEntity(screen,Player);
    SDL_RenderPresent(screen);
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
                            moveEntity(Player,0,-playerSpeed);
                        break;
                        case SDLK_q:
                            moveEntity(Player,-playerSpeed,0);
                        break;
                        case SDLK_s:
                            moveEntity(Player,0,playerSpeed);
                        break;
                        case SDLK_d:
                            moveEntity(Player,playerSpeed,0);
                        break;
                        case SDLK_ESCAPE:
                            terminer = true;
                        break;
                    }
            }
        printFloor(screen,Salle);
        printEntity(screen,Player);
        SDL_RenderPresent(screen);
    }
    // Quitter SDL
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


