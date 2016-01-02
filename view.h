#ifndef __DISPLAY_H__
#define __DISPLAY_H__
#include <iostream>
#include <sstream>
#include <string>

class View {

  protected:
    const int boardSize;
	const std::string columns;
  public:
    View();
    
 /*
  * The Controller calls notify to 
  * update the (r,c) location to be ch
  */
 virtual void notify(std::string, std::string) = 0;

 virtual void print(std::ostream &out) = 0;
 
 virtual void notifyTurn(std::string) = 0;
 
 virtual void notifyStatus(std::string, std::string) = 0;

 virtual void printFinalScores(float, float, std::ostream &) = 0;

 virtual ~View() = 0;
	
};

#endif
