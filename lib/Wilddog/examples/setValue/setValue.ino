/*
  Modify the cloud data

  This sketch demonstrate how to Modify your Wilddog cloud's data
  using an Arduino.

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
     This sketch will push an message {"pin13":"1"}  to the application your just build.    
  2. Modify YOURURL to your application url.
  3. Upload to your Arduino.
  4. You will see {"pin13":"0"} already on your application's data.
  
  
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
#define SETTING_DATA "{\"pin13\":\"0\"}"

Wilddog *p_wd = NULL;
                        
void setValueCallBack(const char *pdata, int error, void* arg)
{
  Serial.print("\n get error : ");
  Serial.print(error);
  if(pdata)
  {
      Serial.print("\n get data : ");
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
  Serial.print("\n set value\n");
  // set value on Wilddog yun.
  res = p_wd->setValue(SETTING_DATA,setValueCallBack,(void*)NULL);
  if(res < 0 )
     Serial.print("\n set value fail \n ");
}

void loop()
{
  //Serial.print("trysyncing ...\n");   
  // receive and transmit.
  if(p_wd)
    p_wd->trySync();
    
}
