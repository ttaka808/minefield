# Minefield

Minefield is a game based on a minigame called Voltorb Flip from Pokemon HeartGold and SoulSilver. Users are given a 5x5 with randomized bomb locations and point values and data on how many points and how many bombs are in each column and row. A user loses if they select a bomb. Using this information, the user uses deduction to determine which locations have bombs and which locations are safe to select. Then, the user enters the coordinate to confirm their choice. The user completes the game when all points values greater than one are located. Currently, a user must win three consecutive levels to win the game. 

## Technologies
### OS
Linux (untested on Unix and Windows)
### Language
C
### Compiler
GCC

## Known Issues
Overflow error for column points array when user input has valid coordinate followed by other characters.

## Future Features
### Score
Score will be kept track of during the current board as well as the overall game.
### Survival Game Mode
A game mode will be created to generate unlimited boards until the user hits a bomb. Users will play for a high score.
