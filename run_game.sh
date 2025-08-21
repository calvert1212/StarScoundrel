#!/bin/bash

# Compile the game with SDL2 and SDL2_mixer
gcc -o /home/chad/SpaceInvaders/space_invaders /home/chad/SpaceInvaders/main.c /home/chad/SpaceInvaders/game.c /home/chad/SpaceInvaders/screens.c -I/usr/include/ncurses -lncurses -lSDL2 -lSDL2_mixer

# Check if compilation was successful
if [ $? -eq 0 ]; then
    echo "Compilation successful. Running the game..."
    # Run the game
    /home/chad/SpaceInvaders/space_invaders
else
    echo "Compilation failed. Please check for errors."
fi
