#ifndef __CELL_H__
#define __CELL_H__
#include <iostream>
#include <string>

class Game;
class ChessPiece;

class Cell {
	std::string colour;  //colour of the cell
	std::string r, c;  //co-ordinates of the cell (e.g. e3 would have r=3, c=e)
	Game * game;  //pointer to game
	ChessPiece * piece;  //pointer to the ChessPiece

public:
	Cell();  // Default constructor

	ChessPiece* getPiece(); //getter for current occupant chesspiece's type
	void setColour(std::string);  //setter for private cell colour
	void setPiece(ChessPiece *);  //setter for private state
	void setCoords(std::string, std::string);  //setter for private co-ordinates of cell
	void setGame(Game *);  //setter for game
	std::string getCoord();
	//void move(std::string, Cell*);
};
#endif
