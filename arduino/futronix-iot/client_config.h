#ifndef __CLIENT_CONFIG__
#define __CLIENT_CONFIG__

//SET YOUR WIFI CREDS 
const char* myWifiSsid      = "mina"; 
const char* myWifiPassword  = "HappyTime";

//SET TO MATCH YOUR HARDWARE 
#define SERIAL_BAUD_RATE    9600

//PIN 0 is D3 ON THE CHIP 
#define IR_PIN              0
#define LED_PIN             2

//scene names to scenes mapping 
const char* sceneNamesMap[] = { 
  "off",                    //OFF
  "scene one",              //1 
  "scene two",              //2 
  "scene three",            //3 
  "scene four",             //4 
  "scene five",             //5 
  "scene six",              //6 
  "scene seven",            //7 
  "scene eight",            //8 
  "scene nine",             //9
  "scene ten",              //10
  "scene eleven",           //11
  "scene twelve",           //12
  "scene thirteen",         //13
  "scene fourteen",         //14
  "scene fifteen",          //15
  "scene sixteen",          //16
  "scene seventeen",        //17
  "scene eighteen",         //18
  "scene nineteen",         //19
  "scene twenty",           //20
  "on"                      //ON
};

#endif
