///* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/vga_uart.h_v   1.0   11 Jun 2014 13:25:26   rjamloki  $ */
#ifndef VGA_UART_H
#define VGA_UART_H
///****************************************************************************/
///*                                                                          */
///*                                                                          */
///*      Copyright (c) Branson Ultrasonics Corporation, 1995                 */
///*     This program is the property of Branson Ultrasonics Corporation      */
///*   Copying of this software is expressly forbidden, without the prior     */
///*   written consent of Branson Ultrasonics Corporation.                    */
///*                                                                          */
///*                                                                          */
///*                                                                          */
///*************************                         **************************/
///*
// ---------------------------- MODULE DESCRIPTION -------------------------------
//
//   Module name:
//   Filename:      qvga_uart.h
//
//
//            Written by: Shishir Madhugiri
//                  Date: 03/06/03
//              Language:  "C"
//
// -------------------------------- REVISIONS ------------------------------------

// ------------------------------- DESCRIPTION -----------------------------------
//
//
// ------------------------------ INCLUDE FILES ----------------------------------
//*/
//
#include "portable.h"
#include "genrlmsg.h"
// Structure of the FIFO buffer
typedef struct {
    SINT8 * buffer;
    UINT16 size;
    UINT16 read;
    UINT16 write;
    UINT16 count;
    } Fifo332;
//
typedef enum {
   STATE_WAIT_FIRST_DLE,	// waiting for first DLE
   STATE_WAIT_STX,		// waiting for STX after DLE
   STATE_WAIT_LENGTH1,	// waiting for upper byte of length
   STATE_WAIT_LENGTH2,	// waiting for lower byte of length
   STATE_WAIT_CODE1,	// waiting for upper byte of command code
   STATE_WAIT_CODE2,	// waiting for lower byte of command code
   STATE_WAIT_DATA,
   STATE_WAIT_CRC,
   STATE_WAIT_SECOND_DLE,	// waiting for second DLE
   STATE_WAIT_ETX,		// waiting for ETX after DLE
   } CHANNEL_STATE;

typedef struct {
   Fifo332 * txfifo;               // transmitter FIFO
   SINT8 * txbuf;               // FIFO ring buffer data
   UINT16 txbufsize;            // FIFO ring buffer size
   SINT8 * rxbuf;               // receiver buffer data (for data part of command)
   UINT16 rxbufsize;            // receiver buffer size
   UINT8 txintmask;             // bit to set to enable transmitter
   CHANNEL_STATE state;         // receiver state machine
   SINT16 length;               // host command length
   UINT16 code;                 // host command code
   UINT16 rxindex;              // pointer into receiver buffer
   UINT8 checksum;              // host command checksum
   } UART_CHANNEL;

typedef struct {
   COMMON_MSG_FIELD_TYPE  common;
   UART_CHANNEL * channel;
   } RVTS_MSG;


#endif
