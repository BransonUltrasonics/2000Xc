/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/portable.h_v   1.6   Nov 06 2017 15:44:44   RJamloki  $
*/
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995,96, 2009        */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/portable.h_v  $
 * 
 *    Rev 1.6   Nov 06 2017 15:44:44   RJamloki
 * Added more defines for hard code numbers sequences 
 * 
 *    Rev 1.5   Jun 07 2017 11:56:30   RJamloki
 * Added defines counters
 * 
 *    Rev 1.4   26 Mar 2014 12:44:06   rjamloki
 * BOOLEAN is now typedef  UINT32 BOOLEAN
 * 
 *    Rev 1.3   05 Mar 2014 13:57:24   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.1   05 Jun 2013 08:39:32   amaurya
 * Initial revision 2.
Revision 1.3  2013/05/24 23:12:02  Ellery
*** empty log message ***

 * 
 *    Rev 1.0   03 Apr 2013 06:56:32   amaurya
 * Initial revision.
 *
 */

#ifndef PORTABLE_H_
#define PORTABLE_H_

typedef  unsigned char       UINT8;           /* 8-bit  unsigned quantity  */
typedef  UINT8               BYTE;            /* 8-bit  unsigned quantity  */
typedef  unsigned short int  UINT16;          /* 16-bit unsigned quantity  */
typedef  unsigned long int   UINT32;          /* 32-bit unsigned quantity  */
typedef  char                SINT8;           /* 8-bit  signed quantity    */
typedef  signed short int    SINT16;          /* 16-bit signed quantity    */
typedef  signed long int     SINT32;          /* 32-bit signed quantity    */
typedef  signed long int     SIZE_T;          /* signed size difference    */
typedef  unsigned long int   PTRDIFF_T;       /* unsigned size difference  */
typedef  signed int          FPOS_T;          /* signed size difference    */
typedef  float               FLOAT;           /* small float               */
typedef  float               DFLOAT;          /* medium float              */
typedef unsigned char   UCHAR;
typedef unsigned short  USHORT;
typedef unsigned int    UINT;
typedef unsigned long   ULONG;
/* Defined to standardize string definitions for the menu structures  */
/* incorporating foreign languages                                    */
typedef  char                STR;
typedef  UINT32 BOOLEAN;

#define  NULL_BYTE      ((UINT8)NULL)         /* null value                */
#define  NULL_PTR       0L                    /* null value                */
#define  NULL_FUNC_PTR  0L                    /* null value                */
#define  FOREVER        1


#define OFF 0
#define ON 1
//{
//   FALSE = 0,
//   TRUE	 = 1
//   } BOOLEAN;                                /* system BOOLEANean definition */

#ifdef   FALSE
#undef   FALSE
#endif
#define FALSE  (0)

#ifdef   TRUE
#undef   TRUE
#endif
#define  TRUE  (1)

/*----------------------------*/
/* Bit manipulation patterns  */
/*----------------------------*/

/* BYTEWISE, WORDWISE or LONGWISE 	*/
#define BIT(x) (1 << x)
/*----------------------------*/
/* Bit manipulation patterns  */
/*----------------------------*/

/* BYTEWISE, WORDWISE or LONGWISE   */

#define BIT0    0x1
#define BIT1    0x2
#define BIT2    0x4
#define BIT3    0x8
#define BIT4    0x10
#define BIT5    0x20
#define BIT6    0x40
#define BIT7    0x80
            /* WORDWISE or LONGWISE       */
#define BIT8    0x100
#define BIT9    0x200
#define BIT10   0x400
#define BIT11   0x800
#define BIT12   0x1000
#define BIT13   0x2000
#define BIT14   0x4000
#define BIT15   0x8000
            /* LONGWISE          */
#define BIT16   0x10000
#define BIT17   0x20000
#define BIT18   0x40000
#define BIT19   0x80000
#define BIT20   0x100000
#define BIT21   0x200000
#define BIT22   0x400000
#define BIT23   0x800000
#define BIT24   0x1000000
#define BIT25   0x2000000
#define BIT26   0x4000000
#define BIT27   0x8000000
#define BIT28   0x10000000
#define BIT29   0x20000000
#define BIT30   0x40000000
#define BIT31   0x80000000

#define ZERO      0
#define ONE       1
#define TWO       2
#define THREE     3
#define FOUR      4
#define FIVE      5
#define SIX       6
#define SEVEN     7
#define EIGHT     8
#define NINE      9
#define TEN       10
#define ELEVEN    11
#define TWELVE    12
#define THIRTEEN  13
#define FOURTEEN  14
#define FIFTEEN   15
#define SIXTEEN   16
#define SEVENTEEN 17
#define EIGHTEEN  18
#define NINETEEN  19
#define TWENTY    20

#endif /* PORTABLE_H_ */
