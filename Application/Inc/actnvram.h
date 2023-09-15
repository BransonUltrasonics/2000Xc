/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/actnvram.h_v   1.11   Nov 06 2017 16:59:54   RJamloki  $ */
#ifndef ACTNVRAM_H
#define ACTNVRAM_H
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1995, 2009           */
/*     This program is the property of Branson Ultrasonics Corporation      */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/************************                         ***************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/actnvram.h_v  $
 * 
 *    Rev 1.11   Nov 06 2017 16:59:54   RJamloki
 * Remove dead code define AEC
 * 
 *    Rev 1.10   Oct 10 2017 15:48:32   RJamloki
 * add defines id's for micro c actuator
 * 
 *    Rev 1.9   09 Jul 2014 13:01:08   rjamloki
 * Removed load cell support.
 * 
 *    Rev 1.8   21 May 2014 10:49:02   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.4   10 Feb 2014 05:00:02   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:47:24   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- MODULE DESCRIPTION -------------------------------

   Module name:  

   Filename:      actnovram.h


 -------------------------------- REVISIONS ------------------------------------


------------------------------- DESCRIPTION -----------------------------------




 ------------------------------ INCLUDE FILES ----------------------------------
*/  


/*
 ------------------------------- DEFINES ---------------------------------------
*/

#define ACTNOVRAMID         0xAA55
#define NEXTADDRESS         0x0001

// Actuator novram memory map addresses

/* 12 bit Commands */
#define ACTRAMENABLE        0x04c0   /* 010011xxxxxx */
#define ACTRAMDISABLE       0x0400   /* 010000xxxxxx */
#define ACTRAMERASEADDR     0x0700   /* 0111AAAAAAAA */
#define ACTRAMERASEALL      0x0480   /* 01001xxxxxxx */
#define ACTRAMWRITEALL      0x0440   /* 010001xxxxxx */

/* 16 bit Commands */
#define ACTREADRAM          0x0600   /* 00000110AAAAAAAA */
#define ACTWRITERAM         0x0500   /* 00000101AAAAAAAA */

#define ACTIDADDR           0x0000

#define ACTSERNUM1          0x0001
#define ACTSERNUM2          0x0002
#define ACTSERNUM3          0x0003
#define ACTSERNUM4          0x0004
#define ACTSERNUM5          0x0005

#define MAXSERIALNUM        10       /* Total displayable characters.  NULL  */
                                     /* is not stored in NOVRAM, but must be */
                                     /* added when copying into CurrentSetup */
                                     /* or BBR.                              */
                                     
#define ACTLIFETIME1        0x0006
#define ACTLIFETIME2        0x0007

#define ACTSTROKELEN1       0x0008
#define ACTSTROKELEN2       0x0009
#define MESSAGE_DELAY1      1
#define TENMILLS_SLEEP      25
#define PREWRITE            0x0500
#define PREREAD             0x0600
#define ENCODER_ADDR          0xA7

#define EWEN                0x4C0    

#define AENVR   1       /* Make sure this is first in list */
#define AONVR   2
#define AEDNVR  3
#define AODNVR  4
#define AEFNVR  5
#define AOFNVR  6       /* Make sure this is last in list */

#define SBEAM        2  /* Sbeam loadcell */

#define CALIBPASSED  1
#define CALIBFAILED  2
#define CALIBDEFAULT 3

#define FORCE_TABLE_SIZE 6

#define NVR_AE                1
#define NVR_AED               3
#define NVR_AEF               5
#define NVR_MICRO             7
#define NVR_MICROC            9
#define NVR_AES               15

#define DEF_CAL_LENGTH            20000   /* 2 inch stroke is default */

#define AED_MAXFORCE_1_5IN        1590    /* means 159.0 lbs  */
#define AED_MAXFORCE_2_0IN        2820    /* max force at given cylinder size */
#define AED_MAXFORCE_2_5IN        4420    /* actuator type and pressure       */
#define AED_MAXFORCE_3_0IN        6360
#define AED_MAXFORCE_3_25IN       7250
#define AED_MAXFORCE_4_0IN       12500

#define AED_MAXFORCE_32MM         1590    /* means 159.0 lbs  */
#define AED_MAXFORCE_40MM         1753
#define AED_MAXFORCE_50MM         2739
#define AED_MAXFORCE_63MM         4348
#define AED_MAXFORCE_80MM         7012
#define AED_MAXFORCE_CUSTOM      16000

#define AEF_MAXFORCE_1_5IN_60PSI   760
#define AEF_MAXFORCE_2_0IN_60PSI  1540
#define AEF_MAXFORCE_2_5IN_60PSI  2550
#define AEF_MAXFORCE_3_0IN_60PSI  3780
#define AEF_MAXFORCE_3_25IN_60PSI 4480
#define AEF_MAXFORCE_4_0IN_60PSI  7070
#define AEF_MAXFORCE_CUSTOM_60PSI 3780

#define AEF_MAXFORCE_1_5IN_80PSI  1110
#define AEF_MAXFORCE_2_0IN_80PSI  2170
#define AEF_MAXFORCE_2_5IN_80PSI  3530
#define AEF_MAXFORCE_3_0IN_80PSI  5190
#define AEF_MAXFORCE_3_25IN_80PSI 6140
#define AEF_MAXFORCE_4_0IN_80PSI  9580
#define AEF_MAXFORCE_CUSTOM_80PSI 5190
#define NO_LOADCELL_OFFSET         100

#define MICRO_MAXFORCE_40MM       1350

enum ENCODER {
 ENCODER_ENGLISH =  1,   /* English encoder*/
 ENCODER_METRIC =   2    /* Metric encoder */
}; 
/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/                           

struct act_nvr
{
   UINT16 ActId;                   // 1-6 ae, ao, aed, aod, aef, aof
   UINT32 ActualLifeTime;          // Number of Cycles in 1K (x1000 cycles) 
   UINT16 DefStrokeLength;         // 1-A> 4.0 5.0 6.0 7.0 8.0 80 100 125 160 Custom
   UINT16 StrokeLength;            // 1-A> 4.0 5.0 6.0 7.0 8.0 80 100 125 160 Custom
   UINT16 DefCylSize;              // 1-A> 1.5 2.0 2.5 3.0 3.25 40 50 63 80 Custom
   UINT16 CylSize;                 // 1-A> 1.5 2.0 2.5 3.0 3.25 40 50 63 80 Custom
   UINT16 DefSerNum[MAXSERIALNUM]; // 10 Words Default Serial Number
   UINT16 SerNum[MAXSERIALNUM];    // 10 Words Serial Number
   UINT16 DefCalUseName[10];       // 10 Words Default Calibration User Name
   UINT16 CalUseName[10];          // 10 Words Calibration User Name
   UINT16 DefCalDate[3];           // 3 Words Default Calibration date: 04 13 1967
   UINT16 CalDate[3];              // 3 Words Calibration date: 04 13 1967
   SINT16 DefLoadCell[11];         // 11 Words Default Load Cell Table
   SINT16 LoadCell[11];            // 11 Words Load Cell Table
   SINT16 DefPressure[11];         // 11 Words Default Pressure Table
   SINT16 Pressure[11];            // 11 Words Pressure Table
   SINT32 DefForce[FORCE_TABLE_SIZE];      // 6 of SINT32 Default Force Table
   SINT32 Force[FORCE_TABLE_SIZE];         // 6 of SINT32 Force Table
   UINT16 DefDeflection[11];       // 11 Words Default Deflection Table
   UINT16 Deflection[11];          // 11 Words Deflection Table
   UINT32 DefCalStrokeLen;         // Default Calibrated Stroke Length = 2.00in.
   UINT32 CalStrokeLen;            // Calibrated Stroke Length
   SINT16 DefCalSysPressure;       // Default Calibrated System Pressure = 60PSI.
   SINT16 CalSysPressure;          // Calibrated System Pressure
   UINT16 DefCalHomeOffset;        // Used to offset the force table
   UINT16 CalHomeOffset;           // Used to offset the force table
   UINT16 DefSpringRateSlope;      // Set to 5lbs per inch
   UINT16 SpringRateSlope;         // Set when sensor calibration is run
   UINT16 CalibDefPass;            // TRUE for pass
   UINT16 CalibPass;               // 1-3,True,False,Default
   UINT16 PSVersion;               // Software version ie. 8.06
   UINT16 ForceGauge;              // Loadcell or Sbeam
   enum ENCODER EncoderType;       // Encoder Settings
};

/*------------------------------- GLOBAL DATA ------------------------------*/
/*                       (scope is global to ALL files)                     */

extern struct act_nvr NVR;

/*
 --------------------------- FUNCTION PROTOTYPES ---------------------------
*/

void NVRWriteEWEN(void);
void NVRCommandEWDS(void);
void NVRWriteSetup(void);
void NVRWriteVerify( UINT16 Data, UINT16 Address);
void NVRWriteNovram( UINT16 Data, UINT16 Address);
void SetPressure(void);
void SetDefPressure(void);
void SetActId(UINT16 Data);
void SetActLifeTime(void);
void SetDefStrokeLength(UINT16 Data);
void SetStrokeLength(UINT16 Data);                       
void SetDefCylSize(UINT16 Data);
void SetCylSize(UINT16 Data);
void SetDefSerNum(UINT8 *Ptr); 
void SetSerNum(SINT8 *Ptr);
void SetDefLoadCell(void);                                         
void SetLoadCell(void);                                         
void SetDefDeflection(UINT16 *Ptr);                                         
void SetDeflection(UINT16 *Ptr);                                         
void SetDefForce(void);
void SetForceNVR(void);
void SetPSVersionNVR(void);
void UpdateDefForce(void);                                         
void UpdateDefCalHomeOffset(void);
void ActPowerUp(void); 
void ResetActLifeTime(void);
void NvrCopyDeftoNon(void);
void SetCalibrationDate(UINT16 *Ptr);
void SetDefCalibDate(UINT16 *Ptr);
void SetCalibPass(UINT16 Val);
void UpdateCylinderFactor(void);

void SetDefCalStrokeLength(UINT32 Data);                         
void SetDefCalSysPressure(SINT16 Data);
void SetCalStrokeLength(void);                       
void SetCalSysPressure(void);
void UpdateDefCalStrokeLength(void);
void UpdateDefCalSysPressure(void);

void SetDefSpringRateSlope(UINT16 Data);
UINT16 GetDefSpringRateSlope(void);
void GetDefCalStrokeLen(void);
void GetDefHomeOffset(void);
void SetCalSpringRateSlope(UINT16 Data);
void SetCalHomeOffset(void);
void SetDefCalHomeOffset(void);
void UpdateDefSpringRateSlope(void);

UINT16 GetActId(void);
UINT32 GetActLifeTime(void);
UINT16 ReadNVR(UINT16);
UINT16 ActNovramExists(void);
void TestWriteToNvram(void);
void TestReadFromNvram(void);
SINT32 GetMaxForce(void);
UINT16 GetDefStrokeLength(void);
UINT16 GetStrokeLength(void);
UINT16 GetDefCylSize(void);
UINT16 GetCylSize(void);
UINT16 GetCalibPass(void);

void GetDefPressure(void);
void GetDefLoadCell(void);
void GetDefForce(void);
void GetDefCalSysPressure(void);
void InitSetupFromAct(void);
void ActRecover(void);
void UpdateDefPressure(void);
void UpdateDefLoadCell(void);                    

void SetForceGauge(UINT16 Type);
BOOLEAN CheckNvrValid(void); 
BOOLEAN IsCalibPass(void);
BOOLEAN CheckForActChange(void);
enum ENCODER GetEncoderType (void);
void SetEncoderType (enum ENCODER Data);

extern UINT8   NovramEnable;
extern SINT16 ForceTableCylFactor,VelocityTableCylFactor;
#endif
