/**
  ******************************************************************************
  * @file    OLED_I2C.h
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
#ifndef __OLED_I2C_H
#define	__OLED_I2C_H

/* Includes ------------------------------------------------------------------*/

#include "stm32f10x.h"

/* Define  ------------------------------------------------------------------*/

#define OLED_ADDRESS	0x78 //通过调整0R电阻,屏可以0x78和0x7A两个地址 -- 默认0x78


/**  OLED_I2C_Exported_Functions ---------------------------------------------------*/

typedef struct {
		u8 x;
		u8 y;
		u8 mode;
	
}_OLED;


void I2C_Configuration(void);
void I2C_WriteByte(uint8_t addr,uint8_t data);
void WriteCmd(unsigned char I2C_Command);
void WriteDat(unsigned char I2C_Data);
void OLED_Init(void);
void OLED_SetPos(unsigned char x, unsigned char y);
void OLED_Fill(unsigned char fill_Data);
void OLED_CLS(void);
void OLED_ON(void);
void OLED_OFF(void);
void OLED_ShowStr(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowStrImg(unsigned char x, unsigned char y, unsigned char ch[], unsigned char TextSize);
void OLED_ShowCN(unsigned char x, unsigned char y, unsigned char str[],unsigned char N);
void OLED_DrawBMP(unsigned char x0,unsigned char y0,unsigned char x1,unsigned char y1,unsigned char BMP[]);
char* itoa(int num,char* str,int radix);	
void OLED_ShowNumber(u8 x,u8 y,u32 num,u8 mode);
void OLED_Show(_OLED oled,char* fmt, ...);
void OLED_Rectangle(u8 x1,u8 y1,u8 x2,u8 y2);
void OLED_RectangleH(u8 x1,u8 y1,u8 x2,u8 y2);






#endif /*__OLED_I2C_H */




