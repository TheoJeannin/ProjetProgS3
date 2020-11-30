#include "structures.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include "extensionsdl.h"
Entity* createEntity(SDL_Renderer* screen,const char *cheminSprite,int x,int y,int w,int h){
    Entity* rEntity = malloc(sizeof(Entity));
    rEntity->sprite=createImage(cheminSprite,screen);
    rEntity->physic.x=x;
    rEntity->physic.y=y;
    if(w==-1){ //Si -1 est fournit en parametre on conserve la largeur de base de l'image
        rEntity->physic.w=getSizeTexture(rEntity->sprite).x;
    }
    else{
        rEntity->physic.w=w;
    }
    if(h==-1){ //Si -1 est fournit en parametre on conserve la hauteur de base de l'image
            rEntity->physic.h=getSizeTexture(rEntity->sprite).y;
    }
    else{
            rEntity->physic.h=h;
    }
    return rEntity;
}

Floor* createEmptyFloor(SDL_Renderer* screen,int id){
    Floor* rFloor=malloc(sizeof(Floor));
    rFloor->tiles_sprites=malloc(sizeof(int)*nbTiles);
    rFloor->tiles_sprites[0]=createImage("ressources/images/floor_texture.png",screen);
    int x = 0;
    int y = 0;
    for(x = 0;x<nbwTiles;x++){
        for(y = 0;y<nbhTiles;y++){
            (rFloor->tiles)[x][y]=0;
        }
    }
    rFloor->id=id;
    return rFloor;
}

void moveEntity(Entity* Entity,int x,int y){
    if(((Entity->physic.x+x)>0)&&((Entity->physic.x+x)<(window_width-Entity->physic.w))){
        Entity->physic.x+=x;
    }
    if(((Entity->physic.y+y)>0)&&((Entity->physic.y+y)<(window_height-Entity->physic.h))){
        Entity->physic.y+=y;
    }
}
