		/************************************************************/
		/*															*/
		/*			     Header file for GeneralFuncs.c				*/
		/*															*/
		/************************************************************/

//
// string types
//
#define ROM_STRING 0
#define RAM_STRING 1


/* ------------------------------------------------------------------------ */
/*						  Public function declarations			  			*/
/* ------------------------------------------------------------------------ */

ram char *StringToRam(rom char *, ram char *);
unsigned int EatSpaceChars(char *S, byte, unsigned int);
char GetCharFromString(char *, byte, unsigned int);
ram char *ConvertSignedIntToString(int, ram char *);
void DelayMS(unsigned int);
void Delay100us(void);

/* ------------------------- End of GeneralFuncs.h ------------------------ */
