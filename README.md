## 简介
`wilddog-client-arduino` 是 WildDog 在 Arduino 上的实现库，通过该库，Arduino 可以轻松访问和同步云端数据。目前 SDK 仅支持 Arduino Yun，用户向 WildDog 云发送的请求是通过 Arduino Yun 的联网模块 ar9331 转发到云端的，我们的库分为以下两部分：

	├── lib
	├── platform

	`lib`: Arduino IDE 中的库，包含库代码、供用户调用的接口及示例.
	`platform`:不同平台下的实现，在 Arduino Yun 中是守护进程及依赖库的ipk安装文件.

## 使用步骤
	
###第一步 安装

####1、配置Arduino Yun

注意，如果 Arduino Yun 为出厂状态，需要进行配置，可参看 doc 目录下的`ArduinoYun-Configuration.md`，如果之前已经有过配置，可以略过。

####2、安装 Wilddog 库

#####在联网模块中安装守护进程及依赖库

ssh 远程登陆到 Arduino Yun 联网模块，使用 lrzsz 命令搭配 SercureCRT 软件进行 ftp 传输，将platform/ArduinoYun/目录下的 ipk 下载到 Arduino Yun 并安装：

	root@Arduino:~# opkg update
	root@Arduino:~# opkg install lrzsz
	root@Arduino:~# rz	（在弹出的窗口中找到并选择libwilddog_xx.ipk和wilddogArduinoYun_xx.ipk，点击确定）
	root@Arduino:~# chmod +x *.ipk
	root@Arduino:~/arduinoYun# opkg install libwilddog_xx.ipk wilddogArduinoYun_xx.ipk

有以下可执行命令表明安装成功

	wilddogd      wilddog_watch
		
**注**：卸载守护进程及依赖库:

	root@Arduino:~# opkg remove --force-remove libwilddog 
	root@Arduino:~# opkg remove --force-remove wilddogArduinoYun

#####在Arduino IDE中安装Wilddog库

	1、把lib目录下的 Wilddog 文件夹放置到 Arduino IDE 的 libraries 目录下.
	2、更新库，打开 Arduino IDE，点击`项目-->加载库-->管理库`，IDE 会自动更新库，并在选择框里输入 Wilddog，出现下图说明库安装成功.
	
![](./doc/res/arduino_ide_updata.png )

###第二步 创建账号和应用

[**注册**](https://www.wilddog.com/my-account/signup)并登录 WildDog 账号，进入控制面板。在控制面板中，添加一个新的应用。

你会获得一个独一无二的应用`URL` `https://<appId>.wilddogio.com/`，在同步和存取数据的时候，你的数据将保存在这个`URL`下。

###第三步 使用
我们在`libraries\Wilddog\examples`下提供了丰富的范例供用户学习和测试。
