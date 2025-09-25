#include "LedControl.h"
#include "binary.h"

/*
 DIN connects to pin 12
 CLK connects to pin 11
 CS connects to pin 10 
*/
LedControl lc=LedControl(12,11,10,1);

int frameCnt=0;
bool death=false;

byte grid[8]= {
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
  B00000000,
};

byte sadgrid[8]= {
  B00000000,
  B00000000,
  B01000100,
  B00000000,
  B00111000,
  B01000100,
  B00000000,
  B00000000,
};

struct paddle{
  int x;
  int y;
  paddle(int xPos, int yPos){
    x=xPos;
    y=yPos;
  };
  paddle(){
    x=0;
    y=0;
  }
  void set(int a,int b){
    x=a;
    y=b;
  }
  void move(int k){
    set(x+k,y);
  }
};

struct ball{
  int x;
  int y;
  int xvel=1;
  int yvel=1;
  ball(int xPos, int yPos){
    x=xPos;
    y=yPos;
  };
  ball(){
    x=4;
    y=4;
  }
  void set(int a,int b){
    x=a;
    y=b;
  }
  void move(){
    if(x<=0 || x>=7) xvel*=-1;
    if(y>=7) yvel*=-1;
    if(y==1 && ((grid[7]>>(7-x)) & 1)){
      yvel*=-1;
    }
    if(y<=0){
      bool death=true;
    }
    set(x+xvel,y+yvel);
  }
};





//Grid Controls

void toggleDot(int x, int y){
  grid[7-y]^=(1<<(7-x));
}

void drawDot(int x, int y){
  grid[7-y]|=(1<<(7-x));
}

void eraseDot(int x, int y){
  grid[7-y]&=~(1<<(7-x));
}




int lButton=2;
int rButton=4;



paddle Paddle;
ball Ball(7,7);

void setup() {
  //button setup
  pinMode(lButton, INPUT);
  pinMode(rButton, INPUT);



  lc.shutdown(0,false);
  lc.setIntensity(0,3);
  lc.clearDisplay(0);
}

void setGrid(){
  for(int i=0;i<=7;i++){
    grid[i]=B00000000;
  }
  for(int i=0;i<=2;i++){
    drawDot(Paddle.x+i,Paddle.y);
  }
  drawDot(Ball.x,Ball.y);
}

void drawGrid(){
  for(int i=0;i<=7;i++){
    lc.setRow(0,i,grid[i]);
  }
}




int lState;
int rState;
int lState_prev=0;
int rState_prev=0;
void loop(){
  if(death){
    for(int i=0;i<=7;i++){
      lc.setRow(0,i,sadgrid[i]);
    }
  }
  else{
    if(Ball.y<0) death=true;
    frameCnt+=1;
    if(frameCnt%100==0) Ball.move();
    setGrid();
    drawGrid();
    lState = digitalRead(lButton);
    rState = digitalRead(rButton);
    
    if (lState == HIGH && lState_prev==LOW) {
      Paddle.move(-1);
    }
    if (rState == HIGH && rState_prev == LOW) {
      Paddle.move(1);
    }
    lState_prev = digitalRead(lButton);
    rState_prev = digitalRead(rButton);
  }
}
