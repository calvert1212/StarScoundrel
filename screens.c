#include "screens.h"
#include "game.h"
#include <SDL2/SDL_mixer.h>

extern Mix_Chunk *jingle_sound;

// Display the start screen and play jingle
int start_screen() {
    clear();
    if (jingle_sound) Mix_PlayChannel(-1, jingle_sound, 0);
    attron(COLOR_PAIR(4));
    mvprintw(5, 15, "        ####   #######   ###   ######");
    mvprintw(6, 15, "       #    #     #     #   #  #     #");
    mvprintw(7, 15, "       #          #     #   #  #     #");
    mvprintw(8, 15, "       #####      #     #####  ######");
    mvprintw(9, 15, "            #     #     #   #  #   #");
    mvprintw(10, 15, "       #    #     #     #   #  #    #");
    mvprintw(11, 15, "        #####     #     #   #  #     #");
    mvprintw(13, 10, "   #######  #######  ####### #     #  #     #  ######   #####   ##### #");
    mvprintw(14, 10, "  #        #        #     #  #     #  # #   #  #     #  #    # #      #");
    mvprintw(15, 10, "  #        #        #     #  #     #  #  #  #  #     #  #    # #      #");
    mvprintw(16, 10, "   #####   #        #     #  #     #  #   # #  #     #  #####  ###### #");
    mvprintw(17, 10, "        #  #        #     #  #     #  #     #  #     #  #   #  #      #");
    mvprintw(18, 10, "  #     #  #        #     #  #     #  #     #  #     #  #    #  #     #");
    mvprintw(19, 10, "   #####   #######  #######   #####   #     #  ######   #     # ##### ######");
    attroff(COLOR_PAIR(4));
    mvprintw(22, 28, "Press any key to start");
    mvprintw(23, 28, "Press 'q' to quit");
    refresh();
    int ch = getch();
    if (ch == 'q' || ch == 'Q') return 0;
    return 1;
}

// Display game over screen
void game_over_screen() {
    clear();
    attron(COLOR_PAIR(4));
    mvprintw(10, 35, "GAME OVER");
    attroff(COLOR_PAIR(4));
    mvprintw(12, 32, "Your score: %d", score);
    mvprintw(14, 28, "Press any key to continue");
    refresh();
    getch();
}

// Display win screen
void win_screen() {
    clear();
    attron(COLOR_PAIR(2));
    mvprintw(10, 35, "YOU WIN!");
    attroff(COLOR_PAIR(2));
    mvprintw(12, 32, "Your score: %d", score);
    mvprintw(14, 28, "Press any key to continue");
    refresh();
    getch();
}
