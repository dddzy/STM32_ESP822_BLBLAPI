#ifndef __USART3_H
#define __USART3_H	 
#include "sys.h"  


#define USART3_REC_LEN  200  	//定义最大接收字节数 200
#define USART3_MAX_SEND_LEN		800					//最大发送缓存字节数
extern u8  USART3_RX_BUF[USART3_REC_LEN]; //接收缓冲,最大USART_REC_LEN个字节
extern u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 		//发送缓冲,最大USART3_MAX_SEND_LEN字节
extern u16 USART3_RX_STA;         		//接收状态标记	 0-14位为接收字节数，15位接收完成标志位

void usart3_init(u32 pclk1,u32 bound);	//串口3初始化 
void u3_printf(char* fmt,...);
#endif


