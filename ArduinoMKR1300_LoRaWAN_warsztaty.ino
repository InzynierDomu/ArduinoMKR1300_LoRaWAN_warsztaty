/**
 * @file ArduinoMKR1300_LoRaWAN.ino
 * @brief LoRaWAN end device - Main
 * @author by Szymon Markiewicz
 * @details  
 * @date 08-2019
 */

#include "config.h"
#include "PinConfig.h"
#include "MKRWAN.h"

LoRaModem modem;    ///< LoRa modem
int internal_counter = 0;   ///< counter for sending interval

/**
 * @brief preparation to work, startup
 */
void setup()
{
  GPIO_setup();
  
#ifdef SERIAL 
  Serial.begin(115200);
  while (!Serial);
#endif /* SERIAL */  

  LoRaWAN_setup();
  digitalWrite(LED_PIN, 0);
}

/**
 * @brief main loop
 */
void loop()
{
  delay(REPS_INTERVAL);
  
  byte pin_state = digitalRead(BTN_PIN);

  String msg = "0000000";
  msg[0] = char(pin_state);
  
  //send msg
  Serial.print("Sending: ");
  for (unsigned int i = 0; i < msg.length(); i++) {
    Serial.print(msg[i] >> 4, HEX);
    Serial.print(msg[i] & 0xF, HEX);
  }  
  Serial.println();
 
  modem.dataRate(0);
  delay(1000);
  
  int err;
  modem.beginPacket();
  modem.print(msg);
  err = modem.endPacket(true);
 
  if (err > 0) {
    Serial.print("Message sent correctly!");
  } else {
    Serial.print("Error sending message");
    Serial.println(err);
  }

  if (modem.available()==0) {
    Serial.println("No downlink message received at this time.");
    return;
  }
  char rcv[64];
  int i = 0;
  while (modem.available()) {
    rcv[i++] = (char)modem.read();
  } 
  Serial.print("Received: ");
  for (unsigned int j = 0; j < i; j++) {
    Serial.print(rcv[j] >> 4, HEX);
    Serial.print(rcv[j] & 0xF, HEX);
    Serial.print(" ");
  } 
}

/**
 * @brief GPIO setup and config
 */
void GPIO_setup()
{
  pinMode(BTN_PIN, INPUT_PULLUP);
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, 1);
}

/**
 * @brief LoRaWAN modem setup and config
 */
void LoRaWAN_setup()
{
   if (!modem.begin(EU868)) {
    Serial.print("Failed to start module");
    while (1) 
    {
      digitalWrite(LED_PIN, 1);
      delay(1000);
      digitalWrite(LED_PIN, 0);
      delay(1000);
    }
  };    
  Serial.print("Module start correct");
  Serial.print("Module version is: ");
  Serial.println(modem.version());
  Serial.print("Device EUI is: ");
  Serial.println(modem.deviceEUI());
  int connected = 0;
  if (IS_OTAA){
    connected = modem.joinOTAA(APPEUI, APPKEY, DEVEUI);
  }else{
    connected = modem.joinABP(DEVADDR, NWKSKEY, APPSKEY);
  }

  if (!connected) {  
    Serial.print("Something went wrong.");   
    while (1) 
    {
      digitalWrite(LED_PIN, 1);
      delay(1000);
      digitalWrite(LED_PIN, 0);
      delay(1000);
    }
  }
  modem.dataRate(0);
  delay(1000);
}
