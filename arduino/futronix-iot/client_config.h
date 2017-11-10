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
  "off",              //OFF
  "scene one",        //1 
  "scene two",        //2 
  "scene three",      //3 
  "scene four",       //4 
  "scene five",       //5 
  "scene six",        //6 
  "scene seven",      //7 
  "scene eight",      //8 
  "scene nine",       //9
  "scene ten",        //10
  "eleven",           //11
  "twelve",           //12
  "thirteen",         //13
  "fourteen",         //14
  "fifteen",          //15
  "sixteen",          //16
  "seventeen",        //17
  "eighteen",         //18
  "nineteen",         //19
  "twenty",           //20
  "on"                //ON
};

#endif
