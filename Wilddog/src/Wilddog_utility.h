/*
  Wilddog_manage.h - Library for flashing Platform_ArduinoYun code.
  Created by Sky.Li, October 27, 2015.
  Released into the public domain.
*/


#ifndef WILDDOG_MANAGE_H
#define WILDDOG_MANAGE_H

#ifdef __cplusplus     
extern "C" {          
#endif
extern int sjson_get_value(const char *input, const char *name,
                        char *output, int *maxlen);  
extern int sjson_countSecialCharacter(const char *src);
extern int sjson_fillSlash(const char *src,char *dst,int *dstLen);

#ifdef __cplusplus
	}
#endif


#endif

