#include "graphicdisplay.h"
using namespace std;

/* GraphicDisplay Constructor
   - creates the Xwindow with default width height
   - calculates the width and height of each rectangle
*/
GraphicDisplay::GraphicDisplay()
  : View(){
  window = new Xwindow(500,600);
  w = 50;
  h = 50;
  t = 100;
  string x[8]={"a","b","c","d","e","f","g","h"};
  string y[8]={"8","7","6","5","4","3","2","1"};
  for (int i=1; i < boardSize; i++){
    for (int j=1; j < boardSize; j++){
      if((i+j)%2==0){
	window->fillRectangle(h + i*h,t+w+j*w,w,h,Xwindow::White);
      }
      else{
	window->fillRectangle(h + i*h,t+w+j*w,w,h,Xwindow::Black);
      }
    }
  }
  
  window->drawBigString(100,50,"Turn:",Xwindow::Green);
  window->drawBigString(300,50,"Status:",Xwindow::Green);

  for(int j=0;j<boardSize;j++){
    window->drawString(25,t+j*w+75,y[j],Xwindow::Black);
    window->drawString(450+25,t+j*w+75,y[j],Xwindow::Black);
  }
  for(int i=0;i<boardSize;i++){
    window->drawString(75+i*h,600-25,x[i],Xwindow::Black);
  }

}

/* GraphicDisplay Destructor
 */
GraphicDisplay::~GraphicDisplay(){
  delete window;
}

void GraphicDisplay::redrawTop(){
  window->fillRectangle(0,0,500,150,Xwindow::White);
  window->drawBigString(100,50,"Turn:",Xwindow::Green);
  window->drawBigString(300,50,"Status:",Xwindow::Green);
}

/* GraphicDisplay::notify
   - called by the Game when a Cell has changed its colour
   - fills the corresponding rectangle with the new colour
*/
void GraphicDisplay::notify(string pos, string piece){
  //window->showAvailableFonts();
  int row,col;
  col=columns.find(pos[0]);
  row=8-(int(pos[1])-48);
  if((col+row)%2==0){
    window->fillRectangle(h+col*h, t+w+row*w, w, h, Xwindow::White);
  } else{
    window->fillRectangle(h+col*h, t+w+row*w, w, h, Xwindow::Black);
  } 
  if(piece!="."){
    if(islower(piece[0])){
      window->drawBigString(h+col*h+15,t+w+row*w+40,piece,Xwindow::Orange);
    }
    else {
      window->drawBigString(h+col*h+15,t+w+row*w+40,piece,Xwindow::Blue);
    }
  }
}

void GraphicDisplay::notifyTurn(string side){
  //redrawTop();
  window->fillRectangle(50,60,200,90,Xwindow::White);
  if (side == ""){
  }
  else if(side == "black"){
    window->drawBigString(100,100,"Black",Xwindow::Orange);
  }
  else {
    window->drawBigString(100,100,"White",Xwindow::Blue);
  }
}

void GraphicDisplay::notifyStatus(string status, string winner){
#if DEBUG
  cout << "   GraphicDisplay::notifyStatus - status = " << status << " winner = " << winner << endl;
#endif
  //redrawTop();
  window->fillRectangle(300,60,200,90,Xwindow::White);
  if(status == ""){
  }
  else if (status == "stalemate") {
    window->drawBigString2(300,80,"Stalemate!",Xwindow::Black);
    window->drawBigString2(300,125,"Draw!",Xwindow::Black);
  }
  else if (status == "check"){
    cout << "drawing" << endl;
    window->drawBigString2(300,80,"In check!",Xwindow::Black);
  }
  else if (status == "resign"){
    winner[0] = toupper(winner[0]);
    window->drawBigString2(300,80,"Resigns!",Xwindow::Black);
    window->drawBigString2(300,125,winner+" wins!",Xwindow::Black);
  }
  else {
    winner[0] = toupper(winner[0]);
    window->drawBigString2(300,80,"Checkmate!",Xwindow::Black);
    window->drawBigString2(300,125,winner+" wins!",Xwindow::Black);
  }
}
/* GraphicDisplay::print
   - do nothing
*/
void GraphicDisplay::print(ostream &out){}

void GraphicDisplay::printFinalScores(float sc_white, float sc_black, ostream &out){
   window->fillRectangle(0,0,500,600,Xwindow::Black);
   window->drawBigString(150, 200 ,"***Final Score***",Xwindow::White);
   ostringstream ossw;
   ostringstream ossb;
   ossw << sc_white;
   ossb << sc_black;
   window->drawBigString(150, 300,"    White: " + ossw.str(),Xwindow::White);
   window->drawBigString(150, 400,"    Black: " + ossb.str(),Xwindow::White);
}
