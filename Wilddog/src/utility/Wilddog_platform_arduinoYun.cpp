/*
  WD_ArduinoYun.cpp - Library for flashing WD_ArduinoYun code.
  Created by Sky.Li, October 27, 2015.
  Released into the public domain.
*/
#include "wilddog_platform_arduinoYun.h"
#include "../Wilddog_utility.h"
						

WD_ArduinoYun::WD_ArduinoYun()
{
  // Initialize Bridge
  Bridge.begin();
}

WD_ArduinoYun::~WD_ArduinoYun() {
	_p.close();
}
/*send string to ar9331.Note that function is not-blocking.
*/
void WD_ArduinoYun::asyncSend(const char *src)
{
	if(src && strlen(src) > 0)
	{
		int len = 0,cnt = 0;
		char *sendBuffer = NULL;
		String sendString;

		cnt = sjson_countSecialCharacter(src);
		len = strlen(src) + cnt + 2;
		sendBuffer = (char*)malloc(len);
		if(sendBuffer == NULL)
			return ;

		memset(sendBuffer,0,len);
		sjson_fillSlash(src,sendBuffer,&len);

		//Serial.print("\n sending: ");
		//Serial.write(sendBuffer,strlen(sendBuffer));
		if( _p.running())
				_p.close();	
		
		sendString = String(sendBuffer);
		_p.runShellCommandAsynchronously(sendString);
		_p.flush();
		if(sendBuffer)
			free(sendBuffer);

	}
}
/*
* Get the number of bytes (characters) available for reading from the serial port. 
* This is data that's already arrived and stored in the serial receive buffer (which holds 64 bytes). 
* Available() inherits from the Stream utility class
*/
int WD_ArduinoYun::available()
{
	return _p.available();
}
/*
* Read a byte receive from ar9331.
*/
int WD_ArduinoYun::read()
{
	return _p.read();
}


