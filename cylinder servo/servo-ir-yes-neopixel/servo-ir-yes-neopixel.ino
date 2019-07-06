//YAY THIS WORKS

#include <Servo.h>
#include <IRremote.h>
#include <Adafruit_NeoPixel.h>


Servo myservo;

const int RECV_PIN = 10; //IR pin
IRrecv irrecv(RECV_PIN);  //IR reciever
decode_results results; //results from IR
 
#define PIN 6 //Neopixel pin
Adafruit_NeoPixel strip = Adafruit_NeoPixel(12, PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  irrecv.enableIRIn();
  strip.begin();
  strip.show();
  strip.setBrightness(8);
}

void loop()
{
  if (irrecv.decode(&results))
  {
    switch(results.value)
    {
      case 16720605: //if A is pushed
        myservo.attach(9);
        myservo.write(0);
        delay(500);
        myservo.detach();
        
        colorWipe(strip.Color(255, 0, 0), 50); //Red
      break;

      case 16712445: //if B is pushed
        myservo.attach(9);
        myservo.write(380);
        delay(500);
        myservo.detach();
        
        colorWipe(strip.Color(0, 255, 0), 50); //Green
      break;

      case 16761405: //if C is pushed
        myservo.attach(9);
        myservo.write(380);
        delay(1000);
        myservo.detach();
        
        colorWipe(strip.Color(0, 0, 255), 50); //Blue
      break;
      }
    delay(600);
    }
}

//function for the neopixel color
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
      strip.setPixelColor(i, c);
      strip.show();
      delay(wait);
  }
}
