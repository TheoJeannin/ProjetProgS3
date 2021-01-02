#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
void printEntity(SDL_Renderer* screen,Entity* entity);
void printRoom(SDL_Renderer* screen,Room* room,SDL_Texture** tiles_sprites);
void printPlayer(SDL_Renderer* screen,Player* player);
void printEnnemies(SDL_Renderer* screen,Ennemie_List* list,SDL_Texture** listSprites);


#endif // AFFICHAGE_H_INCLUDED
