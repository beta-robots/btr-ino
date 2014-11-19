
// Define the pin where relay coil is connected
int relayPin = 12;

//setup
void setup() 
{
    //sets relayPin as an output
    pinMode(relayPin, OUTPUT);  
}
 
//main loop
void loop() 
{
    // switch relay and wait
    digitalWrite(relayPin, HIGH);   
    delay(3000);    
      
    // switch relay and wait
    digitalWrite(relayPin, LOW);
    delay(3000);     
}
