/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/interpol.cpp_v   1.5   06 Oct 2014 06:35:16   AnPawar  $ */
/****************************************************************************/

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/interpol.cpp_v  $
 * 
 *    Rev 1.5   06 Oct 2014 06:35:16   AnPawar
 * GetInterpolatedSINT32() function removed
 * 
 *    Rev 1.4   11 Jun 2014 11:36:18   rjamloki
 * Removed commented code
 * 
 *    Rev 1.3   05 Mar 2014 13:56:26   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.2   03 Jan 2014 08:45:30   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/

/*
  --------------------------- MODULE DESCRIPTION ---------------------------

 Module name: Table Interpolation

 Filename:    Interpol.c

 Function Name: Calibration code

          Written by:   Bill Truchsess
                Date:   04-15-96
            Language:   "C/ASM"

  ----------------------------- DESCRIPTION --------------------------------

   This module includes a support function for the sensor calibration.

  ----------------------------- PSEUDO CODE --------------------------------


  ---------------------------- LOCAL_EQUATES -------------------------------*/
//#define INCLUDE_UNIT_TEST   

/*------------------------------ INCLUDES ----------------------------------*/
#include "portable.h"
#include "interpol.h"

/*
---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/



/*-------------------------- PRIVATE GLOBAL DATA ---------------------------*/



/*-------------------------------- CODE ------------------------------------*/

SINT16 GetInterpolatedSINT16(SINT16 table_vals[], UINT16 data_in)
{
   //TBD
//   asm(" MOVEA.L   $8(A6),A0 "); /* Get the 1st parameter */
//   asm(" MOVE.W    $E(A6),D0 "); /* Get the 2nd paramater */
//   asm(" TBLS.W      (A0),D0   ");
	SINT16 Y;
	UINT16 X;

	X = data_in >> 8;
	Y = (((table_vals[X + 1] - table_vals[X]) * (data_in & 0xFF) + 128) / 256) + table_vals[X];

	return Y;
}

UINT16 GetInterpolatedUINT16(UINT16 table_vals[], UINT16 data_in)
{
	UINT16 Y;
	UINT16 X;

	X = data_in >> 8;
	Y = (((table_vals[X + 1] - table_vals[X]) * (data_in & 0xFF) + 128) / 256) + table_vals[X];

	return Y;
}

UINT16 GetInterpolatedUINT32(UINT32 table_vals[], UINT16 data_in)
{
	UINT32 Y;
	UINT16 X;

	X = data_in >> 8;
	Y = (((table_vals[X + 1] - table_vals[X]) * (data_in & 0xFF) + 128) / 256) + table_vals[X];

	return (UINT16) Y;
}

/* Include for Unit test */
#ifdef INCLUDE_UNIT_TEST
#include "g:\332\ut\interpol.ut"
#endif
/* End of include for unit test */


