/*
  Push message to the cloud data

  This sketch demonstrate how to Access your data on Wilddog Yun
  using an Arduino Yún.

  A Wilddog account are necessary to run all Wilddog examples. 
  If you don't already have one, you can register for a free Wilddog account at 
  http://www.wilddog.com/ 
  
  In order to run this sketch, you'll need to creat an application using
  the Wilddog dashboard console at https://www.wilddog.com/dashboard. 
  After creating the app, you'll get an url which type following 
  https://YourAppId.wilddogio.com/
  Your data can add and save under that url,which will be access in this sketch. 

  Note that since this sketch will access your data on WilddogYun,
  your Arduino Yun need to connect to the Tnternet first.
  
  uasge:
  1. Creat an application on  https://www.wilddog.com/dashboard. 
     This sketch will push an message {"pin13":"1"}  to the application your just build.    
  2. Modify YOURURL to your application.
  3. Upload to your ArduinoYun.
  4. Open the Arduino IDE's Serial port monitor,and it will print serial number that your message have save .
     And you will see {"pin13":"1"} already on your application .
  
  
  This example code is in the public domain.
    
  created on 2015/11/20.
  by skyli.
  
  http://www.wilddog.com/  
  for more information.
*/

#include <Wilddog.h>
#include "Wilddog_utility.h"
#define YOURURL  "coap://YourAppId.wilddogio.com"
#define SETTING_DATA "{\"pin13\":\"1\"}"

Wilddog *p_wd = NULL;
                      
void pushCallBack(const char *pdata, int error, void* arg)
{
  Serial.print("\n get error : ");
  Serial.print(error);
  if(pdata)
  {
      Serial.print("\n get path : ");
      Serial.print(pdata);
    }
  if (arg)
     Serial.print(*(char*)arg);
}

void setup() {
  int res = 0;
  // Initialize Bridge
  Bridge.begin();
  // Initialize Serial
  Serial.begin(9600);
  // Wait until a Serial Monitor is connected.
  while (!Serial);
  
  Serial.print(YOURURL);
  p_wd = new  Wilddog(YOURURL);   
  Serial.print("\n push \n");
  // set value on Wilddog yun.
  res = p_wd->push(SETTING_DATA,pushCallBack,(void*)NULL);
  if(res < 0 )
     Serial.print("\n push  fault \n ");
}

void loop()
{
  Serial.print("trysyncing ...\n");   
  // receive and transmit.
  if(p_wd)
    p_wd->trySync();
    
}
