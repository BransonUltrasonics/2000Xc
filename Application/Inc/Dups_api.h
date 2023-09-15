/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/Dups_api.h_v   1.9   28 Nov 2014 07:54:56   rjamloki  $ */
#ifndef DUPS_API_H 
#define DUPS_API_H
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 1996, 2009     */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/************************                         ***************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/Dups_api.h_v  $
 * 
 *    Rev 1.9   28 Nov 2014 07:54:56   rjamloki
 * DUPS_StartHornScan() removed.
 * 
 *    Rev 1.8   10 Nov 2014 04:39:44   AnPawar
 * dups diagnostic added in enum DUPS_MESSAGES. 
 * 
 *    Rev 1.7   26 Sep 2014 02:58:40   rjamloki
 * Removed psos references
 * 
 *    Rev 1.6   28 Jul 2014 13:00:36   rjamloki
 * bbram to fram renaming
 * 
 *    Rev 1.5   21 May 2014 10:49:04   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:08   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:47:44   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
------------------------- MODULE DESCRIPTION -------------------------------
                                          
   Module name:

   Filename:      dups_api.h

            Written by: Sunil R. Patil 
                  Date: 06/09/00
              Language:  "C"                              


----------------------------- REVISIONS ------------------------------------


------------------------------ DESCRIPTION -------------------------------*/


/* This file contains global DUPS data                                      */


/*----------------------------- INCLUDE FILES ------------------------------*/

#include "battram.h"

/*------------------------------- DEFINES ----------------------------------*/

/* This file contains global data*/


#define DUPS_LIBRARYNAMELEN    20    /* DUPS library name string length */
#define DUPS_PARAMSETNAMELEN   20    /* DUPS Param Set mane string length */
#define DUPS_NUMPARAMSET       20    /* Number of DUPS Presets */
#define DUPS_CURRPARAMSET      (DUPS_NUMPARAMSET -1)   /* reserved slot for current parameter set */
#define DUPS_NUMRESONANCES     6     /* Number of Horn Scan Resonance Freqs detected */ 
#define DUPS_HORNSCANPOINTS    400   /* Number of Horn Scan points printed and stored 
                                        in FRAM */
#define DUPS_HORNSCANMAXPOINTS 1000  /* Max points queried for analysis */
#define DUPS_TIMELIMIT         50   /* 50 RSOS ticks for timeout = 500 ms */
#define HS_NUMCOEFS           17     /* Coff required for filter to smooth out the scan phase data */
#define HS_NUMRAWPHASEPOINTS  (DUPS_HORNSCANMAXPOINTS+HS_NUMCOEFS)

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           


/*These values are used for the error reason codes in the Weld Status report*/
enum DUPS_ERROR_REASON
{  DUPS_POWEROVERLOAD     = 0x01,
   DUPS_CURRENTOVERLOAD   = 0x02,
   DUPS_VOLTAGEOVERLOAD   = 0x04,
   DUPS_THERMALOVERLOAD   = 0x08,
   DUPS_FREQLIMITSEEKLOW  = 0x10,
   DUPS_FREQLIMITSEEKHIGH = 0x20,
   DUPS_FREQLIMITWELDLOW  = 0x40,
   DUPS_FREQLIMITWELDHIGH = 0x80,
   DUPS_PHASELIMIT        = 0x100,
};


/*These values are used in the Weld Status Report for State and Error State*/
enum DUPS_STATE
{  DUPS_NOERROR = 0,
   DUPS_RESET   = 1,
   DUPS_ERROR   = 2,
   DUPS_READY   = 3,
   DUPS_SEEK    = 4,
   DUPS_WELD    = 5,
};


enum DUPS_FREQCONVERSION   /*The appropriate units are as follows:*/
{   DUPS_15KHZ = 3,   /*  15Khz Units = (3 * 0.0025) 0.075hz/bit*/ 
    DUPS_20KHZ = 4,   /*  20Khz Units = (4 * 0.025 ) 0.100hz/bit*/
    DUPS_30KHZ = 6,   /*  30Khz Units = (6 * 0.025 ) 0.150hz/bit*/
    DUPS_40KHZ = 8    /*  40hz  Units = (8 * 0.025 ) 0.200hz/bit*/
};

enum DUPS_PSFREQ             /* The values of the power supply frequencies for the 15khz,20khz,30khz and 40khz*/
{                            /* welders used to populate HornScanInfo structure during initialization.Values are */
  DUPS_MIN15AND30 = 195000,  /* the same for 15khz and 30khz welders AND */                             
  DUPS_MAX15AND30 = 205000,  /*              20khz and 40khz welders.  */
  DUPS_MIN20AND40 = 194500,
  DUPS_MAX20AND40 = 204500
};

/*Parameter Set Status is maintained for each DUPS parameter Sets*/
enum DUPS_LOCK
{  DUPS_PARAMSETLOCKED = 0x01,
   DUPS_PARAMSETAVAIL= 0x02,
   DUPS_PARAMSETSAVED = 0x04};

#define DUPS_PARAMSETUNDEF 255 /*used in x-ref tables when no associated preset*/

/*These values placed in the Operation Status field of the user provided data area when a
DUPS request is made*/
enum DUPS_RESULTS
{  DUPS_PENDING = -1,   /*Transefer or operation is in progress*/
   DUPS_SUCCESS =  0,   /*successfully completed*/
   DUPS_NACK,           /*DUPS board return an error*/  
   DUPS_TIMEOUT,        /*operation did not complete within alotted time*/
   DUPS_CHECKSUM,       /*DUPS board reported or DUPS interface detected error*/
   DUPS_OTHER};         /*other interface error*/


/*The values for Scan Status are defined in following enum*/
enum DUPS_HORNSCANSTATE
{  DUPS_NOSCAN    = 0,
   DUPS_SCANINPROG,
   DUPS_SCANSCOMPLETE,
   DUPS_SCANDATAAVAIL};

/* Resonance Frequency Types*/
enum RESONANCE_FREQ_TYPE
{   FREQ_NONE,
    FREQ_SERIES,
    FREQ_PARALLEL};   


/*These are messages sent to DUPS Manager*/
enum DUPS_MESSAGES
{   DUPS_MSGUPLOADHWID       = 1,
    DUPS_MSGUPLOADSWID,
    DUPS_MSGSELECTPARAMSETNUM,
    DUPS_MSGREQUESTPARAMSETNUM,
    DUPS_MSGDOWNLOADPARAMSET,
    DUPS_MSGUPLOADPARAMSET,
    DUPS_MSGUPLOADLIBRARYNAME,
    DUPS_MSGDOWNLOADLIBRARYNAME,
    DUPS_MSGUPLOADLASTWELDSTATUS,
    DUPS_MSGUPLOADRELEASE,
    DUPS_MSGDOWNLOADSTARTSCAN,
    DUPS_MSGUPLOADSCANPOINT,
    DUPS_MSGINITINTERFACE,  
    DUPS_MSGHORNSCANSTEP,
    DUPS_MSGHORNSCANABORT,
    DUPS_MSGSENABLEDIAGNOSTIC,
    DUPS_MSGLASTMESSAGE

};

/*DUPS Preset Mapping and Status*/
//extern UINT8 DUPS2COP[DUPS_NUMPARAMSET]; /* DUPS_NUMPRESET */
//extern UINT8 COP2DUPS[MAX_PRESETS + 1]; /*DUPS_NUMPRESET*/
//extern UINT16 DUPS_Lock[DUPS_NUMPARAMSET]; /*Avail,Locked,Saved*/
 
/*DUPS information structure: indicates whether or not a DUPS has been detected*/
typedef struct 
{  UINT16    DUPSFlag;                  /*TRUE if DUPS detected*/
   BOOLEAN    DUPSMemFlag;               /* Memory on off flag */
   BOOLEAN    DUPSMemRstFlag;            /* Memory reset flag */
   BOOLEAN    DUPSSeekFlag;              /* Timed seek on off flag */
   UINT16    WeldStatusFlag;            /* Request weld status on overload*/
   SINT32    ProgramId;                 /* SW ID from command 513 */
   UINT16    FlashVersion;              /* Flash version from command 513 */
   UINT16    ActiveWorkNum;             /* current DUPS Preset */
   UINT16    PowerSupplyFreq;           /* system enum */
   UINT16    FreqConversion;            /* 0.025 Hz / bit */
   UINT16    PowerSupplyWatts;          /* Value in Watts   */
   UINT16    LastFunction;              /* Added for dioganostic purpose*/
   SINT16    LastStatus;                /* Added for dioganostic purpose*/
   UINT8     RspCE1;                    /* Added for dioganostic purpose*/
   UINT8     RspCE2;                    /* Added for dioganostic purpose*/
   UINT8     RspFE1;                    /* Added for dioganostic purpose*/
   UINT8     RspFE2;                    /* Added for dioganostic purpose*/
   UINT8     ACKorNACK;                 /* Added for dioganostic purpose*/
   UINT8     LibraryName[DUPS_LIBRARYNAMELEN +1];/*ASCII characters*/
 } DUPS_INFO;
extern DUPS_INFO DUPS_Info; 


// This string contains the uploaded parameter set names during initialization.

//extern STR DUPS_ParamSetName[DUPS_NUMPARAMSET][DUPS_PARAMSETNAMELEN + 1];
//extern STR *DUPS_PsNamePTR[DUPS_NUMPARAMSET][9];

/*The weld status report contains a subset of the data received for the last weld*/
typedef struct 
{  UINT8    ParameterSetName[DUPS_PARAMSETNAMELEN];
   SINT16   OpStatus;    /*progress of command to retrive data - Pending, Success, etc*/
   SINT16   DataStatus;          /*validity of data upon completion of command */
   SINT32   Frequency;          /*Same as HW Id Frequency*/
   SINT32   Power;              /*Same as HW Id Power Level */
   SINT32   Variant;            /* apparently Variant = 0 (EQ or Adv?)*/
   SINT32   ReadHWDip;          /* 1 = read HW dip; 0 = SW dip*/
   SINT32   SWDipSetting; /*meaning described  above */
   SINT32   SeekStartFrequency; /* units = Frequency dependent */
   SINT32   SeekStopFrequency;  /* units = Frequency dependent */
   SINT32   SeekMemoryFrequency;/* units = Frequency dependent */
   SINT32   WeldStartFrequency; /* units = Frequency dependent */
   SINT32   WeldStopFrequency;  /* units = Frequency dependent */
   SINT32   WeldMemoryFrequency;/* units = Frequency dependent */
   SINT32   WeldTime;            /* units = 1 millisecond per bit */
   SINT32   WeldEnergy;         /* units = 100/2047 percent per bit */
   SINT32   Temperature;         /* units = degree F*/
   SINT32   State;               /* see DUPS state enumeration*/
   SINT32   ErrorState;          /* see DUPS state enumeration*/
   SINT32   ErrorReason;         /* see Error Reason enumeration*/
   SINT32   ErrorFrequency;      /* units are Hz */
   SINT32   ErrorPower;          /* units are percent */
   SINT32   ErrorCurrent;        /* units are percent */
   SINT32   ErrorPSV;            /* units 100/255 bits*/
   SINT32   ErrorAmplitude;      /* units are percent */
   SINT32   ErrorTime;           /*millisecs - start of sonics to error*/
}  DUPS_WELDSTATUS;

extern DUPS_WELDSTATUS DUPS_WeldStatus;
                                                  



extern DUPS_CURRENTPARAMSET DUPS_CurrentParamSet;
extern SINT16  DUPS_CurrPSStatus;       /* Set to Pending for upload, DUPS_SUCCESS when complete*/
extern DUPS_CURRENTPARAMSET DUPS_MaxParamSet;
extern DUPS_CURRENTPARAMSET DUPS_MinParamSet;

/*DUPS message buffer is used to send messages to DUPS Manager*/
typedef struct 
{   enum DUPS_MESSAGES mt;    /* message type see DUPS message enumeration */
    UINT16 data1; /* Data value to use in DUPS Manager */
    UINT32 data2; /* Data value to use in DUPS Manager */
    UINT32 data3; /* Data value to use in DUPS Manager */
    UINT32 data4; /* Data value to use in DUPS Manager */
}   DUPS_MSGBUF;

extern DUPS_MSGBUF DUPS_MsgBuf;

/*Horn scan information structure contains data about the parameters and status 
of the most recent scan*/
typedef struct 
{  SINT32   StartFreq;        /* hertz */
   SINT32   StopFreq;         /* hertz */
   SINT32   FreqStep;         /* 0.025 / bit */
   SINT32   TimeDelay;        /* miliseconds */
   SINT32   MaximumAmplitude; /* % */ 
   SINT32   MaximumCurrent;   /* % */
   UINT8    ScanStatus;
   UINT16   NumScanPoints;
   SINT32   ResonanceFreqs[DUPS_NUMRESONANCES]; /* hertz */
   enum RESONANCE_FREQ_TYPE ResonanceFreqType[DUPS_NUMRESONANCES];
   SINT32   Year;
   SINT32   Month;
   SINT32   Day;
   SINT32   Hour;
   SINT32   Minute;
}  HORNSCANINFO;

extern HORNSCANINFO HornScanInfo; 
extern HORNSCANINFO HS_MaxScanInfo;
extern HORNSCANINFO HS_MinScanInfo;

typedef struct 
{  SINT32   StartFreq;        /* hertz */
   SINT32   StopFreq;         /* hertz */
   SINT32   FreqStep;         /* 0.025 / bit */
   SINT32   TimeDelay;        /* miliseconds */
   SINT32   MaximumAmplitude; /* % */ 
   SINT32   MaximumCurrent;   /* % */
}  DUPS_STARTSCANCMD;

extern DUPS_STARTSCANCMD DUPS_StartScanCmd;
/*Horn scan information structure contains max and min limits data about 
the parameters */
typedef struct 
{  UINT16   MaxFreq;             /* hertz */
   UINT16   MinFreq;             /* hertz */
   UINT16   MaxTimeDelay;        /* miliseconds */
   UINT16   MinTimeDelay;        /* miliseconds */
   UINT16   MaxAmplitude;        /* % */ 
   UINT16   MaxCurrent;          /* % */
}  HS_LIMITS;

extern HS_LIMITS HS_Limits;

/*DUPS Horn Scan data for Most recent Horn Scan stored in FRAM*/
extern SINT16  *HornScanCurrent;
extern SINT16  *HornScanPhase;
extern SINT16  *HornScanAmp;

extern BOOLEAN DUPSChangePending;
enum DUPS_CHANGE { DOWNLOAD_PENDING = 1, UPLOAD_PENDING };
extern enum DUPS_CHANGE DUPSChange;
extern UINT16 DUPSUploadPSPending; /* upload param set number */

/*  
 ----------------------------- FUNCTION PROTOTYPES -----------------------------
*/
enum DUPS_RESULTS DUPS_MsgUploadWeldStatus(DUPS_WELDSTATUS * outbuf);
UINT16 DUPS_SetDUPSParamSet(UINT16 COPps);
void   DUPS_ClearDUPSParamSet(UINT16 COPps);
UINT16 DUPS_FindCOP4DUPS(UINT16 DUPSps);
//UINT16 DUPS_FindDUPS4COP(UINT16 COPps);
void   DUPS_ModifySWDipSetting( void );
void   DUPS_SelectParamSetNum(SINT32 psNum);
void   DUPS_UploadParamSet(UINT16 psNum);
void   DUPS_GetLastWeldStatus(DUPS_WELDSTATUS *buf);
void   DUPS_DownloadCurrPS(void);
void   DUPS_QueuedDownloadPS(void);
//void   DUPS_QueuedUploadPS(UINT16 psNum);
void   DUPS_Wait4CurrPS(void);
void   DUPS_DownloadParamSet(UINT16 psNum);
enum DUPS_RESULTS DUPS_ChkParamLimit(void);
void   DUPS_HornScanAbort(void);
void   DUPS_FRAM2RAM(void);
void   DUPS_RAM2FRAM(void);

#endif  /* DUPS_API_H */
