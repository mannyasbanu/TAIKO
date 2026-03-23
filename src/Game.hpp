#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <vector>
#include "Note.hpp"
#include "BeatMap.hpp"
#include <memory>
#include "IGameState.hpp"
#include "MenuState.hpp"
#include "Skin.hpp"
// Manny STL ^

class Game {
public:
  Game();
  void run();

  // state management
  void setState(std::unique_ptr<IGameState> newState); // replace current
  void pushState(std::unique_ptr<IGameState> newState); // push on top of current
  void popState(); // return to previous state

  sf::Font& getFont() { return font; } // for states to access the font
  sf::Sound& getDonSound() { return donSound; }
  sf::Sound& getKaSound() { return kaSound; }

  std::string getMapName();
  int getSelectedMap() const { return selectedMap; }
  int getMapCount() const { return mapList.size(); }
  void setSelectedMap(int index) { selectedMap = index; }

private:
  void processEvents(); // process input
  void update(float dt); // update game state (dt is time since last frame in milliseconds)
  void render(); // render to screen

  sf::RenderWindow window;
  sf::Font font;
  std::vector<std::unique_ptr<IGameState>> states; // game state stack

  std::vector<std::string> mapList;
  int selectedMap = 0;

  // sound effects
  sf::SoundBuffer donBuffer, kaBuffer;
  sf::Sound donSound, kaSound;
};