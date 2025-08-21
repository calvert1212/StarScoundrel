#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>

#include "game.h"
#include "screens.h"

// Global sound pointers
Mix_Chunk *shoot_sound = NULL;
Mix_Chunk *jingle_sound = NULL;

int main() {
    // Initialize ncurses
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);   // Player and stars
    init_pair(2, COLOR_RED, COLOR_BLACK);     // Alien bullets
    init_pair(3, COLOR_GREEN, COLOR_BLACK);   // Aliens
    init_pair(4, COLOR_RED, COLOR_BLACK);     // Title/Game Over
    init_pair(5, COLOR_CYAN, COLOR_BLACK);    // Player bullets
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    srand(time(NULL));

    // Initialize SDL2_mixer for sound
    SDL_Init(SDL_INIT_AUDIO);
    Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048);
    shoot_sound = Mix_LoadWAV("shoot.wav");
    jingle_sound = Mix_LoadWAV("Jingle_Win_Synth_05.wav");

    // Main game loop: show start screen, play game, show end screen
    while (1) {
        nodelay(stdscr, FALSE); // Wait for key press on start screen
        if (!start_screen()) {  // Returns 0 if user pressed 'q'
            break;
        }
        nodelay(stdscr, TRUE); // Restore non-blocking input for gameplay
        init_game();

        while (running) {
            if (!handle_input()) { // Returns 0 if user pressed 'q'
                goto cleanup;
            }
            update_game();
            draw();
            usleep(100000); // 100ms frame delay
        }

        if (aliens_killed == MAX_ALIENS) {
            win_screen();
        } else {
            game_over_screen();
        }
    }

cleanup:
    // Free resources and exit
    Mix_FreeChunk(shoot_sound);
    Mix_FreeChunk(jingle_sound);
    Mix_CloseAudio();
    SDL_Quit();
    endwin();
    return 0;
}
