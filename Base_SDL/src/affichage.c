#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include "structures.h"
#include "extensionsdl.h"

void printEntity(SDL_Renderer* screen,Entity* entity){
    SDL_RenderCopy(screen,entity->sprite,NULL,&(entity->physic));
}

void printRoom(SDL_Renderer* screen,Room* room,SDL_Texture** tiles_sprites){
    int x = 0;
    int y = 0;
    SDL_Rect pos;
    for(x = 0;x<nbwTiles;x++){
        for(y = 0;y<nbhTiles;y++){

                    pos = makeRect(x*(window_width/nbwTiles),y*(window_height/nbhTiles),window_width/nbwTiles,window_height/nbhTiles);
                    SDL_RenderCopy(screen,tiles_sprites[room->tiles[x][y]],NULL,&pos);
        }
    }
}

void printEnnemies(SDL_Renderer* screen,Ennemie_List* list){
    Ennemie* cEnnemie=list->premier;
    while(cEnnemie!=NULL){
        printEntity(screen,&(cEnnemie->e));
        cEnnemie=cEnnemie->suivant;
    }
}

void printPlayer(SDL_Renderer* screen,Player* player){
    SDL_RenderCopy(screen,player->sprites[player->facing-1],NULL,&(player->physic));
}
