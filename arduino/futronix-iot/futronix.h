
#ifndef __FUTRONIX_H__
#define __FUTRONIX_H__

#include "ir.h" 

class Futronix
{
  private: 
    IRTransmitter* _ir;
    
  public: 
    Futronix(int ir_pin); 
    ~Futronix();

    void begin();
    void setScene(unsigned int scene); 

  private: 
    unsigned short getSceneCommand(unsigned int scene);
};


Futronix::Futronix(int ir_pin)
{
  this->_ir = new IRTransmitter(ir_pin);
}

Futronix::~Futronix()
{
  delete _ir;
}

void Futronix::begin()
{
  this->_ir->begin(); 
}

void Futronix::setScene(unsigned int scene)
{
  unsigned short cmd = this->getSceneCommand(scene); 
  if (cmd > 0)
    this->_ir->sendFutronix(cmd);
}

unsigned short Futronix::getSceneCommand(unsigned int scene)
{
  switch(scene)
  {
    case 1: 
      return 0x13; 
    case 2: 
      return 0x14; 
    case 3: 
      return 0x15; 
  }

  return 0;
}

#endif
