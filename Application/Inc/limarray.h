/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/limarray.h_v   1.14   08 Apr 2015 13:51:34   AnPawar  $ */
#ifndef _LIMARRAY_H
#define _LIMARRAY_H

/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/*                                                                          */
/*   Module name:   limarray                                                  */
/*                                                                          */
/*   Filename:      Alimarray.h                                               */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/limarray.h_v  $
 * 
 *    Rev 1.14   08 Apr 2015 13:51:34   AnPawar
 * Welder Control Level Limits array and PARAMNUM enum changed for Pressure Stepping.
 * 
 *    Rev 1.13   11 Mar 2015 09:22:24   amaurya
 * PSETUPLIMIT added to parameterControlLevel[].
 * 
 *    Rev 1.12   05 Feb 2015 07:09:52   amaurya
 * PUSBFLAG variable added to PARAMNUM enum to display USB golbal flag status in WeldSetup PDF.
 * 
 *    Rev 1.11   21 Jan 2015 09:47:28   amaurya
 * controlLevel array changed for Preset Revision ,Validated/locked and New IDs addedto enum PARAMNUM.
 * 
 *    Rev 1.10   28 Nov 2014 07:55:52   rjamloki
 * Warning fix.
 * 
 *    Rev 1.9   10 Nov 2014 04:40:32   AnPawar
 * controlLevel array changed for downspeed reject alaram.
 * 
 *    Rev 1.8   20 Oct 2014 06:39:20   AnPawar
 * controlLevel array changed for all limits in level D and level C.
 * 
 *    Rev 1.7   11 Sep 2014 11:24:10   rjamloki
 * Fixed controlLevel array for level c
 * 
 *    Rev 1.6   05 Sep 2014 04:12:24   rjamloki
 * Added column for level C in default parameter control level array
 * 
 *    Rev 1.5   18 Aug 2014 01:51:02   rjamloki
 * Added weld trigger type in parameterControlLevel table
*/ 



#define MAXLEVELS       6
#define MAXLEVELL       12
#define MAXLIMITS       19
#define MAXWELDMODES    7

enum PRINTFLAG{             /* Checked to see if should be printed   */
   ACTDF,                   // Print if AED|AOD|AEF|AOF
   NOTAVAIL,                /* not printed                           */
   AVAIL,                   /* printed                               */
   AVAILLE,                 /* printed when encoder present          */
   TMODONLY };              /* Print while in TimeMode Only */




extern UINT16 ControlLevelLimit(UINT16);
extern UINT16 CheckIfPrintable(UINT16);


// Welder Control Level Limits
const UINT16 controlLevel[MAXLEVELL][MAXLIMITS][MAXWELDMODES] = {
		// Suspect Limits
		// Time    Energy    Pk. Pwr.  Collapse Absolute Grd.Detect  Cont.
		// Mode     Mode      Mode       Mode     Mode      Mode     Mode
	   {  // SUSPECT CONTROL LEVEL t (old level #1)
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*0  Time + Limit			*/
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*1  Time - Limit          */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*2  Energy + Limit        */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*3  Energy - Limit        */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*4  Power + Limit         */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*5  Power - Limit         */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*6  Collapse + Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*7  Collapse - Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*8  Absolute + Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*9  Absolute - Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*10 Trig. Dist + Limit    */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*11 Trig. Dist - Limit    */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*12 Max Force + Limit     */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*13 Max Force - Limit     */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*14 Freq. + Limit         */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*15 Freq. - Limit         */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*16 Max Force +/- R Limit */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*17 Downspeed + Limit     */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL},  /*18 Downspeed - Limit     */
	   },

	// Suspect Limits
	//   Time     Energy   Pk. Pwr. Collaps  Absolute   Gr. Det.    Cont.
	//   Mode     Mode     Mode      Mode    Mode        Mode        Mode

	   {  // SUSPECT CONTROL LEVEL e (old level #2 no longer used)

		 {NOTAVAIL, AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, AVAIL,    NOTAVAIL}, /*0  Time + Limit			*/
		 {NOTAVAIL, AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, AVAIL,    NOTAVAIL}, /*1  Time - Limit          */
		 {AVAIL,    AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*2  Energy + Limit        */
		 {AVAIL,    AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*3  Energy - Limit        */
		 {AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*4  Power + Limit         */
		 {AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*5  Power - Limit         */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*6  Collapse + Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*7  Collapse - Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*8  Absolute + Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*9  Absolute - Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*10 Trig. Dist + Limit    */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*11 Trig. Dist - Limit    */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*12 Max Force + Limit     */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*13 Max Force - Limit     */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*14 Freq. + Limit         */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*15 Freq. - Limit         */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*16 Max Force +/- R Limit */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*17 Downspeed + Limit     */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}  /*18 Downspeed - Limit     */
	   },

	// Suspect Limits
	//	Time     Energy   Pk. Pwr. Collaps    Absolute  Gr. Det.   Cont
	//	Mode     Mode     Mode     Mode       Mode      Mode       Mode

	     { // SUSPECT CONTROL LEVEL ea (old level #3 and a)

		 {NOTAVAIL, AVAIL,    AVAIL,    AVAILLE, AVAILLE,  AVAIL,    NOTAVAIL}, /*0  Time + Limit		   */
		 {NOTAVAIL, AVAIL,    AVAIL,    AVAILLE, AVAILLE,  AVAIL,    NOTAVAIL}, /*1  Time - Limit          */
		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE,  NOTAVAIL, NOTAVAIL}, /*2  Energy + Limit        */
		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE,  NOTAVAIL, NOTAVAIL}, /*3  Energy - Limit        */
		 {AVAIL,    AVAIL,    NOTAVAIL, AVAILLE, AVAILLE,  NOTAVAIL, NOTAVAIL}, /*4  Power + Limit         */
		 {AVAIL,    AVAIL,    NOTAVAIL, AVAILLE, AVAILLE,  NOTAVAIL, NOTAVAIL}, /*5  Power - Limit         */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL,NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*6  Collapse + Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL,NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*7  Collapse - Limit      */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, NOTAVAIL, AVAILLE,  NOTAVAIL}, /*8  Absolute + Limit      */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, NOTAVAIL, AVAILLE,  NOTAVAIL}, /*9  Absolute - Limit      */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE,  NOTAVAIL, NOTAVAIL}, /*10 Trig. Dist + Limit    */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE,  NOTAVAIL, NOTAVAIL}, /*11 Trig. Dist - Limit    */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL,NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*12 Max Force + Limit     */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL,NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*13 Max Force - Limit     */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL,NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*14 Freq. + Limit         */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL,NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*15 Freq. - Limit         */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL,NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*16 Max Force +/- R Limit */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL,NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*17 Downspeed + Limit     */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL,NOTAVAIL, NOTAVAIL, NOTAVAIL}  /*18 Downspeed - Limit     */
	   },

	// Suspect Limits
	//	Time     Energy   Pk. Pwr. Collaps    Absolute  Gr. Det.   Cont
	//	Mode     Mode     Mode     Mode       Mode      Mode       Mode

	   { // SUSPECT  CONTROL LEVEL d (old level #4 )

		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL}, /*0  Time + Limit	      */
		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL}, /*1  Time - Limit          */
		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL}, /*2  Energy + Limit        */
		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL}, /*3  Energy - Limit        */
		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL}, /*4  Power + Limit         */
		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL}, /*5  Power - Limit         */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, AVAILLE,  NOTAVAIL}, /*6  Collapse + Limit      */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, AVAILLE,  NOTAVAIL}, /*7  Collapse - Limit      */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, AVAILLE,  NOTAVAIL}, /*8  Absolute + Limit      */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, AVAILLE,  NOTAVAIL}, /*9  Absolute - Limit      */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL}, /*10 Trig. Dist + Limit    */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL}, /*11 Trig. Dist - Limit    */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL}, /*12 Max Force + Limit     */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL}, /*13 Max Force - Limit     */
		 {AVAIL ,   AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL}, /*14 Freq. + Limit         */
		 {AVAIL ,   AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL ,   NOTAVAIL}, /*15 Freq. - Limit         */
		 {ACTDF ,   ACTDF,    ACTDF,    ACTDF  , ACTDF  , ACTDF ,   ACTDF  },  /*16	Max Force +/- R Limit */
		 {AVAIL ,   AVAIL,    AVAIL,    AVAILLE, AVAILLE ,AVAIL,    NOTAVAIL}, /*17 Downspeed + Limit     */
		 {AVAIL ,   AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL ,   NOTAVAIL}  /*18 Downspeed - Limit     */
		},

	// Suspect Limits
	//	Time     Energy   Pk. Pwr. Collaps    Absolute  Gr. Det.   Cont
	//	Mode     Mode     Mode     Mode       Mode      Mode       Mode

	   { // SUSPECT CONTROL LEVEL f (old level #5 (EP))

		{NOTAVAIL, AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL}, /*0  Time + Limit			 */
		{NOTAVAIL, AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL}, /*1  Time - Limit          */
		{AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL}, /*2  Energy + Limit        */
		{AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL}, /*3  Energy - Limit        */
		{AVAIL,    AVAIL,    NOTAVAIL, AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL}, /*4  Power + Limit         */
		{AVAIL,    AVAIL,    NOTAVAIL, AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL}, /*5  Power - Limit         */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL}, /*6  Collapse + Limit      */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, NOTAVAIL, NOTAVAIL}, /*7  Collapse - Limit      */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, NOTAVAIL,AVAILLE,  NOTAVAIL}, /*8  Absolute + Limit      */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, NOTAVAIL,AVAILLE,  NOTAVAIL}, /*9  Absolute - Limit      */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL}, /*10 Trig. Dist + Limit    */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL}, /*11 Trig. Dist - Limit    */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL}, /*12 Max Force + Limit     */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL}, /*13 Max Force - Limit     */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, AVAILLE,  NOTAVAIL}, /*14 Freq. + Limit         */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, AVAILLE,  NOTAVAIL}, /*15 Freq. - Limit         */
	    {ACTDF , ACTDF   , ACTDF   , ACTDF   , ACTDF   , ACTDF   , ACTDF   }, /*16 Max Force +/- R Limit */
	    {AVAIL ,   AVAIL,    AVAIL,    AVAILLE, AVAILLE , AVAIL,   NOTAVAIL}, /*17 Downspeed + Limit     */
	   	{AVAIL ,   AVAIL,    AVAIL,    AVAILLE, AVAILLE , AVAIL ,  NOTAVAIL}  /*18 Downspeed - Limit     */
	   },

	   // Suspect Limits
	   //	Time     Energy   Pk. Pwr. Collaps    Absolute  Gr. Det.   Cont
	   //	Mode     Mode     Mode     Mode       Mode      Mode       Mode

	      { // SUSPECT  CONTROL LEVEL c (old level #4 )

	    {AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL}, /*0  Time + Limit			 */
	    {AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL}, /*1  Time - Limit          */
	    {AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL}, /*2  Energy + Limit        */
	    {AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL}, /*3  Energy - Limit        */
	    {AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL}, /*4  Power + Limit         */
	    {AVAIL,    AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL}, /*5  Power - Limit         */
	    {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, AVAILLE,  NOTAVAIL}, /*6  Collapse + Limit      */
	    {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, AVAILLE,  NOTAVAIL}, /*7  Collapse - Limit      */
	    {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, AVAILLE,  NOTAVAIL}, /*8  Absolute + Limit      */
	    {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, AVAILLE,  NOTAVAIL}, /*9  Absolute - Limit      */
	    {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL}, /*10 Trig. Dist + Limit    */
	    {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL}, /*11 Trig. Dist - Limit    */
	    {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL}, /*12 Max Force + Limit     */
	    {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE, AVAILLE, ACTDF   , NOTAVAIL}, /*13 Max Force - Limit     */
	    {AVAIL ,   AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL,    NOTAVAIL}, /*14 Freq. + Limit         */
	    {AVAIL ,   AVAIL,    AVAIL,    AVAILLE, AVAILLE, AVAIL ,   NOTAVAIL}, /*15 Freq. - Limit         */
	    {ACTDF   , ACTDF   , ACTDF   , ACTDF   , ACTDF   , ACTDF,  ACTDF   }, /*16 Max Force +/- R Limit */
	    {AVAIL ,   AVAIL,    AVAIL,    AVAILLE , AVAILLE, AVAIL,   NOTAVAIL}, /*17 Downspeed + Limit     */
	   	{AVAIL ,   AVAIL,    AVAIL,    AVAILLE , AVAILLE, AVAIL ,  NOTAVAIL}  /*18 Downspeed - Limit     */
	      },

		// Reject Limits
		//  Time     Energy   Pk. Pwr.  Collaps   Absolute   Gr. Det.   Cont.
		//  Mode     Mode     Mode      Mode      Mode        Mode      Mode

		   {  // REJECT CONTROL LEVEL t (old level #1)

		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*0  Time + Limit			  */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*1  Time - Limit            */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*2  Energy + Limit          */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*3  Energy - Limit          */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*4  Power + Limit           */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*5  Power - Limit           */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*6  Collapse + Limit        */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*7  Collapse - Limit        */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*8  Absolute + Limit        */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*9  Absolute - Limit        */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*10 Trig. Dist + Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*11 Trig. Dist - Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*12 Max Force + Limit       */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*13 Max Force - Limit       */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*14 Freq. + Limit           */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*15 Freq. - Limit           */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*16	Max Force +/- R Limit */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*17 Downspeed + Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL } /*18 Downspeed - Limit      */
		   },

		// Reject Limits
		//   Time     Energy   Pk. Pwr. Collaps  Absolute   Gr. Det.    Cont.
		//   Mode     Mode     Mode      Mode    Mode        Mode        Mode

		   {  // REJECT CONTROL LEVEL e (old level #2, no longer used)

		 {NOTAVAIL, AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, AVAIL,    NOTAVAIL}, /*0  Time + Limit			*/
		 {NOTAVAIL, AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, AVAIL,    NOTAVAIL}, /*1  Time - Limit          */
		 {AVAIL,    AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*2  Energy + Limit        */
		 {AVAIL,    AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*3  Energy - Limit        */
		 {AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*4  Power + Limit         */
		 {AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*5  Power - Limit         */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*6  Collapse + Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*7  Collapse - Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*8  Absolute + Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*9  Absolute - Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*10 Trig. Dist + Limit    */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*11 Trig. Dist - Limit    */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*12 Max Force + Limit     */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*13 Max Force - Limit     */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*14 Freq. + Limit         */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*15 Freq. - Limit         */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*16 Max Force +/- R Limit */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*17 Downspeed + Limit     */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}  /*18 Downspeed - Limit     */
		 },

		// Reject Limits
		//	Time     Energy   Pk. Pwr. Collaps    Absolute  Gr. Det.   Cont
		//	Mode     Mode     Mode     Mode       Mode      Mode       Mode

			 { // REJECT CONTROL LEVEL ea (old level #3 and a)

		 {NOTAVAIL, AVAIL,    AVAIL,    AVAIL,    AVAIL,    AVAIL,    NOTAVAIL}, /*  Time + Limit			*/
		 {NOTAVAIL, AVAIL,    AVAIL,    AVAIL,    AVAIL,    AVAIL,    NOTAVAIL}, /*  Time - Limit           */
		 {AVAIL,    AVAIL,    AVAIL,    AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL}, /*  Energy + Limit         */
		 {AVAIL,    AVAIL,    AVAIL,    AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL}, /*  Energy - Limit         */
		 {AVAIL,    AVAIL,    NOTAVAIL, AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL}, /*  Power + Limit          */
		 {AVAIL,    AVAIL,    NOTAVAIL, AVAIL,    AVAIL,    NOTAVAIL, NOTAVAIL}, /*  Power - Limit          */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*  Collapse + Limit       */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*  Collapse - Limit       */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, AVAILLE,  NOTAVAIL}, /*  Absolute + Limit       */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, AVAILLE,  NOTAVAIL}, /*  Absolute - Limit       */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL}, /*0 Trig. Dist + Limit     */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL}, /*1 Trig. Dist - Limit     */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*2 Max Force + S Limit    */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*3 Max Force - S Limit    */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*4 Freq. + Limit          */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*5 Freq. - Limit          */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*6 Max Force +/- R Limit  */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}, /*7 Downspeed + Limit      */
		 {NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL, NOTAVAIL}  /*8 Downspeed - Limit      */
		   },

		// Reject Limits
		//	Time     Energy   Pk. Pwr. Collaps    Absolute  Gr. Det.   Cont
		//	Mode     Mode     Mode     Mode       Mode      Mode       Mode

		   { // REJECT CONTROL LEVEL d (old level #4)

		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL}, /*0  Time + Limit			*/
		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL}, /*1  Time - Limit          */
		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL}, /*2  Energy + Limit        */
		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL}, /*3  Energy - Limit        */
		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL}, /*4  Power + Limit         */
		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL}, /*5  Power - Limit         */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE , NOTAVAIL}, /*6  Collapse + Limit      */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE , NOTAVAIL}, /*7  Collapse - Limit      */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE , NOTAVAIL}, /*8  Absolute + Limit      */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE , NOTAVAIL}, /*9  Absolute - Limit      */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL}, /*10 Trig. Dist + Limit    */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL}, /*11 Trig. Dist - Limit    */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL}, /*12 Max Force + Limit     */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL}, /*13 Max Force - Limit     */
		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL}, /*14 Freq. + Limit         */
		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL}, /*15 Freq. - Limit         */
		 {ACTDF  ,  ACTDF  ,  ACTDF  ,  ACTDF  ,  ACTDF  ,  ACTDF   , ACTDF  },  /*16 Max Force +/- R Limit */
		 {AVAIL ,   AVAIL,    AVAIL,    AVAIL  ,  AVAIL  ,  AVAIL,    NOTAVAIL}, /*17 Downspeed + Limit     */
		 {AVAIL ,   AVAIL,    AVAIL,    AVAIL  ,  AVAIL  ,  AVAIL ,   NOTAVAIL}  /*18 Downspeed - Limit     */
		  },


		// Reject Limits
		//	Time     Energy   Pk. Pwr. Collaps    Absolute  Gr. Det.   Cont
		//	Mode     Mode     Mode     Mode       Mode      Mode       Mode

		   { // REJECT CONTROL LEVEL f (old level #5(EP))

		 {NOTAVAIL, AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL ,   NOTAVAIL}, /*0  Time + Limit			*/
		 {NOTAVAIL, AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL ,   NOTAVAIL}, /*1  Time - Limit          */
		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL}, /*2  Energy + Limit        */
		 {AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL}, /*3  Energy - Limit        */
		 {AVAIL,    AVAIL,    NOTAVAIL, AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL}, /*4  Power + Limit         */
		 {AVAIL,    AVAIL,    NOTAVAIL, AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL}, /*5  Power - Limit         */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL}, /*6  Collapse + Limit      */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, NOTAVAIL}, /*7  Collapse - Limit      */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, AVAILLE , NOTAVAIL}, /*8  Absolute + Limit      */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  NOTAVAIL, AVAILLE , NOTAVAIL}, /*9  Absolute - Limit      */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL}, /*10 Trig. Dist + Limit    */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL}, /*11 Trig. Dist - Limit    */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL}, /*12 Max Force + S Limit   */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL}, /*13 Max Force - S Limit   */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE , NOTAVAIL}, /*14 Freq. + Limit         */
		 {AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE , NOTAVAIL}, /*15 Freq. - Limit         */
		 {ACTDF  ,  ACTDF  ,  ACTDF  ,  ACTDF  ,  ACTDF  ,  ACTDF   , ACTDF  },   /*16 Max Force +/- R Limit */
		 {AVAIL ,   AVAIL,    AVAIL,    AVAIL  ,  AVAIL  ,  AVAIL,    NOTAVAIL}, /*17 Downspeed + Limit     */
		 {AVAIL ,   AVAIL,    AVAIL,    AVAIL  ,  AVAIL  ,  AVAIL ,   NOTAVAIL}  /*18 Downspeed - Limit     */
	    },
		{ // REJECT CONTROL LEVEL c (old level #4)

		{AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL}, /*  Time + Limit		   */
		{AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL}, /*  Time - Limit           */
		{AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL}, /*  Energy + Limit         */
		{AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL}, /*  Energy - Limit         */
		{AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL}, /*  Power + Limit          */
		{AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL}, /*  Power - Limit          */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE , NOTAVAIL}, /*  Collapse + Limit       */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE , NOTAVAIL}, /*  Collapse - Limit       */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE , NOTAVAIL}, /*  Absolute + Limit       */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE , NOTAVAIL}, /*  Absolute - Limit       */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL}, /*0 Trig. Dist + Limit     */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL}, /*1 Trig. Dist - Limit     */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL}, /*2 Max Force + Limit      */
		{AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  AVAILLE,  ACTDF   , NOTAVAIL}, /*3 Max Force - Limit      */
		{AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL}, /*4 Freq. + Limit          */
		{AVAIL,    AVAIL,    AVAIL,    AVAILLE,  AVAILLE,  AVAIL   , NOTAVAIL}, /*5 Freq. - Limit          */
		{ACTDF  ,  ACTDF  ,  ACTDF  ,  ACTDF  ,  ACTDF  ,  ACTDF   , ACTDF  },  /*6	Max Force +/- R Limit  */
		{AVAIL ,   AVAIL,    AVAIL,    AVAIL  ,  AVAIL  ,  AVAIL,    NOTAVAIL}, /*7 Downspeed + Limit      */
		{AVAIL ,   AVAIL,    AVAIL,    AVAIL  ,  AVAIL  ,  AVAIL ,   NOTAVAIL}  /*8 Downspeed - Limit      */
		},
	};

const UINT16 parameterControlLevel[][MAXLEVELS] = {
	//  t          e           ea          d           f           c

	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //0   ALWAYS,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //1   PWELDMODE,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //2   PHOLDTIME,

	// only one is picked from mode list
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //3   PWELDTIME,
	{NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //4   PENERGY,
	{NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //5   PPEAKPOWER,
	{NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE,    AVAILLE},  //6   PABSDIST,
	{NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE,    AVAILLE},  //7   PCOLDIST,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //8   PSCRUBTIME,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL}, //9   PFREQUENCYCOUNT,

	// end of mode list
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //10  PAFTERBURST,

	// next entry either amplitude or amplitude stepping
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //11  PAMPLITUDEA,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL},    //12  PAMPLITUDESTEP,

	// end

	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //13  PAFTERBURSTDELAY,
	{NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL},    //14  PAMPLITUDEA1,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //15  PAFTERBURSTTIME,
	{NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL},    //16  PAMPLITUDEB,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //17  PAFTERBURSTAMP,

	// pick only one step
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL},    //18  PSTEPTRIGGERTIME,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL},    //19  PSTEPTRIGGERENERGY,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL},    //20  PSTEPTRIGGERPKPOWER,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE},  //21  PSTEPTRIGGERDISTANCE,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE},  //22  PSTEPTRIGGERFORCE,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL},    //23  PSTEPTRIGGEREXTSIGNAL,
	// end

	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //24  PPOSTWELDSEEK,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //25  PPRETRIGGER,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //26  PFREQUENCYOFFSET,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //27  PAUTOPRETRIGGER,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //28  PTESTAMPLITUDE,
	{NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE,    AVAILLE},  //29  PPRETRIGGERDISTANCE,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL},    //30  PRAPIDTRAVS,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //31  PPRETRIGGERAMP,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL}, //32  PRTDISTANCE,
	{NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE,    AVAILLE},  //33  PACTCLEAROUTPUT,
	{NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE,    AVAILLE},  //34  PACTCLEARDISTANCE,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //35  PCYCLEABORTS,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //36  PGROUNDDETECTCUTOFF,
	{NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE,    AVAILLE},  //37  PMISSINGPARTFLAG,
	{NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE,    AVAILLE},  //38  PMISSINGPARTMAX,
	{NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE,    AVAILLE},  //39  PMISSINGPARTMIN,
	{NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //40  PCONTROLLIMITS,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE},  //41  PCOLLAPSECUTOFF,
	{NOTAVAIL,   AVAIL ,     AVAIL,      AVAIL,      AVAIL,      AVAIL},    //42  PENERGYCOMP,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE},  //43  PABSOLUTECUTOFF,
	{NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //44  PENERGYMAX,
	{NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //45  PPKPOWERCUTOFF,
	{NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //46  PENGERGYMIN,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //47  PMAXTIMEOUT,

	//aef actuator group
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAILLE,    AVAILLE},  //48  PTRIGGERFORCE,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE},  //49  PDOWNSPEED,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE},  //50  PTRIGGERDELAY,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE},  //51  PGAUGEPSI,

	// next entry either pressure or pressure stepping
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,     AVAIL},  //52  PPRESSUREA,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,     AVAIL},  //53  PPRESSURESTEP,
	// end

	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE},  //54  PCALINFO,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,     AVAIL},  //55  PPRESSUREA1,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE},  //56  PCALDATE,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,     AVAIL},  //57  PPRESSUREB,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,        AVAIL},  //58  DRAWLINEFIELD,

	// pick only one step
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE},  //59  PFSTEPTRIGGERTIME,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE},  //60  PFSTEPTRIGGERENERGY,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE},  //61  PFSTEPTRIGGERPEAKPOER,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE},  //62  PFSTEPTRIGGERDISTANCE,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE},  //63  PFSTEPTRIGGERAMPLITUDE,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE},  //64  PFSTEPTRIGGEREXTSIGNAL,
	// end
	// end of aef

	// ae are all writeinfields
	{NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //65  PSUSPECTLIMITS,
	{NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //66  PREJECTLIMITS,
	{NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //67  PSUSPRESETREQ,
	{NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //68  PREJRESETREQ,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //69  PLANGUAGE,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //70  PTRIGGERBEEPER,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //71  PUNITS
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //72  PERRORBEEPER,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //73  PPASSWORD,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //74  PALARMBEEPER,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //75  PFEATURES,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //76  PWELDSCALE,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //77  PADVCOUNTER,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //78  PTESTSCALE,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //79  PHANDHELDSYSTEM,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //80  PDIGFILTER,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //81  PAMPCONTROL,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //82  PFREQCONTROL,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL}, //83  PSEQUENCING,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //84  PCUSTOMACT,

	// display one entry
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //85  PSERIALPORT,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //86  PREMOTETERMINAL,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL},    //87  PHOSTCOMMANDS,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //88  PULSLOGIC,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //89  PBAUDRATE,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL}, //90  PTRSLOGIC,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL}, //91  PSWHANDSHAKE,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL}, //92  PMPSLOGIC,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //93  PECHO,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //94  PGENALARMRESET,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //95  PPSSUPPLY,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //96  PACTUATOR,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //97  PCONTROLLEVEL,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //98  PCYLDIAMETER,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //99  PFREQUENCY,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //100 PCYLSTROKE,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //101 PSWVERSION,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //102 PPSLIFETIME,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //103 PPSSERNUM,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //104 PPRESETCOUNTER,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //105 PSWSERNUM,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL}, //106 PACTLIFETIME,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      ACTDF},    //107 PACTSERNUM,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //108 POVERLCOUNTER,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //109 PGENALARMCNTR,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //110 PPRINTERING,
		  // use for print on sample and print on alarm
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //111 PWELDDATA,
	{NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //112 PPOWERGRAPH,
	{NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL},    //113 PAMPLITUDEGRAPH,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL},    //114 PFREQUENCYGRAPH,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE},  //115 PDISTANCEGRAPH,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE,    AVAILLE},  //116 PVELOCITYGRAPH,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAILLE,    AVAILLE},  //117 PFORCEGRAPH,
	{NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL},    //118 PWELDHISTORY,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //119 PSETUP,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //120 PPRINTERS,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL}, //121 PFORMFEED,
	{NOTAVAIL,   TMODONLY,   TMODONLY,   TMODONLY,   TMODONLY,   TMODONLY}, //122 PAUTOXSCALE,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //123 PPAGESIZE,
	{NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //124 PXSCALE,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //125 PLINESPERPAGE,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL}, //126 NEVERPRINT,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL}, //127 PCONTINUOUS,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAILLE,    AVAILLE},  //128 PHOLDFORCE,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //129 STARTSCREEN,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //130 DIGITALTUNE,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //131 PEXTTRIGDLY,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //132 PDUPSRAMPTIME,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //133 PMEMORY,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //134 PWELDSTATUS,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //135 PSELECTNAME,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //136 PSEEKTIME,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //137 PTIMEDSEEK,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //138 PEXTRACOOLING,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //139 PUSERIO,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //140 PENERGYBRAKING,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //141 PRELEASEBEEPER,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //142 PEXTPRESETS,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //143 PWRITEINFIELD,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //144 PWELDTIMEMIN,
	{NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL},    //145 PENERGYMIN,
	{NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL},    //146 PPEAKPOWERMIN,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      ACTDF},    //147 PWELDCOLLAPSEMIN,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      ACTDF},    //148 PTOTALCOLLAPSEMIN,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      ACTDF},    //149 PTOTALABSOLUTEMIN,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      ACTDF},    //150 PWELDFORCEMIN,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //151 PTOTALCYCLETIMEMIN,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //152 PWELDTIMEMAX,
	{NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL},    //153 PENERGYMAXIMUM,
	{NOTAVAIL,   NOTAVAIL,   AVAIL,      AVAIL,      AVAIL,      AVAIL},    //154 PPEAKPOWERMAX,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      ACTDF},    //155 PWELDCOLLAPSEMAX,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      ACTDF},    //156 PTOTALCOLLAPSEMAX,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      ACTDF},    //157 PTOTALABSOLUTEMAX,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   ACTDF,      ACTDF,      ACTDF},    //158 PWELDFORCEMAX,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //159 PTOTALCYCLETIMEMAX,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //160 PSCRUBAMPLITUDE
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL},    //161 PBATCHCOUNTENABLED,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL},    //162 PBCOUNTWITHALARM,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL},    //163 PBCOUNTRESETTOZERO,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL},    //164 PBATCHCOUNT,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL},    //165 PPRESSURELIMIT,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL},    //166 PPRESSURELIMITPLUS,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL},    //167 PPRESSURELIMITMINUS,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL},    //168 PACTASSEMBLTNUM,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL},    //169 PPSASSEMBLYNUM,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL},    //170 PPSTACKASSEMBLYNUM,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL},    //171 PFLOWCONTROL,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL},    //172 PVALIDLOCK,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //173 PRAPIDTRAVERSEDIST,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //174 PHOLDPRESSURE,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //175 PWELDPRESSURE,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //176 PTRIGGER,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //177 PTRIGGERDIST,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //177 PESTOPBEEP,
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //178 PTRIGGERFORCE,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL},    //179 PVALIDUNLOCKED
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL},    //180 PUNVALIDUNCLOKED
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL},    //181 PPRESETREV
	{AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL,      AVAIL},    //182 PUSBFLAG,
	{NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   NOTAVAIL,   AVAIL},    //183 PSETUPLIMIT,
};

enum LIMITPARAM {
/*0 */    LTIMEPLUS,
/*1 */    LTIMEMINUS,
/*2 */    LENERGYPLUS,
/*3 */    LENERGYMINUS,
/*4 */    LPOWERPLUS,
/*5 */    LPOWERMINUS,
/*6 */    LCOLLAPSEPLUS,
/*7 */    LCOLLAPSEMINUS,
/*8 */    LABSOLUTEPLUS,
/*9 */    LABSOLUTEMINUS,
/*10*/    LTRIGGERDISTPLUS,
/*11*/    LTRIGGERDISTMINUS,
/*12*/    LMAXFORCEPLUS,          // + S Max Force Limit
/*13*/    LMAXFORCEMINUS,         // + S Max Force Limit
/*14*/    LFREQPLUS,                 
/*15*/    LFREQMINUS,
/*16*/    LRMAXFORCE,             // +/- R Max Force Limit 
/*17*/    LDOWNSPEEDPLUS,
/*18*/    LDOWNSPEEDMINUS
};



enum PARAMNUM{
/*0 */  ALWAYS,
/*1 */  PWELDMODE,
/*2 */  PHOLDTIME,
/*3 */  PWELDTIME,
/*4 */  PENERGY,
/*5 */  PPEAKPOWER,
/*6 */  PABSDIST,
/*7 */  PCOLDIST,
/*8 */  PSCRUBTIME,
/*9 */  PFREQUENCYCOUNT,
/*10*/  PAFTERBURST,
/*11*/  PAMPLITUDEA,
/*12*/  PAMPLITUDESTEP,
/*13*/  PAFTERBURSTDELAY,
/*14*/  PAMPLITUDEA1,
/*15*/  PAFTERBURSTTIME,
/*16*/  PAMPLITUDEB,
/*17*/  PAFTERBURSTAMP,
/*18*/  PSTEPTRIGGERTIME,
/*19*/  PSTEPTRIGGERENERGY,
/*20*/  PSTEPTRIGGERPKPOWER,
/*21*/  PSTEPTRIGGERDISTANCE,
/*22*/  PSTEPTRIGGERFORCE,
/*23*/  PSTEPTRIGGEREXTSIGNAL,
/*24*/  PPOSTWELDSEEK,
/*25*/  PPRETRIGGER,
/*26*/  PFREQUENCYOFFSET,
/*27*/  PAUTOPRETRIGGER,
/*28*/  PTESTAMPLITUDE,
/*29*/  PPRETRIGGERDISTANCE,
/*30*/  PRAPIDTRAVS,
/*31*/  PPRETRIGGERAMP,
/*32*/  PRTDISTANCE,
/*33*/  PACTCLEAROUTPUT,
/*34*/  PACTCLEARDISTANCE,
/*35*/  PCYCLEABORTS,
/*36*/  PGROUNDDETECTCUTOFF,
/*37*/  PMISSINGPARTFLAG,
/*38*/  PMISSINGPARTMAX,
/*39*/  PMISSINGPARTMIN,
/*40*/  PCONTROLLIMITS,
/*41*/  PCOLLAPSECUTOFF,
/*42*/  PENERGYCOMP,
/*43*/  PABSOLUTECUTOFF,
/*44*/  PENERGYMAX,
/*45*/  PPKPOWERCUTOFF,
/*46*/  PENGERGYMIN,
/*47*/  PMAXTIMEOUT,
/*48*/  PTRIGGERFORCE,
/*49*/  PDOWNSPEED,
/*50*/  PTRIGGERDELAY,
/*51*/  PGAUGEPSI,
/*52*/  PPRESSUREA,
/*53*/  PPRESSURESTEP,
/*54*/  PCALINFO,
/*55*/  PPRESSUREA1,
/*56*/  PCALDATE,
/*57*/  PPRESSUREB,
/*58*/  DRAWLINEFIELD,
/*59*/  PFSTEPTRIGGERTIME,
/*60*/  PFSTEPTRIGGERENERGY,
/*61*/  PFSTEPTRIGGERPEAKPOER,
/*62*/  PFSTEPTRIGGERDISTANCE,
/*63*/  PFSTEPTRIGGERAMPLITUDE,
/*64*/  PFSTEPTRIGGEREXTSIGNAL,
/*65*/  PSUSPECTLIMITS,
/*66*/  PREJECTLIMITS,
/*67*/  PSUSPRESETREQ,
/*68*/  PREJRESETREQ,
/*69*/  PLANGUAGE,
/*70*/  PTRIGGERBEEPER,
/*71*/  PUNITS,
/*72*/  PERRORBEEPER,
/*73*/  PPASSWORD,
/*74*/  PALARMBEEPER,
/*75*/  PFEATURES,
/*76*/  PWELDSCALE,
/*77*/  PADVCOUNTER,
/*78*/  PTESTSCALE,
/*79*/  PHANDHELDSYSTEM,
/*80*/  PDIGFILTER,
/*81*/  PAMPCONTROL,
/*82*/  PFREQCONTROL,
/*83*/  PSEQUENCING,
/*84*/  PCUSTOMACT,
/*85*/  PSERIALPORT,
/*86*/  PREMOTETERMINAL,
/*87*/  PHOSTCOMMANDS,
/*88*/  PULSLOGIC,
/*89*/  PBAUDRATE,
/*90*/  PTRSLOGIC,
/*91*/  PSWHANDSHAKE,
/*92*/  PMPSLOGIC,
/*93*/  PECHO,
/*94*/  PGENALARMRESET,
/*95*/  PPSSUPPLY,
/*96*/  PACTUATOR,
/*97*/  PCONTROLLEVEL,
/*98*/  PCYLDIAMETER,
/*99*/  PFREQUENCY,
/*100*/ PCYLSTROKE,
/*101*/ PSWVERSION,
/*102*/ PPSLIFETIME,
/*103*/ PPSSERNUM,
/*104*/ PPRESETCOUNTER,
/*105*/ PSWSERNUM,
/*106*/ PACTLIFETIME,
/*107*/ PACTSERNUM,
/*108*/ POVERLCOUNTER,
/*109*/ PGENALARMCNTR,
/*110*/ PPRINTERING,
/*111*/ PWELDDATA,
/*112*/ PPOWERGRAPH,
/*113*/ PAMPLITUDEGRAPH,
/*114*/ PFREQUENCYGRAPH,
/*115*/ PDISTANCEGRAPH,
/*116*/ PVELOCITYGRAPH,
/*117*/ PFORCEGRAPH,
/*118*/ PWELDHISTORY,
/*119*/ PSETUP,
/*120*/ PPRINTERS,
/*121*/ PFORMFEED,
/*122*/ PAUTOXSCALE,
/*123*/ PPAGESIZE,
/*124*/ PXSCALE,
/*125*/ PLINESPERPAGE,
/*126*/ NEVERPRINT,
/*127*/ PCONTINUOUS,
/*128*/ PHOLDFORCE,
/*129*/ STRTSCREEN,
/*130*/ DIGITALTUNE,
/*131*/ PEXTTRIGDLY,
/*132*/ PDUPSRAMPTIME,
/*133*/ PMEMORY,
/*134*/ PWELDSTATUS,
/*135*/ PSELECTNAME,
/*136*/ PSEEKTIME,
/*137*/ PTIMEDSEEK,
/*138*/ PEXTRACOOLING,
/*139*/ PUSERIO,
/*140*/ PENERGYBRAKING,
/*141*/ PRELEASEBEEPER,
/*142*/ PEXTPRESETS,
/*143*/ PWRITEINFIELD,
/*144*/ PWELDTIMEMIN,
/*145*/ PENERGYMIN,
/*146*/ PPEAKPOWERMIN,
/*147*/ PWELDCOLLAPSEMIN,
/*148*/ PTOTALCOLLAPSEMIN,
/*149*/ PTOTALABSOLUTEMIN,
/*150*/ PWELDFORCEMIN,
/*151*/ PTOTALCYCLETIMEMIN,
/*152*/ PWELDTIMEMAX,
/*153*/ PENERGYMAXIMUM,
/*154*/ PPEAKPOWERMAX,
/*155*/ PWELDCOLLAPSEMAX,
/*156*/ PTOTALCOLLAPSEMAX,
/*157*/ PTOTALABSOLUTEMAX,
/*158*/ PWELDFORCEMAX,
/*159*/ PTOTALCYCLETIMEMAX,
/*160*/ PSCRUBAMPLITUDE,
/*161*/ PBATCHCOUNTENABLED,
/*162*/ PBCOUNTWITHALARM,
/*163*/ PBCOUNTRESETTOZERO,
/*164*/ PBATCHCOUNT,
/*165*/ PPRESSURELIMIT,
/*166*/ PPRESSURELIMITPLUS,
/*167*/ PPRESSURELIMITMINUS,
/*168*/ PACTASSEMBLTNUM,
/*169*/ PPSASSEMBLYNUM,
/*170*/ PPSTACKASSEMBLYNUM,
/*171*/ PFLOWCONTROL,
/*172*/ PVALIDLOCK,
/*173*/ PRAPIDTRAVERSEDIST,
/*174*/ PHOLDPRESSURE,
/*175*/ PWELDPRESSURE,
/*176*/ PTRIGGER,
/*177*/ PTRIGGERDIST,
/*178*/ PESTOPBEEP,
/*179*/ PVALIDUNLOCKED,
/*180*/ PUNVALIDUNCLOKED,
/*181*/ PPRESETREV,
/*182*/ PUSBFLAG,
/*183*/ PSETUPLIMIT,
};

/* Parameter */
#define   PRESETSETUPLOAD1(a)    if(CheckIfPrintable(a)) {strncpy(PresetSetup1[SetupCt1++],   buffer, SIZEOFBUF); }
#define   PRESETSETUPLOAD2(a)    if(CheckIfPrintable(a)) {strncpy(PresetSetup2[SetupCt2++],   buffer, SIZEOFBUF); }

/* Limits */
#define   REJLIMPRESETSETUPLOAD1(a)    SusRejFlag = REJACTIVE; if(ControlLevelLimit(a)) {strncpy(PresetSetup1[SetupCt1++],   buffer, SIZEOFBUF); }
#define   SUSLIMPRESETSETUPLOAD2(a)    SusRejFlag = SUSACTIVE; if(ControlLevelLimit(a)) {strncpy(PresetSetup2[SetupCt2++],   buffer, SIZEOFBUF); }

#endif /* _LIMARRAY_H */



 
   
   
   
   
   
     
   
   
   
   
   
   
   
   
   
   
   
     
   
     
   
   
     
     
   
   
   
     
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   
   




















      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
      
