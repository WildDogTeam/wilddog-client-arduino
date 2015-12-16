/*
  Wilddog_manage.cpp - Library for flashing Wilddog_manage code.
  Created by Sky.Li, October 27, 2015.
  Released into the public domain.
*/

#include <stdio.h>
#include "../Wilddog_type.h"

#include "Wilddog_manage.h"
#include "utlist.h"

#define _BIN_WATCH	"wilddog_watch"

#define _BIN_DAEMON "wilddogd"


#define _JSON_CMD_          ".cmd"
#define _JSON_INDEX_        ".index"
#define _JSON_PORT_         ".port"

#define _JSON_DATA_         ".data"
#define _JSON_ERRORCODE_    ".error"
#define _JSON_EVENTTYPE_    ".eventType"
#define _JSON_HOST_         ".host"

static Transfer_Node_T *p_head = NULL;

 
extern int sjson_get_value(const char *input, const char *name,
                        char *output, int *maxlen);
extern  int sjson_fillSlash(const char *src,char *dst,int *dstLen);
extern long int atoll(const char *str);


Transfer_Node_T* manage_appendNode(Daemon_cmd_T cmd,unsigned long index,CallBackFunc f_callback,void *arg)
{
	Transfer_Node_T *newNode = (Transfer_Node_T*)malloc(sizeof(Transfer_Node_T));
	if(newNode == 0)
		return NULL;
	
	memset(newNode,0,sizeof(Transfer_Node_T));
	newNode->cmd = cmd;
	newNode->index = index;
	newNode->arg = arg;
	newNode->f_callback = f_callback;
        
	LL_APPEND(p_head,newNode);
	return newNode;
}
void manage_deleteNode(Transfer_Node_T** pp_dele)
{
    
	if(*pp_dele)
    {
        LL_DELETE(p_head,*pp_dele);
		free(*pp_dele);
    }   
	
	*pp_dele = NULL;
}
void manage_destoryList(void)
{
	Transfer_Node_T *curr = NULL,*tmp = NULL;
    
	if(p_head == NULL)
		return ;
	
	LL_FOREACH_SAFE(p_head,curr,tmp)
	{
		manage_deleteNode(&curr);
	}
}
Transfer_Node_T *manage_searchNode(Daemon_cmd_T cmd,unsigned long index)
{
	Transfer_Node_T *find = NULL,*curr = NULL,*tmp = NULL;
    //printf("p_head = %p \n",p_head);
	if(p_head == NULL)
		return NULL;
	
	LL_FOREACH_SAFE(p_head,curr,tmp)
    {
        if( curr->index == index &&
            curr->cmd == cmd)
        {
            find = curr;
            break;
        }
        
       // printf("curr = %p \n",curr);
            
    }   
    return find;
}
/* return packet len .*/
int manage_getSendPacket
    (   char *dst,int *dstLen,Daemon_cmd_T cmd,unsigned long index,
        Wilddog_EventType_T event,const char *p_data,const char *p_host,
        unsigned long port)
{
    
    memset(dst,0,*dstLen);
    *dstLen = 0;

    if( dst == 0 )
        return -1;
    
	switch(cmd)
    {
    
        case _CMD_INIT: 
            sprintf(dst,"%s  \"{\"%s\":\"%d\"}\"",_BIN_WATCH,_JSON_CMD_,cmd);
            break;
            
        case _CMD_INIT_WILDDOG:
            if( p_data == 0)
                return -1;
            sprintf(dst,"%s \"{\"%s\":\"%ld\",\"%s\":\"%d\",\"%s\":\"%s\"}\"",\
                _BIN_WATCH,_JSON_PORT_,port,_JSON_CMD_,cmd,_JSON_DATA_,p_data);           
            break;
            
        case _CMD_GET:
            sprintf(dst,"%s \"{\"%s\":\"%ld\",\"%s\":\"%d\",\"%s\":\"%ld\"}\"",\
                _BIN_WATCH,_JSON_PORT_,port,_JSON_CMD_,cmd,_JSON_INDEX_,index);            
            break;
            
        case _CMD_SET:
            if( p_data == 0)
                return -1;
            sprintf(dst,"%s \"{\"%s\":\"%ld\",\"%s\":\"%d\",\"%s\":\"%ld\","
            "\"%s\":%s}\"",_BIN_WATCH,_JSON_PORT_,port,_JSON_CMD_,cmd,_JSON_INDEX_,\
            index,_JSON_DATA_,p_data);    
            break;
            
        case _CMD_PUSH:
            if(p_data == 0)
                return -1;
            sprintf(dst,"%s \"{\"%s\":\"%ld\",\"%s\":\"%d\","
                "\"%s\":\"%ld\",\"%s\":%s}\"",\
                _BIN_WATCH,_JSON_PORT_,port,_JSON_CMD_,cmd,_JSON_INDEX_,index,\
                _JSON_DATA_,p_data);
            
            break;
        case _CMD_REMOVE:
             sprintf(dst,"%s \"{\"%s\":\"%ld\",\"%s\":\"%d\",\
                \"%s\":\"%ld\"}\"",_BIN_WATCH,_JSON_PORT_,port,_JSON_CMD_,cmd,\
                _JSON_INDEX_,index);            
            break;
       case _CMD_ON:
            sprintf(dst,"%s \"{\"%s\":\"%ld\",\"%s\":\"%d\",\"%s\":\"%ld\","
                "\"%s\":\"%d\"}\"",
                _BIN_WATCH,_JSON_PORT_,port,_JSON_CMD_,cmd,_JSON_INDEX_,index,\
                _JSON_EVENTTYPE_,event);            
            break;
       case _CMD_OFF:
            sprintf(dst,"%s \"{\"%s\":\"%ld\",\"%s\":\"%d\","
                "\"%s\":\"%ld\",\"%s\":\"%d\"}\"",
                _BIN_WATCH,_JSON_PORT_,port,_JSON_CMD_,cmd,_JSON_INDEX_,index,\
                _JSON_EVENTTYPE_,event);            
            break;
       case _CMD_AUTH:
             if(p_host == 0 || p_data == 0)
                return -1;
             sprintf(dst,"%s \"{\"%s\":\"%ld\",\"%s\":\"%d\","
                "\"%s\":\"%ld\",\"%s\":\"%s\",\"%s\":\"%s\"}\"",\
                _BIN_WATCH,_JSON_PORT_,port,_JSON_CMD_,cmd,_JSON_INDEX_,index,\
                _JSON_HOST_,p_host,_JSON_DATA_,p_data);            
            break;
       case _CMD_DESTORY_WILDDOG:
            sprintf(dst,"%s \"{\"%s\":\"%ld\",\"%s\":\"%d\",\"%s\":\"%ld\"}\"",\
                _BIN_WATCH,_JSON_PORT_,port,_JSON_CMD_,cmd,_JSON_INDEX_,index);            
            break;
       case _CMD_DESTORY:
            sprintf(dst,"%s \"{\"%s\":\"%ld\",\"%s\":\"%d\",\"%s\":\"%ld\"}\"",\
                _BIN_WATCH,_JSON_PORT_,port,_JSON_CMD_,cmd,_JSON_INDEX_,index);
            break;

       case _CMD_NOTIFY:
                sprintf(dst,"%s \"{\"%s\":\"%ld\",\"%s\":\"%d\",\"%s\":\"%ld\"}\"",\
                 _BIN_WATCH,_JSON_PORT_,port,_JSON_CMD_,_CMD_NOTIFY,_JSON_INDEX_,index);
                break;

           default :

                
                return 0;
    }   
   *dstLen = strlen(dst);

   return *dstLen;
}

#if 0
int manage_getSendPacket(char *dst,int *dstLen,Daemon_cmd_T cmd,unsigned long index,
                        Wilddog_EventType_T event,const char *p_data,const char *p_host)
{
    
    char *fillSlashBuffer = NULL;
    memset(dst,0,*dstLen);
    *dstLen = 0;

    if( dst == 0 )
        return -1;
    
    if( p_data != 0 )
    {
        int bufferLen = 2*strlen(p_data)+2;
        fillSlashBuffer = malloc(bufferLen);
        if(fillSlashBuffer == NULL)
            return -1;

        memset(fillSlashBuffer,0,bufferLen);
        sjson_fillSlash( p_data,fillSlashBuffer,&bufferLen);
    }
	switch(cmd)
    {
    
        case _CMD_INIT: 
            //sprintf(dst,"%s  \"{\\\".cmd\\\":\\\"%d\\\"}\"",_BIN_WATCH,cmd);
            sprintf(dst,"%s ",_BIN_DAEMON);
            break;
            
        case _CMD_INIT_WILDDOG:
            if( fillSlashBuffer == 0)
                return -1;
            sprintf(dst,"%s \"{\\\"%s\\\":\\\"%d\\\",\\\"%s\\\":\\\"%s\\\"}\"",\
                _BIN_WATCH,_JSON_CMD_,cmd,_JSON_DATA_,fillSlashBuffer);           
            break;
            
        case _CMD_GET:
            sprintf(dst,"%s \"{\\\"%s\\\":\\\"%d\",\\\"%s\":\\\"%ld\\\"}\"",\
                _BIN_WATCH,_JSON_CMD_,cmd,_JSON_INDEX_,index);            
            break;
            
        case _CMD_SET:
            if( fillSlashBuffer == 0)
                return -1;
            sprintf(dst,"%s \"{\\\"%s\\\":\\\"%d\\\",\\\"%s\\\":\\\"%ld\\\""
            ",\\\"%s\\\":%s}\"",_BIN_WATCH,_JSON_CMD_,cmd,_JSON_INDEX_,index,_JSON_DATA_,fillSlashBuffer);    
            break;
            
        case _CMD_PUSH:
            if(fillSlashBuffer == 0)
                return -1;
            sprintf(dst,"%s \"{\\\"%s\\\":\\\"%d\\\""
                ",\\\"%s\\\":\\\"%ld\\\",\\\"%s\\\":%s}\"",\
                _BIN_WATCH,_JSON_CMD_,cmd,_JSON_INDEX_,index,_JSON_DATA_,fillSlashBuffer);
            
            break;
        case _CMD_REMOVE:
             sprintf(dst,"%s \"{\\\"%s\\\":\\\"%d\\\",\
                \\\"%s\\\":\\\"%ld\\\"}\"",_BIN_WATCH,_JSON_CMD_,cmd,_JSON_INDEX_,index);            
            break;
       case _CMD_ON:
            sprintf(dst,"%s \"{\\\"%s\\\":\\\"%d\\\",\\\"%s\\\":\\\"%ld\\\","
                "\\\"%s\\\":\\\"%d\\\"}\"",
                _BIN_WATCH,_JSON_CMD_,cmd,_JSON_INDEX_,index,_JSON_EVENTTYPE_,event);            
            break;
       case _CMD_OFF:
            sprintf(dst,"%s \"{\\\"%s\\\":\\\"%d\\\","
                "\\\"%s\\\":\\\"%ld\\\",\\\"%s\\\":\\\"%d\\\"}\"",
                _BIN_WATCH,_JSON_CMD_,cmd,_JSON_INDEX_,index,_JSON_EVENTTYPE_,event);            
            break;
       case _CMD_AUTH:
             if(p_host == 0 || fillSlashBuffer == 0)
                return -1;
             sprintf(dst,"%s \"{\\\"%s\\\":\\\"%d\\\","
                "\\\"%s\\\":\\\"%ld\\\",\\\"%s\\\":\\\"%s\\\",\\\"%s\\\":\\\"%s\\\"}\"",\
                _BIN_WATCH,_JSON_CMD_,cmd,_JSON_INDEX_,index,_JSON_HOST_,p_host,_JSON_DATA_,fillSlashBuffer);            
            break;
       case _CMD_DESTORY_WILDDOG:
            sprintf(dst,"%s \"{\\\"%s\\\":\\\"%d\\\",\\\"%s\\\":\\\"%ld\\\"}\"",\
                _BIN_WATCH,_JSON_CMD_,cmd,_JSON_INDEX_,index);            
            break;
       case _CMD_DESTORY:
            sprintf(dst,"%s \"{\\\"%s\\\":\\\"%d\\\",\\\"%s\\\":\\\"%ld\\\"}\"",\
                _BIN_WATCH,_JSON_CMD_,cmd,_JSON_INDEX_,index);
            break;

       case _CMD_NOTIFY:
                sprintf(dst,"%s \"{\\\"%s\\\":\\\"%d\\\",\\\"%s\\\":\\\"%ld\\\"}\"",
                 _BIN_WATCH,_JSON_CMD_,_CMD_NOTIFY,_JSON_INDEX_,index);
                break;

           default :
                if(fillSlashBuffer)
                    free(fillSlashBuffer);
                
                return 0;
    }   

    if(fillSlashBuffer)
        free(fillSlashBuffer);
    
   *dstLen = strlen(dst);

   return *dstLen;
}
#endif
/* return cmd .*/
int manage_handleReceive(   const char *recv,unsigned long *p_index,
                                    int *p_error,unsigned long *port)
{

    int len = strlen(recv)+1,res =0;
    int cmd = -1;
    char *p_buf = (char*)malloc( len);
    Transfer_Node_T *respond_node = NULL;
    
    if( recv == NULL || p_buf == NULL || strlen(recv) == 0)
        return -1;

    len = strlen(recv)+1;
    memset(p_buf,0,strlen(recv)+1);
    if((res = sjson_get_value(recv,_JSON_CMD_,p_buf,&len)) < 0)
        goto _HANDLE_RECV_ERROR;
    cmd = atoi(p_buf);
    
    len = strlen(recv)+1;
    memset(p_buf,0,strlen(recv)+1);
    if((res = sjson_get_value(recv,_JSON_ERRORCODE_,p_buf,&len)) < 0)
        goto _HANDLE_RECV_ERROR;
    
    *p_error = atoi(p_buf);

    /* get index*/
    if ( cmd != _CMD_INIT && 
         cmd != _CMD_DESTORY )
        {
        
        len = strlen(recv)+1;
        memset(p_buf,0,strlen(recv)+1);
        if((res = sjson_get_value(recv,_JSON_INDEX_,p_buf,&len)) < 0)
            goto _HANDLE_RECV_ERROR;

        *p_index = atoll(p_buf);
    }
    
    switch(cmd)
    {
        case _CMD_INIT:
            /* get port */
              len = strlen(recv)+1;
              memset(p_buf,0,strlen(recv)+1);
              
              if((res = sjson_get_value(recv,_JSON_PORT_,p_buf,&len)) < 0)
                  goto _HANDLE_RECV_ERROR;
              *port = atoll(p_buf);
              break;

            
       case _CMD_DESTORY:
            break;
            
        case _CMD_INIT_WILDDOG:
            /* get index*/
            len = strlen(recv)+1;
            memset(p_buf,0,strlen(recv)+1);
            
            if((res = sjson_get_value(recv,_JSON_INDEX_,p_buf,&len)) < 0)
                goto _HANDLE_RECV_ERROR;
            *p_index = atoll(p_buf);
            break;
        case _CMD_DESTORY_WILDDOG:
            break;
            
        default:
             /* get index*/
            len = strlen(recv)+1;
            memset(p_buf,0,strlen(recv)+1);
            
            if((res = sjson_get_value(recv,_JSON_INDEX_,p_buf,&len)) < 0)
                goto _HANDLE_RECV_ERROR;
            *p_index = atoll(p_buf);
            
            /* search node .*/
           respond_node = manage_searchNode(cmd,*p_index);
           if(respond_node == NULL)  
               goto _HANDLE_RECV_ERROR;
           
           /* get paylaod,may be empty.*/
           len = strlen(recv)+1;
           memset(p_buf,0,strlen(recv)+1);
           res = sjson_get_value(recv,_JSON_DATA_,p_buf,&len);
           
           if(respond_node->f_callback)
              respond_node->f_callback(p_buf,*p_error,respond_node->arg);
    
            /* change to notify */
            if(respond_node->cmd == _CMD_ON)
            {
               respond_node->d_notifyFlag = 1;
            }
            else
                 /* destory node */
              manage_deleteNode(&respond_node);

            break;
    
    }
    if(p_buf)
        free(p_buf); 
    return cmd;
    
_HANDLE_RECV_ERROR:

    free(p_buf);
    return res;
    
}

