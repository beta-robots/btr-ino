//testing maxon DC motor

//pin assignement
int pin_led = 13; // Pin 13 has a LED connected on most Arduino boards.
int pin_motor_controller_e2 = 3; //pwm
int pin_motor_controller_m2 = 2; //turn direction
unsigned long motor_iteration_delta_t = 200; //duration of each iteration [milliseconds]
int pwm_min = 100; 
int pwm_max = 200; 
int pwm_step = 2; 

//setup
void setup() 
{
    //sets pin_led as a digital output
    pinMode(pin_led, OUTPUT);
    
    //sets pin_motor_enable as a digital output
    pinMode(pin_motor_controller_m2, OUTPUT);  
}

//stops a motor at a given pin 
void stop(int _pin)
{
    //just send a PWM 0% at the pin
    analogWrite(_pin, 0);   
}

//ramp-up/down pwm to a given pin
void pwmRamp(int _pin, int _pwm_init, int _pwm_end, int _pwm_delta, unsigned long _delay)
{
    int pwm_level;//running level of pwm. 0-> off; 255->100%
    
    //ramp-up case 
    if (_pwm_delta > 0)
    {
        for(pwm_level = _pwm_init; pwm_level <= _pwm_end; pwm_level += _pwm_delta) 
        { 
            //set analog level for speed Control
            analogWrite(_pin, pwm_level);   
            
            //delay
            delay(_delay); 
        }  
    }

    //ramp-down case 
    if (_pwm_delta < 0)
    {
        for(pwm_level = _pwm_init; pwm_level >= _pwm_end; pwm_level += _pwm_delta) 
        { 
            //set analog level for speed Control
            analogWrite(_pin, pwm_level);   
            
            //delay
            delay(_delay); 
        }  
    }
}

//main loop
void loop() 
{    
//1st cycle
    // turn the LED on 
    digitalWrite(pin_led, HIGH);   
 
    //set motor direction
    digitalWrite(pin_motor_controller_m2, HIGH);   

    //ramp-up
    pwmRamp(pin_motor_controller_e2,pwm_min,pwm_max,pwm_step,motor_iteration_delta_t);
    
    //ramp-down
    pwmRamp(pin_motor_controller_e2,pwm_max,pwm_min,-pwm_step,motor_iteration_delta_t);

    //stop
    stop(pin_motor_controller_e2);

    //breath
    delay(200);
    
//2n cycle
    // turn the LED of
    digitalWrite(pin_led, LOW);   
    
    //change motor direction
    digitalWrite(pin_motor_controller_m2, LOW);   
    
    //ramp-up
    pwmRamp(pin_motor_controller_e2,pwm_min,pwm_max,pwm_step,motor_iteration_delta_t);
    
    //ramp-down
    pwmRamp(pin_motor_controller_e2,pwm_max,pwm_min,-pwm_step,motor_iteration_delta_t);
          
    //stop
    stop(pin_motor_controller_e2);

    //breath
    delay(200);

}
