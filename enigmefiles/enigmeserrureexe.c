#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "/usr/include/SDL/SDL.h"
#include "/usr/include/SDL/SDL_image.h"
#include "/usr/include/SDL/SDL_mixer.h"
#include "/usr/include/SDL/SDL_events.h"                        
#include "/usr/include/SDL/SDL_mouse.h"

typedef struct{
    SDL_Surface *image;
    SDL_Rect pos;
}serrure;

int hover(SDL_Rect pos,int x,int y){
    Uint8 p;
    if((x >= pos.x) && (x <= pos.x + pos.w) && ( y >= pos.y) && (y <= pos.y + pos.h)) return 1;
    else return 0;
}

void main(){
    int vie = 3,access = 0;
    serrure lockpick,lockfield[3],screen,image;
    serrure unlocked;
    SDL_Event event;
    lockfield[0].image = IMG_Load("/home/shidono/Desktop/enigme files/picklock/default.png");
    lockfield[1].image = IMG_Load("/home/shidono/Desktop/enigme files/picklock/pos1.png");
    lockfield[2].image = IMG_Load("/home/shidono/Desktop/enigme files/picklock/pos2.png");
    lockpick.image = IMG_Load("/home/shidono/Desktop/enigme files/picklock/lock.png");
    unlocked.image = IMG_Load("/home/shidono/Desktop/enigme files/picklock/pass.png");
    image.image = IMG_Load("/home/shidono/Desktop/game/optiongame/options/background.png");
    lockpick.pos.x = 250;
    lockpick.pos.y = 50;
    unlocked.pos.x = 400;
    unlocked.pos.y = 210;
    lockfield[0].pos.x = 406;
    lockfield[0].pos.y = 205;
    lockfield[1].pos.x = 400;
    lockfield[1].pos.y = 200;
    lockfield[2].pos.x = 390;
    lockfield[2].pos.y = 195;
    screen.image = SDL_SetVideoMode(1000, 550, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    image.pos.x = 0;
    image.pos.y = 0;
    screen.pos.x = 0;
    screen.pos.y = 0;
    screen.pos.w = image.image->w;
    screen.pos.h = image.image->h;
    int done=1,var,x,y;
    srand(time(0));
    var=(rand() % (2-0+1))+0;
    printf("start : %d \n",var);
    SDL_BlitSurface(image.image,NULL,screen.image,&image.pos);
    SDL_BlitSurface(lockpick.image,NULL,screen.image,&lockpick.pos);
    SDL_BlitSurface(lockfield[var].image,NULL,screen.image,&lockfield[var].pos);
    SDL_Flip(screen.image);
   while(done){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    SDL_Quit();
                break;
                case SDL_MOUSEBUTTONDOWN:
                     SDL_GetMouseState(&x,&y);
                    if(hover(lockfield[var].pos,x,y) && SDL_BUTTON(SDL_BUTTON_LEFT)){
                        if(var == 0){
                            SDL_BlitSurface(image.image,NULL,screen.image,&image.pos);
                            SDL_BlitSurface(lockpick.image,NULL,screen.image,&lockpick.pos);
                            SDL_BlitSurface(unlocked.image,NULL,screen.image,&unlocked.pos);
                            SDL_Flip(screen.image);
                            access = 1;
                            printf("access : %d \n",access);
                            SDL_Delay(1000);
                            done = 0;
                        }else{
                            var=(rand() % (2-0+1))+0;
                            printf("random : %d\n",var);
                            SDL_BlitSurface(image.image,NULL,screen.image,&image.pos);
                            SDL_BlitSurface(lockpick.image,NULL,screen.image,&lockpick.pos);
                            SDL_BlitSurface(lockfield[var].image,NULL,screen.image,&lockfield[var].pos);
                            SDL_Flip(screen.image);
                        }
                    }else if(hover(lockpick.pos,x,y) && SDL_BUTTON(SDL_BUTTON_LEFT)){
                        vie--;
                        printf("vie : %d\n",vie);
                        SDL_BlitSurface(image.image,NULL,screen.image,&image.pos);
                        SDL_BlitSurface(lockpick.image,NULL,screen.image,&lockpick.pos);
                        SDL_Flip(screen.image);
                        SDL_Delay(1000);
                        done = 0;
                    }
                break;
            }
        }
    }
    SDL_FreeSurface(lockpick.image);
    SDL_FreeSurface(lockfield[var].image);
    SDL_FreeSurface(unlocked.image);
}


//verifier que vous n'etes pas un robot.