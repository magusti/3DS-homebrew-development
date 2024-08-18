/* 

// SDL 1.2 audio para 3DS
// Adaptació del exemple de https://github.com/zephray/SDL-1.2-N3DS
//

#include <3ds.h>
#include <stdio.h>
// #include "SDL/SDL.h"
#include <SDL.h> //https://github.com/nop90/SDL-3DS /https://github.com/nop90/SDL-3DS

#define SCREEN_W 320
#define SCREEN_H 240


int main(int argc, char **argv)
{
    SDL_Init(SDL_INIT_VIDEO);
    SDL_Surface *screen;
    SDL_Surface *bitmap;
  
    screen = SDL_SetVideoMode(SCREEN_W, SCREEN_H, 16, SDL_SWSURFACE | SDL_TOPSCR | 
            SDL_CONSOLEBOTTOM);
  
    Result rs = romfsInit();
    if (rs)
        printf("romfsInit: %08lx\n", rs);
    else {
        printf("romfs Initialization succeed.\n");
        bitmap = SDL_LoadBMP("romfs:/test.bmp");
        if (bitmap == NULL)
            printf("Open Bitmap failed!\n");
        else
            SDL_BlitSurface(bitmap, NULL, screen, NULL);
    }
    printf("Should be bilted\n");
    SDL_Flip(screen);
    printf("Should be flipped\n");
    SDL_Delay(2000);
    SDL_Quit();
  
    return 0;
}
*/

// /*
//   *  Portant l'exemple de Switch sdl-demo (SDL 2.0)  a 3DS (SDL 1.2)... El que es puga!!!
//   * 
//   * http://gamedevgeek.com/tutorials/getting-started-with-sdl/
//   * https://www.libsdl.org/release/SDL-1.2.15/docs/html/index.html
//   * https://github.com/zephray/SDL-1.2-N3DS/tree/master
//   * 
//   * SDL_image 1.2 <https://www.libsdl.org/projects/old/SDL_image/release-1.2.html>
//   * SDL_mixer 1.2 <https://www.libsdl.org/projects/old/SDL_mixer/release-1.2.html>
//   * SDL_net 1.2 <https://www.libsdl.org/projects/old/SDL_net/docs/index.html>
//   * SDL_TTF 1.2 <https://www.libsdl.org/projects/old/SDL_ttf/release-1.2.html>
//   * SDL_rtf <https://github.com/libsdl-org/SDL_rtf>
//   * 
//   * 
//   $ /opt/devkitpro/portlibs/3ds/bin/sdl-config --cflags
// -I/opt/devkitpro/portlibs/3ds/include/SDL -D_GNU_SOURCE=1 -ffunction-sections -fdata-sections -march=armv6k -mtune=mpcore -mfloat-abi=hard -mword-relocations -I/opt/devkitpro/libctru/include -DARM11 -D_3DS
//   
// $ /opt/devkitpro/portlibs/3ds/bin/sdl-config --libs
// -L/opt/devkitpro/portlibs/3ds/lib -march=armv6k -mfloat-abi=hard -L/opt/devkitpro/portlibs/3ds -lSDL -L/opt/devkitpro/libctru/lib -lcitro3d -lctru -lm
// 
// NO ES PROU per a les PORTLIBS!!!!
// 
//   * sox input.wav -r 22050 output.wav
//   No es nota, però tin-ho a ma.
//   
//   */
// /* Mini SDL Demo
//  * featuring SDL2 + SDL2_mixer + SDL2_image + SDL2_ttf
//  * on Nintendo Switch using libnx
//  *
//  * Copyright 2018 carsten1ns
//  *           2020 WinterMute
//  *
//  * Permission to use, copy, modify, and/or distribute this software for any
//  * purpose with or without fee is hereby granted, provided that the above
//  * copyright notice and this permission notice appear in all copies.
//  *
//  * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
//  * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
//  * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
//  * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
//  * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
//  * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
//  * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
//  *
//  */
// 
#include <time.h>
#include <unistd.h>

#include <SDL.h> //https://github.com/nop90/SDL-3DS /https://github.com/nop90/SDL-3DS
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <3ds.h>

//TOP
#define SCREEN_W 400
#define SCREEN_H 240
// BOTTOM
// #define SCREEN_W 320
// #define SCREEN_H 240


int rand_range(int min, int max){
   return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

//
// https://wiki.libsdl.org/SDL2/GuiaDeMigracion
//
int main(int argc, char** argv) {
    int exit_requested = 0;
    int trail = 0;
    int wait = 0; //12; //25;

    SDL_Surface *screen = NULL;
    SDL_Rect pos = { 0, 0, 0, 0 }, sdl_pos = { 0, 0, 0, 0 };
    Mix_Music *music = NULL;
    Mix_Chunk *sound[4] = { NULL };
    SDL_Event event;

    int col = 0, snd = 0;

    srand(time(NULL));

    romfsInit();
    chdir("romfs:/");

    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
//     SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); Inicialitza l'audio més abaix.
    SDL_ShowCursor( 0 ); // No vull que es veja; damunt, no es pot gastar!

    Mix_Init(MIX_INIT_OGG); //https://www.libsdl.org/projects/old/SDL_mixer/docs/SDL_mixer_frame.html

    screen = SDL_SetVideoMode(320, 240, 16, SDL_TOPSCR | SDL_CONSOLEBOTTOM | SDL_HWSURFACE); 
    

//     SDL_InitSubSystem(SDL_INIT_JOYSTICK);
//     SDL_JoystickEventState(SDL_ENABLE);
//     SDL_JoystickOpen(0);

// Pot ser interesant
//     Uint32 then, now;
//     then = SDL_GetTicks();
//     now = SDL_GetTicks();
// 	printf("Conversion Time: %d milliseconds\n", now-then);
    
// if     (! TTF_Init() )// JA estava dalt.
//     printf("TTF_init Ok\n");
// else
//     printf("TTF_init Error\n");
    

    SDL_InitSubSystem(SDL_INIT_AUDIO);
    Mix_AllocateChannels(5);
//     Mix_OpenAudio(48000, AUDIO_S16, 1, 4096); // Original
//     Mix_OpenAudio(44100, AUDIO_S16, 2, 4096);
    Mix_OpenAudio(22050, AUDIO_S16, 2, 2048);

    // load music and sounds from files
    music = Mix_LoadMUS("data/background.ogg");
    sound[0] = Mix_LoadWAV("data/typewriterbell.wav"); //pop1_original.wav");
    sound[1] = Mix_LoadWAV("data/pop2.wav");
    sound[2] = Mix_LoadWAV("data/pop3.wav");
    sound[3] = Mix_LoadWAV("data/pop4.wav");
    if (music) {
//         Mix_PlayMusic(music, -1);
        printf("Mix_PlayMusic de %s\n", "data/background.ogg");
    }
    
    
    
    snd = 0;
    Mix_PlayChannel(-1, sound[snd], 1);
    printf("1er Mix_PlayChannel de %d\n", snd);
    
    SDL_LoadWAV ("test.wav", &wav_spec, &wav_buffer, &wav_length) == NULL ){
    
    SDL_Delay(3000);
    
    
    
    while (!exit_requested
//         && appletMainLoop()
        && aptMainLoop()
        ) {
        while (SDL_PollEvent(&event)) {  // <->     while ( SDL_WaitEvent(&event) >= 0 ) que bloquea hasta la llegada de un evento
             switch(event.type){  /* Process the appropiate event type */
              case SDL_QUIT:
                exit_requested = 1;
                break;
              case SDL_KEYDOWN: //SDL_KEYUP: //SDL_BlitSurface:  /* Handle a KEYDOWN event */         
                printf("Oh! Key press, %d %c\n", event.key.keysym.sym, event.key.keysym.scancode);
                switch(event.key.keysym.sym){  
                    case SDLK_UP:
                      if (wait > 0)  wait--;
                      printf("Wait? %d\n", wait);
                    break;
                    case SDLK_DOWN:
                      if (wait < 100) wait++;
                      printf("Wait? %d\n", wait);                      
                    break;                    
                    case SDLK_b: // SDLK_B no està, com tampoc SDL_sound, com diu en https://github.com/nop90/SDL-3DS
                        trail =! trail;
                        printf("Deixar l'estela? %d\n", trail);
                        break;
                    default:
                        break;                    
                }
                break;
               case SDL_MOUSEBUTTONUP:  // SDL_MOUSEBUTTONDOWN
                printf("Oh! el ratolí botó %d estat %d coords. %d,%d\n", event.button.button, event.button.state, event.button.x, event.button.y );
//                 if (event.stated == SDL_PRESSED) && ((event.keysym, event.keysym);
//        https://www.libsdl.org/release/SDL-1.2.15/docs/html/guideeventexamples.html         
                        trail =! trail;
                        printf("Deixar l'estela? %d\n", trail);
                 break;
               case SDL_MOUSEMOTION:
                         printf("We got a motion event.\n");
      printf("Current mouse position is: (%d, %d)\n", event.motion.x, event.motion.y);

                   break;
               default: /* Report an unhandled event */
                 printf("I don't know what this event is!\n");                 
               }
            
        }

        // set position and bounce on the walls
//         pos.y += vel_y;
//         pos.x += vel_x;
//         if (pos.x + pos.w > SCREEN_W) {
//             pos.x = SCREEN_W - pos.w;
//             vel_x = -rand_range(1, 5);
//             col = rand_range(0, 4);
//             snd = rand_range(0, 3);
//             if (sound[snd])
//                 Mix_PlayChannel(-1, sound[snd], 0);
//         }
//         if (pos.x < 0) {
//             pos.x = 0;
//             vel_x = rand_range(1, 5);
//             col = rand_range(0, 4);
//             snd = rand_range(0, 3);
//             if (sound[snd])
//                 Mix_PlayChannel(-1, sound[snd], 0);
//         }
//         if (pos.y + pos.h > SCREEN_H) {
//             pos.y = SCREEN_H - pos.h;
//             vel_y = -rand_range(1, 5);
//             col = rand_range(0, 4);
//             snd = rand_range(0, 3);
//             if (sound[snd])
//                 Mix_PlayChannel(-1, sound[snd], 0);
//         }
//         if (pos.y < 0) {
//             pos.y = 0;
//             vel_y = rand_range(1, 5);
//             col = rand_range(0, 4);
//             snd = rand_range(0, 3);
//             if (sound[snd])
//                 Mix_PlayChannel(-1, sound[snd], 0);
//         }

           snd = rand_range(0, 3);
           snd = 0;
           Mix_PlayChannel(-1, sound[snd], 1);
           printf("Mix_PlayChannel de %d\n", snd);



//         SDL_RenderPresent(renderer);
        SDL_Flip(screen);

        SDL_Delay(wait);
    }

//     // stop sounds and free loaded data
    Mix_HaltChannel(-1);
    Mix_FreeMusic(music);
    for (snd = 0; snd < 4; snd++)
        if (sound[snd])
            Mix_FreeChunk(sound[snd]);

    Mix_CloseAudio();
    Mix_Quit();
    
    SDL_Quit();
    romfsExit();
    return 0;
}
