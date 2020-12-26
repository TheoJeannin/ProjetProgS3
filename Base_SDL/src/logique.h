#ifndef LOGIQUE_H_INCLUDED
#define LOGIQUE_H_INCLUDED
Entity* createEntity(SDL_Renderer* screen,const char *cheminSprite,int x,int y,int w,int h);
Room* createEmptyRoom(int id,Room* north,Room* south,Room* east,Room* west);
void moveEntity(SDL_Rect* coord,int floor[nbwTiles][nbhTiles],int x,int y);
Floor* createEmptyFloor(SDL_Renderer* screen,int id);
Room* getCurrentRoom(Floor* floor);
Room* createRightRooms(int id,Room* north,Room* south,Room* east,Room* west);
Room* createFloor(int id,Room* north,Room* south,Room* east,Room* west,statFloorHolder stats, int nbRooms,int nbSide,int principale);
float absolute(float a);
#endif // LOGIQUE_H_INCLUDED
