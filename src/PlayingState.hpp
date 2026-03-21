#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "IGameState.hpp"
#include "BeatMap.hpp"
#include "Note.hpp"
#include "Judge.hpp"
#include "Skin.hpp"

// Manny STL ^

class PlayingState : public IGameState {
public:
  PlayingState(sf::Font& font);

  void handleEvent(sf::Event& event, Game& game) override;
  void update(float dt, Game& game) override;
  void render(sf::RenderWindow& window) override;

  NoteSkin& getSkin() { return skin; }

private:
  void handleInput(NoteType type);

  // gameplay
  sf::Music music;
  BeatMap beatMap;
  float songTimeMs = 0.0f;
  int score = 0;
  int combo = 0;

  // visuals
  sf::Font& font;
  sf::Text scoreText, comboText, resultText;
  std::string lastResult = "";
  float resultTimer = 0.0f;
  NoteSkin skin;
  float hitEffectTimer = 0.0f;

  // sound effects
  sf::SoundBuffer donBuffer, kaBuffer;
  sf::Sound donSound, kaSound;

  // class level constants
  static constexpr float NOTE_SPEED = 0.5f; // pixels per ms
  static constexpr float HIT_ZONE_X = 200.0f;
  static constexpr float NOTE_RADIUS = 30.0f;
  static constexpr float OFFSET_MS = 100.0f; // adjust offset - positive means notes come earlier, negative means later
};