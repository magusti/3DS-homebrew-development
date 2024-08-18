/*
  * 3DS (SDL 1.2)
  * Comprovant el us de les dos pantalles en mode text
  * + llistar els modes de vídeo disponibles 
  * 
  // https://www.gamebrew.org/wiki/SDL-3DS
  // SDL-3DS is a 3DS port of SDL 1.2 - Simple DirectMedia Layer Version 1.2.15. 
  //    
  // Homebrew [Release] SDL-3DS 1.2.15 - Simple DirectMedia Layer for 3DS
  // https://gbatemp.net/threads/release-sdl-3ds-1-2-15-simple-directmedia-layer-for-3ds.459291/
 */

#include <time.h>
#include <unistd.h>

#include <SDL.h> //https://github.com/nop90/SDL-3DS /https://github.com/nop90/SDL-3DS

#include <3ds.h>

// #include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <malloc.h>
// #include <errno.h>
// #include <stdarg.h>
// #include <unistd.h>
// 
// #include <fcntl.h>
// 
// #include <sys/types.h>
// 
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>
// 
// #include <3ds.h>


// 3DS: 240x400 dalt i 240x320 baix
#define SCREEN_W 400
// #define SCREEN_H 400

#define SCREEN_WIDTH_TOP  400       // Width (ample) of the top screen
#define SCREEN_H 240           // -Height (alt) of the top/bottom screens.
#define SCREEN_WIDTH_BOTTOM  320    // Width (ample) of the bottom screen

void obtindreInfoVideoModes() {
//     SDL_VideoModeOK -- Check to see if a particular video mode is supported.
// // SDL_VideoModeOK returns 0 if the requested mode is not supported under any bit depth, or returns the bits-per-pixel of the closest available mode with the given width, height and requested surface flags (see SDL_SetVideoMode).
// 
// SDL_Surface *screen;
// Uint32 bpp;
// 
// printf("Checking mode 640x480@16bpp.\n");
// bpp=SDL_VideoModeOK(640, 480, 16, SDL_HWSURFACE);
// 
// if(!bpp){
//   printf("Mode not available.\n");
//   exit(-1);
// }
// 
// printf("SDL Recommends 640x480@%dbpp.\n", bpp);
// screen=SDL_SetVideoMode(640, 480, bpp, SDL_HWSURFACE);

    
    // https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdllistmodes.html
    //SDL_ListModes -- Returns a pointer to an array of available screen dimensions for the given format and video flags

    SDL_Rect **modes;
    int i;

    printf("\nAnalitzant Modes de vídeo soportats:\n");

    /* Get available fullscreen/hardware modes */
//     modes=SDL_ListModes(NULL, SDL_FULLSCREEN|SDL_HWSURFACE);
    modes=SDL_ListModes(NULL, SDL_SWSURFACE); //SDL_HWSURFACE);

    /* Check is there are any modes available */
    if(modes == (SDL_Rect **)0){
        printf("No modes available!\n");
        exit(-1);
    }

    /* Check if our resolution is restricted */
    if(modes == (SDL_Rect **)-1){
        printf("All resolutions available.\n");
    }
    else{
    /* Print valid modes */
    printf("Available Modes\n");
    for(i=0;modes[i];++i)
        printf("  %d x %d\n", modes[i]->w, modes[i]->h);
    }
} // Fi de obtindreInfoVideoModes


int main(int argc, char** argv) {
    int exit_requested = 0;
    SDL_Surface *pantalla;
    char msg[1024];
    SDL_Rect r;
       
    srand(time(NULL));

//  /opt/devkitpro/portlibs/3ds/include/SDL/SDL_video.h   
 /** Available for SDL_SetVideoMode() */
// #ifdef __3DS__
// #define SDL_TOPSCR        0x00100000      /**< 3DS Top Screen mode */
// #define SDL_BOTTOMSCR     0x00200000      /**< 3DS Bottom Screen mode */
// #define SDL_DUALSCR       0x00300000      /**< 3DS Top+Bottom Screen mode */
// #define SDL_FITWIDTH      0x00400000      /**> Render a resized surface to fit systen screen width */
// #define SDL_FITHEIGHT     0x00800000      /**> Render a resized surface to fit systen screen height */
// #define SDL_CONSOLETOP    0x00040000      /**> Enale console output on Top screen */
// #define SDL_CONSOLEBOTTOM 0x00080000      /**> Enale console output on Bottom screen */
// #endif

 
//     No puc executar
// obtindreInfoVideoModes();
//      que es cau l'aplicació a l'emulador
 
    printf("Antes\n");
    // Inicialitzar en un "segur" i mostrar-ho
    SDL_VideoInfo *videoInfo = SDL_GetVideoInfo(); 

    // NO VA;
//     pantalla = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 8, SDL_CONSOLETOP); 
//     pantalla = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 8, SDL_HWSURFACE | SDL_CONSOLETOP); 
//     pantalla = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 8, SDL_SWSURFACE | SDL_CONSOLETOP); 
    
//     // SÍ VA:
//     pantalla = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 8, SDL_CONSOLEBOTTOM); 
    //     pantalla = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 8, SDL_SWSURFACE | SDL_CONSOLEBOTTOM ); 
//          pantalla = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 8, SDL_HWSURFACE | SDL_CONSOLEBOTTOM ); 

    //     pantalla = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 8, SDL_TOPSCR | SDL_CONSOLEBOTTOM | SDL_SWSURFACE); 
    //     pantalla = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 8,  SDL_CONSOLETOP | SDL_BOTTOMSCR | SDL_SWSURFACE); 
    //     pantalla = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 8, SDL_SWSURFACE | SDL_BOTTOMSCR); // DUALSCR); //CONSOLEBOTTOM); 
//         pantalla2 = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 8, SDL_SWSURFACE | SDL_TOPSCR); 

    //     pantalla = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 8,  SDL_DUALSCR | SDL_SWSURFACE); 
                                             
    
    printf("hw_available? %d \n", videoInfo->hw_available); //	Is it possible to create hardware surfaces?
    printf("wm_available? %d \n", videoInfo->wm_available); //	Is there a window manager available
    printf("blit_hw? %d \n", videoInfo->blit_hw); //	Are hardware to hardware blits accelerated?
    printf("blit_hw_CC? %d \n", videoInfo->blit_hw_CC); //	Are hardware to hardware colorkey blits accelerated?
    printf("blit_hw_A? %d \n", videoInfo->blit_hw_A); //	Are hardware to hardware alpha blits accelerated?
    printf("blit_sw? %d \n", videoInfo->hw_available); //	Are software to hardware blits accelerated?
    printf("blit_sw_CC? %d \n", videoInfo->hw_available); //	Are software to hardware colorkey blits accelerated?
    printf("blit_sw_A? %d \n", videoInfo->hw_available); //	Are software to hardware alpha blits accelerated?
    printf("blit_fill? %d \n", videoInfo->hw_available); //	Are color fills accelerated?
    printf("video_mem? %ld \n", videoInfo->video_mem); //	Total amount of video memory in Kilobytes
    printf("vfmt? Pixel format of the video device\n"); //	Pixel format of the video device
    printf("video_mem BitsPerPixel? %d \n", videoInfo->vfmt->BitsPerPixel );
    printf("video_mem BitsPerPixel? %d \n", videoInfo->vfmt->BitsPerPixel );

    SDL_VideoDriverName(msg, 1024);
    printf("Video Driver %s\n", msg);
  
// //     r = {rand()%SCREEN_W, rand()%SCREEN_H, 64, 64};
//     r.x = rand()%SCREEN_W;
//     r.y = rand()%SCREEN_H;
//     r.w = 64;
//     r.h = 64;
//     SDL_FillRect(pantalla, &r,  SDL_MapRGB(pantalla->format, rand()%255, rand()%255, rand()%255) );
//     SDL_UpdateRect(pantalla, 0, 0, SCREEN_W, SCREEN_H);
// 
//     printf("%d,%d a %d,%d\n", r.x, r.y, r.w, r.h);
//     
   //     SDL_Delay(2000);
//     SDL_Quit();
//     
//     
//     
//     
//     pantalla = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 8, SDL_CONSOLEBOTTOM); //     
//     printf("Enable console output on Bottom screen \n");
//     obtindreInfoVideoModes();
//     SDL_Delay(2000);
//     SDL_Quit();
// 
// 
//     if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
//         printf("Couldn't initialize SDL: %s\n", SDL_GetError());
//         exit(1);
//     }
//     pantalla = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 8, SDL_ANYFORMAT);
// printf("Enable console output on Any format  \n");
// obtindreInfoVideoModes();
//     SDL_Delay(2000);
//     SDL_Quit();
//         
//     if( SDL_Init(SDL_INIT_VIDEO) < 0 ) {
//         printf("Couldn't initialize SDL: %s\n", SDL_GetError());
//         exit(1);
//     }
// // //     pantalla = SDL_SetVideoMode(w, h, 8, SDL_TOPSCR | SDL_CONSOLEBOTTOM | SDL_SWSURFACE);
//     pantalla = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 8, SDL_CONSOLETOP); 
// printf("Enable console output on Top screen \n");
// obtindreInfoVideoModes();
//     SDL_Delay(2000);
//     SDL_Quit();
//     
//     
//     
    
    int w,h;
    
//     w=400; h = 240; pantalla = SDL_SetVideoMode(w, h, 8, SDL_CONSOLETOP | SDL_CONSOLEBOTTOM); // SDL_HWSURFACE     
    
    // Arriba gráfico, abajo texto
    //pantalla = SDL_SetVideoMode(SCREEN_WIDTH_TOP, SCREEN_H, 8, SDL_TOPSCR | SDL_CONSOLEBOTTOM ); // SDL_HWSURFACE
    //pantalla = SDL_SetVideoMode(SCREEN_WIDTH_TOP, SCREEN_H, 8, SDL_CONSOLETOP | SDL_BOTTOMSCR ); // OK
//     pantalla = SDL_SetVideoMode(SCREEN_WIDTH_BOTTOM, SCREEN_H, 8, SDL_CONSOLETOP | SDL_BOTTOMSCR ); // TODO en 
    
    // Arriba y abajo en modo gráfico
//     pantalla = SDL_SetVideoMode(SCREEN_WIDTH_TOP, SCREEN_H, 8, SDL_TOPSCR | SDL_BOTTOMSCR); // SDL_HWSURFACE
//     pantalla = SDL_SetVideoMode(SCREEN_WIDTH_BOTTOM, SCREEN_H, 8, SDL_TOPSCR | SDL_BOTTOMSCR); // TODO en negro
//     w=400; h = 240; pantalla = SDL_SetVideoMode(w, h, 8, SDL_TOPSCR | SDL_BOTTOMSCR);
    w=320; h = 480; pantalla = SDL_SetVideoMode(w, h, 8, SDL_TOPSCR | SDL_BOTTOMSCR); 

    // DUAL
//     pantalla = SDL_SetVideoMode(320, 480, 8, SDL_DUALSCR); // Pegadas
//     pantalla = SDL_SetVideoMode(SCREEN_WIDTH_TOP, 2*SCREEN_H, 8, SDL_DUALSCR| SDL_FULLSCREEN); // Pegadas en vertical y dejando margen negro a la derecha
//     pantalla = SDL_SetVideoMode(SCREEN_WIDTH_BOTTOM, 2*SCREEN_H, 8, SDL_DUALSCR| SDL_FULLSCREEN); // Pegadas, ocupando el ancho 
//     w=320; h = 480; pantalla = SDL_SetVideoMode(w, h, 8, SDL_DUALSCR); // | SDL_SWSURFACE);
    
    
    
    SDL_SetCursor( NULL );
    SDL_Rect f = {0, 0, w, h/2-1}; // x,y, anple, alt
    SDL_FillRect(pantalla, &f,  SDL_MapRGB(pantalla->format, 255, 0, 255) );            
    SDL_Rect f2 = {0, h/2, w, (2*h)-1}; 
    SDL_FillRect(pantalla, &f2,  SDL_MapRGB(pantalla->format, 0, 255, 255) );
    SDL_UpdateRect(pantalla, 0, 0, w, h); 
//         SDL_Delay(10000 );
    while (!exit_requested && aptMainLoop() ) {
      
        // //     r = {rand()%SCREEN_W, rand()%SCREEN_H, 64, 64};
    r.x = rand()%w; //SCREEN_W;
    r.y = rand()%h; //SCREEN_H;
    r.w = 64;
    r.h = 64;
    SDL_FillRect(pantalla, &r,  SDL_MapRGB(pantalla->format, rand()%255, rand()%255, rand()%255) );
//     SDL_UpdateRect(pantalla, 0, 0, SCREEN_W, SCREEN_H);
    SDL_UpdateRect(pantalla, 0, 0, w, h); //320, 480);
 
//     printf("%d,%d a %d,%d\n", r.x, r.y, r.w, r.h);
     
//         
//         gspWaitForVBlank();
//         gfxSwapBuffers();
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
