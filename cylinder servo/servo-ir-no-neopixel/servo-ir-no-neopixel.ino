//YAY THIS WORKS

#include <Servo.h>
#include <IRremote.h>


Servo myservo;

const int RECV_PIN = 10; //IR pin
IRrecv irrecv(RECV_PIN);  //IR reciever
decode_results results; //results from IR

int pos=1;
 
void setup() {
  irrecv.enableIRIn();
}

void loop()
{
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
      break;
      }
    delay(500);
    }
}
