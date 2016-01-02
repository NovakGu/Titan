#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__
#include <iostream>
#include <sstream>
#include <string>
#include "view.h"

class TextDisplay : public View {
  std::string **theDisplay;          //the n x n display
  
 public:
  TextDisplay(); //one arg constructor where the parameter is the gridSize

  ~TextDisplay(); //dtor
  
  /*
   * The Controller calls notify to 
   * update the (c,r) location to be ch
   */
  virtual void notify(std::string, std::string);

  /*
   * Prints the board as specified in the assignment specification.
   */
  virtual void print(std::ostream &out);

  virtual void notifyTurn(std::string);
 
  virtual void notifyStatus(std::string, std::string);

  virtual void printFinalScores(float, float, std::ostream&);
};

#endif
