
#ifndef __FUTRONIX_H__
#define __FUTRONIX_H__

#include "ir.h" 
#include "debug.h"
  #include "client_config.h"

#define COMMANDS_LEN 20

/****************************************
 * Futronix  
 * ---------
 * Futronix command interface. 
 */
class Futronix
{
  private: 
    IRTransmitter* _ir;
    unsigned short _commands[COMMANDS_LEN] = { 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17, 0x18, 0x19, 0x10, 0x1a, 0x1b, 0x1c, 0x3d, 0x37, 0x35, 0x32, 0x36, 0x34, 0x3a }; 
    unsigned short _off = 0x02;
    unsigned short _on = 0x3f; 
    
  public: 
    Futronix(int ir_pin); 
    ~Futronix();

    void begin();
    void setScene(unsigned int scene); 

  private: 
    unsigned short getSceneCommand(unsigned int scene);
};
/****************************************/


// ************************************************************************************
// public constructor 
//
// args
//  ir_pin: pin number for IR pin
//
Futronix::Futronix(int ir_pin)
{
  this->_ir = new IRTransmitter(ir_pin);
}

// ************************************************************************************
// public destructor
// 
Futronix::~Futronix()
{
  delete _ir;
}

// ************************************************************************************
// initializes the instance and gets it ready for use. 
// 
void Futronix::begin()
{
  this->_ir->begin(); 
}

// ************************************************************************************
// sets the specified scene (specified by scene number, 1-based index)
// 
// args
//  scene: the scene number to set (1-based index)
//
void Futronix::setScene(unsigned int scene)
{
  unsigned short cmd = this->getSceneCommand(scene); 
  if (cmd > 0){
    debugPrintln("sending command"); 
    debugPrintln(cmd);
    this->_ir->sendFutronix(cmd);
  }
}

// ************************************************************************************
// gets the command code to set the given scene
// 
// args
//  scene: the scene number to translate (1-based index)
//
// returns: an IR command code 
// 
unsigned short Futronix::getSceneCommand(unsigned int scene)
{
  if (scene > 0 && scene <= COMMANDS_LEN)
    return _commands[scene-1]; 
  else if (scene == 0)
    return _off;
  else if (scene > COMMANDS_LEN)
    return _on;

  return 0;
}

#endif
