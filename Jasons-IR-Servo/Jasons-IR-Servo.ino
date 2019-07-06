/*

*/

#include <IRremote.h>
#include <Servo.h> 

const int RECV_PIN = 7;   //reciever pin attached at pin 7
IRrecv irrecv(RECV_PIN);  //IR reciever
decode_results results;
int servoPin = 9;         //servo designation attached to 9 pin
Servo Servo1;              //servo object
const int BUTTON = 2;


void setup() {
  
   Servo1.attach(servoPin); //servo pin
   
  irrecv.enableIRIn();
  irrecv.blink13(true);
  pinMode (BUTTON, INPUT);
    
}

void loop() {
  
  
  
  if (irrecv.decode(&results)){
  switch(results.value){    //switch for power button to start constant rotation
          case 0xFFA25D: //Keypad button POWER
          Servo1.write(0);
          delay(1000);
          
         if(digitalRead(BUTTON) == HIGH){
          
          Servo1.write(0);
          irrecv.resume();
          }

          irrecv.resume();

         

          
          Servo1.write(90);
          delay(3000);

          if(digitalRead(BUTTON) == HIGH){
          
          Servo1.write(0);
          irrecv.resume();
          }

          

          
          Servo1.write(180);
          delay(1000);

          if(digitalRead(BUTTON) == HIGH){
          
          Servo1.write(0);
          irrecv.resume();
          }

          

         
          Servo1.write(90);
          delay(3000);


        if(digitalRead(BUTTON) == HIGH){
          
          Servo1.write(0);
          irrecv.resume();
        }
  }
         if (irrecv.decode(&results)){

         
          
          switch(results.value){    //switch to stop rotation
          case 0xFF02FD: //Keypad button PLAYPAUSE
          Servo1.write(0);
          delay(1000);
         
         
          irrecv.resume();
         
          }
          
          
          switch(results.value){
          case 0xFFE21D: //keypad button func/stop
          Servo1.write(90);
          delay(1000);
          
          
          irrecv.resume();
        }

         
   
  }
  }  
}
