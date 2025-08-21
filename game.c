#include "game.h"
#include <stdlib.h>
#include <stdio.h>
#include <SDL2/SDL_mixer.h>

// Game state variables
int player_x, player_y, score, running;
struct Bullet bullets[MAX_BULLETS];
struct Alien aliens[MAX_ALIENS];
int alien_direction = 1, aliens_killed = 0;
struct Star stars[MAX_STARS];

extern Mix_Chunk *shoot_sound;

// Initialize game state for a new round
void init_game() {
    player_x = WIDTH / 2;
    player_y = HEIGHT - 2;
    score = 0;
    running = 1;
    aliens_killed = 0;

    // Reset bullets
    for (int i = 0; i < MAX_BULLETS; i++)
        bullets[i].active = 0;

    // Position aliens in a grid
    for (int i = 0; i < MAX_ALIENS; i++) {
        aliens[i].active = 1;
        aliens[i].x = (i % 10) * 6 + 5;
        aliens[i].y = (i / 10) * 2 + 2;
    }

    // Randomize starfield
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].x = rand() % WIDTH;
        stars[i].y = rand() % HEIGHT;
    }
}

// Draw all game elements to the screen
void draw() {
    clear();

    // Draw stars
    attron(COLOR_PAIR(1));
    for (int i = 0; i < MAX_STARS; i++)
        mvprintw(stars[i].y, stars[i].x, ".");
    attroff(COLOR_PAIR(1));

    // Draw player ship
    attron(COLOR_PAIR(1));
    mvprintw(player_y, player_x, "/^\\ ");
    attroff(COLOR_PAIR(1));

    // Draw bullets
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) continue;
        if (bullets[i].direction == 1) { // Player bullet
            attron(COLOR_PAIR(5));
            mvprintw(bullets[i].y, bullets[i].x, "|");
            attroff(COLOR_PAIR(5));
        } else { // Alien bullet
            attron(COLOR_PAIR(2));
            mvprintw(bullets[i].y, bullets[i].x, "|");
            attroff(COLOR_PAIR(2));
        }
    }

    // Draw aliens
    attron(COLOR_PAIR(3));
    for (int i = 0; i < MAX_ALIENS; i++)
        if (aliens[i].active)
            mvprintw(aliens[i].y, aliens[i].x, "0");
    attroff(COLOR_PAIR(3));

    // Draw score and status
    mvprintw(0, 2, "Score: %d", score);
    mvprintw(0, 20, "Killed: %d", aliens_killed);
    mvprintw(HEIGHT - 1, 2, "Press 'q' to quit");

    refresh();
}

// Handle player input and fire bullets
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
            // Fire a bullet from center of ship
            for (int i = 0; i < MAX_BULLETS; i++) {
                if (!bullets[i].active) {
                    bullets[i].active = 1;
                    bullets[i].x = player_x + 1;
                    bullets[i].y = player_y - 1;
                    bullets[i].direction = 1;
                    if (shoot_sound) Mix_PlayChannel(-1, shoot_sound, 0);
                    break;
                }
            }
            break;
        case 'q':
        case 'Q':
            return 0;
    }
    return 1;
}

// Update game state: move bullets, aliens, check collisions
void update_game() {
    // Move bullets
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (bullets[i].active) {
            bullets[i].y -= bullets[i].direction;
            if (bullets[i].y < 0 || bullets[i].y >= HEIGHT)
                bullets[i].active = 0;
        }
    }

    // Move aliens and fire bullets
    int change_direction = 0;
    for (int i = 0; i < MAX_ALIENS; i++) {
        if (!aliens[i].active) continue;
        aliens[i].x += alien_direction;
        if (aliens[i].x <= 0 || aliens[i].x >= WIDTH - 2)
            change_direction = 1;
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
    if (change_direction) {
        alien_direction *= -1;
        for (int i = 0; i < MAX_ALIENS; i++)
            if (aliens[i].active)
                aliens[i].y++;
    }

    // Collision detection
    for (int i = 0; i < MAX_BULLETS; i++) {
        if (!bullets[i].active) continue;
        if (bullets[i].direction == 1) { // Player bullet
            for (int j = 0; j < MAX_ALIENS; j++) {
                if (aliens[j].active &&
                    bullets[i].x == aliens[j].x &&
                    bullets[i].y == aliens[j].y) {
                    bullets[i].active = 0;
                    aliens[j].active = 0;
                    score += 10;
                    aliens_killed++;
                }
            }
        } else if (bullets[i].direction == -1) { // Alien bullet
            // Expanded player hitbox: check all three ship characters
            if ((bullets[i].x >= player_x && bullets[i].x <= player_x + 2) &&
                bullets[i].y == player_y) {
                running = 0; // Game over
            }
        }
    }

    // Win/loss conditions
    if (aliens_killed == MAX_ALIENS)
        running = 0; // Win
    for (int i = 0; i < MAX_ALIENS; i++)
        if (aliens[i].active && aliens[i].y >= HEIGHT - 2)
            running = 0; // Aliens reached bottom

    // Move stars for starfield effect
    for (int i = 0; i < MAX_STARS; i++) {
        stars[i].y++;
        if (stars[i].y >= HEIGHT) {
            stars[i].y = 0;
            stars[i].x = rand() % WIDTH;
        }
    }
}
