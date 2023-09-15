/*
 $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/FlowLookupTable.h_v   1.4   16 Apr 2015 07:33:16   rjamloki  $
 */
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*   Copyright (c) Branson Ultrasonics Corporation, 2015                    */
/*   This program is the property of Branson Ultrasonics Corporation        */
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/FlowLookupTable.h_v  $
 * 
 *    Rev 1.4   16 Apr 2015 07:33:16   rjamloki
 * Added PushPopPresetValues declaration
 * 
 *    Rev 1.3   09 Apr 2015 04:46:02   RJamloki
 * Function renamed as per review comment
 * 
 *    Rev 1.2   11 Mar 2015 09:22:02   amaurya
 *  TweakUpHD(),TweakDownHD(),SetDownspeedTuneFlagHD(),SaveDownSpeedTuneHD(),ExitDownSpeedTuneHD() function declaration added for downspeedtuning screen functionality from horndown.
 * 
 *    Rev 1.1   12 Dec 2014 05:26:16   RJamloki
 * Added TweakUp and Down prototypes.
 * 
 *    Rev 1.0   07 Aug 2014 09:24:54   tayars
 * Initial revision.
 */

#ifndef FLOWLOOKUPTABLE_H_
#define FLOWLOOKUPTABLE_H_


void ExitDownSpeedTune(void);
void SaveDownSpeedTune(void);
void SetDownspeedTuneFlag(void);
void SpeedUp(void);
void SpeedDown(void);

SINT32 FlowLookup(SINT32);
void SpeedUpHD(void);
void SpeedDownHD(void);
void SetDownspeedTuneFlagHD(void);
void SaveDownSpeedTuneHD(void);
void ExitDownSpeedTuneHD(void);
void PushPopPresetValues(BOOLEAN);
#endif /* FLOWLOOKUPTABLE_H_ */
