#include "PlayingState.hpp"
#include "Game.hpp"
#include "Judge.hpp"
#include <cmath>
#include <iostream>
#include "PauseState.hpp"
#include "ResultState.hpp"
#include "Skin.hpp"
#include "NoteRender.hpp"
// Manny STL ^

PlayingState::PlayingState(sf::Font& font, const std::string& mapName): font(font), mapName(mapName) {
  // load beatmap
  if (!beatMap.load("maps/" + mapName + ".txt")) {
    std::cerr << "Failed to load beatmap!" << std::endl;
  }
  // load music
  if (!music.openFromFile("assets/" + mapName + ".ogg")) {
    std::cerr << "Failed to load music!" << std::endl;
  }
  music.setVolume(25);
  music.play();
  // setup text
  scoreText.setFont(font); scoreText.setCharacterSize(24);
  comboText.setFont(font); comboText.setCharacterSize(36);
  resultText.setFont(font); resultText.setCharacterSize(48);
  scoreText.setFillColor(sf::Color::Black);
  comboText.setFillColor(sf::Color::Black);
  resultText.setFillColor(sf::Color::Black);
  // load sound effects
  if (!donBuffer.loadFromFile("assets/don.wav")) {
    std::cerr << "Failed to load don sound!" << std::endl;
  }
  if (!kaBuffer.loadFromFile("assets/ka.wav")) {
    std::cerr << "Failed to load ka sound!" << std::endl;
  }
  donSound.setBuffer(donBuffer);
  kaSound.setBuffer(kaBuffer);
  // load skin
  if (!skin.load("assets/skins/default/")) {
    std::cerr << "Failed to load skin, using fallback colours" << std::endl;
  }
}

void PlayingState::handleEvent(sf::Event& event, Game& game) {
  // read key presses
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::F) handleInput(NoteType::Don);
    if (event.key.code == sf::Keyboard::J) handleInput(NoteType::Ka);
    if (event.key.code == sf::Keyboard::Escape) {
      music.pause();
      game.pushState(std::make_unique<PauseState>(game.getFont())); // push pause state on top of playing state
    }
  }
}

void PlayingState::update(float dt, Game& game) {
  if(music.getStatus() == sf::Music::Paused) music.play();
  songTimeMs = music.getPlayingOffset().asMilliseconds() + OFFSET_MS;
  // is music finished?
  if (music.getStatus() == sf::Music::Stopped) {
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
  if (hitEffectTimer > 0) hitEffectTimer -= dt;
}

void PlayingState::handleInput(NoteType type) {
  // sound effect
  if (type == NoteType::Don) donSound.play();
  else kaSound.play();
  // hit effect
  hitEffectTimer = 100.0f;
  // only judge notes visibly touching hit zone - convert pixel overlap to ms
  float touchWindowMs = (skin.noteRadius * 2) / NOTE_SPEED;
  // find closest unhit matching note in hit window
  Note* best = nullptr;
  float bestDiff = touchWindowMs;
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
  float noteY = H * 0.5f;

  // draw hit effect
  if (hitEffectTimer > 0) {
    float alpha = (hitEffectTimer / 200.0f) * 255.f;
    auto effect = NoteRender::drawHitEffect(skin, alpha);
    std::visit([&](auto& drawable) {
      drawable.setPosition(HIT_ZONE_X, noteY);
      window.draw(drawable);
    }, effect);
  }

  // draw hit zone
  auto hitZone = NoteRender::drawHitZone(skin);
  std::visit([&](auto& drawable) {
    drawable.setPosition(HIT_ZONE_X, noteY);
    window.draw(drawable);
  }, hitZone);

  // draw notes
  for (const auto& note : beatMap.notes) {
    if (note.hit) continue;
    if (note.missed) continue;
    auto shape = NoteRender::drawNote(note, skin);
    std::visit([&](auto& drawable) {
      drawable.setPosition(note.x, noteY);
      window.draw(drawable);
    }, shape);
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
    if (lastResult == "PERFECT") resultText.setFillColor(sf::Color(skin.perfectColour.r, skin.perfectColour.g, skin.perfectColour.b, alpha));
    else if (lastResult == "GOOD") resultText.setFillColor(sf::Color(skin.goodColour.r, skin.goodColour.g, skin.goodColour.b, alpha));
    else resultText.setFillColor(sf::Color(skin.missColour.r, skin.missColour.g, skin.missColour.b, alpha));
    window.draw(resultText);
  }
}