/*
  Wilddog_manage.h - Library for flashing Connect code.
  Created by Sky.Li, October 27, 2015.
  Released into the public domain.
*/


#ifndef WILDDOG_MANAGE_H
#define WILDDOG_MANAGE_H

 
#include "../Wilddog_type.h"

#ifdef __cplusplus     
extern "C" {          
#endif

typedef void (*CallBackFunc)(const char *pdata, int error, void* arg);

	
typedef struct TRANSFER_NODE_T
{
	struct TRANSFER_NODE_T *next;
	
	unsigned long index;
	Daemon_cmd_T cmd;
	CallBackFunc f_callback;
	void *arg;

    unsigned char d_notifyFlag;

}Transfer_Node_T;

int manage_getSendPacket
    (   char *dst,int *dstLen,Daemon_cmd_T cmd,unsigned long index,
        Wilddog_EventType_T event,const char *p_data,const char *p_host,
        unsigned long port);

Transfer_Node_T* manage_appendNode(Daemon_cmd_T cmd,unsigned long index,CallBackFunc f_callback,void *arg);

void manage_deleteNode(Transfer_Node_T** pp_dele);
void manage_destoryList(void);
Transfer_Node_T *manage_searchNode(Daemon_cmd_T cmd,unsigned long index);

int manage_handleReceive(   const char *recv,unsigned long *p_index,
                                    int *p_error,unsigned long *port);

#ifdef __cplusplus
	}
#endif


#endif

