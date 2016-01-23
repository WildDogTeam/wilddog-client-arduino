
/*
  Delete cloud's data

  This sketch demonstrate how to Access your data on Wilddog cloud
  using an Arduino Yún.

  A Wilddog account are necessary to run all Wilddog examples. 
  If you don't already have one, you can register for a free Wilddog account at 
  https://www.wilddog.com/ 
  
  In order to run this sketch, you'll need to creat an application using
  the Wilddog dashboard console at https://www.wilddog.com/dashboard. 
  After creating the app, you'll get an url which type following 
  https://YourAppId.wilddogio.com/
  Your data can add and save under that url,which will be access in this sketch. 

  Note that since this sketch will access your data on Wilddog cloud,
  your Arduino need to connect to the Internet first.
  
  uasge:
  1. Creat an application on  https://www.wilddog.com/dashboard. 
     This sketch will remove all data in YOURURL.
  2. Modify YOURURL to your real URL，also can be like 
	 coap://YourAppId.wilddogio.com/a/b/c .
  3. Upload to your Arduino.
  4. In your application ,You will see data in YOURURL deleted by Arduino.
    
  This example code is in the public domain.

  created on 2015/11/20.
  by skyli.
  
  https://www.wilddog.com/  
  for more information.
*/
#include <Wilddog.h>
#include "Wilddog_utility.h"
/*modify YourAppId to your appid*/
#define YOURURL  "coap://YourAppId.wilddogio.com"

#define _MAX_PIN_   13

Wilddog *p_wd = NULL;
                      
void removeCallBack(const char *pdata, int error, void* arg)
{
  Serial.print("\n remove error : ");
  Serial.print(error);
  if(error >= 200)
  {
    Serial.print("\n remove success!\n");
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
  Serial.print("\n remove value\n");
  // set value on Wilddog yun.
  res = p_wd->removeValue(removeCallBack,(void*)NULL);
  if(res < 0 )
     Serial.print("\n remove value fail \n ");
     
}

void loop()
{
  //Serial.print("trysyncing ...\n");   
  // receive and transmit.
  if(p_wd)
    p_wd->trySync();
    
}
