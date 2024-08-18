/*
  * 3DS (SDL 1.2)
  * Comprovant el us dels events botonera i pantalla
  * 
  // https://www.gamebrew.org/wiki/SDL-3DS
  // SDL-3DS is a 3DS port of SDL 1.2 - Simple DirectMedia Layer Version 1.2.15. 
  //    
  // Homebrew [Release] SDL-3DS 1.2.15 - Simple DirectMedia Layer for 3DS
  // https://gbatemp.net/threads/release-sdl-3ds-1-2-15-simple-directmedia-layer-for-3ds.459291/
  * 
  * https://www.libsdl.org/release/SDL-1.2.15/docs/html/guidevideo.html
  * + 3dslink-demo
 */




#include <time.h>
#include <unistd.h>

#include <SDL.h> //https://github.com/nop90/SDL-3DS /https://github.com/nop90/SDL-3DS

#include <stdio.h>
// #include <stdlib.h>
// #include <string.h>
// #include <malloc.h>
// #include <errno.h>
// #include <stdarg.h>
// #include <unistd.h>
// #include <fcntl.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <netinet/in.h>
// #include <arpa/inet.h>

#include <3ds.h>

// // some switch buttons - Açò està a la llibreria
// #define JOY_A     0
// #define JOY_B     1
// #define JOY_X     2
// #define JOY_Y     3
// #define JOY_PLUS  10
// #define JOY_MINUS 11
// #define JOY_LEFT  12
// #define JOY_UP    13
// #define JOY_RIGHT 14
// #define JOY_DOWN  15

// 3DS: 320x400 dalt i 230x240 baix
#define SCREEN_W 320
#define SCREEN_H 240


int main(int argc, char** argv) {
    int exit_requested = 0;
    int wait = 25,i=0; // , ret;
    SDL_Surface *pantalla;
    SDL_Event event;
    SDL_Joystick *joystick;

  
   SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
   
//     if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK) < 0 ) {
//         printf("Couldn't initialize SDL: %s\n", SDL_GetError());
//         exit(1);
//     }
//  

    /*
     * Initialize the display,
     * requesting a software surface
     */
// //     pantalla = SDL_SetVideoMode(w, h, 8, SDL_TOPSCR | SDL_CONSOLEBOTTOM | SDL_SWSURFACE);
    pantalla = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 8, SDL_CONSOLETOP | SDL_CONSOLEBOTTOM); // SDL_HWSURFACE
 
//     screen = SDL_SetVideoMode(320, 240, 16, SDL_TOPSCR | SDL_CONSOLEBOTTOM | SDL_HWSURFACE); //SDL_DOUBLEBUF | SDL_SWSURFACE | SDL_TOPSCR | SDL_CONSOLEBOTTOM);
    
//     SDL_Delay(2500);
    
    // https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideinput.html
    printf("%i joysticks were found.\n\n", SDL_NumJoysticks() );

    if (SDL_NumJoysticks() > 0) {		
        printf("The names of the joysticks are:\n");
        for( i=0; i < SDL_NumJoysticks(); i++ )   {       
            joystick = SDL_JoystickOpen(i);
            printf("    %s, con %d botones.\n", SDL_JoystickName(i), SDL_JoystickNumButtons(joystick));
            SDL_JoystickClose( joystick );
        }                
       joystick = SDL_JoystickOpen(0);  
    } // if (SDL_NumJoysticks() > 0) {    
   
    while (!exit_requested && aptMainLoop() ) {
        // Game-type Input
        // https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideinputkeyboard.html
//  events with SDL like OnKeyPressed, OnKeyReleased, OnKeyHit, etc,  
//  https://stackoverflow.com/questions/3741055/inputs-in-sdl-on-key-pressed
        // while
    if(SDL_PollEvent(&event))  {  
         printf("event.type %d\n", event.type);
    // SDL_events.h ==> SDL_EventType <-- Event enumerations 
    // SDL_keysym.h ==> SDLK_[TECLA], però n'hi han 322!!! La 3DS No en té tantes!!!

//      /opt/devkitpro/portlibs/3ds/include/SDL/SDL_events.h           
//        0 SDL_NOEVENT ,                 /**< Unused (do not remove) */
//        1 SDL_ACTIVEEVENT,              /**< Application loses/gains visibility */
//        2 SDL_KEYDOWN,                  /**< Keys pressed */
//        3 SDL_KEYUP,                    /**< Keys released */
//        4 SDL_MOUSEMOTION,              /**< Mouse moved */
//        5 SDL_MOUSEBUTTONDOWN,          /**< Mouse button pressed */
//        6 SDL_MOUSEBUTTONUP,            /**< Mouse button released */
//        7 SDL_JOYAXISMOTION,            /**< Joystick axis motion */
//        8 SDL_JOYBALLMOTION,            /**< Joystick trackball motion */
//        9 SDL_JOYHATMOTION,             /**< Joystick hat position change */
//        10 SDL_JOYBUTTONDOWN,           /**< Joystick button pressed */
//        11 SDL_JOYBUTTONUP,             /**< Joystick button released */
//        12 SDL_QUIT,  
         
//  https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlevent.html               
// Structure Definition
// 
// typedef union{
//   Uint8 type;
//   SDL_ActiveEvent active;
//   SDL_KeyboardEvent key;
//   SDL_MouseMotionEvent motion;
//   SDL_MouseButtonEvent button;
//   SDL_JoyAxisEvent jaxis;
//   SDL_JoyBallEvent jball;
//   SDL_JoyHatEvent jhat;
//   SDL_JoyButtonEvent jbutton;
//   SDL_ResizeEvent resize;
//   SDL_ExposeEvent expose;
//   SDL_QuitEvent quit;
//   SDL_UserEvent user;
//   SDL_SysWMEvent syswm;
// } SDL_Event;
        
         
        switch(event.type)
        {                         
            case SDL_KEYDOWN: // SDL_KEYUP
                printf( "SDL_KEYDOWN, %s\n", SDL_GetKeyName( event.key.keysym.sym ) );                
               // https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlkey.html
               printf( "type %u8 state %u8. keysym %d\n", event.key.type, event.key.state, 0); //event.key.keysym,scancode );
//                  if(event.key.keysym.sym == KEY_A)
//                   printf("A\n");
//                  else 
                     if(event.key.keysym.sym == SDLK_a) // No JOY_A
                  printf("SDLK_A\n");
                 else if (event.key.keysym.sym == SDLK_UP) // JOY_UP
                  printf("UP\n");
                 else
                  printf("??? %d\n",event.key.keysym.sym );
                 
//                  break;
                break;

            case SDL_QUIT:
            /* Set whatever flags are necessary to */
            /* end the main game loop here */
                printf( "SDL_QUIT\n" );
                exit_requested = 1;
                break;
                
            case SDL_MOUSEMOTION:
                printf( "SDL_MOUSEMOTION %dx%d\n", event.motion.x, event.motion.y );
                break;
            
            case SDL_MOUSEBUTTONUP:
                // Uint8 type;     /**< SDL_JOYBUTTONDOWN or SDL_JOYBUTTONUP */
//         nn
                 printf( "SDL_MOUSEBUTTONUP type %d button %d %dx%d\n", event.button.type, event.button.button, event.button.x, event.button.y );
                 break;
            case SDL_MOUSEBUTTONDOWN:
                 printf( "SDL_MOUSEBUTTONDOWN type %d button %d %dx%d\n", event.button.type, event.button.button, event.button.x, event.button.y );
                 break;
      
            case SDL_JOYAXISMOTION:  // Handle Joystick Motion: Circle PAd i C-Stick
                printf("SDL_JOYAXISMOTION which %d axis %d val %d\n",event.jaxis.which, event.jaxis.axis, event.jaxis.value );
                // Up  (Circle Pad) / Up (C-Strick) axis3
                // Down  (Circle Pad) / Down (C-Strick) axis1/axis3
                if ( ( event.jaxis.value < -3200 ) || (event.jaxis.value > 3200 ) ) 
                {
                    if( event.jaxis.axis == 0) 
                    {
                        printf( "Left-right movement code goes here\n");
                    }
                    
                    if( event.jaxis.axis == 1) 
                    {
                        printf("Up-Down movement code goes here\b");
                    }
                }
                break;


            // Directional Pad Left/Righ + Up/Down apareix com event.type 9           
            case SDL_JOYHATMOTION:
// /opt/devkitpro/portlibs/3ds/include/SDL/SDL_joystick.h        
// /**
//  *  @name Hat Positions
//  *  The return value of SDL_JoystickGetHat() is one of the following positions:
//  */
// /*@{*/
// #define SDL_HAT_CENTERED        0x00 // Note that zero means the POV is centered
// #define SDL_HAT_UP              0x01
// #define SDL_HAT_RIGHT           0x02
// #define SDL_HAT_DOWN            0x04
// #define SDL_HAT_LEFT            0x08
// #define SDL_HAT_RIGHTUP         (SDL_HAT_RIGHT|SDL_HAT_UP)
// #define SDL_HAT_RIGHTDOWN       (SDL_HAT_RIGHT|SDL_HAT_DOWN)
// #define SDL_HAT_LEFTUP          (SDL_HAT_LEFT|SDL_HAT_UP)
// #define SDL_HAT_LEFTDOWN        (SDL_HAT_LEFT|SDL_HAT_DOWN)
                 printf("SDL_JOYHATBUTTO which %d hat %d val %d\n",event.jhat.which, event.jhat.hat, event.jhat.value);
//                  Directional Pad Left 8 Right 2 Up 1 Down 4
                 break;

            case SDL_JOYBUTTONDOWN:
                // 3DS builtin joypad con 10 botones <-- SDL_JoystickName(i), SDL_JoystickNumButtons(joystick))
                 printf("SDL_JOYBUTTONDOWN which %d button %d state %d\n",event.jbutton.which, event.jbutton.button, event.jbutton.state);

                    if (event.jbutton.button == 0) // Botón Start en la 3DS 
                        printf("Botón Start presionado\n");
                    else if (event.jbutton.button == 1) // Botón A en la 3DS 
                    // Realizar la acción deseada al presionar el botón A
                    // Por ejemplo, imprimir un mensaje
                        printf("Botón A presionado\n");
                    else if (event.jbutton.button == 2)  // Botón B en la 3DS
                        printf("Botón B presionado\n");
                    else if (event.jbutton.button == 3)  // Botón X en la 3DS
                        printf("Botón X presionado\n");
                    else if (event.jbutton.button == 4)  // Botón Y en la 3DS
                        printf("Botón Y presionado\n");
                    else if (event.jbutton.button == 5)  // Botón L - gatillo esquerre en la 3DS
                        printf("Botón y presionado\n");
                    else if (event.jbutton.button == 6)  // Botón R - gatillo dret en la 3DS
                        printf("Botón UP presionado\n");
                    else if (event.jbutton.button == 7)  // Botón Select en la 3DS
                        printf("Botón y presionado\n");
                    else if (event.jbutton.button == 8)  // Botón ZL - gatillo esquerre  en la 3DS
                        printf("Botón y presionado\n");
                    else if (event.jbutton.button == 9)  // Botón ZR - gatillo dret  en la 3DS
                        printf("Botón y presionado\n");                  
                    
                    break;
// /opt/devkitpro/portlibs/3ds/include/SDL/SDL_events.h
//  /** Joystick button event structure */
// typedef struct SDL_JoyButtonEvent {
//         Uint8 type;     /**< SDL_JOYBUTTONDOWN or SDL_JOYBUTTONUP */
//         Uint8 which;    /**< The joystick device index */
//         Uint8 button;   /**< The joystick button index */
//         Uint8 state;    /**< SDL_PRESSED or SDL_RELEASED */
// } SDL_JoyButtonEvent;

           case SDL_JOYBUTTONUP:
                printf("SDL_JOYBUTTONUP, botó %d\n", event.jbutton.button );
                    if (event.jbutton.button == 1)  // Botón A en la 3DS
                        printf("Botón A soltat\n");
                    break;
                                    
            case SDL_JOYBALLMOTION:  /* Handle Joyball Motion */
                printf("SDL_JOYBALLMOTION %d, \n", event.jball.ball );
                if( event.jball.ball == 0 )
                {
                    /* ball handling */
                }
                break;
            default: /* Report an unhandled event */
                printf("I don't know what this event is!\n");
                    
        }// switch        
    } //    if/while(SDL_PollEvent(&event))
        SDL_Delay(wait);
    }

    if (joystick != NULL )
        SDL_JoystickClose( joystick );
    SDL_Quit();
    romfsExit();
    return 0;
}
