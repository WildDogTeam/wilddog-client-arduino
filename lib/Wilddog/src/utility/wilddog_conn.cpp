/*
  Connect.cpp - Library for flashing Platform_ArduinoYun code.
  Created by Sky.Li, October 27, 2015.
  Released into the public domain.
*/
#include "Wilddog_conn.h"
#include "Wilddog_manage.h"
#include "../Wilddog_config.h"

						
int Connect::_l_initUrl_num = 0;
unsigned long Connect::_l_port = 0;

void Connect::_print(const char *src)
{
	Serial.print(src);  
	Serial.flush();
}

void Connect::_printArray(const char *src,int len)
{
    Serial.write(src,len);
    Serial.flush();
}
Connect::Connect()
{
}

Connect::~Connect() {
}
/*
*/
long int Connect::_connect_send(Daemon_cmd_T cmd,Wilddog_EventType_T event,unsigned long index,
					const char *src,const char *p_host)
{
	int res,len = 0,src_len = 0; 
	char *p_buf = NULL;
	if(src)
	{
		src_len = strlen((char*)src);
	}
	if(p_host)
	{
		len += strlen((char*)p_host);
	}
	len += 100 + src_len;
	p_buf = (char*)malloc(len);
	if(p_buf == NULL)
		return -1;

	memset(p_buf,0,len);
	/* get send packet..*/
	res = manage_getSendPacket(p_buf,&len,cmd,index,event,src,p_host,_l_port);	

	/** sending out.*/
	if( res > 0 && strlen(p_buf) > 0 )
	{
		_p.asyncSend(p_buf);	
#if 0	
		if(cmd != _CMD_NOTIFY)
		{
			/* DEBUGing....*/
			_print("\n cmd :");
			Serial.print(cmd);
			_print("\n event :");
			Serial.print(event);
			_print("\n index :");
			Serial.print(index);

			if(p_host)
			{
				_print("\n p_host :");
				Serial.print(p_host);
			}
			if(src)
			{
				_print("\n data :");
				Serial.print(src);
			}


			_print("\n src_len  :");
			Serial.print(src_len);
			
			_print("\n malloc len :");
			Serial.print(len);
			_print("\n shell cmd 3 :");
			_printArray(p_buf,strlen(p_buf));
			_print("\n shell cmd len :");
			Serial.print(strlen(p_buf));
		}
#endif
	}
	
	free(p_buf);
	return res;
}
/* return cmd.*/
int Connect::_connect_asyncReceive(Daemon_cmd_T *p_cmd,int *p_error)
{


	char *buffer = NULL;
	int len = 0,receiveLen = 0;

	if( (receiveLen = _p.available()) > 0)
	{
		//_print(" receive data: \n");
		receiveLen +=128;
		buffer = (char*)malloc(receiveLen);
		if(buffer == NULL)
			return 0;

		memset(buffer,0,receiveLen);
		for(len = 0;_p.available() > 0;len++)
		{
		
			if(len  < receiveLen)
			{
				//char c;
				buffer[len]=_p.read();
				//c = buffer[len];
				//Serial.print(c);
 			}
		}
		
		*p_cmd = (Daemon_cmd_T)manage_handleReceive(buffer,&index,p_error,&_l_port);
#if 0		
		_print("\n receive buf : \n");
		_printArray(buffer,strlen(buffer));

		_print(" \n _connect_asyncReceive cmd :\n");
		Serial.print(*p_cmd,DEC);
		_print(" \n _connect_asyncReceive index :\n");
		Serial.print(index,DEC);
		_print(" \n _connect_asyncReceive error :\n");
		Serial.print(*p_error,DEC);
		_print("\tend \n");
#endif		
		if(buffer)
			free(buffer);

		return receiveLen;
	}

	return 0;
}
void Connect::_connect_blockingReceive()
{
	int block_time = 0,error = 0;
	Daemon_cmd_T cmd = _CMD_MAX;

	while(1) 
	{
		//_print("+");

		if( _connect_asyncReceive(&cmd,&error) > 0 )
			break;
		
		delay(1);
		if( block_time++ > WILDDOG_RECEIVE_TIMEOUT)
			break;
	}
}

void Connect::_connect_getRespond(unsigned long wd_index)
{
	_connect_send(_CMD_NOTIFY,(Wilddog_EventType_T)0,wd_index,NULL,NULL);
}

void Connect::trySync()
{


	_connect_blockingReceive();
	_connect_getRespond(index);

}

/* return index.*/
unsigned long Connect::connect_init(const char *url)
{
	int cmd = -1, error = 0;
	long int res = 0;
#if 1	
	if(_l_initUrl_num == 0)
	{
		res = _connect_send(_CMD_INIT,(Wilddog_EventType_T)0,0,NULL,NULL);
		if(res == -1)
			return NULL;
		/* wait and read respond.*/
		while(1)
		{
			_connect_asyncReceive((Daemon_cmd_T*)&cmd,&error);
			if(cmd == _CMD_INIT )
			{
				 if(error < 0 )
				 	return NULL;
				 break;
			}
		}
	}
#endif	
	_l_initUrl_num++;

	res = _connect_send(_CMD_INIT_WILDDOG,(Wilddog_EventType_T)0,0,url,NULL);
	if(res == -1)
		return -1;
	
	while(1)
	{
		_connect_asyncReceive((Daemon_cmd_T*)&cmd,&error);
		if(cmd == _CMD_INIT_WILDDOG )
		{
			if(error < 0 )
				return NULL;
			break;
		}
	}
	/* sdk can't fix retransmit auth request cause receive two diff token.*/
	delay(5500);
	return index;
}
int Connect::connect_deInit(void)
{
	int cmd = -1, error = 0;
	long int  res = 0;
	
	res = _connect_send(_CMD_DESTORY_WILDDOG,(Wilddog_EventType_T)0,index,NULL,NULL);
	if(res <0)
		return -1;
	/*blocking and waitting for respond.*/
	while(1)
	{
		_connect_asyncReceive((Daemon_cmd_T*)&cmd,&error);
		if(cmd == _CMD_DESTORY_WILDDOG )
		{
			if(error < 0 )
				return NULL;
			break;
		}
	}
	_l_initUrl_num--;
	if(_l_initUrl_num == 0)
	{
		
		res = _connect_send(_CMD_DESTORY,(Wilddog_EventType_T)0,index,NULL,NULL);
		if(res < 0 )
			return -1;
		/*blocking and waitting for respond.*/		
		while(1)
		{
			_connect_asyncReceive((Daemon_cmd_T*)&cmd,&error);
			if(cmd == _CMD_DESTORY )
			{
				if(error < 0 )
					return NULL;
				break;
			}
		}
		manage_destoryList();
	
		
	}
	return error;
}
/* only off.*/
int Connect::connect_send(Daemon_cmd_T cmd,Wilddog_EventType_T event)
{
	long int res = 0;

	res = _connect_send(cmd,event,index,NULL,NULL);
	
	return res;
}
int Connect::connect_send(Daemon_cmd_T cmd,CallBackFunc f_callback,void *arg)
{
	long int res = 0;
	res = _connect_send(cmd,(Wilddog_EventType_T)0,index,NULL,NULL);
	if( manage_appendNode(cmd,index,f_callback,arg) == NULL )
		return -1;
	else
		return res;
}
int Connect::connect_send(Daemon_cmd_T cmd,Wilddog_EventType_T event,CallBackFunc f_callback,void *arg)
{
	long int res = 0;
	res = _connect_send(cmd,event,index,NULL,NULL);
	
	if(manage_appendNode(cmd,index,f_callback,arg) == NULL )
	{
		
		return -1;
	
	}
	else
		return res;
}
int Connect::connect_send(Daemon_cmd_T cmd,const char *data,CallBackFunc f_callback,void *arg)
{
	long int res = 0;
	res = _connect_send(cmd,(Wilddog_EventType_T)0,index,data,NULL);
	
	if(manage_appendNode(cmd,index,f_callback,arg) == NULL )
		return -1;
	else
		return res;
}
int Connect::connect_send(Daemon_cmd_T cmd,const char *data,const char *p_host,CallBackFunc f_callback,void *arg)
{
	long int res = 0;
	res = _connect_send(cmd,(Wilddog_EventType_T)0,index,data,p_host);
	
	if(manage_appendNode(cmd,index,f_callback,arg) == NULL )
		return -1;
	else
		return res;
}
