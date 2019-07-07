/* July 6th, 2019
 * This code was created by Jason Rockburn, Maya Roman, Ruben Verhagen and Ben Koo
 * 
 * Inputs:
 * 3 buttons for servo position
 * 1 digital pin for mic on/off state
 * IR sensor
 * Bluetooth data 
 * 
 * Outputs:
 * Servo movement
 * Neopixel states
 * 
 * Need to to:
 * assign specific pins to input and outputs
 * bluetooth control of the servos
 * add an input for the mic cable connection
 * configure the feedback system for the neopixels
 * make a copy of this code each for Maya's and Jason's arduinos
 */

#include <Servo.h>
#include <IRremote.h>
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

//for servo
Servo myservo;
int pos=1;

//for IR sensor
const int RECV_PIN = 10; //IR pin
IRrecv irrecv(RECV_PIN);  //IR receiver
decode_results results; //results from IR

//for bluetooth reading
SoftwareSerial Bluetooth(10, 9); // RX, TX
int LED = 13; // the on-board LED
int Data; // the data received

//for buttons
const int button1pin = 2; //number of button pins
const int button2pin = 3;
const int button3pin = 4;
int buttonState1 = 0; //initialize button states
int buttonState2 = 0;
int buttonState3 = 0;

//for neopixel ring
#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

void setup()
{
  //bluetooth setup
  Bluetooth.begin(9600);
  Serial.begin(9600);
  Serial.println("Waiting for command...");
  Bluetooth.println("Send 1 to turn on the LED. Send 0 to turn Off");
  pinMode(LED,OUTPUT);
  digitalWrite(LED,LOW);
  
  //IR setup
  irrecv.enableIRIn();
  strip.begin();
  strip.show();
  strip.setBrightness(8);
  
  //button setup
  pinMode(button1pin, INPUT);
  pinMode(button2pin, INPUT);
  pinMode(button3pin, INPUT);
    
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(8);

  //show that the device is starting
  colorWipe(strip.Color(255, 0, 0), 50);//red
  delay(1000);
}

void loop()
{
  /**********************IR reading*************************/
  if (irrecv.decode(&results))
  {
    irrecv.resume();
    switch(results.value)
    {
      case 16720605: //if A is pushed
        if (pos==1){
        }
        else if(pos==2)
        {
            myservo.attach(9);
            myservo.write(180);
            delay(200);
            myservo.detach();
        }
        else if(pos==3)
        {
            myservo.attach(9);
            myservo.write(180);
            delay(700);
            myservo.detach();
        }
        pos=1;
        colorWipe(strip.Color(255, 0, 0), 50); //Red
      break;

      case 16712445: //if B is pushed
        if(pos==1)
        {
            myservo.attach(9);
            myservo.write(0);
            delay(200);
            myservo.detach();
        }
        else if(pos==2){
        }
        else if(pos==3)
        {
            myservo.attach(9);
            myservo.write(180);
            delay(200);
            myservo.detach(); 
        }
        pos=2;
        colorWipe(strip.Color(0, 255, 0), 50); //Green
      break;

      case 16761405: //if C is pushed
        if(pos==1)
        {
            myservo.attach(9);
            myservo.write(0);
            delay(700);
            myservo.detach();
        }
        else if(pos==2)
        {
            myservo.attach(9);
            myservo.write(0);
            delay(200);
            myservo.detach();
        }
        else if(pos==3){
        }
        pos=3;
        colorWipe(strip.Color(0, 0, 255), 50); //Blue
      break;
    }
  }

  /**********************Bluetooth reading*************************/
  if (Bluetooth.available()){ //wait for data received
    Data=Bluetooth.read();
    if(Data=='1'){  
      digitalWrite(LED,HIGH);
      Serial.println("LED On!");
      Bluetooth.println("LED On!");
    }
    else if(Data=='0'){
       digitalWrite(LED,LOW);
       Serial.println("LED Off!");
       Bluetooth.println("LED  On D13 Off ! ");
    }
    else{;}
  }


  /**********************Button reading*************************/

  //read button states
  buttonState1=digitalRead(button1pin);
  buttonState2=digitalRead(button2pin);
  buttonState3=digitalRead(button3pin);
  
  if(buttonState1 == HIGH)
  {
    if (pos==1){
    }
    else if(pos==2)
    {
      myservo.attach(9);
      myservo.write(180);
      delay(200);
      myservo.detach();
    }
    else if(pos==3)
    {
      myservo.attach(9);
      myservo.write(180);
      delay(700);
      myservo.detach();
    }
    pos=1;
    colorWipe(strip.Color(255, 0, 0), 50); // Red
  }
  else if(buttonState2 == HIGH)
  {
    if(pos==1){
      myservo.attach(9);
      myservo.write(0);
      delay(200);
      myservo.detach();
    }else if(pos==2){
    }
    else if(pos==3){
      myservo.attach(9);
      myservo.write(180);
      delay(200);
      myservo.detach(); 
    }
    pos=2;
    colorWipe(strip.Color(0, 255, 0), 50); // Green
    }
  else if(buttonState3 == HIGH)
  {
    if(pos==1){
      myservo.attach(9);
      myservo.write(0);
      delay(700);
      myservo.detach();
    }else if(pos==2){
      myservo.attach(9);
      myservo.write(0);
      delay(200);
      myservo.detach();
    }else if(pos==3){
    }
    pos=3;
    colorWipe(strip.Color(0, 0, 255), 50); // Blue
  }  


  //time (ms) between readings
  delay(100);  

}

void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
