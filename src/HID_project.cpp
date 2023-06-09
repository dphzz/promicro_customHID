#include <Arduino.h>
#include <HID-Project.h>
#include <Wire.h>


void setup() {
  // Initialize USB HID
  HID().begin();
}

void loop() {
  // Create a 2-byte report buffer
  uint8_t reportBuf[2] = {0, 0};

  // Set the values of the two bytes
  reportBuf[0] = 0x12;
  reportBuf[1] = 0x34;

  // Send the report over USB HID
  HID().SendReport(1, reportBuf, 2);

  // Wait a short time before sending the next report
  delay(100);
}