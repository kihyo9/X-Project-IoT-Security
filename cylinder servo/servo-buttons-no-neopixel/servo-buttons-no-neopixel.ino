#include <Servo.h>
Servo myservo;

const int button1pin = 2; //number of button pins
const int button2pin = 3;
const int button3pin = 4;

int buttonState1 = 0;
int buttonState2 = 0;
int buttonState3 = 0;

int pos=1;

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
    }
}
