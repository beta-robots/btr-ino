//testing maxon DC motor

//pin assignement
int pin_led = 13; // Pin 13 has a LED connected on most Arduino boards.
int pin_motor_controller_e1 = 3; //pwm
int pin_motor_controller_m1 = 2; //turn direction
unsigned long motor_iteration_delta_t = 200; //duration of each iteration [milliseconds]

//setup
void setup() 
{
    //sets pin_led as a digital output
    pinMode(pin_led, OUTPUT);
    
    //sets pin_motor_enable as a digital output
    pinMode(pin_motor_controller_m1, OUTPUT);  
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
    digitalWrite(pin_motor_controller_m1, HIGH);   

    //ramp-up
    pwmRamp(pin_motor_controller_e1,100,200,2,motor_iteration_delta_t);
    
    //ramp-down
    pwmRamp(pin_motor_controller_e1,200,100,-2,motor_iteration_delta_t);


    //breathe
    delay(200);
    
//2n cycle
    // turn the LED of
    digitalWrite(pin_led, LOW);   
    
    //change motor direction
    digitalWrite(pin_motor_controller_m1, LOW);   
    
    //ramp-up
    pwmRamp(pin_motor_controller_e1,100,200,2,motor_iteration_delta_t);
    
    //ramp-down
    pwmRamp(pin_motor_controller_e1,200,100,-2,motor_iteration_delta_t);
}
