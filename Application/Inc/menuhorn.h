/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/menuhorn.h_v   1.8   16 Apr 2015 15:01:50   rjamloki  $*/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/menuhorn.h_v  $
 * 
 *    Rev 1.8   16 Apr 2015 15:01:50   rjamloki
 * Added new line in the end of file to remove compiler warning
 * 
 *    Rev 1.7   16 Mar 2015 02:29:22   rjamloki
 * HdTempParamSet structure created to keep pressure and downspeed values during horn down
*/

#ifndef MENUHORN_H
#define MENUHORN_H

/*
 ------------------------------ INCLUDE FILES --------------------------------
*/
#include "portable.h"

/*
 ----------------------------- FUNCTION PROTOTYPES -------------------------
*/
void HornDownISR(void);

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
 ---------------------------- PRIVATE GLOBAL DATA ----------------------------
                        (scope is global to THIS file)
*/


/*
 ---------------------------- EXTERNAL FUNCTIONS -------------------------------
*/


/*
 --------------------------- LOCAL FUNCTION PROTOTYPES -------------------------
*/



/*
 ---------------------------------- CODE -------------------------------------
*/


/*
 ------------------------------- GLOBAL DATA ---------------------------------
                        (scope is global to ALL files)
*/

extern BOOLEAN HornDownFlag;     /* When TRUE disables state machine */
extern BOOLEAN VGAHornDown;
extern UINT16 VGAAction;
void VGAProcessHornDownMsg (void);


//struct contain values of pressure and flow parameters during horn down.
struct HdTempParamSet
{
	SINT32 WeldPressure;
	SINT32 DownSpeed;
	UINT8 TunedFlowValue;
	SINT32 TempDownSpeed;
	BOOLEAN DownSpeedTuned;
};

extern HdTempParamSet HdParams;

#endif

