#pragma once
#include "PlayingState.hpp"
#include "MenuState.hpp"
#include <SFML/Graphics.hpp>
#include "IGameState.hpp"

class ResultState : public IGameState {
public:
  ResultState(sf::Font& font, int finalScore);
  void handleEvent(sf::Event& event, Game& game) override;
  void update(float dt, Game& game) override;
  void render(sf::RenderWindow& window) override;
private:
  int finalScore;
  sf::Text scoreText;
  sf::Text retryText;
  sf::Text quitText;
};