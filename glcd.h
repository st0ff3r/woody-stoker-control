#include <pic18fregs.h>

#define LCD_DATA		PORTD
#define LCD_TRIS		TRISD

#define ENABLE			PORTEbits.RE2
#define ENABLE_TRIS		TRISEbits.TRISE2

#define RW				PORTEbits.RE1
#define RW_TRIS			TRISEbits.TRISE1

#define DI				PORTEbits.RE0
#define DI_TRIS			TRISEbits.TRISE0

#define RESET			PORTCbits.RC5
#define RESET_TRIS		TRISCbits.TRISC5

#define CS1				PORTCbits.RC0
#define CS1_TRIS		TRISCbits.TRISC0

#define CS2				PORTCbits.RC1
#define CS2_TRIS		TRISCbits.TRISC1

#define LCD_LEFT		0b01
#define LCD_RIGHT		0b10
#define LCD_BOTH		0b11
#define LCD_NONE		0b00

void lcd_init(void);
void lcd_enable(void);
unsigned char lcd_status(void);
void lcd_reset(void);
void lcd_waitbusy(void);

void lcd_screenon(unsigned char on);
void lcd_cls(void);
void lcd_setpage(unsigned char page);
void lcd_setyaddr(unsigned char y);
void lcd_selectside(unsigned char sides);
void lcd_write (unsigned char d);
unsigned char lcd_read (void);
void lcd_plot_pixel(unsigned char rx, unsigned char ry);

//void delay_20us();
#define delay_2us()	__asm nop __endasm; __asm nop __endasm;
//void delay_500us();