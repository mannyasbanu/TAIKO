#pragma once
#include <SFML/Graphics.hpp>

class Game;

class IGameState {
public:
  virtual ~IGameState() = default;
  virtual void handleEvent(sf::Event& event) = 0;
  virtual void update(float dt, Game& game) = 0;
  virtual void render(sf::RenderWindow& window) = 0;
};