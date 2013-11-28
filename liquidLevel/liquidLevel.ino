
//user parameters
int nReadings = 10; //indicates how many sensor readings are used to compute a mean.
boolean verbose = true; //when true, enables displaying debug info through serial port

//arduino pins
int analogPin = 5; //analog pin where the sensor voltage divider is connected
int ledPins[] = {2,3,4}; //pins where leds are connected

//parameters (electronics)
double Vcc = 9.25; //power supply voltage [V]
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
int nLeds;//number of leds in the bar
int nLedsOn; //how many leds should be on

//setup
void setup() 
{
      //opens serial port, sets data rate to 9600 bps, Useful for debugging
      Serial.begin(9600);  
      
      //sets analog reference to 5V on arduino Uno
      analogReference(DEFAULT); 
      
      //sets pin as an input
      pinMode(analogPin, INPUT);

      //sets number of leds from ledPins allocation and set led pins as outputs
      nLeds = sizeof(ledPins)/2;
      for (jj=0; jj<nReadings; jj++)
      {
            pinMode(ledPins[jj], OUTPUT); // initialize the digital pin as an output.
      }
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
            //compute mean
            liquidLevelMean = 0;
            for (jj=0; jj<nReadings; jj++)
            {
                  liquidLevelMean += liquidLevelArray[jj];
            }
            liquidLevelMean = liquidLevelMean/nReadings;
            
            //indcate with leds
            nLedsOn = liquidLevelMean/lmax*3+1;
            if (nLeds > nLeds) nLedsOn = nLeds;//check upper bound (in case of noisy readings)
            if (nLeds < 0) nLedsOn = nLeds;//check upper bound (in case of noisy readings)
            for (jj=0; jj<nLedsOn; jj++) digitalWrite(ledPins[jj], HIGH);
            for (jj=nLedsOn; jj<nLeds; jj++) digitalWrite(ledPins[jj], LOW);
      }
      
      
      //Serial messaging if verbose mode, each 10 iterations
      if ( (verbose) && (ii%10 == 0) )
      {
            Serial.print("analogLevel: ");
            Serial.println(analogLevel, DEC);
            Serial.print("analogVoltage: ");
            Serial.println(analogVoltage, DEC);
            Serial.print("liquidLevel: ");
            Serial.println(liquidLevel, DEC);
            Serial.print("liquidLevelMean: ");
            Serial.println(liquidLevelMean, DEC);
            Serial.print("nLeds:  ");
            Serial.println(nLeds, DEC);
            Serial.print("nLedsOn:  ");
            Serial.println(nLedsOn, DEC);
            Serial.print("----------------------------\n\n");
      }
      
      // wait for 100 milliseconds
      delay(100); 
      
      //increment iterator;
      ii ++;
}
