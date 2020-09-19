#include "HX711.h"
// HX711 circuit wiring
const int LOADCELL1_DOUT_PIN = 2;
const int LOADCELL1_SCK_PIN = 3;
const int LOADCELL2_DOUT_PIN = 5;
const int LOADCELL2_SCK_PIN = 6;
HX711 scale;
HX711 scale2;
unsigned int starting_time = 3000;
unsigned int sample_start_time;
const int max_sample_times = 20;
long sample_count = 0;
double list1[max_sample_times], list2[max_sample_times];
void setup() {
  Serial.begin(57600);
  scale.begin(LOADCELL1_DOUT_PIN, LOADCELL1_SCK_PIN);
  scale2.begin(LOADCELL2_DOUT_PIN, LOADCELL2_SCK_PIN);
  scale.set_scale(462215.845);
  scale2.set_scale(375795.375); // same item, larger scale, smaller result
  Serial.println("- - - - - Start tare - - - - -");
  scale.tare();
  scale2.tare();
  Serial.println("- - - - - End tare (hang now) - - - - -");
  Serial.println("- - - - - Counting down on start phase - - - - -");
  delay(starting_time);
  Serial.println("- - - - - Begin sampling - - - - -");
}
void loop() {
  if(sample_count % 10 == 0){
    Serial.print(sample_count);
    Serial.println(" samples processed");
  }
  if(sample_count >= max_sample_times){
    double sum1=0, sum2=0;
    for(unsigned int i=0; i<max_sample_times; ++i){
      sum1 += list1[i];
      sum2 += list2[i];
    }
    Serial.print("Cell 1 result: \t");
    Serial.println(sum1/max_sample_times);
    Serial.print("Cell 2 result: \t");
    Serial.println(sum2/max_sample_times);
    delay(1500);
    exit(-1); 
  }
  if(!scale.is_ready() || !scale2.is_ready()){
    Serial.println("Disconnection appeared");
    if(!scale.is_ready()){
      Serial.print("Cell 1 disconnected at sample ");
      Serial.println(sample_count);
    }
    if(!scale2.is_ready()){
      Serial.print("Cell 2 disconnected at sample ");
      Serial.println(sample_count);
    }
    delay(2000);
    exit(-2);
  }
  list1[sample_count] = scale.get_units(5);
  list2[sample_count] = scale2.get_units(5);
  ++sample_count;
  delay(100);
}
