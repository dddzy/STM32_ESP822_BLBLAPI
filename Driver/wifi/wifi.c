/**
  ******************************************************************************
  * @file    wifi.h
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
	
/* Includes ------------------------------------------------------------------*/

#include "../allincludes.h"


/* Define to prevent recursive inclusion -------------------------------------*/


_BLBL BLBL =
{
	0x00,
	"6191721",
	"1CE411P7Jh",
	{
		"x/relation/stat?vmid", 			//follower
		"x/space/upstat?mid",				//view
		"x/web-interface/view?bvid" //bv
		
	},
	{
		"follower",
		"view"
	},
	{
		'\0',
		'\0'
	}
};

/** @defgroup void wifi_Init(void)函数声明
  * @{
  */

/**
  * @brief  wifi初始化        
  * @param  none
	* @return 返回值
  * @retval 返回值类型
  */
void wifi_Init(void)
{
	GPIO_InitTypeDef GPIO_InitStr;//GPIO_Init函数 第二参数定义结构体
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);//始能时钟GPIOA
	
	
	GPIO_InitStr.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStr.GPIO_Pin = GPIO_Pin_1;
	GPIO_InitStr.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStr);  //初始化GPIOB
	GPIO_ResetBits(GPIOB,GPIO_Pin_1);	//初始化GPIOB Pin1低电平
	delay_ms(100);
	GPIO_SetBits(GPIOB,GPIO_Pin_1);	
	delay_ms(100);

}


/** @defgroup char* strstri(char * inBuffer, char * inSearchStr)函数声明
  * @{
  */

/**
  * @brief  自定义strstr 不区分大小写对比命令       
  * @param  输入参数说明
	* @return 返回值
  * @retval 返回值类型
  */

char* strstri(char * inBuffer, char * inSearchStr)
{
    char*  currBuffPointer = inBuffer;

    while (*currBuffPointer != 0x00)
    {
        char* compareOne = currBuffPointer;
        char* compareTwo = inSearchStr;
        //统一转换为小写字符
        while (tolower(*compareOne) == tolower(*compareTwo))
        {
            compareOne++;
            compareTwo++;
            if (*compareTwo == 0x00)
            {
                return (char*) currBuffPointer;
            }

        }
        currBuffPointer++; 
    }
    return NULL;
}
/** @defgroup  char * MatchOrder(char *str,char *order)函数声明
  * @{
  */

/**
  * @brief  匹配命令        
  * @param  char *str待必对内容 char *order比对命令
	* @return char *result 对比结果返回 NULL比对失败 !NULL比对成功
  * @retval  char
  */

char * MatchOrder(char *str,char *order)
{
	char *result = NULL;
	result = strstri(str,order);
	return result;
}

u8 find_bilibiliAPI(_OLED oled,char*src,char *order,char value[10])
{
	char *linP = NULL;
	unsigned char linNum = 0;
	memset(value,'\0',12);

	if((linP=MatchOrder(src,order))!=NULL)
	{
		linP+=(strlen(order)+2);
		for(linNum=0;;linP++,linNum++)
		{
			if(*linP==','||*linP=='}')break; 
			value[linNum] = *linP;
		}
		OLED_Show(oled,"%-11s",value);
		u3_printf("收到%s信息:%s\n",order,value);
		return 1;
	}	
	return 0;
}

void find_bilibiliBV(_OLED oled,char*src)
{
	
}

/** @defgroup 模块定义/函数声明
  * @{
  */

/**
  * @brief  wifi指令解析        
  * @param  输入参数说明
	* @return 返回值
  * @retval 返回值类型
  */

void get_wifi(void)
{
	if(USART_RX_STA&0x8000)
	{
			USART_RX_STA = 0;
			USART1_GetNum = 0;
			find_bilibiliAPI((_OLED){40,1,2},(char *)BLBL_API_RX,BLBL.order.fans,BLBL.value.fans);
			if(BLBL.value.view[0]=='\0')
					find_bilibiliAPI((_OLED){40,5,2},(char *)BLBL_API_RX,BLBL.order.view,BLBL.value.view);

			u3_printf("USART_RX_BUF:%s\n",USART_RX_BUF);
			memset(USART_RX_BUF,'\0',USART_REC_LEN);
	}
}
/** @defgroup _bool AT_RST(u8 mode)函数声明
  * @{
  */

/**
  * @brief  ESP8266复位        
  * @param  0软件复位 1硬件复位
	* @return TRUE：成功复位 FALSE：失败 可用于检测模块是否存在
  * @retval bool
  */

_bool AT_RST(u8 mode)
{
	USART1_GetNum = 99;
	if(mode)//硬复位
	{
		GPIO_ResetBits(GPIOB,GPIO_Pin_1);	//初始化GPIOB Pin1低电平
		delay_ms(100);
		GPIO_SetBits(GPIOB,GPIO_Pin_1);	
		delay_ms(1000);
	}
	else //软复位
		ESP8266_AT("AT+RST\n");
	if(USART_RX_STA&0x8000)
	{
			USART_RX_STA=0;
			if(MatchOrder((char *)USART_RX_BUF,"ready")!=NULL)
			{
				memset(USART_RX_BUF,'\0',USART_REC_LEN);
				return TRUE;
			}
			memset(USART_RX_BUF,'\0',USART_REC_LEN);
	}
	return FALSE;
}
/** @defgroup u8 AT_Return(char *str)函数声明
  * @{
  */

/**
  * @brief  判断ESP8266返回内容        
  * @param  判断返回值
	* @return 比对成功1 失败0
  * @retval u8
  */
u8 AT_Return(char *str)
{
	if(USART_RX_STA&0x8000)
	{
			USART_RX_STA=0;
			#ifdef debug
				u3_printf("%s",USART_RX_BUF);
			#endif
			if(MatchOrder((char *)USART_RX_BUF,str)!=NULL)
			{
				memset(USART_RX_BUF,'\0',USART_REC_LEN);
				return 1;
			}
			memset(USART_RX_BUF,'\0',USART_REC_LEN);
	}
	return 0;
}

void Other_tasks(void)
{
		u8 flash = 0;
		if(systemtime.msec1flag == 1) 
		{
			systemtime.msec1flag = 0;		
		}
				
	 if(systemtime.msec10flag == 1)
		{
				systemtime.msec10flag = 0;
				if(KEY_Scan(1)==1)
				{
					if(key_state>=100)
					{
							AT_RST(1);
							While_Setwifi();
							OLED_CLS();
							OLED_Show((_OLED){16,2,2},"Waiting for WiFi link");
							while(1)
							{
								if(AT_Return("GOT")) {OLED_Show((_OLED){88,6,2},"TRUE ");break;}
								else{OLED_Show((_OLED){88,6,2},"FALSE");}
								if(systemtime.msec1000flag == 1)//1s
								{
									systemtime.msec1000flag = 0;
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
							BlblConnect();
							ESP8266_SendTime = 5;
							memset(BLBL.value.view,'\0',12);
							ImgInit();
					}

				}//if(KEY_Scan(0)==1)
		}
		if(systemtime.msec100flag == 1) 
		{
				systemtime.msec100flag = 0;	
				get_pc();
		}			
}
		
/** @defgroup u8 AT_SetWifi(u8 error)函数声明
  * @{
  */

/**
  * @brief  设置wifi        
  * @param  错误
	* @return 错误
  * @retval u8
  */
u8 AT_SetWifi(u8 error)
{
	u8 i = 0;
	OLED_CLS();
	OLED_Show((_OLED){16,2,2},"Wait for feedback");
	if(error==0||error==0x01) {}
	else if(error==0x02) goto two;
	else if(error==0x03) goto three;
	for(i=0;FALSE==AT_Return("OK");i++)
	{
		ESP8266_AT("AT\r\n");
		delay_ms(1000);
		if(i==3) return 0x01;//模块无连接
		}
two:
	for(i=0;FALSE==AT_Return("OK");i++)
	{
		ESP8266_AT("AT+CWMODE=3\r\n");
		delay_ms(1000);
		if(i==3) return 0x02;//模式设置失败
	}
three:	
	for(i=0;FALSE==AT_Return("CONNECTED");i++)
	{
		ESP8266_AT("AT+CWJAP=\"%s\",\"%s\"\r\n",PC.value.ssid,PC.value.password);
		delay_ms(1000);
		delay_ms(1000);
		delay_ms(1000);
		if(i==5) return 0x03;//WiFi连接失败
	}

	W25QXX_Write((u8*) Wifi_SetOK,0,14);//写入flash
	return 0;//无错误
}

void While_Setwifi(void)
{
	u8 error = 0;
	while((error=AT_SetWifi(error)))
	{
		OLED_CLS();
		switch(error)
		{
			case 0x01:	OLED_Show((_OLED){16,2,2},"Module not connected  ");break;
			case 0x02:	OLED_Show((_OLED){16,2,2},"Mode setting failed   ");break;
			case 0x03:	OLED_Show((_OLED){16,2,2},"WiFi connection failed");break;
			default:break;
		}
		delay_ms(1000);
		AT_RST(1);
	}
}
/** @defgroup u8 AT_BlblConnect(u8 error)函数声明
  * @{
  */

/**
  * @brief  设置TCP透传哔哩哔哩     
  * @param  错误
	* @return 错误
  * @retval u8
  */
u8 AT_BlblConnect(u8 error)
{
	u8 i;
	OLED_CLS();
	if(error==0||error==0x04) {}
	else if(error==0x05) goto two;
	else if(error==0x06) goto three;
	OLED_Show((_OLED){16,2,2},"Wait TCP    ");
	for(i=0;FALSE==AT_Return("OK");i++)
	{
		ESP8266_AT("AT+CIPSTART=\"TCP\",\"www.bilibili.com\",80\r\n");
		delay_ms(1000);
		if(i==3) return 0x04;//TCP失败
	}
two:	
	OLED_Show((_OLED){16,2,2},"Wait CIPMODE");
	for(i=0;FALSE==AT_Return("OK");i++)
	{
		ESP8266_AT("AT+CIPMODE=1\r\n");
		delay_ms(1000);
		if(i==3) return 0x05;//CIPMODE失败
	}
three:
	OLED_Show((_OLED){16,2,2},"Wait CIPSEND");
	for(i=0;FALSE==AT_Return("OK");i++)
	{
		ESP8266_AT("AT+CIPSEND\r\n");
		delay_ms(1000);
		if(i==3) return 0x06;//CIPSEND失败
	}
	
	return 0;
}
/** @defgroup void BlblConnect(void)函数声明
  * @{
  */

/**
  * @brief  连接哔哩哔哩        
  * @param  none
	* @return none
  * @retval none
  */
void BlblConnect(void)
{
	u8 error = 0;
	while((error=AT_BlblConnect(error)))
	{
		OLED_CLS();
		switch(error)
		{
			case 0x01:	OLED_Show((_OLED){16,2,2},"TCP ERROR    ");break;
			case 0x02:	OLED_Show((_OLED){16,2,2},"CIPMODE ERROR");break;
			case 0x03:	OLED_Show((_OLED){16,2,2},"CIPSEND ERROR");break;
			default:break;
		}
		delay_ms(1000);
		AT_RST(1);
	}
}
