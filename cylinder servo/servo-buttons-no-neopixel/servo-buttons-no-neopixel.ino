#include <Servo.h>
Servo myservo;

const int button1pin = 2; //number of button pins
const int button2pin = 3;
const int button3pin = 4;

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

void setup() {
  pinMode(button1pin, INPUT);
  pinMode(button2pin, INPUT);
  pinMode(button3pin, INPUT);
}

void loop() {
  buttonState1=digitalRead(button1pin);
  buttonState2=digitalRead(button2pin);
  buttonState3=digitalRead(button3pin);
  
  if(buttonState1 == HIGH)
  {
    myservo.attach(9);
    myservo.write(0);
    delay(500);
    myservo.detach();
  }
  else if(buttonState2 == HIGH)
  {
    myservo.attach(9);
    myservo.write(380);
    delay(500);
    myservo.detach();
    }
  else if(buttonState3 == HIGH)
  {
    myservo.attach(9);
    myservo.write(380);
    delay(1000);
    myservo.detach();
    }
}
