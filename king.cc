#include "king.h"

using namespace std;

King::King(Cell* c, Game* g, string colour) :ChessPiece(c, g, colour) {
  name = "K";
  point = 8;
  game->updateKingCount(colour, 1, cell);
#if DEBUG
  cout << "   King::ctor - " << colour << " has a king at " << cell->getCoord() << endl;
#endif
}

King::~King(){
#if DEBUG
  cout << "   King::dtor - " << colour << " has lost a King!" << endl;
#endif
  game->updateKingCount(colour, -1, cell);
}

bool King::isAccessible(string prev, string next){
  int distx, disty;
  distx = (next[0] - prev[0]);
  disty = (next[1] - prev[1]);
  
  if(abs(distx) <= 1 && abs(disty) <= 1){
    return true;
  }
  return false;
}

bool King::validMoves(string colour_player, string prev, string next) {
#if DEBUG
  cout << "   King::validMoves - from (" << prev << ") to (" << next << ")" << endl;
#endif
  if(!validMovesHelper(colour_player, prev, next)){
    return false;
  }
  
  int distx, disty;
  distx = (next[0] - prev[0]);
  disty = (next[1] - prev[1]);

  string colour_oppo;
  if (colour_player == "white"){
    colour_oppo = "black";
  }
  else {
    colour_oppo = "white";
  }

  //Castling
  if (abs(distx) == 2){
    if (moves != 0){  //king has not moved before
      return false;
    }
    Cell* cell_R = NULL;
    ChessPiece* rook = NULL;
    string between_pos;
    if (colour_player == "white"){
      if (next == "g1"){
	cell_R = game->getCell("h1");
	between_pos = "f1";
      }
      else if (next == "c1"){
	cell_R = game->getCell("a1");
	between_pos = "d1";
      }
    }
    else {
      if (next == "g8"){
	cell_R = game->getCell("h8");
	between_pos = "f8";
      }
      else if (next == "c8"){
	cell_R = game->getCell("a8");
	between_pos = "d8";
      }
    }
    if (cell_R == NULL){  //not g1, c1 for white or g8, c8 for black
      return false;
    }
    else {
      rook = cell_R->getPiece();
    }
    if (rook == NULL || rook->getName() != "R"){
      //cout << "Error: invalid castling move, Rook is no longer in its original position" << endl;
      return false;
    }
    if (rook->getMoves() != 0){
      //cout << "Error: castle has moved before, unable to castle" << endl;
      return false;
    }
    //Need to check its current, final and between positions are not in check
    if(!game->checkCheck(prev, colour_oppo)){
      if(!game->checkCheck(next, colour_oppo)){
	if(!game->checkCheck(between_pos, colour_oppo)){
	  return true;
	}
	else {
	  //cout << "Error: invalid castling move, King cannot pass through a cell that's in check" << endl;
	  return false;
	}
      }
      else {
	//cout << "Error: invalid castling move, King cannot move to a checked position" << endl;
	return false;
      }
    }
    else{
      //cout << "Error: invalid castling move, King is currently in check" << endl;
      return false;
    }
    return false;
  }
  //Normal move
  else if (abs(distx) <= 1 && abs(disty) <= 1){
    if(!putKingInDanger(colour_player, prev, next)){
      return true;
    }
    else {
      //cout << "Error: invalid move, King cannot move to a checked position" << endl;
      return false;
    }
  }
  return false;
}
