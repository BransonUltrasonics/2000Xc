/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/menu7.h_v   1.6   03 Oct 2014 06:25:10   rjamloki  $ */
/****************************************************************************/ 
/*                                                                          */
/*                                                                          */
/*      Copyright (c) Branson Ultrasonics Corporation, 1997                 */
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

   Filename: menu7.h


 --------------------------------- REVISIONS --------------------------------

 --------------------------- FUNCTION PROTOTYPES -----------------------------
*/
extern SINT32 MinParClampDelay ;// = 0;
extern SINT32 MaxPartClampDelay;//  = 10000;
extern SINT32 MinPSWatt;// = 100;
extern SINT32 MaxPSWatt;// = 9999;
extern SINT32 MinLimitForcePC ;//= 49;
extern SINT32 MinLimitVelocityPC;// = 1;
extern SINT32 MaxLimitVelocityPC;// = 10;
extern SINT32 MinLimitGainFactor ;//= 100;
extern SINT32 MaxLimitGainFactor;// = 3000;
extern SINT32 MinLimitMinTrigForce;// = 50;
extern SINT32 MaxLimitMinTrigForce;// = 500;
extern SINT32 MinLimitIdleSpeed;// = 10;
extern SINT32 MaxLimitIdleSpeed;// = 100;

extern SINT32 MinBUCFactoryDefaults;// = 0;
extern SINT32 MaxBUCFactoryDefaults;// = 999999999;

extern SINT32 MinLimitMin ;// 0;
extern SINT32 MaxLimitMax ;// 999999999;
extern SINT32 AlarmPtrMin ;// 0;
extern SINT32 AlarmPtrMax ;// 0x0fffffff;
extern SINT32 EnergyBrakeTimeMin ;// 10;
extern SINT32 EnergyBrakeTimeMax ;// 1000;
extern SINT32 EnergyBrakePercentMin ;// 5;
extern SINT32 EnergyBrakePercentMax ;// 100;
extern SINT32 BUCFactoryDefaults ;// 0;

extern UINT16 FreqControlInt;
extern UINT16 FreqControlExternal;
extern UNION_BOOL_UINT16 FreqControlInternal;

void UpdateAllUserOutputs(void);
void UpdatePresetDateandTime(void);
void SetCurrentUser(void);
void SetAmpControl(void);
void SetFreqControl(void);
void InitCopyFeaturesSetting(void);
void GetPSFreq(void);
void PutPSFreq(void);
void UpdateLanguage(void);
void DealWithExtPresetChange(void);
void VGAResetWeldCounterOk(void);
