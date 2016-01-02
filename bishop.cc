#include "bishop.h"

using namespace std;

Bishop::Bishop(Cell* c, Game* g, string colour) :ChessPiece(c, g, colour){
  name = "B";
  point = 3;
}

bool Bishop::isAccessible(string prev, string next){
  int distx, disty;
  distx = abs(next[0] - prev[0]);
  disty = abs(next[1] - prev[1]);
  
  if (game->nothingBetween(prev, next)){  //no chesspiece between prev and next
    if (distx == disty){  //diagonal
      return true;
    }
  }
  return false;
}

bool Bishop::validMoves(string colour_player, string prev, string next){
#if DEBUG
  cout << "   Bishop::validMoves - from (" << prev << ") to (" << next << ")" << endl;
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
