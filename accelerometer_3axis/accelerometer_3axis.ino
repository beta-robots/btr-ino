//testing ADXL335

//pin assignement
int pin_led = 13; // Pin 13 has a LED connected on most Arduino boards.
int pin_x_input = 2; //x analog input
int pin_y_input = 1; //y analog input
int pin_z_input = 0; //z analog input

//constants
int num_readings = 20; 
float gravity = 9.81; 

//sensor calibration (from datasheet)
float v_supply = 3.3; //supplied at 3.3V
float x_zerog_volts = 1.42*(v_supply/3.0); //Bias level 1.5V at Vs=3V, ratiometric to Vs
float y_zerog_volts = 1.42*(v_supply/3.0); //Bias level 1.5V at Vs=3V, ratiometric to Vs
float z_zerog_volts = 1.5*(v_supply/3.0); //Bias level 1.5V at Vs=3V, ratiometric to Vs
float sensitivity_volts_g = 0.3*(v_supply/3.0);//sensitivity 300mV/g at Vs=3V, ratiometric to Vs

//program mode
boolean verbose = true;  

//setup
void setup() 
{
    //sets pin_led as a digital output
    pinMode(pin_led, OUTPUT);
    
    //sets ADC reference (top voltage to 2.56V)
    analogReference(INTERNAL2V56);
    
    //opens serial port, sets data rate to 9600 bps, Useful for debugging
    Serial.begin(9600);     
}
 
//main loop
void loop() 
{    
    int ii; //runing index
    int x_adc, y_adc, z_adc; //direct levels from analog to digital converter, for x,y,z
    float x_volts, y_volts, z_volts; //voltage levels for x,y,z [V]
    float x_accel, y_accel, z_accel; //accel for x,y,z axis [N]
    float angle_roll; //angle of rotation around x axis
    
    // turn the LED on 
    digitalWrite(pin_led, HIGH);   
    
    //reading x,y,z
    x_adc = 0; 
    y_adc = 0; 
    z_adc = 0; 
    for (ii=0; ii<num_readings; ii++)
    {
        x_adc += analogRead(pin_x_input);
        y_adc += analogRead(pin_y_input);
        z_adc += analogRead(pin_z_input);        
        delay(10);
    }
    
    //mean and convert to volts, 1024 levels, 2.56V reference top voltage
    x_volts = (2.56/1023.0)*((float)x_adc/(float)num_readings);
    y_volts = (2.56/1023.0)*((float)y_adc/(float)num_readings);
    z_volts = (2.56/1023.0)*((float)z_adc/(float)num_readings);
    
    //Convert to force
    x_accel = ((x_volts-x_zerog_volts)/sensitivity_volts_g)*gravity;
    y_accel = ((y_volts-y_zerog_volts)/sensitivity_volts_g)*gravity; 
    z_accel = ((z_volts-z_zerog_volts)/sensitivity_volts_g)*gravity; 
    
    //compute the roll angle
    angle_roll = atan2(y_accel,z_accel)*180/3.14159; 
    
    //print results if verbose mode
    if ( verbose )
    {
        Serial.print("x_accel: ");
        Serial.println(x_accel, DEC);
        Serial.print("y_accel: ");
        Serial.println(y_accel, DEC);
        Serial.print("z_accel: ");
        Serial.println(z_accel, DEC);
        Serial.print("roll (about x): ");
        Serial.println(angle_roll, DEC);
        Serial.print("----------------------------\n\n");
    }

    
    //relax
    delay(500); 
    
 
}
