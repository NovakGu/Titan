#include "textdisplay.h"
using namespace std;

/* TextDisplay Constructor
   - creates 2D array of strings based on the boardSize (default is 8)
*/
TextDisplay::TextDisplay()
  : View() {
  theDisplay = new string*[boardSize];
  for (int i = 0; i < boardSize; i++) {
    theDisplay[i] = new string[boardSize];
    for (int j = 0; j < boardSize; j++) {
      if ((i + j) % 2 == 0) { //white
	theDisplay[i][j] = " ";
      }
      else {  //black
	theDisplay[i][j] = "_";
      }
    }
  }
#if DEBUG
  //cout << "   TextDisplay::TextDisplay - done initializing display of boardSize = " << boardSize << endl;
#endif
}

/* TextDisplay Destructor
 */
TextDisplay::~TextDisplay() {
  for (int i = 0; i < boardSize; i++) {
    delete[] theDisplay[i];
  }
  delete[] theDisplay;
}

/* TextDisplay::notify
   - called by the Game when a Cell has changed its chess piece
   - Parameters: pos ("e3"), piece("K")
*/
void TextDisplay::notify(string pos, string piece) {
  int col, row;
  try {
    col = columns.find(pos[0]);
    row = 8 - (int(pos[1])-48);
    if (piece == ".") {  //piece is deleted, reset square
      if ((row + col) % 2 == 0) {
	theDisplay[row][col] = " ";
      }
      else {
	theDisplay[row][col] = "_";
      }
    }
    else {  //changing piece
      theDisplay[row][col] = piece;
    }
  }
  catch (...){
    cout << "Error: invalid input of " << pos << endl;
  }
#if DEBUG
  //cout << "   TextDisplay::notify - (" << pos << ") = " << theDisplay[row][col] << endl;
#endif
}

/* TextDisplay::print
   - called by the Controller after a "move" command
*/
void TextDisplay::print(ostream &out) {
  out << endl;
  for (int i = 0; i < boardSize; i++) {
    out << 8 - i << " ";
    for (int j = 0; j < boardSize; j++) {
      out << theDisplay[i][j];
    }
    out << endl;
  }
  out << endl << "  " << columns << endl << endl;
}

void TextDisplay::notifyTurn(string a) {}

void TextDisplay::notifyStatus(string a, string b) {}

void TextDisplay::printFinalScores(float sc_white, float sc_black, ostream &out){
  out << "***Final Score***" << endl;
  out << "   White  " << sc_white << endl;
  out << "   Black  " << sc_black << endl;
}
  
