/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/ipscdmsg.h_v   1.6   26 Sep 2014 02:58:40   rjamloki  $ */
#ifndef IPS_COMMAND_MSG_H
#define IPS_COMMAND_MSG_H

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/ipscdmsg.h_v  $
 * 
 *    Rev 1.6   26 Sep 2014 02:58:40   rjamloki
 * Removed psos references
 * 
 *    Rev 1.5   21 May 2014 10:49:08   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.3   10 Feb 2014 05:00:14   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.2   03 Jan 2014 08:48:18   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: ips_command_msg

   Filename:  ipscdmsg.h


            Written by: Mark Lazarewicz
                  Date: 03/18/96
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------

 ------------------------------ INCLUDE FILES ----------------------------------
*/

#include "portable.h"
#include "weld_obj.h"
#include "commnmsg.h"

/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/
typedef struct
   {
   COMMON_MSG_FIELD_TYPE  common;          /* 32 bits */
   ULONG                  partition_id;    /* 32 bits */
   UINT16                 offset;     
   UINT16                 byte_count;    
   void                   *data_pointer;
   }HOST_COMMAND_MSG;

typedef struct
   {
   COMMON_MSG_FIELD_TYPE  common;          /* 32 bits */
   ULONG                  partition_id;    /* 32 bits */
   UINT16                 offset;     
   UINT16                 byte_count;    
   WELD_DATA              *data_pointer;
   }HOST_CMD_WELD_MSG;

/*----------------------- FUNCTION PROTOTYPES ------------------------------*/

/*----------------------------- EXTERNAL DATA ------------------------------*/

#endif /* IPS_COMMAND_MSG_H */
