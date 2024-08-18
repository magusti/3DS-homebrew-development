 /*
  *  Portant l'exemple sdl-simple de Switch (SDL 2.0)  a 3DS (SDL 1.2).
  * 
  * http://gamedevgeek.com/tutorials/getting-started-with-sdl/
  * 
 */
#include <stdlib.h>
#include <stdio.h>

#include <SDL.h> // SDL 1.2 per a 3DS
// #include <SDL_video.h> 

// some switch buttons - Açò està a la llibreria
#define JOY_A     0
#define JOY_B     1
#define JOY_X     2
#define JOY_Y     3
#define JOY_PLUS  10
#define JOY_MINUS 11
#define JOY_LEFT  12
#define JOY_UP    13
#define JOY_RIGHT 14
#define JOY_DOWN  15

#define anchoRect 16
#define altoRect  16

#define SCREEN_WIDTH_TOP  400       // Width (ample) of the top screen
#define SCREEN_HEIGHT 240           // Height (alt) of the top/bottom screens.
#define SCREEN_WIDTH_BOTTOM  320    // Width (ample) of the bottom screen

int main(int argc, char *argv[])
{
    SDL_Event event;
//     SDL_Window *window;
//     SDL_Renderer *renderer;
    SDL_Surface *pantalla;
    int done = 0, w, h;
    int x=0, y =0;

    w = SCREEN_WIDTH_TOP; //320;
    h = SCREEN_HEIGHT; 

    if (SDL_Init(SDL_INIT_VIDEO ) < 0) {
//         SDL_Log("SDL_Init: %s\n", SDL_GetError());
        return -1;
    }




    /*
     * Initialize the display,
     * requesting a software surface
     */
    pantalla = SDL_SetVideoMode(w, h, 32, //8, 
                                        SDL_TOPSCR | SDL_CONSOLEBOTTOM | SDL_HWSURFACE);
    if ( pantalla == NULL ) {
//         printf("Couldn't set %dx%dx8 video mode: %s\n", w, h, SDL_GetError()); // ¿Para qué? ¡No se ve en pantalla!
        exit(1);
    }

#define RED  "\x1B[31m"
#define GRN  "\x1B[32m"
#define BLU  "\x1B[34m"

    
    printf( "SDL simpleRect: Mueve el cuadrado con la cruceta.\n");
    printf( " A activa/desactiva el rastro.\n");
    printf( " B...\n");
    printf( "Rect en (x,y) = (%d,%d).\n", x, y);
//     printf( "%s \x1b[3;4f SDL simpleRect\n\nMueve el cuadrado con la cruceta\n", RED);
//     printf( "%s \x1b[4;6f A activa/desactiva el rastro\n", GRN );
//     printf( "%s \x1b[5;6f  B...\n", GRN);
//     printf( "%s \x1b[7;4f Rect en (x,y) = (%d,%d)\n", BLU, x, y);
    SDL_Delay( 100 );
    
    
    while (!done) {
        while (SDL_PollEvent(&event)) {
//         while ( SDL_WaitEvent(&event) ) {  // >= 0
            switch (event.type) {
                case SDL_JOYAXISMOTION:
//                     SDL_Log("Joystick %d axis %d value: %d\n",
//                             event.jaxis.which,
//                             event.jaxis.axis, event.jaxis.value);
                    break;

                case SDL_JOYBUTTONDOWN:
//                     SDL_Log("Joystick %d button %d down\n",
//                             event.jbutton.which, event.jbutton.button);
                    // https://github.com/devkitPro/SDL/blob/switch-sdl2/src/joystick/switch/SDL_sysjoystick.c#L52
                    // seek for joystick #0
                    if (event.jbutton.which == 0) {
                        if (event.jbutton.button == JOY_A) { // 0
                            // (A) button down
//                             if(w == 1920) {
// //                                 SDL_SetWindowSize(window, 1280, 720);
//                             } else {
// //                                 SDL_SetWindowSize(window, 1920, 1080);
//                             }
                        } else if (event.jbutton.button == JOY_PLUS) { //10
                            // (+) button down
                            done = 1;
                        }
                    }
                    break;

                case SDL_MOUSEBUTTONDOWN: 
//        https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideeventexamples.html         
                    break;

                default:
                    break;
            }
        }

//         SDL_Rect f = {0, 0, w, h};
//         SDL_FillRect(pantalla, &f,  SDL_MapRGB(pantalla->format, 111, 111, 111) );


//         draw_rects(pantalla, x, 0);
//         draw_rects(pantalla, x, h - altoRect);
        SDL_Rect r = {x, y, anchoRect, altoRect};
        SDL_FillRect(pantalla, &r,  SDL_MapRGB(pantalla->format, 255, 0, 0) );
        
                    
        /* update the screen */
        SDL_UpdateRect(pantalla, 0, 0, w, h);

        x++;
        if (x > w + (anchoRect/2)) {
            x = w;
        }
        
//     printf( "%s\x1b[47m \x1b[3;4f SDL simpleRect: Mueve el cuadrado con la cruceta\n", RED);
//     printf( "%s\x1b[47m \x1b[5;6f A activa/desactiva el rastro\n", GRN );
//     printf( "%s\x1b[47m \x1b[6;6f  B...\n", GRN);
//     printf( "%s\x1b[47m \x1b[8;4f Rect en (x,y) = (%d,%d)\n", BLU, x, y);
    printf( "\x1b[2JSDL simpleRect: Mueve el cuadrado con la cruceta.\n");
    printf( " A activa/desactiva el rastro.\n");
    printf( " B...\n");
    printf( "Rect en (x,y) = (%d,%d).\n", x, y);
    SDL_Delay( 1 );
        
    } // while (!done)

    SDL_FreeSurface( pantalla );
    SDL_Quit(); // https://www.libsdl.org/release/SDL-1.2.15/docs/html/index.html

    return 0;
}
