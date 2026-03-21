#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Note.hpp"
#include "BeatMap.hpp"
#include <memory>
#include "IGameState.hpp"
// Manny STL ^

class Game {
public:
  Game();
  void run();

  // state management
  void setState(std::unique_ptr<IGameState> newState); // replace current
  void pushState(std::unique_ptr<IGameState> newState); // push on top of current
  void popState(); // return to previous state

  sf::Font& getFont() { return font; } // for states to access the font

private:
  void processEvents(); // process input
  void update(float dt); // update game state (dt is time since last frame in milliseconds)
  void render(); // render to screen
  void handleInput(NoteType type);

  sf::RenderWindow window;
  sf::Music music;
  BeatMap beatMap;

  float songTimeMs = 0.0f;
  int score = 0;
  int combo = 0;

  // visuals
  sf::Font font;
  sf::Text scoreText, comboText, resultText;
  std::string lastResult = "";
  float resultTimer = 0.0f;

  // sound effects
  sf::SoundBuffer donBuffer, kaBuffer;
  sf::Sound donSound, kaSound;

  // class level constants
  static constexpr float NOTE_SPEED = 0.5f; // pixels per ms
  static constexpr float HIT_ZONE_X = 200.0f; // x position of hit zone
  static constexpr float NOTE_RADIUS = 30.0f;
};