
//user parameters
double lTh = 15; //length threshold to open electrovalve [cm] 
int analogPin = 5; //analog pin where the sensor voltage divider is connected
int nReadings = 10; //indicates how many sensor readings are used to compute a mean.
boolean verbose = true; //when true, enables displaying debug info through serial port

//parameters (electronics)
double Vcc = 9.0; //power supply voltage [V]
double RL = 1500; //resistance of the voltage divider [ohm]
double Rmin = 300;//min resistance value of eTape sensor [ohm]
double lmax = 21.4; //total length of eTape sensor [cm]
double alpha = 56; //conversion factor eTape sensor [ohm/cm]
double arduinoVref = 5.0; //measure it in your 5V pin [V]

//program variables
int analogLevel; //Output from AD converter
double analogVoltage; //Sensor reading after at voltage divider [V]
double liquidLevel; //liquid level following the eTape sensor printed meter [cm]
double liquidLevelMean;//the mean over nReadings consecutive readings [cm]
double liquidLevelArray[10]; //an array of the last nReadings readings [cm]
int arrayPt = 0; //indicates the index of liquidLevelArray to be set in the current iteration
int ii; //iterator counter
int jj; //array counter

//setup
void setup() 
{
      //opens serial port, sets data rate to 9600 bps, Useful for debugging
      Serial.begin(9600);  
      
      //sets analog reference to 5V on arduino Uno
      analogReference(DEFAULT); 
      
      //sets pin as an input
      pinMode(analogPin, INPUT);
}
 
//main loop
void loop() 
{      
      //gets sensor reading
      analogLevel = analogRead(analogPin); // read the input pin
      analogVoltage = arduinoVref*analogLevel/1023.0; //convert digital level to analog voltage
      
      //converts voltage to liquid level. The equation comes from the voltage divider and eTape sensor characteristics
      liquidLevel = lmax + ( Rmin-RL/(Vcc/analogVoltage - 1) )*1/alpha; 
      
      //sets current reading to the vector position
      arrayPt = ii%nReadings; 
      liquidLevelArray[arrayPt] = liquidLevel; 
      
      //Entry to compute the mean , once we have the liquidLevelArray full 
      if (ii >= nReadings) 
      {
            liquidLevelMean = 0;
            for (jj=0; jj<nReadings; jj++)
            {
                  liquidLevelMean += liquidLevelArray[jj];
            }
            liquidLevelMean = liquidLevelMean/nReadings;
      }
      
      //Serial messaging if verbose mode, each 10 iterations
      if ( (verbose) && (ii%10 == 0) )
      {
            //Serial.print("analogLevel is ");//prints through serial port
            //Serial.println(analogLevel, DEC);//prints through serial port
            //Serial.print("analogVoltage is ");//prints through serial port
            //Serial.println(analogVoltage, DEC);//prints through serial port
            //Serial.print("liquidLevel is ");//prints through serial port
            //Serial.println(liquidLevel, DEC);//prints through serial port
            Serial.print("liquidLevelMean is ");//prints through serial port
            Serial.println(liquidLevelMean, DEC);//prints through serial port
      }
      
      // wait for a second
      delay(100); 
      
      //increment iterator and array pointer;
      ii ++;
}
