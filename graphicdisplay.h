#ifndef __GRAPHICDISPLAY_H__
#define __GRAPHICDISPLAY_H__
#include <iostream>
#include <sstream>
#include <string>
#include <stdlib.h>
#include "view.h"
#include "window.h"

class GraphicDisplay : public View {
  Xwindow *window;
  int w,h;
  int t;
  void redrawTop();
  
 public:
  GraphicDisplay();

  ~GraphicDisplay(); //dtor
  
  /*
   * The Controller calls notify to 
   * update the (r,c) location to be ch
   */
  virtual void notify(std::string, std::string);
  virtual void notifyTurn(std::string);
  virtual void notifyStatus(std::string, std::string);
  virtual void print(std::ostream &out);
  virtual void printFinalScores(float, float, std::ostream&);
};

#endif
