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

connect   
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