/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/fmtstrs.cpp_v   1.8   11 Dec 2014 08:35:04   AnPawar  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/fmtstrs.cpp_v  $
 * 
 *    Rev 1.8   11 Dec 2014 08:35:04   AnPawar
 * removed nested comment.
 * 
 *    Rev 1.7   26 Sep 2014 03:14:24   rjamloki
 * Removed psos references
 * 
 *    Rev 1.6   21 May 2014 10:47:54   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.5   21 May 2014 03:02:14   rjamloki
 * extern variables clean up
 * 
 *    Rev 1.4   05 Mar 2014 13:56:22   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:34   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:24   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION ----------------------------

   Module name: fmtstrs

   Filename: fmtstrs.c

   Function name: void FormatTitleStr();
                  void FormatStr1();
                  void FormatStr2();


 ------------------------------ INCLUDE FILES --------------------------------
*/

#include "portable.h"
#include "menu.h"
#include "preset.h"

/*
 ------------------------------- EXTERNAL DATA -------------------------------
*/

/*
 ------------------------------- LOCAL DEFINES -------------------------------
*/
                                   
/*
 ---------------------------- LOCAL TYPE DECLARATIONS ------------------------
*/

/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

/*
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/


/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/



/*
 ---------------------------------- CODE -------------------------------------
*/

void FormatStr1( SINT8 String[], SINT8 StringStart, SINT8 NumDisplayChar,
                 SINT32 Value, SINT8 Delimiter)
{
   UINT8 StringEnd = LINESIZE -1;
   UINT8 FilIndex = StringStart;
   SINT32 Temp;

   while(FilIndex < LINESIZE)
      String[FilIndex++] = FILLCHAR;

   if(Value != 0)
   {
      while(NumDisplayChar > 0 && Value != 0)
      {
           Temp = Value % 10;
         String[StringEnd--] = Temp + 0x30;
         Value /= 10;
         NumDisplayChar--;
      }
   }
   else
        String[StringEnd] = 0x30;   /* Display zero character */
   if(Delimiter != 0)
      String[StringStart] = Delimiter;

}



void FormatStr2( SINT8 String[], SINT8 StringStart, SINT8 Delimiter1,
                 SINT8 NumDisplayChar1, SINT32 Value1, SINT8 Delimiter2,
                 SINT8 NumDisplayChar2, SINT32 Value2)
{
   UINT8 StringEnd = LINESIZE -1;
   UINT8 FillIndex = StringStart;
   SINT32 Temp;

   while(FillIndex < LINESIZE)
      String[FillIndex++] = FILLCHAR;

   while(NumDisplayChar2 != 0)
   {
        Temp = Value2 % 10;
        String[StringEnd--] = Temp + 0x30;
        Value2 /= 10;
      NumDisplayChar2--;
   }

   if(Delimiter2 != 0)
    String[StringEnd--] = Delimiter2;

   if(Value1 != 0)
   {
      while(NumDisplayChar1 != 0 && Value1 != 0)
      {
           Temp = Value1 % 10;
        String[StringEnd--] = Temp + 0x30;
            Value1 /= 10;
         NumDisplayChar1--;
      }
   }
   else
        String[StringEnd--] = 0x30;

   if(Delimiter1 != 0)
    String[StringStart] = Delimiter1;

}

void FormatTimeStr1( SINT8 String[], SINT8 Delimiter1, UINT8 NumDisplayChar1,
                    SINT32 Hour, SINT8 Delimiter2, UINT8 NumDisplayChar2,
                    SINT32 Minute )
{
   SINT32 Temp;
   UINT8 StringEnd;
   
   StringEnd = LINESIZE -1;
   while(NumDisplayChar2 != 0)
   {
        Temp = Minute % 10;
        String[StringEnd--] = Temp + 0x30;
        Minute /= 10;
        NumDisplayChar2--;
   }

   if(Delimiter2 != 0)
      String[StringEnd--] = Delimiter2;
   while(NumDisplayChar1 != 0)
   {
        Temp = Hour % 10;
        String[StringEnd--] = Temp + 0x30;
        Hour /= 10;
        NumDisplayChar1--;
   }
   if(Delimiter1 != 0)
      String[StringEnd--] = Delimiter1;
}

void FormatDateStr1( SINT8 String[], SINT8 Delimiter1, UINT8 NumDisplayChar1,
                    SINT32 Month, SINT8 Delimiter2, UINT8 NumDisplayChar2,
                    SINT32 Day, SINT8 Delimiter3, UINT8 NumDisplayChar3,
                    SINT32 Year )
{
   SINT32 Temp;
   UINT8 StringEnd;

   StringEnd = LINESIZE -1;
   while(NumDisplayChar3 != 0)
   {
        Temp = Year % 10;
        String[StringEnd--] = Temp + 0x30;
        Year /= 10;
        NumDisplayChar3--;
   }

   if(Delimiter3 != 0)
      String[StringEnd--] = Delimiter3;

   while(NumDisplayChar2 != 0)
   {
        Temp = Day % 10;
           String[StringEnd--] = Temp + 0x30;
        Day /= 10;
        NumDisplayChar2--;
   }

   if(Delimiter2 != 0)
      String[StringEnd--] = Delimiter2;

   while(NumDisplayChar1 != 0)
   {
        Temp = Month % 10;
        String[StringEnd--] = Temp + 0x30;
        Month /= 10;
        NumDisplayChar1--;
   }
   
   String[StringEnd--] = ' ';   /* space character */

   if(Delimiter1 != 0)
      String[StringEnd--] = Delimiter1;
}
