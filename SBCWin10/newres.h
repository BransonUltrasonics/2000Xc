/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/newres.h_v   1.2   28 Mar 2014 14:33:06   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/newres.h_v  $
 * 
 *    Rev 1.2   28 Mar 2014 14:33:06   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:05:02 rjamloki
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:52 amaurya
 * Initial Revision.
*/
 
#ifndef __NEWRES_H__
#define __NEWRES_H__

#define  SHMENUBAR RCDATA
#if !(defined(_WIN32_WCE_PSPC) && (_WIN32_WCE >= 300))
	#undef HDS_HORZ  
	#undef HDS_BUTTONS 
	#undef HDS_HIDDEN 

	#include <commctrl.h>
	// for MenuBar
	#define I_IMAGENONE		(-2)
	#define NOMENU			0xFFFF
	#define IDS_SHNEW		1
	#define IDM_SHAREDNEW        10
	#define IDM_SHAREDNEWDEFAULT 11

	// for Tab Control
	#define TCS_SCROLLOPPOSITE      0x0001   // assumes multiline tab
	#define TCS_BOTTOM              0x0002
	#define TCS_RIGHT               0x0002
	#define TCS_VERTICAL            0x0080
	#define TCS_MULTISELECT         0x0004  // allow multi-select in button mode
	#define TCS_FLATBUTTONS         0x0008	
#endif //_WIN32_WCE_PSPC


#endif //__NEWRES_H__
