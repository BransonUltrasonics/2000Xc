/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/graphs.cpp_v   1.20   Oct 09 2017 16:22:04   RJamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/graphs.cpp_v  $
 * 
 *    Rev 1.20   Oct 09 2017 16:22:04   RJamloki
 * added CurrentSetup.Actuator=MICROC in if statement that, evaluate actuator id's
 * 
 *    Rev 1.19   16 Apr 2015 07:22:02   rjamloki
 * Removed unused local vars to fix warnings
 * 
 *    Rev 1.18   09 Apr 2015 05:18:00   RJamloki
 * Corrected pressure stepping tick text for graph. Added fix for horn clamp not working on PMC alarms. Fixed two negative signs getting displayed on graph.
 * 
 *    Rev 1.17   27 Mar 2015 11:07:12   amaurya
 * Removed Redundant SetDisplayRefreshButton function.
 * 
 *    Rev 1.16   08 Jan 2015 03:18:22   AnPawar
 * printf removed
 * 
 *    Rev 1.15   11 Dec 2014 08:35:22   AnPawar
 * removed nested comment
 * 
 *    Rev 1.14   26 Sep 2014 03:11:04   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.13   11 Sep 2014 10:51:58   rjamloki
 * Formatting and indentation as per review comments
 * 
 *    Rev 1.12   18 Aug 2014 01:36:04   rjamloki
 * Added MICRO support
 * 
 *    Rev 1.11   28 Jul 2014 12:44:44   rjamloki
 * Support for Amp and Current HS Graph
 * 
 *    Rev 1.10   09 Jul 2014 10:51:34   rjamloki
 * Menu4.h removed
 * 
 *    Rev 1.9   11 Jun 2014 11:31:40   rjamloki
 * removed and cleaned up redundant globals
 * 
 *    Rev 1.8   21 May 2014 10:47:58   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.7   21 May 2014 03:05:50   rjamloki
 * coverity fix
 * 
 *    Rev 1.6   07 May 2014 14:42:26   rjamloki
 * Buffer size fix in GraphLabel function.
 * 
 *    Rev 1.5   26 Mar 2014 12:16:38   rjamloki
 * UINT16 DrawHSGraph() function changed.Removed some extern declarations
 * 
 *    Rev 1.4   05 Mar 2014 13:56:24   rjamloki
 * Screens and PDf working
 * 
 *    Rev 1.3   10 Feb 2014 04:59:36   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:45:28   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

 Module name:

 Filename: graphs.c

 Written by:
 Date: 04/28/2003
 Language: "C"

 ------------------------------- DESCRIPTION ---------------------------------
 */

/*
 ------------------------------ INCLUDE FILES --------------------------------
 */

#include <string.h>
#include "dups_api.h"
#include "menu.h"
#include "preset.h"
#include "util.h"
#include "portable.h"
#include "graphs.h"
#include "battram.h"
#include "param.h"
#include "weld_obj.h"
#include "stdio.h"
#include "ready.h"
#include "beep.h"
#include "WeldManagerTask.h"
/*
 ------------------------------- LOCAL DEFINES -------------------------------
 */
#define LABELVAL 12
#define METRICRESOLUTION  10000
#define ENGRESOLUTION  1000
#define STARTBOTTOMGRAPH "-0.1"
#define LONGWELDTIME  20000
#define LONGSTARTGRAPH "0.00"
#define MINUSSTR  "-"
#define HS_GRAPH_HEIGHT 136
#define MAX_TICK_MARKS  7

/*
 --------------------------LOCAL DATA------------------------------------------
 */
SINT32 ActualValuePMC1;
SINT32 ActualValuePMC2;
BOOLEAN IsGraphDrawing = FALSE;
BOOLEAN VGAHistoryData = FALSE;
BOOLEAN PMCPlusBandFlag;
BOOLEAN PMCMinusBandFlag;
UINT16 VGATickmarks[MAX_TICK_MARKS];
UINT16 VGATickInfo[MAX_TICK_MARKS];
UINT32 VGAUIVmaxlabel;
UINT32 VGAUIVminlabel;
static UINT16 VGAGraphCurrentlySelected;
SINT32 StoreCycleCount;
const STR * const Str_TickLabel[] = { "T", "A", "P", "W", "H", " ", "G" };

/*
 -------------------------EXTERNAL DATA----------------------------------------
 */
extern UINT16 WeldDataCount;
extern WELD_OBJECT *MsPointer;
extern WELD_DATA *PrintFinalPtr;
extern SINT32 DigTuneValue;
extern UINT16 TotalCycle;
extern BOOLEAN AllParamColumnFlag;
extern UINT16 ResonanceFreqEnable[];
extern UINT8 *VGAAckBuf;
extern WELD_OBJECT *MsDataPtr;
/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
 */
UINT32 UIVmaxlabel, UIVminlabel, UIHmaxlabel;
static void GraphVLabel(UINT16 CWhichGraph, UINT32 UIMaxlabel,
		UINT32 UIMinlabel, UINT16 INum, SINT8 CMess[]);
static void GraphHLabel(UINT32 UIHmaxlabel, SINT8 Hlabel[]);
WELD_DATA * GetLastWeldResultPtr(void);
UINT16 AddToBuffer(UINT8 * * to, SINT8 byte);
UINT16 AddToBufferString(UINT8 * * to, SINT8 * string, UINT16 length);
UINT16 LangStrLen(SINT8 * str);
void StrCpyTwoBytes(SINT8 * to, SINT8 * from);
void AddToPMCData(void);

UINT16 DrawHSGraph(UINT8 * * Response, UINT16 GraphID);
UINT16 WeldParams(UINT8 * *Response, UINT16 WeldCount, BOOLEAN ParamFlag);
/*
 ---------------------------------- CODE -------------------------------------
 */

/**--------------------------------------------------------------**
 ** While drawing of the graph the vertical labels have to       **
 ** be printed in every 5th line. This function calculates the   **
 ** value of the actual label and prints it.                     **
 ** IN: Maxlabel, Minlabel, index of the actual label            **
 ** OUT:                                                         **
 **--------------------------------------------------------------**/
static void GraphVLabel(UINT16 CWhichGraph, UINT32 UIMaxlabel,
		UINT32 UIMinlabel, UINT16 INum, SINT8 CMess[]) {
	UINT32 UIValue;
	UIValue = ((4 - INum) * (UIMaxlabel - UIMinlabel)) / 4 + UIMinlabel;
	switch (CWhichGraph) {
	case DISTINGRAPH:
	case ABSINGRAPH:
	case ABSMMGRAPH:
	case DISTMMGRAPH:
		/* If collapse, absolute distance, label is float */
		sprintf(CMess, "%5.3f", (double) UIValue / 10000.0);
		break;
	case VELINGRAPH:
	case VELMMGRAPH:
		sprintf(CMess, "%5.2f", (double) UIValue / 10000.0);
		break;
	case POWGRAPH:
		sprintf(CMess, "%5.1f", (double) UIValue / 10.0);
		break;
	case AMPLIGRAPH:
		sprintf(CMess, "%5lu", UIValue / 10);
		break;
	default:
		sprintf(CMess, "%5lu", UIValue);
		break;
	}
}

/**----------------------------------------------------**
 ** The horizontal labels are calculated, written in a **
 ** buffer line and printed.                           **
 ** IN: maximum horizontal label.                      **
 ** OUT:                                               **
 **----------------------------------------------------**/
static void GraphHLabel(UINT32 UIHmaxlabel, SINT8 Hlabel[])
{
	double FValue = 0.0, FIncValue = 0.0;
	SINT8 CVal[10];
	SINT32 tempInt;
	SINT32 tempval = 0;
	SINT32 count;
	/*-- Calculate x-axis scale --*/
	FIncValue = (UIHmaxlabel) / VALUEDIV; /*-- 10000 points per 10 seconds --*/

	tempInt = (UIHmaxlabel / INCLABEL);
	FValue = 0.0;

	for (count = 0; count <= INCLABEL; count++) {
		if (count == 0) {
			if (CurrentSetup.HandHeld == TRUE) {
				strcpy(CVal, LONGSTARTGRAPH);
				FValue = 0.000;
				tempval = 0;
			} else {
				if (UIHmaxlabel < LONGWELDTIME) {
					strcpy(CVal, STARTBOTTOMGRAPH);
				} else {
					strcpy(CVal, LONGSTARTGRAPH);
				}

				FValue = STARTLABEL;
				tempval = LABELINT;
			}
		} else {
			FValue += (double) 0.00001;
			FValue += FIncValue;
			tempval += tempInt;
			sprintf(CVal, "%3.2f", FValue);

		}
		strcpy(&Hlabel[count * 7], CVal);

	} /* end of for */

}/*-- void PrintGraphHLabel(UINT32 UIWeldtime)--*/

WELD_DATA * GetLastWeldResultPtr(void)
/****************************************************************************/
/*Description:-                                                             */
/* Returns Last Weld Data pointer                                           */
/****************************************************************************/
{
	SINT32 Addr;
	UINT8 *BatHistoryPtr;
	WELD_DATA * LastWeldResultPtr;

	BatHistoryPtr = (UINT8 *) (FRAM1200_HISTORY_START );
	Addr = (SINT32) BatHistoryPtr;

	/*-- Get the last Weld Data position --*/
	if (CurrentSetup.WeldHistoryPtr != Addr)
		LastWeldResultPtr = (WELD_DATA *) (CurrentSetup.WeldHistoryPtr
				- (sizeof(WELD_DATA)));
	else
		LastWeldResultPtr = (WELD_DATA *) (Addr
				+ ((HISTORYDATA - 1) * sizeof(WELD_DATA)));

	PrintFinalPtr = LastWeldResultPtr;
	return (LastWeldResultPtr);
}

UINT16 SendGraphData(UINT8 * * Response, UINT16 GraphID)
/****************************************************************************/
/*Description:-                                                             */
/* Sends Graph Object                                                       */
/* Response - Buffer to which data is written                               */
/* Returns Length of the buffer                                             */
/****************************************************************************/
{
	WELD_DATA *LastWeldPtr;
	SINT8 HlabelBuffer[100];
	SINT8 TempStr[VGA_LINESIZE];
	SINT16 Index;
	UINT16 Index1 = 0;
	UINT16 SampleCount;
	UINT16 length = 0;
	UINT16 GraphColor = 0;
	SINT8 Str_Vlabel[VGA_LINESIZE];

	if (GraphID == VGAPOWERGRAPH) {
		VGAGraphCurrentlySelected = POWGRAPH;
		GraphColor = COLOR_BLUE;
	} else if (GraphID == VGAFREQUENCYGRAPH) {
		VGAGraphCurrentlySelected = FREQUGRAPH;
		GraphColor = COLOR_BLACK;
	} else if (GraphID == VGAAMPLITUDEGRAPH) {
		VGAGraphCurrentlySelected = AMPLIGRAPH;
		GraphColor = COLOR_BROWN;
	} else if (GraphID == VGAFORCEGRAPH) {
		VGAGraphCurrentlySelected =
				CurrentSetup.Units ? FORCENGRAPH : FORCELBGRAPH;
		GraphColor = COLOR_RED;
	} else if (GraphID == VGAVELOCITYGRAPH) {
		VGAGraphCurrentlySelected =
				CurrentSetup.Units ? VELMMGRAPH : VELINGRAPH;
		GraphColor = COLOR_MAGENTA;
	} else if (GraphID == VGACOLDISTGRAPH) {
		VGAGraphCurrentlySelected =
				CurrentSetup.Units ? DISTMMGRAPH : DISTINGRAPH;
		GraphColor = COLOR_GREEN;
	}
	/*Get Last Weld Data pointer*/
	LastWeldPtr = GetLastWeldResultPtr();

	if ((MsPointer->TotalPts != 0) && (MsPointer->DontPrintGraph == FALSE)) {
		/*Test*/
		length += AddToBuffer(Response,
				(UINT8) (VGAGraphCurrentlySelected >> 8));
		length += AddToBuffer(Response, (UINT8) VGAGraphCurrentlySelected);
		/*Get Graph Data*/
		length += AddToBuffer(Response, (UINT8) (GraphColor));
		SetupVals((WHICHGRAPH) VGAGraphCurrentlySelected, val2);
		GetMaxMinLabel(VGAGraphCurrentlySelected, val2, WeldDataCount,
				&VGAUIVmaxlabel, &VGAUIVminlabel);
		/*Calibrate the Graph data*/
		RecalibVal(val2, VGAGraphCurrentlySelected, VGAUIVmaxlabel,
				VGAUIVminlabel);
		/*Send Graph Data*/
		IsGraphDrawing = TRUE;
		if (WeldDataCount < MAX_WELD_SAMPLES)
			SampleCount = WeldDataCount;
		else
			SampleCount = MAX_WELD_SAMPLES;

		length += AddToBuffer(Response, (UINT8) (SampleCount >> 8));
		length += AddToBuffer(Response, (UINT8) SampleCount);

		for (Index = 0; Index < SampleCount; Index++) {
			if (val2[Index] < 0)
				val2[Index] = 0;
			else if (val2[Index] > 160)
				val2[Index] = 160;
			length += AddToBuffer(Response, (UINT8) val2[Index]);
		}
		IsGraphDrawing = FALSE;

		/*Send Vertical Labels*/
		for (Index = 3; Index >= 0; Index--) {
			GraphVLabel(VGAGraphCurrentlySelected, VGAUIVmaxlabel,
					VGAUIVminlabel, Index, Str_Vlabel);
			StrCpyTwoBytes(TempStr, Str_Vlabel);
			length += AddToBuffer(Response, LangStrLen(TempStr));
			length += AddToBufferString(Response, TempStr, LangStrLen(TempStr));
		}

		UIHmaxlabel = UIWeldtime;
		VGAPrepTickMarks();

		/*Send Horizontal Labels*/
		GraphHLabel(UIHmaxlabel, HlabelBuffer);
		for (Index = 0; Index <= INCLABEL; Index++) {
			StrCpyTwoBytes(TempStr, &HlabelBuffer[Index * 7]);
			length += AddToBuffer(Response, LangStrLen(TempStr));
			length += AddToBufferString(Response, TempStr, LangStrLen(TempStr));
		}

		/* insert the tickmarks of FinalResults in Graph */
		for (Index = 0; Index < MAX_TICK_MARKS; Index++) {
			if (VGATickmarks[Index] != 0) /*Check for valid Tick Mark*/
				Index1++;
		}
		length += AddToBuffer(Response, (UINT8) Index1);

		for (Index = 0; Index < MAX_TICK_MARKS; Index++) {
			if (VGATickmarks[Index] != 0) /*Check for valid Tick Mark*/
			{
				length += AddToBufferString(Response,
						(SINT8*) Str_TickLabel[Index], 1);
				length += AddToBuffer(Response,
						(UINT8) (VGATickmarks[Index] >> 8));
				length += AddToBuffer(Response, (UINT8) VGATickmarks[Index]);
			}
		} /*End of for loop*/

		/* Send Tick info to be displayed on the bottom part of print graph*/
		for (Index = 0; Index < MAX_TICK_MARKS; Index++) {
			length += AddToBuffer(Response, (UINT8) (VGATickInfo[Index] >> 8));
			length += AddToBuffer(Response, (UINT8) VGATickInfo[Index]);
		} /*End of for loop*/

		if (GraphID == VGAAMPLITUDEGRAPH) {
			/*Send Info for special note to be printed for Amp graph*/
			if (CurrentSetup.ControlLevel >= LEVEL_ea)
				length += AddToBuffer(Response, 1);
			else
				length += AddToBuffer(Response, 0);
		} else if (GraphID == VGAFORCEGRAPH) {
			length += AddToBuffer(Response, 0);
		} else
			length += AddToBuffer(Response, 0);

		/*Manual scale*/
		if (((LastWeldPtr->Weldmode == TIMEMODE)
				&& (MsPointer->PrintBottomFlags & MANUALSCALEFLAG))
				|| (LastWeldPtr->Weldmode != TIMEMODE))
			length += AddToBuffer(Response, 1);
		else
			length += AddToBuffer(Response, 0);

		/*Cycle count text*/
		sprintf(TempStr, "%ld", LastWeldPtr->CycleCount);
		length += AddToBuffer(Response, LangStrLen(TempStr));
		length += AddToBufferString(Response, TempStr, LangStrLen(TempStr));

		/*Guage pressure*/
		if (((CurrentSetup.Actuator == AED) || (CurrentSetup.Actuator == AES) || (CurrentSetup.Actuator == MICROC)
				|| (CurrentSetup.Actuator == MICRO))
				&& (CurrentSetup.ControlLevel >= LEVEL_d)) {
			FormatVariables(LastWeldPtr->WeldPressure, PRESSURE, TempStr, 6,
					CurrentSetup.Units);
			TempStr[6] = 0;

			length += AddToBuffer(Response, LangStrLen(TempStr));
			length += AddToBufferString(Response, TempStr, LangStrLen(TempStr));

		} else
			length += AddToBuffer(Response, 0);

	} else {
		VGAGraphCurrentlySelected = NO_VALID_GRAPH;
		length += AddToBuffer(Response,
				(UINT8) (VGAGraphCurrentlySelected >> 8));
		length += AddToBuffer(Response, (UINT8) VGAGraphCurrentlySelected);
	}
	return length;
}

UINT16 ProcessWeldGraphValue(UINT8 WeldGraphDataReq, UINT8 WeldCount)
/***************************************************************************/
/*Processes Request for weld and graph data to be sent                     */
/*WeldGraphDataReq - Byte that decides what graphs are to be sent as well  */
/*                   as well as weld data to be sent                       */
/*WeldCount - Number of Weld cycle data to be sent                         */
/***************************************************************************/
{
	UINT8 index;
	UINT8 j = 1;
	UINT16 length = 0;
	UINT8 * PointertoAckBuf;

	PointertoAckBuf = (VGAAckBuf + 8);
	VGAHistoryData = FALSE; // History dat for last 25 weld cycles
	for (index = 0; index < 8; index++) {
		switch (index) {
		case 0:
			if (WeldGraphDataReq & j) // Weld Data to be sent
					{
				TotalCycle = WeldCount & 0x7F; // Nos of cycles requested for
				if (WeldCount & 0x80)
					VGAHistoryData = TRUE; //History data for first 25 cycles to be sent
				AllParamColumnFlag = TRUE;
				length += WeldParams(&PointertoAckBuf, TotalCycle,
						AllParamColumnFlag);

			}
			break;

		case 1:
			if (WeldGraphDataReq & j) // Power graph data
				length += SendGraphData(&PointertoAckBuf, VGAPOWERGRAPH);
			break;

		case 2:
			if (WeldGraphDataReq & j) // Frequency graph data
				length += SendGraphData(&PointertoAckBuf, VGAFREQUENCYGRAPH);
			break;

		case 3:
			if (WeldGraphDataReq & j) // Amplitude graph data
				length += SendGraphData(&PointertoAckBuf, VGAAMPLITUDEGRAPH);
			break;

		case 4:
			if (WeldGraphDataReq & j) // Force graph data
				length += SendGraphData(&PointertoAckBuf, VGAFORCEGRAPH);
			break;

		case 5:
			if (WeldGraphDataReq & j) // Velocity graph data
				length += SendGraphData(&PointertoAckBuf, VGAVELOCITYGRAPH);
			break;

		case 6:
			if (WeldGraphDataReq & j) // Collapse graph data
				length += SendGraphData(&PointertoAckBuf, VGACOLDISTGRAPH);
			break;

		case 7:
			if (WeldGraphDataReq & j) // HS graph data
				length += DrawHSGraph(&PointertoAckBuf, VGAHORNSCANGRAPH);
			break;
		}
		j = j * 2;
	}
	return (length);
}

UINT16 DrawHSGraph(UINT8 * * Response, UINT16 /*GraphID*/)
/***************************************************************************/
/* Sends Horn Scan Graph Data to SBC.Scan graph includes phase,amplitude and
 * current data.First max value of each parameter is found then the points
 * are calibrated according to SBC graph axis height.
 ***************************************************************************/
{
	SINT8 TempStr[VGA_LINESIZE];
	SINT8 TempStr1[VGA_LINESIZE];
	UINT16 Index;
	SINT32 tempMaxval;
	double maxval;
	double minval;
	double scale; /* scaling maximum value */
	UINT16 length = 0;
	UINT16 GraphColor = COLOR_BLACK;
	UINT8 NumHSFreqAvail = 0;

	if (HornScanInfo.ScanStatus == DUPS_SCANDATAAVAIL) {
		VGAGraphCurrentlySelected = PHASEGRAPH;
		length += AddToBuffer(Response,
				(UINT8) (VGAGraphCurrentlySelected >> 8));
		length += AddToBuffer(Response, (UINT8) VGAGraphCurrentlySelected);
		/*Get Graph Data*/
		length += AddToBuffer(Response, (UINT8) (GraphColor));
		SetupVals(PHASEGRAPH, val1);
		SetupVals(CURRENTGRAPH, val2);
		SetupVals(HSAMP_GRAPH, val3);

		//GetMaxMinLabel(AMPLIGRAPH, val2, DUPS_HORNSCANPOINTS, &VGAUIVmaxlabel, &VGAUIVminlabel);
		VGAUIVmaxlabel = 1000;
		VGAUIVminlabel = 0;
		/*Calibrate the Graph data*/
		RecalibVal(val2, CURRENTGRAPH, VGAUIVmaxlabel, VGAUIVminlabel);
		//GetMaxMinLabel(AMPLIGRAPH, val3, DUPS_HORNSCANPOINTS, &VGAUIVmaxlabel, &VGAUIVminlabel);
		/*Calibrate the Graph data*/
		RecalibVal(val3, HSAMP_GRAPH, VGAUIVmaxlabel, VGAUIVminlabel);

		/*Find Max: Phase Value*/
		tempMaxval = (double) val1[0];
		for (Index = 0; Index < DUPS_HORNSCANPOINTS; Index++) {
			if (tempMaxval < val1[Index])
				tempMaxval = val1[Index];
		}
		maxval = (double) tempMaxval;
		/*Find Min: Phase Value*/
		minval = maxval;
		for (Index = 0; Index < DUPS_HORNSCANPOINTS; Index++) {
			if (val1[Index] < minval)
				minval = val1[Index];
		}

		/* scale val for plot */
		if (minval > 0) /* all positive */
			scale = maxval;
		else if (maxval < 0) /* all negative */
			scale = -minval;
		else /* on both sides of 0 */
		{
			scale = maxval; /* real limit could be minval or maxval, */
			if (-minval > scale) /* whichever's absolute value is larger */
				scale = -minval;
		}

		length += AddToBuffer(Response, (UINT8) (DUPS_HORNSCANPOINTS >> 8));
		length += AddToBuffer(Response, (UINT8) DUPS_HORNSCANPOINTS);
		for (Index = 0; Index < DUPS_HORNSCANPOINTS; Index++) {
			val1[Index] = HS_GRAPH_HEIGHT / 2
					+ (SINT32) ((double) (val1[Index] * HS_GRAPH_HEIGHT / 2)
							/ scale);
			if (val1[Index] > 136)
				val1[Index] = 136;
			else if (val1[Index] < 0)
				val1[Index] = 0;
			length += AddToBuffer(Response, (UINT8) val1[Index]);
		}

		/*Draw the Horizontal Label 1*/
		sprintf(TempStr, "%5ld", HornScanInfo.StartFreq);
		StrCpyTwoBytes(TempStr1, TempStr);
		length += AddToBuffer(Response, LangStrLen(TempStr1));
		length += AddToBufferString(Response, TempStr1, LangStrLen(TempStr1));
		/*Draw the Horizontal Label 2*/
		sprintf(TempStr, "%5ld",
				(HornScanInfo.StopFreq - HornScanInfo.StartFreq) / 2
						+ HornScanInfo.StartFreq);
		StrCpyTwoBytes(TempStr1, TempStr);
		length += AddToBuffer(Response, LangStrLen(TempStr1));
		length += AddToBufferString(Response, TempStr1, LangStrLen(TempStr1));
		/*Draw the Horizontal Label 3*/
		sprintf(TempStr, "%5ld", HornScanInfo.StopFreq);
		StrCpyTwoBytes(TempStr1, TempStr);
		length += AddToBuffer(Response, LangStrLen(TempStr1));
		length += AddToBufferString(Response, TempStr1, LangStrLen(TempStr1));

		for (Index = 0; Index < DUPS_NUMRESONANCES; Index++) {
			if (ResonanceFreqEnable[Index])
				NumHSFreqAvail++;
		}
		length += AddToBuffer(Response, NumHSFreqAvail);
		for (Index = 0; Index < DUPS_NUMRESONANCES; Index++) {
			if (ResonanceFreqEnable[Index]) {
				length += AddToBuffer(Response,
						(UINT8) (HornScanInfo.ResonanceFreqs[Index] >> 24));
				length += AddToBuffer(Response,
						(UINT8) (HornScanInfo.ResonanceFreqs[Index] >> 16));
				length += AddToBuffer(Response,
						(UINT8) (HornScanInfo.ResonanceFreqs[Index] >> 8));
				length += AddToBuffer(Response,
						(UINT8) HornScanInfo.ResonanceFreqs[Index]);
				length += AddToBuffer(Response,
						(UINT8) HornScanInfo.ResonanceFreqType[Index]);
			}
		}
		length += AddToBuffer(Response, (UINT8) (DigTuneValue >> 24));
		length += AddToBuffer(Response, (UINT8) (DigTuneValue >> 16));
		length += AddToBuffer(Response, (UINT8) (DigTuneValue >> 8));
		length += AddToBuffer(Response, (UINT8) DigTuneValue);
		length += AddToBuffer(Response, (UINT8) (HornScanInfo.Year >> 24));
		length += AddToBuffer(Response, (UINT8) (HornScanInfo.Year >> 16));
		length += AddToBuffer(Response, (UINT8) (HornScanInfo.Year >> 8));
		length += AddToBuffer(Response, (UINT8) HornScanInfo.Year);
		length += AddToBuffer(Response, (UINT8) (HornScanInfo.Month >> 24));
		length += AddToBuffer(Response, (UINT8) (HornScanInfo.Month >> 16));
		length += AddToBuffer(Response, (UINT8) (HornScanInfo.Month >> 8));
		length += AddToBuffer(Response, (UINT8) HornScanInfo.Month);
		length += AddToBuffer(Response, (UINT8) (HornScanInfo.Day >> 24));
		length += AddToBuffer(Response, (UINT8) (HornScanInfo.Day >> 16));
		length += AddToBuffer(Response, (UINT8) (HornScanInfo.Day >> 8));
		length += AddToBuffer(Response, (UINT8) HornScanInfo.Day);
		length += AddToBuffer(Response, (UINT8) (HornScanInfo.Hour >> 24));
		length += AddToBuffer(Response, (UINT8) (HornScanInfo.Hour >> 16));
		length += AddToBuffer(Response, (UINT8) (HornScanInfo.Hour >> 8));
		length += AddToBuffer(Response, (UINT8) HornScanInfo.Hour);
		length += AddToBuffer(Response, (UINT8) (HornScanInfo.Minute >> 24));
		length += AddToBuffer(Response, (UINT8) (HornScanInfo.Minute >> 16));
		length += AddToBuffer(Response, (UINT8) (HornScanInfo.Minute >> 8));
		length += AddToBuffer(Response, (UINT8) HornScanInfo.Minute);

		length += AddToBuffer(Response, (UINT8) (DUPS_HORNSCANPOINTS >> 8));
		length += AddToBuffer(Response, (UINT8) DUPS_HORNSCANPOINTS);
		for (Index = 0; Index < DUPS_HORNSCANPOINTS; Index++) {
			length += AddToBuffer(Response, (UINT8) val2[Index]);
		}
		length += AddToBuffer(Response, (UINT8) (DUPS_HORNSCANPOINTS >> 8));
		length += AddToBuffer(Response, (UINT8) DUPS_HORNSCANPOINTS);
		for (Index = 0; Index < DUPS_HORNSCANPOINTS; Index++) {
			length += AddToBuffer(Response, (UINT8) val3[Index]);
		}
	} else {
		VGAGraphCurrentlySelected = NO_VALID_GRAPH;
		length += AddToBuffer(Response,
				(UINT8) (VGAGraphCurrentlySelected >> 8));
		length += AddToBuffer(Response, (UINT8) VGAGraphCurrentlySelected);
	}
	return length;
}

void AddToPMCData(void)
/****************************************************************************/
/*Description:-                                                             */
/* This function averages Power match curve data                            */
/****************************************************************************/
{
	UINT16 Index;
	UINT16 TempPMCVal;
	UINT16 SampleCount;
	UINT16 PrevMaxPowerVal;
	UINT16 CurrentMaxPowerVal;

	VGAGraphCurrentlySelected = POWGRAPH;

	if ((MsPointer->TotalPts != 0)
			&& (StoreCycleCount != WeldingResults.CycleCount)) {

		/*Get Graph Data*/
		SetupVals((WHICHGRAPH) VGAGraphCurrentlySelected, val2);

		GetMaxMinLabel(VGAGraphCurrentlySelected, val2, WeldDataCount,
				&VGAUIVmaxlabel, &VGAUIVminlabel);

		/*Calibrate the Graph data*/
		RecalibVal(val2, VGAGraphCurrentlySelected, VGAUIVmaxlabel,
				VGAUIVminlabel);

		if (WeldDataCount < MAX_WELD_SAMPLES)
			SampleCount = WeldDataCount;
		else
			SampleCount = MAX_WELD_SAMPLES;

		if (CurrentPreset.PMCCycleCount)
			PrevMaxPowerVal = (UINT16) CurrentPreset.PMCData[PMCDATAPOINTS - 2];
		else
			PrevMaxPowerVal = 0;
		CurrentMaxPowerVal = (UINT16) (VGAUIVmaxlabel / 10);

		if (PrevMaxPowerVal > CurrentMaxPowerVal) {
			for (Index = 0; Index < SampleCount; Index++) {
				if (val2[Index] < 0)
					val2[Index] = 0;
				val2[Index] = ((val2[Index] * CurrentMaxPowerVal)
						/ PrevMaxPowerVal);
			}
		} else if (PrevMaxPowerVal < CurrentMaxPowerVal) {
			for (Index = 0; Index < PMCDATAPOINTS - 2; Index++) {
				if (CurrentPreset.PMCData[Index] != 0xFF)
					CurrentPreset.PMCData[Index] =
							((CurrentPreset.PMCData[Index] * PrevMaxPowerVal)
									/ CurrentMaxPowerVal);
			}
			CurrentPreset.PMCData[PMCDATAPOINTS - 2] =
					(UINT8) CurrentMaxPowerVal;
		}

		for (Index = 0; Index < SampleCount; Index++) {
			if (val2[Index] < 0)
				val2[Index] = 0;
			if (CurrentPreset.PMCData[Index] == 0xFF)
				CurrentPreset.PMCData[Index] = val2[Index];
			else {
				TempPMCVal = val2[Index]
						+ (CurrentPreset.PMCData[Index]
								* CurrentPreset.PMCCycleCount);
				CurrentPreset.PMCData[Index] = (UINT8) (TempPMCVal
						/ (CurrentPreset.PMCCycleCount + 1));
			}
		}
		CurrentPreset.PMCCycleCount++;
		StoreCycleCount = WeldingResults.CycleCount;
	} else
		Beep(ERRORBEEP);
}

UINT16 SendPMCValue(UINT8 * AckBuf)
/****************************************************************************/
/*Description:-                                                             */
/* This function sends Power match curve data                               */
/*Input Parameters:-                                                        */
/* AckBuf:  Pointer to the buffer where data is to be written               */
/*Output:-                                                                  */
/* Length of the bytes written to the buffer                                */
/****************************************************************************/
{
	UINT16 length = 0;
	UINT16 Index;
	UINT16 VGAGraphCurrentlySelected;
	if (CurrentPreset.PMCCycleCount != 0) {

		length += AddToBuffer(&AckBuf, (UINT8) (PMC_GRAPH >> 8));
		length += AddToBuffer(&AckBuf, (UINT8) PMC_GRAPH);
		length += AddToBuffer(&AckBuf, (UINT8) CurrentPreset.PMCEnabled);
		length += AddToBuffer(&AckBuf,
				(UINT8) (CurrentPreset.PMCCycleCount >> 8));
		length += AddToBuffer(&AckBuf, (UINT8) CurrentPreset.PMCCycleCount);
		length += AddToBuffer(&AckBuf, (UINT8) (CurrentPreset.PMCTimeout >> 8));
		length += AddToBuffer(&AckBuf, (UINT8) CurrentPreset.PMCTimeout);
		if (!CurrentPreset.PMCMinusBandFlag)
			length += AddToBuffer(&AckBuf, (UINT8) CurrentPreset.PMCLowLimit);
		else
			length += AddToBuffer(&AckBuf, 0);
		if (!CurrentPreset.PMCPlusBandFlag)
			length += AddToBuffer(&AckBuf, (UINT8) CurrentPreset.PMCHighLimit);
		else
			length += AddToBuffer(&AckBuf, 0);
		if (CurrentPreset.PMCCycleCount) {
			for (Index = 0; Index < PMCDATAPOINTS; Index++) {
				length += AddToBuffer(&AckBuf,
						(UINT8) CurrentPreset.PMCData[Index]);
			}
		}
	} else {
		VGAGraphCurrentlySelected = NO_VALID_GRAPH;
		length += AddToBuffer(&AckBuf,
				(UINT8) (VGAGraphCurrentlySelected >> 8));
		length += AddToBuffer(&AckBuf, (UINT8) VGAGraphCurrentlySelected);
	}
	return (length);
}

void CheckPMCWithPwrGraph(void)
/****************************************************************************/
/*Description:-                                                             */
/* This function compares average power curve with current Power graph data */
/* and sets +R PMC and -R PMC band flags.                                   */
/****************************************************************************/
{
	UINT16 Index;
	SINT32 TempVal;
	UINT16 SampleCount;
	UINT16 PMCPlusLimitCount;
	UINT16 PMCMinusLimitCount;
	UINT16 TempHighLimit;
	UINT16 TempLowLimit;
	UINT16 TempPrevVal;

	VGAGraphCurrentlySelected = POWGRAPH;
	PMCPlusBandFlag = FALSE;
	PMCMinusBandFlag = FALSE;
	PMCPlusLimitCount = 0;
	PMCMinusLimitCount = 0;

	memcpy(&FinalResults, &WeldingResults, sizeof(WeldingResults));
	MsPointer = MsDataPtr;

	if ((MsPointer->TotalPts != 0) && (CurrentPreset.PMCCycleCount != 0)
			&& (CurrentPreset.PMCEnabled == TRUE)) {

		/*Get Graph Data*/
		SetupVals((WHICHGRAPH) VGAGraphCurrentlySelected, val2);

		GetMaxMinLabel(VGAGraphCurrentlySelected, val2, WeldDataCount,
				&VGAUIVmaxlabel, &VGAUIVminlabel);

		/*Calibrate the Graph data*/
		RecalibVal(val2, VGAGraphCurrentlySelected, VGAUIVmaxlabel,
				VGAUIVminlabel);

		TempHighLimit = (CurrentPreset.PMCHighLimit * 160)
				/ (VGAUIVmaxlabel / 10);
		TempLowLimit = (CurrentPreset.PMCLowLimit * 160)
				/ (VGAUIVmaxlabel / 10);

		if (WeldDataCount < MAX_WELD_SAMPLES)
			SampleCount = WeldDataCount;
		else
			SampleCount = MAX_WELD_SAMPLES;

		for (Index = 0; Index < SampleCount; Index++) {
			if (val2[Index] < 0)
				val2[Index] = 0;

			if (CurrentPreset.PMCData[Index] != 0xFF) {
				TempPrevVal = (UINT16) ((CurrentPreset.PMCData[Index]
						* CurrentPreset.PMCData[PMCDATAPOINTS - 2])
						/ (VGAUIVmaxlabel / 10));
				if (val2[Index] > (SINT32) (TempPrevVal + TempHighLimit)) // + R PMC band check
						{
					ActualValuePMC1 = val2[Index];
					ActualValuePMC1 = (ActualValuePMC1 / 160.0)
							* (VGAUIVmaxlabel / 10);

					PMCPlusLimitCount++;
					if (PMCPlusLimitCount >= CurrentPreset.PMCTimeout) {
						PMCPlusBandFlag = TRUE;
						break;
					}
				} else
					PMCPlusLimitCount = 0;

				TempVal = (SINT32) (TempPrevVal - TempLowLimit);
				if (TempVal < 0)
					TempVal = 0;

				if (val2[Index] < TempVal) // -R PMC band check
						{
					ActualValuePMC2 = val2[Index];
					ActualValuePMC2 = (ActualValuePMC2 / 160.0)
							* (VGAUIVmaxlabel / 10);
					PMCMinusLimitCount++;
					if (PMCMinusLimitCount >= CurrentPreset.PMCTimeout) {
						PMCMinusBandFlag = TRUE;
						break;
					}
				} else
					PMCMinusLimitCount = 0;
			}
		}
	}
	if (PMCPlusBandFlag && !(RunningPreset.PMCPlusBandFlag))
	  RecordAlarm(PR21);
	if (PMCMinusBandFlag && !(RunningPreset.PMCMinusBandFlag))
	  RecordAlarm(PR22);

}
/***************************************END***********************************/
