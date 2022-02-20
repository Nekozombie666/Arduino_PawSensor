#include "sensor.h"

/*
****PINOUT****
 PAW    Arduino
  1 ----- GND
  2 ----- A0
  3 ----- A1
  4 ----- D2
  5 ----- D3
  6 ----- 3.3V
*/

PawSensor sensor;

void setup() {
  Serial.begin(115200);// シリアル通信の開始
  sensor.InitPawSensor();
}


void loop() {
  
}
