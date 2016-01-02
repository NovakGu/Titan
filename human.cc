#include "human.h"

using namespace std;

/*Constructor
*/
Human::Human(const string colour, Game* game)
  : Player(0, colour, game){
#if DEBUG
  cout << "   Human::ctor - new human player. Colour = " << colour << endl;
#endif

}

/*getMove
*/
bool Human::move(istream& input){
  string old_pos, new_pos, extra;
  input >> old_pos;
  input >> new_pos;
#if DEBUG
  cout << "**Human::move - from (" << old_pos << ") to (" << new_pos << ")" << endl;
#endif
  ChessPiece* piece = game->getChessPiece(old_pos);
  if (piece == NULL){
    cout << "Error: invalid input, no chess piece at " << old_pos << endl;
    return false;
  }

  if (piece->getName() == "P" && (new_pos[1] == '1' || new_pos[1] == '8')){  //Pawn promition
    input >> extra;
  }
  bool success = game->move(colour, old_pos, new_pos, extra);
  return success;
}
