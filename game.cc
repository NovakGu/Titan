#include "game.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"

using namespace std;

/* Game Constructor
   - initialize grid to NULL
   - initiliaze game notification to Null
   - set colours to be {0,1,2,3,4}
*/
Game::Game()
  : columns("abcdefgh") {
  theBoard = NULL;
  notification = NULL;
  num_whiteK = 0;
  num_blackK = 0;
  cell_whiteK = NULL;
  cell_blackK = NULL;
}

/* Game Destructor
   - clears the grid
*/
Game::~Game() {
  clearGame();
}

/* clearGame
   - clears the grid
*/
void Game::clearGame() {
  if (theBoard != NULL) {
    for (int i = 0; i < boardSize; i++) {
      for (int j=0; j < boardSize; j++){
	delete theBoard[i][j].getPiece();
      }
      delete [] theBoard[i];
    }
  }
}

/* inBoundary
 */
bool Game::inBoundary(string pos) {
  if (pos.length() != 2){
    return false;
  }
  if (pos[1]>56 || pos[1]<49) {
    return false;
  }
  else if (pos[0]>104 || pos[0] < 97) {
    return false;
  }
  return true;
}

/* Game::notify
   - called by Cell::notify when the Cell has changed its piece
   - pass on the new state to the notification (i.e. View) to update the display
*/
void Game::notify(string pos, string new_piece) {
#if DEBUG
  cout << "   Game::notify - received from (" << pos << ") to change to"<< new_piece << endl;
#endif
  notification->notifyViews(pos, new_piece);
}

/* Game::checkCheck()
 */
bool Game::checkCheck(string pos, string colour_oppo){
#if DEBUG
  cout << "  Game::checkCheck - checking for (" << pos << ") against " << colour_oppo << endl;
#endif
  string checkBy;
  for (int i=0; i<boardSize; i++){
    for (int j=0; j<boardSize; j++){
      ChessPiece* piece = theBoard[i][j].getPiece();
      if (piece != NULL && piece->getColour() == colour_oppo){  //opponent piece detected
	string piece_pos = theBoard[i][j].getCoord();
	if(piece_pos != pos && piece->isAccessible(piece_pos, pos)){  //if the piece can access the position
#if DEBUG
	  cout << "  Game::checkCheck - (" << pos << ") is accessible by " << piece->getName() << " at (" << theBoard[i][j].getCoord() << ")" << endl;
#endif
	  checkBy += piece_pos + " ";
	}
      }
    }
  }
  if (checkBy == ""){
    return false;
  }
  else {
    return true;
  }
}

/* Game::noLegalMove()
 */
bool Game::noLegalMove(string colour){
#if DEBUG
  cout << "  Game::noLegalMove - (" << colour << ")" << endl;
#endif
  bool unable_to_move = true;
  for (int i=0; i<boardSize; i++){
    for (int j=0; j<boardSize; j++){
      ChessPiece* piece = theBoard[i][j].getPiece();
      if(piece!=NULL && piece->getColour() == colour && unable_to_move){
	string piece_pos = theBoard[i][j].getCoord();
	for (int x=0; x<boardSize; x++){
	  for (int y=0; y<boardSize; y++){
	    string dest = theBoard[x][y].getCoord();
	    if (piece->validMoves(colour, piece_pos, dest)){
#if DEBUG
	      cout << "   Game::noLegalMove - (" << piece_pos << ") can move to (" << dest << ")" << endl;
#endif
	      unable_to_move = false;
	      return false;
	    }
	  }
	}
      }
    }
  }
  return unable_to_move;
}
	

/* Game::checkWin
   - checks the game status after each move ("", "check", "checkmate", "stalemate")
*/
string Game::checkWin(string side){
  string status;
  string colour_oppoK;
  if (side == "white"){
    colour_oppoK = "black";
  }
  else {
    colour_oppoK = "white";
  }
  string pos_oppoK = getCellK(colour_oppoK)->getCoord();
#if DEBUG
  cout << "  Game::checkWin (" << side << ") - pos_oppoK = (" << pos_oppoK << ")" << endl;
#endif
  bool checked_oppoK = checkCheck(pos_oppoK, side);
  bool no_legal_move_oppo = noLegalMove(colour_oppoK);
#if DEBUG
  cout << "  Game::checkWin (" << side << ") - checked_oppoK = " << checked_oppoK << " no_legal_move_oppo = " << no_legal_move_oppo << endl;
#endif
  if (checked_oppoK){
    if(no_legal_move_oppo){
      status = "checkmate";
    }
    else {
      status = "check";
    }
  }
  else {
    if (no_legal_move_oppo){
      status = "stalemate";
    }
    else {
      status = "";
    }
  }
  return status;
}

/* Game::init
   - initializes theGrid, neighbours and notification
*/
void Game::init(GameNotification *gameNotification, string config) {
  clearGame();  //clears theBoard first
  boardSize = 8;
  notification = gameNotification;  //set the notification
  string pieceColour;
  theBoard = new Cell*[boardSize];
  for (int i = 0; i < boardSize; i++) {  //2-D array of Cell
    theBoard[i] = new Cell[boardSize];
    for (int j = 0; j < boardSize; j++) {
      ostringstream oss;
      oss << (boardSize - i);
      theBoard[i][j].setCoords(oss.str(), columns.substr(j,1));  //initialize fields in each Cell
      theBoard[i][j].setGame(this);

      if ((i + j) % 2 == 0) {
	theBoard[i][j].setColour("white");
      }
      else {
	theBoard[i][j].setColour("black");
      }
      
      string pos = columns.substr(j,1)+oss.str();
      string pieceName = config.substr(i*boardSize + j,1);
      bool success;
      if(pieceName == "_"){
	success = setChessPiece(pos, ".");
      }
      else {
	success = setChessPiece(pos, pieceName);
      }

      if (!success) {
	cout << "Error: invalid piece config" << endl;
      }
    }
  }
#if DEBUG
  cout << "   Game::init - done initializing grid of boardSize = " << boardSize << endl;
#endif
#if DEBUG
  cout << "   Game::init - cell_whiteK = " << (cell_whiteK != NULL) << " num_blackK = " << (cell_blackK != NULL) << endl;
#endif
}

/*updateKingCount
 */
void Game::updateKingCount(string side, int c, Cell* cell){
  if (side == "white"){
    num_whiteK += c;
  }
  else {
    num_blackK += c;
  }

  if (c == 1){
    if (side == "white"){
      cell_whiteK = cell;
    }
    else {
      cell_blackK = cell;
    }
  }
  else {  //need to rescan for new king
    string deleting_pos = cell->getCoord();
    if(side == "white" && num_whiteK > 0){
      for(int i=0; i<boardSize; i++){
	for (int j=0; j<boardSize; j++){
	  ChessPiece* piece = theBoard[i][j].getPiece();
	  if(piece != NULL && piece->getName() == "K" && piece->getColour() == "white" && theBoard[i][j].getCoord() != deleting_pos){
	    cell_whiteK = &theBoard[i][j];
#if DEBUG
	    cout << "   Game::updateKingCount - updated White king to (" << cell_blackK->getCoord() << ")" << endl;
#endif
	    return;
	  }
	}
      }
    }
    if (side == "black" && num_blackK > 0){
      for(int i=0; i<boardSize; i++){
	for (int j=0; j<boardSize; j++){
	  ChessPiece* piece = theBoard[i][j].getPiece();
	  if(piece != NULL && piece->getName() == "K" && piece->getColour() == "black" && theBoard[i][j].getCoord() != deleting_pos){
	    cell_blackK = &theBoard[i][j];
#if DEBUG
	    cout << "   Game::updateKingCount - updated Black king to (" << cell_blackK->getCoord() << ")" << endl;
#endif
	    return;
	  }
	}
      }
    }
  }

#if DEBUG
  cout << "   Game::updateKingCount - num_whiteK = " << num_whiteK << " num_blackK = " << num_blackK << endl;
#endif
}

/* setPiece
 */
bool Game::setChessPiece(string pos, string p){
  string pieceColour;
  char pieceName = p[0];
  int col, row;

  if (isupper(pieceName)) {
    pieceColour = "white";
  }
  else {
    pieceColour = "black";
  }

  if(!inBoundary(pos)){
    cout << "Error: invalid position input of " << pos << endl;
    return false;
  }

  col = columns.find(pos[0]);
  row = 8 - (pos[1] - 48);

#if DEBUG
  cout << "   Game::setChessPiece - setting (" << row << "," << col << ")" << endl;
#endif

  if (tolower(pieceName) == '.'){
    theBoard[row][col].setPiece(NULL);
  }
  else if (tolower(pieceName) == 'p'){
    theBoard[row][col].setPiece(new Pawn(&theBoard[row][col], this, pieceColour));
  }
  else if (tolower(pieceName) == 'r'){
    theBoard[row][col].setPiece(new Rook(&theBoard[row][col], this, pieceColour));
  }
  else if (tolower(pieceName) == 'n'){
    theBoard[row][col].setPiece(new Knight(&theBoard[row][col], this, pieceColour));
  }
  else if (tolower(pieceName) == 'b'){
    theBoard[row][col].setPiece(new Bishop(&theBoard[row][col], this, pieceColour));
  }
  else if (tolower(pieceName) == 'q'){
    theBoard[row][col].setPiece(new Queen(&theBoard[row][col], this, pieceColour));
  }
  else if (tolower(pieceName) == 'k'){
    theBoard[row][col].setPiece(new King(&theBoard[row][col], this, pieceColour));
  }
  else {
    cout << "Error: invalid chess piece name of " << p << endl;
    return false;
  }
  notify(pos, p);
  return true;
}

/* setupStatus
   - Checks if the board contains exactly one white king and exactly one black king
*/
string Game::setupStatus(string colour_next_player) {
  ostringstream ossw, ossb;
  ossw << num_whiteK;
  ossb << num_blackK;
  string status = "# whiteK: " + ossw.str() + " and # blackK: " + ossb.str();
  if (num_whiteK == 1 && num_blackK == 1) {
    string pos_whiteK = cell_whiteK->getCoord();
    string pos_blackK = cell_blackK->getCoord();
    int distx = abs(pos_whiteK[0] - pos_blackK[0]);
    int disty = abs(pos_whiteK[1] - pos_blackK[1]);
    if (distx <= 1 && disty <= 1){
      status = "kings are adjacent to each other";
    }
    else{
      bool checked_whiteK = checkCheck(pos_whiteK, "black");  //cannot have any king in check
      bool checked_blackK = checkCheck(pos_blackK, "white");
      if (checked_whiteK && checked_blackK){
	status = "both Kings are in check";
      }
      else if (checked_whiteK){
	status = "White King is in check";
      }
      else if (checked_blackK){
	status = "Black King is in check";
      }
      else {
	bool no_pawn_at_end = true;
	for (int i=0; i<8; i++){
	  if (theBoard[0][i].getPiece() != NULL && theBoard[0][i].getPiece()->getName() == "P"){
	    no_pawn_at_end = false;
	  }
	  if (theBoard[7][i].getPiece() != NULL && theBoard[7][i].getPiece()->getName() == "P"){
	    no_pawn_at_end = false;
	  }
	}
	if (no_pawn_at_end){
	  status = "Complete";
	}
	else {
	  status = "there are Pawns on the end rows";
	}
      }
    }
  }
  return status;
}

/* getCell
 */
Cell* Game::getCell(string pos) {
  int col, row;
  Cell* cell = NULL;
  if(inBoundary(pos)){
    col = columns.find(pos[0]);
    row = 8 - (int(pos[1])-48);
    cell = &theBoard[row][col];
  }
  else {
    cout << "Error: invalid position input of " << pos << endl;
  }
  return cell;
}

/* getCellK
 */
Cell* Game::getCellK(string colour){
  if (colour == "white"){
    return cell_whiteK;
  }
  else {
    return cell_blackK;
  }
}

/* getChessPiece
 */
ChessPiece* Game::getChessPiece(string pos) {
  Cell* cell = getCell(pos);
  return cell->getPiece();
}

/* getPieceName
 */

string Game::getPieceName(string pos) {
  ChessPiece* piece = getChessPiece(pos);
  return piece->getName();
}

/* move
 */
bool Game::move(string colour_player, string old_pos, string new_pos, string extra) {
  if (extra != "" && extra != "R" && extra != "r" && extra != "B" && extra != "b" && extra != "Q" && extra != "q" && extra != "N" && extra != "n") {
    cout << "Error: invalid promotion from Pawn to " << extra << endl;
    return false;
  }
#if DEBUG
  cout << "   Game::move - EXTRA = " << extra << endl;
#endif

  ChessPiece* piece = getChessPiece(old_pos);
  ChessPiece* dest_piece = getChessPiece(new_pos);
  string pieceName = getPieceName(old_pos);
  string pieceColour = piece->getColour();

  bool valid = piece->validMoves(colour_player, old_pos, new_pos);
  if (valid) {
    int old_col, old_row, new_col, new_row;
    old_col = columns.find(old_pos[0]);
    old_row = 8 - (int(old_pos[1])-48);
    new_col = columns.find(new_pos[0]);
    new_row = 8 - (int(new_pos[1])-48);
    theBoard[old_row][old_col].setPiece(NULL);  //moving piece away

    if (extra == "") {  //not a pawn trying to be promoted
      theBoard[new_row][new_col].setPiece(piece);  //moving piece to new position
      piece->setCell(&theBoard[new_row][new_col]);
      piece->incrMoves();
      if (piece->getName() == "K"){
	if(piece->getColour() == "white"){
	  cell_whiteK = &theBoard[new_row][new_col];
	}
	else {
	  cell_blackK = &theBoard[new_row][new_col];
	}
      }
      //Castling
      if (piece->getName() == "K" && abs(new_col - old_col) == 2){
	Cell* old_rook_cell;
	Cell* new_rook_cell;
	ChessPiece* rook;
	if (colour_player == "white"){
	  if(piece->getCell()->getCoord() == "g1"){
	    old_rook_cell = getCell("h1");
	    new_rook_cell = getCell("f1");
	    rook = getChessPiece("h1");
	  }
	  else{
	    old_rook_cell = getCell("a1");
	    new_rook_cell = getCell("d1");
	    rook = getChessPiece("a1");
	  }
	}
	else {
	  if(piece->getCell()->getCoord() == "g8"){
	    old_rook_cell = getCell("h8");
	    new_rook_cell = getCell("f8");
	    rook = getChessPiece("h8");
	  }
	  else{
	    old_rook_cell = getCell("a8");
	    new_rook_cell = getCell("d8");
	    rook = getChessPiece("a8");
	  }
	}
	old_rook_cell->setPiece(NULL);
	new_rook_cell->setPiece(rook);
	rook->setCell(new_rook_cell);
	rook->incrMoves();
	notify(old_rook_cell->getCoord(), ".");  //updating views
	if(colour_player == "black"){
	  notify(new_rook_cell->getCoord(),"r");
	}
	else {
	  notify(new_rook_cell->getCoord(),"R");
	}
      }
    }
    else {  //Pawn promotion
      delete piece;
      if (extra == "Q" || extra == "q") {  //pawn promiting to a queen
	piece = new Queen(&theBoard[new_row][new_col], this, pieceColour);
      }
      else if (extra == "R" || extra == "r") {
	piece = new Rook(&theBoard[new_row][new_col], this, pieceColour);
      }
      else if (extra == "N" || extra == "n") {
	piece = new Knight(&theBoard[new_row][new_col], this, pieceColour);
      }
      else if (extra == "B" || extra == "b") {
	piece = new Bishop(&theBoard[new_row][new_col], this, pieceColour);
      }
      theBoard[new_row][new_col].setPiece(piece);
      piece->incrMoves();
      pieceName = extra;
    }

    if (dest_piece != NULL) {  //capturing enemy piece
      delete dest_piece;
    }

    notify(old_pos, ".");  //updating views
    if(colour_player == "black"){
      pieceName[0] = tolower(pieceName[0]);
    }
    notify(new_pos, pieceName);
    return true;
  }
  else {
#if DEBUG
    cout << "Error: invalid move of " << pieceName << " from " << old_pos << " to " << new_pos << endl;
#endif
    return false;
  }
}


/*nothingBetween
 */
bool Game::nothingBetween(string start, string end){
  int distx, disty;  //distance, absolute value
  distx = abs(end[0] - start[0]);
  disty = abs(end[1] - start[1]);

  if (distx != 0 && disty != 0 && distx != disty){  //must be either horizontal, vertical or diagonal
    return false;
  }

  int dirx, diry;  //direction, +/- 1
  if (distx == 0) {
    dirx = 0;
  } else {
    dirx = distx / (end[0] - start[0]);
  }
  if (disty == 0){
    diry = 0;
  } else {
    diry = disty / (end[1] - start[1]);
  }

  bool nothing = true;

  if (distx == 0){
    for (int j=1; j<disty; j++){
      string pos = start;
      pos[1] += j * diry;
#if DEBUG
      cout << "   Game::nothingBetween - @ (" << pos  << ") = " << (getChessPiece(pos) != NULL) << endl;
#endif
      if (getChessPiece(pos) != NULL){
	nothing = false;
      }
    }
  }
  if (disty == 0){
    for (int i=1; i<distx; i++){
      string pos = start;
      pos[0] += i * dirx;
      if (getChessPiece(pos) != NULL){
	nothing = false;
      }
    }
  }
  if (distx == disty){
    for (int i=1; i<distx; i++){
      string pos = start;
      pos[0] += i * dirx;
      pos[1] += i * diry;
      if (getChessPiece(pos) != NULL){
	nothing = false;
      }
    }
  }
#if DEBUG
  cout << "   Game::nothingBetween - from (" << start  << ") to (" << end << ") = " << nothing << endl;
#endif
  return nothing;
}
