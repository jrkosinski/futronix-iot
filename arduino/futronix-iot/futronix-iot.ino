
#include "client_config.h"
#include "debug.h"              // Serial debugger printing
#include "wifi.h"               // Wifi connection 
#include "wemulator.h"
#include "callback.h"
#include "futronix.h" 


WifiConnection* wifi;           // wifi connection
Futronix* futronix;             // infrared sender
Wemulator* wemulator;           // wemo emulator

//This is used as a crude workaround for a threading issue
unsigned int sceneNum = 0;

void blinkLed(int, int);


// ************************************************************************************
//Runs once, when device is powered on or code has just been flashed 
//
void setup()
{
  //if set wrong, your serial debugger will not be readable 
  Serial.begin(SERIAL_BAUD_RATE);

  //initialize the IR 
  futronix = new Futronix(IR_PIN); 

  //initialize wifi connection 
  wifi = new WifiConnection(myWifiSsid, myWifiPassword); 
  wifi->begin(); 

  //initialize wemo emulator 
  wemulator = new Wemulator(); 

  //connect to wifi 
  if (wifi->connect())
  {
    wemulator->begin();
    
    wemulator->addDevice("scene one", 80, new WemoCallbackHandler(&sceneNum, 1)); 
    wemulator->addDevice("scene two", 81, new WemoCallbackHandler(&sceneNum, 2)); 
    wemulator->addDevice("scene three", 82, new WemoCallbackHandler(&sceneNum, 3)); 
  }
}


// ************************************************************************************
// Runs constantly 
//
void loop() 
{    
  //let the wemulator listen for voice commands 
  if (wifi->isConnected)
  {
    //blinkLed(1, 100);
    wemulator->listen();
  }

  //if we've received a command, do the action 
  if (sceneNum > 0)
  {
    debugPrintln("COMMAND OUTGOING:");
    futronix->setScene(sceneNum); 
    sceneNum = 0; 
    delay(100); 
  }
}


// ************************************************************************************
// blink the LED a given number of times 
//
// args: 
//  count: number of times to blink
//  delayMs: delay between blinks
void blinkLed(int count, int delayMs)
{
  for(int n=0; n<count; n++)
  {
    debugPrintln("blink");
    digitalWrite(LED_PIN, LOW);
    delay(delayMs);
    digitalWrite(LED_PIN, HIGH);
    delay(delayMs);
  }
}

