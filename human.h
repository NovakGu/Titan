#ifndef __HUMAN_H__
#define __HUMAN_H__

#include <iostream>
#include <string>
#include "player.h"
//#include "game.h"

class Human : public Player{
 public:
  Human(const std::string, Game*);
  bool move(std::istream&);
};

#endif
