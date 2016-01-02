#include "chesspiece.h"

using namespace std;

ChessPiece::ChessPiece(Cell* c, Game* g, string co) {
  moves = 0;
  cell = c;
  game = g;
  colour = co;
}

ChessPiece::~ChessPiece() {
#if DEBUG
  cout << "   ChessPiece::DTOR!" << endl;
#endif
}

Cell* ChessPiece::getCell() {
  return cell;
}

string ChessPiece::getName(){
  return name;
}

string ChessPiece::getColour() {
  return colour;
}

int ChessPiece::getMoves(){
  return moves;
}

void ChessPiece::incrMoves(){
  moves += 1;
}

void ChessPiece::setCell(Cell* c) {
  cell = c;
}

int ChessPiece::getPoint(){
  return point;
}

bool ChessPiece::putKingInDanger(string colour_player, string prev, string next){
#if DEBUG
  cout << "   ChessPiece::putKingInDanger - checking (" << prev << ") to (" << next << ")" << endl;
#endif
  string colour_oppo;
  if (colour_player == "white"){
    colour_oppo = "black";
  }
  else {
    colour_oppo = "white";
  }

  ChessPiece* piece_K = game->getCellK(colour_player)->getPiece();
  ChessPiece* old_prev_piece = game->getChessPiece(prev);
  ChessPiece* old_next_piece = game->getChessPiece(next);
  //Simulate the effect of moving the piece
  game->getCell(prev)->setPiece(NULL);
  game->getCell(next)->setPiece(old_prev_piece);
  old_prev_piece->setCell(game->getCell(next));
  //Check if the King will be in check
  bool danger = game->checkCheck(piece_K->getCell()->getCoord(),colour_oppo);
  //Reverse the effect
  game->getCell(prev)->setPiece(old_prev_piece);
  game->getCell(next)->setPiece(old_next_piece);
  old_prev_piece->setCell(game->getCell(prev));
#if DEBUG
  cout << "   ChessPiece::putKingInDanger - danger = " << danger << endl;
#endif
  return danger;
}

bool ChessPiece::validMovesHelper(string colour_player, string prev, string next){
  if (prev == next){  //going to same place
    return false;
  }
  if (colour != colour_player){  //not the right player to move it
    return false;
  }
  Cell* dest = game->getCell(next);
  ChessPiece* dest_piece = game->getChessPiece(next);
  if (dest == NULL){ // out of bound
    return false;
  }
  if (dest_piece != NULL && dest_piece->getColour() == colour){  //capture the same colour
    return false;
  }
  return true;
}
