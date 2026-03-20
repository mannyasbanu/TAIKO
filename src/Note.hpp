#pragma once

enum class NoteType {
  Don,
  Ka,
};

struct Note {
  NoteType type;
  float timeMs; // when this note should be hit
  float x; // current x pos
  bool hit = false;
  bool missed = false;
};