#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include "game.h"
#include "player.h"
#include "view.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include <fstream>

class Controller : public GameNotification {

  View *td; // The text display.
  View *gd; // The graphic display.    
  std::string savedfile;  // is the graphic command enabled
  Game *game;
  Player *players[2]; //pointer to two players
  std::string colours[2];
  float scores[2];
  int next_player;

  void setup(std::istream & input, Game & g);
  bool checkWin(std::string);
  void addScores(float, float);

 public:
  Controller(std::string);
  ~Controller();
  void play();
  void notifyViews(std::string, std::string);
};

#endif
