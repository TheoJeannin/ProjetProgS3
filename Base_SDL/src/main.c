#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
int main(int argc, char *argv[])
    {
    SDL_Window* fenetre; // D�claration de la fen�tre
    SDL_Event evenements; // �v�nements li�s � la fen�tre

    bool terminer = false;
    if(SDL_Init(SDL_INIT_VIDEO) < 0) // Initialisation de la SDL
    {
        printf("Erreur d�initialisation de la SDL: %s",SDL_GetError());

        SDL_Quit();
        return EXIT_FAILURE;
    }
    // Cr�er la fen�tre
    fenetre = SDL_CreateWindow("Projet Base", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, 600, 600, SDL_WINDOW_RESIZABLE);
    if(fenetre == NULL) // En cas d�erreur
    {
        printf("Erreur de la creation d�une fenetre: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
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
                        case SDLK_ESCAPE:
                        case SDLK_q:
                        terminer = true;
                        break;
                    }
            }
    }
    // Quitter SDL
    SDL_DestroyWindow(fenetre);
    SDL_Quit();
    return 0;
}
