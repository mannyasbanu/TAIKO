#pragma once
#include "IGameState.hpp"
#include <SFML/Graphics.hpp>

class Game;

class PauseState : public IGameState {
public:
  PauseState(sf::Font& font);
  void handleEvent(sf::Event& event, Game& game) override;
  void update(float dt, Game& game) override;
  void render(sf::RenderWindow& window) override;
private:
  sf::Text pauseText;
  sf::Text resumeText;
  sf::Text quitText;
};