#ifndef __SPI_FLASH_H
#define __SPI_FLASH_H

#include "stm32f10x.h"
#include <stdio.h>

//#define  sFLASH_ID              0xEF3015   //W25X16
//#define  sFLASH_ID              0xEF4015	 //W25Q16
#define  sFLASH_ID              0XEF4018   //W25Q128
//#define  sFLASH_ID              0XEF4017    //W25Q64


#define SPI_CSHIGH  GPIO_SetBits(GPIOA,GPIO_Pin_4)  // CS----PB9
#define SPI_CSLOW   GPIO_ResetBits(GPIOA,GPIO_Pin_4)  
  
#define SPI_SCKHIGH GPIO_SetBits(GPIOA,GPIO_Pin_7)    //SCLK----PA5
#define SPI_SCKLOW  GPIO_ResetBits(GPIOA,GPIO_Pin_7)  

#define SPI_OUTHIGH GPIO_SetBits(GPIOA,GPIO_Pin_5)  
#define SPI_OUTLOW  GPIO_ResetBits(GPIOA,GPIO_Pin_5)  //MOSI----PA7

#define SPI_IN      GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)  //MISO----PA6



void W25x16_Init(void) ;
void MYSPI_Init(void);
uint8_t SPI_SendData(uint8_t data);
#endif /* __SPI_FLASH_H */

