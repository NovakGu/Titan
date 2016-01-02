#ifndef _BOT_H__
#define _BOT_H__
#include "cell.h"
#include "chesspiece.h"
#include "game.h"
#include "player.h"
#include <string>

using namespace std;

class Chesspiece;
class game;

class Bot : public Player
{
 public:
  Bot(const int, const string, Game*);
  ~Bot();
  string GenerateMove_Lv1();
  string GenerateMove_Lv2();
  string GenerateMove_Lv3();
 string GenerateMove_Lv4();
  bool move(std::istream& input);
 private:
  string side;
};
#endif
