#include "rook.h"

using namespace std;

Rook::Rook(Cell* c, Game* g, string colour) :ChessPiece(c, g, colour) {
  name = "R";
  point = 5;
}

bool Rook::isAccessible(string prev, string next){
  int distx, disty;
  distx = abs(next[0] - prev[0]);
  disty = abs(next[1] - prev[1]);
  
  if (game->nothingBetween(prev, next)){  //no chesspiece between prev and next
    if (distx == 0 || disty == 0){  //horizontal and vertical
      return true;
    }
  }
  return false;
}

bool Rook::validMoves(string colour_player, string prev, string next){
#if DEBUG
  cout << "   Rook::validMoves - from (" << prev << ") to (" << next << ")" << endl;
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
