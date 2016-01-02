#ifndef _BISHOP_H__
#define _BISHOP_H__
#include "chesspiece.h"
#include <string>
#include <sstream>
#include <stdlib.h>
#include <cctype>

class Bishop : public ChessPiece{
 public:
  Bishop(Cell*, Game*, std::string);
  bool isAccessible(std::string, std::string);
  bool validMoves(std::string, std::string, std::string);
};

#endif
