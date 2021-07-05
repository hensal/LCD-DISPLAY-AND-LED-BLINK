/***********************************************************************
Private variables and functions
?O?Åh?v???g?^?C?v?e??
***********************************************************************/
void dispset_titl(void);
void lcd_init(void);
void panel_init0(void);
void panel(void);         
void lcd_l1(unsigned char column);
void lcd_l2(unsigned char column);
void lcd_cout(unsigned char code);
void lcd_dout(unsigned char code);
void delay_micro(unsigned int icnt);
void delay_msec(unsigned int icnt);
void dispset_count(void);
//**** ?I?Åh
extern unsigned char dpcnt[4];
