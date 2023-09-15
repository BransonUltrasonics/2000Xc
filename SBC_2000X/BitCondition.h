/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/BitCondition.h_v   1.3   09 Jul 2014 06:44:18   akaushal  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/BitCondition.h_v  $
 * 
 *    Rev 1.3   09 Jul 2014 06:44:18   akaushal
 * Added function declaration in class.
 * 
 *    Rev 1.2   28 Mar 2014 14:32:54   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:04:44 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:40 amaurya      
 * Initial Revision.
*/


#if !defined(AFX_BITCONDITION_H__467EF3E5_DD15_4763_8C20_8E5FFCE033D6__INCLUDED_)
#define AFX_BITCONDITION_H__467EF3E5_DD15_4763_8C20_8E5FFCE033D6__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Condition.h"
class CVgaMenuItem;
class CBitCondition : public CCondition  
{
public:
	CBitCondition();
	virtual ~CBitCondition();
bool bitState;
	int bitValue;
   int Mask1;
   int Cond1;
   int Mask2;
   int Cond2;
   int CaseValue;
protected:
	virtual bool Evaluate(CVgaMenuItem *) const;
	virtual bool EvaluateChangeCond(CVgaMenuItem *) const ;
};

#endif // !defined(AFX_BITCONDITION_H__467EF3E5_DD15_4763_8C20_8E5FFCE033D6__INCLUDED_)
