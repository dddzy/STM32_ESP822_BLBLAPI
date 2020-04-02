# STM32_ESP822_BLBLAPI
# Readme

## 硬件接线：

### ESP8266   串口使用串口1 PA9  10  
### PC通信	串口使用串口3 PB10  11   
### key1 	  PB0  
### 长按进行更改WiFi设置，大约3s  

## PC 指令  
+ ### 1更新WiFi  
> ssid+"你的WiFi名"+:+"密码"+;   
> 例：wifi名pitest 密码123456789    
> 则发送指令为：ssidpitest:123456789;  
+ ### 2更新BilibiliAPI信息  
> UID+个人UID 例: UID123456  
> BV+BV号     例：BV1234567   

` (指令不区分大小写) 例：UID123456与uid123456相同 `  
![哔哩哔哩](https://pandao.github.io/editor.md/images/logos/editormd-logo-180x180.png "Pandao editor.md")

# 注意：PC指令必须加回车换行(/r/n 0D0A)，串口助手勾选增加回车  
[![](https://timgsa.baidu.com/timg?image&quality=80&size=b9999_10000&sec=1585807501073&di=efd94251c7fc15dd70f29d9edfa492d4&imgtype=0&src=http%3A%2F%2Fi0.hdslb.com%2Fbfs%2Farticle%2F8cafbabe0c6e61b476595fd31cd6b729a7bcd79e.png)](https://www.bilibili.com/video/BV1Sg4y1b7rf "哔哩哔哩")

