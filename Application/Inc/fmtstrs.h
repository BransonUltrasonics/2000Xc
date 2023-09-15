/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/fmtstrs.h_v   1.4   28 Nov 2014 07:55:44   rjamloki  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name:

   Filename: menu.h

   Function name:

 --------------------------------- REVISIONS --------------------------------*/


/*
 ------------------------------- DESCRIPTION ---------------------------------
*/ 


/*
 ------------------------------ INCLUDE FILES --------------------------------
*/

/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/

void FormatTitleStr( SINT8 String[], SINT8 NumDisplayChar1, SINT32 Value1,
                     SINT8 NumDisplayChar2, SINT32 Value2);

void FormatStr1( SINT8 String[], SINT8 StringStart, SINT8 NumDisplayChar,
                 SINT32 Value, SINT8 Delimiter);

void FormatStr2( SINT8 String[], SINT8 StringStart, SINT8 Delimiter1,
                 SINT8 NumDisplayChar1, SINT32 Value1, SINT8 Delimiter2,
                 SINT8 NumDisplayChar2, SINT32 Value2);

void FormatBargraphStr(SINT8 String1[], SINT8 String2[], UINT8 DisplayType);

void FormatTimeStr( SINT8 String[], SINT8 Delimiter1, UINT8 NumDisplayChar1,
                    SINT32 Hour, SINT8 Delimiter2, UINT8 NumDisplayChar2,
                    SINT32 Minute );

void FormatDateStr( SINT8 String[], SINT8 Delimiter1, UINT8 NumDisplayChar1,
                    SINT32 Month, SINT8 Delimiter2, UINT8 NumDisplayChar2,
                    SINT32 Day, SINT8 Delimiter3, UINT8 NumDisplayChar3,
                    SINT32 Year );

void FormatValue( SINT8 String[], UINT8 TotalChar, UINT8 NumDisplayChar1, SINT32 Value,
                  SINT8 Delimiter, UINT8 NumDisplayChar2);

void FormatAlarmStr( SINT8 *String, SINT8 NumDisplayChar, SINT32 Value);

void FormatNAStr( SINT8 String[] );

void FormatSignedInt( SINT8 String[], UINT8 LastChar, UINT8 NumDisplayChar,
 SINT32 Value );
