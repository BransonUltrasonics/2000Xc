/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/ticks.h_v   1.6   03 Oct 2014 06:28:50   rjamloki  $ */
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/ticks.h_v  $
 * 
 *    Rev 1.6   03 Oct 2014 06:28:50   rjamloki
 * RTOS.h included
 * 
 *    Rev 1.5   26 Sep 2014 02:58:42   rjamloki
 * Removed psos references
*/
#ifndef TICKS_H
#define TICKS_H
#include "RTOS.h"
/*
------------------------- MODULE DESCRIPTION -------------------------------

   Filename:  ticks.h

---------------------------- DESCRIPTION -----------------------------------

   These defines are converts TICK to Milliseconds and vice versa.
   One can select a length of duration in the typical time units and not need to
   concern oneself with the conversion to 'TICK' count.
  
---------------------------- INCLUDE FILES ----------------------------------
*/


/*
----------------------------- DEFINES ---------------------------------------
*/


      /* NOTE: Somebody goofed and defined MILLS_PER_TICK as 10 when it's  */
      /* really 5.  This macro and the ones defined from it have been used */
      /* all over the code, so it's somewhat risky to correct the mistake. */
      /* Instead, new macros, MS_PER_TICK, MS_TO_TICKS, TICKS_TO_MS have   */
      /* been defined instead.  These should be used in future conversions.*/


                  /* NOTE: MILLS_PER_TICK * TICKS_PER_SECOND = 1000 */
                  /*       If not, then something is amiss.         */

#define MILLS_PER_TICK 10               /* Must be an integer value */

#define MS_PER_TICK    MILLS_PER_TICK   /* This is right now too */

#define TICKS_PER_SECOND 100            /* Must be an integer value */


/*
   These defines are for use with the fifo read write calls that require a count
   of systems TICKS for a duration of time. Conditions are checked that
   insure 32-bit signed integer math does not overflow (i.e., can only
   wait up to 24 days time). If someone wants to foolishly pass in a
   negative parameter, let them.
*/

#define MS_TO_TICKS(ms)    ((!ms) ? (0) : (((ms) / MS_PER_TICK) + 1))    /* +1 prevents 0 unless ms is 0 */
#define TICKS_TO_MS(ticks) ( (ticks) * MS_PER_TICK )

#define MILLS_TO_TICKS(mills) \
         ( ( (mills) / MILLS_PER_TICK) + 1 )

#define SECONDS_TO_TICKS(secs) \
         ( ( (secs) * 1000 / MILLS_PER_TICK) )

#define MINUTES_TO_TICKS(mins) \
         ( ( (mins) * 60000 / MILLS_PER_TICK) )

/*
------------------------- TYPE DECLARATIONS ---------------------------------
*/


/*  
--------------------------- FUNCTION PROTOTYPES -----------------------------
*/


/*
---------------------------- EXTERNAL DATA ----------------------------------
*/

#endif     /* TICKS_H */

