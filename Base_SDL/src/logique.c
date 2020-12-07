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
    rFloor->tiles_sprites=malloc(sizeof(int)*nbTilesText);
    rFloor->tiles_sprites[0]=createImage("ressources/images/floor_texture.png",screen); //Chargement texture sol
    rFloor->tiles_sprites[1]=createImage("ressources/images/floor_rock.png",screen); //Chargement texture rocher
    int x = 0;
    int y = 0;
    for(x = 0;x<nbwTiles;x++){
        for(y = 0;y<nbhTiles;y++){
            (rFloor->tiles)[x][y]=0;
        }
    }
    (rFloor->tiles)[5][5]=1;
    rFloor->id=id;
    return rFloor;
}

void moveEntity(Entity* Entity,int floor[nbwTiles][nbhTiles],int x,int y){
    SDL_Rect nextPos;
    nextPos.x=Entity->physic.x+x;
    nextPos.y=Entity->physic.y+y;
    if(((nextPos.x)>0)&&((nextPos.x)<(window_width-Entity->physic.w))){
        if(((nextPos.y)>0)&&((nextPos.y)<(window_height-Entity->physic.h))){
            if((floor[((nextPos.x)/(window_width/nbwTiles))][((nextPos.y)/(window_height/nbhTiles))]==0)&&
               ((floor[((nextPos.x+Entity->physic.w)/(window_width/nbwTiles))][((nextPos.y+Entity->physic.h)/(window_height/nbhTiles))]==0))&&
               ((floor[((nextPos.x)/(window_width/nbwTiles))][((nextPos.y+Entity->physic.h)/(window_height/nbhTiles))]==0))&&
               ((floor[((nextPos.x+Entity->physic.w)/(window_width/nbwTiles))][((nextPos.y)/(window_height/nbhTiles))]==0)))
                {
                Entity->physic.x+=x;
                Entity->physic.y+=y;
            }
        }
    }
}

Ennemie_List* createList_Ennemie(){
    Ennemie_List* liste = malloc(sizeof(Ennemie_List*));
    if (liste == NULL)
    {
        exit(EXIT_FAILURE);
    }
    liste->premier=NULL;
    return liste;
}

void ajouterList_Ennemie(Ennemie_List* liste,int type,int health,int speed,int damage,int x,int y,int w,int h, char* spriteL,SDL_Renderer* renderer){
    Ennemie* nEnnemie = malloc(sizeof(Ennemie*));
    if(nEnnemie==NULL)
    {
        exit(EXIT_FAILURE);
    }
    nEnnemie->suivant=liste;
    nEnnemie->type=type;
    nEnnemie->speed=speed;
    nEnnemie->damage=damage;
    nEnnemie->e.physic.x=x;
    nEnnemie->e.physic.y=y;
    nEnnemie->e.physic.w=w;
    nEnnemie->e.physic.h=h;
    nEnnemie->e.sprite=createImage(spriteL,renderer);
    nEnnemie->suivant=liste->premier;
    liste->premier=nEnnemie;
}


