/*
  Wilddog.h - Library for flashing Wilddog code.
  Created by Sky.Li, October 27, 2015.
  Released into the public domain.
*/

#ifndef Wilddog__h
#define Wilddog__h

#include "Arduino.h"
#include "utility/Wilddog_conn.h"

class Wilddog
{
    public:
        Wilddog(const char *p_url);
        ~Wilddog();

        int getValue(CallBackFunc f_callback,void *arg);
        int setValue(const char *p_data,CallBackFunc f_callback,void *arg);
        int push(const char *p_data,CallBackFunc f_callback,void *arg);
        int removeValue(CallBackFunc f_callback,void *arg);
        int addObserver(Wilddog_EventType_T event,CallBackFunc f_callback,void *arg);
        int removeObserver(Wilddog_EventType_T event);
        int auth(const char *p_auth,const char *p_host,CallBackFunc onAuth,void *arg);
        
        void trySync();

    
    private:
        
       Connect _wd_connect;
       unsigned long wilddog_index;
        
};


#endif
