/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/limits.h_v   1.7   09 Apr 2015 04:49:10   RJamloki  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/***************************************************************************/
/*                                                                         */
/*  These defines are the bit assignments for both Reject and Suspect      */
/*  limits.  BIT0 is reserved for globally enabling or disabling all       */
/*  limits within the group.  BIT15 is unused.                             */
/*                                                                         */
/*  Notes: The M prefix in each name stands for Minus and the P stands     */
/*         for Plus.  For example, MTIMEBIT is the minus time bit.         */
/*                                                                         */
/*         The FORCE define is for Max Force during the weld cycle.        */
/*                                                                         */
/***************************************************************************/

#define MENERGYBIT    BIT1
#define PENERGYBIT    BIT2
#define MPKPOWERBIT   BIT3
#define PPKPOWERBIT   BIT4
#define MCOLDISTBIT   BIT5
#define PCOLDISTBIT   BIT6
#define MABSDISTBIT   BIT7
#define PABSDISTBIT   BIT8
#define MTRIGDISTBIT  BIT9 
#define PTRIGDISTBIT  BIT10
#define MFORCEBIT     BIT11
#define PFORCEBIT     BIT12
#define MTIMEBIT      BIT13
#define PTIMEBIT      BIT14
#define MVELOCITYBIT  BIT15
#define PVELOCITYBIT  BIT16

#define MSBLFREQBIT   BIT19
#define PSBLFREQBIT   BIT20

#define MTOTCYCLETIMEBIT  BIT9
#define PTOTCYCLETIMEBIT  BIT10
#define MWELDCOLLAPSEBIT  BIT0 
#define PWELDCOLLAPSEBIT  BIT15

#define MPRESSURELIMITBIT BIT1
#define PPRESSURELIMITBIT BIT2

#define MDOWNSPEEDLIMITBIT BIT0
#define PDOWNSPEEDLIMITBIT BIT1

/*Bits for Setup limits*/
#define WELDPRESSURE_PBIT   BIT1
#define WELDPRESSURE_MBIT   BIT2
#define HOLDPRESSURE_PBIT   BIT3
#define HOLDPRESSURE_MBIT   BIT4
#define HOLDTIME_PBIT       BIT5
#define HOLDTIME_MBIT       BIT6
#define AMPA_PBIT           BIT7
#define AMPA_MBIT           BIT8
#define DOWNSPEED_PBIT      BIT9
#define DOWNSPEED_MBIT      BIT10
#define TRIGFORCE_PBIT      BIT11
#define TRIGFORCE_MBIT      BIT12
#define WELDTIME_PBIT       BIT13
#define WELDTIME_MBIT       BIT14

#define WELDENERGY_PBIT		BIT1
#define WELDENERGY_MBIT		BIT2
#define PEAKPWR_PBIT		BIT3
#define PEAKPWR_MBIT		BIT4
#define COLDIST_PBIT		BIT5
#define COLDIST_MBIT		BIT6
#define ABSDIST_PBIT		BIT7
#define ABSDIST_MBIT		BIT8
#define SCRUBTIME_PBIT		BIT9
#define SCRUBTIME_MBIT		BIT10
#define AMPSCRUBTIME_PBIT	BIT11
#define AMPSCRUBTIME_MBIT	BIT12
#define TRIGDIST_PBIT      	BIT13
#define TRIGDIST_MBIT      	BIT14

/***************************************************************************/
/*                                                                         */
/*  This set of masks is used to eliminate those reject or suspect limits  */
/*  which are invalid in certain weld modes.                               */
/*                                                                         */
/***************************************************************************/

#define TIMEMODEMASK    (MENERGYBIT | PENERGYBIT | MPKPOWERBIT | PPKPOWERBIT | MCOLDISTBIT | PCOLDISTBIT | MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT | MFORCEBIT | PFORCEBIT)
#define ENERGYMODEMASK  (MTIMEBIT | PTIMEBIT | MENERGYBIT | PENERGYBIT | MPKPOWERBIT | PPKPOWERBIT | MCOLDISTBIT | PCOLDISTBIT | MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT | MFORCEBIT | PFORCEBIT)
#define PKPOWERMODEMASK (MTIMEBIT | PTIMEBIT | MENERGYBIT | PENERGYBIT | MCOLDISTBIT | PCOLDISTBIT | MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT | MFORCEBIT | PFORCEBIT)
#define COLLMODEMASK    (MTIMEBIT | PTIMEBIT | MENERGYBIT | PENERGYBIT | MPKPOWERBIT | PPKPOWERBIT | MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT | MFORCEBIT | PFORCEBIT| MCOLDISTBIT | PCOLDISTBIT)
#define ABSMODEMASK     (MTIMEBIT | PTIMEBIT | MENERGYBIT | PENERGYBIT | MPKPOWERBIT | PPKPOWERBIT | MCOLDISTBIT | PCOLDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT | MFORCEBIT | PFORCEBIT | MABSDISTBIT | PABSDISTBIT)
#define GNDDETMODEMASK  (MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT | MFORCEBIT | PFORCEBIT | MTIMEBIT | PTIMEBIT)
#define CONTMODEMASK    (MPKPOWERBIT | PPKPOWERBIT)

#define ALLMODEMASK     (MENERGYBIT | PENERGYBIT | MPKPOWERBIT | PPKPOWERBIT | MCOLDISTBIT | PCOLDISTBIT | MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT | MFORCEBIT | PFORCEBIT | MTIMEBIT | PTIMEBIT)


/***************************************************************************/
/*                                                                         */
/*  This set of masks is used to eliminate those reject or suspect limits  */
/*  which are not valid for certain products or models.                    */
/*                                                                         */
/***************************************************************************/

#define CTRL_LEVEL_tMASK      (0)
#define CTRL_LEVEL_eMASK      (CTRL_LEVEL_tMASK | MENERGYBIT | PENERGYBIT | MPKPOWERBIT | PPKPOWERBIT | MTIMEBIT | PTIMEBIT)
#define CTRL_LEVEL_eaMASK      (CTRL_LEVEL_eMASK)
#define CTRL_LEVEL_dMASK      (CTRL_LEVEL_eaMASK | MCOLDISTBIT | PCOLDISTBIT | MABSDISTBIT | PABSDISTBIT | MTRIGDISTBIT | PTRIGDISTBIT | MFORCEBIT | PFORCEBIT)
#define CTRL_LEVEL_fMASK      (CTRL_LEVEL_dMASK)
                            
struct SetupMinMax {
	UINT16 ID;
	UINT16 *MaskVar;
	UINT16 MinMask;
	UINT16 Maxmask;
	SINT32 MinLimit;
	SINT32 MaxLimit;
	SINT32 MinLimMLT;
	SINT32 MaxLimPLT;
	SINT32 CurrentValue;
	UINT16 MBIT;
	UINT16 PBIT;
	BOOLEAN UseOriginalMinMax;
};
BOOLEAN IsRejectLimitsEnabled();
void SetupLimitChanged(void);
void PreSetupLimitMinMax(UINT16 ID);
void SetSetupLimits(struct SetupMinMax *paramLim);
extern SINT32 MinSetupLim;
extern SINT32 MaxSetupLim;

