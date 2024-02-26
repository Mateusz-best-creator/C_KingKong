# C++ Crafted Donkey Kong Game

Welcome to the C++ Crafted Donkey Kong Game – an exciting and nostalgic gaming experience! This project brings the classic Donkey Kong arcade game to life, meticulously crafted in C++ to capture the essence of the original while adding modern features.

## Screenshots

**Start Page**

**Level 2**

**Custom Generated Level**

## Features:

### 1. Authentic Gameplay:
   - Immerse yourself in the authentic Donkey Kong experience with faithful recreation of the classic game mechanics.
   - Climb ladders, jump barrels, and navigate challenging levels just like in the original game.

### 2. Multi-Level Adventure:
   - Conquer multiple levels of increasing difficulty as you are trying to get the treasure.
   - Each level presents new challenges and obstacles to keep you engaged and entertained.

### 3. Hall of Fame:
   - Compete with other players to reach the top of the Hall of Fame.
   - Showcase your gaming skills by achieving high scores and establishing your dominance in the leaderboard.

### 4. Collectibles Galore:
   - Grab coins, trophies, and treasures as you progress through the game.

### 5. Save and Load:
   - Save your progress and continue your game later with the convenient save and load feature.
   - Never lose your hard-earned progress and resume your Donkey Kong adventure whenever you like.

### Interface Instructions:

You can quit the interface immediately by pressing ESC.
Use the arrow keys to move a rectangle and select one of the following options:

1. **Quit:**
   - Quit the game immediately.

2. **Pick Level 2:**
   - Move to level 2 for a new challenge.

3. **Authenticate:**
   - Authenticate to personalize your gaming experience.

4. **Generate Level (Feature Not Implemented Yet):**
   - Go to infinite playing mode. Every time you play, a new board is created with random obstacles, ensuring an exciting experience every round. 

5. **Choose Level 2:**
   - Choose to play level 2 directly.

6. **Player's Account, Points, and Times:**
   - View information about players, their points, and playing times.

7. **Load Game from File:**
   - Load a previously saved game from a file.

8. **Level 3:**
   - Move to level 3 for an even more challenging experience.

9. **Hall of Fame:**
   - View the Hall of Fame where top 5 players are sorted based on their scores.

### Game Instructions:

1. **Authentication:**
   - Sign in to personalize your gaming experience and participate in the leaderboard.

2. **Controls:**
   - Use arrow keys to move.
   - Press spacebar to jump.
   - Press n to start completely new game
   - Press s to save current state of the game
   - Press 1, 2 or 3 to automatically switch to another level
   - Press ESC to quit the game
   - Navigate through the levels, avoiding obstacles, and reach the top to grab the treasure.

3. **Competition:**
   - Challenge friends or fellow players to see who can achieve the highest score.
   - Climb to the top of the Hall of Fame and become the ultimate Donkey Kong champion!

4. **Save and Load:**
   - Save your game progress for later or load a previously saved game to continue your adventure.

Enjoy the classic nostalgia of Donkey Kong with a touch of modern gaming features. Get ready for a thrilling journey filled with challenges, collectibles, and fierce competition!

### About jumps and movement

It may happen that mario, barells will be very fast on your computer (beacuse yours is faster than mine), then you have to go to mario.h and barrels.h file and tweak some constant values like speed, jump height etc.

# Setup

## Prerequisites

If you are unable to start the project, download SDL2 from the following link:
- [SDL2 Releases](https://github.com/libsdl-org/SDL/releases/tag/release-2.28.5)

Of course download the latest versions of the liblaries. Ensure you download the versions compatible with your Visual Studio setup. If you are using VS Code, download the VS Code versions of the libraries.

## Configuration Steps

If you are unable to clone this repo, click on a **.sln** file and run this game please follow these steps:

1. **Configure Include Directories:**
   - Go to the properties of your project.
   - In the C/C++ section, click on General.
   - Navigate to Additional Include Directories and provide the path to your SDL include folder.

2. **Configure Linker Directories:**
   - Still in the properties of your project, go to the Linker section.
   - Click on General.
   - Go to Additional Library Directories and select `lib\x64` from your SDL folder.

3. **Configure Linker Input:**
   - In the Linker section, go to Input.
   - Navigate to Additional Dependencies.
   - Add the following entries: `SDL2.lib;SDL2main.lib;`.

4. **Optional Recommendation:**
   - If you get an error that SDL2_some_package.dll cannot be found, try to copy some_package.dll and paste it in the same directory where your main.cpp is.

Now, you should be able to build and run the DonkeyKong game smoothly.

## Build and Run in Microsoft Visual Studio

To build and run the chess game using Microsoft Visual Studio, follow these simple steps:

1. **Open the Project:**
   - Launch Microsoft Visual Studio.
   - Open the chess game project in Visual Studio(click on **.sln** file).

2. **Build and Run:**
   - Press `F5` to build and run the chess game.

That's it! You should now be able to enjoy playing chess. Feel free to explore the features and functionalities of the game. The code is available here: https://github.com/Mateusz-best-creator/DonkeyKong_C.

Happy gaming!
