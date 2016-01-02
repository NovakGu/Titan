#include "pawn.h"

using namespace std;

Pawn::Pawn(Cell* c, Game* g, string colour) :ChessPiece(c, g, colour) {
  name = "P";
  point = 2;
  if (colour == "white"){  //move forward (e.g. from e2 to e3 or e2 to e4)
    dir = 1;
  }
  else {
    dir = -1;
  }
}

bool Pawn::isAccessible(string prev, string next){
  ChessPiece* dest_piece = game->getChessPiece(next);
  //Normal Movement
  if (moves == 0){
    if (next[0] == prev[0] && next[1] == prev[1] + dir && dest_piece == NULL){
      return true;
    }
    else if (next[0] == prev[0] && next[1] == prev[1] + dir*2 && dest_piece == NULL && game->nothingBetween(prev, next)){
      return true;
    }
  }
  else {
    if (next[0] == prev[0] && next[1] == prev[1] + dir && dest_piece == NULL){
      return true;
    }
  }
  //Capture
  if (abs(next[0] - prev[0]) == 1 && next[1] == prev[1] + dir && dest_piece != NULL){
    return true;
  }

  return false;
}

bool Pawn::validMoves(string colour_player, string prev, string next){
#if DEBUG
  cout << "   Pawn::validMoves - from (" << prev << ") to (" << next << ")" << endl;
#endif
  if (validMovesHelper(colour_player, prev, next)){
    if(!putKingInDanger(colour_player, prev, next)){
      if(isAccessible(prev, next)){
	return true;
      }
    }
  }
  return false;
}

