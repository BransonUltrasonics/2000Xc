/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/A1025R.h_v   1.3   16 Apr 2015 07:38:28   rjamloki  $
 */
/****************************************************************************/
/*                                                                          */
/*                                                                          */
/*   Copyright (c) Branson Ultrasonics Corporation, 1995,96, 2009        	*/
/*   This program is the property of Branson Ultrasonics Corporation      	*/
/*   Copying of this software is expressly forbidden, without the prior     */
/*   written consent of Branson Ultrasonics Corporation.                    */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*************************                         **************************/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/A1025R.h_v  $
 * 
 *    Rev 1.3   16 Apr 2015 07:38:28   rjamloki
 * Added defines for Estop Hw selection values stored in mac chip
 * 
 *    Rev 1.1   21 May 2014 04:04:12   rjamloki
 * Fixed Wait state defines for FRAM and Nand flash
 * 
 *    Rev 1.0   14 Apr 2014 06:33:58   rjamloki
 * Initial revision.
*/
//File is suppose to contain A1025R board specific definitions
#ifndef A1025R_H_
#define A1025R_H_
#include "Board.h"

//(flexbus chip select 1) Cyprus nvSRAM
#define CHIPSELCT_PIN1 			  1

#define WAITSTATES_FRAM_CS1   	  4 
#define DATABUSWIDTH_FRAM_CS1  	  8
#define FRAM_BASEADDRESS   		  0x0B000000


//(flexbus chip select 2) Nand Flash
#define CHIPSELCT_PIN2 			  2
#define WAITSTATES_NAND_CS2   	  2
#define DATABUSWIDTH_NAND_CS2  	  8
#define NAND_BASEADDRESS   		  0x08000000


#define MEMSTORE_EXTINT_NUM  	1
#define WD_TRIGGERCNT 			1000//In ms(1 second) max Limit 1.6 second for TPS3823A

#define ONE_POLE_ESTOP  		0xAA55//Board with single pole ESTOP checksum in PS Novram chip
#define TWO_POLE_ESTOP			0x55AA//Board with two pole ESTOP checksum in PS Novram chip

extern BOOLEAN TwoPoleEstop;
#endif /* A1025R_H_ */
