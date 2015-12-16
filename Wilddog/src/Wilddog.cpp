/*
 * Wilddog.cpp - Library for flashing Wilddog code.
 * Created by Sky.Li, October 27, 2015.
 * Released into the public domain.
 * Copyright (C) 2014-2016 Wilddog Technologies. All Rights Reserved. 
 *
 * FileName: Wilddog.cpp
 *
 * Description: Wilddog class interface implementation.
 *
 * History:
 * Version      Author          Date        	Description
 *
 * 0.5       	lxs              2015-12-07  	Create file.
 *
 */

#include "Wilddog.h"
#include "wilddog_type.h"
#include "utility/Wilddog_conn.h"

/*
 * Function:    trySync
 * Description: When called, try to sync interal time and receive data from 
 *              internet.
 * Input:       N/A
 * Output:      N/A
 * Return:      N/A
*/
void Wilddog::trySync()
{
    _wd_connect.trySync();
}
/*
 * Function:    Wilddog.
 * Description: Init a wilddog object and the path in the HOST tree.
 * Input:       p_url: A url such as coaps://<appid>.wilddogio.com/<path>.
 * Output:      N/A.
 * Return:      N/A.
*/
Wilddog::Wilddog(const char *p_url)
{
    wilddog_index = _wd_connect.connect_init(p_url);
}
/*
 * Function:    ~Wilddog.
 * Description: Destory a wilddog object.
 * Input:       N/A.
 * Output:     N/A.
 * Return:      N/A.
*/
Wilddog::~Wilddog() 
{
    _wd_connect.connect_deInit();
    wilddog_index = 0;
}
/*
 * Function:    getValue
 * Description: Get the data of the object from server.
 * Input:       
 *              f_callback: the callback function called when the server returns 
 *                      a response or send fail.
 *              args: the arg defined by user, if you do not need, can be NULL.
 * Output:      N/A
 * Return:      0 means succeed, negative number means failed.
*/
int Wilddog::getValue(CallBackFunc f_callback,void *arg)
{
  if(wilddog_index) 
    return _wd_connect.connect_send(_CMD_GET,f_callback,arg);  
  else
    return -1;
}
/*
 * Function:    setValue
 * Description: Post the data of the object to server.
 * Input:       
 *              p_data: a point to json which you want to post to the serer.
 *              f_callback: the callback function called when the server returns 
 *                      a response or send fail.
 *              args: the arg defined by user, if you do not need, can be NULL.
 * Output:      N/A
 * Return:      0 means succeed, negative number means failed.
*/

int Wilddog::setValue(const char *p_data,CallBackFunc f_callback,void *arg)
{
    if(wilddog_index)
        return _wd_connect.connect_send(_CMD_SET,p_data,f_callback,arg);  
    else
        return -1;
}
/*
 * Function:    push
 * Description: Push the data of the object to server.
 * Input:   
 *              p_data: a point to json which you want to post to the serer.
 *              f_callback: the callback function called when the server returns 
 *                      a response or send fail.
 *              args: the arg defined by user, if you do not need, can be NULL.
 * Output:      N/A
 * Return:      0 means succeed, negative number means failed.
*/
int Wilddog::push(const char *p_data,CallBackFunc f_callback,void *arg)
{
    if(wilddog_index)
        return _wd_connect.connect_send(_CMD_PUSH,p_data,f_callback,arg);  
    else
        return 0;
}
/*
 * Function:    removeValue
 * Description: Remove the data of the object from server.
 * Input:     
 *              f_callback: the callback function called when the server returns 
 *                      a response or send fail.
 *              arg: the arg defined by user, if you do not need, can be NULL.
 * Output:      N/A
 * Return:      0 means succeed, negative number means failed.
*/
int Wilddog::removeValue(CallBackFunc f_callback,void *arg)
{
    
    if(wilddog_index)
        return _wd_connect.connect_send(_CMD_REMOVE,f_callback,arg); 
    else 
        return -1;
}
/*
 * Function:    addObserver
 * Description: Subscibe the object's data change, if data changed, server 
 *              will notify the client.
 * Input:     
 *              event: Event type, see the struct.
 *              f_callback: The callback function called when the server 
 *                          sends a data change packet.
 *              arg: The arg defined by user, if you do not need, 
 *                          can be NULL.
 * Output:      N/A
 * Return:      0 means succeed, negative number means failed.
*/
int Wilddog::addObserver(Wilddog_EventType_T event,CallBackFunc f_callback,void *arg)
{
    if(wilddog_index)
        return _wd_connect.connect_send(_CMD_ON,event,f_callback,arg);  
    else
        return -1;
}
/*
 * Function:    removeObserver
 * Description: Unsubscibe the object's data change.
 * Input:       
 *              event: Event type, see the struct.
 * Output:      N/A
 * Return:      0 means succeed, negative number means failed.
*/
int Wilddog::removeObserver(Wilddog_EventType_T event)
{
    if(wilddog_index)
        return _wd_connect.connect_send(_CMD_OFF,event);  
    else
        return -1;
}
/*
 * Function:    auth
 * Description: Set the auth data to a host(such as aaa.wilddogio.com).
 * Input:       p_host: a pointer to host .
 *              p_auth: the auth data
 *              onAuth: the callback function called when the server returns 
 *                      a response or send fail.
 *              args: the arg defined by user, if you do not need, can be NULL.
 * Output:      N/A
 * Return:      0 means succeed, negative number means failed.
*/
int Wilddog::auth(const char *p_auth,const char *p_host,CallBackFunc onAuth,void *arg)
{
    if(wilddog_index)
        return _wd_connect.connect_send(_CMD_AUTH,p_auth,p_host,onAuth,arg);  
    else
        return -1;
}
