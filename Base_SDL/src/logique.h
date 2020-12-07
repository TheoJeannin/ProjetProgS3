#ifndef LOGIQUE_H_INCLUDED
#define LOGIQUE_H_INCLUDED
Entity* createEntity(SDL_Renderer* screen,const char *cheminSprite,int x,int y,int w,int h);
Floor* createEmptyFloor(SDL_Renderer* screen,int id);
void moveEntity(Entity* Entity,int floor[nbwTiles][nbhTiles],int x,int y);

#endif // LOGIQUE_H_INCLUDED
