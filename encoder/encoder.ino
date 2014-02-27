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

//ENCODER PARAMETERS
int ppr = 360; //pulses per revolution

//main variables
volatile int encoderBpin = 3; //pin where encoder B signal is attached
volatile long pulses = 0; //encoder pulse counter
long p0 = 0; //last value for pulses
long p1 = 0; //current value for pulses
int t0 = 0; //last time measurement
int t1 = 0; //current time measurement
double vRot = 0; //rotational velocity in degrees/s 

void setup()
{
      //opens serial port, sets data rate to 9600 bps
      Serial.begin(9600);
      
      //attach interrupts to A and B encoder signals
      attachInterrupt(0, encoderAinterrupt, RISING);
      
      //init t0
      t0 = millis();
}

void loop()
{      
      // wait for 1/5 second
      delay(200);       
      
      //get time now
      t1 = millis();
      
      //get number of pulses from interrupt counter (should be protected by a kind of mutex !)
      p1 = pulses;
      
      //compute vRot
      vRot = ((double)(p1-p0)/(double)(t1-t0))*1000*(360.0/(double)ppr);
      
      //keep current values
      t0 = t1;
      p0 = p1;
      
      //Output rotational velocity value
      Serial.print(t1,DEC);
      Serial.print(" ");
      Serial.print(p1,DEC);
      Serial.print(" ");
      Serial.println(vRot, DEC);
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
