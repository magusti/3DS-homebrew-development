// Conversió a SDL 1.2.0 per a la 3DS de l'exemple gpusprites (per a 3DS con Citro2D)
//
// SDL 1.2 to 2.0 Migration Guide
// https://wiki.libsdl.org/SDL2/MigrationGuide
// Getting started with the SDL2 library for Game Development
// https://blog.conan.io/2023/07/20/introduction-to-game-dev-with-sdl2.html
//
//
//
// Simple citro2d sprite drawing example
// Images borrowed from:
//   https://kenney.nl/assets/space-shooter-redux
// #include <citro2d.h>

#include <3ds.h> //3dslinkstudio
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/resource.h>
#include <sys/unistd.h> // chdir
#include <malloc.h> // memalign



#include <SDL.h>
#include <SDL_image.h> // IMG_Load



#include <SDL_rotozoom.h> //rotozoomSurface; /usr/include/SDL/SDL_rotozoom.h --> SDL_gfx
 
#include <SDL_ttf.h> //TTF_Font, ...

#include "llistaSprintes.h" // els NSPRITES i llistaSprites

//PC
// #define MAX_SPRITES   768
// #define SCREEN_WIDTH  640
// #define SCREEN_HEIGHT 480
//3DS
#define MAX_SPRITES   33
//768
#define SCREEN_WIDTH  400
//320
#define SCREEN_HEIGHT 240
#define SCREEN_W 320
#define SCREEN_H 240

// Copie les estructures x als sprites mantenint el nom per minimitzar canvits durant la portabilitat

typedef struct {
struct {
   float   x;
   float   y;
   float   w;
   float   h;
} 	pos;
struct {
   float   x;
   float   y;
} 	center;
float 	depth;
float 	angle;
}  C2D_DrawParams;

typedef struct {
  SDL_Surface      *image;
  C2D_DrawParams    params;
} C2D_Sprite;

// Simple sprite struct
typedef struct {
    C2D_Sprite spr;
	float dx, dy; // velocity
} Sprite;


  static Sprite sprites[MAX_SPRITES];
  static size_t numSprites = 1; //MAX_SPRITES/2;
  // SDL1.2
  SDL_Surface *pantalla;

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
  
//     int col = 0, snd = 0;


static void deinitSprites() {

	for (size_t i = 0; i < MAX_SPRITES; i++)
	{
		SDL_FreeSurface( sprites[i].spr.image );
    }
}
//---------------------------------------------------------------------------------
static void initSprites() {
//---------------------------------------------------------------------------------
// 	size_t numImages = C2D_SpriteSheetCount(spriteSheet);
    size_t numImages = NSPRITES;
	srand(time(NULL));

	for (size_t i = 0; i < MAX_SPRITES; i++)
	{
		Sprite* sprite = &sprites[i];

		// Random image, position, rotation and speed
        sprite->spr.image = IMG_Load( llistaSprites[rand() % numImages] );
        printf("Carregant %d/%d\r", i, MAX_SPRITES );
        sprite->spr.params.center.x = 0.5f;
        sprite->spr.params.center.y = 0.5f;
        
        sprite->spr.params.pos.x = rand() % SCREEN_WIDTH;
        sprite->spr.params.pos.y = rand() % SCREEN_HEIGHT;
        
        sprite->spr.params.angle = rand()/(float)RAND_MAX;
		sprite->dx = rand()*4.0f/RAND_MAX - 2.0f;
		sprite->dy = rand()*4.0f/RAND_MAX - 2.0f;
	}
}

//---------------------------------------------------------------------------------
static void moveSprites() {
//---------------------------------------------------------------------------------

    SDL_Rect pos = { 0, 0, 0, 0 };
    int zoom = 1;
    Sprite *sprite;
    
    // Borra la pantalla, pintant de negre
     Uint32 colorDeFondo = SDL_MapRGB(pantalla->format, 0, 0, 0 );
     SDL_FillRect(pantalla, NULL, colorDeFondo);
    
    for (size_t i = 0; i < numSprites; i++)	{            
		sprite = &sprites[i];
       
        pos.x = sprite->spr.params.pos.x + sprite->dx;
        pos.y = sprite->spr.params.pos.y + sprite->dy;
        pos.w = sprite->spr.params.pos.w;
        pos.h = sprite->spr.params.pos.h;        
        //Actualitza-ho
        sprite->spr.params.pos.x = pos.x;
        sprite->spr.params.pos.y = pos.y;
        // Espera, no el pinte encara que l'he de rotar
        //         SDL_BlitSurface(sprite->spr.image, NULL, pantalla, &pos);        
        if (sprite->spr.params.angle < 350 )
            sprite->spr.params.angle += 10;
        else
            sprite->spr.params.angle = 0;
        
       // Rotar?
// https://www.ferzkopp.net/Software/SDL_gfx-2.0/Docs/html/index.html
        SDL_Surface* rotatedSprite = rotozoomSurface(sprite->spr.image, sprite->spr.params.angle, zoom, 0); // Rota el sprite
        SDL_BlitSurface(rotatedSprite, NULL, pantalla, &pos); // Dibuja el sprite rotado en la pantalla

    
		// Check for collision with the screen boundaries
		if ((sprite->spr.params.pos.x < sprite->spr.params.pos.w / 2.0f && sprite->dx < 0.0f) ||
			(sprite->spr.params.pos.x > (SCREEN_WIDTH-(sprite->spr.params.pos.w / 2.0f)) && sprite->dx > 0.0f))
			sprite->dx = -sprite->dx;

		if ((sprite->spr.params.pos.y < sprite->spr.params.pos.h / 2.0f && sprite->dy < 0.0f) ||
			(sprite->spr.params.pos.y > (SCREEN_HEIGHT-(sprite->spr.params.pos.h / 2.0f)) && sprite->dy > 0.0f))
			sprite->dy = -sprite->dy;
             
	}

}


SDL_Surface * render_text(SDL_Surface *renderer, const char* text, TTF_Font *font, 
                          SDL_Color color, SDL_Rect *rect) 
{
   SDL_Surface *surface;

    surface = TTF_RenderText_Solid(font, text, color);
    rect->w = surface->w;
    rect->h = surface->h;

    return surface;
}

SDL_Rect mensatges_rect = { 0, SCREEN_HEIGHT - 36, 0, 0 };
SDL_Surface *mensatges_tex = NULL;
SDL_Surface *pantalla = NULL;


#define SOC_ALIGN       0x1000
#define SOC_BUFFERSIZE  0x100000

static u32 *SOC_buffer = NULL;
s32 sock = -1, csock = -1;

// __attribute__((format(printf,1,2)))
// void failExit(const char *fmt, ...);

//---------------------------------------------------------------------------------
void failExit(const char *fmt, ...) {
//---------------------------------------------------------------------------------

        if(sock>0) close(sock);
        if(csock>0) close(csock);

        va_list ap;

        printf(CONSOLE_RED);
        va_start(ap, fmt);
        vprintf(fmt, ap);
        va_end(ap);
        printf(CONSOLE_RESET);
        printf("\nPress B to exit\n");

        while (aptMainLoop()) {
                gspWaitForVBlank();
                hidScanInput();

                u32 kDown = hidKeysDown();
                if (kDown & KEY_B) exit(0);
        }
}
//---------------------------------------------------------------------------------
void socShutdown() {
//---------------------------------------------------------------------------------
        printf("waiting for socExit...\n");
        socExit();

}

// int rand_range(int min, int max){
//    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
// }
// 

//---------------------------------------------------------------------------------
int main(int argc, char* argv[]) {
//---------------------------------------------------------------------------------
        int ret;
    int exit_requested = 0;
    SDL_Event event;
    Uint8 *keys;
    Uint32 start_time, stop_time, nCuadres, nTics;    
    clock_t start, end;
    double cpu_time_used;

    srand(time(NULL));
    romfsInit();
    chdir("romfs:/");
    
        // allocate buffer for SOC service
        SOC_buffer = (u32*)memalign(SOC_ALIGN, SOC_BUFFERSIZE);

        if(SOC_buffer == NULL) {
                failExit("memalign: failed to allocate\n");
        }

        // Now intialise soc:u service
        if ((ret = socInit(SOC_buffer, SOC_BUFFERSIZE)) != 0) {
        failExit("socInit: 0x%08X\n", (unsigned int)ret);
        }

        // register socShutdown to run at exit
        // atexit functions execute in reverse order so this runs before gfxExit
        atexit(socShutdown);
   link3dsStdio();

//     SDL_Init(SDL_INIT_VIDEO ); //|SDL_INIT_TIMER);
    SDL_Init(SDL_INIT_VIDEO|SDL_INIT_TIMER);
    SDL_ShowCursor( 0 ); // No vull que es veja
    
    // Create screens
    // SDL 1.2
    // Per similitut en gpusprites: 1 pantalla
    pantalla  = SDL_SetVideoMode(320, 240, 32, SDL_TOPSCR | SDL_CONSOLEBOTTOM | SDL_HWSURFACE); // 16?
    
    printf("pantalla = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, 32, SDL_DUALSCR | SDL_SWSURFACE);\n");
    
    IMG_Init(IMG_INIT_PNG); // Conter a les dependències: miara el Makefile que he habut de modificar
    TTF_Init();
    // load font from romfs
    TTF_Font* font = TTF_OpenFont("ttf/LeroyLetteringLightBeta01.ttf", 36);
    mensatges_tex = render_text(pantalla, "SDL 1.2 sprites!", font, colors[1], &mensatges_rect);

    SDL_BlitSurface(mensatges_tex, NULL, pantalla, &mensatges_rect );
    
    SDL_Flip( pantalla ); // Actualiza la pantalla
    
    //  // no need to keep the font loaded
//     TTF_CloseFont(font);
    printf("mensatges_tex = render_text(pantalla, SDL 1.2 sprites!...\n");

// 3DS SDL 1.2
    SDL_Rect f = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT*2};
    SDL_FillRect(pantalla, &f,  SDL_MapRGB(pantalla->format, 0, 0, 0) );


// 	// Load graphics
    // Initialize sprites
	initSprites();

	printf("\x1b[8;1HUp para añadir sprites.");
	printf("\x1b[9;1HDown para quitar sprites.");
   
   
    stop_time = nCuadres = nTics = 0;
    
	// Main loop
    while (!exit_requested) {
        start = clock();
//         start_time = SDL_GetTicks();         
        
		hidScanInput();
		// Respond to user input
		u32 kDown = hidKeysDown();
		if (kDown & KEY_START)
			break; // break in order to return to hbmenu
		u32 kHeld = hidKeysHeld();
		if ((kHeld & KEY_UP) && numSprites < MAX_SPRITES)
			numSprites++;
		if ((kHeld & KEY_DOWN) && numSprites > 1)
			numSprites--;

        while (SDL_PollEvent(&event)) {                                   
            const Uint8* keystates = SDL_GetKeyState(NULL);
            if(keystates[SDLK_UP]){
              if (numSprites < MAX_SPRITES) numSprites++;
            }
            if(keystates[SDLK_DOWN]){
              if (numSprites > 1) numSprites--;
            }
  		printf("\x1b[1;7 state %d == %d && event.key.keysym.sym %d == SDLK_UP %d\n",event.key.state, SDL_PRESSED, event.key.keysym.sym, SDLK_UP );
            if((event.key.state == SDL_PRESSED) && (event.key.keysym.sym  == SDLK_UP)){
                printf("Es repeteix SDLK_UP: numSprites \n");
              if (numSprites < MAX_SPRITES) numSprites++;
              printf("Es repeteix SDLK_UP: numSprites %u.\n", numSprites);
            }
            if((event.key.state == SDL_PRESSED) && (event.key.keysym.sym  == SDLK_DOWN)){
                printf("Es repeteix SDLK_DOWN\n");
              if (numSprites > 1) numSprites--;
            }
            
            switch( event.type ) {
// https://www.libsdl.org/release/SDL-1.2.15/docs/html/sdlkeyboardevent.html
// The type and state actually report the same information, they just use different values to do it! A keyboard event occurs when a key is released (type=SDK_KEYUP or state=SDL_RELEASED) and when a key is pressed (type=SDL_KEYDOWN or state=SDL_PRESSED). The information on what key was pressed or released is in the keysym structure.
                case SDL_KEYDOWN:
                    switch( event.key.keysym.sym ) {
//                         case SDLK_ESCAPE:
//                             exit_requested = 1; 
//                             break;
                        case SDLK_UP:
                            if (numSprites < MAX_SPRITES) numSprites++;
                            break;
                        case SDLK_DOWN:
                            if (numSprites > 1) numSprites--;
                            break;
                        default:
                            break;
                    } // switch( event.key.keysym.sym )
                    break;
                 case SDL_QUIT:
                    exit_requested = 1; 
                    break;
                 default:  
                     break;                                 
            } // switch( event.type ) 
        } //         while (SDL_PollEvent(&event))                    
 
		moveSprites();

		printf("\x1b[1;1HSprites: %zu/%u\x1b[K\n", numSprites, MAX_SPRITES);

		// Render the scene        
		for (size_t i = 0; i < numSprites; i ++) {
          SDL_Rect pos = { 0, 0, 0, 0 };
		  int zoom = 1;
          Sprite* sprite = &sprites[i];     
          pos.x = sprite->spr.params.pos.x;
          pos.y = sprite->spr.params.pos.y;
          pos.w = sprite->spr.params.pos.w;
          pos.h = sprite->spr.params.pos.h;     
          SDL_BlitSurface(sprite->spr.image, NULL, pantalla, &pos);
        }
        SDL_BlitSurface(mensatges_tex, NULL, pantalla, &mensatges_rect); 

        // Refresca la pantalla
        SDL_Flip( pantalla ); // Actualiza la pantalla
        nCuadres++;

        SDL_Delay( 25 );
    } // while (!exit_requested) {

	// Delete graphics
    deinitSprites();
    
 
// no need to keep the font loaded
    TTF_CloseFont(font);

    if ( mensatges_tex )
        SDL_FreeSurface( mensatges_tex );
    if (pantalla)
        SDL_FreeSurface( pantalla );

    IMG_Quit();
    TTF_Quit(); // Undefinet reference

    SDL_FreeSurface( pantalla ); // https://www.libsdl.org/release/SDL-1.2.15/docs/html/index.html

    SDL_Quit();

    return 0;
}
