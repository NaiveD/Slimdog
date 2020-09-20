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
  scale.set_scale();
  scale2.set_scale();
  Serial.println("- - - - - Start tare - - - - -");
  scale.tare();
  scale2.tare();
  Serial.println("- - - - - End tare - - - - -");
  delay(1000);
  Serial.println("- - - - - Please hang item - - - - -");
  delay(15000);
  Serial.println("- - - - - Clear - - - - -");
  double reading1 = scale.get_units(10);
  double reading2 = scale2.get_units(10);
  double item_weight = 1.405;
  Serial.println("cell parameters: ");
  Serial.println(reading1 / item_weight);
  Serial.println(reading2 / item_weight);
  delay(1000);
  exit(-1);
}
