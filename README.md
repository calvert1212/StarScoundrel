<img width="866" height="611" alt="Image" src="https://github.com/user-attachments/assets/3baddc33-794c-4af5-8730-7073935ec49d" />
# Space Scoundrels: An ASCII Space Invaders Game

## Table of Contents

- [Introduction](#introduction)
- [Features](#features)
- [How to Play](#how-to-play)
- [File Structure](#file-structure)
- [Compilation and Execution](#compilation-and-execution)
- [Troubleshooting](#troubleshooting)
- [Future Enhancements](#future-enhancements)
- [License](#license)

## Introduction

"Space Scoundrels" is a classic Space Invaders-style arcade game implemented in C, utilizing the `ncurses` library for terminal-based graphics and interaction. The game features ASCII art for all its elements, providing a nostalgic 1980s arcade feel directly in your terminal.

## Features

-   **ASCII Graphics**: All game elements, including the player's ship, alien invaders, and bullets, are rendered using ASCII characters.
-   **Player Control**: Move your ship left and right to dodge incoming fire and position yourself for accurate shots.
-   **Shooting Mechanics**: Fire single shots to eliminate alien invaders.
-   **Alien AI**: Invaders move in a coordinated formation, descending towards your position, and periodically fire back.
-   **Collision Detection**: Accurate detection for player-bullet, alien-bullet, and alien-player collisions.
-   **Scoring System**: Earn points for each alien destroyed.
-   **Start Screen**: A retro 1980s arcade-style ASCII art logo for "STAR SCOUNDRELS" welcomes players, with options to start the game or quit.
-   **Win/Loss Conditions**: The game ends if all aliens are defeated (win), if the player's ship is hit, or if aliens reach the bottom of the screen (loss).
-   **Game Over/Win Screens**: Dedicated screens display the final score upon game completion, offering a seamless return to the start screen for another round.
-   **Sound Effects**: A simple beep sound effect plays when the player shoots.

## How to Play

1.  **Start the Game**: Run the executable from your terminal. You will be greeted by the "STAR SCOUNDRELS" title screen.
2.  **Navigate Menus**: Press any key to start the game from the title screen. Press 'q' to quit the game from the title screen.
3.  **Player Movement**: Use the 'a' key or the Left Arrow key to move your ship left.
4.  **Player Movement**: Use the 'd' key or the Right Arrow key to move your ship right.
5.  **Shoot**: Press the Spacebar to fire a bullet.
6.  **Quit Mid-Game**: Press the 'q' key at any point during gameplay to immediately exit the program.
7.  **Continue After Game Over/Win**: After the game ends, press any key on the Game Over or Win screen to return to the main title screen.

## File Structure

The project is organized into several files for better modularity and maintainability:

-   `main.c`: Contains the `main` function, which initializes the `ncurses` environment, sets up color pairs, and manages the overall game flow, including transitions between the start screen, gameplay, and end screens.

-   `game.h`: The header file for `game.c`. It declares global game state variables (e.g., player position, score, bullet and alien arrays) and function prototypes for game-related logic such as `init_game`, `draw`, `handle_input`, and `update_game`. It also defines game constants like `WIDTH` and `HEIGHT`.

-   `game.c`: Implements the core game logic. This includes functions for initializing game elements, drawing them on the screen, processing player input, updating game states (like bullet and alien movement), and handling collision detection.

-   `screens.h`: The header file for `screens.c`. It declares function prototypes for the various game screens: `start_screen`, `game_over_screen`, and `win_screen`.

-   `screens.c`: Implements the visual and interactive elements of the game's different screens. This includes rendering the ASCII art logo for the start screen, displaying game over/win messages, and handling user input to transition between screens.

-   `Makefile`: A utility file that automates the compilation process. It defines rules for compiling individual `.c` files into object files (`.o`) and then linking these object files together to create the final `space_invaders` executable. It also includes a `clean` rule to remove compiled files.

## Compilation and Execution

To compile and run "Space Scoundrels" on your Linux system, follow these steps:

1.  **Navigate to the Project Directory**: Open your terminal and change your current directory to where you have cloned or extracted the game files (e.g., `/home/chad/SpaceInvaders`).

    ```bash
    cd /home/chad/SpaceInvaders
    ```

2.  **Compile the Game**: Use the `make` command to compile the project. The `Makefile` will handle compiling all necessary `.c` files and linking them.

    ```bash
    make
    ```

    *Note: If `make` is not installed, you might need to install it using your distribution's package manager (e.g., `sudo apt install make` on Debian/Ubuntu, `sudo dnf install make` on Fedora, `sudo pacman -S make` on Arch Linux).* 

3.  **Run the Game**: Once compiled, execute the game using the following command:

    ```bash
    ./space_invaders
    ```

    *Note: Ensure your terminal supports `ncurses` and colors for the best experience. `xterm-256color` is recommended.*

## Troubleshooting

-   **"Cannot hear beep sound"**: Ensure your terminal's audible bell is enabled in its settings. Also, check your system's sound volume.
-   **"Colors are not displayed correctly"**: Verify that your terminal emulator supports 256 colors and that your `TERM` environment variable is set appropriately (e.g., `export TERM=xterm-256color`).
-   **"Game does not start or crashes"**: Ensure all necessary `ncurses` development libraries are installed on your system (e.g., `libncurses-dev` or `ncurses-devel`).

## Future Enhancements

-   **More Alien Types**: Introduce different alien behaviors and appearances.
-   **Power-ups**: Implement temporary power-ups for the player (e.g., rapid fire, shields).
-   **Levels**: Add multiple levels with increasing difficulty.
-   **High Score Tracking**: Save and display high scores.
-   **Improved Graphics**: Explore more complex ASCII art or pseudo-graphics characters.

## License

This project is open-source and available under the [MIT License](LICENSE).
