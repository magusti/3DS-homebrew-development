#include <3ds.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

int main(int argc, char *argv[]) {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);

    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    
    
    romfsInit();

    Mix_Chunk *sound = Mix_LoadWAV("romfs:/test.wav"); //sound.wav");
    Mix_PlayChannel(-1, sound, 0);
    
    while (Mix_Playing(-1)) {
        SDL_Delay(1000);
    }
    
    Mix_FreeChunk(sound);
    Mix_CloseAudio();
    SDL_Quit();
    
    return 0;
}
