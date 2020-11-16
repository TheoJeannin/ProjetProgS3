#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#define window_width 600
#define window_height 600
#define nbwTiles 12
#define nbhTiles 8
#define nbTiles 1
struct entity {
    SDL_Texture* sprite;
    SDL_Rect physic;
};

typedef struct entity Entity;

struct floor {
    int id;
    int tiles[12][8];
    SDL_Texture** tiles_sprites;
};

typedef struct floor Floor;

SDL_Rect makeRect(int x, int y,int w,int h);
SDL_Texture* createImage(const char *cheminFichier,SDL_Renderer* screen);
Entity* createEntity(SDL_Renderer* screen,const char *cheminSprite,int x,int y,int w,int h);
SDL_Point getSizeTexture(SDL_Texture *texture);
void printEntity(SDL_Renderer* screen,Entity* entity);
Floor* createEmptyFloor(SDL_Renderer* screen,int id);

int main(int argc, char *argv[])
    {
    SDL_Window* window;
    SDL_Event evenements;
    SDL_Renderer* screen;
    bool terminer = false;
    //Initialisation SDL
    if(SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Erreur d’initialisation de la SDL: %s",SDL_GetError());

        SDL_Quit();
        return EXIT_FAILURE;
    }

    window = SDL_CreateWindow("Projet Base", SDL_WINDOWPOS_CENTERED,
    SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_RESIZABLE);
    if(window == NULL)
    {
        printf("Erreur de la creation d’une window: %s",SDL_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }
    screen = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    //Initialisation Jeu
    Floor* Salle = createEmptyFloor(screen,1);
    printFloor(screen,Salle);
    SDL_RenderPresent(screen);
    // Boucle principale
    while(!terminer){
        SDL_PollEvent( &evenements );
            switch(evenements.type)
            {
                case SDL_QUIT:
                terminer = true;
                break;
                case SDL_KEYDOWN:
                    switch(evenements.key.keysym.sym)
                    {
                        case SDLK_ESCAPE:
                        case SDLK_q:
                        terminer = true;
                        break;
                    }
            }
    }
    // Quitter SDL
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}

SDL_Rect makeRect(int x, int y,int w,int h){
    SDL_Rect rRect;
    rRect.x=x;
    rRect.y=y;
    rRect.w=w;
    rRect.h=h;
    return rRect;
}

    SDL_Texture* createImage(const char *cheminFichier,SDL_Renderer* screen){
        SDL_Surface* hSurface = IMG_Load(cheminFichier);
        return SDL_CreateTextureFromSurface(screen,hSurface);
    }

SDL_Point getSizeTexture(SDL_Texture *texture){
    SDL_Point size;
    SDL_QueryTexture(texture, NULL, NULL, &size.x, &size.y);
    return size;
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

void printEntity(SDL_Renderer* screen,Entity* entity){
    SDL_RenderCopy(screen,entity->sprite,NULL,&(entity->physic));
}

Floor* createEmptyFloor(SDL_Renderer* screen,int id){
    Floor* rFloor=malloc(sizeof(Floor));
    rFloor->tiles_sprites=malloc(sizeof(int)*nbTiles);
    rFloor->tiles_sprites[0]=createImage("ressources/images/floor_texture.png",screen);
    int x = 0;
    int y = 0;
    for(x = 0;x<nbwTiles;x++){
        for(y = 0;y<nbhTiles;y++){
            (rFloor->tiles)[x][y]=0;
        }
    }
    rFloor->id=id;
    return rFloor;
}

void printFloor(SDL_Renderer* screen,Floor* floor){
    int x = 0;
    int y = 0;
    SDL_Rect pos;
    for(x = 0;x<nbwTiles;x++){
        for(y = 0;y<nbhTiles;y++){
                    pos = makeRect(x*(window_width/nbwTiles),y*(window_height/nbhTiles),window_width/nbwTiles,window_height/nbhTiles);
                    SDL_RenderCopy(screen,floor->tiles_sprites[floor->tiles[x][y]],NULL,&pos);
        }
    }
}

