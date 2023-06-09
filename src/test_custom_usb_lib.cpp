#include <Arduino.h>
#include <USBController.h>
#include <Wire.h>


USBController controller;
void setup(){
  Serial.begin(9600);
}

void loop(){
  int recv = controller.read();
  if (recv != 0) {
    Serial.println(recv);
    recv = 0;
  }
  uint8_t tx_buffer[] = {0x17, 0x16};
  controller.write(tx_buffer, 2);
  delay(100);
}