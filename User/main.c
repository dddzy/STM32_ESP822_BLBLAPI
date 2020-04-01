/**
  ******************************************************************************
  * @file    main.c
  * @author  dzy
  * @version V1.0.0
  * @date    2020-3-29
  * @brief   main function.
  ******************************************************************************
  * @attention
  *
	*		There is no
  * 
  ******************************************************************************
* */

/* Includes ------------------------------------------------------------------*/

#include "../allincludes.h"


/* Define ------------------------------------------------------------------*/

u8 ESP8266_SendTime = 0;
/**  Main_Functions		*/



/** @defgroup int main(void)
  * @{
  */

/**
  * @brief  主函数        
  * @param  none
	* @return none
  * @retval none
  */
int main(void)
{
	uint8_t flash = 0;
	uint8_t show = 0;
	uint8_t get = 0;
	char Get_WifiSet[20];
	NVIC_PriorityGroupConfig(2);
	LED_Init();
	delay_init();
	OLED_Init();
	uart_init(115200);
	usart3_init(36,115200);
	SystemTimeInit();
	KEY_Init();
	USART1_GetNum = 99;
	W25QXX_Init();																//W25QXX初始化
	while(W25QXX_ReadID()!=W25Q128)								//检测不到W25Q128
	{
		OLED_Show((_OLED){64,2,2},"W25Q128 Check !");
	}
	wifi_Init();
	W25QXX_Read((u8*)Get_WifiSet,0,14);   //读取flash
	if(0!=strcmp(Get_WifiSet,Wifi_SetOK))
	{
		AT_RST(1);
		While_Setwifi();
	}
	else
	{
		OLED_CLS();
		OLED_Show((_OLED){16,2,2},"Waiting for WiFi link");
		while(1)
		{
			if(AT_Return("GOT")) {OLED_Show((_OLED){88,6,2},"TRUE ");break;}
			else{OLED_Show((_OLED){88,6,2},"FALSE");}
			if(KEY_Scan(1)==1)
			{
				if(get_key()) break;
			
			}//if(KEY_Scan(1)==1)
			if(systemtime.msec1000flag == 1)//1s
			{
				systemtime.msec1000flag = 0;
				get_pc();
				ESP8266_SendTime++;
				PBout(12) = flash;
				flash=!flash;
				if(ESP8266_SendTime==10) 
				{
					AT_RST(1);
					ESP8266_SendTime = 0;
				}
			}
		}
	}
	BlblConnect();
	
	//ImgInit();
	BLBL.get = 0x01;
	ESP8266_SendTime = 5;
	while(1)
	{		
  		
		Other_tasks();
		if(systemtime.msec1000flag == 1) 
		 {
				systemtime.msec1000flag = 0;	
			 	get_wifi();
				PBout(12) = flash;
			 
				flash=!flash;
				ESP8266_SendTime++;
		                                                                         
				if(ESP8266_SendTime>=5)
				{
					switch(BLBL.get)
					{
						case 0x01:if(0x00==show){show=0x01;ImgInit();}if(0==get){ESP8266_AT("GET /%s=%s HTTP/1.1\nHost:api.bilibili.com\n\n",\
											BLBL.api.fans,BLBL.uid);if(BLBL.value.view[0]=='\0'){get=1;}else {ESP8266_SendTime=0;}}
											else{ESP8266_AT("GET /%s=%s HTTP/1.1\nHost:api.bilibili.com\n\n",\
											BLBL.api.view,BLBL.uid);get=0;ESP8266_SendTime=0;}
											break;
						case 0x02:if(0x01==show){show=0x00;ImgInit();}break;
						default:break;
					}//switch(BLBL.get)
				}//if(ESP8266_SendTime>=5)
			}		

	}//while(1)
}//main

