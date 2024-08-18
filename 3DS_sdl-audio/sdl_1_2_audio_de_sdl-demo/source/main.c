// #include "SDL/SDL.h"
// // #include "SDL/SDL_thread.h"
// 
// static Uint8 *audio_chunk;
// static Uint32 audio_len;
// static Uint8 *audio_pos;
// 
// void fill_audio(void *udata, Uint8 *stream, int len)
// {
//         /* Only play if we have data left */
//         if ( audio_len == 0 )
//             return;
// 
//         /* Mix as much data as possible */
//         len = ( len > audio_len ? audio_len : len );
//         SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
//         audio_pos += len;
//         audio_len -= len;
// }
// 
// long fileLoad(const char * filename, unsigned char * * buffer) {
//     FILE * pFile;
//     long lSize;
//   
//     pFile = fopen(filename, "rb");
//     if (pFile != NULL) {
//         fseek(pFile, 0, SEEK_END);
//         lSize = ftell(pFile);
//         rewind(pFile);
//         *buffer = (unsigned char *)malloc(lSize);
//         if (buffer != NULL) {
//             return fread(*buffer, 1, lSize, pFile);
//         }
//         fclose(pFile);
//     }
//     return 0;
// }
// 
// int main(int argc, char **argv)
// {
//     SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
//     SDL_Surface *screen;
// //     SDL_Surface *bitmap;
//   
// // Es necesita????
// //     SDL_Thread *thread1, *thread2;
// //     int threadReturnValue;
//   
//     screen = SDL_SetVideoMode(400, 240, 32, SDL_SWSURFACE | SDL_TOPSCR | 
//             SDL_CONSOLEBOTTOM);
//   
//     romfsInit();
//     audio_len = fileLoad("romfs:/test.wav", &audio_chunk);
//     audio_pos = audio_chunk;
//     printf("Ready to play\n");
//   
//     SDL_AudioSpec audioSpec;
//   
// // //     file /usr/share/sounds/speech-dispatcher/test.wav romfs/
// // //      RIFF (little-endian) data, WAVE audio, Microsoft PCM, 16 bit, mono 16000 Hz
// // 
// // //   file  audio_zephray/zephray_SDL_Example_audio/romfs/test.wav: RIFF (little-endian) data, WAVE audio, Microsoft PCM, 16 bit, stereo 22050 Hz
// //     audioSpec.freq = 22050;
// //     audioSpec.format = AUDIO_S16;
// //     audioSpec.channels = 2;
// //     audioSpec.samples = 2048;
// //     audioSpec.callback = fill_audio;
// //     audioSpec.userdata = NULL;
// // 
// // //     audio_len = fileLoad("romfs:/test2.wav", &audio_chunk);
// // //     audio_pos = audio_chunk;
// // //     printf("Ready to play\n");
// // //   
// // //     SDL_AudioSpec audioSpec;
// // // $  file  /usr/share/sounds/speech-dispatcher/test.wav 
// // // /usr/share/sounds/speech-dispatcher/test.wav: RIFF (little-endian) data, WAVE audio, Microsoft PCM, 16 bit, mono 16000 Hz
// // //     audioSpec.freq = 16000;
// // //     audioSpec.format = AUDIO_S16;
// // //     audioSpec.channels = 1;
// // //     audioSpec.samples = 2048;
// // //     audioSpec.callback = fill_audio;
// // //     audioSpec.userdata = NULL;
// // 
// // 
// //     if (SDL_OpenAudio(&audioSpec, NULL) < 0) {
// //         printf("Sound initialization failed.\n");
// //     }
// //     
// //     
//     Uint32 wav_length;
// Uint8 *wav_buffer;
// 
// /* Load the WAV */
// if( SDL_LoadWAV("romfs:/test.wav", &audioSpec, &wav_buffer, &wav_length) == NULL ){
//   fprintf(stderr, "Could not open test.wav: %s\n", SDL_GetError());
// //   exit(-1);
// }
// else
//     printf("Carregat %s de %ldbytes\n", "romfs:/test.wav", wav_length);
// 
//     // Abrir el dispositivo de audio
//  if (SDL_OpenAudio(&audioSpec, NULL) < 0) {
//         printf("Error al abrir el dispositivo de audio: %s\n", SDL_GetError());
//         SDL_FreeWAV(wav_buffer);
//  }
//  else
//      printf("SDL_OpenAudio frec %d, canals %d, mostres $d\n", audioSpec.freq, audioSpec.channels, audioSpec.samples );
//         
// SDL_PauseAudio(0);
// // SDL_MixAudio(Uint8 *dst, Uint8 *src, Uint32 len, int volume);
// // SDL_Delay(10000);
//     while ( (SDL_GetAudioStatus() == SDL_AUDIO_PLAYING) )
// 	{
// 		SDL_Delay(1000);
//         printf("esperem\n");
// 	}
// 
// printf("seguim\n");
//    SDL_FreeWAV(wav_buffer);
//    
//     SDL_PauseAudio(0);
//     while (audio_len > 0) {
//         printf("Playing: %lu left \n", audio_len);
//         SDL_Delay(1000);
//     }
//     free(audio_chunk);
//     
//     SDL_Delay(10000);
//     SDL_Quit();
//   
//     return 0;
// }

