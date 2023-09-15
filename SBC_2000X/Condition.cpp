/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Condition.cpp_v   1.3   09 Jun 2014 11:38:06   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Condition.cpp_v  $
 * 
 *    Rev 1.3   09 Jun 2014 11:38:06   rjamloki
 * Variable initialization in constructor.
 * 
 *    Rev 1.2   28 Mar 2014 14:32:56   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:04:48 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:09:44 amaurya      
 * Initial Revision.
*/



#include "stdafx.h"
#include "SBC.h"
#include "Condition.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

CCondition::CCondition()
{
	variable = NULL;
}

CCondition::~CCondition()
{

}
