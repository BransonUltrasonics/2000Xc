/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/uartype.h_v   1.3   05 Mar 2014 13:57:40   rjamloki  $ */
#ifndef UART_PORT_TYPE_H
#define UART_PORT_TYPE_H

/*
 ---------------------------- INCLUDE DESCRIPTION ------------------------------

   Module name: uart_port_type.h


   Filename:  uartype.h
  

            Written by:  
                  Date: 
              Language:  "C"

 -------------------------------- REVISIONS ------------------------------------



 ------------------------------- DESCRIPTION -----------------------------------

  UART port designations

 ------------------------------ INCLUDE FILES ----------------------------------
*/


/*
 --------------------------------- DEFINES -------------------------------------
*/

/*
 ---------------------------- TYPE DECLARATIONS --------------------------------
*/

/*
 * UART Port designators
 * NOTE: These values are used as indices
 *       DO NOT CHANGE THESE VALUES!!!
 */
typedef enum
   {
   UART_A          = 0,
   UART_B          = 1,
   UART_UNASSIGNED = 0xFF,
   } UART_PORT_TYPE;

/*
 --------------------------- FUNCTION PROTOTYPES -------------------------------
*/


/*
 ------------------------------ EXTERNAL DATA ----------------------------------
*/

#endif /* UART_PORT_TYPE_H */

