/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/qsm.cpp_v   1.7   06 Oct 2014 06:42:56   AnPawar  $ */
/****************************************************************************/

/*
 ---------------------------- MODULE DESCRIPTION --------------------------
 Name: qsm.c
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/qsm.cpp_v  $
 * 
 *    Rev 1.7   06 Oct 2014 06:42:56   AnPawar
 * AD7689A1025::ReadInput(),
 * AD7689A1025::ReadInputsThroughSequencing() function changed. 
 * 
 *    Rev 1.6   28 Jul 2014 12:49:32   rjamloki
 * psos.h removed
 * 
 *    Rev 1.5   27 May 2014 10:13:40   amaurya
 * Diagnostic function for adc read moved to InputTask
 * 
 *    Rev 1.4   01 May 2014 09:08:18   lmarkure
 * Removed extra conversion and rescaled to 10 bits
 -------------------------------- REVISIONS -------------------------------

 Revision #     Date         Author       Description
 ----------     -------      ------       -----------

 1.1          05/04/99      LAM         added packed keyword for DIAB


 ----------------------------- INCLUDE FILES -------------------------------
 */

#include "portable.h"
#include "qsm.h"
#include "Board.h"
#include "DSPI.h"
#include "CPLD.h"
#include "names.h"
#include "qdef.h"
#include "genrlmsg.h"

/*
 ------------------------------ LOCAL DEFINES ----------------------------------
 */

/*
 ------------------------------- LOCAL DATA ------------------------------------
 */
AT93C66 * ActNvRam;
ADC * ActAdc;
DAC * PsDac;
ADC * PsAdc;
LPC1758 * ActLpc;

enum CTAR {
	CTAR_PSADC = 1, CTAR_ACTADC, CTAR_PSDAC, CTAR_ACTPV, CTAR_ACTNVR,
};


/****************************************************************************/
/****************************************************************************/

void InitQsm(void) {
	SPI * spi = Board::GetSPI(0, 5, 5);
	ActNvRam = new AT93C66(spi, 3, CTAR_ACTNVR);
	ActAdc = new AD7890(spi, 5, CTAR_ACTADC);
	PsDac = new TLV5604(spi, 1, CTAR_PSDAC);
	PsAdc  = new AD7689(spi, 2, CTAR_PSADC, 6);
	ActLpc = new LPC1758(spi, 0, CTAR_ACTPV);
}



