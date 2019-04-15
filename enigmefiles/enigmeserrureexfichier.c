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

typedef struct{
    serrure lockpick,lockfield[3],screen,image,unlocked;
}enigme;
int hover(SDL_Rect pos,int x,int y){
    Uint8 p;
    if((x >= pos.x) && (x <= pos.x + pos.w) && ( y >= pos.y) && (y <= pos.y + pos.h)) return 1;
    else return 0;
}

void main(){
    int vie,access = 0;
    serrure lockpick,lockfield[3],screen,image;
    serrure unlocked;
    enigme e;
    SDL_Event event;
    lockfield[0].image = IMG_Load("/home/shidono/Desktop/enigme files/picklock/default.png");
    lockfield[1].image = IMG_Load("/home/shidono/Desktop/enigme files/picklock/pos1.png");
    lockfield[2].image = IMG_Load("/home/shidono/Desktop/enigme files/picklock/pos2.png");
    lockpick.image = IMG_Load("/home/shidono/Desktop/enigme files/picklock/lock.png");
    unlocked.image = IMG_Load("/home/shidono/Desktop/enigme files/picklock/pass.png");
    image.image = IMG_Load("/home/shidono/Desktop/game/optiongame/options/background.png");
    lockpick.pos.x = 250;
    lockpick.pos.y = 50;
    unlocked.pos.x = 380;
    unlocked.pos.y = 190;
    lockfield[0].pos.x = 380;
    lockfield[0].pos.y = 190;
    lockfield[1].pos.x = 380;
    lockfield[1].pos.y = 200;
    lockfield[2].pos.x = 380;
    lockfield[2].pos.y = 190;
    screen.image = SDL_SetVideoMode(1000, 550, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
    image.pos.x = 0;
    image.pos.y = 0;
    screen.pos.x = 0;
    screen.pos.y = 0;
    screen.pos.w = image.image->w;
    screen.pos.h = image.image->h;
    FILE* f = fopen("fichier.bin","w");
    e.lockpick = lockpick;
    e.lockfield[3] = lockfield[3];
    e.unlocked = unlocked;
    fwrite(&e,sizeof(enigme),1,f);
    fclose(f);
    f = fopen("fichier.bin","wb");
    fread(&e,sizeof(enigme),1,f);
    fclose(f);
    int done=1,var,x,y;
    srand(time(0));
    var=(rand() % (2-0+1))+0;
    SDL_BlitSurface(e.image.image,NULL,e.screen.image,&e.image.pos);
    SDL_BlitSurface(e.lockpick.image,NULL,e.screen.image,&e.lockpick.pos);
    SDL_BlitSurface(e.lockfield[var].image,NULL,e.screen.image,&e.lockfield[0].pos);
    SDL_Flip(e.screen.image);
   while(done){
        while(SDL_PollEvent(&event)){
            switch(event.type){
                case SDL_QUIT:
                    SDL_Quit();
                break;
                case SDL_MOUSEBUTTONDOWN:
                     SDL_GetMouseState(&x,&y);
                    if(hover(e.lockfield[0].pos,x,y) && SDL_BUTTON(SDL_BUTTON_LEFT)){
                        if(var == 0){
                            SDL_BlitSurface(e.image.image,NULL,e.screen.image,&e.image.pos);
                            SDL_BlitSurface(e.lockpick.image,NULL,e.screen.image,&e.lockpick.pos);
                            SDL_BlitSurface(e.unlocked.image,NULL,e.screen.image,&e.unlocked.pos);
                            SDL_Flip(e.screen.image);
                            access = 1;
                            printf("access : %d \n",access);
                            SDL_Delay(1000);
                            done = 0;
                        }else{
                            var=(rand() % (2-0+1))+0;
                            SDL_BlitSurface(e.image.image,NULL,e.screen.image,&e.image.pos);
                            SDL_BlitSurface(e.lockpick.image,NULL,e.screen.image,&e.lockpick.pos);
                            SDL_BlitSurface(e.lockfield[var].image,NULL,e.screen.image,&e.lockfield[0].pos);
                            SDL_Flip(screen.image);
                        }
                    }else if(hover(e.lockpick.pos,x,y) && SDL_BUTTON(SDL_BUTTON_LEFT)){
                        vie--;
                        printf("vie : %d\n",vie);
                        SDL_BlitSurface(e.image.image,NULL,e.screen.image,&e.image.pos);
                        SDL_BlitSurface(e.lockpick.image,NULL,e.screen.image,&e.lockpick.pos);
                        SDL_Flip(e.screen.image);
                        SDL_Delay(1000);
                        done = 0;
                    }
                break;
            }
        }
    }
    SDL_FreeSurface(e.lockpick.image);
    SDL_FreeSurface(e.lockfield[var].image);
    SDL_FreeSurface(e.unlocked.image);
}


//verifier que vous n'etes pas un robot.