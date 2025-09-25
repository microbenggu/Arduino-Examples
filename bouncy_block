#include "LedControl.h"
#include "binary.h"

/*
 DIN connects to pin 12
 CLK connects to pin 11
 CS connects to pin 10 
*/
LedControl lc=LedControl(12,11,10,1);

// delay time between faces
unsigned long delaytime=200;

struct pos{
  int x;
  int y;
  pos(int xPos, int yPos):x(xPos), y(yPos) {};
  pos(){
    x=0;
    y=0;
  }
  void set(int a,int b){
    x=a;
    y=b;
  }
};

// happy face
byte face[8]= {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
};

pos dotPos(2,5);
int xVel=1;
int yVel=1;

void drawDot(int x, int y){
  face[7-y]^=(1<<(7-x));
}

void moveDot(){
  drawDot(dotPos.x,dotPos.y);
  if(dotPos.x>=7 || dotPos.x<=0){
    xVel*=-1;
  }
  if(dotPos.y>=7 || dotPos.y<=0){
    yVel*=-1;
  }
  dotPos.x+=xVel;
  dotPos.y+=yVel;
  drawDot(dotPos.x,dotPos.y);
}
void setup() {
  lc.shutdown(0,false);
  // Set brightness to a medium value
  lc.setIntensity(0,1);
  // Clear the display
  lc.clearDisplay(0);

  drawDot(dotPos.x,dotPos.y);
}
void setMatrix(){
  for(int i=0;i<=7;i++){
    lc.setRow(0,i,face[i]);
  }
}

void dotLoop(){
  moveDot();
  setMatrix();
  delay(delaytime);
}

void loop(){
  dotLoop();
}
