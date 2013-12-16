/*
 * Project name: Testing GLCD with PIC16F887
 * Copyright:
     (c) Embedded-Lab.com, 2011.

 * Description:
     This routine demonstrates how to initialize a KS0108 based GLCD and 
     activate the pixels on display. A sub-routine is written to draw a point on
     the GLCD at a given coordinates.
      * Test configuration:
     MCU:             PIC16F887
     Dev.Board:       UNI-DS6
     Oscillator:      HS, 10.0000 MHz
     Ext. Modules:    GLCD 128x64, KS108/107 controller

*/

// Glcd module connections
#define GLCD_Data   PORTD
#define GLCD_Dir    TRISD

sbit GLCD_CS1 at RB0_bit;
sbit GLCD_CS2 at RB1_bit;
sbit GLCD_RS  at RB2_bit;
sbit GLCD_RW  at RB3_bit;
sbit GLCD_RST  at RB4_bit;
sbit GLCD_EN at RB5_bit;

sbit GLCD_CS1_Direction at TRISB0_bit;
sbit GLCD_CS2_Direction at TRISB1_bit;
sbit GLCD_RS_Direction  at TRISB2_bit;
sbit GLCD_RW_Direction  at TRISB3_bit;
sbit GLCD_RST_Direction  at TRISB4_bit;
sbit GLCD_EN_Direction at TRISB5_bit;
// End Glcd module connections

void Enable_Pulse()
{
   GLCD_EN = 1; //EN high
   delay_us(5);
   GLCD_EN = 0; //EN low
   delay_us(5);
}

void GLCD_ON()
{
    //Activate both chips
    GLCD_CS1 = 0;
    GLCD_CS2 = 0;
    GLCD_RS = 0;          //RS low --> command
    GLCD_RW = 0;          //RW low --> write
    GLCD_Data = 0x3F;         //ON command
    Enable_Pulse();
}

void Set_Start_Line(unsigned short line)
{
    GLCD_RS = 0;             //RS low --> command
    GLCD_RW = 0;             //RW low --> write
    //Activate both chips
    GLCD_CS1 = 0;
    GLCD_CS2 = 0;
    GLCD_Data = 0xC0 | line;     //Set Start Line command
    Enable_Pulse();
}

void GOTO_COL(unsigned int x)
{
   unsigned short Col_Data;
   GLCD_RS = 0;              //RS low --> command
   GLCD_RW = 0;              //RW low --> write
   if(x<64)             //left section
   {
      GLCD_CS1 = 0;          //select chip 1
      GLCD_CS2 = 1;          //deselect chip 2
      Col_Data = x;              //put column address on data port
   }
   else                 //right section
   {

      GLCD_CS2 = 0;
      GLCD_CS1 = 1;
      Col_Data = x-64;   //put column address on data port
   }
   Col_Data = (Col_Data | 0x40 ) & 0x7F;  //Command format
   GLCD_Data = Col_Data;
   Enable_Pulse();
}

void GOTO_ROW(unsigned int y)
{
   unsigned short Col_Data;
   GLCD_RS = 0;                  //RS low --> command
   GLCD_RW = 0;                  //RW low --> write
   Col_Data = (y | 0xB8 ) & 0xBF; //put row address on data port set command
   GLCD_Data = Col_Data;
   Enable_Pulse();
}

void GOTO_XY(unsigned int x,unsigned int y)
{
    GOTO_COL(x);
    GOTO_ROW(y);
}

void GLCD_Write(unsigned short b)
{
   GLCD_RS = 1;          //RS high --> data
   GLCD_RW = 0;          //RW low --> write
   GLCD_Data = b;            //put data on data port
   delay_us(1);
   Enable_Pulse();
}

unsigned short GLCD_Read(unsigned short column)
{
    unsigned short read_data = 0; //Read data here
    GLCD_Dir = 0xFF;     //PORTD as Input
    GLCD_RW = 1;             //Read
    GLCD_RS = 1;             //Data
    GLCD_CS1 = (column>63);
    GLCD_CS2 = !GLCD_CS1;         //Disable/Enable CS2
    delay_us(1);        //tasu
    GLCD_EN = 1;             //Latch RAM data into ouput register
    delay_us(1);        //twl + tf

    //Dummy read
    GLCD_EN = 0;             //Low Enable
    delay_us(5);
    GLCD_EN = 1;             //latch data from output register to data bus
    delay_us(1);             //tr + td(twh)

    read_data = GLCD_Data;    //Input data
    GLCD_EN = 0;             //Low Enable to remove data from the bus
    delay_us(1);        //tdhr
    GLCD_Dir = 0x00;     //Output again
    return read_data;
}

 void GLCD_Clrln(unsigned short ln)
 {
    int i;
    GOTO_XY(0,ln);      //At start of line of left side
    GOTO_XY(64,ln);     //At start of line of right side (Problem)
    GLCD_CS1 = 0;
    for(i=0;i<65;i++)
    GLCD_Write(0);
 }

//-------------------------

void GLCD_CLR()
{
   unsigned short m;
   for(m=0;m<8;m++){
    GLCD_Clrln(m);
   }
}

void Draw_Point(unsigned short x,unsigned short y, unsigned short color)
{
    unsigned short Col_Data;;
    GOTO_XY(x,(y/8));
    switch (color)
    {
        case 0:         //Light spot
            Col_Data = ~(1<<(y%8)) & GLCD_Read(x);
        break;
        case 1:         //Dark spot
            Col_Data = (1<<(y%8)) | GLCD_Read(x);
        break;
    }
    GOTO_XY(x,(y/8));
    GLCD_Write(Col_Data);
}

void main() {
  unsigned short u, v;
  ANSEL  = 0;                  // Configure AN pins as digital
  ANSELH = 0;
  C1ON_bit = 0;                // Disable comparators
  C2ON_bit = 0;
  TRISD = 0x00;
  TRISB = 0x00;
  PORTB = 0x00;
  PORTD = 0x00;
  GLCD_CS1 = 1;                // De-Activate both chips
  GLCD_CS2 = 1;
  GLCD_RST = 1;
  GLCD_ON();
  GLCD_CLR();
  Set_Start_Line(0);
  do {
     
     for(u=0; u<64; u+=6)
      for (v=0; v<128; v+=2)
      Draw_Point(v, u, 1);
      delay_ms(1000);
      GLCD_CLR();
      delay_ms(1000);

  } while(1);
}