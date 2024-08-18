//
// SDL 1.2 vídeo para 3DS
// Adaptació del exemple de https://github.com/zephray/SDL-1.2-N3DS
//

#include <3ds.h>
#include <stdio.h>
// #include "SDL/SDL.h"
#include <SDL.h> //https://github.com/nop90/SDL-3DS /https://github.com/nop90/SDL-3DS
#include <SDL_image.h> //https://github.com/nop90/SDL-3DS /https://github.com/nop90/SDL-3DS

#define SCREEN_W 320
#define SCREEN_H 240

 

int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *pantalla;
    SDL_Surface *bitmaps[4];
    char *rutes[4] = {"romfs:/test.bmp", "romfs:/w3c.png", "romfs:/drunkentimes.png", "romfs:/sdl.png"};
    SDL_Rect rects[4] = {{10,10, 0,0}, {30, 50, 0,0}, {100,75, 0,0}, {200,100, 0,0}};

    pantalla = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 32, 
                              SDL_SWSURFACE | SDL_TOPSCR | SDL_CONSOLEBOTTOM);
  
    Result rs = romfsInit();
    if (rs)
        printf("romfsInit: %08lx\n", rs);
    else {
        printf("romfs Initialization succeed.\n");
        bitmaps[0] = SDL_LoadBMP( rutes[0] );
        if (bitmaps[0] == NULL)
            printf("Open Bitmap %s failed!\n", rutes[0] );
        else{
            SDL_BlitSurface(bitmaps[0], NULL, pantalla, &rects[0]);
            printf("%s Should be bilted\n", rutes[0] );
        }
        
         	
// https://www.libsdl.org/projects/old/SDL_image/docs/SDL_image.html#SEC24
       // load sample.png into image
        SDL_RWops *rwop;
        rwop=SDL_RWFromFile(rutes[1], "rb");
        bitmaps[1] = IMG_LoadPNG_RW(rwop);
        if (bitmaps[1] == NULL)
            printf("Open Bitmap %s failed!\n", rutes[1] );
        else {
            SDL_BlitSurface(bitmaps[1], NULL, pantalla, &rects[1]);
            printf("%s Should be bilted\n", rutes[1] );
        }

        rwop=SDL_RWFromFile(rutes[2], "rb");
        bitmaps[2] = IMG_LoadPNG_RW(rwop);
        if (bitmaps[2] == NULL)
            printf("Open Bitmap %s failed!\n", rutes[2] );
        else {
            SDL_BlitSurface(bitmaps[2], NULL, pantalla, &rects[2]);
            printf("%s Should be bilted\n", rutes[2] );
        }
     
        rwop=SDL_RWFromFile(rutes[3], "rb");
        bitmaps[3] = IMG_LoadPNG_RW(rwop);
        if (bitmaps[3] == NULL)
            printf("Open Bitmap %s failed!\n", rutes[3] );
        else {
            SDL_BlitSurface(bitmaps[3], NULL, pantalla, &rects[3] );
            printf("%s Should be bilted\n", rutes[3] );
        }

        
    } // else de if (rs)
    
    SDL_Delay(1000);

    SDL_Flip(pantalla);
    printf("Should be flipped\n");
    SDL_UpdateRect(pantalla, 0, 0, SCREEN_W, SCREEN_H); 
    SDL_Delay(5000);
    
    SDL_FreeSurface( bitmaps[0] );
    SDL_FreeSurface( bitmaps[1] );
    SDL_FreeSurface( bitmaps[2] );
    SDL_FreeSurface( bitmaps[3] );
    
    SDL_Quit();
  
    return 0;
}
