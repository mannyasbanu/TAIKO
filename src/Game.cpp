#include "Game.hpp"
#include "Judge.hpp"
#include <cmath>
#include <iostream>
// Manny STL ^

Game::Game(): window(sf::VideoMode(1400, 400), "MannyTaiko") {
  // set fps limit
  window.setFramerateLimit(60);
  // load beatmap
  if (!beatMap.load("maps/test.txt")) {
    std::cerr << "Failed to load beatmap!" << std::endl;
  }
  // load music
  if (!music.openFromFile("assets/test.ogg")) {
    std::cerr << "Failed to load music!" << std::endl;
  }
}

void Game::run() {
  sf::Clock clock;
  // run game until window is closed
  while (window.isOpen()) {
    float dt = clock.restart().asMilliseconds();
    songTimeMs += dt;
    // game loop
    processEvents();
    update(dt);
    render();
  }
}

void Game::processEvents() {
  // create event object and poll events
  sf::Event event;
  while (window.pollEvent(event)) {
    // read for window close
    if (event.type == sf::Event::Closed) {
      window.close();
    }
    // read key presses
    if (event.type == sf::Event::KeyPressed) {
      if (event.key.code == sf::Keyboard::F) handleInput(NoteType::Don);
      if (event.key.code == sf::Keyboard::J) handleInput(NoteType::Ka);
      if (event.key.code == sf::Keyboard::Escape) window.close();
    }
  }
}

void Game::update(float dt) {
  // scroll notes
  for (auto& note : beatMap.notes) {
    if (note.hit || note.missed) continue; // skip hit/missed notes
    note.x = HIT_ZONE_X + (note.timeMs - songTimeMs) * NOTE_SPEED;

    // auto miss notes that pass hit zone
    if (note.x < HIT_ZONE_X - NOTE_RADIUS * 2) {
      note.missed = true;
      combo = 0;
      lastResult = "MISS";
      resultTimer = 600.0f; // how long to show result
    }
  }

  if (resultTimer > 0) resultTimer -= dt;

  std::cout << "Song Time: " << songTimeMs << std::endl;
}

void Game::handleInput(NoteType type) {
  // find closest unhit matching note in hit window
  Note* best = nullptr;
  float bestDist = 9999.0f;

  for (auto& note: beatMap.notes) {
    if (note.hit || note.missed) continue; // skip hit/missed notes
    if (note.type != type) continue; // skip wrong type
    float dist = std::abs(note.timeMs - songTimeMs); // distance in ms from beatmap timing
    if (dist < bestDist) {
      bestDist = dist;
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

void Game::render() {
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

  // draw score/combo once font added

  window.display();
}