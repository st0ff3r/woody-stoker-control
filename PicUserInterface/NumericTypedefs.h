		/************************************************************/
		/*															*/
		/*		      Typedefs for BYTE, WORD, DWORD,...			*/
		/*															*/
		/************************************************************/


typedef unsigned char   byte;           // 8-bit
typedef unsigned int    word;           // 16-bit
typedef short long		shortlong;		// 24-bit
typedef unsigned long   dword;          // 32-bit


//
// data type for a byte with individual bits addressable
//
typedef union _BYTE
{	byte _byte;
	
    struct
    {   unsigned b0:1;
        unsigned b1:1;
        unsigned b2:1;
        unsigned b3:1;
        unsigned b4:1;
        unsigned b5:1;
        unsigned b6:1;
        unsigned b7:1;
    };
} BYTE;



//
// data type for a word (2 bytes) with individual bytes and bits addressable
//
typedef union _WORD
{	word _word;
	
    struct
    {   byte byte0;
        byte byte1;
    };
    
    struct
    {   BYTE Byte0;
        BYTE Byte1;
    };
    
    struct
    {   BYTE LowB;
        BYTE HighB;
    };
    
    struct
    {   byte v[2];
    };
} WORD;



//
// data type for a shortlong (3 bytes) with individual bytes addressable
//
typedef union _SHORTLONG
{	shortlong _shortlong;
	
    struct
    {   byte byte0;
        byte byte1;
        byte byte2;
    };
    
    struct
    {   BYTE Byte0;
        BYTE Byte1;
        BYTE Byte2;
    };
    
    struct
    {   byte v[3];
    };
} SHORTLONG;



//
// data type for a dword (4 bytes) with individual bytes and bits addressable
//
typedef union _DWORD
{	dword _dword;
	
    struct
    {   byte byte0;
        byte byte1;
        byte byte2;
        byte byte3;
    };
    
    struct
    {   word word0;
        word word1;
    };
    
    struct
    {   BYTE Byte0;
        BYTE Byte1;
        BYTE Byte2;
        BYTE Byte3;
    };
    
    struct
    {   WORD Word0;
        WORD Word1;
    };
    
    struct
    {   byte v[4];
    };

} DWORD;



//
// data type for a pointer (16 bit) with individual bytes addressable
//
typedef union _POINTER
{   word _word;

	struct
    {   byte bLow;
        byte bHigh;
    };
    
    byte* bRam;
    
    word* wRam;
    
    rom byte* bRom;
    
    rom word* wRom;
} POINTER;



//
// define TRUE as 1, FALSE as 0, and the BOOL datatype
//
typedef enum _BOOL { FALSE = 0, TRUE } BOOL;



//
// macros for addressing individual bytes from arrays of char
//
#define LSB(a)      	((a).v[0])
#define MSB(a)      	((a).v[1])
#define LOWER_LSB(a)    ((a).v[0])
#define LOWER_MSB(a)    ((a).v[1])
#define UPPER_LSB(a)    ((a).v[2])
#define UPPER_MSB(a)    ((a).v[3])


/* ----------------------- End of NumericTypedefs.h --------------------- */
