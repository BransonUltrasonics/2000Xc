/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/DUPS.h_v   1.5   28 Jul 2014 13:02:44   rjamloki  $ */
#ifndef DUPS_H 
#define DUPS_H
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
------------------------- MODULE DESCRIPTION -------------------------------
                                          
   Module name:

   Filename:      dups.h

            Written by: Ashish Sharma 
                  Date: 06/09/00
              Language:  "C"                              


----------------------------- REVISIONS ------------------------------------


------------------------------ DESCRIPTION -------------------------------*/

/* Things needed by DUPS files. The data structures and function prototypes are 
    accessed by DUPS manager and interface files. They are not meant for global
    usage.
*/

/*----------------------------- INCLUDE FILES ------------------------------*/
#include "Dups_api.h"

/*------------------------------- DEFINES ----------------------------------*/


#define DUPS_MAXCOMMAND       2540/* size of command buffer */
#define DUPS_PARAMSETNAMELEN  20 /* Parameter set name is 20 characters */
#define DUPS_CMDHEADER        9  /*bytes in command header and trailer(DLE,Count etc)*/
#define DUPS_INITTRIES        3  /* try first message 3 times then quit*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           

enum DUPS_COMMANDS
{  DUPS_CMDUPLOADHWID           = 512,
   DUPS_CMDUPLOADSWID           = 513,
   DUPS_CMDSELECTPARAMSETNUM    = 514,
   DUPS_CMDREQUESTPARAMSETNUM   = 515,
   DUPS_CMDDOWNLOADPARAMSET     = 516,
   DUPS_CMDUPLOADPARAMSET       = 517,
   DUPS_CMDUPLOADLIBRARYNAME    = 525,
   DUPS_CMDDOWNLOADLIBRARYNAME  = 526,
   DUPS_CMDUPLOADLASTWELDSTATUS = 530,
   DUPS_CMDUPLOADRELEASE        = 540,
   DUPS_CMDDOWNLOADSTARTSCAN    = 545,
   DUPS_CMDUPLOADSCAN           = 546,
   DUPS_CMDNACK                 = 550,
};


enum DUPS_SWDIPBITMASK
{  DUPS_SWDIPBIT0UNUSED       = 0x01,
   DUPS_SWDIPBIT1UNUSED       = 0x02,
   DUPS_SWDIPAMPLITUDEEXTERN  = 0x04,
   DUPS_SWDIPCLEARMEMATRST    = 0x08,
   DUPS_SWDIPSTOREMEMATWLDEND = 0x10,
   DUPS_SWDIPBIT5UNUSED       = 0x20,
   DUPS_SWDIPAUTOSEEK         = 0x40,
   DUPS_SWDIPPOWERUPSEEK      = 0x80,
};


typedef struct
{   UINT8  DLE_Byte;
    UINT8  STX_Byte;
    UINT16 Count;
    UINT16 Cmd;
    UINT8  Cmd_Data[DUPS_MAXCOMMAND];
}   __attribute__((__packed__))  DUPS_CMDBUF;

extern DUPS_CMDBUF DUPS_CmdBuf;

typedef  struct
{   UINT8  ACK_NACK;
    UINT8  DLE_Byte;
    UINT8  STX_Byte;
    UINT16 Count;
    UINT16 Cmd;
    UINT8  Rsp_Data[DUPS_MAXCOMMAND];
}  __attribute__((__packed__)) DUPS_RESPONSEBUF;

extern DUPS_RESPONSEBUF DUPS_RspBuf;

typedef struct
{
   UINT16 PointIndex; 
}    DUPS_HORNSCANCMD;

typedef struct
{  UINT8    ParameterSetName[DUPS_PARAMSETNAMELEN];
   SINT32   Frequency;          /*Same as HW Id Frequency*/
   SINT32   Power;              /*Same as HW Id Power Level */
   SINT32   Variant;            /* apparently Variant = 0 (EQ or Adv?)*/
   SINT32   ReadHWDip;          /* 1 = read HW dip; 0 = SW dip*/
   SINT32   SWDipSetting;       /*meaning described  above */
   SINT32   SeekStartFrequency; /* units = Frequency dependent */
   SINT32   SeekStopFrequency;  /* units = Frequency dependent */
   SINT32   SeekMemoryFrequency;/* units = Frequency dependent */
   SINT32   WeldStartFrequency; /* units = Frequency dependent */
   SINT32   WeldStopFrequency;  /* units = Frequency dependent */
   SINT32   WeldMemoryFrequency;/* units = Frequency dependent */
   SINT32   WeldTime;           /* units = 1 millisecond per bit */
   SINT32   WeldEnergy;         /* units = 100/2047 percent per bit */
   SINT32   Temperature;        /* units = 100/2047 deg Celsius/bit*/
   SINT32   State;              /* see description below */
   SINT32   Reserve1st[5];
   SINT32   ErrorState;         /* see description below */
   SINT32   ErrorReason;        /* see Error Reason descriptions*/
   SINT32   ErrorFrequency;     /* units are Hz */
   SINT32   ErrorPower;         /* units are percent */
   SINT32   ErrorCurrent;       /* units are percent */
   SINT32   ErrorPSV;           /* units 100/255 bits*/
   SINT32   ErrorAmplitude;     /* units are percent */
   SINT32   ErrorTime;          /* msecs - start of sonics to error*/
   SINT32   Reserve2nd[16];
} __attribute__((__packed__)) DUPS_RAWWELDSTATUS;

//extern DUPS_RAWWELDSTATUS DUPS_RawWeldStatus;


typedef  struct       /* ParamIDs */
{  SINT32   DipFlag;            /* DUPS_DIPFLAG */
   SINT32   SWDipSetting;       /*DUPS_SWDIPSETTING  */
   SINT32   SeekAmplitude;      /*DUPS_SEEKAMPLITUDE*/
   SINT32   SeekRampTime;       /*DUPS_SEEKRAMPTIME milisecons*/
   SINT32   SeekTime;           /* DUPS_SEEKTIME  miliseconds*/
   SINT32   SeekFreqLimitHigh;  /*DUPS_SEEKFLIMH  hertz*/
   SINT32   SeekFreqLimitLow;   /* DUPS_SEEKFLIML hertz*/
   SINT32   SeekPhaseLoop;      /* DUPS_SEEKPHLOOPI */
   SINT32   SeekPhaseLoopCF;    /* DUPS_SEEKPHLOOPCF */
   SINT32   SeekAmplitudeLoopC1;/* DUPS_SEEKAMPLOOPC1 */
   SINT32   SeekAmplitudeLoopC2;/*DUPS_SEEKAMPLOOPC2 */
   SINT32   ReservedA[6];
   SINT32   WeldAmplitude;      /*DUPS_WELDAMPLITUDE */
   SINT32   WeldRampTime;       /* DUPS_WELDRAMPTIME */
   SINT32   WeldPhaseLoop;      /* DUPS_WELDPHLOOPI */
   SINT32   WeldPhaseLoopCF;    /* DUPS_WELDPHLOOPCF */
   SINT32   WeldAmplitudeLoopC1;/*DUPS_WELDAMPLOOPC1 */
   SINT32   WeldAmplitudeLoopC2;/* DUPS_WELDAMPLOOPC2 */
   SINT32   WeldFreqLimitHigh;  /* DUPS_WELDFLIMH  hertz*/
   SINT32   WeldFreqLimitLow;   /* DUPS_WELDFLIML  hertz*/
   SINT32   WeldPhaseLimit;     /* DUPS_WELDPHLIM */
   SINT32   WeldPhaseLimitTime; /* DUPS_WELDPHLIMTIME  miliseconds*/
   SINT32   Reserved[15];
}  __attribute__((__packed__))DUPS_RAWPARAMSET;

extern DUPS_RAWPARAMSET DUPS_RawParamSet;


typedef  struct
{  UINT8    ParameterSetNum;
   UINT8    ParameterSetName[DUPS_PARAMSETNAMELEN];
   SINT32   Frequency;
   SINT32   Power;
   SINT32   Variant;
   DUPS_RAWPARAMSET Paramset;
} __attribute__((__packed__)) DUPS_DOWNLOADPARAMCMD;           /* DUPSParameterMsg */


typedef  struct
{  UINT8    ParameterSetName[DUPS_PARAMSETNAMELEN];
   SINT32   Frequency;
   SINT32   Power;
   SINT32   Variant;
   DUPS_RAWPARAMSET Paramset;
}  __attribute__((__packed__))DUPS_UPLOADPARAMRSP;           /* DUPSParameterMsg */

extern DUPS_DOWNLOADPARAMCMD DUPS_DownloadParamCmd;
extern DUPS_UPLOADPARAMRSP DUPS_UploadParamRsp;


/* constants used to control the state of Horn Scan Processing */
enum HORNSCANSTATES
{
   HORNSCANABORTED = -1,
   HORNSCANIDLE = 0,
   HORNSCANSTARTED,
   HORNSCANCOLLECTING,
   HORNSCANCALCULATING,
   HORNSCANCOMPLETED,
}  ;


typedef struct
{  UINT16  Frequency;
   SINT16  PSV;
   SINT16  Amplitude;
   SINT16  Current;
   SINT16  Power;
   SINT16  Phase;
   SINT16  Status;
}  __attribute__((__packed__)) HORNSCANPOINT;

extern HORNSCANPOINT HornScanPoint;


/* The values for Scan Point status are in the following enumeration. */
enum HORNScanPointStatus
{  HornScanPointValid    = 0,
   HornScanPointLast     = 1,
   HornScanPointNotValid = 2
};

enum { HS_POINTCOUNT = 400 };

/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/
/* Dups protocol functions */
void DUPS_Manager(void);
enum DUPS_RESULTS DUPS_DataXfer(void);

/* DUPS Messaging functions */
enum DUPS_RESULTS DUPS_MsgUploadHWId(void);
enum DUPS_RESULTS DUPS_MsgUploadSWId(void);
enum DUPS_RESULTS DUPS_MsgSelectParamSetNum(UINT8 psNum);
enum DUPS_RESULTS DUPS_MsgReqParamSetNum(void);
enum DUPS_RESULTS DUPS_MsgDownloadParamSet(UINT8 psNum);
enum DUPS_RESULTS DUPS_MsgUploadParamSet(UINT8 psNum);
enum DUPS_RESULTS DUPS_MsgUploadLibraryName(void);
enum DUPS_RESULTS DUPS_MsgDownloadLibraryName(void);
enum DUPS_RESULTS DUPS_MsgUploadReleaseId(void);
enum DUPS_RESULTS DUPS_MsgDownloadStartScan(void);
enum DUPS_RESULTS DUPS_MsgInitInterface(void);
enum DUPS_RESULTS DUPS_MsgHornScanStep(SINT16 scanStep);
//enum DUPS_RESULTS DUPS_MsgHornScanAbort(void);
enum DUPS_RESULTS DUPS_MsgUploadScanPt(void);

SINT32 DUPS_FreqD2C(SINT32 DUPSFreq);
SINT32 DUPS_FreqC2D(SINT32 COPFreq);

/* Function prototypes for DUPS HornScan functions */

void HS_Resonance(void);
void HS_FirFilt( SINT16 vector[], UINT16 vectsize);
enum DUPS_RESULTS HS_CrossingExists (SINT16 vector[], SINT16 vectsize);
void HS_4Clusters(void);
UINT16 HS_X4YZero(UINT16 xcap[], SINT16 ycap[],UINT16 vectsize);
void HS_UpdateVFDLine(UINT16 index);
UINT16 HS_Decimate(SINT16 * curr_in, SINT16 * phase_in,SINT16 * Amp_in, UINT16 count,
                    SINT16 * curr_out, SINT16 * phase_out,SINT16 * Amp_out);
void HS_FindPhaseIndex(SINT16 * phase, UINT16 base_index, UINT16 count,UINT16 result[2]);


#endif  /* DUPS_H */
