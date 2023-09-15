/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Condition.h_v   1.3   09 Jul 2014 06:48:14   akaushal  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Condition.h_v  $
 * 
 *    Rev 1.3   09 Jul 2014 06:48:14   akaushal
 * added declaration EvaluateChangeCond()
 * 
 *    Rev 1.2   28 Mar 2014 14:32:58   rjamloki
 * Removed old header comments and cleanup
 *
 *
 *    Rev 1.1     03 Jan 2014 09:04:48 rjamloki     
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:44 amaurya      
 * Initial Revision.
*/

#if !defined(AFX_CONDITION_H__197EB7EE_CA48_41B2_9FD8_EA6746D45911__INCLUDED_)
#define AFX_CONDITION_H__197EB7EE_CA48_41B2_9FD8_EA6746D45911__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000
class CVariable;
class CVgaMenuItem;
class CCondition  
{
public:
	CCondition();
	virtual ~CCondition();
   virtual bool Evaluate(CVgaMenuItem *) const = 0;
   virtual bool EvaluateChangeCond(CVgaMenuItem *) const =0;
   CVariable * variable;
};

#endif // !defined(AFX_CONDITION_H__197EB7EE_CA48_41B2_9FD8_EA6746D45911__INCLUDED_)
