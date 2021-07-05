#include<stdio.h>
#include<string.h>
#include "iodefine.h"
#include"common.h"
#include"config.h"
#include"system.h"
#include"sfr.h"
#include"lcd_con.h"
#include "watchdogtimer.h"

void main(void);
void main_loop(void);
void hdwinit(void);
void SystemInit(void);
void WDT_Init(void);
void WDT_Reset(void);
void IRQ_Init(void);
void PORT_Init(void);
void Clock_Init(void);
void dispset_count(void);

void lcd_init(void);

unsigned char disp_address;
unsigned char sw_data;

unsigned char n;
unsigned char dsp_buf;
unsigned char ucsysclocksrc;
unsigned char ucsysclockfreq;
unsigned char uccmcinitval;
unsigned char code_msb, code_lsb;
unsigned char pos;	

unsigned char dpcnt[4];

void main(void)
{
                                         /*Hardware initialize*/
	hdwinit();
	 
	                                 /*Panel initialize*/
	panel_init0();
	
	                                /*LCD initiate*/
	 lcd_init();
	 
	                                  /*Main loop*/
	 main_loop();
}

void main_loop(void) {
while(1) {
       dispset_titl();                
       panel();                                       /*pannel proccesing */
       WDT_Reset();               /*watchdog timer reset starat*/
       dispset_count();
    }
}

void hdwint(void)
{
	__DI( );                                 //DI(); this function also automatically converts into _DI().Both way can be used.Interrupt disabled
	SystemInit( );
	__EI( );                                 //Interrupt enabled.also EI(); can be used insted
}

void SystemInit(void) {
	
          PIOR0 = 0x00;                                      /*INITIALIZE THE PERIPHERAL I/O REDIRECTION REGISTERS*/
          PIOR1 = 0x00;  
          PIOR2 = 0x00;  
          PIOR3 = 0x00;  

          PER0 =  0x00;                                     /*INITIALIZE THE PERIPHERAL ENABLE REGISTERS*/
          PER1 =  0x00;
          PER2 =  0x00;
  
          Clock_Init();                                          /*CLOCK GENERATE INITIATE*/

          PORT_Init();                                         /*PORT INITIATE*/

          WDT_Init();                                          /*WatchDogTimer INITIATE*/
 
          IRQ_Init();                                            /*IRQ (interrupt request)  INITIATE*/
        }

void IRQ_Init(void)   {
	
          MK0L= 0xFF;                                     //ALL INDIVIDUAL INTERRUPT IS PROHIBITED      //interrupt mask flag register 
          IF0L =   0x00;                                    //INTERRUPT REQUEST FLAG ALL CLEARNESS     //Interrupt request flag registers
          PR00L= 0xFF;                                  //PRIORITY LEVEL CLEARNESS
          PR10L= 0xFF;                                 //PRIORITY LEVEL CLEARNESS

          MK1H= 0xFF;
          IF0H= 0x00;
          PR00H= 0xFF;
          PR10H= 0xFF;

          MK1L= 0xFF;
          IF1L= 0x00;
          PR01L= 0xFF;
          PR11L= 0xFF;

          MK1H= 0xFF;
          IF1H= 0x00;
          PR01H= 0xFF;
          PR11H= 0xFF;

          MK2L= 0xFF;
          IF2L= 0x00;
          PR02L= 0xFF;
          PR12L= 0xFF;

          MK2H= 0xFF;
          IF2H= 0x00;
          PR02H= 0xFF;
          PR12H= 0xFF;

          EGP0= 0x00;                                      //EXTERNAL INTERRUPT RISING EDGE
          EGN0= 0x00;                                      //EXTERNAL INTERRUPT RISING EDGE
          EGP1= 0x00;                                      //EXTERNAL INTERRUPT RISING EDGE
          EGN1= 0x00;                                      //EXTERNAL INTERRUPT RISING EDGE
}

void PORT_Init(void) {
	
                                                      /*initialize the port output mode register 0*/
          POM0= 0x00;  
	  POM2= 0x00;
          POM3= 0x00;
          POM4= 0x00;
          POM5= 0x00;
   
                                                    /*INITIALIZE THE PORT REGISTER*/
          P0= INIT_P0;
          P2= INIT_P2;
          P3= INIT_P3;
          P4= INIT_P4;
          P5= INIT_P5;
   
                                                   /*INITIALIZE THE PULL-UP RESISTOR OPTION REGISTER*/
          PU0= INIT_PU0;
          PU3= INIT_PU3;
          PU4= INIT_PU4;
          PU5= INIT_PU5;
          PU12= INIT_PU12;
   
                                                   /*INITIALIZE MODE REGISTERS*/
          PM0= INIT_PM0;
          PM2= INIT_PM2;
          PM3= INIT_PM3;
          PM4= INIT_PM4;
          PM5= INIT_PM5;
   
                                                     /*INITIALIZE PORT MODE CONTROL REGISTER 0*/
          PMC0= INIT_PMC0;
          PMC2= INIT_PMC2;
          PMC3= INIT_PMC3;
          PMC5= INIT_PMC5;
}

void Clock_Init( void )
{
	UCHAR	ucsysclocksrc;
	UCHAR	ucsysclockfreq;
	UCHAR	uccmcinitval;

	ucsysclocksrc = SYS_CLOCK_SRC;
	if( (ucsysclocksrc == CLOCK_SRC_X1) || (ucsysclocksrc == CLOCK_SRC_EXTERNAL) ) {
		uccmcinitval = 0x00;
		if(ucsysclocksrc == CLOCK_SRC_X1) {
			uccmcinitval = CMC_MODE_X1;
			ucsysclockfreq = SYS_CLOCK_FREQ;
			if(ucsysclockfreq > 10) {
				uccmcinitval |= CMC_SYS_CLOCK_OVER_10MHZ;
			}
			else {
				uccmcinitval |= CMC_SYS_CLOCK_UNDER_10MHZ;
			}
		}
		else {
			uccmcinitval = CMC_MODE_EXTCLOCK;
		}
		CMC = uccmcinitval;

		/* CSC register setting */
		CSC = CSC_INVALID_VAL;

		if(ucsysclocksrc == CLOCK_SRC_X1) {
			while(OSTC != 0xFF);
		}

		MCM0 = 1;
		while (MCS != 1)		/* Wait Main Clock to be set. */
		{
			NOP();
		}
		HIOSTOP  = 1;			/* HOCO operation stop */
	}
	else if( ucsysclocksrc == CLOCK_SRC_MIDDLESPEED ) {
		
		switch (SYS_CLOCK_FREQ)
		{
			case 4:
				/* clock is set to 4MHz. */
				MOCODIV = 0x00;
				
				break;
				
			case 2:
				/* clock is set to 2MHz. */
				MOCODIV = 0x01;
				
				break;
				
			case 1:
				/* clock is set to 1MHz. */
				MOCODIV = 0x02;
				
				break;
				
			default:
				break;
		}
		
		/* Clock changing: change to MOCO. */
		MIOEN = 1;					/* MOCO operation start */
		MCM1 = 1;					/* Set fOCO to MOCO. */
		while (MCS1 != 1)			/* Wait fOCO to be set to MOCO. */
		{
			NOP();
		}
		HIOSTOP  = 1;				/* HOCO operation stop */
	}
}

        
