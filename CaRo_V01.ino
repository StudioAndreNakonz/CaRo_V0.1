
/*************************************************************
* Project: CaRo V0.1
* CARO is a rope robot that enables easy and cost-effective entry into programming and robotics.
* Author: Andre Nakonz
* Date: 2019/02/15
*
* For this example you need to install some libraries:
* 
* Adafruit nRF51 BLE Library
* Adafruit seesaw Library
* Blynk Library
*
* CREDITS
* Code snippets are from Adafruit. 
*
**************************************************************/
#include <Wire.h>

// BLYNK /////////////////////////////////////////
#define BLYNK_USE_DIRECT_CONNECT
#define BLYNK_PRINT Serial
#include <BlynkSimpleSerialBLE.h>
// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "YourToken";


// Bluetooth LE /////////////////////////////////////////
#include <Adafruit_BLE.h>
#include <Adafruit_BluefruitLE_SPI.h>
#include <SPI.h>
// SHARED SPI SETTINGS (see adafruit webpages for details)
#define BLUEFRUIT_SPI_CS               8
#define BLUEFRUIT_SPI_IRQ              7
#define BLUEFRUIT_SPI_RST              -1    // Optional but recommended, set to -1 if unused
#define BLUEFRUIT_VERBOSE_MODE         true
// Create ble instance, see pinouts above
Adafruit_BluefruitLE_SPI ble(BLUEFRUIT_SPI_CS, BLUEFRUIT_SPI_IRQ, BLUEFRUIT_SPI_RST);


// Crickit and Servos /////////////////////////////////////////
#include "Adafruit_Crickit.h"
#include "seesaw_servo.h"
Adafruit_Crickit crickit;
#define NUM_SERVOS 3
//create an array of 4 servos with our crickit object
seesaw_Servo servos[] = { seesaw_Servo(&crickit),
                          seesaw_Servo(&crickit), 
                          seesaw_Servo(&crickit) };
//these are the pins they will be attached to
int servoPins[] = { CRICKIT_SERVO1, CRICKIT_SERVO2, CRICKIT_SERVO3 };




void setup() {
  Serial.begin(115200);

  //bluetooth settings
  ble.begin(BLUEFRUIT_VERBOSE_MODE);
  ble.factoryReset(); // Optional
  ble.setMode(BLUEFRUIT_MODE_DATA);

  //Blynk
  Blynk.begin(auth, ble);

  //begin the crickit
  if(!crickit.begin()){
    Serial.println("ERROR!");
    while(1);
   }
  else Serial.println("Crickit started");

  //attach the servos to their pins
  for(int i=0; i<NUM_SERVOS; i++)
    servos[i].attach(servoPins[i]);  // attaches the servo to the pin
}

void loop(){ 
Blynk.run(); 
} 


/* How does the joystick work?
 * A continuously rotating servo hold its position at signal value 90. 
 * At a signal of 85, the servo slowly rotates to the left, 
 * at 0 it rotates to the left at full speed. 
 * At signal 180 it rotates with full speed to the right.
 * 
 * The values of the joystick could be used directly as the speed for the servos.
 * Example:
 * BLYNK_WRITE(V1){                  //Joystick #2
      int x = param[0].asInt(); 
      int y = param[1].asInt();  
      if(y<90){                       //up
      servos[0].write(y);
      servos[1].write(y);
      servos[2].write(y);
 * 
 * For higher precision, it is better if the motors rotating slower.
 * So that the motors do not move unintentionally, the y / x value is very small. 
 * Only when the joystick clearly points in one direction, the motors react.
 */
 
BLYNK_WRITE(V0){                  //Joystick #1
int x = param[0].asInt(); 
int y = param[1].asInt();  
  if(y<20){                       //forward
      servos[0].write(95);
      servos[1].write(80);
      servos[2].write(95);
} else if(y>160){                 //backward
      servos[0].write(85);
      servos[1].write(100);
      servos[2].write(85);
}  else if(x<20){                 //right 
      servos[0].write(95);
      servos[1].write(90);
      servos[2].write(85);
}else if(x>160){                  //left
      servos[0].write(85);
      servos[1].write(90);
      servos[2].write(95);
} else {                          //hold position
      servos[0].write(90);
      servos[1].write(90);
      servos[2].write(90);
 } 
} 

BLYNK_WRITE(V1){                  //Joystick #2
int x = param[0].asInt(); 
int y = param[1].asInt();  
  if(y<20){                       //up
      servos[0].write(85);
      servos[1].write(85);
      servos[2].write(85);
}else if(y>160){                  //down
      servos[0].write(95);
      servos[1].write(95);
      servos[2].write(95);
} else {                          //hold position
      servos[0].write(90);
      servos[1].write(90);
      servos[2].write(90);
 } 
} 

