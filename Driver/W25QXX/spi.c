/**
  ******************************************************************************
  * @file    spi.c
  * @author  dzy
  * @version V1.0.0
  * @date    2018-8-25
  * @brief   spi function.
  ******************************************************************************
  * @attention
  *
	*		There is no
  * 
  ******************************************************************************
* */

/* Includes ------------------------------------------------------------------*/
#include "allincludes.h"



/* Define ------------------------------------------------------------------*/




/** Exported_Functions		*/



/**  Spi_Functions		*/
/** @defgroup uint8_t SPI_SendData(uint8_t data) 函数声明
  * @{
  */

/**
	* @brief  SPI发送接收八位数据        
  * @param  data
	* @return RecevieData
  * @retval uint8_t
  */
uint8_t SPI_SendData(uint8_t data)  
{  
    uint8_t RecevieData=0,i;  

    for(i=0;i<8;i++)  
    {  
        if(data&0x80)  
        {  
            SPI_OUTHIGH;  
        }  
        else  
        {  
            SPI_OUTLOW;  
        }  

      SPI_SCKHIGH;              //下降沿采集数据
       data<<=1; 
     __NOP();__NOP();__NOP();__NOP(); 
     RecevieData <<= 1;

        if(SPI_IN)
        {
            RecevieData |= 1; //Wait SDO to go Hi
        }
       SPI_SCKLOW;           
    }  
    return RecevieData;  
}

/** @defgroup void MYSPI_Init(void)  
  * @{
  */

/**
  * @brief  SPI引脚初始化        
  * @param  none
	* @return none
  * @retval none
  */
void MYSPI_Init(void)  
{  
    GPIO_InitTypeDef GPIO_InitStructure;  
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOA ,ENABLE);                      
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz;  
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_7; //SPI_CS  and SPI_SCK and SPI_OUT  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
    GPIO_Init(GPIOA,&GPIO_InitStructure);  

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6; //SPI_IN  
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;  
    GPIO_Init(GPIOA,&GPIO_InitStructure);  


    SPI_CSHIGH;  
    SPI_SCKLOW;  
    SPI_OUTLOW;  
}


