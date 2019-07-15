/*
  Last edited: Jul 14 2019
  by Ruben Verhagen
*/

#include <SoftwareSerial.h>
#include <Servo.h> 
#include <Adafruit_NeoPixel.h>

//PIN DEFINITIONS
#define ledPin    6
#define relayPin   10
#define servoPin  9

#define ledCount 12
Adafruit_NeoPixel strip(ledCount, ledPin);

SoftwareSerial Bluetooth(3,4);  //defines arduino RX,TX  

Servo servo1; //servo object
int data=0;
int i=0;
int pos=1;
int power=1;

void setup() {
  servo1.attach(servoPin); //servo pin
  Bluetooth.begin(9600);

  pinMode(relayPin, OUTPUT); //relay
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
  strip.setBrightness(4); // Set BRIGHTNESS (max = 255)
}//setup

/* BLUETOOTH APP DATA
 *  when a button is pressed on the app, it will send a certain data value
 *  Function-------------Value
 *  Camera Covered-------0
 *  Camera Open----------1
 *  Intermittent Camera--2
 *  Relay Off------------3
 *  Relay On-------------4
 */

void loop() {
  if (Bluetooth.available()){//checks if the app is sending new data
    data=Bluetooth.read();
    switch(data){    
      case 0:
        pos=0;
        break;
      case 1:
        pos =1;
        break;
      case 2:
        pos=2;
        break;
      case 3:
        power= 0;
        digitalWrite(relayPin, LOW);
        colorWipe(0,0);
        break;
      case 4:
        power= 1;
        digitalWrite(relayPin, HIGH);
        break;
    }//switch data
  }  //if Bluetooth.available

  //SERVO AND COLOR
  switch(pos){
    case 0:
      if(servo1.read()!=90)
        servo1.write(90);
      if(power==1)
        colorWipe(strip.Color(255,   0,   0), 50); // Red
      break;
    case 1:
      if(servo1.read()!=0)
        servo1.write(0);
      if(power==1){
        colorWipe(strip.Color(0,   255,   0), 50); // Green
        colorWipe(0, 50); // Blank
      }//if
      break;
    case 2:
      if(servo1.read()!=90)
        servo1.write(90);
      delay(5);
      i+=5;
      if(i>=3000&&power==1){
        servo1.write(0);
        colorWipe(strip.Color(255,   255,   0), 0); // Yellow
        colorWipe(0, 80); // Blank
        i=0;
      }//if
      break;
      
  }//switch(pos)
}//loop

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }//for
}//colorWipe
