ELEMENTAL CLASH - A C++ STRATEGY GAME

Elemental Clash is a console-based turn-based strategy game written in C++. Players choose an elemental warrior (Fire, Earth, Water, or Lightning) and battle using attack and status moves until one player's health drops to zero.

GAMEPLAY OVERVIEW

Two players choose from elemental characters:

Pyra the Flame

Terros the Earthshaker

Voltra the Spark

Aquon the Wave

Each turn, players are offered 3 random moves:

Usually 3 damage-dealing elemental attacks

Occasionally, one of the moves is a status effect (Heal or Poison)

Elements have strengths and weaknesses:

Fire is weak to Water (x2 damage) and Lightning (x1)

Earth is weak to Fire (x2) and Water (x1)

Lightning is weak to Earth (x2) and Fire (x1)

Water is weak to Lightning (x2) and Earth (x1)

Status Moves:

Heal: +20 HP or cures poison

Poison: Applies poison; opponent loses 5 HP each turn

FEATURES

Object-oriented design using structs for characters and attacks

Randomized turn-based battle mechanics

Weakness multiplier system for attacks

Healing and poison status effects

Game continues until one player's HP (Health Points) reaches zero

CONCEPTS USED

Structs and functions in C++

Random number generation (random, srand, time)

Vectors and maps for storing attacks and weaknesses

Turn-based logic with conditional branching

Code modularization and user interaction

HOW TO RUN

Copy the code into any C++ IDE or an online compiler like Programiz or Replit

Compile and run the code

Follow on-screen instructions to choose characters and start the game

TEAM

Pranati Parandkar

Anoushka

Jharana

Project supervised by Puvulla Kiranmaie, CBIT Hyderabad

FILE STRUCTURE

main.cpp – Complete game code and logic in a single file

FUTURE IMPROVEMENTS

Add AI opponent or single-player mode

Include a graphical user interface (GUI)

Expand to include more elements and status effects

Implement game history or score tracking

THANK YOU

Thank you for exploring Elemental Clash. Feel free to fork the repository, explore the code, or share your feedback!