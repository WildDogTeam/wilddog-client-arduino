/*
Title: API�ĵ�
Sort: 3
*/


# Wilddog (*Methods*)

## new Wilddog

###### ����

new Wilddog(wilddogUrl)

###### ˵��

 ��ʼ��URL��Ӧ�Ľڵ�ʵ����

###### ����

* wilddogUrl `string` : Ӧ��URL���磺https://<appId>.wilddogio.com

###### ����ֵ

 Wilddog ��������á�

###### ʾ��
```c
ref = new Wilddog("https://<appId>.wilddogio.com/a/b/c");
```

----

## getValue()

###### ����

int getValue(CallBackFunc f\_callback,void \*arg)

###### ˵��

��ȡWilddog��������Ӧ�Ľڵ��ֵ��

###### ����

* f_callback `CallBackFunc` : ����˻�Ӧ���ݻ��߻�Ӧ��ʱ�����Ļص�����, ������`void (*CallBackFunc)(const char *pdata, int error, void* arg)`������`pdata`�Ƿ��ص����ݣ�`error`�Ƿ����룬`arg`���û�������Զ��������
* arg `void*` : �û��Զ����������ΪNULL����

###### ����ֵ

 `int` : ���� 0:�ɹ� <0:ʧ�ܣ�ע�⣬����ָ�ĳɹ�ʧ�ܽ�ָ�Ƿ�ɹ����뷢�Ͷ��С�

###### ʾ��
```c
void getValueCallBack(const char *pdata, int error, void* arg)
{
	Serial.print("\n get error : ");
	Serial.print(error);
	if(pdata)
	{
		Serial.print("\n get newest data : ");
		Serial.print(pdata);
    }
	return;
}

Wilddog *ref = NULL;

void setup() {
	
	... // other codes, such as serial init, bridge init
	
	ref = new Wilddog("https://<appId>.wilddogio.com/a/b/c");
	ref->getValue(getValueCallBack,(void*)NULL);
}

void loop(){
	if(ref)
		ref->trySync();
}
```

----

## setValue()

###### ����

int setValue(const char \*p\_data,CallBackFunc f\_callback,void \*arg)
  
###### ˵��

����Wilddog��������Ӧ�Ľڵ��ֵ��

###### ����

* p_data `const char*` : ׼�����õĽڵ��ֵ��json�ַ�����ʽ��
* f_callback `CallBackFunc` : ����˻�Ӧ���ݻ��߻�Ӧ��ʱ�����Ļص�����, ������`void (*CallBackFunc)(const char *pdata, int error, void* arg)`������`pdata`ΪNULL��`error`�Ƿ����룬`arg`���û�������Զ��������
* arg `void*` : �û��Զ����������ΪNULL����

###### ����

 `int` : ���� 0:�ɹ� <0:ʧ�ܣ�ע�⣬����ָ�ĳɹ�ʧ�ܽ�ָ�Ƿ�ɹ����뷢�Ͷ��С�

###### ʾ��
```c
void setValueCallBack(const char *pdata, int error, void* arg)
{
	Serial.print("\n set error : ");
	Serial.print(error);
	if(error >= 200 && error < 400)
	{
	    Serial.print("\n set data success!\n");
	}
	return;
}

Wilddog *ref = NULL;

void setup() {
	
	... // other codes, such as serial init, bridge init
	
	ref = new Wilddog("https://<appId>.wilddogio.com/a/b/c");
	ref->setValue("{\"pin13\":\"1\"}", setValueCallBack,(void*)NULL);
}

void loop(){
	if(ref)
		ref->trySync();
}
```

----

## push()

###### ����

int push(const char \*p\_data,CallBackFunc f\_callback,void \*arg)

###### ˵��

 �ڵ�ǰ�ڵ�������һ���ڵ㣬�ڵ��ֵ�ɴ���Ĳ������������óɹ��󷵻ؽڵ��path���ڵ��key�ɷ�����������ɡ�

###### ����

* p_data `const char*` : �ڵ��ֵ��Ϊjson�ַ�����
* f_callback `CallBackFunc` : ����˻�Ӧ���ݻ��߻�Ӧ��ʱ�����Ļص�����, ������`void (*CallBackFunc)(const char *pdata, int error, void* arg)`������`pdata`Ϊ�����Ľڵ��path��`error`�Ƿ����룬`arg`���û�������Զ��������
* arg `void *` : �û��Զ����������ΪNULL����

###### ����

 `int` : ���� 0:�ɹ� <0:ʧ�ܣ�ע�⣬����ָ�ĳɹ�ʧ�ܽ�ָ�Ƿ�ɹ����뷢�Ͷ��С�

###### ʾ��
```c
void pushValueCallBack(const char *pdata, int error, void* arg)
{
	Serial.print("\n push error : ");
	Serial.print(error);
	if(pdata)
	{
	    Serial.print("\n new data path : ");
	    Serial.print(pdata);
	}
	return;
}

Wilddog *ref = NULL;

void setup() {
	
	... // other codes, such as serial init, bridge init
	
	ref = new Wilddog("https://<appId>.wilddogio.com/a/b/c");
	ref->push("{\"pin13\":\"1\"}", pushValueCallBack,(void*)NULL);
}

void loop(){
	if(ref)
		ref->trySync();
}
```

----

## removeValue()

###### ����

int removeValue(CallBackFunc f\_callback,void \*arg)

###### ˵��

 ɾ����ǰ�ڵ��ֵ��

###### ����

* f_callback `CallBackFunc` : ����˻�Ӧ���ݻ��߻�Ӧ��ʱ�����Ļص�����, ������`void (*CallBackFunc)(const char *pdata, int error, void* arg)`������`pdata`ΪNULL��`error`�Ƿ����룬`arg`���û�������Զ��������
* arg `void*` : �û��Զ����������ΪNULL����

###### ����

 `int` ���� 0:�ɹ� <0:ʧ�ܣ�ע�⣬����ָ�ĳɹ�ʧ�ܽ�ָ�Ƿ�ɹ����뷢�Ͷ��С�

###### ʾ��
```c
void removeCallBack(const char *pdata, int error, void* arg)
{
	Serial.print("\n remove error : ");
	Serial.print(error);
	if(error >= 200 && error < 400)
	{
		Serial.print("\n remove success!\n");
	}
	return;
}

Wilddog *ref = NULL;

void setup() {
	
	... // other codes, such as serial init, bridge init
	
	ref = new Wilddog("https://<appId>.wilddogio.com/a/b/c");
	ref->removeValue(removeCallBack,(void*)NULL);
}

void loop(){
	if(ref)
		ref->trySync();
}
```

----

## addObserver()

###### ����

int addObserver(Wilddog\_EventType\_T event,CallBackFunc f\_callback,void \*arg)

###### ˵��

*�����ڵ��µ�ĳ���¼��������ݱ仯��,�¼������󣬻ص������ᱻ���á�

###### ����

* event `Wilddog_EventType_T` : �¼����ͣ�Ŀǰֻ����Ϊ1����
* f_callback `CallBackFunc` : ����˻�Ӧ���ݻ��߻�Ӧ��ʱ�����Ļص�����, ������`void (*CallBackFunc)(const char *pdata, int error, void* arg)`������`pdata`�Ƿ��ص����ݣ�`error`�Ƿ����룬`arg`���û�������Զ��������
* arg �û��Զ����������ΪNULL����

###### ����

 `int` : ���� 0:�ɹ� <0:ʧ�ܣ�ע�⣬����ָ�ĳɹ�ʧ�ܽ�ָ�Ƿ�ɹ����뷢�Ͷ��С�

###### ʾ��
```c
void addObserverCallBack(const char *pdata, int error, void* arg)
{
	Serial.print("\n observe error : ");
	Serial.print(error);
    if(pdata)
    {
        Serial.print("\n get newest data : ");
        Serial.print(pdata);
    }
	return;
}

Wilddog *ref = NULL;

void setup() {
	
	... // other codes, such as serial init, bridge init
	
	ref = new Wilddog("https://<appId>.wilddogio.com/a/b/c");
	ref->addObserver(WD_ET_VALUECHANGE,addObserverCallBack,(void*)NULL);
}

void loop(){
	if(ref)
		ref->trySync();
}
```

----

## removeObserver()

###### ����

int removeObserver(Wilddog\_EventType\_T event)

###### ˵��

 ȡ�������¼���

###### ����

* event `Wilddog_EventType_T` : �¼����ͣ�Ŀǰֻ����Ϊ1����

###### ����

 `int` : ���� 0:�ɹ� <0:ʧ�ܣ�ע�⣬����ָ�ĳɹ�ʧ�ܽ�ָ�Ƿ�ɹ����뷢�Ͷ��С�

###### ʾ��
```c
int observed = FALSE;

void addObserverCallBack(const char *pdata, int error, void* arg)
{
	Serial.print("\n observe error : ");
	Serial.print(error);
    if(pdata)
    {
        Serial.print("\n get newest data : ");
        Serial.print(pdata);

	    //set var observed to TRUE
	    *(int*)arg = TRUE;
    }
	return;
}

Wilddog *ref = NULL;

void setup() {
	
	... // other codes, such as serial init, bridge init
	
	ref = new Wilddog("https://<appId>.wilddogio.com/a/b/c");
	ref->addObserver(WD_ET_VALUECHANGE,addObserverCallBack,(void*)&observed);
}

void loop(){
	if(ref)
	{
		if(observed == TRUE)
		{
			ref->removeObserver(WD_ET_VALUECHANGE);
		}
		ref->trySync();
	}
}
```

----

## trySync()

###### ����

void trySync()

###### ˵��

ͨ������wilddog_trySync����WildDog�ƶ�ͬ�����ݡ�ÿ�ε��ö��ᴦ�������ƶ˵����ͺ�����ʱ���ط��������ӵ�ά�� ���Լ������û�ע��Ļص�������

###### ����ֵ

 �ޡ�

###### ʾ��

 ������ʾ����

----

# AuthData (*Methods*)

## auth()

###### ����

int auth(const char \*p\_auth,const char \*p\_host,CallBackFunc onAuth,void \*arg)

###### ˵��

 ����auth���ݵ�������������֤��

###### ����

* p_auth `const char*` : auth���ݣ��ַ������͡�
* p_host `const char*` : �ڵ��host����appid.wilddogio.com����
* onAuth `CallBackFunc` : ����˻�Ӧ���ݻ��߻�Ӧ��ʱ�����Ļص�����, ������`void (*CallBackFunc)(const char *pdata, int error, void* arg)`������`pdata`ΪNULL��`error`�Ƿ����룬`arg`���û�������Զ��������
* arg `void*` : �û��Զ����������ΪNULL����

###### ����ֵ

 `int` : ���� 0:�ɹ� <0:ʧ�ܣ�ע�⣬����ָ�ĳɹ�ʧ�ܽ�ָ�Ƿ�ɹ����뷢�Ͷ��С�

###### ʾ��
```c
void authCallBack(const char *pdata, int error, void* arg)
{
	Serial.print("\n auth error : ");
	Serial.print(error);
    if(error >= 200 && error < 400)
    {
        Serial.print("\n auth success!\n");
    }
	return;
}

Wilddog *ref = NULL;

void setup() {
	
	... // other codes, such as serial init, bridge init
	
	ref = new Wilddog("https://<appId>.wilddogio.com/a/b/c");
	ref->auth("token data", "<appId>.wilddogio.com", authCallBack,(void*)NULL);
}

void loop(){
	if(ref)
		ref->trySync();
}
```
