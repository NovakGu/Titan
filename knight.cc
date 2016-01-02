#include "knight.h"

using namespace std;

Knight::Knight(Cell* c, Game* g, string colour) :ChessPiece(c, g, colour){
  name = "N";
  point = 4;
}

bool Knight::isAccessible(string prev, string next){
  int distx, disty;
  distx = abs(next[0] - prev[0]);
  disty = abs(next[1] - prev[1]);

  if (distx == 2 && disty == 1){
    return true;
  }
  else if (distx == 1 && disty == 2){
    return true;
  }
  return false;
}

bool Knight::validMoves(string colour_player, string prev, string next){
#if DEBUG
  cout << "   Knight::validMoves - from (" << prev << ") to (" << next << ")" << endl;
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
