/* 
 * IoT Security Flipping Camera Cover Assembly
 * Developed by: Ben Koo, Jason Rockburn, Maya Roman, Ruben Verhagen
 * Last updated: Jul 26, 2019
 */

#include <SoftwareSerial.h>
#include <Servo.h> 
#include <Adafruit_NeoPixel.h>
#include <IRremote.h>

//PIN DEFINITIONS
#define ledPin    13
#define relayPin   6
#define servoPin  0
#define irPin 1
#define button1Pin 7
#define button2Pin 5
#define button3Pin 2
#define micPin 12
#define rxPin 4
#define txPin 3

#define shortDelay 200  //control servo rotation
#define longDelay 700

#define ledCount 12
Adafruit_NeoPixel strip(ledCount, ledPin);

IRrecv irrecv(irPin);  //IR reciever
decode_results results; //results from IR

SoftwareSerial Bluetooth(rxPin, txPin);  //connects to BT module TX, RX respectively

Servo myservo; //servo object

//VARIABLES
  int data = 0;     //carries number sent by BT app
  int pos = 1;    //indicates cover position, initialized to OPEN
  int prev = 1;   //used to determine which way the motor should rotate
  
  bool power = 1;   //initialized to ON
  bool change = 1;
  bool micState = 1;
  
/*****CUSTOMIZABLE VARIABLES*****/
  int brite = 255;  //LED backlight brightness, max 255
  int pulse = 25;   //controls speed of LED colorWipe animation, decrease value to increase speed
  

void setup() {
  Bluetooth.begin(9600);

  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, HIGH);
  
  strip.begin();
  strip.show();  // Initialize all pixels to 'off'
  strip.setBrightness(255); // Set BRIGHTNESS (max = 255)

  irrecv.enableIRIn();

  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  pinMode(button3Pin, INPUT);
  pinMode(micPin, INPUT);

   //initialize mic lights
  if(digitalRead(micPin) == HIGH)
  {
    for(int j=ledCount-4; j<ledCount; j++) { 
      strip.setPixelColor(j, strip.Color(0,   0, brite));  
      strip.show();   
    }//for
    micState = 1;
  }
  else
  {
    for(int j=ledCount-4; j<ledCount; j++) {
      strip.setPixelColor(j, 0); 
      strip.show();
    }//for
    micState = 0;
  }
}//setup

/* BLUETOOTH APP DATA
 *  when a button is pressed on the app, it will send a certain data value
 *  FUNCTION-------------VALUE
 *  Camera Covered-------0
 *  Camera Open----------1
 *  Intermittent Camera--2
 *  Relay Off------------3
 *  Relay On-------------4
 */

/* IR REMOTE DATA
 *  when a button is pressed on the remote, it will send a certain data value
 *  BUTTON----FUNCTION--------------VALUE
 *  On/Off----Toggle Relay On/Off---16736925
 *  A---------Camera Open-----------16720605
 *  B---------Intermittent Camera---16712445
 *  C---------Camera Covered--------16761405
 */

void loop() {

/*****BLUETOOTH APP INPUT DATA*****/
  if (Bluetooth.available()){//checks if the app is sending new data
    data=Bluetooth.read();
    switch(data){    
      case 0:
        pos = 0;
        change = 1;
        break;
      case 1:
        pos = 1;
        change = 1;
        break;
      case 2:
        pos = 2;
        change = 1;
        break;
      case 3:
        power = 0;
        digitalWrite(relayPin, LOW);
        colorWipe(0,0);
        for(int j=ledCount-4; j<ledCount; j++) { // For each pixel in strip...
            strip.setPixelColor(j, 0);         //  Set pixel's color (in RAM) to BLANK
            strip.show();                       //  Update strip to match
        }//for
          micState = 0;
        break;
      case 4:
        power = 1;
        change =1;
        digitalWrite(relayPin, HIGH);
        break;
    }//switch data
  }  //if Bluetooth.available

/*****IR REMOTE INPUT DATA*****/
  if (irrecv.decode(&results))
  {
    irrecv.resume();
    switch(results.value)
    {
      case 16720605: //if A is pushed OPEN
        pos = 1;
        change = 1;
        break;
      case 16712445: //if B is pushed OBSCURED
        pos = 2;
        change = 1;
        break;
      case 16761405: //if C is pushed CLOSED
        pos = 0;
        change = 1;
        break;
      case 16736925: //if ON/OFF is pushed
        if(power == 0)
        {
          power = 1;
          change = 1;
          digitalWrite(relayPin, HIGH);
        }//if
        else if(power == 1)
        {
          power = 0;
          digitalWrite(relayPin, LOW);
          colorWipe(0,0);
          for(int j=ledCount-4; j<ledCount; j++) { // For each pixel in strip...
            strip.setPixelColor(j, 0);         //  Set pixel's color (in RAM) to BLANK
            strip.show();                          //  Update strip to match
          }//for
          micState = 0;
        }//else
        break;
      
    }//switch
  } //if irrecv

/*****BUTTON INPUT DATA*****/
  if(digitalRead(button1Pin) == HIGH)
  {
    pos = 1;
    change = 1;
  }
  else if(digitalRead(button2Pin) == HIGH)
  {
    pos = 2;
    change = 1;
  }
  else if(digitalRead(button3Pin) == HIGH)
  {
    pos = 0;
    change = 1;
  }

/*****SERVO AND COLOR OUTPUT*****/
  switch(pos){
    case 0: //OFF
      if(change == 1)
      {
        if(prev == 1)
        {
            myservo.attach(servoPin);
            myservo.write(180);
            delay(shortDelay);
            myservo.detach();
        }
        else if(prev == 2)
        {
            myservo.attach(servoPin);
            myservo.write(180);
            delay(longDelay);
            myservo.detach();
        }
      }//if change
      
      if(power == 1)
      {
          colorWipe(strip.Color(brite,   0,   0), pulse); // Red
      }
      change = 0;
      prev = 0;
      break;
      
    case 1: //ON
      if(change == 1){
        if(prev == 0)
          {
              myservo.attach(servoPin);
              myservo.write(0);
              delay(shortDelay);
              myservo.detach();
          }
        else if(prev == 2)
        {
            myservo.attach(servoPin);
            myservo.write(180);
            delay(shortDelay);
            myservo.detach(); 
        }
      }//if change
      
      if(power == 1)
      {
          colorWipe(strip.Color(0,   brite,   0), pulse); // Green
      }
      change = 0;
      prev = 1;
      break;
      
    case 2: //OBSCURED
      if(change == 1){
       if(prev == 0)
        {
            myservo.attach(servoPin);
            myservo.write(0);
            delay(longDelay);
            myservo.detach();
        }
        else if(prev == 1)
        {
            myservo.attach(servoPin);
            myservo.write(0);
            delay(shortDelay);
            myservo.detach();
        }
      }//if change
      
      if(power == 1){
        colorWipe(strip.Color(brite,   brite,   0), pulse); // Yellow
      }//if
      change = 0;
      prev = 2;
      break;
      
  }//switch(pos)

/*****MIC CONNECTION LED OUTPUT*****/
  if(digitalRead(micPin) == HIGH && power == 1)
  {
    if(micState == 0)
    {
      for(int j=ledCount-4; j<ledCount; j++) { // For each pixel in strip...
        strip.setPixelColor(j, strip.Color(0,   0, brite));         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
      }//for
    }
    micState = 1;
  }
  else
  {
    if(micState == 1)
    {
      for(int j=ledCount-4; j<ledCount; j++) { // For each pixel in strip...
        strip.setPixelColor(j, 0);         //  Set pixel's color (in RAM)
        strip.show();                          //  Update strip to match
      }//for
    }
    micState = 0;
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
