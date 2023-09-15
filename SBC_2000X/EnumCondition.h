/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/EnumCondition.h_v   1.10   27 Mar 2015 11:03:56   amaurya  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/EnumCondition.h_v  $
 * 
 *    Rev 1.10   27 Mar 2015 11:03:56   amaurya
 * PRESET_BARCODE_START_ID moved to ChildView.h.
 * 
 *    Rev 1.9   11 Feb 2015 06:19:04   amaurya
 * functions and flag declarations to handle event details display isuue after alarm reset
 * 
 *    Rev 1.8   10 Nov 2014 02:49:14   rjamloki
 * PRESET_BARCODE_START_ID Macro Added.
 * 
 *    Rev 1.7   20 Oct 2014 07:08:22   RJamloki
 * macro defined ACTSERIALNO_ID
 * 
 *    Rev 1.6   28 Jul 2014 13:42:54   rjamloki
 * declared function bool AuthCheckClampFunc(CVgaAlphanumeric *ptr).
 * 
 *    Rev 1.5   09 Jul 2014 06:50:34   akaushal
 * Added declaration EvaluateChangeCond() and enum Data_TYPE
 * 
 *    Rev 1.4   09 Jun 2014 11:40:12   rjamloki
 * POWERSUPPLYSERIALNOID macro added
 * 
 *    Rev 1.3   21 Apr 2014 13:34:14   akaushal
 * Macro for 20 Radio buttons.
 * 
 *    Rev 1.2   28 Mar 2014 14:32:58   rjamloki
 * Removed old header comments and cleanup
 *
 *   Rev 1.1     03 Jan 2014 09:04:54 rjamloki     
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:46 amaurya     
 * Initial Revision.
*/


#if !defined(AFX_ENUMCONDITION_H__929C9419_9559_49DA_8312_E6CD6FB9B9C8__INCLUDED_)
#define AFX_ENUMCONDITION_H__929C9419_9559_49DA_8312_E6CD6FB9B9C8__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Text.h"
#include "Condition.h"
#include "VgaButton.h"
#include "VgaAlphanumeric.h"
#define MAXRADIOITEMS  20
#define SETUP_ALARM           7
#define SETUP_ALARM_END       10
#define POWERSUPPLYSERIALNOID  23 
#define POWERSUPPLY_IP_ID   290
#define ACTSERIALNO_ID   24


 
class CVgaMenuItem;
class CEnumCondition : public CCondition  
{
public:
	CEnumCondition();
	virtual ~CEnumCondition();
	int enumflagvalue;
	int EnumValue;
	int StringID;
	CString FunName;
	int CalibMenuIndex;
	bool EnableCommand;
	int CalibMenuIndexAED;
	int AEDActuatorValue;
	enum DATA_TYPE {
		NONE, 
		UINT8_TYPE, 
		SINT8_TYPE, 
		UINT16_TYPE, 
		SINT16_TYPE, 
		UINT32_TYPE, 
		SINT32_TYPE, 
		BOOLEAN_TYPE, 
		STR_TYPE, 
		ARR_TYPE
	};
protected:
	virtual bool Evaluate(CVgaMenuItem *) const;
	virtual bool EvaluateChangeCond(CVgaMenuItem *item) const;

};
extern bool ReasonDisplayFlag;
extern bool NameDisplayFlag;
bool CheckOperatorFunc(CVgaButton *ptr);
bool CheckSupervisorFunc(CVgaButton *ptr);
bool CheckNoBransonFunc(CVgaButton *ptr);
bool AuthCheckClampFunc(CVgaAlphanumeric *ptr);
bool CheckForNameDisplay(CVgaButton *ptr);
bool CheckForReasonDisplay(CVgaButton *ptr);
#endif // !defined(AFX_ENUMCONDITION_H__929C9419_9559_49DA_8312_E6CD6FB9B9C8__INCLUDED_)
