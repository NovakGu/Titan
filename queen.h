#ifndef _QUEEN_H__
#define _QUEEN_H__
#include "chesspiece.h"
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cctype>

class Queen : public ChessPiece{
 public:
  Queen(Cell*, Game*, std::string);
  bool isAccessible(std::string, std::string);
  bool validMoves(std::string, std::string, std::string);
};

#endif
