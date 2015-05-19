//include arduino Servo library
#include "Servo.h"

//user parameters
int n_readings = 10; //indicates how many sensor readings are used to compute a mean.
boolean verbose = true; //when true, enables displaying debug info through serial port

//arduino pins
int us_pin = 5; //analog pin where the sensor voltage divider is connected
int led_pins[] = {2,3,4}; //pins where leds are connected
int motor_pin = 3; 

//parameters (electronics)
double Vcc = 5; //power supply voltage

//motor object from Servo library
Servo motor; 

//program variables
int us_analog_level; //Output from AD converter
double us_analog_voltage; //Sensor reading in Volts
double us_range; //Range measurement in cm
double us_range_mean;//the mean over nReadings consecutive readings [cm]
double us_range_array[10]; //an array of the last n_readings readings [cm]
int array_ii = 0; //indicates the index of us_range_array to be set in the current iteration
int ii; //iterator counter
int jj; //auxiliar iterator
int n_leds;//number of leds in the bar
int n_leds_on; //how many leds should be on
double motor_angle = 180; 
double motor_speed = 90; 
double us_range_to_motor;

//setup
void setup() 
{      
      //sets analog reference to 5V on arduino Uno
      analogReference(EXTERNAL); 
      
      //sets pin as an input
      pinMode(us_pin, INPUT);

      //sets number of leds from ledPins allocation and set led pins as outputs
      n_leds = sizeof(led_pins)/2;
      for (jj=0; jj<n_leds; jj++)
      {
            pinMode(led_pins[jj], OUTPUT); // initialize the digital pin as an output.
      }
      
      //opens serial port, sets data rate to 9600 bps, Useful for debugging
      Serial.begin(9600);        
      
      //attach motor to pin 9. Min, max PWM pulse widths are 1000 us, 2000 us
      //motor.attach(motor_pin,544,2400);//Vex position servo 
      motor.attach(motor_pin,0,1000);//Vex speed servo 
      
      //stops the motor
      //motor.write(motor_angle);
      motor.write(motor_speed);
}
 
//main loop
void loop() 
{      
      //gets sensor reading
      us_analog_level = analogRead(us_pin); // read input from sensor
      us_analog_voltage = Vcc*(double)us_analog_level/1023.0; //convert digital level to analog voltage
      
      //converts voltage to range. The equation comes from the US sensor characteristics
      us_range = us_analog_voltage*512*2.54/5;
      
      //sets current reading to the vector position
      array_ii = ii%n_readings; 
      us_range_array[array_ii] = us_range; 
      
      //compute the mean. First readings may not be correct
      us_range_mean = 0;
      for (jj=0; jj<n_readings; jj++)
      {
            us_range_mean += us_range_array[jj];
      }
      us_range_mean = us_range_mean/n_readings;
      
      //sets motor speed according distance
      if (us_range_mean > 400 ) us_range_to_motor = 400; 
      else us_range_to_motor = us_range_mean; 
      motor_speed = 90 + 90*us_range_to_motor/400; //0->400 cm mapped to 90->180 servo speeds
      motor.write(motor_speed);
      
      //Serial messaging if verbose mode, each n_readings iterations
      if ( (verbose) && (ii%n_readings == 0) )
      {
            Serial.print("us_analog_level[#]: ");
            Serial.println(us_analog_level, DEC);
            Serial.print("us_analog_voltage[V]: ");
            Serial.println(us_analog_voltage, DEC);
            Serial.print("us_range[cm]: ");
            Serial.println(us_range, DEC);
            Serial.print("us_range_mean[cm]: ");
            Serial.println(us_range_mean, DEC);
            Serial.print("motor_speed: ");
            Serial.println(motor_speed, DEC);            
            Serial.print("----------------------------\n\n");
      }
      
      // wait for 100 milliseconds
      delay(100); 
      
      //increment iterator;
      ii ++;
}
