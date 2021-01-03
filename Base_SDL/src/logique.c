#include "structures.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include <math.h>
#include "extensionsdl.h"
#include "structures.h"
#include "logique.h"

Entity* createEntity(SDL_Renderer* screen,const char *cheminSprite,int x,int y,int w,int h){
    Entity* rEntity = malloc(sizeof(Entity));
    rEntity->sprite = createImage(cheminSprite,screen);
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


SDL_Texture** createEnnemiesSpritesList(SDL_Renderer* screen){
    SDL_Texture** rEnnemiesSpritesList = malloc(sizeof(SDL_Texture*)*nbennemies);
    rEnnemiesSpritesList[0]=createImage("ressources/images/bat.png",screen);
    rEnnemiesSpritesList[1]=createImage("ressources/images/red_bat.png",screen);
    rEnnemiesSpritesList[2]=createImage("ressources/images/taurus_bat.png",screen);
    rEnnemiesSpritesList[3]=createImage("ressources/images/shooter_bat.png",screen);
    rEnnemiesSpritesList[4]=createImage("ressources/images/bullet.png",screen);
    rEnnemiesSpritesList[5]=createImage("ressources/images/boot.png",screen);
    rEnnemiesSpritesList[6]=createImage("ressources/images/heartplus.png",screen);
    return rEnnemiesSpritesList;
}

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
    rPlayer->health=baseHealth;
    rPlayer->attacking=0;
    rPlayer->sword=createEntity(screen,"ressources/images/sword_down.png",x,y,20,50);
    rPlayer->swordSprites=malloc(sizeof(SDL_Texture*)*4);
    rPlayer->swordSprites[0]=rPlayer->sword->sprite;
    rPlayer->swordSprites[1]=createImage("ressources/images/sword_left.png",screen);
    rPlayer->swordSprites[2]=createImage("ressources/images/sword_right.png",screen);
    rPlayer->swordSprites[3]=createImage("ressources/images/sword_up.png",screen);
    return rPlayer;
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

void ajouterList_Ennemie(Ennemie_List* liste,int type,int health,int vSpeed,int hSpeed,int damage,int x,int y,int w,int h){
    static int s = 0;
    s++;
    SDL_Log("S:%d",s);
    Ennemie* nEnnemie = malloc(sizeof(Ennemie));
    if(nEnnemie==NULL)
    {
        exit(EXIT_FAILURE);
    }
    nEnnemie->type=type;
    nEnnemie->damage=damage;
    nEnnemie->e.physic.x=x;
    nEnnemie->e.physic.y=y;
    nEnnemie->e.physic.w=w;
    nEnnemie->e.physic.h=h;
    nEnnemie->precedent=NULL;
    nEnnemie->suivant=liste->premier;
    if(liste->premier!=NULL){
        nEnnemie->suivant->precedent=nEnnemie;
    }
    nEnnemie->vSpeed=vSpeed;
    nEnnemie->hSpeed=hSpeed;
    nEnnemie->state=0;
    liste->premier=nEnnemie;
}


void freeFloor(Floor* Etage){
    freeSpriteArray(Etage->tiles_sprites,nbTilesText);
    freeSpriteArray(Etage->entity_sprites,nbennemies);
    freeRooms(Etage->start,5);
}

void freeSpriteArray(SDL_Texture** EntitiesSprites,int nbI){
    int i =0;
    for(i=0;i<nbI;i++){
        SDL_DestroyTexture(EntitiesSprites[i]);
    }
}

void freePlayer(Player* player){
    freeSpriteArray(player->sprites,4);
    freeSpriteArray(player->sprites,4);
    free(player->sword);
    free(player);
}

void freeEnnemies(Ennemie_List* ennemies){
    Ennemie* cEnnemie;
    cEnnemie=ennemies->premier;
    Ennemie* fEnnemie = cEnnemie;
    while(cEnnemie!=NULL){
        fEnnemie=cEnnemie;
        cEnnemie=cEnnemie->suivant;
        free(fEnnemie);
    }
    free(ennemies);
}

void freeRooms(Room* sRoom,int direction){
    static int i = 0;
    i++;
    SDL_Log("%d",i);
    freeEnnemies(sRoom->ennemies);
    if((((sRoom->north!=NULL)+(sRoom->east!=NULL)+(sRoom->west!=NULL)+(sRoom->south!=NULL))==1)&&(direction!=5)){
        SDL_Log("cul");
        free(sRoom);
    }else{
        if((sRoom->east!=NULL)&&(direction!=1)){
            SDL_Log("east");
            freeRooms(sRoom->east,2);
        }
        if((sRoom->west!=NULL)&&(direction!=2)){
            SDL_Log("west");
            freeRooms(sRoom->west,1);
        }
        if((sRoom->south!=NULL)&&(direction!=3)){
            SDL_Log("south");
            freeRooms(sRoom->south,4);
        }
        if((sRoom->north!=NULL)&&(direction!=4)){
            SDL_Log("north");
            freeRooms(sRoom->north,3);
        }
    }
    free(sRoom);
}

Room* createFloorRooms(int property,Room* north,Room* south,Room* east,Room* west,statFloorHolder stats, int nbRooms,int nbSide){
    Room* rRoom=malloc(sizeof(Room));
    static int id = -1;
    id++;
    int s = 0;
    int nextProperty = 0;
    rRoom->property=property;
    static int size_emb=0;
    if(id==0){
        size_emb=(nbRooms/2)-1;
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
    rRoom->east=east;
    rRoom->west=west;
    rRoom->south=south;
    rRoom->north=north;
    //Genérationn tiles de la salle
    rRoom->ennemies=NULL;
    makeRoomTiles(rRoom);
    SDL_Log("zea%p",rRoom->ennemies->premier);
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
            rRoom->east=createFloorRooms(nextProperty,NULL,NULL,NULL,rRoom,stats,nbRooms-1,nbSide);
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
            rRoom->west=createFloorRooms(nextProperty,NULL,NULL,rRoom,NULL,stats,nbRooms-1,nbSide);
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
            rRoom->south=createFloorRooms(nextProperty,rRoom,NULL,NULL,NULL,stats,nbRooms-1,nbSide);
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
            rRoom->north=createFloorRooms(nextProperty,NULL,rRoom,NULL,NULL,stats,nbRooms-1,nbSide);
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
            rRoom->east=createFloorRooms(nextProperty,NULL,NULL,NULL,rRoom,stats,randomIntBetween(2,size_emb),0);
        }else if((stats.pWest+stats.pEast>s)&&(rRoom->west==NULL)){
            (rRoom->tiles)[nbwTiles-1][nbhTiles/2]=0;
            (rRoom->tiles)[nbwTiles-1][nbhTiles/2-1]=0;
            SDL_Log("%d W",rRoom->id);
            stats.direction='W';
            stats.pEast=0;
            stats.pWest=80;
            stats.pSouth=10;
            stats.pNorth=10;
            rRoom->west=createFloorRooms(nextProperty,NULL,NULL,rRoom,NULL,stats,randomIntBetween(2,size_emb),0);
        }else if((stats.pSouth+stats.pWest+stats.pEast>s)&&(rRoom->south==NULL)){
            (rRoom->tiles)[nbwTiles/2][nbhTiles-1]=0;
            (rRoom->tiles)[nbwTiles/2-1][nbhTiles-1]=0;
            SDL_Log("%d S",rRoom->id);
            stats.direction='S';
            stats.pEast=10;
            stats.pWest=10;
            stats.pSouth=80;
            stats.pNorth=0;
            rRoom->south=createFloorRooms(nextProperty,rRoom,NULL,NULL,NULL,stats,randomIntBetween(2,size_emb),0);
        }else{
            (rRoom->tiles)[nbwTiles/2][0]=0;
            (rRoom->tiles)[nbwTiles/2-1][0]=0;
            SDL_Log("%d N",rRoom->id);
            stats.direction='N';
            stats.pEast=10;
            stats.pWest=10;
            stats.pSouth=0;
            stats.pNorth=80;
            rRoom->north=createFloorRooms(nextProperty,NULL,rRoom,NULL,NULL,stats,randomIntBetween(2,size_emb),0);
        }
        }
    }
    SDL_Log("%p",rRoom->ennemies->premier);
    return rRoom;
}

Floor* createFloor(SDL_Renderer* screen,int id){
    Floor* rEtage = malloc(sizeof(Floor));
    rEtage->id=0;
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
    statFloorHolder Stats;
    Stats.direction='S';
    Stats.pEast=80;
    Stats.pWest=10;
    Stats.pSouth=80;
    Stats.pNorth=0;
    Stats.pEmb=40;
    rEtage->entity_sprites=createEnnemiesSpritesList(screen);
    rEtage->start=createFloorRooms(0,NULL,NULL,NULL,NULL,Stats,8,2);
    rEtage->cRoom=rEtage->start;
    return rEtage;
}

void makeRoomTiles(Room* salle){
        FILE * roomFile;
        char filename[100];
        char* tileValues = malloc(sizeof(char)*(nbwTiles+2));
        int i = 0;
        int y = 0;
        switch(salle->property){
            case 0:
                sprintf(filename,"ressources/rooms/common/%d.txt",4);
            break;
            case 1:
                sprintf(filename,"ressources/rooms/treasure/%d.txt",randomIntBetween(1,nbTreasureRoom));
            break;
            case 2:
                sprintf(filename,"ressources/rooms/boss/%d.txt",randomIntBetween(1,nbBossRoom));
            break;
        }
        roomFile = fopen(filename,"r");
        for(i = 0; i<nbhTiles; i++){
                tileValues = fgets(tileValues,nbwTiles+2,roomFile);
                SDL_Log(tileValues);
                for(y = 0; y<nbwTiles;y++){
                    (salle->tiles)[y][i]=tileValues[y]-48;
                }
        }
        SDL_Log("Ouga %d",i);
        i=0;
        (salle->ennemies)=createList_Ennemie();
        while(!feof(roomFile)){
            SDL_Log("Asses ");
            tileValues = fgets(tileValues,nbwTiles+2,roomFile);
            SDL_Log("%s",tileValues);
            SDL_Log("Asses");
            for(y = 0; y<nbwTiles;y++){
                switch(tileValues[y]-48){
                    case 1 :
                            SDL_Log("Asses");
                            ajouterList_Ennemie(salle->ennemies,1,1,4,4,1,y*(window_width/nbwTiles)+((window_width/nbwTiles)/2)-25,i*(window_height/nbhTiles)+((window_height/nbhTiles)/2)-25,50,50);
                            SDL_Log("x : %d y : %d",y*(window_width/nbwTiles),i*(window_height/nbhTiles));
                    break;
                    case 2 :
                            ajouterList_Ennemie(salle->ennemies,2,1,2,2,1,y*(window_width/nbwTiles)+((window_width/nbwTiles)/2)-25,i*(window_height/nbhTiles)+((window_height/nbhTiles)/2)-25,50,50);
                            SDL_Log("x : %d y : %d",y*(window_width/nbwTiles),i*(window_height/nbhTiles));
                    break;
                    case 3 :
                        ajouterList_Ennemie(salle->ennemies,3,1,0,0,1,y*(window_width/nbwTiles)+((window_width/nbwTiles)/2)-25,i*(window_height/nbhTiles)+((window_height/nbhTiles)/2)-25,50,50);
                        SDL_Log("x : %d y : %d",y*(window_width/nbwTiles),i*(window_height/nbhTiles));
                    break;
                    case 4 :
                        ajouterList_Ennemie(salle->ennemies,4,1,1,1,1,y*(window_width/nbwTiles)+((window_width/nbwTiles)/2)-25,i*(window_height/nbhTiles)+((window_height/nbhTiles)/2)-25,50,50);
                        SDL_Log("x : %d y : %d",y*(window_width/nbwTiles),i*(window_height/nbhTiles));
                    break;
                    case 6 :
                        ajouterList_Ennemie(salle->ennemies,6,0,0,0,0,y*(window_width/nbwTiles)+((window_width/nbwTiles)/2)-25,i*(window_height/nbhTiles)+((window_height/nbhTiles)/2)-25,50,50);
                        SDL_Log("x : %d y : %d",y*(window_width/nbwTiles),i*(window_height/nbhTiles));
                        SDL_Log("H");
                    break;
                    case 7 :
                        ajouterList_Ennemie(salle->ennemies,7,0,0,0,0,y*(window_width/nbwTiles)+((window_width/nbwTiles)/2)-25,i*(window_height/nbhTiles)+((window_height/nbhTiles)/2)-25,50,50);
                        SDL_Log("x : %d y : %d",y*(window_width/nbwTiles),i*(window_height/nbhTiles));
                        SDL_Log("BOOT");
                    break;
                }
            }
            i++;
        }
        free(tileValues);
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

void moveMobTowardPlayer(Player* joueur, Ennemie* ennemie){
    float vDifference;
    float hDifference;
    float hRatio;
    float vRatio;
    vDifference=joueur->physic.y-ennemie->e.physic.y;
    hDifference=joueur->physic.x-ennemie->e.physic.x;
    if((vDifference!=0)||(hDifference!=0)){
        hRatio=hDifference/(vAbsolue(vDifference)+vAbsolue(hDifference));
        vRatio=vDifference/(vAbsolue(vDifference)+vAbsolue(hDifference));
        ennemie->e.physic.x+=round(ennemie->vSpeed*hRatio);
        ennemie->e.physic.y+=round(ennemie->vSpeed*vRatio);
    }
}

void moveMobCharging(Player* joueur,Ennemie* ennemie){
    SDL_Point midPlayer;
    midPlayer.x= joueur->physic.x+(joueur->physic.w/2);
    midPlayer.y= joueur->physic.y+(joueur->physic.h/2);
    SDL_Rect nextPos;
    if(((midPlayer.x>=ennemie->e.physic.x)&&(midPlayer.x<=ennemie->e.physic.x+ennemie->e.physic.w))&&(ennemie->state!=1)){
            if(ennemie->e.physic.y>joueur->physic.y){
                ennemie->vSpeed=-5;
                ennemie->hSpeed=0;
            }
            else{
                ennemie->vSpeed=5;
                ennemie->hSpeed=0;
            }
            ennemie->state=1;
       }
    else if(((midPlayer.y>=ennemie->e.physic.y)&&(midPlayer.y<=ennemie->e.physic.y+ennemie->e.physic.h))&&(ennemie->state!=1)){
            if(ennemie->e.physic.x>joueur->physic.x){
                ennemie->vSpeed=0;
                ennemie->hSpeed=-5;
                SDL_Log("A");
            }
            else{
                ennemie->vSpeed=0;
                ennemie->hSpeed=5;
                SDL_Log("B");
            }
            ennemie->state=1;
    }
    nextPos.x=ennemie->e.physic.x+ennemie->hSpeed;
    nextPos.y=ennemie->e.physic.y+ennemie->vSpeed;
    if((((nextPos.x)>0)&&((nextPos.x)<(window_width-ennemie->e.physic.w)))&&(((nextPos.y)>0)&&((nextPos.y)<(window_height-ennemie->e.physic.h)))){
        ennemie->e.physic.x+=ennemie->hSpeed;
        ennemie->e.physic.y+=ennemie->vSpeed;
    }
    else if(ennemie->state==0){
        ennemie->e.physic.x=0;
        ennemie->e.physic.y=0;
    }
}

void walkTurnObstacle(int floor[nbwTiles][nbhTiles],Ennemie* ennemie){
    SDL_Rect nextPos;
    nextPos.x=ennemie->e.physic.x+ennemie->hSpeed;
    nextPos.y=ennemie->e.physic.y+ennemie->vSpeed;
    nextPos.h=ennemie->e.physic.h;
    nextPos.w=ennemie->e.physic.w;
    SDL_Log("%d",(isCollidingWithLayout(floor,nextPos)));
    if((isCollidingWithLayout(floor,nextPos))){
        switch(randomIntBetween(1,4)){
            case 1 :
                ennemie->hSpeed=2;
                ennemie->vSpeed=0;
            break;
            case 2 :
                ennemie->vSpeed=2;
                ennemie->hSpeed=0;
            break;
            case 3:
                ennemie->hSpeed=2;
                ennemie->vSpeed=0;
            break;
            case 4:
                ennemie->vSpeed=2;
                ennemie->hSpeed=0;
            break;
        }
    }else{
        ennemie->e.physic.x+=ennemie->hSpeed;
        ennemie->e.physic.y+=ennemie->vSpeed;
    }
}

int entityCollide(SDL_Rect a, SDL_Rect b){
    if (a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.h + a.y > b.y) {
        return 1;
    }
    else{
        return 0;
    }
}

void makeShooterShoot(Ennemie_List* ennemies,Ennemie* ennemie,Player* joueur){
    float vDifference;
    float hDifference;
    float hRatio;
    float vRatio;
    if(ennemie->state>=60){
        vDifference=joueur->physic.y-ennemie->e.physic.y;
        hDifference=joueur->physic.x-ennemie->e.physic.x;
        if((vDifference!=0)||(hDifference!=0)){
            hRatio=hDifference/(vAbsolue(vDifference)+vAbsolue(hDifference));
            vRatio=vDifference/(vAbsolue(vDifference)+vAbsolue(hDifference));
        }
        ajouterList_Ennemie(ennemies,5,1,round(5*vRatio),round(5*hRatio),1,ennemie->e.physic.x+((ennemie->e.physic.w)/2),(ennemie->e.physic.y+((ennemie->e.physic.h))/2),25,25);
        ennemie->state=0;
    }
    else{
        ennemie->state=ennemie->state+1;
    }
}


void travelRoom(Player* player,Floor* Etage){
        if(((player->physic.x)>=window_width-(player->physic.w)-10)&&((player->facing)==3)){
            player->physic.x=3;
            Etage->cRoom=Etage->cRoom->west;
        }
        else if(((player->physic.x)<=0)&&((player->facing)==2)){
            player->physic.x=window_width-(player->physic.w)-10;
            Etage->cRoom=Etage->cRoom->east;
        }else if(((player->physic.y)>=window_height-(player->physic.h)-10)&&((player->facing)==1)){
            player->physic.y=0;
            Etage->cRoom=Etage->cRoom->south;
        }else if(((player->physic.y)<=0)&&((player->facing)==4)){
            player->physic.y=window_height-(player->physic.h)-10;
            Etage->cRoom=Etage->cRoom->north;
        }
}

void moveBullets(Ennemie* ennemie){
    ennemie->e.physic.x+=ennemie->hSpeed;
    ennemie->e.physic.y+=ennemie->vSpeed;
}

int isCollidingWithLayout(int floor[nbwTiles][nbhTiles],SDL_Rect Pos){
            if((floor[((Pos.x)/(window_width/nbwTiles))][((Pos.y)/(window_height/nbhTiles))]==0)&&
               ((floor[((Pos.x+Pos.w-4)/(window_width/nbwTiles))][((Pos.y+Pos.h-4)/(window_height/nbhTiles))]==0))&&
               ((floor[((Pos.x)/(window_width/nbwTiles))][((Pos.y+Pos.h-4)/(window_height/nbhTiles))]==0))&&
               ((floor[((Pos.x+Pos.w-4)/(window_width/nbwTiles))][((Pos.y)/(window_height/nbhTiles))]==0)))
                {
                return 0;
            }
            else{
                return 1;
            }
}

void attackPlayer(Player* joueur,Ennemie_List* ennemies,int floor[nbwTiles][nbhTiles]){
    joueur->attacking--;
    joueur->sword->sprite=joueur->swordSprites[joueur->facing-1];
    SDL_Point coordPic;
    switch(joueur->facing){
        case 1:
             joueur->sword->physic.h=50;
             joueur->sword->physic.w=20;
             joueur->sword->physic.x=joueur->physic.x+((joueur->physic.w)/2);
             joueur->sword->physic.y=joueur->physic.y+joueur->physic.h;
             coordPic.x=joueur->sword->physic.x+(joueur->sword->physic.w/2);
             coordPic.y=joueur->sword->physic.y+joueur->sword->physic.h;
        break;
        case 2:
             joueur->sword->physic.h=20;
             joueur->sword->physic.w=50;SDL_Log("south");
             joueur->sword->physic.x=joueur->physic.x-joueur->sword->physic.w;
             joueur->sword->physic.y=joueur->physic.y+(2*(joueur->physic.h)/3);
             coordPic.x=joueur->sword->physic.x;
             coordPic.y=joueur->sword->physic.y+(joueur->sword->physic.h/2);
        break;
        case 3:
             joueur->sword->physic.h=20;
             joueur->sword->physic.w=50;
             joueur->sword->physic.x=joueur->physic.x+joueur->physic.w;
             joueur->sword->physic.y=joueur->physic.y+(2*(joueur->physic.h)/3);
             coordPic.x=joueur->sword->physic.x+joueur->sword->physic.w;
             coordPic.y=joueur->sword->physic.y+(joueur->sword->physic.h/2);
        break;
        case 4:
             joueur->sword->physic.h=50;
             joueur->sword->physic.w=20;
             joueur->sword->physic.x=joueur->physic.x+((joueur->physic.w)/2);
             joueur->sword->physic.y=joueur->physic.y-joueur->sword->physic.h;
             coordPic.x=joueur->sword->physic.x+(joueur->sword->physic.w/2);
             coordPic.y=joueur->sword->physic.y;
             SDL_Log("A");
        break;
    }
    if((floor[((coordPic.x)/(window_width/nbwTiles))][((coordPic.y)/(window_height/nbhTiles))]==1)){
        floor[((coordPic.x)/(window_width/nbwTiles))][((coordPic.y)/(window_height/nbhTiles))]=0;
    }
    Ennemie* cEnnemie = ennemies->premier;
    Ennemie* fEnnemie;
    while(cEnnemie!=NULL){
        fEnnemie=cEnnemie;
        cEnnemie=cEnnemie->suivant;
        if(entityCollide(joueur->sword->physic,fEnnemie->e.physic)){
            retireFromList(ennemies,fEnnemie);
        }
    }
}

void moveEnnemies(Ennemie_List* ennemies,Player* player,int floor[nbwTiles][nbhTiles]){
    Ennemie* cEnnemie = ennemies->premier;
    while(cEnnemie!=NULL){
        switch(cEnnemie->type){
            case 1 :
                moveMobTowardPlayer(player,cEnnemie);
            break;
            case 2 :
                moveMobTowardPlayer(player,cEnnemie);
            break;
            case 3 :
                moveMobCharging(player,cEnnemie);
            break;
            //case 4 :
                //makeShooterShoot(ennemies,cEnnemie,player);
            //break;
            case 5 :
                moveBullets(cEnnemie);
                SDL_Log("Fiou");
            break;
        }
        cEnnemie=cEnnemie->suivant;
    }
}

void retireFromList(Ennemie_List* ennemies,Ennemie* adEnnemie){
    if(ennemies->premier==adEnnemie){
        ennemies->premier=adEnnemie->suivant;
        if(ennemies->premier!=NULL){
            ennemies->premier->precedent=NULL;
        }
        free(adEnnemie);
        SDL_Log("A");
    }
    else{
        adEnnemie->precedent->suivant=adEnnemie->suivant;
        if(adEnnemie->suivant!=NULL){
            adEnnemie->suivant->precedent=adEnnemie->precedent;
        }
        free(adEnnemie);
    }
}

void ennemiesCollideWithPlayer(Ennemie_List* ennemies,Player* joueur){
    Ennemie* cEnnemie = ennemies->premier;
    Ennemie* fEnnemie;
    while(cEnnemie!=NULL){
        fEnnemie=cEnnemie;
        cEnnemie=cEnnemie->suivant;
        if(entityCollide(fEnnemie->e.physic,joueur->physic)){
            retireFromList(ennemies,fEnnemie);
        }
    }
}
