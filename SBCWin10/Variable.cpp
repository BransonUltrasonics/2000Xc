/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Variable.cpp_v   1.3   09 Jun 2014 11:58:42   rjamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Variable.cpp_v  $
 * 
 *    Rev 1.3   09 Jun 2014 11:58:42   rjamloki
 * Variable initialization in constructor
 * 
 *    Rev 1.2   28 Mar 2014 14:33:16   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     03 Jan 2014 09:05:30 rjamloki      
 * Header Fix and added command to assign ip.
 *
 *    Rev 1.0     03 Apr 2013 10:10:04 amaurya      
 * Initial Revision.
*/

#include "stdafx.h"
#include "VGA.h"
#include "Variable.h"

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

CVariable::CVariable()
{
	name = "";
	address = "";
	value = 0;
}

CVariable::~CVariable()
{
}
