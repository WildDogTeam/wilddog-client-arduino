/*
  Wilddog_type.h - Library for flashing Connect code.
  Created by Sky.Li, October 27, 2015.
  Released into the public domain.
*/

#ifndef _WILDDOG_TYPE_H_
#define _WILDDOG_TYPE_H_


typedef enum DAEMON_CMD{
    
    _CMD_INIT_WILDDOG,//
    _CMD_GET,
    _CMD_SET,
    _CMD_PUSH,
    _CMD_REMOVE,
    _CMD_ON,
    _CMD_OFF,//
    _CMD_AUTH,
    
    _CMD_DESTORY_WILDDOG,//
    _CMD_INIT,//
    _CMD_DESTORY,//

    _CMD_NOTIFY,
    _CMD_MAX
    
}Daemon_cmd_T;

typedef enum WILDDOG_EVENTTYPE_T
{
    WD_ET_NULL        = 0x00,
    WD_ET_VALUECHANGE = 0x01,
    WD_ET_CHILDADD    = 0x02,
    WD_ET_CHILDCHANGE = 0x04,
    WD_ET_CHILDREMOVE = 0x08,
    WD_ET_CHILDMOVED  = 0x10,
}Wilddog_EventType_T;


typedef enum WILDDOG_RETURN_T
{
/*****************client inner error*******************/
    WILDDOG_ERR_NOERR = 0,
    WILDDOG_ERR_NULL = -1,
    WILDDOG_ERR_INVALID = -2,
    
    WILDDOG_ERR_SENDERR = -3,
    WILDDOG_ERR_OBSERVEERR =-4,
    WILDDOG_ERR_SOCKETERR = -5,
    WILDDOG_ERR_NOTAUTH = -7,
    WILDDOG_ERR_QUEUEFULL = -8,
    WILDDOG_ERR_MAXRETRAN = -9,
    WILDDOG_ERR_RECVTIMEOUT = -10,
    WILDDOG_ERR_RECVNOMATCH = -11,
    WILDDOG_ERR_CLIENTOFFLINE = -12,
/*****************HTTP return error******************/
    WILDDOG_HTTP_OK = 200,
    WILDDOG_HTTP_CREATED = 201,
    WILDDOG_HTTP_NO_CONTENT = 204,

    WILDDOG_HTTP_NOT_MODIFIED = 304,

    WILDDOG_HTTP_BAD_REQUEST = 400,
    WILDDOG_HTTP_UNAUTHORIZED = 401,
    WILDDOG_HTTP_FORBIDDEN = 403,
    WILDDOG_HTTP_NOT_FOUND = 404,
    WILDDOG_HTTP_METHOD_NOT_ALLOWED = 405,
    WILDDOG_HTTP_NOT_ACCEPTABLE = 406,
    WILDDOG_HTTP_PRECONDITION_FAIL = 412,
    WILDDOG_HTTP_REQ_ENTITY_TOOLARGE = 413,
    WILDDOG_HTTP_UNSUPPORT_MEDIA = 415,

    WILDDOG_HTTP_INTERNAL_SERVER_ERR = 500,
    WILDDOG_HTTP_NOT_IMPLEMENTED = 501,
    WILDDOG_HTTP_BAD_GATEWAY = 502,
    WILDDOG_HTTP_SERVICE_UNAVAILABLE = 503,
    WILDDOG_HTTP_GATEWAY_TIMEOUT = 504,
    WILDDOG_HTTP_PROXY_NOT_SUPPORT = 505
}Wilddog_Return_T;

#endif /* _WILDDOG_TYPE_H_ */
