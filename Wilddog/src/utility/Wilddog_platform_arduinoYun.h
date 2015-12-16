/*
  Connect.h - Library for flashing Connect code.
  Created by Sky.Li, October 27, 2015.
  Released into the public domain.
*/
/*
  Connect.h - Library for flashing Connect code.
  Created by Sky.Li, October 27, 2015.
  Released into the public domain.
*/

#ifndef _WILDDOG_PLATFORM_ARDUINOYUN_H_
#define _WILDDOG_PLATFORM_ARDUINOYUN_H_

#include "Arduino.h"
#include <Bridge.h>
#include <Process.h>


class WD_ArduinoYun
{
  public:
    
    WD_ArduinoYun();
	~WD_ArduinoYun();
    
  void asyncSend(const char *src);
  
  int available();
  int read();

  private:
    Process _p; 
  
};


#endif
