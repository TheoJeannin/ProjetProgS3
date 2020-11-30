#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
SDL_Rect makeRect(int x, int y,int w,int h){
    SDL_Rect rRect;
    rRect.x=x;
    rRect.y=y;
    rRect.w=w;
    rRect.h=h;
    return rRect;
}

SDL_Texture* createImage(const char *cheminFichier,SDL_Renderer* screen){
    SDL_Surface* hSurface = IMG_Load(cheminFichier);
    return SDL_CreateTextureFromSurface(screen,hSurface);
}

SDL_Point getSizeTexture(SDL_Texture *texture){
    SDL_Point size;
    SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
    return size;
}
