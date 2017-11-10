#ifndef __WEMO_CALLBACK_HANDLER_H__
#define __WEMO_CALLBACK_HANDLER_H__

#include "wemulator.h"
#include "debug.h"

/****************************************
 * WemoCallbackHandler
 * --------------------
 */
class WemoCallbackHandler : public IWemoCallbackHandler 
{
  private: 
    unsigned int _scene;
    unsigned int* _pSceneNo;
    
  public: 
    WemoCallbackHandler(unsigned int* pSceneNo, unsigned int targetScene); 
 
    virtual void handleCallback(int param); 
}; 
/****************************************/


// ************************************************************************************
// constructor; pass reference to a flag
// 
 WemoCallbackHandler::WemoCallbackHandler(unsigned int* pSceneNo, unsigned int targetScene)
{
  this->_pSceneNo = pSceneNo;
  this->_scene = targetScene;
}

// ************************************************************************************
// handles the callback; param is ignored 
// 
void WemoCallbackHandler::handleCallback(int param)
{
  debugPrintln("got callback");
  *(this->_pSceneNo) = this->_scene;
}

#endif 
