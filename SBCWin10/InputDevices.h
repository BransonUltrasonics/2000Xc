/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/InputDevices.h_v   1.1   16 Apr 2015 06:25:44   sesharma  $*/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/InputDevices.h_v  $
 * 
 *    Rev 1.1   16 Apr 2015 06:25:44   sesharma
 * New file to support auto hide of cursor if mouse is not plugged in.
 * 
 *    Rev 1.0   16 Apr 2015 06:22:54   sesharma
 * Initial revision.
*/
#if !defined(INPUTDEVICES_H)
#define INPUTDEVICES_H

	void MouseDetect(bool FirstTime);
	void MouseTimerInit();
	void KillMouseTimer();

#endif