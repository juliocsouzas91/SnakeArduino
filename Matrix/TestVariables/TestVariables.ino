int posx = 0;
void setup() {
 Serial.begin(9600);

}

void loop() {
  posx &=0x0007;
  Serial.print(posx);
  Serial.print('\n');
  posx++;
  delay(200);

}
