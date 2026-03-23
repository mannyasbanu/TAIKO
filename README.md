# MannyTaiko

A simple Taiko-style rhythm game built in C++ with SFML.

## Requirements & Installation

### WSL2 (Ubuntu)
    sudo apt install -y build-essential cmake libsfml-dev

### macOS
Install Homebrew if you don't have it:

    /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"

Then install dependencies:

    brew install cmake sfml

## Building

    ./build.sh

> **macOS note:** If you see a security warning when running the binary,
> go to System Settings → Privacy & Security → allow the app, then run again.

## Running

    ./build/taiko

## Controls

| Key    | Action       |
|--------|--------------|
| F      | Don (red)    |
| J      | Ka (blue)    |
| Escape | Pause        |

## Beatmap Format

Maps live in `maps/` as plain `.txt` files. Each map needs a matching
`.ogg` file in `assets/` with the same name.

    # maps/mysong.txt
    DON 1000
    KA  1500
    DON 2000

Time is in milliseconds from the start of the song.

Example matching pair:

    maps/mysong.txt
    assets/mysong.ogg

## Project Structure

    taiko/
    ├── build.sh
    ├── CMakeLists.txt
    ├── assets/
    │   ├── skins/
    │   │   └── default/    # don.png, ka.png, hit_zone.png
    │   ├── don.wav
    │   ├── ka.wav
    │   └── *.ogg           # music files (match map name)
    ├── maps/
    │   └── *.txt           # beatmap files (match music name)
    └── src/
        ├── main.cpp
        ├── Game.hpp / Game.cpp
        ├── IGameState.hpp
        ├── MenuState.hpp / MenuState.cpp
        ├── PlayingState.hpp / PlayingState.cpp
        ├── PauseState.hpp / PauseState.cpp
        ├── ResultState.hpp / ResultState.cpp
        ├── BeatMap.hpp / BeatMap.cpp
        ├── Note.hpp
        ├── Judge.hpp
        ├── Skin.hpp
        ├── NoteRender.hpp / NoteRender.cpp
        └── beatmapper.cpp