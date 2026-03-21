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
};

void MenuState::handleEvent(sf::Event& event, Game& game) {
  if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Enter) {
    game.setState(std::make_unique<PlayingState>(game.getFont())); // make_unique creates a unique pointer which automatically deletes the object when it goes out of scope
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

  window.draw(titleText);
  window.draw(startText);
}