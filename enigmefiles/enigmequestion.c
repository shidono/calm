#include <stdio.h>
#include <stdlib.h>
#include <time.h>
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
}*serrure;


void initialiserenigmeserrure(serrure lockpick,serrure *lockfield[3],serrure unlocked){
    position[0].image = IMG_Load("default");
    position[1].image = IMG_Load("pos1");
    position[2].image = IMG_Load("pos2");
    lockpick.image = IMG_Load("lockpick");
    unlocked.image = IMG_Load("unlocked");
    //lockpick.pos.x = ??;
    //lockpick.pos.y = ??;
    //lockfield[0].pos.x = ??;
    //lockfield[0].pos.y = ??;
    //unlocked.pos.x = ??;
    //unlocked.pos.y = ??;
    lockfield[1].pos = lockfield[0].pos;
    lockfield[2].pos = lockfield[0].pos;
}


void afficherenigmeserrure(serrure *lockpick,serrure *lockfield[3],serrue *unlocked){
    int done=1,var;
    srand(time(0));
    var=(rand() % (2-0+1))+0;
    SDL_BlitSurface(lockpick.image,NULL,screen,&lockpick.pos);
    SDL_BlitSurface(lockfield[var].image,NULL,screen,&lockfield[0].pos);
    SDL_flip(screen);
   while(done){
        SDL_GetMouseState(&x,&y);
        if(hover(lockfield[0].pos,x,y) && SDL_BUTTON(SDL_BUTTON_LEFT)){
            if(var == 0){
                SDL_BlitSurface(lockpick.image,NULL,screen,&lockpick.pos);
                SDL_BlitSurface(unlocked.image,NULL,screen,&unlocked.pos);
                delay(1000);
                done = 0;
            }else{
                var=(rand() % (2-0+1))+0;
                SDL_BlitSurface(lockpick.image,NULL,screen,&lockpick.pos);
                SDL_BlitSurface(lockfield[var].image,NULL,screen,&lockfield[0].pos);
                SDL_flip(screen);
            }
        }
    }
    freesurface(lockpick.image);
	freesurface(lockfield[var].image);
    freesurface(unlocked.image);
}