//include arduino Servo library
#include "Servo.h"
 
// Pin 13 has a LED connected on most Arduino boards.
int ledPin = 13;

//motor object from Servo library
Servo motor; 

//setup
void setup() 
{
      //attach motor to pin 9. Min, max PWM pulse widths are 1000 us, 2000 us
      motor.attach(9,1000,2000);
      
      //stops the motor
      motor.write(90);
        
      //also sets LED_PIN as an output
      pinMode(ledPin, OUTPUT);  
}
 
//main loop
void loop() 
{
      digitalWrite(ledPin, HIGH);   // turn the LED on 
      motor.write(180);             // maximum positive rotational velocity
      delay(1000);                  // wait for a second

      digitalWrite(ledPin, LOW);    // turn the LED off
      motor.write(0);               // maximum negative rotational velocity
      delay(1000);                  // wait for a second
}
