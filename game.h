#ifndef GAME_H
#define GAME_H

#include <ncurses.h>

// Game dimensions
#define WIDTH 80
#define HEIGHT 36

// Game state variables
extern int player_x, player_y, score, running;

// Bullet structure and array
#define MAX_BULLETS 50
struct Bullet {
    int x, y;
    int active;
    int direction; // 1 for player, -1 for alien
};
extern struct Bullet bullets[MAX_BULLETS];

// Alien structure and array
#define MAX_ALIENS 30
struct Alien {
    int x, y;
    int active;
};
extern struct Alien aliens[MAX_ALIENS];
extern int alien_direction, aliens_killed;

// Star structure and array for starfield
#define MAX_STARS 50
struct Star {
    int x, y;
};
extern struct Star stars[MAX_STARS];

// Game logic function prototypes
void init_game();
void draw();
int handle_input();
void update_game();

#endif // GAME_H
