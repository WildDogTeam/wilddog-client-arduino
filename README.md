### 简介
`wilddog-client-arduino` 是一个`arduino`库，通过该库你的`arduino Yun`可以非常轻松的访问和更新云端的数据。目前`wilddog-client-arduino` 仅支持`Arduino Yun`，用户通过Api向`wilddog`云端发送的请求先是通过其内部联网部件（`Ar9331`）转发到云端的，我们的库有两部分，如下：

	.
	├── wilddog
	├── arduinoYun

	`wilddogarduino库，供用户调用的接口及其实现.
	`arduinoYun.tar.gz` 把数据中转到云端的实现.

### 使用步骤
	
####第一步 创建账号和应用

首先[**注册**](https://www.wilddog.com/account/signup)并登录Wilddog账号，进入控制面板。在控制面板中，添加一个新的应用。

你会获得一个独一无二的应用`URL` `https://<appId>.wilddogio.com/`，在同步和存取数据的时候，你的数据将保存在这个`URL`下。

####第二步 安装
分三部分，配置`ArduinoYun`连接网络，通过`ssh`把可执行文件`arduinoYun.tar.gz`上传到`ArduinoYun`内并安装。
#####1、配置网络

默认情况下，`ArduinoYun`作为Ap模式，你需要用电脑或者手机连接你的`ArduinoYun` 其ssid名字的格式为`ArduinoYun-XXXXXXXXXXXX`，
打开浏览器，在地址栏输入`http://arduino.local`或者`192.168.240.1`，按下`Enter`后会看到以下网页。

![](https://raw.githubusercontent.com/skylli/Wilddog_Arduino_Yun/master/Doc/YunWebPassword.png)

登录密码框中输入`arduino`（ArduinoYun默认登录密码为`arduino`），点击`LOG IN`进入以下页面，该页面展示`ArduinoYun`当前的网络信息。

![](https://raw.githubusercontent.com/skylli/Wilddog_Arduino_Yun/master/Doc/YunWebDiagnostic.png)


点击`CONFIGURE`进入配置页面，如下

![](https://raw.githubusercontent.com/skylli/Wilddog_Arduino_Yun/master/Doc/YunWebConfig.png)

在`WIRELESS NAME` 中输入你想要的连接的`wifi`热点名字，`SECURITY` 中选择其加密方式，`PASSWORD`中输入其访问密码，点击`CONFIGURE & RESTART`,`ArduinoYun` 会自动重启并连接你所配置的网络。

![](https://raw.githubusercontent.com/skylli/Wilddog_Arduino_Yun/master/Doc/YunRebooting.png )


	
#####2、获取ArduinoYun的IP

利用`SSH`登录`ArduinoYun`需要获取`ArduinoYun`的`IP`，可以直接登录路由获取，也可以用`Arduino 1.6.6`或者以上版本的`IDE`获取`ArduinoYun`的`IP`。`ArduinoYun`保持上电，打开`Arduino IDE`，选择`工具-->端口`如下图：

![](https://raw.githubusercontent.com/skylli/Wilddog_Arduino_Yun/master/Doc/getIP.png )
	
#####3、SSH登录ArduinoYun

`SecureCRT`自带文件传输工具，这里以`SecureCRT`为例。打开`SecureCRT`，选择`file-->Quick Connect`，在`Hostname`框中输入`ArduinoYun`的`IP`，`name`输入`root`，如下图：

![](https://raw.githubusercontent.com/skylli/Wilddog_Arduino_Yun/master/Doc/SecureCrt_ssh_config.png )


点击`Connect`后弹出下图，输入密码登录`arduino`（默认），进入以下界面说明`SSH`登录成功。

![](https://raw.githubusercontent.com/skylli/Wilddog_Arduino_Yun/master/Doc/SecureCrt_ssh_ok.png )

######4、安装`ArduinoYun_ar9331_Bin`
	
	root@Arduino:~# opkg update
	root@Arduino:~# opkg install lrzsz
	root@Arduino:~# rz	（在弹出的窗口中选择ArduinoYun_ar9331_Bin，点击确定）
	root@Arduino:~# ls
	arduinoYun.tar.gz
	root@Arduino:~# tar zxvf  arduinoYun.tar.gz
	root@Arduino:~# cd arduinoYun
	root@Arduino:~/arduinoYun# opkg install libwilddog_xx.ipk wilddogArduinoYun_xx.ipk
	root@Arduino:~# wilddog_(tab，有以下可执行命令表明安装成功)
	wilddogd      wilddog_watch
		
######5、卸载:
	root@Arduino:~# opkg remove --force-remove libwilddog 
	root@Arduino:~# opkg remove --force-remove wilddogArduinoYun

######6、安装`wilddog`库

	1、把`wilddog` 放置到`C:\Program Files (x86)\Arduino\libraries`路径下.
	2、更新库，打开Arduino IDE，点击`项目-->管理库`，IDE会自动更新库，并在选择框里输入`wilddog`，出现下图说明库安装成功.

![](https://raw.githubusercontent.com/skylli/Wilddog_Arduino_Yun/master/Doc/arduino_ide_updata.png )

	3、我们在`C:\Program Files (x86)\Arduino\libraries\Wilddog\examples\ArduinoYun`下提供了丰富的范例供用户学习和测试。
