# STM32_ESP822_BLBLAPI
#Readme

##硬件接线：##

### ESP8266   串口使用串口1 PA9  10
### PC通信	串口使用串口3 PB10  11 
### key1 	  PB0
###长按进行更改WiFi设置，大约3s

## PC 指令
+ ###1更新WiFi
> ssid+ssid+:+password+;	
例：wifi名pitest 密码123456789
	ssidpitest:123456789;
+ ###2更新BilibiliAPI信息
> UID+个人UID 例: UID123456
BV+BV号     例：BV1234567 

` (指令不区分大小写) 例：UID123456与uid123456相同 `

# 注意：PC指令必须加回车换行(/r/n 0D0A)，串口助手勾选增加回车
