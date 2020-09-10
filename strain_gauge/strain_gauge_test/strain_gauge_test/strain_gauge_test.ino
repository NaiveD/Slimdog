#include "HX711.h"

// HX711 circuit wiring
const int LOADCELL1_DOUT_PIN = 2;
const int LOADCELL1_SCK_PIN = 3;
const int LOADCELL2_DOUT_PIN = 5;
const int LOADCELL2_SCK_PIN = 6;
HX711 scale;
HX711 scale2;

void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL1_DOUT_PIN, LOADCELL1_SCK_PIN);
  scale2.begin(LOADCELL2_DOUT_PIN, LOADCELL2_SCK_PIN);
}

void loop() {

  if (scale.is_ready()) {
    long reading = scale.read();
    Serial.print("Cell_1 reading: ");
    Serial.println(reading);
  } else {
    Serial.println("Cell_1 not found.");
  }
  if (scale2.is_ready()) {
    long reading2 = scale2.read();
    Serial.print("Cell_2 reading: ");
    Serial.println(reading2);
  } else {
    Serial.println("Cell_2 not found.");
  }

  delay(1000);
  
}
