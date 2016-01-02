#ifndef _PAWN_H__
#define _PAWN_H__
#include "chesspiece.h"
#include <string>
#include <sstream>
#include <cctype>
#include <stdlib.h>

class Pawn : public ChessPiece{
  int dir;
 public:
  Pawn(Cell*, Game*, std::string);
  bool isAccessible(std::string, std::string);
  bool validMoves(std::string, std::string, std::string);
};

#endif
