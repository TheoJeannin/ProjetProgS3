#ifndef SURCOUCHE_SDL_H_INCLUDED
#define SURCOUCHE_SDL_H_INCLUDED

SDL_Rect makeRect(int x, int y,int w,int h);
SDL_Texture* createImage(const char *cheminFichier,SDL_Renderer* screen);
SDL_Point getSizeTexture(SDL_Texture *texture);


#endif //
