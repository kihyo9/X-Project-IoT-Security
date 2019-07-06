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

void setup() {
  pinMode(button1pin, INPUT);
  pinMode(button2pin, INPUT);
  pinMode(button3pin, INPUT);

  strip.begin();
  strip.show(); // Initialize all pixels to 'off'
  strip.setBrightness(8);
}

void loop() {
  buttonState1=digitalRead(button1pin); //read button states
  buttonState2=digitalRead(button2pin);
  buttonState3=digitalRead(button3pin);
  
  if(buttonState1 == HIGH)
  {
    myservo.attach(9);
    myservo.write(0);
    delay(500);
    myservo.detach();
    colorWipe(strip.Color(255, 0, 0), 50); // Red
  }
  else if(buttonState2 == HIGH)
  {
    myservo.attach(9);
    myservo.write(380);
    delay(500);
    myservo.detach();
    colorWipe(strip.Color(0, 255, 0), 50); // Green
    }
  else if(buttonState3 == HIGH)
  {
    myservo.attach(9);
    myservo.write(380);
    delay(1000);
    myservo.detach();
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
