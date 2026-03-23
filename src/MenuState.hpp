#pragma once
#include "IGameState.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>

class MenuState : public IGameState {
public:
  MenuState(sf::Font& font);
  void handleEvent(sf::Event& event, Game& game) override;
  void update(float dt, Game& game) override;
  void render(sf::RenderWindow& window) override;

private:
  sf::Text titleText;
  sf::Text startText;
  sf::Text mapText;
  sf::Texture backgroundTexture;
  sf::Sprite background;
  sf::Music preview;
  std::string currentPreview;
  void startPreview(const std::string& mapName);
  static constexpr float PREVIEW_START_MS = 10000.0f;
  static constexpr float PREVIEW_DURATION_MS = 8000.0f;
};