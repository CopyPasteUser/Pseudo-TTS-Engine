#include <uiohook.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>

typedef struct {
    char filename[256];
} SoundParams;


int fileExists(const char *filename) {
    return access(filename, F_OK) == 0;
}

void* playSoundThread(void* arg) {
    SoundParams* params = (SoundParams*)arg;
    char path[256];
    snprintf(path, sizeof(path), "sounds/%s", params->filename);
    
    if (!fileExists(path)) {
        printf("Sounddatei %s existiert nicht!\n", path);
        free(params);
        return NULL;
    }

    Mix_Chunk *sound = Mix_LoadWAV(path);
    if (!sound) {
        fprintf(stderr, "Mix_LoadWAV Fehler: %s\n", Mix_GetError());
        free(params);
        return NULL;
    }

    int channel = Mix_PlayChannel(-1, sound, 0);
    if (channel == -1) {
        fprintf(stderr, "Mix_PlayChannel Fehler: %s\n", Mix_GetError());
        Mix_FreeChunk(sound);
        free(params);
        return NULL;
    }

    
    while (Mix_Playing(channel)) {
        SDL_Delay(100);
    }

    Mix_FreeChunk(sound);
    free(params);
    return NULL;
}

void playSound(const char *filename) {
    SoundParams* params = malloc(sizeof(SoundParams));
    if (!params) {
        fprintf(stderr, "Speicherzuweisung fehlgeschlagen\n");
        return;
    }
    snprintf(params->filename, sizeof(params->filename), "%s", filename);

    pthread_t thread;
    if (pthread_create(&thread, NULL, playSoundThread, params) != 0) {
        fprintf(stderr, "Thread konnte nicht erstellt werden\n");
        free(params);
        return;
    }
    pthread_detach(thread); 
}

void handle_event(uiohook_event * const event) {
    if (event->type == EVENT_KEY_PRESSED) {
        char filename[256];
        const char *keyname = NULL;
        
            switch (event->data.keyboard.keycode) {
            //buchstaben
            case VC_A: keyname = "a"; break;
            case VC_B: keyname = "b"; break;
            case VC_C: keyname = "c"; break;
            case VC_D: keyname = "d"; break;
            case VC_E: keyname = "e"; break;
            case VC_F: keyname = "f"; break;
            case VC_G: keyname = "g"; break;
            case VC_H: keyname = "h"; break;
            case VC_I: keyname = "i"; break;
            case VC_J: keyname = "j"; break;
            case VC_K: keyname = "k"; break;
            case VC_L: keyname = "l"; break;
            case VC_M: keyname = "m"; break;
            case VC_N: keyname = "n"; break;
            case VC_O: keyname = "o"; break;
            case VC_P: keyname = "p"; break;
            case VC_Q: keyname = "q"; break;
            case VC_R: keyname = "r"; break;
            case VC_S: keyname = "s"; break;
            case VC_T: keyname = "t"; break;
            case VC_U: keyname = "u"; break;
            case VC_V: keyname = "v"; break;
            case VC_W: keyname = "w"; break;
            case VC_X: keyname = "x"; break;
            case VC_Y: keyname = "y"; break;
            case VC_Z: keyname = "z"; break;

            //zahlen
            case VC_1: keyname = "1"; break;
            case VC_2: keyname = "2"; break;
            case VC_3: keyname = "3"; break;
            case VC_4: keyname = "4"; break;
            case VC_5: keyname = "5"; break;
            case VC_6: keyname = "6"; break;
            case VC_7: keyname = "7"; break;
            case VC_8: keyname = "8"; break;
            case VC_9: keyname = "9"; break;
            case VC_0: keyname = "0"; break;
            
             // Sonderzeichen (Standard ohne Shift)
            case VC_MINUS: keyname = "-"; break;
            case VC_EQUALS: keyname = "="; break;
            case VC_OPEN_BRACKET: keyname = "["; break;
            case VC_CLOSE_BRACKET: keyname = "]"; break;
            case VC_SEMICOLON: keyname = ";"; break;
            case VC_QUOTE: keyname = "'"; break;
            case VC_COMMA: keyname = ","; break;
            case VC_PERIOD: keyname = "."; break;
            case VC_SLASH: keyname = "/"; break;
            
            
             // Sondertasten
            case VC_F1: keyname = "f1"; break;
            case VC_F2: keyname = "f2"; break;
            case VC_F3: keyname = "f3"; break;
            case VC_F4: keyname = "f4"; break;
            case VC_F5: keyname = "f5"; break;
            case VC_F6: keyname = "f6"; break;
            case VC_F7: keyname = "f7"; break;
            case VC_F8: keyname = "f8"; break;
            case VC_F9: keyname = "f9"; break;
            case VC_F10: keyname = "f10"; break;
            case VC_F11: keyname = "f11"; break;
            case VC_F12: keyname = "f12"; break;

            //funktionstasten
             case VC_SPACE: keyname = "space"; break;
            case VC_ENTER: keyname = "enter"; break;
            case VC_TAB: keyname = "tab"; break;
            case VC_BACKSPACE: keyname = "backspace"; break;
            case VC_DELETE: keyname = "delete"; break;
            case VC_LEFT: keyname = "left"; break;
            case VC_RIGHT: keyname = "right"; break;
            case VC_UP: keyname = "up"; break;
            case VC_DOWN: keyname = "down"; break;

            
            

            case VC_ESCAPE:
                printf("Escape gedrückt, beende Programm\n");
                hook_stop();
                return;
            default:
                printf("Unbekannte Taste (Keycode: %u)\n", event->data.keyboard.keycode);
                return;
        }

        if (keyname) {
            snprintf(filename, sizeof(filename), "%s.mp3", keyname);
            printf("Taste %s gedrückt - spiele %s\n", keyname, filename);
            playSound(filename);
        }
    }
}
            
int main() {
    
    DIR* dir = opendir("sounds");
    if (dir) {
        closedir(dir);
    } else {
        printf("Erstelle sounds-Ordner...\n");
        mkdir("sounds", 0755);
    }

   #
    if (SDL_Init(SDL_INIT_AUDIO) < 0) {
        fprintf(stderr, "SDL_Init Fehler: %s\n", SDL_GetError());
        return 1;
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
        fprintf(stderr, "Mix_OpenAudio Fehler: %s\n", Mix_GetError());
        SDL_Quit();
        return 1;
    }

   
    Mix_AllocateChannels(16); 

    hook_set_dispatch_proc(handle_event);
    if (hook_run() != UIOHOOK_SUCCESS) {
        fprintf(stderr, "Hook konnte nicht gestartet werden.\n");
        Mix_CloseAudio();
        SDL_Quit();
        return 1;
    }

    Mix_CloseAudio();
    SDL_Quit();
    return 0;
}