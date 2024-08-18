#include <3ds.h>
#include <stdio.h>
#include <SDL/SDL.h>

// https://www.ecosia.org/chat?addon=firefox&addonversion=4.1.0&q=Play%20WAVE%20file%20with%20SDL%201.2

void audioCallback(void* userdata, Uint8* stream, int len) {
    SDL_RWops* rw = (SDL_RWops*)userdata;
    SDL_RWread(rw, stream, 1, len);
}

int main(int argc, char *argv[]) {
    SDL_Surface *screen;
    SDL_AudioSpec wavSpec;
    Uint8* wavBuffer;
    Uint32 wavLength;
  
    SDL_Init(SDL_INIT_AUDIO);
      screen = SDL_SetVideoMode(400, 240, 32, SDL_SWSURFACE | SDL_TOPSCR | 
             SDL_CONSOLEBOTTOM);
   
        romfsInit();

    
    if (SDL_LoadWAV("romfs:/test.wav", &wavSpec, &wavBuffer, &wavLength) == NULL) {
        printf("Error en SDL_LoadWAV: %s\n","romfs:/test.wav");
    }
    else
        printf("SDL_LoadWAV: %s --> frec %d, canales %d y muestras %d\n",
               "romfs:/test.wav", wavSpec.freq, wavSpec.channels, wavSpec.samples );
    
//     SDL_OpenAudio(&wavSpec, NULL); ESte no val ???
    SDL_AudioSpec obtainedSpec;
    SDL_AudioSpec desiredSpec;
    desiredSpec.freq = wavSpec.freq;
    desiredSpec.format = wavSpec.format;
    desiredSpec.channels = wavSpec.channels;
    desiredSpec.samples = 2048;
    desiredSpec.callback = audioCallback;
    desiredSpec.userdata = SDL_RWFromConstMem(wavBuffer, wavLength);

    SDL_OpenAudio(&desiredSpec, &obtainedSpec);

    SDL_PauseAudio(0);
    printf("espere un poc");
    SDL_Delay(10000);
//     SDL_Delay( wavLength / (wavSpec.freq * wavSpec.channels * (SDL_AUDIO_BITSIZE(wavSpec.format) / 8))); // Error: SDL_AUDIO_BITSIZE
    
    SDL_FreeWAV(wavBuffer);
    SDL_Quit();
    
    return 0;
}


