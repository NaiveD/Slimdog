#include "HX711.h"
// https://www.youtube.com/watch?v=cztWFrd-gQA
HX711 scale(2,3);
long int values = 0;
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(scale.read());
  delay(100);
}
