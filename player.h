#ifndef __PLAYER_H__
#define __PLAYER_H__

#include <iostream>
#include <string>
#include "game.h"

class Player{
 protected:
  Game *game;
  int type;
  std::string colour;
 public:
  Player(const int, const std::string, Game*);
  virtual ~Player();
  int getType();
  std::string getColour();
  virtual bool move(std::istream&) = 0;
};

#endif
