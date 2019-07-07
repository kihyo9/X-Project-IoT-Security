#include <Servo.h>
#include <Adafruit_NeoPixel.h>

Servo myservo;

#define PIN 6
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

const int button1pin = 2; //number of button pins
const int button2pin = 3;
const int button3pin = 4;

int buttonState1 = 0; //initialize button states
int buttonState2 = 0;
int buttonState3 = 0;

int pos=1; //initializing position variable

void setup() {
  pinMode(button1pin, INPUT);
  pinMode(button2pin, INPUT);
  pinMode(button3pin, INPUT);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(8);
  colorWipe(strip.Color(255, 0, 0), 50);//red
}

void loop() {
  buttonState1=digitalRead(button1pin); //read button states
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
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
