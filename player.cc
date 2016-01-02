#include "player.h"
#include <iostream>
#include <string>

using namespace std;

/*Constructor
*/
Player::Player(const int type, const string colour, Game* game){
  this->type = type;
  this->colour = colour;
  this->game = game;
}

/*Destructor
*/
Player::~Player(){}

/*getType
  - Returns the type of the player (0: human, 1-4: bot)
*/
int Player::getType(){
	return type;
}

/*getColour
 */
string Player::getColour(){
  return colour;
}
