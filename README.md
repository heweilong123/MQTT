# MQTT
 8266 MQTT ONENETTT


## 8266
**连接ONENET** 
AT+RST  
AT+CWMODE=3  //STA  
AT+CWLAP  
AT+CWJAP="1234","heweilong"  
AT+CIPSTA?  
AT+CIPMUX=0  
AT+CIPSTART="TCP","183.230.40.39",6002  
AT+CIPMODE=1  
AT+CIPSEND  //开始传输  
+++ //（除了这个指令不带回车，其他的都要带） 

## MQTT
MQTT文档  
https://mcxiaoke.gitbooks.io/mqtt-cn/content/mqtt/01-Introduction.html  

ONENET控制台  
开发者中心 ->全部产品服务 ->多协议接入  


客户端ID    （设备ID）  589493534   
用户名	    （产品ID）  330283  
密码	    （鉴权信息）123456  

CONNECT  
10 剩余长度 00 04 M Q T T 协议级别(04) 连接标志(C2) 保持连接(秒为单位 00 78) 长度(00 09) 客户端ID 长度(00 06) 用户名 长度(00 06) 密码

连接标志(C2) 
清理会话 Clean Session(BIT1)
如果 Clean Session=0，启用持久会话。
代理服务器会记录客户端的订阅信息，并保存未接收的消息。如果客户端断开连接，代理服务器会保留所有相关的信息，直到下次客户端连接时恢复。
如果 Clean Session=1，启用清除会话。
代理服务器不会记录客户端的订阅信息和未接收的消息。当客户端断开连接时，代理服务器会立即删除与该客户端相关的所有信息。
遗嘱标志 Will Flag(BIT2)
Will Flag=1，如果异常断连,所有订阅了的客户端都会收到遗嘱
遗嘱QoS(BIT4BIT3)
XXX
遗嘱保留(BIT5)
XXX
密码标志(BIT6)
=1 有效载荷中必须包含密码字段
用户名标志(BIT7)
=1 有效载荷中必须包含用户名字段

有效载荷（保持连接之后）
必须按这个顺序出现：客户端标识符，遗嘱主题，遗嘱消息，用户名，密码

10 25 00 04 4D 51 54 54 04 C2 00 78 00 09 35 38 39 34 39 33 35 33 34 00 06 33 33 30 32 38 33 00 06 31 32 33 34 35 36

订阅   
82 0A 00 0A 00 05 74 6F 70 69 63 01

发送  
使用的是API调试  
API使用文档  https://open.iot.10086.cn/doc/v5/develop/detail/607  
url APIKEY  
URL参数 参数=topic  参数值=订阅的主题名字    
HTTP请求参数  发送的信息

## 发送测试需要用到的内容
连接 
10 25 00 04 4D 51 54 54 04 C2 00 78 00 09 35 38 39 34 39 33 35 33 34 00 06 33 33 30 32 38 33 00 06 31 32 33 34 35 36 

发送 qos2
34 14 00 05 74 6F 70 69 63 00 01 74 6F 70 69 63 20 68 65 6C 6C 6F 
62 02 00 01 

qos1
32 14 00 05 74 6F 70 69 63 00 01 74 6F 70 69 63 20 68 65 6C 6C 6F 

## demo6

8266 连接onenet MQTT 订阅 收到“test” 主题的数据后 取消订阅

## demo7

收到“test” 主题的数据后  通过“topic“发布


发布信息
QOS0 （快速发送）
send -发布信息-> rec
QOS1 （需要自己去重）
send -发布信息-> rec
rec  -发布收到-> send
QOS1 （肯定收到）
send -发布信息-> rec
rec  -发布收到-> send
send -发布释放-> rec
rec  -发布完成-> send


