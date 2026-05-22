#include <3ds.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
// #include <console.h> //consoleClear

// Definiciones
#define SCREEN_WIDTH 40 // Ancho de la pantalla de texto (aproximado)
#define SCREEN_HEIGHT 30 // Alto de la pantalla de texto (aproximado)
// 40, parpadeja; 30 tb
#define MAX_STREAMS 20
#define MIN_STREAM_LENGTH 5
#define MAX_STREAM_LENGTH 15
#define FALL_SPEED 1
#define FRAME_DELAY 16666 // Microsegundos (aproximadamente 60 FPS)

// Estructura para representar una "gotera" de caracteres
typedef struct {
    int column;
    int length;
    int position; // Posición vertical de la cabeza de la corriente
    int speed;
} Stream;

// Genera un carácter ASCII imprimible aleatorio
char getRandomChar() {
    return (rand() % 94) + 33; // Rango ASCII imprimible (33 a 126)
}

// Función para imprimir un carácter con color y posición usando secuencias de escape ANSI
void printColoredChar(PrintConsole* console, int x, int y, char ch, int color) {
    consoleSelect(console);
    printf("\x1b[%d;%dH\x1b[3%dm%c\x1b[0m", y + 1, x + 1, color, ch);
}

int main(int argc, char **argv) {
    int color = 2; // 2 es verde en las secuencias de escape ANSI (aproximado)
    
    
    gfxInitDefault();
    PrintConsole topScreen, bottomScreen;
    consoleInit(GFX_TOP, &topScreen);
    consoleInit(GFX_BOTTOM, &bottomScreen);
    srand(time(NULL));

    // Inicializar las corrientes
    Stream streams[MAX_STREAMS];
    for (int i = 0; i < MAX_STREAMS; ++i) {
        streams[i].column = rand() % SCREEN_WIDTH;
        streams[i].length = (rand() % (MAX_STREAM_LENGTH - MIN_STREAM_LENGTH + 1)) + MIN_STREAM_LENGTH;
        streams[i].position = -(rand() % (SCREEN_HEIGHT * 2)); // Empezar fuera de la pantalla
        streams[i].speed = FALL_SPEED + (rand() % 2);
    }

    // Bucle principal
    while (aptMainLoop()) {
        hidScanInput();
        u32 kDown = hidKeysDown();

        if (kDown & KEY_START)
            break; // Salir del bucle con START

        // Limpiar ambas pantallas
        consoleSelect(&topScreen); consoleClear();
        consoleSelect(&bottomScreen); consoleClear();

        // Dibuixar en les dos pantalles
        for (int i = 0; i < MAX_STREAMS; ++i) {
            for (int j = 0; j < streams[i].length; ++j) {
                int row = streams[i].position + j;
                if (row >= 0 && row < SCREEN_HEIGHT) {
                    char ch = getRandomChar();
                    if (j == (streams[i].length-1) )
                        color = 37;
                    else
                        color = 2; // 2 es verde en las secuencias de escape ANSI (aproximado)
                    printColoredChar(&topScreen, streams[i].column, row, ch, color);
                    printColoredChar(&bottomScreen, streams[i].column, row, ch, color);
                }
            }
            streams[i].position += streams[i].speed;
            if (streams[i].position > SCREEN_HEIGHT) {
                streams[i].position = -(rand() % MAX_STREAM_LENGTH);
                streams[i].length = (rand() % (MAX_STREAM_LENGTH - MIN_STREAM_LENGTH + 1)) + MIN_STREAM_LENGTH;
                streams[i].speed = FALL_SPEED + (rand() % 2);
            }
        }


        // Esperar el siguiente frame (introducir el delay)
         svcSleepThread(FRAME_DELAY * 1000); // svcSleepThread: en nanosegundos

        // Esperar el siguiente frame
        gspWaitForVBlank();
    }

    gfxExit();
    return 0;
}
