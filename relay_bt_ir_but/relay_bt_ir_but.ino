/*
  Last edited: Jul 19 2019
  by Ruben Verhagen
*/

#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>
#include <IRremote.h>

//PIN DEFINITIONS
#define ledPin    6
#define relayPin   4  
#define irPin 10 //power, gnd, pin
#define switchPin 7 //
#define micPin 12 //digital


#define ledCount 16
Adafruit_NeoPixel strip(ledCount, ledPin);

IRrecv irrecv(irPin);  //IR reciever
decode_results results; //results from IR

SoftwareSerial Bluetooth(2,3);  //defines arduino RX,TX  

int data=0;
int brite=255;
int pulse=25;
int change=1;
bool micState = true;
bool relayState = true;

void setup() {
  Bluetooth.begin(9600);

  pinMode(relayPin, OUTPUT); //relay
  digitalWrite(relayPin, HIGH);
  
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
  strip.setBrightness(255); // Set BRIGHTNESS (max = 255)

  irrecv.enableIRIn();

  pinMode(relayPin, INPUT);
  pinMode(micPin, INPUT);
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

  //MIC CONTROLS
  if(digitalRead(micPin) == HIGH)
  {
    if(micState == false)
    {
      for(int j=ledCount-4; j<ledCount; j++) { // For each pixel in strip...
        strip.setPixelColor(j, strip.Color(0,   0, brite));         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
      }//for
    }
    micState = true;
  }
  else
  {
    if(micState == true)
    {
      for(int j=ledCount-4; j<ledCount; j++) { // For each pixel in strip...
        strip.setPixelColor(j, 0);         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
      }//for
    }
    micState = false;
  }

  //BLUETOOTH DATA CONTROL
  if (Bluetooth.available()){//checks if the app is sending new data
    data=Bluetooth.read();
    switch(data){    
      case 3:
        digitalWrite(relayPin, LOW);
        colorWipe(0,0);
        break;
      case 4:
        change=1;
        digitalWrite(relayPin, HIGH);
        colorWipe(strip.Color(0,   brite,   0), pulse); // Green
        break;
    }//switch data
  }  //if Bluetooth.available

  //IR DATA CONTROL
  if (irrecv.decode(&results))
  {
    irrecv.resume();
    switch(results.value)
    {
      case 16736925: //if ON/OFF is pushed
        if(relayState==false){
          digitalWrite(relayPin, HIGH);
          colorWipe(strip.Color(0,   brite,   0), pulse); // Green
          relayState=true;
        }//if
        else if(relayState==true){
          digitalWrite(relayPin, LOW);
          colorWipe(0,0);
          relayState=false;
        }//else
        break;
      
    }//switch
  } //if irrecv

  //SWITCH CONTROL
  if(digitalRead(switchPin)==HIGH){
    if(relayState==false){
      colorWipe(strip.Color(0,   brite,   0), pulse); // Green
      digitalWrite(relayPin, HIGH);
      relayState=true;
      
    }
    if(relayState==true){
      colorWipe(0, 0); // Blank
      digitalWrite(relayPin, LOW);
      relayState=false;
    }
  }
  else{
    
  }

}//loop

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int j=0; j<strip.numPixels()-4; j++) { // For each pixel in strip...
    strip.setPixelColor(j, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
   
  }//for
}//colorWipe
