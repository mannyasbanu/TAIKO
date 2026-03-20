#include "BeatMap.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
// Manny STL ^

bool BeatMap::load(const std::string& filepath) {
  std::ifstream file(filepath);
  if (!file.is_open()) {
    std::cerr << "Failed to load beatmap: " << filepath << std::endl;
    return false;
  }
  
  std::string line;
  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#') continue; // skip empty lines and comments
    std::istringstream ss(line); // convert line to character stream for parsing
    std::string typeStr;
    float timeMs;
    ss >> typeStr >> timeMs;

    Note note;
    note.timeMs = timeMs;
    note.x = 1400.0f; // start off screen to the right
    if (typeStr == "DON") note.type = NoteType::Don;
    else if (typeStr == "KA") note.type = NoteType::Ka;
    else continue; // skip invalid lines

    notes.push_back(note);
  }
  return true;
}