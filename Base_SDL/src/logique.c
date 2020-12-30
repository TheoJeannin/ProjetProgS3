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
    rEtage->tiles_sprites[1]=createImage("ressources/images/crackeling_wall.png",screen); //Chargement texture rocher
    rEtage->tiles_sprites[2]=createImage("ressources/images/wall_texture.png",screen);
    rEtage->tiles_sprites[3]=createImage("ressources/images/treasure_room_floor.png",screen);
    rEtage->tiles_sprites[4]=createImage("ressources/images/treasure_room_wall.png",screen);
    rEtage->tiles_sprites[5]=createImage("ressources/images/boss_room_floor.png",screen);
    rEtage->tiles_sprites[6]=createImage("ressources/images/boss_room_wall.png",screen);
    rEtage->tiles_sprites[7]=createImage("ressources/images/hole.png",screen);
    rEtage->tiles_sprites[8]=createImage("ressources/images/cold_floor.png",screen);
    return rEtage;
}

void retireEnnemie(){
}

void makeRoomTiles(Room* salle){
        FILE * roomFile;
        char filename[100];
        char* tileValues = malloc(sizeof(char)*(nbwTiles+2));
        int i = 0;
        int y = 0;
        switch(salle->property){
            case 0:
                sprintf(filename,"ressources/rooms/common/%d.txt",randomIntBetween(1,nbCommonRoom));
            break;
            case 1:
                sprintf(filename,"ressources/rooms/treasure/%d.txt",randomIntBetween(1,nbTreasureRoom));
            break;
            case 2:
                sprintf(filename,"ressources/rooms/boss/%d.txt",randomIntBetween(1,nbBossRoom));
            break;
        }
        SDL_Log("%s",filename);
        roomFile = fopen(filename,"r");
        for(i = 0; i<nbhTiles; i++){
                tileValues = fgets(tileValues,nbwTiles+2,roomFile);
                SDL_Log(tileValues);
                for(y = 0; y<nbwTiles;y++){
                    (salle->tiles)[y][i]=tileValues[y]-48;
                }
                y=0;
        }
        free(tileValues);
}

Room* createFloor(int property,Room* north,Room* south,Room* east,Room* west,statFloorHolder stats, int nbRooms,int nbSide){
    Room* rRoom=malloc(sizeof(Room));
    static int id = -1;
    id++;
    int x = 0;
    int y = 0;
    int s = 0;
    int nextProperty = 0;
    rRoom->property=property;
    static int size_emb=0;
    if(id==0){
        size_emb=(nbRooms/2)-1;
        SDL_Log("%d",size_emb);
    }
    int makeside = 0;
    s=randomIntBetween(0,100);
    if(stats.pEmb!=0){
        while(((makeside<2)&&(nbSide>0))&&((stats.pEmb>s)||(nbRooms<=size_emb))){
            s=randomIntBetween(0,100);
            nbSide=nbSide-1;
            makeside=makeside+1;
            stats.pEmb=20;
        }
        if(makeside==0){
            stats.pEmb+=20;
        }
    }
    //Genérationn tiles de la salle
    makeRoomTiles(rRoom);
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
    //Generation futur salle du chemin principale
    if((nbRooms==1)&&(stats.pEmb==0)){
        nextProperty=1;
    }
    else if(nbRooms==1){
        nextProperty=2;
    }
    else{
        nextProperty=0;
    }
    rRoom->id=id;
    s=randomIntBetween(0,100);
    if(nbRooms>0){
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
            rRoom->east=createFloor(nextProperty,NULL,NULL,NULL,rRoom,stats,nbRooms-1,nbSide);
            stats.pEast=0;
            stats.pSouth=50;
            stats.pNorth=50;
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
            rRoom->west=createFloor(nextProperty,NULL,NULL,rRoom,NULL,stats,nbRooms-1,nbSide);
            stats.pWest=0;
            stats.pSouth=50;
            stats.pNorth=50;
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
            rRoom->south=createFloor(nextProperty,rRoom,NULL,NULL,NULL,stats,nbRooms-1,nbSide);
            stats.pSouth=0;
            stats.pEast=50;
            stats.pWest=50;
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
            rRoom->north=createFloor(nextProperty,NULL,rRoom,NULL,NULL,stats,nbRooms-1,nbSide);
            stats.pNorth=0;
            stats.pEast=50;
            stats.pWest=50;
        }
        //Generation du chemin secondaire
        stats.pEmb=0;
        if(makeside>1){
            s=-1;
        }
        else{
            s=randomIntBetween(0,100);
        }
        while(makeside){
        makeside=makeside-1;
        if((stats.pEast>s)&&(rRoom->east==NULL)){
            (rRoom->tiles)[0][nbhTiles/2]=0;
            (rRoom->tiles)[0][nbhTiles/2-1]=0;
            SDL_Log("%d E",rRoom->id);
            stats.direction='E';
            stats.pEast=80;
            stats.pWest=0;
            stats.pSouth=10;
            stats.pNorth=10;
            rRoom->east=createFloor(nextProperty,NULL,NULL,NULL,rRoom,stats,randomIntBetween(2,size_emb),0);
        }else if((stats.pWest+stats.pEast>s)&&(rRoom->west==NULL)){
            (rRoom->tiles)[nbwTiles-1][nbhTiles/2]=0;
            (rRoom->tiles)[nbwTiles-1][nbhTiles/2-1]=0;
            SDL_Log("%d W",rRoom->id);
            stats.direction='W';
            stats.pEast=0;
            stats.pWest=80;
            stats.pSouth=10;
            stats.pNorth=10;
            rRoom->west=createFloor(nextProperty,NULL,NULL,rRoom,NULL,stats,randomIntBetween(2,size_emb),0);
        }else if((stats.pSouth+stats.pWest+stats.pEast>s)&&(rRoom->south==NULL)){
            (rRoom->tiles)[nbwTiles/2][nbhTiles-1]=0;
            (rRoom->tiles)[nbwTiles/2-1][nbhTiles-1]=0;
            SDL_Log("%d S",rRoom->id);
            stats.direction='S';
            stats.pEast=10;
            stats.pWest=10;
            stats.pSouth=80;
            stats.pNorth=0;
            rRoom->south=createFloor(nextProperty,rRoom,NULL,NULL,NULL,stats,randomIntBetween(2,size_emb),0);
        }else{
            (rRoom->tiles)[nbwTiles/2][0]=0;
            (rRoom->tiles)[nbwTiles/2-1][0]=0;
            SDL_Log("%d N",rRoom->id);
            stats.direction='N';
            stats.pEast=10;
            stats.pWest=10;
            stats.pSouth=0;
            stats.pNorth=80;
            rRoom->north=createFloor(nextProperty,NULL,rRoom,NULL,NULL,stats,randomIntBetween(2,size_emb),0);
        }
        }
    }
    rRoom->ennemies=NULL;
    return rRoom;
}

int randomIntBetween(int a, int b){
    return (rand() % (b)) + a ;
}

float vAbsolue(float a){
    if(a<0){
        return -a;
    }
    else{
        return a;
    }
}

void moveMobTowardPlayer(Player* Joueur, Ennemie_List* Ennemies){
    Ennemie* cEnnemie = Ennemies->premier;
    float vDifference;
    float hDifference;
    float hRatio;
    float vRatio;
    while(cEnnemie!=NULL){
        vDifference=Joueur->physic.y-cEnnemie->e.physic.y;
        hDifference=Joueur->physic.x-cEnnemie->e.physic.x;
        if((vDifference!=0)||(hDifference!=0)){
            hRatio=hDifference/(vAbsolue(vDifference)+vAbsolue(hDifference));
            vRatio=vDifference/(vAbsolue(vDifference)+vAbsolue(hDifference));
            cEnnemie->e.physic.x+=round(batSpeed*hRatio);
            cEnnemie->e.physic.y+=round(batSpeed*vRatio);
        }
        cEnnemie=cEnnemie->suivant;
        }
}

int entityCollide(SDL_Rect a, SDL_Rect a){
    if (a.x < b.x + b.width && a.x + a.width > b.x && a.y < b.y + b.height && a.height + a.y > b.y) {
        return 1;
    }
    else{
        return 0;
    }
}
