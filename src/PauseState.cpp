#include "PauseState.hpp"
#include "Game.hpp"
#include "MenuState.hpp"

PauseState::PauseState(sf::Font& font) {
  // pause text
  pauseText.setFont(font);
  pauseText.setString("Game Pause");
  pauseText.setCharacterSize(48);
  pauseText.setFillColor(sf::Color::White);
  // resume text
  resumeText.setFont(font);
  resumeText.setString("Press Enter to Resume");
  resumeText.setCharacterSize(24);
  resumeText.setFillColor(sf::Color::White);
  // quit text
  quitText.setFont(font);
  quitText.setString("Press Escape to Quit");
  quitText.setCharacterSize(24);
  quitText.setFillColor(sf::Color::White);
};

PauseState::handleEvent(sf::Event& event, Game& game) {
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Enter) game.popState(); // pop pause state to resume
    if (event.key.code == sf::Keyboard::Escape) game.changeState(std::make_unique<MenuState>(game.getFont())); // go back to menu
  }
}

PauseState::update(float dt, Game& game) {
  // animations etc
}

PauseState::render(sf::RenderWindow& window) {
  auto [W, H] = window.getSize();
  
  // center text
  pauseText.setOrigin(pauseText.getGlobalBounds().width / 2, 0);
  resumeText.setOrigin(resumeText.getGlobalBounds().width / 2, 0);
  quitText.setOrigin(quitText.getGlobalBounds().width / 2, 0);
  pauseText.setPosition(W / 2, H * 0.3f);
  resumeText.setPosition(W / 2, H * 0.5f);
  quitText.setPosition(W / 2, H * 0.7f);
  
  // draw text
  window.draw(pauseText);
  window.draw(resumeText);
  window.draw(quitText);
}