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
#define nbTilesText 3
#define playerSpeed 10
#define floorSize 10


struct entity {
    SDL_Texture* sprite;
    SDL_Rect physic;
};
typedef struct entity Entity;

typedef struct ennemie Ennemie;
struct ennemie_list {
    Ennemie* premier;
};
typedef struct ennemie_list Ennemie_List;

struct ennemie{
    Ennemie_List* suivant;
    int type;
    int health;
    int speed;
    int damage;
    Entity e;
};

struct player{
    SDL_Texture** sprites;
    SDL_Rect physic;
    int facing;
};
typedef struct player Player;

typedef struct room Room;
struct room {
    int id;
    int tiles[nbwTiles][nbhTiles];
    Room* north;
    Room* south;
    Room* east;
    Room* west;
};

struct floor{
    int id;
    Room* start;
    SDL_Texture** tiles_sprites;
};
typedef struct floor Floor;






#endif // STRUCTURES_H_INCLUDED
