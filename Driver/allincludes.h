/**
  ******************************************************************************
  * @file    allincludes.h
	* @author	 author
  * @version V1.0
  * @date    20xx-xx-xx
  * @brief   简易说明
  ******************************************************************************
  * @attention 注意/备注事项
  *
  *
  ******************************************************************************
  */ 
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _allincludes_H
#define _allincludes_H

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x.h"
#include "delay.h"
#include "led.h"
#include "../oled/OLED_I2C.h"
#include "usart.h"	
#include <string.h>
#include <stdlib.h>
#include "../wifi/wifi.h"
#include "..\systemtime\systemtime.h"
#include <stdarg.h>
#include <ctype.h>
#include "../ADC/adc.h"
#include "../USART3/usart3.h"
#include "../pc/pc.h"
#include "../W25QXX/spi.h"
#include "../W25QXX/w25qxx.h"
#include "../key/key.h"

/* Define  ------------------------------------------------------------------*/



/** @defgroup 模块定义
  * @{
  */
//#define debug 	

#define StartDebug   0
#define StartTest    1
#define Wifi_SetOK 										  "WiFi is set"

#define ESP8266_AT(fmt,arg...)          printf(fmt"\n",##arg)
#define SendWifi(fmt,arg...)            printf(fmt"\n",##arg)
#define Info(fmt,arg...)           			printf("<<-INFO->> "fmt"\n",##arg)
#define Error(fmt,arg...)          			printf("<<-ERROR->> "fmt"\n",##arg)


#define BLBL_API_RX												USART_RX_BUF
#define PC_RX															USART3_RX_BUF
#define ImgInit()													OLED_CLS();\
																					OLED_DrawBMP(0,0,32,4,gImage_fans);\
																					OLED_DrawBMP(0,4,32,8,gImage_view)
														
																						
																					

extern unsigned char gImage_fans[];																				
extern unsigned char gImage_view[];																				
extern unsigned char F16x16[];
																					

extern char ssid[20] ;
extern char passworld[20];
extern 	u8 USART1_GetNum;
extern  u8 ESP8266_SendTime;
/**  allincludes_Exported_Functions ---------------------------------------------------*/


void Other_tasks(void);	
#endif /*__allincludes_H */
