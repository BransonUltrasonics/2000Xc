/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/VPRESET4.H_v   1.3   05 Mar 2014 13:57:42   rjamloki  $ */
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

/*--------------------------- MODULE DESCRIPTION ---------------------------*/

/*   Module name: VPRESET_MODEL4                                            */

/*   Filename:    vpreset4.h                                                */

/*------------------------------- REVISIONS --------------------------------*/
/*                                                                          */
/*                                                                          */
/*                                                                          */


/*------------------------------ DESCRIPTION -------------------------------*/



/*----------------------------- INCLUDE FILES ------------------------------*/

#include "portable.h"            /* fundamental data object types       */


UINT32 VerifyPresetModel4(void);
BOOLEAN CheckForValidDistances(SINT32 MaxStroke);
BOOLEAN CheckForValidForces(UINT32 MaximumForce);



