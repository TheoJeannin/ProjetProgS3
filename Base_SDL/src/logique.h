#ifndef LOGIQUE_H_INCLUDED
#define LOGIQUE_H_INCLUDED
ajouterList_Ennemie(Ennemie_List* liste,int type,int health,int vSpeed,int hSpeed,int damage,int x,int y,int w,int h);
Room* createEmptyRoom(int id,Room* north,Room* south,Room* east,Room* west);
void walkTurnObstacle(int floor[nbwTiles][nbhTiles],Ennemie* ennemie);
int isCollidingWithLayout(int floor[nbwTiles][nbhTiles],SDL_Rect Pos);
void moveEntity(SDL_Rect* coord,int floor[nbwTiles][nbhTiles],int x,int y);
Floor* createEmptyFloor(SDL_Renderer* screen,int id);
Room* getCurrentRoom(Floor* floor);
Room* createRightRooms(int id,Room* north,Room* south,Room* east,Room* west);
Room* createFloor(int id,Room* north,Room* south,Room* east,Room* west,statFloorHolder stats, int nbRooms,int nbSide,int principale);
float absolute(float a);
Entity* createEntity(SDL_Renderer* screen,const char *cheminSprite,int x,int y,int w,int h);
Ennemie_List* createList_Ennemie();
void moveEnnemies(Ennemie_List* ennemies,Player* player,int floor[nbwTiles][nbhTiles]);

#endif // LOGIQUE_H_INCLUDED
