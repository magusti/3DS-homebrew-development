/*
  *  Portant l'exemple de Switch sdl-demo (SDL 2.0)  a 3DS (SDL 1.2)... El que es puga!!!
  * 
  * http://gamedevgeek.com/tutorials/getting-started-with-sdl/
  * https://www.libsdl.org/release/SDL-1.2.15/docs/html/index.html
  * https://github.com/zephray/SDL-1.2-N3DS/tree/master
  * 
  * SDL_image 1.2 <https://www.libsdl.org/projects/old/SDL_image/release-1.2.html>
  * SDL_mixer 1.2 <https://www.libsdl.org/projects/old/SDL_mixer/release-1.2.html>
  * SDL_net 1.2 <https://www.libsdl.org/projects/old/SDL_net/docs/index.html>
  * SDL_TTF 1.2 <https://www.libsdl.org/projects/old/SDL_ttf/release-1.2.html>
  * SDL_rtf <https://github.com/libsdl-org/SDL_rtf>
  * 
  * 
  $ /opt/devkitpro/portlibs/3ds/bin/sdl-config --cflags
-I/opt/devkitpro/portlibs/3ds/include/SDL -D_GNU_SOURCE=1 -ffunction-sections -fdata-sections -march=armv6k -mtune=mpcore -mfloat-abi=hard -mword-relocations -I/opt/devkitpro/libctru/include -DARM11 -D_3DS
  
$ /opt/devkitpro/portlibs/3ds/bin/sdl-config --libs
-L/opt/devkitpro/portlibs/3ds/lib -march=armv6k -mfloat-abi=hard -L/opt/devkitpro/portlibs/3ds -lSDL -L/opt/devkitpro/libctru/lib -lcitro3d -lctru -lm

NO ES PROU per a les PORTLIBS!!!!

  * sox input.wav -r 22050 output.wav
  No es nota, però tin-ho a ma.
  
  */
/* Mini SDL Demo
 * featuring SDL2 + SDL2_mixer + SDL2_image + SDL2_ttf
 * on Nintendo Switch using libnx
 *
 * Copyright 2018 carsten1ns
 *           2020 WinterMute
 *
 * Permission to use, copy, modify, and/or distribute this software for any
 * purpose with or without fee is hereby granted, provided that the above
 * copyright notice and this permission notice appear in all copies.
 *
 * THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
 * WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
 * MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
 * ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
 * WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
 * ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
 * OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
 *
 */

#include <time.h>
#include <unistd.h>

#include <SDL.h> //https://github.com/nop90/SDL-3DS /https://github.com/nop90/SDL-3DS
#include <SDL_mixer.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
// #include <switch.h>
#include <3ds.h>

// portlibs/3ds/include/freetype2/freetype/freetype.h
// portlibs/3ds/include/freetype2/freetype/config/ftheader.h
// portlibs/3ds/include/freetype2/freetype/config/ftconfig.h
// portlibs/3ds/include/freetype2/freetype/ftmodapi.h

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

// #define SCREEN_W 1280
#define SCREEN_W 320
// #define SCREEN_H 720
#define SCREEN_H 240

// SDL_Texture * render_text(SDL_Renderer *renderer, const char* text, TTF_Font *font, SDL_Color color, SDL_Rect *rect) 
SDL_Surface * render_text(SDL_Surface *renderer, const char* text, TTF_Font *font, SDL_Color color, SDL_Rect *rect) 
{
    SDL_Surface *surface;
//     SDL_Texture *texture;
//     SDL_Surface *texture;

    surface = TTF_RenderText_Solid(font, text, color);
//     texture = SDL_CreateTextureFromSurface(renderer, surface);
    rect->w = surface->w;
    rect->h = surface->h;

//     SDL_FreeSurface(surface);
//     return texture;
    return surface;
}

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

//     SDL_Texture *switchlogo_tex = NULL, *sdllogo_tex = NULL, *helloworld_tex = NULL;
//     SDL_Surface *switchlogo_tex = NULL, *sdllogo_tex = NULL, 
    SDL_Surface *helloworld_tex = NULL;
    SDL_Rect pos = { 0, 0, 0, 0 }, sdl_pos = { 0, 0, 0, 0 };
    Mix_Music *music = NULL;
    Mix_Chunk *sound[4] = { NULL };
    SDL_Event event;

    SDL_Color colors[] = {
        { 128, 128, 128, 0 }, // gray
        { 255, 255, 255, 0 }, // white
        { 255, 0, 0, 0 },     // red
        { 0, 255, 0, 0 },     // green
        { 0, 0, 255, 0 },     // blue
        { 255, 255, 0, 0 },   // brown
        { 0, 255, 255, 0 },   // cyan
        { 255, 0, 255, 0 },   // purple
    };
    int col = 0, snd = 0;

    srand(time(NULL));
    int vel_x = rand_range(1, 5);
    int vel_y = rand_range(1, 5);

    romfsInit();
    chdir("romfs:/");

    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
//     SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO); Inicialitza l'audio més abaix.
    SDL_ShowCursor( 0 ); // No vull que es veja; damunt, no es pot gastar!

    Mix_Init(MIX_INIT_OGG); //https://www.libsdl.org/projects/old/SDL_mixer/docs/SDL_mixer_frame.html
    IMG_Init(IMG_INIT_PNG); // Conter a les dependències: miara el Makefile que he habut de modificar
    TTF_Init();

//     SDL_Window* window = SDL_CreateWindow("sdl2+mixer+image+ttf demo", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_W, SCREEN_H, SDL_WINDOW_SHOWN);
//     SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_SOFTWARE);
    SDL_Surface *screen; // És la pantalla (el renderer en SDL 2.9).
//     pantallaSuperior = SDL_SetVideoMode(w, h, 8, SDL_TOPSCR | SDL_CONSOLEBOTTOM | SDL_SWSURFACE);
//     screen = SDL_SetVideoMode(400, 320, 16, SDL_TOPSCR | SDL_CONSOLEBOTTOM | SDL_HWSURFACE); //SDL_DOUBLEBUF | SDL_SWSURFACE | SDL_TOPSCR | SDL_CONSOLEBOTTOM);
    screen = SDL_SetVideoMode(320, 240, 16, SDL_TOPSCR | SDL_CONSOLEBOTTOM | SDL_HWSURFACE); //SDL_DOUBLEBUF | SDL_SWSURFACE | SDL_TOPSCR | SDL_CONSOLEBOTTOM);
    
//     IMG_Init(IMG_INIT_PNG); // carregar el soport per  aPNG J aestà dalt

    // load logos from file
    SDL_Surface *sdllogo = IMG_Load("data/sdl.png");
//     SDL_Surface *sdllogo = SDL_LoadBMP("data/sdl.bmp");  // 1.2 carrega no més BMP o això és la statndard library
    if (sdllogo) {
        sdl_pos.w = sdllogo->w;
        sdl_pos.h = sdllogo->h;
//         sdllogo_tex = SDL_CreateTextureFromSurface(renderer, sdllogo);
        SDL_BlitSurface(sdllogo, NULL, screen, NULL);
//         SDL_FreeSurface(sdllogo);
    }


    SDL_Surface *switchlogo = IMG_Load("data/switch.png");
//     SDL_Surface *switchlogo = SDL_LoadBMP("data/switchlogo.bmp");
    if (switchlogo) {
        pos.x = SCREEN_W / 2 - switchlogo->w / 2;
        pos.y = SCREEN_H / 2 - switchlogo->h / 2;
        pos.w = switchlogo->w;
        pos.h = switchlogo->h;
//         switchlogo_tex = SDL_CreateTextureFromSurface(renderer, switchlogo);
        SDL_BlitSurface(switchlogo, NULL, screen, NULL);
//         SDL_FreeSurface(switchlogo);
    }

    col = rand_range(0, 7);

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
    
    // load font from romfs
    TTF_Font* font = TTF_OpenFont("data/LeroyLetteringLightBeta01.ttf", 36);
// No hem fet res de control d'errors!!!
//     if (font == NULL) {
//      printf("Error: la font %s no es carrega!\n", "data/LeroyLetteringLightBeta01.ttf");
//     } else {
//      printf("Carregant la font %s!\n", "data/LeroyLetteringLightBeta01.ttf");        
//     }
    // render text as texture
    SDL_Rect helloworld_rect = { 0, SCREEN_H - 36, 0, 0 };
//     helloworld_tex = render_text(renderer, "Hello, world!", font, colors[1], &helloworld_rect);
//     https://thenumb.at/cpp-course/sdl2/07/07.html
//  SDL_Color color = { 0, 0, 0 };
// text = TTF_RenderText_Solid( font, "Hello World!", color );
    helloworld_tex = render_text(screen, "Hello, world!", font, colors[1], &helloworld_rect);

    // no need to keep the font loaded
    TTF_CloseFont(font);

    SDL_InitSubSystem(SDL_INIT_AUDIO);
    Mix_AllocateChannels(5);
//     Mix_OpenAudio(48000, AUDIO_S16, 2, 4096);
    Mix_OpenAudio(22050/2, AUDIO_S16, 2, 2048);



    // load music and sounds from files
    music = Mix_LoadMUS("data/background.ogg");
    sound[0] = Mix_LoadWAV("data/pop1.wav");
    sound[1] = Mix_LoadWAV("data/pop2.wav");
    sound[2] = Mix_LoadWAV("data/pop3.wav");
    sound[3] = Mix_LoadWAV("data/pop4.wav");
    if (music)
        Mix_PlayMusic(music, -1);
    
    while (!exit_requested
//         && appletMainLoop()
        && aptMainLoop()
        ) {
// Ací sí la pille                 
//                 hidScanInput();
//                 u32 kDown = hidKeysDown();        
//                 if (kDown & KEY_B)  printf("La B, dins\n");
        while (SDL_PollEvent(&event)) {  // <->     while ( SDL_WaitEvent(&event) >= 0 ) que bloquea hasta la llegada de un evento
//                 hidScanInput();
//                 kDown = hidKeysDown();        
//                 if (kDown & KEY_B)  printf("La B, dins\n");

                //             if (event.type == SDL_QUIT)
//                 exit_requested = 1;
//             // use joystick
//             if (event.type == SDL_JOYBUTTONDOWN) {
//                 if (event.jbutton.button == JOY_UP)
//                     if (wait > 0)
//                         wait--;
//                 if (event.jbutton.button == JOY_DOWN)
//                     if (wait < 100)
//                         wait++;
// 
//                 if (event.jbutton.button == JOY_PLUS)
//                     exit_requested = 1;
// 
//                 if (event.jbutton.button == JOY_B)
//                     trail =! trail;
//             }
             printf("event.type %d == %d %d %d %d %d???\n", event.type, SDL_QUIT, SDL_JOYBUTTONDOWN, SDL_KEYUP, SDL_MOUSEBUTTONUP, SDL_MOUSEMOTION );

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
//     printf("Este aplega?\n");

        // set position and bounce on the walls
        pos.y += vel_y;
        pos.x += vel_x;
        if (pos.x + pos.w > SCREEN_W) {
            pos.x = SCREEN_W - pos.w;
            vel_x = -rand_range(1, 5);
            col = rand_range(0, 4);
            snd = rand_range(0, 3);
            if (sound[snd])
                Mix_PlayChannel(-1, sound[snd], 0);
        }
        if (pos.x < 0) {
            pos.x = 0;
            vel_x = rand_range(1, 5);
            col = rand_range(0, 4);
            snd = rand_range(0, 3);
//             if (sound[snd])
//                 Mix_PlayChannel(-1, sound[snd], 0);
        }
        if (pos.y + pos.h > SCREEN_H) {
            pos.y = SCREEN_H - pos.h;
            vel_y = -rand_range(1, 5);
            col = rand_range(0, 4);
            snd = rand_range(0, 3);
            if (sound[snd])
                Mix_PlayChannel(-1, sound[snd], 0);
        }
        if (pos.y < 0) {
            pos.y = 0;
            vel_y = rand_range(1, 5);
            col = rand_range(0, 4);
            snd = rand_range(0, 3);
            if (sound[snd])
                Mix_PlayChannel(-1, sound[snd], 0);
        }

        if (!trail) {
//             SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
//             SDL_RenderClear(renderer);

//            SDL_Rect screen_rect = { 0, 0, SCREEN_W, SCREEN_H };
           Uint32 colorDeFondo = SDL_MapRGB(switchlogo->format, 0, 0, 0);
           SDL_FillRect(screen, NULL, colorDeFondo);
            // Pero pinta tot el rectangle, no més vol canbiar el color de primer pla?
            //             // Definir el color que deseas aplicar (en este caso, rojo)
//             Uint32 deColor = SDL_MapRGB(switchlogo->format, colors[col].r, colors[col].g, colors[col].b);
//             // Rellenar la superficie temporal con el color rojo
//             SDL_FillRect(switchlogo, NULL, deColor);            
        }

        // put logos on screen
//         if (sdllogo_tex)
//             SDL_RenderCopy(renderer, sdllogo_tex, NULL, &sdl_pos);
        // Pq és el primer es queda sempre per damunt???
        if (sdllogo)
            SDL_BlitSurface(sdllogo, NULL, screen, &sdl_pos);

//         if (switchlogo_tex) {
//             SDL_SetTextureColorMod(switchlogo_tex, colors[col].r, colors[col].g, colors[col].b);
//             SDL_RenderCopy(renderer, switchlogo_tex, NULL, &pos);
        if (switchlogo) {//docencia/2k23-2k24/docenciaEnXarxa/articles/exemplesPortabilitat_SDL/3DS_SDL_1_2/sdl_sprites
            SDL_BlitSurface(switchlogo, NULL, screen, &pos);

        }
        
//         // put text on screen
        if (helloworld_tex)
//             SDL_RenderCopy(renderer, helloworld_tex, NULL, &helloworld_rect);
               SDL_BlitSurface(helloworld_tex, NULL, screen, &helloworld_rect);

//         SDL_RenderPresent(renderer);
        SDL_Flip(screen);

        SDL_Delay(wait);
    }

//     // clean up your textures when you are done with them
//     if (sdllogo_tex)
//         SDL_DestroyTexture(sdllogo_tex);
// 
//     if (switchlogo_tex)
//         SDL_DestroyTexture(switchlogo_tex);
// 
    if (sdllogo)
        SDL_FreeSurface(sdllogo);
    if (switchlogo)
        SDL_FreeSurface(switchlogo);
   
//     if (helloworld_tex)
//         SDL_DestroyTexture(helloworld_tex);

//     // stop sounds and free loaded data
    Mix_HaltChannel(-1);
    Mix_FreeMusic(music);
    for (snd = 0; snd < 4; snd++)
        if (sound[snd])
            Mix_FreeChunk(sound[snd]);

    IMG_Quit();
    Mix_CloseAudio();
    TTF_Quit(); // Undefinet reference
    Mix_Quit();
    
    SDL_Quit();
    romfsExit();
    return 0;
}
