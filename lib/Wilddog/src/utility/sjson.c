
#include <stdio.h>

#define _ISDIGIT_(a)    ((a) !=NULL && \
                            ((a)>='0' && (a)<= '9'))

#if 0
/***
*long atol(char *nptr) - Convert string to long
*
*Purpose:
*       Converts ASCII string pointed to by nptr to binary.
*       Overflow is not detected.
*
*Entry:
*       nptr = ptr to string to convert
*
*Exit:
*       return long int value of the string
*
*Exceptions:
*       None - overflow is not detected.
*
*******************************************************************************/
long  s_atol(
        const char *nptr
        )
{
        int c;              /* current char */
        long total;         /* current total */
        int sign;           /* if '-', then negative, otherwise positive */

        /* skip whitespace */
        while ( isspace((int)(unsigned char)*nptr) )
            ++nptr;

        c = (int)(unsigned char)*nptr++;
        sign = c;           /* save sign indication */
        if (c == '-' || c == '+')
            c = (int)(unsigned char)*nptr++;    /* skip sign */

        total = 0;

        while (isdigit(c)) {
            total = 10 * total + (c - '0');     /* accumulate digit */
            c = (int)(unsigned char)*nptr++;    /* get next char */
        }

        if (sign == '-')
            return -total;
        else
            return total;   /* return result, negated if necessary */
}
#endif
char* strstr(const char *s1,const char *s2)
{
    const char *p=s1;
    const size_t len=strlen(s2);
    for(;(p=strchr(p,*s2))!=0;p++)
    {
        if(strncmp(p,s2,len)==0)
            return  (char*)p;
    }
    
    return(NULL);
}

static const char *skip_space(const char *str)
{
    while(*str == ' ' || *str == '\t')
    {
        str++;
    }
    return str;
}
long int atoll(const char *str)  
{  
    long int  i,n,sign;  
    char *p = NULL;
    if(str== NULL)
        return 0;
    
    p = skip_space(str); 
    
    if(p== NULL)
        return 0;
    
    sign=(*p == '-')?-1:1;  
    if(*p=='+'||*p==' -')       
        p++;  
    for(n=0;_ISDIGIT_(*p);p++)  
        n=10*n+(*p-'0');          
        
    return sign*n; 

}


/*
* Function:    sjson_get_value
* Description: get json value
* Input:      input :json ; name: item's key ; maxlen : input buf sizeof
* Output:     output : value  ;
*                 *maxlen :  value's len
* Return:     value's len
*/
int sjson_get_value(const char *input, const char *name,
                        char *output, int *maxlen)
{
    const char *p_name = strstr(input, name);
    const char *p;
   // const char tmp = ':';
    char start = 0,end = 0,subItem = 0;
    int i;
    int len;
    
    if(p_name == NULL)
        goto err1;
    
    end = '\"';
    p = skip_space(p_name);
    if( strncmp(p,":\"",sizeof(":\"")) == 0)
    {
        p += 2;
    }
    else
    {
        
        while( *p!=':' && p!= NULL)
            p++;

        if(p == NULL)
            goto err1;
        
        p += 1;
        p = skip_space(p);
        if(*p == '{')
        {
            start = '{';
            end = '}';
        }
        else
        if(*p == '\"')
        {
            p += 1;
            start = '\"';
            end = '\"';
        }
        else
        if(*p == '[')
        {
            start = '\[';
            end = ']';
        }
        else
        {
            start = 0;
            end = ',';
        }
        subItem = 0;
    }

    memset(output, 0, *maxlen);
    len = 0;
    for(i = 0; i < *maxlen; i++)
    {
        while(*p == '\\')
        {
            p++;
        }
        subItem = (*p == start)?(subItem+1):subItem;
        if(*p == end)
        {
            if(end == '}')
            {
                if(subItem == 0)
                    break;
                else
                    subItem--;
                output[i] = *p;
            }
            else
            {
                break;
            }
        }
        
        output[i] = *p;
        p++;
        len++;
    }
    *maxlen = len;
    return len;
err1:
    return -1;
}
/*
* Function:    sjson_fillSlash
* Description: fill slash in json
* Input:      input :json ;  
* Output:     dst :   ;
*                 *dstLen :  value's len
* Return:     dst's len
*/
int sjson_fillSlash(const char *src,char *dst,int *dstLen)
{
	char *p_src = src;
	int i;
	if(src == NULL || dst == NULL)
		return 0;

	for(i=0;*p_src != '\0';p_src++)
	{
		if(*p_src == '"'||  *p_src == '\\')
		{
			if(i> *dstLen)
				goto _FILLSLASH_END;
			dst[i] = '\\';
			i++;
		}	
		if(i> *dstLen)
			goto _FILLSLASH_END;
		dst[i] = *p_src;
		i++;
		
	}
	
_FILLSLASH_END:
	*dstLen = i;
	return i;
	
}
/* 
*	count the number of sepecial character.
*/
int sjson_countSecialCharacter(const char *src)
{
	int cnt = 0,i;
	char *p = src;

    if(src == NULL)
        return 0;
    
	for(;*p != '\0';p++)
	{
	
		if(*p == '"'||  *p== '\\')
			cnt++;
	}

	return cnt;
}


