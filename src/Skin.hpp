#pragma once
#include <SFML/Graphics.hpp>

struct NoteSkin {
  // textures
  sf::Texture donTexture;
  sf::Texture kaTexture;
  
  // fallback colours
  sf::Color donColour = sf::Color(220, 60, 60);
  sf::Color kaColour = sf::Color(60, 120, 220);

  // note size
  float noteRadius = 50.0f;

  // hit zone
  sf::Texture hitZoneTexture;
  sf::Color hitZoneColour = sf::Color(255, 255, 255, 128);

  // hit effects
  sf::Color perfectColour = sf::Color(255, 215, 0);
  sf::Color goodColour = sf::Color(100, 220, 100);
  sf::Color missColour = sf::Color(180, 180, 180);

  sf::Texture hitEffectTexture;

  bool loaded = false;

  // load textures
  bool load(const std::string& skinPath) {
    loaded = true;
    if (!donTexture.loadFromFile(skinPath + "don.png")) loaded = false;
    if (!kaTexture.loadFromFile(skinPath + "ka.png")) loaded = false;
    if (!hitZoneTexture.loadFromFile(skinPath + "hitzone.png")) loaded = false;
    if (!hitEffectTexture.loadFromFile(skinPath + "hiteffect.png")) loaded = false;

    return loaded;
  }
};
