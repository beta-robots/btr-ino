/**
 *
 * Basic radio receiver using panstamp NRG. 
 * Just waiting to receive three bytes at 1Hz: SOURCE_ADDR, DESTINATION_ADDR, DATA 
 * See panstamp_tx for details on transmission
 * Based on basicradio.ino by Daniel Berenguer on 07/23/2014
 *
*/

//required to display data through serial monitor
#include "HardwareSerial.h"

//constants 
#define RFCHANNEL        0       // Let's use channel 0
#define SYNCWORD1        0xB5    // Synchronization word, high byte
#define SYNCWORD0        0x47    // Synchronization word, low byte
#define SOURCE_ADDR      4       // Sender address
#define DESTINATION_ADDR 5       // Receiver address

//received data
byte src_addr_; 
byte dest_addr_; 
byte data_;

//Radio rx callback: This function is called whenever a wireless packet is received
void radioCallback(CCPACKET *packet)
{   
  // The LED will toggle when a new packet is received
  digitalWrite(LED, !digitalRead(LED));

  //check packet length and decode message
  if (packet->length == 3)
  {
    src_addr_ = packet->data[0];   // source address (Tx)
    dest_addr_ = packet->data[1];   // Our address (Rx)
    data_ = packet->data[2];   // data
  }
  
  //print thorugh serial monitor
  Serial.print(src_addr_, DEC);  
  Serial.print(" ");  
  Serial.print(dest_addr_, DEC);
  Serial.print(" ");    
  Serial.println(data_, DEC);
  
}

void setup()
{
  //configure radio
  //panstamp.init(CRFREQ_915); 
  panstamp.radio.setChannel(RFCHANNEL);
  panstamp.radio.setSyncWord(SYNCWORD1, SYNCWORD0);
  panstamp.radio.setDevAddress(DESTINATION_ADDR);
  panstamp.radio.setCCregs();

  // Let's disable address check for the current project so that our device will receive packets even not addressed to it.
  //panstamp.radio.disableAddressCheck();
  panstamp.radio.enableAddressCheck();

  // Declare RF callback function
  panstamp.setPacketRxCallback(radioCallback);
  
  //opens serial port, sets data rate to 38400 bps (debugging purposes)
  Serial.begin(38400);
}

void loop()
{
  //alive message
  Serial.println("Rx alive");
  
  // sleep
  delay(5000); 

  //For low-power applications replace "delay" by "panstamp.sleepWd(WDTO_8S)" for example
  //panstamp.sleepWd(WDTO_8S);
  
  //wake up on radio
  //panstamp.radio.setWorState(100);
  //delay(1);
}

