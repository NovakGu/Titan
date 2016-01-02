
#ifndef __GAME_H__
#define __GAME_H__
#include <iostream>
#include <string>
#include <stdio.h>
#include <stdlib.h>
#include <cctype>
#include <sstream>
#include "cell.h"
#include "chesspiece.h"

/*
 * Abstract class to allow Game to send noticiations
 * to a registered object
 */
class GameNotification {
 public:
  virtual void notifyViews(std::string, std::string) = 0;
};

class Game {
  Cell **theBoard;  // The actual chess board
  int boardSize;    // Size of the board
  const std::string columns;
  GameNotification *notification;  // object registered for notifications
  int num_whiteK, num_blackK;
  Cell* cell_whiteK;
  Cell* cell_blackK;
  void clearGame();   // Frees the board.
  bool inBoundary(std::string);

 public:
  Game();
  ~Game();
  void notify(std::string, std::string);
  std::string checkWin(std::string);
  bool checkCheck(std::string, std::string);
  bool noLegalMove(std::string);
  void init(GameNotification *gameNotification, std::string); // Sets up an 8 x 8 board
  void updateKingCount(std::string, int, Cell*);
  bool setChessPiece(std::string, std::string);
  std::string setupStatus(std::string);
  Cell* getCell(std::string);
  Cell* getCellK(std::string);
  ChessPiece* getChessPiece(std::string);
  std::string getPieceName(std::string);
  bool move (std::string, std::string, std::string, std::string);
  bool nothingBetween(std::string, std::string);
};

#endif
