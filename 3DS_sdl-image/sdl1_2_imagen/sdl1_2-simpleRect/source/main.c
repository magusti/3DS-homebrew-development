/*
  * 3DS (SDL 1.2)
  * Comprovant el us de Rect per dibuixar
  * 
  // Homebrew [Release] SDL-3DS 1.2.15 - Simple DirectMedia Layer for 3DS
  // https://gbatemp.net/threads/release-sdl-3ds-1-2-15-simple-directmedia-layer-for-3ds.459291/
 */

#include <time.h>
// #include <unistd.h>
#include <SDL.h> //https://github.com/nop90/SDL-3DS /https://github.com/nop90/SDL-3DS
#include <3ds.h>



// 3DS: 240x400 dalt i 240x320 baix
#define SCREEN_W 400
#define SCREEN_WIDTH_TOP  400       // Width (ample) of the top screen
#define SCREEN_H 240           // -Height (alt) of the top/bottom screens.
#define SCREEN_WIDTH_BOTTOM  320    // Width (ample) of the bottom screen



int main(int argc, char** argv) {
    int exit_requested = 0;
    SDL_Surface *pantalla;
    char msg[1024];
    SDL_Rect r;
       
    srand(time(NULL));

    if (SDL_Init(SDL_INIT_VIDEO ) < 0) {
        return -1;
    }

    SDL_VideoDriverName(msg, 1024);
    printf("Video Driver %s\n", msg);
    
    int w,h;
//     w=320; h = 480; pantalla = SDL_SetVideoMode(w, h, 8, SDL_TOPSCR | SDL_BOTTOMSCR);
    w=400; h = 240; pantalla = SDL_SetVideoMode(w, h, 8, SDL_TOPSCR | SDL_CONSOLEBOTTOM); 

    
    SDL_SetCursor( NULL );
    SDL_Rect f = {0, 0, w, h/2-1}; // x,y, anple, alt
    SDL_FillRect(pantalla, &f,  SDL_MapRGB(pantalla->format, 255, 0, 255) );            
//     SDL_Rect f2 = {0, h/2, w, (2*h)-1}; 
//     SDL_FillRect(pantalla, &f2,  SDL_MapRGB(pantalla->format, 0, 255, 255) );
    SDL_UpdateRect(pantalla, 0, 0, w, h); 
//         SDL_Delay(10000 );
    while (!exit_requested && aptMainLoop() ) {
      
        // //     r = {rand()%SCREEN_W, rand()%SCREEN_H, 64, 64};
    r.x = rand()%w; //SCREEN_W;
    r.y = rand()%h; //SCREEN_H;
    r.w = rand()%w; //64;
    r.h = rand()%h; //64;
    SDL_FillRect(pantalla, &r,  SDL_MapRGB(pantalla->format, rand()%255, rand()%255, rand()%255) );
    SDL_UpdateRect(pantalla, 0, 0, w, h); //320, 480);
 
    printf("%d,%d a %d,%d\n", r.x, r.y, r.w, r.h);
     
        hidScanInput();
        
        u32 kDown = hidKeysDown();
        
        if ( (kDown & KEY_START) || (kDown & KEY_A) ) { 
            break; 
        }
    }
    
    SDL_FreeSurface( pantalla );
 
    SDL_Quit();
    return 0;
}
