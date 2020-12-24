#include "structures.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include "extensionsdl.h"
#include "structures.h"
Player* createPlayer(SDL_Renderer* screen,int x,int y,int w,int h){
    Player* rPlayer=malloc(sizeof(Player));
    rPlayer->sprites=malloc(sizeof(SDL_Texture*)*4);
    rPlayer->sprites[0]=createImage("ressources/images/player_idle.png",screen);
    rPlayer->sprites[1]=createImage("ressources/images/player_left.png",screen);
    rPlayer->sprites[2]=createImage("ressources/images/player_right.png",screen);
    rPlayer->sprites[3]=createImage("ressources/images/player_up.png",screen);
    rPlayer->physic.x=x;
    rPlayer->physic.y=y;
    rPlayer->physic.w=w;
    rPlayer->physic.h=h;
    rPlayer->facing=1;
    return rPlayer;
}

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

void moveEntity(SDL_Rect* coord,int floor[nbwTiles][nbhTiles],int x,int y){
    SDL_Rect nextPos;
    nextPos.x=coord->x+x;
    nextPos.y=coord->y+y;
    //if(((nextPos.x)>0)&&((nextPos.x)<(window_width-coord->w))){
        //if(((nextPos.y)>0)&&((nextPos.y)<(window_height-coord->h))){
            if((floor[((nextPos.x)/(window_width/nbwTiles))][((nextPos.y)/(window_height/nbhTiles))]==0)&&
               ((floor[((nextPos.x+coord->w-4)/(window_width/nbwTiles))][((nextPos.y+coord->h-4)/(window_height/nbhTiles))]==0))&&
               ((floor[((nextPos.x)/(window_width/nbwTiles))][((nextPos.y+coord->h-4)/(window_height/nbhTiles))]==0))&&
               ((floor[((nextPos.x+coord->w-4)/(window_width/nbwTiles))][((nextPos.y)/(window_height/nbhTiles))]==0)))
                {
                coord->x+=x;
                coord->y+=y;
            }
        //}
    //}
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
    Ennemie* nEnnemie = malloc(sizeof(Ennemie));
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

Floor* createEmptyFloor(SDL_Renderer* screen,int id){
    int i = 0;
    int y = 0;
    Floor* rEtage = malloc(sizeof(Floor));
    rEtage->id=0;
    rEtage->start=NULL;
    rEtage->tiles_sprites=malloc(sizeof(int)*nbTilesText);
    rEtage->tiles_sprites[0]=createImage("ressources/images/floor_texture.png",screen); //Chargement texture sol
    rEtage->tiles_sprites[1]=createImage("ressources/images/floor_rock.png",screen); //Chargement texture rocher
    rEtage->tiles_sprites[2]=createImage("ressources/images/wall_texture.png",screen);
    return rEtage;
}

Room* createRightRooms(int id,Room* north,Room* south,Room* east,Room* west){
    Room* rRoom=malloc(sizeof(Room));
    int x = 0;
    int y = 0;
    for(x = 0;x<nbwTiles;x++){
        for(y = 0;y<nbhTiles;y++){
            if((((x==0)||(x==nbwTiles-1))||(y==0))||(y==nbhTiles-1)){
                (rRoom->tiles)[x][y]=2;
            }
            else{
                (rRoom->tiles)[x][y]=0;
            }
        }
    }
    if(north!=NULL){
        rRoom->north=north;
        (rRoom->tiles)[nbwTiles/2][0]=1;
        (rRoom->tiles)[nbwTiles/2-1][0]=1;
    }
    else{
        rRoom->north=NULL;
    }
    if(south!=NULL){
        rRoom->south=south;
        (rRoom->tiles)[nbwTiles/2][nbhTiles-1]=0;
        (rRoom->tiles)[nbwTiles/2-1][nbhTiles-1]=0;
    }
    else{
        rRoom->south=NULL;
    }
    if(east!=NULL){
        rRoom->east=east;
        (rRoom->tiles)[0][nbhTiles/2]=0;
        (rRoom->tiles)[0][nbhTiles/2-1]=0;
    }
    if(west!=NULL){
        rRoom->west=west;
        (rRoom->tiles)[nbwTiles-1][nbhTiles/2]=0;
        (rRoom->tiles)[nbwTiles-1][nbhTiles/2-1]=0;
    }
    if(id<=8){
        rRoom->west=createRightRooms(id+1,NULL,NULL,rRoom,NULL);
        (rRoom->tiles)[nbwTiles/2][0]=1;
        (rRoom->tiles)[nbwTiles/2-1][0]=1;
    }
    (rRoom->tiles)[5][5]=1;
    (rRoom->tiles)[8][4]=1;
    (rRoom->tiles)[4][5]=1;
    (rRoom->tiles)[2][2]=1;
    rRoom->id=id;
    rRoom->ennemies=NULL;
    return rRoom;
}

Room* createFloor(int id,Room* north,Room* south,Room* east,Room* west,statFloorHolder stats){
    Room* rRoom=malloc(sizeof(Room));
    int x = 0;
    int y = 0;
    int s = 0;
    //Genérationn tiles de la salle
    for(x = 0;x<nbwTiles;x++){
        for(y = 0;y<nbhTiles;y++){
            if((((x==0)||(x==nbwTiles-1))||(y==0))||(y==nbhTiles-1)){
                (rRoom->tiles)[x][y]=2;
            }
            else{
                (rRoom->tiles)[x][y]=0;
            }
        }
    }
    //Generation des portes
    if(north!=NULL){
        rRoom->north=north;
        (rRoom->tiles)[nbwTiles/2][0]=0;
        (rRoom->tiles)[nbwTiles/2-1][0]=0;
    }
    else{
        rRoom->north=NULL;
    }
    if(south!=NULL){
        rRoom->south=south;
        (rRoom->tiles)[nbwTiles/2][nbhTiles-1]=0;
        (rRoom->tiles)[nbwTiles/2-1][nbhTiles-1]=0;
    }
    else{
        rRoom->south=NULL;
    }
    if(east!=NULL){
        rRoom->east=east;
        (rRoom->tiles)[0][nbhTiles/2]=0;
        (rRoom->tiles)[0][nbhTiles/2-1]=0;
    }
    if(west!=NULL){
        rRoom->west=west;
        (rRoom->tiles)[nbwTiles-1][nbhTiles/2]=0;
        (rRoom->tiles)[nbwTiles-1][nbhTiles/2-1]=0;
    }
    //Generation futur salle
    SDL_Log("%s","ABC");
    s=randomIntBetween(0,100);
    if(id<=8){
        if((stats.pEast>s)&&(east==NULL)){
            (rRoom->tiles)[0][nbhTiles/2]=0;
            (rRoom->tiles)[0][nbhTiles/2-1]=0;
            if(stats.direction=='E'){
                SDL_Log("%s","EA");
                stats.pEast-=20;
                stats.pSouth+=10;
                stats.pNorth+=10;
            }else{
                SDL_Log("%s","EC");
                stats.direction='E';
                stats.pEast=80;
                stats.pWest=0;
                stats.pSouth=10;
                stats.pNorth=10;
            }
            rRoom->east=createFloor(id+1,NULL,NULL,NULL,rRoom,stats);
        }else if((stats.pWest+stats.pEast>s)&&(west==NULL)){
            (rRoom->tiles)[nbwTiles-1][nbhTiles/2]=0;
            (rRoom->tiles)[nbwTiles-1][nbhTiles/2-1]=0;
            if(stats.direction=='W'){
                SDL_Log("%s","WA");
                stats.pWest-=20;
                stats.pSouth+=10;
                stats.pNorth+=10;
            }else{
                SDL_Log("%s","WC");
                stats.direction='W';
                stats.pEast=0;
                stats.pWest=80;
                stats.pSouth=10;
                stats.pNorth=10;
            }
            rRoom->west=createFloor(id+1,NULL,NULL,rRoom,NULL,stats);
        }else if((stats.pSouth+stats.pWest+stats.pEast>s)&&(south==NULL)){
            (rRoom->tiles)[nbwTiles/2][nbhTiles-1]=0;
            (rRoom->tiles)[nbwTiles/2-1][nbhTiles-1]=0;
            if(stats.direction=='S'){
                SDL_Log("%s","SA");
                stats.pEast+=10;
                stats.pWest+=10;
                stats.pSouth-=20;
            }else{
                SDL_Log("%s","SC");
                stats.direction='S';
                stats.pEast=10;
                stats.pWest=10;
                stats.pSouth=80;
                stats.pNorth=0;
            }
            rRoom->south=createFloor(id+1,rRoom,NULL,NULL,NULL,stats);
        }else{
            (rRoom->tiles)[nbwTiles/2][0]=0;
            (rRoom->tiles)[nbwTiles/2-1][0]=0;
            if(stats.direction=='N'){
                SDL_Log("%s","NA");
                stats.pEast+=10;
                stats.pWest+=10;
                stats.pNorth-=20;
            }else{
                SDL_Log("%s","NC");
                stats.direction='N';
                stats.pEast=10;
                stats.pWest=10;
                stats.pSouth=0;
                stats.pNorth=80;
            }
            rRoom->north=createFloor(id+1,NULL,rRoom,NULL,NULL,stats);
        }
    }
    (rRoom->tiles)[5][5]=1;
    (rRoom->tiles)[8][4]=1;
    (rRoom->tiles)[4][5]=1;
    (rRoom->tiles)[2][2]=1;
    rRoom->id=id;
    rRoom->ennemies=NULL;
    return rRoom;
}

int randomIntBetween(int a, int b){
    return (rand() % (b+1)) + a ;
}



