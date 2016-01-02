#include "cell.h"
#include "game.h"
#include "chesspiece.h"
using namespace std;

/* Cell Constructor
   - Initiailize numNeighbours to 0
   - Create space for neighbours, maximum of 4
   - Initialize game pointer to NULL
*/
Cell::Cell() {
	game = NULL;
	piece = NULL;
}

ChessPiece* Cell::getPiece() {
	return piece;
}

void Cell::setColour(string new_colour) {
	colour = new_colour;
#if DEBUG
	//cout << "   Cell::setColour - (" << c << r << ") changed to " << colour << endl;
#endif
}

void Cell::setCoords(string new_r, string new_c) {
	r = new_r;
	c = new_c;
#if DEBUG
	//cout << "   Cell::setCoords - set (" << c << r << ")" << endl;
#endif
}

void Cell::setGame(Game * new_game) {
	game = new_game;
#if DEBUG
	//cout << "   Cell::setGame - set" << endl;
#endif
}

void Cell::setPiece(ChessPiece * new_piece) {
	piece = new_piece;
#if DEBUG
	/*
	if (piece != NULL){
	  cout << "   Cell::setPiece - set (" << c << r << ") to " << piece->getName() << endl;
	}
	else {
	  cout << "   Cell::setPiece - set (" << c << r << ") to NULL" << endl;
	}
	*/
#endif
}

std::string Cell::getCoord() {
	return c + r;
}

/*
void Cell::move(string new_pos, Cell* dest_cell) {
	string new_r = new_pos.substr(0,1);
	string new_c = new_pos.substr(1,1);
}
*/
