/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/commnmsg.h_v   1.4   26 Sep 2014 02:58:40   rjamloki  $ */
#ifndef COMMON_MSG_FIELD_H
#define COMMON_MSG_FIELD_H
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/commnmsg.h_v  $
 * 
 *    Rev 1.4   26 Sep 2014 02:58:40   rjamloki
 * Removed psos references
*/

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: NA

   Filename:    commnmsg.h


            Written by: Mark Lazarewicz 
                  Date: 02/08/96 
              Language:  "C"

 -------------------------------- REVISIONS -----------------------------------


 ------------------------------- DESCRIPTION -----------------------------------
  COMMON_MSG_FIELD_TYPE incorporates common information required for all Q read write calls
  messages queue messages.
*/

/*
 ------------------------------ INCLUDE FILES ----------------------------------
*/
#include "opcodes.h"              /* typedef enum for all message opcodes  */
#include "names.h"
/*
 ------------------------------- DEFINES ---------------------------------------
*/

/*
 --------------------------- TYPE DECLARATIONS ---------------------------------
*/ 
/* An indication of whether the provided pointer (if any) should be deallocated as a  */
/* from the task which receives the message                                            */
typedef  enum
   {
   DATA_PTR_DEALLOC    = 0u,
   DATA_PTR_NO_DEALLOC = 1,
   NO_DATA_PTR         = 255
   } QUEUE_POINTER_FLAG_TYPE;

/* This common field shall appear at the start of all queue messages */
/* This type is 32-bits in size                                            */
typedef  struct
    {   
    QUEUE_POINTER_FLAG_TYPE pointer_flag;   
    SOURCE_TASK_ID_TYPE     source_task;
    MSG_OPCODE_TYPE         opcode;
    } COMMON_MSG_FIELD_TYPE;

#endif /* COMMON_MSG_FIELD_H */
