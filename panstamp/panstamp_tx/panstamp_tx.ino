/**
 *
 * Basic radio transmitter using panstamp NRG. 
 * Just send three bytes each second: SOURCE_ADDR, DESTINATION_ADDR, DATA
 * Based on basicradio.ino by Daniel Berenguer on 07/23/2014
 *
*/

//constants 
#define RFCHANNEL        0       // Let's use channel 0
#define SYNCWORD1        0xB5    // Synchronization word, high byte
#define SYNCWORD0        0x47    // Synchronization word, low byte
#define SOURCE_ADDR      4       // Sender address
#define DESTINATION_ADDR 5       // Receiver address

CCPACKET tx_packet_;  // packet object
byte data_ = 0;

void setup()
{
  // Setup LED output pin
  //pinMode(LED, OUTPUT);
  //digitalWrite(LED, LOW);

  //configure radio
  panstamp.radio.setChannel(RFCHANNEL);
  panstamp.radio.setSyncWord(SYNCWORD1, SYNCWORD0);
  panstamp.radio.setDevAddress(SOURCE_ADDR);
  panstamp.radio.setCCregs();

  // Let's disable address check for the current project so that our device will receive packets even not addressed to it.
  //panstamp.radio.disableAddressCheck();
}

void loop()
{
  //set packet length
  tx_packet_.length = 3; 

  //fill packet with addresses and data
  tx_packet_.data[0] = SOURCE_ADDR; 
  tx_packet_.data[1] = DESTINATION_ADDR; 
  tx_packet_.data[2] = data_++;
  
  // Transmit packet
  panstamp.radio.sendData(tx_packet_);     
  
  //indicate activity with LED
  digitalWrite(LED, !digitalRead(LED));
  
  // Transmit every 1 seconds (For low-power applications replace "delay" by "panstamp.sleepWd(WDTO_8S)" for example)
  delay(1000);
}

