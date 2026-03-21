#include "PlayingState.hpp"
#include "Game.hpp"
#include "Judge.hpp"
#include <cmath>
#include <iostream>
#include "PauseState.hpp"
#include "ResultState.hpp"
// Manny STL ^

PlayingState::PlayingState(sf::Font& font): font(font) {
  // load beatmap
  if (!beatMap.load("maps/megalovania.txt")) {
    std::cerr << "Failed to load beatmap!" << std::endl;
  }
  // load music
  if (!music.openFromFile("assets/MEGALOVANIA.ogg")) {
    std::cerr << "Failed to load music!" << std::endl;
  }
  music.play();
  // load font
  if (!font.loadFromFile("assets/PressStart2P-Regular.ttf")) {
    std::cerr << "Failed to load font!" << std::endl;
  }
  // setup text
  scoreText.setFont(font); scoreText.setCharacterSize(24);
  comboText.setFont(font); comboText.setCharacterSize(36);
  resultText.setFont(font); resultText.setCharacterSize(48);
  // load sound effects
  if (!donBuffer.loadFromFile("assets/don.wav")) {
    std::cerr << "Failed to load don sound!" << std::endl;
  }
  if (!kaBuffer.loadFromFile("assets/ka.wav")) {
    std::cerr << "Failed to load ka sound!" << std::endl;
  }
  donSound.setBuffer(donBuffer);
  kaSound.setBuffer(kaBuffer);
}

void PlayingState::handleEvent(sf::Event& event, Game& game) {
  // read key presses
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::F) handleInput(NoteType::Don);
    if (event.key.code == sf::Keyboard::J) handleInput(NoteType::Ka);
    if (event.key.code == sf::Keyboard::Escape) {
      game.pushState(std::make_unique<PauseState>(game.getFont())); // push pause state on top of playing state
    }
  }
}

void PlayingState::update(float dt, Game& game) {
  songTimeMs += dt;
  // is music finished?
  if (songTimeMs >= music.getDuration().asMilliseconds()) {
    game.setState(std::make_unique<ResultState>(game.getFont(), score)); // go to result screen
  }
  
  // scroll notes
  for (auto& note : beatMap.notes) {
    if (note.hit || note.missed) continue; // skip hit/missed notes
    note.x = HIT_ZONE_X + (note.timeMs - songTimeMs) * NOTE_SPEED;

    // auto miss notes that pass hit zone
    if (songTimeMs > note.timeMs + Judge::GOOD_WINDOW_MS) {
      note.missed = true;
      combo = 0;
      lastResult = "MISS";
      resultTimer = 600.0f; // how long to show result
    }
  }

  if (resultTimer > 0) resultTimer -= dt;
}

void PlayingState::handleInput(NoteType type) {
  // sound effect
  if (type == NoteType::Don) donSound.play();
  else kaSound.play();
  // find closest unhit matching note in hit window
  Note* best = nullptr;
  float bestDiff = Judge::GOOD_WINDOW_MS; // only judge notes within good window

  for (auto& note: beatMap.notes) {
    if (note.hit || note.missed) continue; // skip hit/missed notes
    if (note.type != type) continue; // skip wrong type
    float diff = std::abs(note.timeMs - songTimeMs); // distance in ms from beatmap timing
    if (diff <= bestDiff) {
      bestDiff = diff;
      best = &note;
    }
  }

  if (!best) return; // no notes in range

  // judge hit
  auto result = Judge::evaluate(songTimeMs, best->timeMs);
  best->hit = true;

  // update score/combo
  if (result == HitResult::Perfect) {
    score += 300;
    combo++;
    lastResult = "PERFECT";
  } else if (result == HitResult::Good) {
    score += 100;
    combo++;
    lastResult = "GOOD";
  } else {
    combo = 0;
    lastResult = "MISS";
  }
  resultTimer = 600.0f; // how long to show result
}

void PlayingState::render(sf::RenderWindow& window) {
  auto [W, H] = window.getSize();
  
  // clear screen
  window.clear(sf::Color::Black);

  // draw hit zone
  sf::CircleShape hitZone(NOTE_RADIUS);
  hitZone.setOrigin(hitZone.getRadius(), hitZone.getRadius());
  hitZone.setPosition(HIT_ZONE_X, 200);
  hitZone.setFillColor(sf::Color::Transparent);
  hitZone.setOutlineThickness(3);
  hitZone.setOutlineColor(sf::Color::White);
  window.draw(hitZone);

  // draw notes
  for (const auto& note : beatMap.notes) {
    if (note.hit) continue;
    if (note.missed) continue;

    sf::CircleShape circle(NOTE_RADIUS);
    circle.setOrigin(NOTE_RADIUS, NOTE_RADIUS);
    circle.setPosition(note.x, 200);
    circle.setFillColor(note.type == NoteType::Don ? sf::Color::Red : sf::Color::Blue);
    window.draw(circle);
  }

  // draw score
  scoreText.setString("Score: " + std::to_string(score));
  scoreText.setPosition(W * 0.02f, H * 0.05f);
  window.draw(scoreText);

  // draw combo
  comboText.setString(combo > 1 ? std::to_string(combo) + "x" : "");
  comboText.setOrigin(comboText.getLocalBounds().width / 2, 0);
  comboText.setPosition(W * 0.5f, H * 0.65f);
  window.draw(comboText);

  // draw last result
  if (resultTimer > 0) {
    resultText.setString(lastResult);
    resultText.setOrigin(resultText.getLocalBounds().width / 2, 0);
    resultText.setPosition(W * 0.5f, H * 0.3f);

    // fade out
    sf::Uint8 alpha = static_cast<sf::Uint8>((resultTimer / 600.0f) * 255);
    resultText.setFillColor(sf::Color(255, 255, 255, alpha));

    window.draw(resultText);
  }

  window.display();
}