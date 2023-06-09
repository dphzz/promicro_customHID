#include <Arduino.h>
#include <HID.h>
#include <Wire.h>
// #include <Keyboard.h>
// put function declarations here:

#define dir_pin PD2
#define step_pin PD4

String serial_input;

void send_serial(String data);

void setup() {
  // put your setup code here, to run once:
  //USB_Init();
  //Keyboard.begin();
  Serial.begin(9600);
  while (!Serial) {
     // wait for serial port to connect. Needed for native USB
  }

}

void loop() {
  // while(!Serial);
  

  if(Serial.available()){
    // serial_input = Serial.readString(); //The string send over from cool term also contain \n
    serial_input = Serial.readStringUntil('\n');
  }
  
  send_serial(serial_input);

  delay(1000);
 
 
 
  // put your main code here, to run repeatedly:
}


void send_serial(String data){
  if (!Serial){

  } else {
    Serial.println(data);
  } //Have to use this code right here to send serial data
}

// void read_abs_encoder(){

// }

// void stepper_control(bool step_dir, int no_step){
//   if (step_dir){

//   } else {

//   }


// }
