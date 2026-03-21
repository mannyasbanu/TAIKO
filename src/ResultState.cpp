#include "ResultState.hpp"
#include "Game.hpp"

ResultState::ResultState(sf::Font& font, int finalScore): finalScore(finalScore) {
  // score text
  scoreText.setFont(font);
  scoreText.setString("Final Score: " + std::to_string(finalScore));
  scoreText.setCharacterSize(48);
  scoreText.setFillColor(sf::Color::White);
  // retry text
  retryText.setFont(font);
  retryText.setString("Press Enter to Retry");
  retryText.setCharacterSize(24);
  retryText.setFillColor(sf::Color::White);
  // quit text
  quitText.setFont(font);
  quitText.setString("Press Escape to Quit");
  quitText.setCharacterSize(24);
  quitText.setFillColor(sf::Color::White);
};

void ResultState::handleEvent(sf::Event& event, Game& game) {
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Enter) {
      game.setState(std::make_unique<PlayingState>(game.getFont())); // restart game
    }
    if (event.key.code == sf::Keyboard::Escape) {
      game.setState(std::make_unique<MenuState>(game.getFont())); // go back to menu
    }
  }
}

void ResultState::update(float dt, Game& game) {
  // animations etc
}

void ResultState::render(sf::RenderWindow& window) {
  auto [W, H] = window.getSize();
  
  // center text
  scoreText.setOrigin(scoreText.getGlobalBounds().width / 2, 0);
  retryText.setOrigin(retryText.getGlobalBounds().width / 2, 0);
  quitText.setOrigin(quitText.getGlobalBounds().width / 2, 0);
  scoreText.setPosition(W / 2, H * 0.3f);
  retryText.setPosition(W / 2, H * 0.5f);
  quitText.setPosition(W / 2, H * 0.7f);
  
  // draw text
  window.draw(scoreText);
  window.draw(retryText);
  window.draw(quitText);
}