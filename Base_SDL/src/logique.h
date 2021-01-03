#ifndef LOGIQUE_H_INCLUDED
#define LOGIQUE_H_INCLUDED
int isCollidingWithLayout(int floor[nbwTiles][nbhTiles],SDL_Rect Pos);
void ajouterList_Ennemie(Ennemie_List* liste,int type,int health,int vSpeed,int hSpeed,int damage,int x,int y,int w,int h);
Room* createEmptyRoom(int id,Room* north,Room* south,Room* east,Room* west);
void walkTurnObstacle(int floor[nbwTiles][nbhTiles],Ennemie* ennemie);
void moveEntity(SDL_Rect* coord,int floor[nbwTiles][nbhTiles],int x,int y);
Floor* createEmptyFloor(SDL_Renderer* screen,int id);
Room* getCurrentRoom(Floor* floor);
Room* createRightRooms(int id,Room* north,Room* south,Room* east,Room* west);
Floor* createFloor(SDL_Renderer* screen,int id);
void retireFromList(Ennemie_List* ennemies,Ennemie* adEnnemie);
Room* createFloorRooms(int property,Room* north,Room* south,Room* east,Room* west,statFloorHolder stats, int nbRooms,int nbSide);
float absolute(float a);
Entity* createEntity(SDL_Renderer* screen,const char *cheminSprite,int x,int y,int w,int h);
Ennemie_List* createList_Ennemie();
void moveEnnemies(Ennemie_List* ennemies,Player* player,int floor[nbwTiles][nbhTiles]);
SDL_Texture** createEnnemiesSpritesList(SDL_Renderer* screen);
int randomIntBetween(int a, int b);
void makeRoomTiles(Room* salle);
Player* createPlayer(SDL_Renderer* screen,int x,int y,int w,int h);
void travelRoom(Player* player,Floor* Etage);
void attackPlayer(Player* joueur,Ennemie_List* ennemies,int floor[nbwTiles][nbhTiles]);
void ennemiesCollideWithPlayer(Ennemie_List* ennemies,Player* joueur);
void freePlayer(Player* player);
void freeFloor(Floor* Etage);
void freeSpriteArray(SDL_Texture** EntitiesSprites,int nbI);
void freeRooms(Room* sRoom,int direction);
#endif // LOGIQUE_H_INCLUDED
