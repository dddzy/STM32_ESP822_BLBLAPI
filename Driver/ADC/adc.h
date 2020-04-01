#ifndef __ADC_H
#define __ADC_H	
#include "sys.h"

#define Battery_Ch 1

typedef struct
{
	u16 voltage;//电压值
	
	float percent_V;//电量百分比
	float EK;
}_VOL;

extern _VOL vol;

void Adc_Init(void);
u16 Get_Adc(u8 ch);
int Get_battery_volt(void);   
void Get_battery(_VOL *v) ;
void Get_V(_VOL *v);
u16 Get_Adc_Average(u8 ch);
#endif 















