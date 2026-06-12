# Acorn Adventure

Acorn Adventure is a 2D arcade adventure game built in C++ with OpenGL. The game follows a squirrel protagonist through multiple playable stages with collectible acorns, animated obstacles, enemy encounters, sound effects, background music, and a packaged Windows playable build.

The project combines side-scrolling movement, platforming, collectible objectives, level progression, and integrated gameplay systems such as pause/help screens, menu navigation, and level transitions across three themed stages.
[Game Play Video](https://youtu.be/Rur5JOJJNAQ)

## Features

* Three playable levels with distinct mechanics, objectives, and visual themes
* Animated squirrel character with movement, jumping, hit, and action states
* Collectible acorn system with score tracking and level objectives
* Lives, collision detection, hit reactions, reset behavior, and game progression
* Main menu, level selection, intro screens, pause/help overlay, and return-to-menu flow
* Dynamic obstacles and enemies including cars, foxes, snakes, birds, rocks, and environmental hazards
* Level-specific mechanics such as traffic avoidance, forest traversal, log collection, river crossing, climbing sequences, thrown acorns, and the final golden acorn objective
* Sprite-based rendering with parallax-style backgrounds and custom visual assets
* Sound effects and background music integration using irrKlang
* Shared texture caching system to improve texture loading and reuse
* Packaged Windows playable build with required runtime files included

## My Role

I served as the primary developer for Acorn Adventure and led most of the final implementation. My work focused on gameplay programming, level design, scene flow, visual integration, debugging, and preparing the final playable build.

My main contributions included:

* Implementing and polishing the core gameplay loop
* Building the menu flow, level selection, pause behavior, and scene transitions
* Reworking and expanding Levels 1 and 2
* Fully implementing Level 3 and the final game sequence
* Programming player movement, jumping, collectibles, hazards, hit states, enemy behavior, and objective progression
* Creating and tuning gameplay systems such as traffic avoidance, thrown acorns, forest traversal, climbing mechanics, and the golden acorn finale
* Integrating sprites, backgrounds, UI screens, sound effects, and music into the gameplay experience
* Debugging build/runtime issues and packaging the game into a playable Windows version

## Collaboration Note

Acorn Adventure began as a small collaborative project using a provided starter framework. Other contributors helped with early planning, initial prototype levels, debugging support, and project organization. I built on that foundation and completed the majority of the gameplay systems, level implementation, final polish, and playable build.

## Core Technologies

* C++
* OpenGL
* GLUT
* GLEW
* SOIL
* irrKlang
* Code::Blocks
* MinGW

## How to Play

A playable Windows version is included in the `Play_Game` folder.

1. Download or clone the repository.
2. Open the `Play_Game` folder.
3. Run `START_GAME_HERE.bat`.

Do not run the game directly from inside a ZIP archive. Extract the project first, then run the launcher.

## Project Structure

```text
Source_Code/   Source code, headers, external libraries, and build files
Play_Game/     Playable Windows build with launcher, assets, EXE, and required DLLs
```

Inside the source code:

```text
src/        Gameplay, rendering, audio, texture, input, and level systems
include/    Header files and shared interfaces
images/     Sprites, backgrounds, UI screens, and level assets
sounds/     Music and sound effects
common/     External headers and supporting libraries
```

## Status

Playable Windows build complete.
