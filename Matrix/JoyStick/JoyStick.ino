int Vx = A0;
int Vy = A1;
int Sw = 7;
int xPosition,yPosition,Sw_state;
void setup() {
  
  // put your setup code here, to run once:
  Serial.begin(9600); 
  pinMode(Vx,INPUT);
  pinMode(Vy,INPUT);
  pinMode(Sw,INPUT_PULLUP);
}

void loop() {
  xPosition = analogRead(Vx);
  yPosition = analogRead(Vy);
  Sw_state = digitalRead(Sw);

  if(xPosition>600){
  Serial.print("Direita");
  Serial.print("\n");    
    }
  if(xPosition<400){
  Serial.print("Esquerda");
  Serial.print("\n");       
    }    
  if(yPosition>600){
  Serial.print("Cima");
  Serial.print("\n");   
    }
  if(yPosition<400){
  Serial.print("Baixo");
  Serial.print("\n");       
    }
  delay(500);
  

}
