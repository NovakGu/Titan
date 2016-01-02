#ifndef _CHESSPIECE_H__
#define _CHESSPIECE_H__
#include "cell.h"
#include "game.h"
#include <string>
#include <cctype>
#include <iostream>
#include <sstream>

class ChessPiece {
 protected:
  std::string name;
  std::string colour;
  int moves;
  Cell *cell;
  Game *game;
  int point;
 public:
  ChessPiece(Cell*, Game*, std::string);
  virtual ~ChessPiece();
  Cell* getCell();
  std::string getName();
  std::string getColour();
  int getMoves();
  void incrMoves();
  void setCell(Cell*);
  int getPoint();
  //PutKingInDanger(player colour, prev, next)
  bool putKingInDanger(std::string, std::string, std::string);
  bool validMovesHelper(std::string, std::string, std::string);
  virtual bool isAccessible(std::string, std::string) = 0;
  virtual bool validMoves(std::string, std::string, std::string) = 0;
  
};



#endif
