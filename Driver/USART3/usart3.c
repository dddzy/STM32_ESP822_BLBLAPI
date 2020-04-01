#include "allincludes.h"
#include "stdarg.h"	 	 
#include "stdio.h"	 

u8  USART3_TX_BUF[USART3_MAX_SEND_LEN]; 			//发送缓冲,最大USART3_MAX_SEND_LEN字节
u8 USART3_RX_BUF[USART3_REC_LEN]; //数组用来存储接收到的数据，而USART3_REC_LEN为最多能接收的字节限度
u16 USART3_RX_STA=0;         		//接收状态标记	 0-14位为接收字节数，15位接收完成标志位
//串口3中断服务函数
void USART3_IRQHandler(void)
{
	u8 res;	   

	if(USART3->SR&(1<<5))//接收到数据
	{	 
		res=USART3->DR; 
		#ifdef debugo
			USART3_RX_BUF[USART3_RX_STA&0X3FFF]=res;
			USART3_RX_STA++;
			USART3_RX_STA|=0x8000;	//接收完成了 
		#else
		if((USART3_RX_STA&0x8000)==0)//接收未完成
		{
			if(USART3_RX_STA&0x4000)//接收到了0x0d
			{
				if(res!=0x0a)USART3_RX_STA=0;//接收错误,重新开始
				else USART3_RX_STA|=0x8000;	//接收完成了 
			}else //还没收到0X0D
			{	
				if(res==0x0d)USART3_RX_STA|=0x4000;
				else
				{
					USART3_RX_BUF[USART3_RX_STA&0X3FFF]=res;
					USART3_RX_STA++;
					if(USART3_RX_STA>(USART3_REC_LEN-1))USART3_RX_STA=0;//接收数据错误,重新开始接收	  
				}		 
			}
		}
		#endif
//	   	res=USART3->DR; 			 
//		   USART3_RX_BUF[USART3_RX_STA&0x7FFF]=res;//数据放进数组中，则可以用到main函数中了
//		   USART3_RX_STA++;                         //字节长度++
//		  if(USART3_RX_STA>(USART3_REC_LEN-1))USART3_RX_STA=0;//接收数据错误,重新开始接收	+; 
//		   USART3_RX_STA|=0x8000;//串口3接收完成
////		 USART_ClearITPendingBit(USART3,USART_IT_RXNE);//清除接收中断标志
	}
		
			
}

//初始化IO 串口3
//pclk1:PCLK1时钟频率(Mhz)
//bound:波特率 
void usart3_init(u32 pclk1,u32 bound)
{  	 
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC->APB2ENR|=1<<3;   	//使能PORTB口时钟  
 	GPIOB->CRH&=0XFFFF00FF;	//IO状态设置
	GPIOB->CRH|=0X00008B00;	//IO状态设置 
	
	RCC->APB1ENR|=1<<18;  	//使能串口时钟 	 
	RCC->APB1RSTR|=1<<18;   //复位串口3
	RCC->APB1RSTR&=~(1<<18);//停止复位	
	//波特率设置
 	USART3->BRR=(pclk1*1000000)/(bound);// 波特率设置	 
	USART3->CR1|=0X200C;  	//1位停止,无校验位.
	//使能接收中断 
	USART3->CR1|=1<<5;    	//接收缓冲区非空中断使能	  
  NVIC_InitStructure.NVIC_IRQChannel = USART3_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=3 ;//抢占优先级3
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器	
}

//串口3,printf 函数
//确保一次发送数据不超过USART3_MAX_SEND_LEN字节
void u3_printf(char* fmt,...)  
{  
	u16 i,j; 
	va_list ap; 
	va_start(ap,fmt);
	vsprintf((char*)USART3_TX_BUF,fmt,ap);
	va_end(ap);
	i=strlen((const char*)USART3_TX_BUF);		//此次发送数据的长度
	for(j=0;j<i;j++)							//循环发送数据
	{
		while((USART3->SR&0X40)==0);			//循环发送,直到发送完毕   
		USART3->DR=USART3_TX_BUF[j];  
	} 
}
