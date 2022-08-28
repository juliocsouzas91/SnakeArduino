#if ARDUINO < 100
#include <WProgram.h>                              // Add other libraries on demand as requested
#else
#include <Arduino.h>                               // Needed when working with libraries
#endif
#include <MaxMatrix.h>
int debug                         =  0;            // Debug counter; if set to 1, will write values via serial
const unsigned int baudRate       =  9600;         // Baud rate for the serial monitor
int data                          =  2;            // (13) DIN pin of MAX7219 module
int load                          =  3;            // (10) CS pin of MAX7219 module
int clock                         =  4;           // (9) CLK pin of MAX7219 module
int RdnInp                        =  A5;
int Vx                            =  A0;
int Vy                            = A1;
int Sw                            = 7;

int xPosition,yPosition,Sw_state;
int maxInUse =  1;
int Debug = 1;
int posx, posy;
int dir = 0; //0 dir, 1 esq, 2 cima, 3 baixo
int dotx,doty;
int SnakeSize = 2 ,SnakePointer = 0;
int *SnakePositionX, * SnakePositionY;

MaxMatrix m(data, load, clock, maxInUse); 

void setup() {
  if(Debug){
    Serial.begin(9600); 
  }
  m.init();                                        // Initialize module
  m.setIntensity(0);                               // Dot matix intensity 0-15
  
  pinMode(RdnInp,INPUT);
  pinMode(Vx,INPUT);
  pinMode(Vy,INPUT);
  pinMode(Sw,INPUT_PULLUP);
  randomSeed(analogRead(RdnInp));
  posx = random(0,8);
  randomSeed(analogRead(RdnInp));
  posy = random(0,8);
  randomSeed(analogRead(RdnInp));
  dotx = random(0,8);
  randomSeed(analogRead(RdnInp));
  doty = random(0,8);
  m.setDot(posx,posy,true);
  m.setDot(dotx,doty,true);
  SnakePositionX = (int*)malloc(64* sizeof(int));
  SnakePositionY = (int*)malloc(64* sizeof(int));
  *(SnakePositionX) = posx;
  *(SnakePositionY) = posy;
  }                                                  // End of void setup() 


void loop() {

  xPosition = analogRead(Vx);
  yPosition = analogRead(Vy);
  Sw_state = digitalRead(Sw);
  TreatInput(xPosition,yPosition,&dir);
  TrocaPos(&posx, &posy, dir);
  //UpdateSnakePosition(&posx,&posy,dir);
  //PrintSnake(SnakePositionX,SnakePositionY,posx,posy,SnakeSize,&SnakePointer);
  CheckColision(&dotx,&doty,posx,posy);
  delay(200);
}

//###Auxiliar Functions###

void CheckColision(int *dotx, int *doty, int posx, int posy){
  if(*dotx==posx&*                                                 doty==posy){
    m.setDot(*dotx,*doty,false);
    randomSeed(analogRead(RdnInp));
    *dotx = random(0,8);
    randomSeed(analogRead(RdnInp));
    *doty = random(0,8);
  }
  m.setDot(*dotx,*doty ,true);

  return;
}

void PrintSnake(int *SnakePositionX,int *SnakePositionY,int posx,int posy,int SnakeSize,int *SnakePointer){
  int aux2 = 0, AuxPoint;
  m.setDot(*(SnakePositionX + *SnakePointer),*(SnakePositionY + *SnakePointer), false);
  *(SnakePositionX + *SnakePointer) = posx;
  *(SnakePositionY + *SnakePointer) = posy;
  m.setDot(*(SnakePositionX + *SnakePointer),*(SnakePositionY + *SnakePointer), false);
  for (aux2 = 0; aux2<SnakeSize-1; aux2++){
    AuxPoint = (*SnakePointer + aux2) & SnakeSize;
    m.setDot(*(SnakePositionX + AuxPoint),*(SnakePositionY + AuxPoint), true);
  }  
  *SnakePointer ++;
  *SnakePointer &= SnakeSize;
  return ; 
}

void UpdateSnakePosition(int *posx, int *posy, int dir){
  switch(dir){
    case 0:
      *posx = *posx + 1;
      break;
    case 1:
      *posx = *posx - 1;
      break;
    case 2:
      *posy = *posy + 1;
      break;
    case 3:
      *posy = *posy - 1;
      break;
    } 
  *posy &= 0x0007;
  *posx &= 0x0007;
  }

  
void TrocaPos(int *posx, int *posy, int dir){
  m.setDot(*posx, *posy, false);
  switch(dir){
    case 0:
      *posx = *posx + 1;
      break;
    case 1:
      *posx = *posx - 1;
      break;
    case 2:
      *posy = *posy + 1;
      break;
    case 3:
      *posy = *posy - 1;
      break;
    } 
  *posy &= 0x0007;
  *posx &= 0x0007;
  m.setDot(*posx, *posy, true);
  }
  
int TreatInput(int xPosition,int yPosition, int *dir){
  if(xPosition>700){
    *dir = 0;
    return;
  }    
  if(xPosition<300){
    *dir = 1;
    return;
  }    
  if(yPosition>700){
    *dir = 2;
    return;
  }
  if(yPosition<300){
    *dir = 3;
    return;
  }
  return  dir;

}
