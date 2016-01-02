#include "controller.h"
#include "textdisplay.h"
#include "graphicdisplay.h"
#include "human.h"
#include "bot.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

Controller::Controller(string file) {
  game = new Game;
  savedfile = file;
  for (int i = 0; i < 2; i++) {
    players[i] = NULL;
    scores[i] = 0.0;
    if (i==0){
      colours[i] = "white";
    }
    else {
      colours[i] = "black";
    }
  }
  td = NULL;
  gd = NULL;
#if DEBUG
  cout << "   Controller::Controller - done initialization with savedfile = " << savedfile << endl;
#endif
}

/*
 * Update the View(s) to indicate the new game state
 */
void Controller::notifyViews(string pos, string piece) {
#if DEBUG
  cout << "   Controller::notifyViews - notifying views to change (" << pos << ") to " << piece << endl;
#endif
  td->notify(pos, piece);
  gd->notify(pos, piece);
}

/*
 * Called when command setup is received
 */
void Controller::setup(istream & input, Game & g) {
  string op, piece, pos, colour, status;
  while (1) {
    input >> op;
    if (op == "done") {
      //Check if the game setup is complete based on the next player
      status = game->setupStatus(colours[next_player]);
      if (status == "Complete") {
	break;
      }
      else {
	cout << "Error: cannot exit setup because " << status << endl;
      }
    }
    else if (op == "+") {
      input >> piece;
      input >> pos;
      if (game->getCell(pos) != NULL){  //not invalid position input
	ChessPiece* old_piece = game->getChessPiece(pos);
	if (old_piece != NULL){  //previously occupied by another piece
#if DEBUG
	  cout << "   Controller::setup + deleting old_piece at (" << pos << "), name = " << old_piece->getName() << endl;
#endif
	  delete old_piece;
	}
	bool success = game->setChessPiece(pos, piece);
	if (success){  //not invalid piece input
	  td->print(cout);
	}
      }
    }
    else if (op == "-") {
      input >> pos;
      if (game->getCell(pos) != NULL){
	ChessPiece* old_piece = game->getChessPiece(pos);
	if (old_piece != NULL){
#if DEBUG
	  cout << "   Controller::setup + deleting old_piece at (" << pos << "), name = " << old_piece->getName() << endl;
#endif
	  delete old_piece;
	  bool success = game->setChessPiece(pos, ".");
	  if (success){
	    td->print(cout);
	  }
	}
#if DEBUG
	else {
	  cout << "Nothing to delete" << endl;
	}
#endif
      }
    }
    else if (op == "=") {
      input >> colour;
      if (colour == "white") {
	next_player = 0;
      }
      else if (colour == "black") {
	next_player = 1;
      }
      else {
	cout << "Error: invalid colour input. Enter either \"white\" or \"black\"" << endl;
      }
      gd->notifyTurn(colours[next_player]);
    }
  }
}

bool Controller::checkWin(string colour_this_player) {
#if DEBUG
  cout << "**Controller::checkWin (" << colour_this_player << ")" << endl;
#endif
  string result = game->checkWin(colour_this_player);
  string colour_next_player;
  if(colour_this_player == "white"){
    colour_next_player = "black";
  }
  else {
    colour_next_player = "white";
  }
  
  if (result == ""){
    gd->notifyStatus("",colour_next_player);
    //gd->notifyTurn(colour_this_player);
    return false;
  }
  else if (result == "check"){
    cout << (char)toupper(colour_next_player[0]) << colour_next_player.substr(1) << " is in check." << endl;
    gd->notifyStatus("check",colour_this_player);
    //gd->notifyTurn(colour_next_player);
    return false;
  }
  else if (result == "checkmate"){
    cout << "Checkmate! " << (char)toupper(colour_this_player[0]) << colour_this_player.substr(1) << " wins!" << endl;
    gd->notifyStatus("checkmate",colour_this_player);
    gd->notifyTurn("");
    if(colour_this_player == "white"){
      addScores(1,0);
    }
    else {
      addScores(0,1);
    }
    return true;
  }
  else if (result == "stalemate"){
    cout << "Stalemate! " << (char)toupper(colour_next_player[0]) << colour_next_player.substr(1) << " is unable to make any legal move!" << endl;
    gd->notifyStatus("stalemate",colour_this_player);
    gd->notifyTurn("");
    addScores(0.5, 0.5);
    return true;
  }
  else {
    cout << "Error: unusual result = " << result << endl;
    return false;
  }
}

void Controller::play() {
#if DEBUG
  cout << "   Controller::play - STARTED!!" << endl;
#endif
  string cmd;
  while (cin >> cmd) {
    if (cmd == "game") {
      string config;
      string first_player;
      if (savedfile == ""){
	config = "rnbqkbnrpppppppp________________________________PPPPPPPPRNBQKBNR";
	first_player = "W";
      }
      else {
	ifstream infile(savedfile.c_str());
	for (int i=0; i<8; i++){
	  string s;
	  infile >> s;
	  config += s;
	  //cout << "Config: " << config << endl;
	}
	infile >> first_player;
      }
      if (first_player == "W"){
	next_player = 0;
      }
      else {
	next_player = 1;
      }
      
      delete td;
      delete gd;
      td = new TextDisplay();
      gd = new GraphicDisplay();

      gd->notifyStatus("",colours[next_player]);
      gd->notifyTurn(colours[next_player]);

      game->init(this, config);
      if(checkWin("white") && checkWin("black")){
	cout << "Error: cannot have both Kings in check during initilization. Terminating program." << endl;
	return;
      }
      td->print(cout);
      for (int i = 0; i < 2; i++) {  //2 players
	string playerType;
	cin >> playerType;
	if (playerType == "human") {
	  players[i] = new Human(colours[i], game);
	}
	else {
	  istringstream iss(playerType.substr(playerType.length() - 1));
	  int diff;
	  iss >> diff;
	  players[i] = new Bot(diff, colours[i], game);
	}
#if DEBUG
	cout << "   Controller::player - new, player" << i + 1 << " = " << players[i]->getType() << endl;
#endif
      }
    }
    else if (cmd == "setup") {
      td->print(cout);
#if DEBUG
      cout << "**Controller::play - setup" << endl;
#endif 
      setup(cin, *game);
#if DEBUG
      cout << "**Controller::play - Done setting up" << endl;
#endif
      td->print(cout);
      gd->notifyTurn(colours[next_player]);
      if (checkWin("white") || checkWin("black")) {
	  cout << "Enter \"game [player] [player]\" to start a new game" << endl;
      }
      else{
	cout << (char)toupper(colours[next_player][0]) << colours[next_player].substr(1) << "'s turn:" << endl;
      }
    }
    else if (cmd == "resign") {
      cout << colours[next_player] << " resigns, " << colours[(next_player + 1) % 2] << " wins!" << endl;
      gd->notifyStatus("resign",colours[(next_player + 1)%2]);
      gd->notifyTurn("");
      if (colours[next_player] == "white"){
	addScores(0,1);
      }
      else {
	addScores(1,0);
      }
      cout << "Enter \"game\" to start a new game" << endl;
    }
    else if (cmd == "move") {
      string current_colour = players[next_player]->getColour();
      bool success = players[next_player]->move(cin);
      if (!success) {
	cout << "Error: move unsucessful, try again" << endl;
	td->print(cout);
	string next_colour = players[next_player]->getColour();
	cout << (char)toupper(next_colour[0]) << next_colour.substr(1) << "'s turn:" << endl;
	gd->notifyTurn(colours[next_player]);
      } else {
	//Winning situation
	if (checkWin(current_colour)){
	  cout << "Enter \"game\" to start a new game" << endl;
	}
	else {
	  next_player = (next_player + 1) % 2;
	  td->print(cout);
	  string next_colour = players[next_player]->getColour();
	  cout << (char)toupper(next_colour[0]) << next_colour.substr(1) << "'s turn:" << endl;
	  gd->notifyTurn(colours[next_player]);
	}
      }
    }
    else {
      cout << "Error: invalid command input" << endl;
    }
  }
  if (td != NULL && gd != NULL){
    td->printFinalScores(scores[0],scores[1], cout);
    gd->printFinalScores(scores[0],scores[1], cout);
  }
}

void Controller::addScores(float sc_white, float sc_black){
  scores[0] += sc_white;
  scores[1] += sc_black;
}

/* Controller Destructor
   - delete the Game
   - delete the Players
   - delete the View (i.e. textDisplay and graphicDisplay)
*/
Controller::~Controller() {
  delete game;
  for (int i = 0; i < 2; i++) {
    delete players[i];
  }
  delete td;
  delete gd;
}
