#pragma once
#include <vector>
#include <string>
#include "Note.hpp"
// Manny STL ^

class BeatMap {
public:
  std::vector<Note> notes;
  bool load(const std::string& filepath);
};