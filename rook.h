#ifndef _ROOK_H__
#define _ROOK_H__
#include "chesspiece.h"
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cctype>

class Rook : public ChessPiece{
 public:
  Rook(Cell*, Game*, std::string);
  bool isAccessible(std::string, std::string);
  bool validMoves(std::string, std::string, std::string);
};

#endif
