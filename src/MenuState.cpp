#include "MenuState.hpp"
#include "Game.hpp"
#include "PlayingState.hpp"
#include <iostream>

void MenuState::startPreview(const std::string& mapName) {
  if (!preview.openFromFile("assets/" + mapName + ".ogg")) {
    std::cerr << "Failed to load preview music!" << std::endl;
    return;
  }
  preview.setVolume(25);
  preview.setPlayingOffset(sf::milliseconds(PREVIEW_START_MS));
  preview.play();
}

MenuState::MenuState(sf::Font& font) {
  titleText.setFont(font);
  titleText.setString("MannyTAIKO");
  titleText.setCharacterSize(64);
  titleText.setFillColor(sf::Color::White);
  titleText.setOutlineColor(sf::Color::Black);
  titleText.setOutlineThickness(6);

  startText.setFont(font);
  startText.setString("Press ENTER to Start");
  startText.setCharacterSize(24);
  startText.setFillColor(sf::Color::White);
  startText.setOutlineColor(sf::Color::Black);
  startText.setOutlineThickness(3);

  mapText.setFont(font);
  mapText.setString("Use Arrow Keys to Select Map");
  mapText.setCharacterSize(24);
  mapText.setFillColor(sf::Color::White);
  mapText.setOutlineColor(sf::Color::Black);
  mapText.setOutlineThickness(3);

  if (!backgroundTexture.loadFromFile("assets/menu_bg.png")) {
    std::cerr << "Failed to load background texture!" << std::endl;
  }
  background.setTexture(backgroundTexture);
};

void MenuState::handleEvent(sf::Event& event, Game& game) {
  if (event.type == sf::Event::KeyPressed) {
    if (event.key.code == sf::Keyboard::Up) {
      int selected = game.getSelectedMap();
      if (selected > 0) game.setSelectedMap(selected - 1);
      else game.setSelectedMap(game.getMapCount() - 1);
      mapText.setString(game.getMapName());
      startPreview(game.getMapName());
    }
    if (event.key.code == sf::Keyboard::Down) {
      int selected = game.getSelectedMap();
      if (selected < game.getMapCount() - 1) game.setSelectedMap(selected + 1);
      else game.setSelectedMap(0);
      mapText.setString(game.getMapName());
      startPreview(game.getMapName());
    }
    if (event.key.code == sf::Keyboard::Enter) {
      preview.stop();
      game.setState(std::make_unique<PlayingState>(game.getFont(), game.getMapName())); // make_unique creates a unique pointer which automatically deletes the object when it goes out of scope
    }
  }
};

void MenuState::update(float dt, Game& game) {
  if (preview.getStatus() == sf::Music::Playing) {
    if (preview.getPlayingOffset().asMilliseconds() > PREVIEW_START_MS + PREVIEW_DURATION_MS) {
      preview.setPlayingOffset(sf::milliseconds(PREVIEW_START_MS));
    }
  }
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

  float scaleX = W / (float)backgroundTexture.getSize().x;
  float scaleY = H / (float)backgroundTexture.getSize().y;
  background.setScale(scaleX, scaleY);

  window.draw(background);
  window.draw(titleText);
  window.draw(startText);
  window.draw(mapText);
}
