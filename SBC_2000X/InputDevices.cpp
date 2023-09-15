/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/InputDevices.cpp_v   1.2   16 Apr 2015 14:18:14   rjamloki  $*/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/InputDevices.cpp_v  $
 * 
 *    Rev 1.2   16 Apr 2015 14:18:14   rjamloki
 * Coverity fixes done before release
 * 
 *    Rev 1.1   16 Apr 2015 06:25:44   sesharma
 * New file to support auto hide of cursor if mouse is not plugged in.
 * 
 *    Rev 1.0   16 Apr 2015 06:22:54   sesharma
 * Initial revision.
*/
#include "stdafx.h"
#include "VGA.h"
#include "InputDevices.h"
#include <devguid.h>
#include <Dbt.h>
#include <WinBase.h>
#include <stdio.h>
#include "ChildView.h"

#define PLUGIN true
#define PLUGOUT false

bool Mstate;
static bool MouseState = false;
#define MOUSE_EVENT_TIME 5000
#define NUM_PREKNOWN_VENDORIDS 2
/*
Below are pre-known vendor and product Ids of HID devices/drivers installed in SBC system.
We need no ignore them while checking for mouse plug in/out for cursor change requirement.
*/
CString PreKnownVendorIds[NUM_PREKNOWN_VENDORIDS] = 
							{
							_T("Vid_0596&Pid_0003"),
							_T("Vid_0430&Pid_0508"),
							};
/**************************************************************************************************************
*	This Function is called at power up and when ever a device change notification is received. 
* It detects whether mouse is plugged in or not by parsing the RawInputDevice lists using windows api functions.
* If mouse is detected cursor is drawn else cursor is removed. On windows embedded standard function takes around ~2
* ms in execution
***************************************************************************************************************/
void MouseDetect(bool FirstTime)
{
	UINT nDevices;
	int nNoOfDevices = 0;
	RID_DEVICE_INFO rdi;
	int i = 0, j;
	bool Skip;
	UINT size = 256;
	TCHAR tBuffer[256] = {0};
	PRAWINPUTDEVICELIST pRawInputDeviceList;
	CString S = "";
	if (GetRawInputDeviceList(NULL, &nDevices, sizeof(RAWINPUTDEVICELIST)) == 0)//Firsr find number of devices
	{
		//allocate buffer big enough to retrieve all devices information
		if ((pRawInputDeviceList = (PRAWINPUTDEVICELIST)malloc(sizeof(RAWINPUTDEVICELIST) * nDevices)) != NULL) 
		{
			if ((nNoOfDevices = GetRawInputDeviceList(pRawInputDeviceList, &nDevices, sizeof(RAWINPUTDEVICELIST))) != ((UINT) - 1)) 
			{
					rdi.cbSize = sizeof(RID_DEVICE_INFO);
					for(i = 0; i < nNoOfDevices; i++)
					{        
						if(MouseState == true)
						{
							if(!FirstTime)
								KillMouseTimer();
							free(pRawInputDeviceList);
							return;
						}
   						
						if(GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICENAME, tBuffer, &size) != ((UINT) - 1))//coverity 12569
						{
							S = tBuffer;
							Skip = false;
							for(j = 0; (j < NUM_PREKNOWN_VENDORIDS) && (Skip == false); j++)
							{
								if(S.Find(PreKnownVendorIds[j], 0) != -1)
									Skip = true;
						    }
							if(Skip)
								continue;							
						}				
						
						UINT cbSize = rdi.cbSize;
						if(GetRawInputDeviceInfo(pRawInputDeviceList[i].hDevice, RIDI_DEVICEINFO, &rdi, &cbSize) != ((UINT) - 1))
						{				
							if(rdi.dwType == RIM_TYPEMOUSE)
							{			
								if(rdi.mouse.dwNumberOfButtons == 3)
								{
									while(ShowCursor(PLUGIN) <= 0);
										Mstate = PLUGIN;								
									MouseState = true;				
								}
								else
								{
									while(ShowCursor(PLUGOUT) >= 0);
										Mstate = PLUGOUT;
								}
							}
						}
					}
			}
			free(pRawInputDeviceList);//coverity 12574
		}		
	}	
	if(!FirstTime)
		KillMouseTimer();
}

/**************************************************************************************************************
*	This Function is called from OnDeviceChange windows event. It start a 5 second timer. Call back of the timer
*   calls MouseDetect function and determine the state(plugged/unplugged) of mouse. The reason fro 5 second delay is
*   to give sufficient time to windows to set the proper state of plugged/unplugged HID devices.
***************************************************************************************************************/
void MouseTimerInit()
{
	CChildView::InitialiseTimer(MOUSE_DETECT_TIMER, MOUSE_EVENT_TIME);	
	MouseState = false;
}

/**************************************************************************************************************
*	This Function is called from Mouse Detect after the mouse state is determined. It kills the timer started 
*   by OnDeviceChange windows event notification.
***************************************************************************************************************/
void KillMouseTimer()
{
	CChildView::KillTimers(MOUSE_DETECT_TIMER);	
}