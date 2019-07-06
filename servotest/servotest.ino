#include <Servo.h>
Servo myservo;

const int button1pin = 4; //number of button pins
const int button2pin = 2;
const int button3pin = 3;

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

void setup() {
  myservo.attach(9);
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
    myservo.write(0);
  }
  else if(buttonState2 == HIGH)
  {
    myservo.write(90);
  }
  else if(buttonState3 == HIGH)
  {
    myservo.write(45);
  }
}
