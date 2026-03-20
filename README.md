# MannyTaiko

A simple Taiko-style rhythm game built in C++ with SFML.

## Requirements

- WSL2 (Ubuntu)
- SFML, CMake, GCC

Install dependencies:
    sudo apt install -y build-essential cmake libsfml-dev

## Building

    ./build.sh

## Running

    ./build/taiko

## Controls

| Key | Action |
|-----|--------|
| F   | Don (red note) |
| J   | Ka (blue note) |
| Esc | Quit |

## Beatmap Format

Maps live in the `maps/` folder as plain `.txt` files.

    # This is a comment
    DON 1000
    KA  1500
    DON 2000

Time is in milliseconds from the start of the song.

## Adding Music

Drop a `.ogg` file into `assets/` and uncomment the music lines in `Game.cpp`:

    if (!music.openFromFile("assets/song.ogg")) { ... }
    music.play();

Then sync `songTimeMs` to the music:

    songTimeMs = music.getPlayingOffset().asMilliseconds();

## Project Structure

    taiko/
    ├── build.sh         # Build script
    ├── CMakeLists.txt
    ├── assets/          # Music files (.ogg)
    ├── maps/            # Beatmap files (.txt)
    └── src/
        ├── main.cpp
        ├── Game.hpp / Game.cpp
        ├── Note.hpp
        ├── BeatMap.hpp / BeatMap.cpp
        ├── Judge.hpp
        └── Judge.cpp