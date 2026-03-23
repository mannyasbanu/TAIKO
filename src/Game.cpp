#include "Game.hpp"
#include "Judge.hpp"
#include <cmath>
#include <iostream>
#include <filesystem>
// Manny STL ^

Game::Game(): window(sf::VideoMode(1400, 800), "MannyTaiko") {
  // set fps limit
  window.setFramerateLimit(200);
  // load font
  if (!font.loadFromFile("assets/PressStart2P-Regular.ttf")) {
    std::cerr << "Failed to load font!" << std::endl;
  }
  // start on menu
  states.push_back(std::make_unique<MenuState>(font));
  // get map list
  for (const auto& entry : std::filesystem::directory_iterator("maps/"))
    if (entry.path().extension() == ".txt")
      mapList.push_back(entry.path().stem().string());
}

void Game::run() {
  sf::Clock clock;
  // run game until window is closed
  while (window.isOpen()) {
    float dt = clock.restart().asMilliseconds();
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
    // handle events
    if (!states.empty()) {
      states.back()->handleEvent(event, *this); // pass event to current state
    }
  }
}

void Game::update(float dt) {
  if (!states.empty()) {
    states.back()->update(dt, *this); // update current state
  }
}

void Game::render() {
  auto [W, H] = window.getSize();
  
  // clear screen
  window.clear(sf::Color::Black);

  // draw
  if (!states.empty()) {
    states.back()->render(window); // render current state
  }

  window.display();
}

void Game::setState(std::unique_ptr<IGameState> newState) {
  states.clear(); // remove all states
  states.push_back(std::move(newState)); // add new state
}

void Game::pushState(std::unique_ptr<IGameState> newState) {
  states.push_back(std::move(newState)); // add new state on top of current
}

void Game::popState() {
  if (!states.empty()) {
    states.pop_back(); // remove current state, revealing previous
  }
}

std::string Game::getMapName() {
  if (selectedMap >= 0 && selectedMap < mapList.size()) {
    return mapList[selectedMap];
  }
  return "";
}