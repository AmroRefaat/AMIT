#include <stdio.h>
#include <stdlib.h>
#include "BIT_MATH.h"
#include"Compiler.h"
#include"DIO_interface.h"
#include"S_SEGMENT.h"
#include"S_SEGMENT_CONFIG.h"
#include "STD_TYPES.h"
#include "ADC_interface.h"
#include "AVR_INT_REG.h"
#include "INT_interface.h"
#include "Delay_Cfg.h"
#include "Delay_interface.h"
#include "TIMER_interface.h"
#include "AVR_TIMER_REG.h"

#define EEAR *((volatile uint8_t*)0x3E)//eerom
#define EEDR *((volatile uint8_t*)0x3D)//eerom
#define EECR *((volatile uint8_t*)0x3C) //eerom




uint8_t state;
uint8_t flagup;
uint8_t  flag1;
uint8_t flagdown;
uint8_t flag2;
uint8_t check;
void changestateup(void);
void changestatedown(void);
void blinkSS(void);
void blinkled(void);
void systemOn_off(void);


int main()
{
	uint16_t tempvalue;


	uint8_t set_tempvalue=60;

	ADC_ConfigStr_t LM35={ADC_AREF_INTERNAL_VREF_OFF,ADC_POLLING,ADC_RIGHT_ADJUST,ADC_RIGHT_ADJUST,ADC_PRESCALLER_128};
	Str_TimerConfiguration_t timer1={TIMER1,F_CPU_CLOCK_1024_TIMER_0,TIMER_COUNTER_MODE,TIMER_INTERRUPT};
	Str_TimerConfiguration_t timer2={TIMER2,F_CPU_CLOCK_1024_TIMER_0,TIMER_COUNTER_MODE,TIMER_INTERRUPT};
	MCAL_DIO_u8SetPinDir(DIO_PORTA,DIO_PIN_0,DIO_INPUT);//up
	MCAL_DIO_u8SetPinDir(DIO_PORTA,DIO_PIN_1,DIO_INPUT);//down
	MCAL_DIO_u8SetPinDir(DIO_PORTA,DIO_PIN_2,DIO_INPUT);//on off
	MCAL_DIO_u8SetPinDir(DIO_PORTB,DIO_PIN_1,DIO_OUTPUT);//heater
	MCAL_DIO_u8SetPinDir(DIO_PORTB,DIO_PIN_2,DIO_OUTPUT);//cooler
	MCAL_DIO_u8SetPinDir(DIO_PORTB,DIO_PIN_3,DIO_OUTPUT);//LED
	MCAL_ADC_Init(&LM35); // ADC int
	initialize_S_SEGMENT(); // S_segment int
	MCAL_Timer_Init(&timer1);
	MCAL_Timer_Init(&timer2);
	HAL_DelayInit(TIMER1); // delay int
	MCAL_EXTINT_u8Init(EXTINT_0 , EXTINT_ON_CHANGE);//INT int
	MCAL_EXTINT_u8Init(EXTINT_1 , EXTINT_RISING_EDGE );//INT int
	MCAL_EXTINT_u8Init(EXTINT_2 , EXTINT_RISING_EDGE );
	MCAL_EXTINT_SetCallBack(EXTINT_0 ,systemOn_off);//power on or off

	MCAL_EXTINT_SetCallBack(EXTINT_1 ,changestateup);
	MCAL_EXTINT_SetCallBack(EXTINT_2 ,changestatedown);

	MCAL_TIMER_SetCallBack(TIMER1,blinkled);//for LED
	MCAL_TIMER_SetCallBack(TIMER2,blinkSS);//forS_segment

	EEAR=0x5f;
	SET_BIT(EECR,1);
	SET_BIT(EECR,2);
	EECR=set_tempvalue;

while(1){

	set_tempvalue=EECR;

	turn_OFF_S_SEGMENT_1();
	turn_OFF_S_SEGMENT_2();
	MCAL_DIO_u8SetPinValue(DIO_PORTB,DIO_PIN_3,DIO_LOW);//led off
	MCAL_DIO_u8SetPinValue(DIO_PORTB,DIO_PIN_2,DIO_LOW);//cooler off
	MCAL_DIO_u8SetPinValue(DIO_PORTB,DIO_PIN_1,DIO_LOW);//heater off


	while(state==1)//system in on
	{

		MCAL_ADC_StartCoversionBusyWait(ADC_CHANNEL0,&tempvalue);


		 turn_ON_S_SEGMENT_1();
		 turn_ON_S_SEGMENT_2();
	     show_ON_S_SEGMENT(tempvalue);

		while((tempvalue>set_tempvalue)&&((tempvalue-set_tempvalue)>4))
		{
			MCAL_DIO_u8SetPinValue(DIO_PORTB,DIO_PIN_2,DIO_HIGH);//cooler on
			MCAL_DIO_u8SetPinValue(DIO_PORTB,DIO_PIN_3,DIO_HIGH);//led on
			if(state == 0)
			 {
				break;
			 }
			if(flagup==1||flagdown==1)
				{
					break;
				}

		}
		while((tempvalue<set_tempvalue)&&((set_tempvalue-tempvalue)>4))
		{
			MCAL_DIO_u8SetPinValue(DIO_PORTB,DIO_PIN_1,DIO_HIGH);//heater on
			MCAL_DIO_u8SetPinValue(DIO_PORTB,DIO_PIN_3,DIO_HIGH);//led on
			MCAL_Timer_Start(TIMER1,8000);//timer that toggle

			if(state == 0)
			{
				break;
			}
			if(flagup==1||flagdown==1)
			{
				break;
			}
		}


		while(flagup>=1||flagdown>=1)

		{
			flagup=1;
			flagdown=1;
			MCAL_Timer_Start(TIMER2,8000);
		    show_ON_S_SEGMENT(set_tempvalue);

		    if(flagup>1&&set_tempvalue<75)
		    	{
		    		set_tempvalue=set_tempvalue+5;
		    		check=0;
		    	}
		    if(flagdown>1&&set_tempvalue>35)
		    	{
		    	    set_tempvalue=set_tempvalue-5;
		    	    check=0;
		    	}
		    if(check>=5)
		    {
		    	flagup=0;
		    	flagdown=0;
		    	break;
		    }
		}




	}

	EECR=set_tempvalue;
}
}



void systemOn_off(void)
{
	state ^=(1<<1);
}
void blinkled(void)
{
	flag1 ^=(1<<1);
	MCAL_DIO_u8SetPinValue(DIO_PORTB,DIO_PIN_3,flag1);
}

void blinkSS(void)
{
	check++;
	flag2 ^=(1<<1);
	if(flag2==1)
	{
		turn_OFF_S_SEGMENT_1();
		turn_OFF_S_SEGMENT_2();
	}
	else
	{
		turn_ON_S_SEGMENT_1();
		turn_ON_S_SEGMENT_2();
	}
}

void changestatedown(void)
{
	flagdown=1;
}

void changestateup(void)
{
	flagup=1;
}
