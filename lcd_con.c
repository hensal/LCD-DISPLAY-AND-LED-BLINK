//******************************************
//**           ��t?��?\?|?i?\?|?��?a ?@?@?@  **
//******************************************
//**includes **
//**
#include <stdio.h>
#include <string.h>
#include "iodefine.h"
#include "common.h"
#include "config.h"
#include "system.h"
#include "sfr.h"
#include "lcd_con.h"


/**********************************************************************
*** define?@(?��??�fe?`?j
**********************************************************************/
extern unsigned char TITL0[16] = "DISPLAYtest 2021";
extern unsigned char TITL1[16] = "�welcome home";

unsigned int del_cnt;

//*****************************************
void dispset_titl(void)
{
	unsigned char n;
	unsigned char dsp_buf;

	lcd_l1(0x00);				//1?s?U?a�ga?A?h???X?Z?b?g
	for (n=0 ;n<16 ;n++) {
		dsp_buf = TITL0[n];		//line 1
		lcd_dout(dsp_buf);		//1data write
	}
//
	lcd_l2(0x00);				//2?s?U?a�ga?A?h???X?Z?b?g
	for (n=0 ;n<16 ;n++) {
		dsp_buf = TITL1[n];		//line 2
		lcd_dout(dsp_buf);		//1data write
	}
}
//****************************************
//**
void dispset_count(void)
{
	
	delay_msec(100);
	dpcnt[0]++;
	if (dpcnt[0] > 9){
		dpcnt[0] = 0;
		dpcnt[1]++;
	}
	if (dpcnt[1] > 9){
		dpcnt[1] = 0;
		dpcnt[2]++;
	}
	if (dpcnt[2] > 9){
		dpcnt[2] = 0;
		dpcnt[3]++;
	}
	if (dpcnt[3] > 9){
		dpcnt[3] = 0;
	}
	lcd_cout(0x8C);
	lcd_dout(dpcnt[3] + 0x30);
	lcd_dout(dpcnt[2] + 0x30);
	lcd_dout(dpcnt[1] + 0x30);
	lcd_dout(dpcnt[0] + 0x30);
}

//****************************************
//**?@LCD?��?u���
//
void lcd_init(void)
{
	P0 = 0x00;		//E=0,R/W=0
//	
	P2 = 0x03;
	P0 = 0x02;		//E=1,R/W=0
	delay_micro(100);
	P0 = 0x00;		//E=0,R/W=0
	delay_msec(5);
//
	P2 = 0x03;
	P0 = 0x02;		//E=1,R/W=0
	delay_micro(100);
	P0 = 0x00;		//E=0,R/W=0
	delay_msec(5);
//
	P2 = 0x03;
	P0 = 0x02;		//E=1,R/W=0
	delay_micro(100);
	P0 = 0x00;		//E=0,R/W=0
	delay_msec(5);
//
	P2 = 0x02;		//4bitAT��A�f�E?Y�fe
	P0 = 0x02;		//E=1,R/W=0
	delay_micro(100);
	P0 = 0x00;		//E=0,R/W=0
	delay_msec(5);
//** ?�}?�}?c?c4ET�PAAT��A�f�E
	lcd_cout(0x08);		//?\?|��I	
	delay_msec(5);
	lcd_cout(0x01);		//?\?|�COO��	
	delay_msec(5);
	lcd_cout(0x06);		//�LYAO��O��AT?�PA	
	delay_msec(5);
	lcd_cout(0x0E);		//?\?|on?A����?Uon	
	delay_msec(5);
}

//*****************************************
//** 1?s?U�}ATU??�PA
//** column(?n)
//
void lcd_l1(unsigned char column)
{
	unsigned char pos;
	
	pos = column & 0x0F;	//?n?I?A�ea�fl??16
	pos = pos | 0x80;	//1?s?UET�PA�fC��A
	lcd_cout(pos);
	delay_msec(5);
}
//*****************************************
//** 2?s?U�}ATU??�PA
//
void lcd_l2(unsigned char column)
{
	unsigned char pos;

	pos = column & 0x0F;	//?n?I?A�ea�fl??16
	pos = pos | 0xC0;	//2?s?UET�PA�fC��A
	lcd_cout(pos);
	delay_msec(5);
}
//*****************************************
//** �E�ʁ~�CALCD?@oYAU��Uo��AT?o?I
//
void lcd_cout(unsigned char code)
{
	unsigned char code_msb,code_lsb;

	code_msb = code / 0x10;
	code_lsb = code & 0x0F;
	P0 = 0x00;		//E=0,R/W=0
//
	P2 = code_msb;
	P0 = 0x02;		//E=1,R/W=0
	delay_micro(2);
	P0 = 0x00;		//E=0,R/W=0
//
	delay_micro(2);
//
	P2 = code_lsb;
	P0 = 0x02;		//E=1,R/W=0
	delay_micro(2);
	P0 = 0x00;		//E=0,R/W=0
	delay_micro(50);
//
}
//****************************************
//** �E�ʁ~�CALCD?@AT��Ao��AT?o?I
//
void lcd_dout(unsigned char code)
{
	unsigned char code_msb,code_lsb;

	code_msb = code / 0x10;
	code_lsb = code & 0x0F;
	P0 = 0x01;		//E=0,R/W=1
//
	P2 = code_msb;
	P0 = 0x03;		//E=1,R/W=1
	delay_micro(2);
	P0 = 0x01;		//E=0,R/W=1
//
	delay_micro(2);
//
	P2 = code_lsb;
	P0 = 0x03;		//E=1,R/W=1
	delay_micro(2);
	P0 = 0x01;		//E=0,R/W=1
	delay_micro(50);
//
}
//*****************************************
//** I2�CU?b�fx��?
void delay_micro(unsigned int icnt)
{
	unsigned int del_cnt;

	for (del_cnt=0;del_cnt<icnt;del_cnt++){
			NOP();
			NOP();
			NOP();
			NOP();
			NOP();
	}
}
//******************************************
//** DO?b�fx��?
void delay_msec(unsigned int icnt)
{
	unsigned int del_cnt;

	for (del_cnt=0;del_cnt<icnt;del_cnt++){
//		wdt_rst();
		delay_micro(1000);
	}
}
//******** END ********
