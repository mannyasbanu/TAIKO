#pragma once
#include "IGameState.hpp"
#include <SFML/Graphics.hpp>

class MenuState : public IGameState {
public:
  MenuState(sf::Font& font);
  void handleEvent(sf::Event& event, Game& game) override;
  void update(float dt, Game& game) override;
  void render(sf::RenderWindow& window) override;

private:
  sf::Text titleText;
  sf::Text startText;
};