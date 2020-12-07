#ifndef STRUCTURES_H_INCLUDED
#define STRUCTURES_H_INCLUDED
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#define window_width 600
#define window_height 600
#define nbwTiles 12
#define nbhTiles 8
#define nbTilesText 2
#define playerSpeed 10
struct entity {
    SDL_Texture* sprite;
    SDL_Rect physic;
};
typedef struct entity Entity;

struct floor {
    int id;
    int tiles[nbwTiles][nbhTiles];
    SDL_Texture** tiles_sprites;
};

typedef struct floor Floor;



#endif // STRUCTURES_H_INCLUDED
