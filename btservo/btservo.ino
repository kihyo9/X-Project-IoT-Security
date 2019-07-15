/*

*/

#include <SoftwareSerial.h>
#include <Servo.h> 
#include <Adafruit_NeoPixel.h>

#define LED_PIN    6
#define LED_COUNT 12
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN);  

#define RELAY_PIN   10


SoftwareSerial Bluetooth(3,4);
int servoPin = 9;         //servo designation attached to 9 pin
Servo Servo1;              //servo object
int Data=1;
int pos=1;
int power=1;
//const int BUTTON = 2;


void setup() {
  
  Servo1.attach(servoPin); //servo pin
  Bluetooth.begin(9600);
  //pinMode (BUTTON, INPUT); //button 

    pinMode(RELAY_PIN, OUTPUT); //relay
  strip.begin();
     strip.show();  // Initialize all pixels to 'off'
     strip.setBrightness(255); // Set BRIGHTNESS to about 4/5 (max = 255)
}

void loop() {
  
  
  
  if (Bluetooth.available()){
    Data=Bluetooth.read();
  switch(Data){    

   
          /*case 0xFF02FD: //Keypad button PLAYPAUSE*/
          case 0:
          Servo1.write(90);
          delay(200);
         
         
          Bluetooth.println("View is covered");
          pos=0;
          break;
          
          
         
          
    
    //switch for power button to start constant rotation
          /*case 0xFFA25D: //Keypad button POWER*/
          case 1:

          Servo1.write(0);
          Bluetooth.println("View is clear");
          pos=1;
         break;
          
         

        
          /*case 0xFFE21D: //keypad button func/stop*/
          case 2:
          pos=2; 
          Data=2;
          Servo1.write(0);
          delay(1000);
          
          if(Data==2){//Obscured
    colorWipe(strip.Color(255,   255,   0), 50); // Yellow
     colorWipe(0, 50); // Blank
   }
          
         if(Data == 1){
          
          Servo1.write(0);
         
          break;
          
          }

         

         

          
          Servo1.write(90);
          delay(3000);

          if(Data == 1){
          
          Servo1.write(0);
          break;
          
          }

          

          
          Servo1.write(0);
          delay(1000);

          if(Data == 1){
          
          Servo1.write(0);
          break;
         
          }

          

         
          Servo1.write(90);
          delay(3000);


        if(Data == 1){
          
          Servo1.write(0);
          break;
         
        }
        
         

         
          
          
          
  
        

         
   
  }//switch Data
  //RELAY
   if(Data==4)//RELAY ON
   {
    digitalWrite(RELAY_PIN, HIGH);
    
      Data=pos;
    power=1;
   }
   else if(Data==3) //RELAY OFF
   {
    digitalWrite(RELAY_PIN, LOW);
    colorWipe(0, 0); // Blank
    power=0;
   }
  
  }  //if Bluetooth.available
  //COLOR
  if(power==1){
    Serial.print("Relay On: ddata is ");
    Serial.println(Data);
   if(Data==0){//Closed
    colorWipe(strip.Color(255,   0,   0), 50); // Red
   }
   else if(Data==1){//Open
    colorWipe(strip.Color(0,   255,   0), 50); // Green
     colorWipe(0, 50); // Blank
   }
   else if(Data==2){//Obscured
    colorWipe(strip.Color(255,   255,   0), 50); // Yellow
     colorWipe(0, 50); // Blank
   }
    }//power on
delay(50);
}

// Fill strip pixels one after another with a color. Strip is NOT cleared
// first; anything there will be covered pixel by pixel. Pass in color
// (as a single 'packed' 32-bit value, which you can get by calling
// strip.Color(red, green, blue) as shown in the loop() function above),
// and a delay time (in milliseconds) between pixels.
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}
