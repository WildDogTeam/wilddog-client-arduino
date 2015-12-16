/*
  subscribe

  This sketch demonstrate how to subscribe your data on Wilddog Yun
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
     Add {"pin13":"1"} to your application which this sketch ask for.
            
  2. Modify YOURURL to your application.
  3. Upload to your ArduinoYun.
  4.Open the Arduino IDE's Serial port monitor,and it will print the cloud data.
  5. Modify your application's data to {"pin13":"0"} and Take care L13 on your ArudinoYun.
  
  
  This example code is in the public domain.
    
  created on 2015/11/20.
  by skyli.
  
  http://www.wilddog.com/  
  for more information.
*/
#include <Wilddog.h>
#include "Wilddog_utility.h"
#define YOURURL  "coap://YourAppId.wilddogio.com"
#define _KEY_PIN  "pin"

#define _MAX_PIN_   13

Wilddog *p_wd = NULL;


                        
int getPinValue(const char *src,int pinNumber,int *value)
{
  char pinName[100],pinValue[100];
  int len =100;

  memset(pinName,0,sizeof(pinName));
  memset(pinValue,0,sizeof(pinValue));

  sprintf(pinName,"%s%d",_KEY_PIN,pinNumber);
  if(sjson_get_value(src,pinName,pinValue,&len) < 0 )
    return 0;
    
 *value = atoi(pinValue);
  return 1;
}

void handleReceivePacket(const char *src)
{
    int i=0,value;

    for(i=0;i<=_MAX_PIN_;i++ )
    {
      if(getPinValue(src,i,&value) == 0)
        continue;
      if(value == 0)
        digitalWrite(i, LOW);
      else
        digitalWrite(i, HIGH);
      }
      
   return ;   
}
                        
void addObserverCallBack(const char *pdata, int error, void* arg)
{
  Serial.print("\n get error : ");
  Serial.print(error);
  if(pdata)
  {
      Serial.print("\n get newest data : ");
      Serial.print(pdata);
      /* get pin no and pin value */
       handleReceivePacket(pdata);
    }
  if (arg)
     Serial.print(*(char*)arg);
}

void setup() {
  int res = 0 ;
  // Initialize Bridge
  Bridge.begin();
  // Initialize Serial
  Serial.begin(9600);
  // Wait until a Serial Monitor is connected.
  while (!Serial);
  Serial.print(YOURURL);
  //wd.setValue(TEST_DATA,getcallbackFunc,(void*)NULL);
  
  Serial.print(YOURURL);
  p_wd = new  Wilddog(YOURURL);   
  Serial.print("\n star addObserver \n");
  
  res = p_wd->addObserver(WD_ET_VALUECHANGE,addObserverCallBack,(void*)NULL);
  if(res < 0 )
     Serial.print("\n subscribe fault \n ");
     
  Serial.print("\n setup end : ");
}

void loop()
{
  Serial.print("trysyncing ...\n");   
  if(p_wd)
    p_wd->trySync(); 
}
