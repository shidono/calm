#include <stdio.h>
#include <stdlib.h>
#include "/usr/include/SDL/SDL.h"
#include "/usr/include/SDL/SDL_image.h"
#include "/usr/include/SDL/SDL_mixer.h"
#include "/usr/include/SDL/SDL_events.h"
#include "/usr/include/SDL/SDL_mouse.h"

int hover(SDL_Rect pos,int x,int y){
    Uint8 p;
    if((x >= pos.x) && (x <= pos.x + pos.w) && ( y >= pos.y) && (y <= pos.y + pos.h)) return 1;
    else return 0;
}

typedef struct{
    SDL_Surface *image;
    SDL_Rect pos;
    int direction;
}*protocol;

typedef struct{
    SDL_Surface *image;
    SDL_Rect pos;
}*simple;

void initialiserenigmehack(simple map,SDL_Surface *3pos1,SDL_Surface *3pos2,SDL_Surface *3pos3,SDL_Surface *3pos4,SDL_Surface *2pos1,SDL_Surface *2pos2,simple locked,simple unlocked,protocol firstleft,protocol middle,protocol bottom,protocol final2pos,protocol final3pos){
    map.image = IMG_Load("plan");
    3pos1 = IMG_Load("3pos1");
    3pos2 = IMG_Load("3pos2");
    3pos3 = IMG_Load("3pos3");
    3pos4 = IMG_Load("3pos4");
    2pos1 = IMG_Load("2pos1");
    2pos2 = IMG_Load("2pos2");
    //correct places
    /*
    firstleft.image = 3pos2;
    middle.image = 3pos1;
    bottom.image = 2pos1;
    final3pos.image = 3pos2;
    final2pos.image = 2pos1;
    */
    firstleft.image = 3pos1;
    middle.image = 3pos3;
    bottom.image = 2pos2;
    final3pos.image = 3pos1;
    final2pos.image = 2pos2;
    unlocked.image = IMG_Load("unlocked");
    locked.image = IMG_Load("locked");
    firstleft.direction = 1;middle.direction = 3;bottom.direction = 2;final3pos.direction = 1;final2pos.direction = 2;
    //positions rigell jawik
}


void afficherenigmehack(int *vie,int *access,SDL_Surface *screen,simple map,SDL_Surface *3pos1,SDL_Surface *3pos2,SDL_Surface *3pos3,SDL_Surface *3pos4,SDL_Surface *2pos1,SDL_Surface *2pos2,simple locked,simple unlocked,protocol firstleft,protocol middle,protocol bottom,protocol final2pos,protocol final3pos){
    int done=1;
   while(done){
        SDL_BlitSurface(map.image,NULL,screen,&map.pos);
        SDL_BlitSurface(firstleft.image,NULL,screen,&firstleft.pos);
        SDL_BlitSurface(middle.image,NULL,screen,&middle.pos);
        SDL_BlitSurface(bottom.image,NULL,screen,&bottom.pos);
        SDL_BlitSurface(final3pos.image,NULL,screen,&final3pos.pos);
        SDL_BlitSurface(final2pos.image,NULL,screen,&final2pos.pos);
        SDL_BlitSurface(locked.image,NULL,screen,&locked.pos);
        SDL_GetMouseState(&x,&y);
        if((firstleft.direction == 2) && (middle.direction == 3) && (bottom.direction == 2) && (final3pos.direction == 1) && (final2pos.direction == 2)){
            SDL_BlitSurface(unlocked.image,NULL,screen,&locked.pos);
            SDL_flip(screen);
            delay(3000);
            done = 0;
        }else{
        	SDL_BlitSurface(locked.image,NULL,screen,&locked.pos);
            SDL_flip(screen);
        	if((hover(firstleft.pos,x,y) || hover(middle.pos,x,y) || hover(final3pos.pos,x,y)) && SDL_BUTTON(SDL_BUTTON_LEFT)){
                if(firstleft.direction == 4 || middle.direction == 4 || final3pos.direction == 4){
                    if(firstleft.direction == 4){
                        firstleft.direction = 1;
                        firstleft.image = 3pos1;
                    }else if(middle.direction == 4){
                        middle.direction = 1;
                        middle.image = 3pos1;
                    }else{
                        final3pos.direction = 1;
                        final3pos.image = 3pos1;
                    }
                }else if(firstleft.direction == 1 || middle.direction == 1 || final3pos.direction == 1){
                    if(firstleft.direction == 1){
                        firstleft.direction++;
                        firstleft.image = 3pos2;
                    }else if(middle.direction == 1){
                        middle.direction++;
                        middle.image = 3pos2;
                    }else{
                        final3pos.direction++;
                        final3pos.image = 3pos2;
                    }
                }else if(firstleft.direction == 2 || middle.direction == 2 || final3pos.direction == 2){
                    if(firstleft.direction == 2){
                        firstleft.direction++;
                        firstleft.image = 3pos3;
                    }else if(middle.direction == 2){
                        middle.direction++;
                        middle.image = 3pos3;
                    }else{
                        final3pos.direction++;
                        final3pos.image = 3pos3;
                    }
                }else if(firstleft.direction == 3 || middle.direction == 3 || final3pos.direction == 3){
                    if(firstleft.direction == 3){
                        firstleft.direction++;
                        firstleft.image = 3pos4;
                    }else if(middle.direction == 3){
                        middle.direction++;
                        middle.image = 3pos4;
                    }else{
                        final3pos.direction++;
                        final3pos.image = 3pos4;
                    }
                }
        }else if((hover(bottom.pos,x,y) || hover(final2pos.pos,x,y)) && SDL_BUTTON(SDL_BUTTON_LEFT)){
            if(bottom.direction == 2 || final2pos.direction == 2){
                if(bottom.direction == 2){
                    bottom.direction = 1;
                    bottom.image = 2pos1;
                }else{
                    final2pos.direction = 1;
                    final2pos.image = 2pos1;
                }
            }else{
                if(bottom.direction == 1){
                    bottom.direction++;
                    bottom.image = 2pos2;
                }else{
                    final2pos.direction++;
                    bottom.image = 2pos2;
                }
            }
        }
      }
    }
    SDL_FreeSurface(map.image);
	SDL_FreeSurface(firstleft.image);
	SDL_FreeSurface(middle.image);
	SDL_FreeSurface(bottom.image);
	SDL_FreeSurface(final3pos.image);
	SDL_FreeSurface(final2pos.image);
	SDL_FreeSurface(locked.image);
}