#ifndef _SYSTEM_H_
#define _SYSTEM_H_

#define CMC_MODE_X1						0b01000000
#define CMC_MODE_EXTCLOCK				0b11000000
#define	CMC_SYS_CLOCK_UNDER_10MHZ		0b00000000
#define	CMC_SYS_CLOCK_OVER_10MHZ		0b00000001

#define	CSC_INIT_VAL					0b01000000
#define CSC_HOCO_VAL					0b01000000
#define CSC_MOCO_VAL					0b01000011
#define CSC_INVALID_VAL					0b01000001

#define	CKC_INIT_VAL					0b00010000
#define CKC_HOCO_VAL					0b00000000
#define CKC_MOCO_VAL					0b00000011

/*	Function Prototype	*/
void	Clock_Init( void );
void	hdwinit( void );

#endif /* _SYSTEM_H_ */
