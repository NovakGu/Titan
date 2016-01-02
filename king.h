#ifndef _KING_H__
#define _KING_H__
#include "chesspiece.h"
#include <string>
#include <sstream>
#include <cctype>
#include <stdlib.h>

class King : public ChessPiece{
 private:
  bool danger;
  bool checked;
 public:
  King(Cell*, Game*, std::string);
  ~King();
  bool isAccessible(std::string, std::string);
  bool validMoves(std::string, std::string, std::string);
};

#endif
