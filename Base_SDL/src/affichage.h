#ifndef AFFICHAGE_H_INCLUDED
#define AFFICHAGE_H_INCLUDED
void printEntity(SDL_Renderer* screen,Entity* entity);
void printRoom(SDL_Renderer* screen,Room* room,SDL_Texture** tiles_sprites);
void printPlayer(SDL_Renderer* screen,Player* player);


#endif // AFFICHAGE_H_INCLUDED
