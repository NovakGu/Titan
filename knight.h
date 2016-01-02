#ifndef _KNIGHT_H__
#define _KNIGHT_H__
#include "chesspiece.h"
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cctype>


class Knight : public ChessPiece{
 public:
  Knight(Cell*, Game*, std::string);
  bool isAccessible(std::string, std::string);
  bool validMoves(std::string, std::string, std::string);
};

#endif
