#include "NoteRender.hpp"

std::variant<sf::Sprite, sf::CircleShape> NoteRender::drawNote(const Note& note, const NoteSkin& skin) {
 if (skin.loaded) {
    const sf::Texture& tex = (note.type == NoteType::Don) ? skin.donTexture : skin.kaTexture;
    sf::Sprite sprite(tex);
    float scale = (skin.noteRadius * 2.f) / tex.getSize().x;
    sprite.setOrigin(tex.getSize().x / 2.f, tex.getSize().y / 2.f);
    sprite.setScale(scale, scale);
    return sprite;
  } else {
    sf::CircleShape circle(skin.noteRadius);
    circle.setOrigin(skin.noteRadius, skin.noteRadius);
    circle.setFillColor(note.type == NoteType::Don ? skin.donColour : skin.kaColour);
    return circle;
  }
}

std::variant<sf::Sprite, sf::CircleShape> NoteRender::drawHitZone(const NoteSkin& skin) {
  if (skin.loaded) {
    sf::Sprite sprite(skin.hitZoneTexture);
    sprite.setOrigin(skin.hitZoneTexture.getSize().x / 2.f, skin.hitZoneTexture.getSize().y / 2.f);
    sprite.setScale((skin.noteRadius * 2.f) / skin.hitZoneTexture.getSize().x, (skin.noteRadius * 2.f) / skin.hitZoneTexture.getSize().y); // desired size / original size = scale factor
    return sprite;
  } else {
    sf::CircleShape circle(skin.noteRadius + 6);
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(3);
    circle.setOutlineColor(skin.hitZoneColour);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    return circle;
  }
}

std::variant<sf::Sprite, sf::CircleShape> NoteRender::drawHitEffect(const NoteSkin& skin, const int alpha) {
  if (skin.loaded) {
    sf::Sprite sprite(skin.hitEffectTexture);
    sprite.setColor(sf::Color(255, 255, 255, alpha));
    sprite.setOrigin(skin.hitEffectTexture.getSize().x / 2.f, skin.hitEffectTexture.getSize().y / 2.f);
    float scale = (skin.noteRadius * 2.5f) / skin.hitEffectTexture.getSize().x;
    sprite.setScale(scale, scale);
    return sprite;
  } else {
    sf::CircleShape circle(skin.noteRadius + 10);
    circle.setOrigin(circle.getRadius(), circle.getRadius());
    circle.setFillColor(sf::Color::Transparent);
    circle.setOutlineThickness(3);
    circle.setOutlineColor(sf::Color(255, 255, 255, alpha));
    return circle;
  }
}