#include <Arduino.h>
#include <Keyboard.h>
#include <Wire.h>
#include <USBAPI.h>
#include <USBCore.h>
#include <PluggableUSB.h>

// #define TEST_CUSTOM_HID_CODE
// #define USB_VID 0x2014
// #define USB_PID 0x2015
// #define USB_MANUFACTURER "Test right here"

//USB receive variable
uint8_t rx_buffer[64];
uint8_t tx_buffer[64] = {0x17, 0x16};

// set pin numbers for the five buttons:
// const int upButton = 2;
// const int downButton = 3;
// const int leftButton = 4;
// const int rightButton = 5;
// const int mouseButton = 6;



void setup() {  // initialize the buttons' inputs:
  // pinMode(upButton, INPUT);
  // pinMode(downButton, INPUT);
  // pinMode(leftButton, INPUT);
  // pinMode(rightButton, INPUT);
  // pinMode(mouseButton, INPUT);

  Serial.begin(9600);
  // initialize mouse control:
//   Mouse.begin();
  Keyboard.begin();
}

int last_increment = millis();
int last_send_time = millis();
int last_serial_time = millis();
int last_read_time = millis();
void loop() {
  if ((millis() - last_send_time) > 100){
    // byte data[2] = {0x17, 0x16};
    HID().SendReport(1, tx_buffer, 3);
    last_send_time = millis();

  }

  // if(HID().Receive_data(1, rx_buffer, 3)){
  //   if ((uint8_t)rx_buffer[1] != 0x18 && (uint8_t)rx_buffer[1] != 0x1C && (uint8_t)rx_buffer[1] != 0x0C){  //Use a control byte to reject irrelevant data such as 0x18, 0x1C, 0x0C
  //     tx_buffer[0] = (uint8_t)rx_buffer[1];
  //     tx_buffer[1] = (uint8_t)rx_buffer[2];

  //   }
  // }

  // tx_buffer[0] = (uint8_t)1;
  tx_buffer[1] = (uint8_t)10;
  tx_buffer[2] = (uint8_t)15;
  
  if (last_increment - millis() > 1000){
    last_increment = millis();
    tx_buffer[0] = tx_buffer[0] + (uint8_t)(1);
    if (tx_buffer[0] > 255){
      tx_buffer[0] = 0;
    }
  }
  delay(1000);

  // for (int i = 1; i < 64; i++){
  //   tx_buffer[i-1] = rx_buffer[i]; //Return back the received data
  // }    
  

  // if ((millis() - last_serial_time) > 1000){
  //   last_serial_time = millis();
  //   Serial.println(String(rx_buffer[0]) + " " + String(rx_buffer[1]) + " " + String(rx_buffer[2]) + " ");
  // }
  // delay(1000);


    // if (USB_Available){
    //   USB_Recv(PluggableUSB, tx_buffer, 2);
    // }
    // HID().recv();
  // use serial input to control the mouse:
//   if (Serial.available() > 0) {
//     char inChar = Serial.read();

//     switch (inChar) {
//       case 'u':
//         // move mouse up
//         Mouse.move(0, -40);
//         break;
//       case 'd':
//         // move mouse down
//         Mouse.move(0, 40);
//         break;
//       case 'l':
//         // move mouse left
//         Mouse.move(-40, 0);
//         break;
//       case 'r':
//         // move mouse right
//         Mouse.move(40, 0);
//         break;
//       case 'm':
//         // perform mouse left click
//         Mouse.click(MOUSE_LEFT);
//         break;
//     }
//   }

  // use the pushbuttons to control the keyboard:
//   if (digitalRead(upButton) == HIGH) {
//     Keyboard.write('u');
//   }
//   if (digitalRead(downButton) == HIGH) {
//     Keyboard.write('d');
//   }
//   if (digitalRead(leftButton) == HIGH) {
//     Keyboard.write('l');
//   }
//   if (digitalRead(rightButton) == HIGH) {
//     Keyboard.write('r');
//   }
//   if (digitalRead(mouseButton) == HIGH) {
//     Keyboard.write('m');
//   }
}