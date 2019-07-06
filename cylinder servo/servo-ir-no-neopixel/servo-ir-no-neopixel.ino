//YAY THIS WORKS

#include <Servo.h>
#include <IRremote.h>


Servo myservo;

const int RECV_PIN = 10; //IR pin
IRrecv irrecv(RECV_PIN);  //IR reciever
decode_results results; //results from IR
 
void setup() {
  irrecv.enableIRIn();
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
      break;

      case 16712445: //if B is pushed
        myservo.attach(9);
        myservo.write(380);
        delay(500);
        myservo.detach();
      break;

      case 16761405: //if C is pushed
        myservo.attach(9);
        myservo.write(380);
        delay(1000);
        myservo.detach();
      break;
      }
    delay(600);
    }
}
