#ifndef _CONFIG_H_
#define _CONFIG_H_

/* Applilet EZ PL for RL78 Append below */

#define	DEVICE_R5F1058AALA

#define	SYS_CLOCK_SRC		CLOCK_SRC_HIGHSPEED
#define	SYS_CLOCK_FREQ		12
#define	SYS_FLASHMODE		FLASHMODE_HS

/* PORT Initialize */
#define	INIT_P0			0x00
#define	INIT_P2			0x00
#define	INIT_P3			0x00
#define	INIT_P4			0x00
#define	INIT_P5			0x00

/* PORT IN/OUT MODE */
#define	INIT_PM0		0xff
#define	INIT_PM2		0xf0
#define	INIT_PM3		0xf7
#define	INIT_PM4		0xff
#define	INIT_PM5		0xff
#define	INIT_PM12		0xff
#define	INIT_PM13		0xff

/* PORT Pull-up resistor */
#define	INIT_PU0		0x03
#define	INIT_PU2		0x00
#define	INIT_PU3		0x07
#define	INIT_PU4		0x01
#define	INIT_PU5		0x7e
#define	INIT_PU12		0x20
#define	INIT_PU13		0x00


/* A/D PORT conf */
#define	INIT_PMC0		0xfc
#define	INIT_PMC2		0xf0
#define	INIT_PMC3		0xf0
#define	INIT_PMC5		0xbf


#define	TIM_USED		(1)
#define	DGOUT_USED		(1)

#endif /*_CONFIG_H_*/
