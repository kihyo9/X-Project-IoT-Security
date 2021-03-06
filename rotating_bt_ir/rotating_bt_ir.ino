/*
  Last edited: Jul 14 2019
  by Ruben Verhagen
*/

#include <SoftwareSerial.h>
#include <Servo.h> 
#include <Adafruit_NeoPixel.h>
#include <IRremote.h>

//PIN DEFINITIONS
#define ledPin    6
#define relayPin   11
#define servoPin  9
#define irPin 10 

#define ledCount 12
Adafruit_NeoPixel strip(ledCount, ledPin);

IRrecv irrecv(irPin);  //IR reciever
decode_results results; //results from IR

SoftwareSerial Bluetooth(3,4);  //defines arduino RX,TX  

Servo myservo; //servo object
int data=0;
int i=0;
int pos=1;
int power=1;
int brite=255;
int pulse=75;

void setup() {
  myservo.attach(servoPin); //servo pin
  Bluetooth.begin(9600);

  pinMode(relayPin, OUTPUT); //relay
  digitalWrite(relayPin, HIGH);
  
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
  strip.setBrightness(255); // Set BRIGHTNESS (max = 255)

  irrecv.enableIRIn();
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

 /* IR REMOTE DATA
 * On/Off 16736925
 * A      16720605
 * B      16712445
 * C      16761405
 * CENTER 16718055
 * UP     16750695
 * DOWN   16726215
 * LEFT   16724175
 * RIGHT  16743045
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

  if (irrecv.decode(&results))
  {
    irrecv.resume();
    switch(results.value)
    {
      case 16720605: //if A is pushed OPEN
        pos=1;
        break;
      case 16712445: //if B is pushed OBSCURED
        pos=2;
        break;
      case 16761405: //if C is pushed CLOSED
        pos=0;
        break;
      case 16736925: //if ON/OFF is pushed
        if(power==0){
          power=1;
          digitalWrite(relayPin, HIGH);
        }//if
        else if(power==1){
          power= 0;
          digitalWrite(relayPin, LOW);
          colorWipe(0,0);
        }//else
        break;
      
    }//switch
  } //if irrecv

  //SERVO AND COLOR
  switch(pos){
    case 0:
      if(myservo.read()!=90)
        myservo.write(90);
      if(power==1)
        colorWipe(strip.Color(brite,   0,   0), pulse); // Red
      break;
    case 1:
      if(myservo.read()!=0)
        myservo.write(0);
      if(power==1){
        colorWipe(strip.Color(0,   brite,   0), pulse); // Green
        colorWipe(0, pulse); // Blank
      }//if
      break;
    case 2:
      if(myservo.read()!=90)
        myservo.write(90);
      delay(5);
      i+=5;
      if(i>=3000&&power==1){
        myservo.write(0);
        colorWipe(strip.Color(brite,   brite,   0), 0); // Yellow
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
  for(int j=0; j<strip.numPixels(); j++) { // For each pixel in strip...
    strip.setPixelColor(j, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
   
  }//for
}//colorWipe
