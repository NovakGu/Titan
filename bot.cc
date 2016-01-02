#include "bot.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"
#include "king.h"
#include "pawn.h"
#include <stdlib.h>
#include <time.h>



Bot::Bot(const int type, const string colour, Game* game) : Player(type,colour,game){
  side = colour;
}

Bot::~Bot(){};


bool Bot::move(std::istream& input){
  string moves;
  if(type == 1){
    moves = GenerateMove_Lv1();
  }
  else if (type == 2){
    moves = GenerateMove_Lv2();
  }
  else if (type == 3){
    moves = GenerateMove_Lv3();
  }
  else if (type == 4){
    moves = GenerateMove_Lv4();
  }
  string old_pos = moves.substr(0,2);
  string new_pos = moves.substr(2,2);
  string extra="";
  ChessPiece* piece = game->getChessPiece(old_pos);
  if (piece != NULL && piece->getName() == "P"){
    if (piece->getColour() == "white"){
      if(new_pos[1]=='8'){
	extra = "Q";
      }
    }
    else {
      if(new_pos[1]=='1'){
	extra = "Q";
      }
    }
  }
  bool success = game->move(colour, old_pos, new_pos, extra);
  return success;
}

string Bot::GenerateMove_Lv1(){
  ChessPiece* randomPiece[16] = { NULL };
  ChessPiece* currentPiece = NULL;
  Cell* randomCell[16] = { NULL };
  Cell* currentCell;
  int count = 0;
  int ran;
  //string randomMoves[20] = { "" };
  int count_m = 0;
  //string Move = "";
  string finalMove = "";
  bool check = true;
  string allPossibleMoves[64] = { "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8",
				  "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8",
				  "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8",
				  "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8",
				  "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8",
				  "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8",
				  "g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8",
				  "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8" };

  for (int i = 0; i < 64; i++){
    currentCell = game->getCell(allPossibleMoves[i]);
    if (currentCell->getPiece() != NULL && currentCell->getPiece()->getColour() == side){
      randomCell[count] = currentCell;
      count++;
    }
  }
  srand(time(NULL));
  while (check){
    ran = rand() % count;
    currentCell = randomCell[ran];
    for (int g = 0; g < 64; g++){
      if (currentCell->getPiece()!=NULL && currentCell->getPiece()->validMoves(colour, currentCell->getCoord(), allPossibleMoves[g])){
	check = false;
	finalMove = currentCell->getCoord() + allPossibleMoves[g];
	break;
      }
    }
  }
  return finalMove;
}



string Bot::GenerateMove_Lv2(){
  //string bestMove = "";
  //int bestPoints = 0;
  int ran = 0;
  int currentPoints = 0;
  //ChessPiece* bestPiece = NULL;
  ChessPiece* currentPiece = NULL;
  Cell* currentCell = NULL;
  //Cell* bestCell = NULL;
  ChessPiece* randompiece[5] = { NULL };
  Cell* randomcell[5] = { NULL };
  int randompoint[5] = { 0 };
  string randomMove[5] = { "" };

  string allPossibleMoves[64] = { "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8",
				  "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8",
				  "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8",
				  "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8",
				  "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8",
				  "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8",
				  "g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8",
				  "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8" };

  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      //error: type name is not allowed
      currentPiece = game->getCell(allPossibleMoves[i * 8 + j])->getPiece();
      currentCell = game->getCell(allPossibleMoves[i  * 8 + j]);
      //error: pointer to incomplete class type is not allowed
      if (currentPiece != NULL && currentPiece->getColour() == side){
	for (int k = 0; k < 64; k++){
	  if (currentPiece->validMoves(colour, currentCell->getCoord(), allPossibleMoves[k])){
	    ChessPiece* piece = game->getChessPiece(allPossibleMoves[k]);
	    if (piece != NULL && piece->getName() == "P"){
	      currentPoints = 2;
	    }
	    else if (piece != NULL && piece->getName() == "B"){
	      currentPoints = 3;
	    }
	    else if (piece != NULL && piece->getName() == "N"){
	      currentPoints = 4;
	    }
	    else if (piece != NULL && piece->getName() == "R"){
	      currentPoints = 5;
	    }
	    else if (piece != NULL && piece->getName() == "Q"){
	      currentPoints = 7;
	    }
	    else if (piece != NULL && piece->getName() == "K"){
	      currentPoints = 8;
	    }
	    else{
	      currentPoints = 1;
	    }
	    for (int b = 4; b >= 0; b--){
	      if (b == 0 && currentPoints > randompoint[0]){
		randompoint[b] = currentPoints;
		randompiece[b] = currentPiece;
		randomcell[b] = currentCell;
		randomMove[b] = allPossibleMoves[k];
	      }
	      else if (currentPoints > randompoint[b]){
		continue;
		/*bestPoints = currentPoints;
		  bestMove = allPossibleMoves[k];
		  bestPiece = currentPiece;
		  bestCell = currentCell;*/
	      }
	      else if (currentPoints == randompoint[b]&&b==4) break;

	   
	      else if (currentPoints <= randompoint[b] && b < 4){
		randompoint[b + 1] = currentPoints;
		randompiece[b + 1] = currentPiece;
		randomcell[b + 1] = currentCell;
		randomMove[b + 1] = allPossibleMoves[k];
	      }
	      else{}
	    }
	  }


	}
      }
    }
  }
  string finalMove = "";
  //error: pointer to incomplete class type is not allowed
  while(1){
    srand(time(NULL));
    ran = rand() % 2;
#if DEBUG
    //cout << "   Bot::GeneratateMove_Lv2 - randomcell[ran] = (" << ran << ") = " << (randomcell[ran]==NULL)  << endl;
#endif
    if (randomcell[ran] != NULL){
      finalMove = randomcell[ran]->getCoord() + randomMove[ran];
      break;
    }
  }
  return finalMove;
}

string Bot::GenerateMove_Lv3(){
  //string bestMove = "";
  //int bestPoints = 0;
  int ran = 0;
  int currentPoints = 0;
  //ChessPiece* bestPiece = NULL;
  ChessPiece* currentPiece = NULL;
  Cell* currentCell = NULL;
  //Cell* bestCell = NULL;
  ChessPiece* randompiece[5] = { NULL };
  Cell* randomcell[5] = { NULL };
  int randompoint[5] = { -10 };
  string randomMove[5] = { "" };
  ChessPiece* currentOpPiece = NULL;
  Cell* currentOpCell = NULL;
  string OpColour;
  string allPossibleMoves[64] = { "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8",
				  "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8",
				  "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8",
				  "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8",
				  "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8",
				  "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8",
				  "g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8",
				  "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8" };
  //same error as Lv-2
  if (colour == "white"){
    OpColour = "black";
  }
  else {
    OpColour = "white";
  }
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      currentPiece = game->getCell(allPossibleMoves[i * 8 + j])->getPiece();
      currentCell = game->getCell(allPossibleMoves[i * 8 + j]);
      if (currentPiece != NULL && currentPiece->getColour() == side){
	for (int k = 0; k < 64; k++){
	  if (currentPiece->validMoves(colour, currentCell->getCoord(), allPossibleMoves[k])){
	    ChessPiece* piece = game->getChessPiece(allPossibleMoves[k]);
	    if (piece != NULL && piece->getName() == "P"){
	      currentPoints = 2;
	    }
	    else if (piece != NULL && piece->getName() == "B"){
	      currentPoints = 3;
	    }
	    else if (piece != NULL && piece->getName() == "N"){
	      currentPoints = 4;
	    }
	    else if (piece != NULL && piece->getName() == "R"){
	      currentPoints = 5;
	    }
	    else if (piece != NULL && piece->getName() == "Q"){
	      currentPoints = 7;
	    }
	    else if (piece != NULL && piece->getName() == "K"){
	      currentPoints = 8;
	    }
	    else{
	      currentPoints = 1;
	    }

	    for (int l = 0; l < 64; l++){
	      currentOpPiece = game->getCell(allPossibleMoves[l])->getPiece();
	      currentOpCell = game->getCell(allPossibleMoves[l]);
	      if (currentOpPiece != NULL && currentOpPiece->validMoves(OpColour, currentOpCell->getCoord(), allPossibleMoves[k])){
		//add addtional field to every piece type
		//add virtual function to chesspiece
		//ass getPoints to access the point value for each piece
		currentPoints -= currentPiece->getPoint();
		break;
	      }
	    }
	    /*if (currentPoints > bestPoints){
	      bestPoints = currentPoints;
	      bestMove = allPossibleMoves[k];
	      bestPiece = currentPiece;
	      bestCell = currentCell;
	      }*/
	    for (int b = 4; b >= 0; b--){
	      if (b == 0 && currentPoints > randompoint[0]){
		randompoint[b] = currentPoints;
		randompiece[b] = currentPiece;
		randomcell[b] = currentCell;
		randomMove[b] = allPossibleMoves[k];
	      }
	      else if (currentPoints > randompoint[b]){
		continue;
		/*bestPoints = currentPoints;
		  bestMove = allPossibleMoves[k];
		  bestPiece = currentPiece;
		  bestCell = currentCell;*/
	      }
	      else if (currentPoints == randompoint[b] && b == 4) break;


	      else if (currentPoints <= randompoint[b] && b < 4){
		randompoint[b + 1] = currentPoints;
		randompiece[b + 1] = currentPiece;
		randomcell[b + 1] = currentCell;
		randomMove[b + 1] = allPossibleMoves[k];
	      }
	      else{}
	    }
	  }
	}
      }
    }
  }
  string finalMove = "";
  //error: pointer to incomplete class type is not allowed
  while (1){
    srand(time(NULL));
    ran = rand() % 5;
#if DEBUG
    //cout << "   Bot::GeneratateMove_Lv3 - randomcell[ran] = (" << ran << ") = " << (randomcell[ran]==NULL)  << endl;
#endif
    if (randomcell[ran] != NULL){
      finalMove = randomcell[ran]->getCoord() + randomMove[ran];
      break;
    }
  }
  return finalMove;
}

string Bot::GenerateMove_Lv4(){
  //string bestMove = "";
  bool captured = false;
  //int bestPoints = -10;
  int currentPoints = -10;
  //ChessPiece* bestPiece = NULL;
  ChessPiece* currentPiece = NULL;
  ChessPiece* future = NULL;
  Cell* currentCell = NULL;
  Cell* futureCell = NULL;
  //Cell* bestCell = NULL;
  string OpColour;
  ChessPiece* randompiece[5] = { NULL };
  Cell* randomcell[5] = { NULL };
  int randompoint[5] = { -10 };
  string randomMove[5] = { "" };
  ChessPiece* currentOpPiece = NULL;
  Cell* currentOpCell = NULL;
  int ran = 0;
  //ChessPiece* currentOpPiece = NULL;
  string allPossibleMoves[64] = { "a1", "a2", "a3", "a4", "a5", "a6", "a7", "a8",
				  "b1", "b2", "b3", "b4", "b5", "b6", "b7", "b8",
				  "c1", "c2", "c3", "c4", "c5", "c6", "c7", "c8",
				  "d1", "d2", "d3", "d4", "d5", "d6", "d7", "d8",
				  "e1", "e2", "e3", "e4", "e5", "e6", "e7", "e8",
				  "f1", "f2", "f3", "f4", "f5", "f6", "f7", "f8",
				  "g1", "g2", "g3", "g4", "g5", "g6", "g7", "g8",
				  "h1", "h2", "h3", "h4", "h5", "h6", "h7", "h8" };
  //same error as Lv-2
  if (colour == "white"){
    OpColour = "black";
  }
  else {
    OpColour = "white";
  }
  for (int i = 0; i < 8; i++){
    for (int j = 0; j < 8; j++){
      currentPiece = game->getCell(allPossibleMoves[i * 8 + j])->getPiece();
      currentCell = game->getCell(allPossibleMoves[i * 8 + j]);
      if (currentPiece != NULL && currentPiece->getColour() == side){
	for (int k = 0; k < 64; k++){
	  if (currentPiece->validMoves(colour, currentCell->getCoord(), allPossibleMoves[k])){
	    ChessPiece* piece = game->getChessPiece(allPossibleMoves[k]);
	    if (piece != NULL && piece->getName() == "P"){
	      currentPoints = 2;
	    }
	    else if (piece != NULL && piece->getName() == "B"){
	      currentPoints = 3;
	    }
	    else if (piece != NULL && piece->getName() == "N"){
	      currentPoints = 4;
	    }
	    else if (piece != NULL && piece->getName() == "R"){
	      currentPoints = 5;
	    }
	    else if (piece != NULL && piece->getName() == "Q"){
	      currentPoints = 7;
	    }
	    else if (piece != NULL && piece->getName() == "K"){
	      currentPoints = 8;
	    }
	    else{
	      currentPoints = 1;
	    }
	    for (int l = 0; l < 64; l++){
	      currentOpPiece = game->getCell(allPossibleMoves[l])->getPiece();
	      currentOpCell = game->getCell(allPossibleMoves[l]);
	      if (currentOpPiece != NULL && currentOpPiece->validMoves(OpColour, currentOpCell->getCoord(), allPossibleMoves[k])){
		//add addtional field to every piece type
		//add virtual function to chesspiece
		//ass getPoints to access the point value for each piece
		currentPoints -= currentPiece->getPoint();
		captured = true;
		break;
	      }

	    }



	    if (captured){
	      for (int a = 0; a < 64; a++){
		future = game->getCell(allPossibleMoves[a])->getPiece();
		futureCell = game->getCell(allPossibleMoves[a]);
		if (future != NULL && futureCell->getCoord() != currentCell->getCoord() && future->validMoves(colour, futureCell->getCoord(), allPossibleMoves[k])){
		  ChessPiece* piece = game->getChessPiece(allPossibleMoves[k]);
		  if (piece != NULL && piece->getName() == "P"){
		    currentPoints += 2;
		  }
		  else if (piece != NULL && piece->getName() == "B"){
		    currentPoints += 3;
		  }
		  else if (piece != NULL && piece->getName() == "N"){
		    currentPoints += 4;
		  }
		  else if (piece != NULL && piece->getName() == "R"){
		    currentPoints += 5;
		  }
		  else if (piece != NULL && piece->getName() == "Q"){
		    currentPoints += 7;
		  }
		  else if (piece != NULL && piece->getName() == "K"){
		    currentPoints += 8;
		  }
		  else{
		    currentPoints += 0;
		  }





		  for (int b = 4; b >= 0; b--){
		    if (b == 0 && currentPoints > randompoint[0]){
		      randompoint[b] = currentPoints;
		      randompiece[b] = currentPiece;
		      randomcell[b] = currentCell;
		      randomMove[b] = allPossibleMoves[k];
		    }
		    else if (currentPoints > randompoint[b]){
		      continue;
		      /*bestPoints = currentPoints;
			bestMove = allPossibleMoves[k];
			bestPiece = currentPiece;
			bestCell = currentCell;*/
		    }
		    else if (currentPoints == randompoint[b] && b == 4) break;


		    else if (currentPoints <= randompoint[b] && b < 4){
		      randompoint[b + 1] = currentPoints;
		      randompiece[b + 1] = currentPiece;
		      randomcell[b + 1] = currentCell;
		      randomMove[b + 1] = allPossibleMoves[k];
		    }
		    else{}
		  }
		}
	      }
	    }


	  }
	}
      }
    }
  }
  string finalMove = "";
  //error: pointer to incomplete class type is not allowed
  while (1){
    srand(time(NULL));
    ran = rand() % 5;
#if DEBUG
    //cout << "   Bot::GeneratateMove_Lv3 - randomcell[ran] = (" << ran << ") = " << (randomcell[ran]==NULL)  << endl;
#endif
    if (randomcell[ran] != NULL){
      finalMove = randomcell[ran]->getCoord() + randomMove[ran];
      break;
    }
  }
  return finalMove;
}
