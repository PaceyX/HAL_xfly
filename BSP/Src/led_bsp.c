#include "led_bsp.h"




unsigned short LEDmapTmp[51];


/*
*	@brief: send data to IC.
*	@param: command: diverse function; 	   dat: 0000-FFFF
*	@return: none.
*/
void SendData(char command, unsigned short dat)
{
	unsigned char compare_data = 0x0;
	
	switch(command)
	{
		case command_NO_COMMAND:                      compare_data = 0xF;break;
		case command_WRITE_SWITCH:                    compare_data = 0xE;break;
		case command_DATA_LATCH:                      compare_data = 0xC;break;
		case command_GLOBAL_LATCH:                    compare_data = 0xA;break;
		case command_WRITE_CONFIGURATION:             compare_data = 0x8;break;
		case command_READ_CONFIGURATION:              compare_data = 0x0;break;
		case command_OPEN_ERROR_DETECTION:            compare_data = 0x0;break;
		case command_SHORT_ERROR_DETECTION:           compare_data = 0x0;break;
		case command_COMBINED_ERROR_DETECTION:        compare_data = 0x0;break;
		case command_END_ERROR_DETECTION:             compare_data = 0x0;break;
		case command_THERMAL_ERROR_READING:           compare_data = 0x0;break;
		default:;
	}

	
	unsigned char i;
	
	LE_L();
	CLK_L();
	Delay_us(1);
	
	for(i = 0; i<16; i++)
	{
		if( (dat<<i)&0x8000)	SDI_H();
		else		SDI_L();
		
		Delay_us(1);
		CLK_H();
		Delay_us(1);
		CLK_L();
		Delay_us(1);
	
		
		if(i>=compare_data)  LE_H();
		else	LE_L();
	}
	
	LE_L();

}

/*
*	@brief: update the new status in all channel.
*	@param: LEDmap[]: the arrey for load the data.
*	@return: none.
*/
void LDI_UseNewLEDmap(unsigned short LEDmap[])
{
	int count1;
	unsigned short LEDmapTemp_[51];
	
	for(count1 = 0; count1<51; count1++)
		LEDmapTemp_[count1] = LEDmap[count1];
	
	if(NUMs_1642 == 0x3)												/* matrix 3*16*/
	{
		for(count1 = 0; count1 < 16-1 ; count1++)
		{
			SendData(command_NO_COMMAND, LEDmapTemp_[3*count1 + 0]);
			SendData(command_NO_COMMAND, LEDmapTemp_[3*count1 + 1]);
			SendData(command_DATA_LATCH, LEDmapTemp_[3*count1 + 2]);
		}
		SendData(command_NO_COMMAND, LEDmapTemp_[3*count1 + 0]);
		SendData(command_NO_COMMAND, LEDmapTemp_[3*count1 + 1]);
		SendData(command_GLOBAL_LATCH, LEDmapTemp_[3*count1 + 2]);
		
		count1++;
		SendData(command_NO_COMMAND, LEDmapTemp_[3*count1 + 0]);
		SendData(command_NO_COMMAND, LEDmapTemp_[3*count1 + 1]);
		SendData(command_WRITE_SWITCH, LEDmapTemp_[3*count1 + 2]);		/* write switch 	*/
	}
	else if(NUMs_1642 == 0x2)											/* matrix 2*16*/
	{
		for(count1 = 0; count1 < 16-1; count1++)
		{
			SendData(command_NO_COMMAND, LEDmapTemp_[2*count1 + 0]);
			SendData(command_DATA_LATCH, LEDmapTemp_[2*count1 + 1]);
		}
		SendData(command_NO_COMMAND, LEDmapTemp_[2*count1 + 0]);
		SendData(command_GLOBAL_LATCH, LEDmapTemp_[2*count1 + 1]);
		
		count1++;
		SendData(command_NO_COMMAND, LEDmapTemp_[2*count1 + 0]);
		SendData(command_WRITE_SWITCH, LEDmapTemp_[2*count1 + 1]);		/* write switch		*/
	}
	else if(NUMs_1642 == 0X1)											/* matrix 1*16*/
	{
		for(count1 =0; count1 < 16-1; count1++)
		{
			SendData(command_DATA_LATCH, LEDmapTemp_[1*count1 + 0]);
		}
		SendData(command_GLOBAL_LATCH,LEDmapTemp_[1*count1 + 0]);
		
		count1++;
		SendData(command_WRITE_SWITCH, LEDmapTemp_[1*count1 + 0]);		/* write switch		*/
	}
	
}

/*
*	@brief: adjust the led colour, the detatil please see the chart.
*	@param: num: the led to be changed; 
			Red_level: the red level; 
			Green_Level: the green level; 
			Blue_Level: the blue level.
*	@return: none.
*/
void LEDs_ColorAdjust(unsigned char num, uint8_t Red_level, uint8_t Green_Level, uint8_t Blue_Level)
{
	unsigned short level[3];
	
	#ifdef LED1642_IC3
	if(Red_level <= 255 && Green_Level <= 255 && Blue_Level <= 255)
	{
		LEDmapTmp[48] = 0xFFFF;
		LEDmapTmp[49] = 0xFFFF;
		LEDmapTmp[50] = 0xFFFF;
		
		num--;
		
		level[0] =  Red_level * 257;
		level[1] =  Green_Level * 257;
		level[2] =  Blue_Level * 257;
		
		LEDmapTmp[3*num + 0]=level[0];
		LEDmapTmp[3*num + 1]=level[1];
		LEDmapTmp[3*num + 2]=level[2];
		
		LDI_UseNewLEDmap(LEDmapTmp);
	}
	
	#endif
	
	
	#ifdef LED1642_IC2
	if(Red_level <= 255 && Green_Level <= 255 && Blue_Level <= 255)
	{
		LEDmapTmp[32] = 0xFFFF;
		LEDmapTmp[33] = 0xFFFF;
		
		num--;
		
		level[0] =  Red_level * 257;
		level[1] =  Green_Level * 257;
		level[2] =  Blue_Level * 257;
		
		LEDmapTmp[3*num + 0]=level[0];
		LEDmapTmp[3*num + 1]=level[1];
		LEDmapTmp[3*num + 2]=level[2];	
		
		LDI_UseNewLEDmap(LEDmapTmp);
	}
	#endif
	
	
	#ifdef LED1642_IC1
	if(Red_level <= 255 && Green_Level <= 255 && Blue_Level <= 255)
	{
		LEDmapTmp[16] = 0xFFFF;
		
		num--;
		
		level[0] =  Red_level * 257;
		level[1] =  Green_Level * 257;
		level[2] =  Blue_Level * 257;
		
		LEDmapTmp[3*num + 0]=level[0];
		LEDmapTmp[3*num + 1]=level[1];
		LEDmapTmp[3*num + 2]=level[2];	
		
		LEDmapTmp[16] = 0xFFFF;
		LDI_UseNewLEDmap(LEDmapTmp);
	}
	#endif
	
}

/**
* @brief  ResetupDriver.
*         Set configuration register for the given value.
* @param  16 bit configuration register value
* @retval always return 0x00
*/
void LEDsSetConfig(void)
{
	uint16_t data;
	data = 0x8001;		/* 8045 */

	SendData(command_WRITE_CONFIGURATION, data);

}


uint8_t Red_levelt =30 , Green_Levelt =30, Blue_Levelt =40 ;



void run_led_test(void)
{
	unsigned char num;
	
	unsigned short level[3];
	
	for(num = 0; num < 16; num++)
	{
		level[0] =  Red_levelt * 257;
		level[1] =  Green_Levelt * 257;
		level[2] =  Blue_Levelt * 257;
		
		LEDmapTmp[3*num + 0]=level[0];
		LEDmapTmp[3*num + 1]=level[1];
		LEDmapTmp[3*num + 2]=level[2];	
		
		LDI_UseNewLEDmap(LEDmapTmp);
		Delay_ms(100);
	}
	
	for(num = 15; num > 0; num--)
	{
		level[0] =  255 * 257;
		level[1] =  255 * 257;
		level[2] =  255 * 257;
		
		LEDmapTmp[3*num + 0]=level[0];
		LEDmapTmp[3*num + 1]=level[1];
		LEDmapTmp[3*num + 2]=level[2];	
		
		LDI_UseNewLEDmap(LEDmapTmp);
		Delay_ms(100);
	}
	LEDmapTmp[0 + 0]=level[0];
	LEDmapTmp[0 + 1]=level[1];
	LEDmapTmp[0 + 2]=level[2];	
	
	LDI_UseNewLEDmap(LEDmapTmp);
	Delay_ms(100);
	
//	Red_levelt+=60;
	Green_Levelt+=60;
//	Blue_Levelt+=60;
	if(Red_levelt>255)		Red_levelt = 255;
	if(Green_Levelt>255)	Green_Levelt = 255;
	if(Blue_Levelt>255)		Blue_Levelt = 255;
}



void bright_test(void)
{
	//Keeping all the channels on
	LEDmapTmp[16] = 0xFFFF;
//	LEDmapTmp[3] = 0xFFFF;
//	LEDmapTmp[6] = 0xFFFF;
	
	//Startup sequence demo
	for (int count1=0; count1<48; count1++)
	{
		LEDmapTmp[count1] = 0x0000;
	}
	
	/************Show inner rectangle in red************/
	LEDmapTmp[9]=255*257;LEDmapTmp[8]=10*257;LEDmapTmp[7]=0;				//   RGB
	LEDmapTmp[12]=0;LEDmapTmp[11]=105*257;LEDmapTmp[10]=180*257;		//	 RGB
	LEDmapTmp[15]=0;LEDmapTmp[14]=10*257;LEDmapTmp[13]=200*257;					//	 RGB
	
	LEDmapTmp[16] = 0xFFFF;
	
	LDI_UseNewLEDmap(LEDmapTmp);
	
	
}

