		/************************************************************/
		/*															*/
		/*		     	 General purpose functions					*/
		/*															*/
		/************************************************************/

#include <p18cxxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "NumericTypedefs.h"
#include "GeneralFuncs.h"


//
// performance and memory used of different methods:
//
//	strcpypgm2ram(SBuf, "reifel");
//		Including:	51 bytes
//		Calling: 	23 bytes
//		Execute:	9.2us
//
// StringToRam("Reifel", SBuf);
//		Including:	49 bytes
//		Calling: 	18 bytes
//		Execute:	23us
//
// sprintf(SBuf, "Reifel");
//		Including:	1915 bytes
//		Calling: 	26 bytes
//		Execute:	96us
//
// itoa(1234, SBuf);
//		Including:	169 bytes
//		Calling: 	16 bytes
//		Execute:	90us
//
// btoa(123, SBuf);
//		Including:	142 bytes
//		Calling: 	13 bytes
//		Execute:	36us
//
// sprintf(SBuf, "%d", 1234);
//		Including:	1918 bytes
//		Calling: 	27 bytes
//		Execute:	740us
//	
// SBufPtr = SBuf;
// SBufPtr = StringToRam("Reifel:  ", SBufPtr);
// itoa(1234, SBufPtr);
//		Execute:	126us
//
// 	sprintf(SBuf, "Reifel:  %d", 1235);
//		Execute:	860us
//


/* ------------------------------------------------------------------------ */
/*						  	Public general functions 		 				*/
/* ------------------------------------------------------------------------ */
#pragma code


//
// copy a string stored in ROM to a RAM buffer
//		Enter:	Src -> source string in ROM
//				Dst -> RAM buffer to copy string to
//		Exit:	pointer to termination zero in Dst buffer returned
//
ram char *StringToRam(rom char *Src, ram char *Dst)
{	char C;
	
	do
	{	C = *Src++;
		*Dst++ = C;
	} while(C);
	
	return(Dst - 1);
}



//
// scan through a string to find the first non-space character
//		Enter:	S -> string to find line break
//				StringType = ROM_STRING or RAM_STRING
//				StartIdx = index of starting point in string
//
unsigned int EatSpaceChars(char *S, byte StringType, unsigned int StartIdx)
{	while (GetCharFromString(S, StringType, StartIdx) == ' ')
		StartIdx++;				
	
	return(StartIdx);
}



//
// get the character in the string at the start index
//		Enter:	S -> string to find line break
//				StringType = ROM_STRING or RAM_STRING
//				StartIdx = index of starting point in string
//
char GetCharFromString(char *S, byte StringType, unsigned int StartIdx)
{	if (StringType == ROM_STRING)
		return(((rom char *)S)[StartIdx]);	

	else
		return(((ram char *)S)[StartIdx]);	
}



//
// convert a signed integer to a ASCII string
//		Enter:	i = interger to convert
//				Dst -> RAM buffer store string in
//		Exit:	pointer to termination zero in Dst buffer returned
//
ram char *ConvertSignedIntToString(int i, ram char *Dst)
{	//
	// convert the string to text
	//
	itoa(i, Dst);
	
	//
	// find the end of the string
	//
	while(*Dst++)
		;
	
	return(Dst - 1);
}



//
// busy wait for n ms
//		Enter:	DelayTimeMS = number of milliseconds to delay (1 - 255ms)
//
void DelayMS(unsigned int DelayTimeMS)
{	byte i;

	do
	{	for (i = 0; i < 10; i++)				// delay 1 ms
			Delay100us();
	
		DelayTimeMS--;
	} while(DelayTimeMS != 0);
}



//
// busy wait for 100us, requires the PIC running with a 40Mhz clock
//
void Delay100us(void)
{	register unsigned char DelayCounter;

	//
	// delay 100us, subtract 4 for the time required to call and return
	//		
	DelayCounter = 250 - 4;						// set counter for 40Mhz clock
	do							
	{	DelayCounter--;							// DECF 0xfdf, F, ACCESS (1)
	} while(DelayCounter);						// MOVF 0xfdf, W, ACCESS (1),   BNZ 0xe4 (2)
}

/* ------------------------- End of GeneralFuncs.c ------------------------ */
