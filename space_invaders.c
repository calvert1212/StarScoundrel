#include <ncurses.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define WIDTH 160
#define HEIGHT 48

// Game state
int player_x;
int player_y;
int score;
int running;

// Bullets
#define MAX_BULLETS 100
struct Bullet {
    int x, y;
    int active;
    int direction; // 1 for player, -1 for alien
} bullets[MAX_BULLETS];

// Aliens
#define MAX_ALIENS 30
struct Alien {
    int x, y;
    int active;
} aliens[MAX_ALIENS];
int alien_direction = 1;
int aliens_killed = 0;

void init_game() {
    player_x = WIDTH / 2;
    player_y = HEIGHT - 2;
    score = 0;
    running = 1;
    aliens_killed = 0;

    // Initialize bullets
    for (int i = 0; i < MAX_BULLETS; i++) {
        bullets[i].active = 0;
    }

    // Initialize aliens
    for (int i = 0; i < MAX_ALIENS; i++) {
        aliens[i].active = 1;
        aliens[i].x = (i % 10) * 6 + 5;
        aliens[i].y = (i / 10) * 2 + 2;
    }
}

void draw() {
    clear();

    // Draw player
    attron(COLOR_PAIR(1));
    mvprintw(player_y, player_x, "/^\\\");
    attroff(COLOR_PAIR(1));

    // Draw bullets
    attron(COLOR_PAIR(2));
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            mvprintw(bullets[i].y, bullets[i].x, "|");
        }
    }
    attroff(COLOR_PAIR(2));

    // Draw aliens
    attron(COLOR_PAIR(3));
    for (int i = 0; i < MAX_ALIENS; i++) {
        if (aliens[i].active) {
            mvprintw(aliens[i].y, aliens[i].x, "O");
        }
    }
    attroff(COLOR_PAIR(3));

    // Draw score
    mvprintw(0, 2, "Score: %d", score);
    mvprintw(0, 20, "Killed: %d", aliens_killed);
    mvprintw(HEIGHT - 1, 2, "Press 'q' to quit");


    refresh();
}

int start_screen() {
    clear();
    attron(COLOR_PAIR(4));
    mvprintw(5, 15, "  #####   #######  ######   ######   #####   ");
    mvprintw(6, 15, " #     #     #     #     # #     # #     #  ");
    mvprintw(7, 15, " #           #     #     # #     # #          ");
    mvprintw(8, 15, "  #####      #     ######  ######  #          ");
    mvprintw(9, 15, "        #    #     #   #   #   #   #          ");
    mvprintw(10, 15, " #     #     #     #    #  #    #  #     #  ");
    mvprintw(11, 15, "  #####      #     #     # #     #   #####   ");
    mvprintw(13, 10, "   #######  #######  #######  #     #  #######  #     #  #######  #####   ");
    mvprintw(14, 10, "  #        #     #  #     #  #     #  #     #  #     #  #        #     #  ");
    mvprintw(15, 10, "  #        #     #  #     #  #     #  #     #  #     #  #        #        ");
    mvprintw(16, 10, "   #####   #     #  #     #  #     #  #     #  #     #  #####     #####   ");
    mvprintw(17, 10, "        #  #     #  #     #  #     #  #     #   #   #   #              #  ");
    mvprintw(18, 10, "  #     #  #     #  #     #  #     #  #     #    # #    #        #     #  ");
    mvprintw(19, 10, "   #####   #######  #######   #####   #######     #     #######   #####   ");
    attroff(COLOR_PAIR(4));
    mvprintw(22, 28, "Press any key to start");
    mvprintw(23, 28, "Press 'q' to quit");
    refresh();
    int ch = getch();
    if (ch == 'q') {
        return 0;
    }
    return 1;
}

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

int handle_input() {
    int ch = getch();
    switch (ch) {
        case 'a':
        case KEY_LEFT:
            if (player_x > 0) player_x--;
            break;
        case 'd':
        case KEY_RIGHT:
            if (player_x < WIDTH - 1) player_x++;
            break;
        case ' ':
            // Fire a bullet
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (!bullets[i].active) {
                    bullets[i].active = 1;
                    bullets[i].x = player_x;
                    bullets[i].y = player_y - 1;
                    bullets[i].direction = 1;
                    printf("\a");
                    break;
                }
            }
            break;
        case 'q':
            return 0;
    }
    return 1;
}

void update_game() {
    // Move bullets
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].y -= bullets[i].direction;
            if (bullets[i].y < 0 || bullets[i].y >= HEIGHT) {
                bullets[i].active = 0;
            }
        }
    }

    // Move aliens
    int change_direction = 0;
    for (int i = 0; i < MAX_ALIENS; i++) {
        if (aliens[i].active) {
            aliens[i].x += alien_direction;
            if (aliens[i].x <= 0 || aliens[i].x >= WIDTH - 2) {
                change_direction = 1;
            }
            // Alien firing
            if (rand() % 100 < 2) {
                 for (int j = 0; j < MAX_BULLETS; j++) {
                    if (!bullets[j].active) {
                        bullets[j].active = 1;
                        bullets[j].x = aliens[i].x;
                        bullets[j].y = aliens[i].y + 1;
                        bullets[j].direction = -1;
                        break;
                    }
                }
            }
        }
    }

    if (change_direction) {
        alien_direction *= -1;
        for (int i = 0; i < MAX_ALIENS; i++) {
            if (aliens[i].active) {
                aliens[i].y++;
            }
        }
    }

    // Collision detection
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active && bullets[i].direction == 1) { // Player bullet
            for (int j = 0; j < MAX_ALIENS; j++) {
                if (aliens[j].active && bullets[i].x == aliens[j].x && bullets[i].y == aliens[j].y) {
                    bullets[i].active = 0;
                    aliens[j].active = 0;
                    score += 10;
                    aliens_killed++;
                }
            }
        } else if (bullets[i].active && bullets[i].direction == -1) { // Alien bullet
            if (bullets[i].x == player_x && bullets[i].y == player_y) {
                running = 0; // Game over
            }
        }
    }

    // Check for win/loss
    if (aliens_killed == MAX_ALIENS) {
        running = 0; // You win!
    }

    for (int i = 0; i < MAX_ALIENS; i++) {
        if(aliens[i].active && aliens[i].y >= HEIGHT -2) {
            running = 0; // Aliens reached the bottom
        }
    }
}

int main() {
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_YELLOW, COLOR_BLACK);
    init_pair(3, COLOR_GREEN, COLOR_BLACK);
    init_pair(4, COLOR_RED, COLOR_BLACK);
    cbreak();
    noecho();
    keypad(stdscr, TRUE);
    nodelay(stdscr, TRUE);
    curs_set(0);
    srand(time(NULL));

    while(1) { // Loop indefinitely to allow playing multiple games
        if (!start_screen()) { // If start_screen returns 0 (user pressed 'q')
            break; // Exit the main loop
        }
        init_game();

        while (running) {
            if (!handle_input()) { // If handle_input returns 0 (user pressed 'q')
                endwin();
                return 0; // Exit the program immediately
            }
            update_game();
            draw();
            usleep(100000); // 100ms
        }

        if (aliens_killed == MAX_ALIENS) {
            win_screen();
        } else {
            game_over_screen();
        }
    }

    endwin();

    return 0;
}
