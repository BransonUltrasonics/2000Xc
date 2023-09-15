/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/battram.h_v   1.19   09 Apr 2015 04:44:30   RJamloki  $ */
#ifndef BATTRAM_H
#define BATTRAM_H 

/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/battram.h_v  $
 * 
 *    Rev 1.19   09 Apr 2015 04:44:30   RJamloki
 * Removed unused defines for fram addresses
 * 
 *    Rev 1.18   11 Mar 2015 09:21:42   amaurya
 * FRAM_PRESET_ADDR_BEFORE12J macro added.
 * 
 *    Rev 1.17   11 Dec 2014 08:32:12   AnPawar
 * address adjusted for storing new structure.
 * 
 *    Rev 1.16   28 Nov 2014 07:54:40   rjamloki
 * PollingCommandCounter variable added to FramVersionInfo structure.
 * 
 *    Rev 1.15   14 Nov 2014 05:23:00   rjamloki
 * FRAM1200_EVENTDATA_START macro added.
 * 
 *    Rev 1.14   11 Nov 2014 06:13:40   AnPawar
 * Added old flash crc in Fram
 * 
 *    Rev 1.13   10 Nov 2014 04:38:34   AnPawar
 * Changes for FRAM new initialization.
 * 
 *    Rev 1.12   26 Sep 2014 02:59:52   rjamloki
 * Renaming according to Ver12
 * 
 *    Rev 1.11   11 Sep 2014 11:23:00   rjamloki
 * renaming of preset structure as per review 
 * 
 *    Rev 1.10   05 Sep 2014 04:07:12   rjamloki
 * Compressed Preset removed
 * 
 *    Rev 1.9   28 Jul 2014 13:01:48   rjamloki
 * renamed battram to fram for review comment fix
 * 
 *    Rev 1.8   15 Jul 2014 16:54:28   hasanchez
 * Change about the special menu
 * 
 *    Rev 1.7   11 Jun 2014 12:45:46   rjamloki
 * minor cleanup with externs.
 * 
 *    Rev 1.6   21 May 2014 10:49:02   rjamloki
 * Fixed Header.
 * 
 *    Rev 1.4   10 Feb 2014 05:00:04   rjamloki
 * Preset changes to support 1000 preset.
 * 
 *    Rev 1.3   03 Jan 2014 08:47:30   rjamloki
 * Header Fix.
 *
 *
 *****************************************************************************/
/*
------------------------------ MODULE DESCRIPTION -----------------------------

------------------------------ REVISIONS --------------------------------------



----------------------------- DESCRIPTIONS ------------------------------------

   This file contains the function prototype and related definitions for the 
   battram module.

---------------------------- INCLUDE FILES ------------------------------------
*/

#include "portable.h"
#ifndef PRESET_H
#include "preset.h"
#endif
#include "Alarms.h"
#include "weld_obj.h"
#include "command.h"

struct FramVersionInfo
{
    UINT32 FramVersion;
    UINT32 FlashCRC;
    UINT32 PollingCommandCounter;
    UINT32 Resreved;
};
/* -------------------------------DEFINES  ------------------------------------- */

#define START_MINIMAL_APP  TRUE

/* ----------  These defines are for Version 8.00  ---------- */
extern unsigned char __FRAM_START[];
extern unsigned char __FRAM_END[];
#define NMBR_OF_WELD_HISTORY       50
#define FRAM_INIT_VALUE             0x5555
extern SINT8 SWVersionLabelOld[SW_VERSION_LENTGH + 1];
extern FramVersionInfo FramVerInfo;
#define FRAM1200_START_ADDRESS       FRAM1200_RES_START //Skip Software Version old and FramVersion Info while clearing FRAM
#define FRAM_SIZE                ((unsigned int)__FRAM_END -  (unsigned int)__FRAM_START)//this is total size of FRAM app is suinf currently
																						  //and any value in this range can be read here by factory test commandy
//Skip size of SwVersionOld and FramVersionInfoe while clearing FRAM
#define FRAM1200_SIZE                ((unsigned int)__FRAM_END -  (unsigned int)__FRAM_START) - sizeof(SWVersionLabelOld) - sizeof(FramVersionInfo)
/* The first chunk is rese */
extern UINT8 ReservedStart[0xFF - sizeof(FramVersionInfo)];
#define FRAM1200_RES_START          (UINT8*)( &ReservedStart)//FRAM1200_START_ADDRESS
#define FRAM1200_RES_SIZE           sizeof(ReservedStart)//0x0100      /* 256 bytes */

extern UINT8 SystemStart[0x0800];
///* The next chunk is system stuff like DUPS, alarm mask and BUC menus */
#define FRAM1200_SYSTEM_START        (UINT8*)( &SystemStart)
#define FRAM1200_SYSTEM_SIZE         sizeof(SystemStart)//0x0800      /* 2048 bytes */

/*---------  These are sub sections of the System stuff  --------*/
extern ALARM_MASKS FRAMAlarmMasks;
#define FRAM1200_ALARM_START         (ALARM_MASKS*) &FRAMAlarmMasks//FRAM1200_SYSTEM_START
#define FRAM1200_ALARM_SIZE          sizeof(FRAMAlarmMasks)//0x080       /* 128 bytes */

extern UINT8 FRAMDUPSLock[64];
#define FRAM1200_DUPSLOCK_START      (UINT8*)( &FRAMDUPSLock)//(FRAM1200_ALARM_START + FRAM1200_ALARM_SIZE)
#define FRAM1200_DUPSLOCK_SIZE       0x040       /* 64 bytes */

extern UINT8 FRAMHORNSCAN_START[128];
#define FRAM1200_HORNSCAN_START       (UINT8*)( &FRAMHORNSCAN_START)//(FRAM1200_COP2DUPS_START + FRAM1200_COP2DUPS_SIZE)
#define FRAM1200_HORNSCAN_SIZE       0x080       /* 128 bytes */
//
extern UINT8 FRAMDUPSBackup[16];
#define FRAM1200_DUPSBACKUP_START    (UINT8*)( &FRAMDUPSBackup)//(FRAM1200_HORNSCAN_START + FRAM1200_HORNSCAN_SIZE)
#define FRAM1200_DUPSBACKUP_SIZE     0x010       /* 16 bytes */
//
extern BUCMENU_1200 FRAMBUCMenu;
#define FRAM1200_BUCMENU_START       (BUCMENU_1200*)( &FRAMBUCMenu)//(FRAM1200_DUPSBACKUP_START + FRAM1200_DUPSBACKUP_SIZE)
#define FRAM1200_BUCMENU_SIZE        sizeof(BUCMENU_1200)//0x080       /* 128 bytes */


extern DEPOT_FLAGS FRAMDEPOTFlags;
#define FRAM1200_DEPOT_START         (DEPOT_FLAGS*) (&FRAMDEPOTFlags)//(FRAM1200_BUCMENU_START + FRAM1200_BUCMENU_SIZE)
#define FRAM1200_DEPOT_SIZE          sizeof(DEPOT_FLAGS)//0x08        /* 8 bytes */

/* The next Chunk is used to Save QVGA Calib. Co-Ordinates */
//#define FRAM1200_QVGASCRNCLAIB_START (FRAM1200_DEPOT_START + FRAM1200_DEPOT_SIZE)
//#define FRAM1200_QVGASCRNCALIB_SIZE  0x40        /*64 Bytes*/

extern UINT8 FRAMUnUsed[100];
#define FRAM1200_UNUSED_START        (UINT8*)( &FRAMUnUsed)//(FRAM1200_VGASCRNCLAIB_START + FRAM1200_VGASCRNCALIB_SIZE)
#define FRAM1200_UNUSED_SIZE         sizeof(FRAMUnUsed)//(FRAM1200_SYSTEM_START + FRAM1200_SYSTEM_SIZE - FRAM1200_UNUSED_START)

/*---------  End of System stuff  ----------*/
extern CONFIGSETUP FRAMConfigSetup;
/* The next chunk is for system configuration */
#define FRAM1200_CONFIG_START        (CONFIGSETUP*)(&FRAMConfigSetup)//(FRAM1200_SYSTEM_START + FRAM1200_SYSTEM_SIZE)
#define FRAM1200_CONFIG_SIZE         sizeof(FRAMConfigSetup)//0x0400       /* 1024 bytes */

/* The next chunk is for presets */
#define FRAM1200_PRESET_START        (SETUPS_Ver1200 *)(&FRAMPreset[0])//(FRAM1200_CONFIG_START + FRAM1200_CONFIG_SIZE)
#define FRAM1200_PRESET_SIZE         sizeof(FRAMPreset)//0x4000       /* 16384 bytes */

/* Here are the individual starting locations for each preset */
#define PRESET_N_START(n)  (SETUPS_Ver1200 *)(&FRAMPreset[n])

extern UINT8 FRAMHORNGraph[2400];
/* The next chunk is to save the horn scan graph*/
#define FRAM1200_HORNGRAPH_START     (UINT8*) (&FRAMHORNGraph)//(FRAM1200_PRESET_START + FRAM1200_PRESET_SIZE)
#define FRAM1200_HORNGRAPH_SIZE      sizeof(FRAMHORNGraph)//0x0640       /* 1600 bytes)                               */

extern UINT8 FRAMNotAssigned[0x07AC];
/* The next chunk is not assigned */
#define FRAM1200_NOTASSIGNED_START   (UINT8*)(&FRAMNotAssigned)//(FRAM1200_HORNGRAPH_START + FRAM1200_HORNGRAPH_SIZE)
#define FRAM1200_NOTASSIGNED_SIZE    sizeof(FRAMNotAssigned)//0x0CC0       /* 3264 bytes */

extern WELD_DATA FRAMHistory[50];
/* The last usable chunk is for weld history */
#define FRAM1200_HISTORY_START       (WELD_DATA*) (&FRAMHistory)//(FRAM1200_NOTASSIGNED_START + FRAM1200_NOTASSIGNED_SIZE)
#define FRAM1200_HISTORY_SIZE        50 * sizeof(WELD_DATA)//0x1FF0       /* 8176 bytes */
#define WELD_DATA_SIZE_800         (50 * sizeof(WELD_DATA))


extern FRAMUserID FRAMUserIdObj;
#define FRAM1200_USERIDDATA_START  (UINT8*)(&FRAMUserIdObj)
#define FRAM1200_EVENTDATA_START  (UINT8*)(&FRAMEventHistoryObj)

///* Check the programmer.  See if all individual system stuff sizes added up are still less then the full system chunk */
//#if (FRAM1200_ALARM_SIZE+FRAM1200_DUPSLOCK_SIZE+FRAM1200_DUPS2COP_SIZE+FRAM1200_COP2DUPS_SIZE+FRAM1200_HORNSCAN_SIZE+FRAM1200_DUPSINFO_SIZE+FRAM1200_DUPSBACKUP_SIZE+FRAM1200_BUCMENU_SIZE+FRAM1200_DEPOT_SIZE) > FRAM1200_SYSTEM_SIZE
//#error Individual entries have exceeded the space allocated for system stuff in battram.h!
//#endif

/* Here add the size for each major section and ensure they still fit within the full 32K */

//#if (FRAM1200_RES_SIZE+FRAM1200_SYSTEM_SIZE+FRAM1200_CONFIG_SIZE+FRAM1200_PRESET_SIZE+FRAM1200_HORNGRAPH_SIZE+FRAM1200_NOTASSIGNED_SIZE+FRAM1200_HISTORY_SIZE) > FRAM1200_SIZE
//#error FRAM allocation has exceeded its physical size in battram.h!
//#endif

/* Now lets check the preset size */

//#if (36 * SIZE_OF_COMPRESSED_PRESET) > FRAM1200_PRESET_SIZE
//#error Total size of presets is too large for space allocated for presets!
//#endif

/*-------------------------- TYPE DECLARATIONS --------------------------------*/
typedef  enum
      {
      FRAM_STATUS_OK = 1u,               /* Successful access to sram */
      FRAM_STATUS_BAD_ARG,               /* Out of bound argument     */
      }  FRAM_STATUS_TYPE;  

typedef  enum
      {
      FRAM_READ = 0u,                    /* Request to read data from nvm */
      FRAM_WRITE                         /* Request to write data into nvm*/
      }  FRAM_ACCESS_TYPE;


typedef enum {
    RESERVED_SECTION = 1u,                  /* Access to the Reserved section */
    SYSTEM_SECTION,                     /* Access to entire system section */
    ALARM_SECTION,                      /* Access to alarm masks for customer specials */
    DUPSLOCK_SECTION,                   /* Access to lock information about DUPS presets */
    DUPS2COP_SECTION,                   /* Access to DUPS to COP preset mapping array */
    COP2DUPS_SECTION,                   /* Access to COP to DUPS preset mapping array */
    HORNSCAN_SECTION,                   /* Access to frequency results of horn scan */
    DUPSINFO_SECTION,                   /* Access to results of sonics from DUPS */
    DUPSBACKUP_SECTION,                 /* Access to 4 DUPS parameters that used can be changed */
    BUCMENU_SECTION,                    /* Access to parameters only available in BUC menu */
    DEPOT_SECTION,                      /* Access to configuration information to disable 'Checksum' */
    SYSTEM_UNUSED_SECTION,              /* Access to still unused system stuff section */
    CONFIG_SECTION,                     /* Access to the system configuration section */
    PRESET_SECTION,                     /* Access to the preset section */
    HORN_SECTION,                       /* Access to the horn scan section */
    NOTASSIGNED_SECTION,                /* Access to the unassigned section */
    HISTORY_SECTION                     /* Access to the weld history section */
    } FRAM_SECTION_TYPE;
 


#endif /* FRAM_H */

extern Ver1200Setups FRAMPreset[37];
extern BUCMENU_1200 *BUCMenuFRAM;
extern BUCMENU_1200 BUCMenuRAM;
/* ------------------------- FUNCTION PROTOTYPES ------------------------------ */

FRAM_STATUS_TYPE  FramAccess(  
                               FRAM_ACCESS_TYPE  Request,     
                               FRAM_SECTION_TYPE SecID,   
                               UINT8            *DataPointer,
                               UINT32           Offset,     
                               UINT16           ByteCount   );

BOOLEAN CheckFramDefaults(void);
BOOLEAN IsStartModeMinMode(void);
void FixFram(void);
void ClearOutFram(void);
