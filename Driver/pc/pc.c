/**
  ******************************************************************************
  * @file    PC.h
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

_PC PC = 
{
	{
		"ssid",
		NULL,
		"uid",
		"bv"
	},
	{
		"pitest",
		"123456789"
	}
	
};



/** @defgroup 模块定义/函数声明
  * @{
  */

/**
  * @brief  PC指令解析        
  * @param  输入参数说明
	* @return 返回值
  * @retval 返回值类型
  */
char* PC_MatchOrder(char* str,char* order,char *save)
{
	char *linP = NULL;
	if((linP=MatchOrder(str,order))!=NULL)
	{
		linP+=strlen(order);
		sprintf(save,"%s",linP);
		ESP8266_SendTime = 5;
		u3_printf("收到%s信息:%s\n",order,save);
		return order;
	}
	return NULL;
}
void get_pc(void)
{
	char *linP = NULL;
	unsigned char linNum = 0;
	if(USART3_RX_STA&0x8000)
	{
			USART3_RX_STA=0;
			#ifdef debug
				u3_printf("PC_RX=%s\r\n",PC_RX);
				if((linP=MatchOrder((char *)PC_RX,"hub"))!=NULL)
				{
					ESP8266_AT("GET /%s=%s HTTP/1.1\nHost:api.bilibili.com\n\n",BLBL.api.fans,BLBL.uid);
					if(BLBL.value.view[0]=='\0')
					{
						delay_ms(1000);
						ESP8266_AT("GET /%s=%s HTTP/1.1\nHost:api.bilibili.com\n\n",BLBL.api.view,BLBL.uid);
					}
					
				}
				else  ESP8266_AT("%s\r\n",PC_RX);
			#endif
			if((linP=MatchOrder((char *)PC_RX,PC.order.ssid))!=NULL)
			{
				memset(PC.value.ssid,'\0',30);
				memset(PC.value.password,'\0',30);
			
    	 	linP+=4;
				for(linNum=0;*linP!=':';linP++,linNum++)
				{
					PC.value.ssid[linNum] = *linP;
				}
				linP+=1;
				for(linNum=0;*linP!=';';linP++,linNum++)
				{
					PC.value.password[linNum] = *linP;
				}
				u3_printf("收到WiFi信息 ssid=%s,password=%s\n",PC.value.ssid,PC.value.password);
			}
			
			if(PC_MatchOrder((char *)PC_RX,PC.order.bv,BLBL.bv)==PC.order.bv)
			{
				BLBL.get = 0x02;
			}
			if((PC_MatchOrder((char *)PC_RX,PC.order.uid,BLBL.uid))==PC.order.uid)
			{
				memset(BLBL.value.view,'\0',12);
				BLBL.get = 0x01;
				u3_printf("BLBL.value.view清空\nBLBL.value.view[0]:%c\n,BLBL.value.view:%s",BLBL.value.view[0],BLBL.value.view);
			}
			
			memset(USART3_RX_BUF,'\0',USART3_REC_LEN);
	}
}
