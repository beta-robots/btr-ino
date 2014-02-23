//
// PURPOSE: 
// This program reads signals A and B from an incremental encoder Hohner Serie 11.
// The program outputs average rotational velocity at %Hz with rotation direction sense
//
// AUTHOR:
// Andreu Corominas Murtra, andreu@beta-robots.com, www.beta-robots.com
//
// LICENSE
// BSD, ... so take it, copy it, and do whatever you want. 
// However, even if you are not forced, it would be nice to hear from you, specially if you find bugs or you improve something :-)
//

//main variables
volatile long pulses = 0;
volatile int encoderBpin = 3;

void setup()
{
      // opens serial port, sets data rate to 9600 bps
      Serial.begin(9600);
      
      //attach interrupts to A and B encoder signals
      attachInterrupt(0, encoderAinterrupt, RISING);
}

void loop()
{
      //Output current pulses
      Serial.print("pulses: ");
      Serial.println(pulses, DEC);
      
      // wait for 1/5 second
      delay(200);       
}

void encoderAinterrupt()
{
      //check quadrature signal (signal B) to decide increment or decrement
      if ( digitalRead(encoderBpin) == HIGH ) 
      {
            pulses ++;
      }
      else
      {
            pulses --;
      }
}
