#ifndef LOGIQUE_H_INCLUDED
#define LOGIQUE_H_INCLUDED
Entity* createEntity(SDL_Renderer* screen,const char *cheminSprite,int x,int y,int w,int h);
Room* createEmptyRoom(int id,Room* north,Room* south,Room* east,Room* west);
void moveEntity(Entity* Entity,int floor[nbwTiles][nbhTiles],int x,int y);
Floor* createEmptyFloor(SDL_Renderer* screen,int id);
Room* getCurrentRoom(Floor* floor);
#endif // LOGIQUE_H_INCLUDED
