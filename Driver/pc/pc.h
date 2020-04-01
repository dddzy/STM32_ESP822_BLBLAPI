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
	
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef _PC_H
#define _PC_H

/* Includes ------------------------------------------------------------------*/

#include "string.h"
#include <stdio.h>
#include "sys.h"


/* Define  ------------------------------------------------------------------*/

typedef struct
{
	char *ssid;
	char *password;
	char *uid;
	char *bv;
}_PCAPI;
typedef struct
{
	char ssid[30];
	char password[30];
}_PCV;

typedef struct
{
	_PCAPI order;
	_PCV value;
}_PC;


extern _PC PC;

/** @defgroup 模块定义/函数声明
  * @{
  */

/**  PC_Exported_Functions ---------------------------------------------------*/

void get_pc(void);


#endif /*__PC_H */
