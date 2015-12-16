/*
  Wilffog_conn.h - Library for flashing Connect code.
  Created by Sky.Li, October 27, 2015.
  Released into the public domain.
*/
/*
  Connect.h - Library for flashing Connect code.
  Created by Sky.Li, October 27, 2015.
  Released into the public domain.
*/

#ifndef _WILDDOG_CONN_H_
#define _WILDDOG_CONN_H_

#include "Arduino.h"
#include <Bridge.h>
#include <Process.h>

#include "../Wilddog_type.h"
#if defined (ARDUINO_AVR_YUN) || defined (ARDUINO_AVR_TRE)

#include "Wilddog_platform_arduinoYun.h"
#define _PLATFORM   WD_ArduinoYun

#else

#define _PLATFORM   WD_ESP8266

#endif


typedef void (*CallBackFunc)(const char *pdata, int error, void* arg);


class Connect
{
  public:
    
    Connect();
	~Connect();
    unsigned long connect_init(const char *url);
    int connect_deInit(void);
    
    int connect_send(Daemon_cmd_T cmd,CallBackFunc f_callback,void *arg);
    int connect_send(Daemon_cmd_T cmd,Wilddog_EventType_T event);
    int connect_send(Daemon_cmd_T cmd,Wilddog_EventType_T event,CallBackFunc f_callback,void *arg);
    int connect_send(Daemon_cmd_T cmd,const char *data,CallBackFunc f_callback,void *arg);
    int connect_send(Daemon_cmd_T cmd,const char *data,const char *p_host,CallBackFunc f_callback,void *arg);

    void trySync();
  
	
  private:

    
    _PLATFORM _p; 
	
	void _connect_getRespond(unsigned long wd_index);
	
    /* debug*/
    void _print(const char *src);
    void _printArray(const char *src,int len);

    void _connect_blockingReceive();
    int _connect_asyncReceive(Daemon_cmd_T *p_cmd,int *p_error);
    long int _connect_send(Daemon_cmd_T cmd,Wilddog_EventType_T event,unsigned long index,
					const char *src,const char *p_host);
    
    unsigned long index;
	static int _l_initUrl_num;
    static unsigned long _l_port;
};

#endif
