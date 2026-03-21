#pragma once
#include <SFML/Graphics.hpp>
#include "Note.hpp"
#include "Skin.hpp"
#include <variant>

namespace NoteRender {
  // variant holds either sprite or circle shape
  std::variant<sf::Sprite, sf::CircleShape> drawNote(const Note& note, const NoteSkin& skin);
  std::variant<sf::Sprite, sf::CircleShape> drawHitZone(const NoteSkin& skin);
  std::variant<sf::Sprite, sf::CircleShape> drawHitEffect(const NoteSkin& skin, const int alpha);
}