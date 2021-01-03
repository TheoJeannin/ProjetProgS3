#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <SDL2/SDL_image.h>
#include "structures.h"
#include "extensionsdl.h"

//fonction affichant la salle
void printRoom(SDL_Renderer* screen,Room* room,SDL_Texture** tiles_sprites){
    int x = 0;
    int y = 0;
    SDL_Rect pos;
    for(x = 0;x<nbwTiles;x++){
        for(y = 0;y<nbhTiles;y++){
                    pos = makeRect(x*(window_width/nbwTiles),y*(window_height/nbhTiles),window_width/nbwTiles,window_height/nbhTiles);
                    switch(room->tiles[x][y]){
                        case 0 :
                            if(room->property==1){
                                SDL_RenderCopy(screen,tiles_sprites[3],NULL,&pos);
                            }
                            else if(room->property==2){
                                SDL_RenderCopy(screen,tiles_sprites[5],NULL,&pos);
                            }
                            else{
                                SDL_RenderCopy(screen,tiles_sprites[0],NULL,&pos);
                            }
                        break;
                        case 1 :
                                SDL_RenderCopy(screen,tiles_sprites[1],NULL,&pos);
                        break;
                        case 2 :
                            if(room->property==1){
                                SDL_RenderCopy(screen,tiles_sprites[4],NULL,&pos);
                            }
                            else if(room->property==2){
                                SDL_RenderCopy(screen,tiles_sprites[6],NULL,&pos);
                            }
                            else{
                                SDL_RenderCopy(screen,tiles_sprites[2],NULL,&pos);
                            }
                        break;
                        case 7 :
                            SDL_RenderCopy(screen,tiles_sprites[7],NULL,&pos);
                        break;
                        case 8 :
                            SDL_RenderCopy(screen,tiles_sprites[8],NULL,&pos);
                        break;
                    }
        }
    }
}

//fonction affichant les ennemies
void printEnnemies(SDL_Renderer* screen,Ennemie_List* list,SDL_Texture** listSprites){
    if(list!=NULL){
        Ennemie* cEnnemie=list->premier;
        while(cEnnemie!=NULL){
            switch(cEnnemie->type){
            case 1:
                SDL_RenderCopy(screen,listSprites[0],NULL,&(cEnnemie->e.physic));
            break;
            case 2:
                SDL_RenderCopy(screen,listSprites[1],NULL,&(cEnnemie->e.physic));
            break;
            case 3:
                SDL_RenderCopy(screen,listSprites[2],NULL,&(cEnnemie->e.physic));
            break;
            case 4:
                SDL_RenderCopy(screen,listSprites[3],NULL,&(cEnnemie->e.physic));
            break;
            case 5:
                SDL_RenderCopy(screen,listSprites[4],NULL,&(cEnnemie->e.physic));
            break;
            case 6:
                SDL_RenderCopy(screen,listSprites[5],NULL,&(cEnnemie->e.physic));
            break;
            case 7:
                SDL_RenderCopy(screen,listSprites[6],NULL,&(cEnnemie->e.physic));
            break;
            }
            cEnnemie=cEnnemie->suivant;
        }
    }
}

//Fonction affichant le joueur
void printPlayer(SDL_Renderer* screen,Player* player){
    SDL_RenderCopy(screen,player->sprites[player->facing-1],NULL,&(player->physic));
    if(player->attacking>=10){
        SDL_RenderCopy(screen,player->sword->sprite,NULL,&(player->sword->physic));
    }
}
