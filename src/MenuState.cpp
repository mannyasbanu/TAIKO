#include "MenuState.hpp"
#include "Game.hpp"
#include "PlayingState.hpp"

MenuState::MenuState(sf::Font& font) {
  titleText.setFont(font);
  titleText.setString("MannyTAIKO");
  titleText.setCharacterSize(64);
  titleText.setFillColor(sf::Color::White);

  startText.setFont(font);
  startText.setString("Press ENTER to Start");
  startText.setCharacterSize(24);
  startText.setFillColor(sf::Color::White);

  mapText.setFont(font);
  mapText.setString("Use Arrow Keys to Select Map");
  mapText.setCharacterSize(24);
  mapText.setFillColor(sf::Color::White);
};

void MenuState::handleEvent(sf::Event& event, Game& game) {
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Up) {
      int selected = game.getSelectedMap();
      if (selected > 0) game.setSelectedMap(selected - 1);
      else game.setSelectedMap(game.getMapCount() - 1);
    }
    if (event.key.code == sf::Keyboard::Down) {
      int selected = game.getSelectedMap();
      if (selected < game.getMapCount() - 1) game.setSelectedMap(selected + 1);
      else game.setSelectedMap(0);
    }
    mapText.setString(game.getMapName());
    if (event.key.code == sf::Keyboard::Enter) {
      game.setState(std::make_unique<PlayingState>(game.getFont(), game.getMapName())); // make_unique creates a unique pointer which automatically deletes the object when it goes out of scope
    }
  }
};

void MenuState::update(float dt, Game& game) {
  // animate title later
};

void MenuState::render(sf::RenderWindow& window) {
  auto [W, H] = window.getSize();

  titleText.setOrigin(titleText.getLocalBounds().width / 2, 0);
  titleText.setPosition(W * 0.5f, H * 0.3f);

  startText.setOrigin(startText.getLocalBounds().width / 2, 0);
  startText.setPosition(W * 0.5f, H * 0.55f);

  mapText.setOrigin(mapText.getLocalBounds().width / 2, 0);
  mapText.setPosition(W * 0.5f, H * 0.45f);

  window.draw(titleText);
  window.draw(startText);
  window.draw(mapText);
}
