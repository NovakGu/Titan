#include "controller.h"
#include <iostream>
#include <string>
using namespace std;

int main (int argc, char* argv[]) {
  string savedfile;
  if (argc > 1){
    savedfile = argv[1];
  }
  #if DEBUG
  cout << "Saved file? " << savedfile << endl;
  #endif
  Controller c(savedfile);  //construct Controller, given savedfile or no
  c.play();
}
