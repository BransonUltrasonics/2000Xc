/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/NandFlash.h_v   1.6   11 Mar 2015 09:23:16   amaurya  $
*/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/NandFlash.h_v  $
 * 
 *    Rev 1.6   11 Mar 2015 09:23:16   amaurya
 * New argument added to ReadPreset() and WritePreset() function declaration.
 * 
 *    Rev 1.5   05 Sep 2014 04:28:18   rjamloki
 * Made Nandptr public to access it from other files.
 * 
 *    Rev 1.4   09 Jul 2014 15:12:06   rjamloki
 * Added nand flash test function.
 * 
 *    Rev 1.3   27 May 2014 10:16:12   amaurya
 * Clean up for preset saving
 * 
 *    Rev 1.2   21 May 2014 04:07:26   rjamloki
 * fixed status register bit definitions
 * 
 *    Rev 1.1   14 Apr 2014 08:24:00   rjamloki
 * Made inner level functions inline
 * 
 *    Rev 1.0   05 Mar 2014 15:49:02   rjamloki
 * Initial revision.
*/

#ifndef NANDFLASH_H_
#define NANDFLASH_H_
#include "portable.h"
#include "CPLD.h"
#include "preset.h"
#include "Mutex.h"
//Module contains definition specific to Nand flash MT29F8G08ABABA by Micron. Most of the definition may be true
//for other Nand flashes by other manufacturers as they are governed by ONFI.

//MT29F8G08ABABA Memory layout
//1 LUN = 2 Planes
//1 Plane = 1024 blocks
//1 Block = 128 Pages
//1 Page = 4096 + 224 spare bytes

struct NandAddress {
	/* Logical unit address */
	UINT32 Lun;
	/* Plane address */
	UINT32 Plane;
	/* Block address */
	UINT32 Block;
	/* Page address */
	UINT32 Page;
	/* Column address */
	UINT32 Column;
};

// Parameter Page Data Structure
typedef struct ParamPage {
	/* Parameter page signature (ONFI)*/
	SINT8 Signature[4]; //0-3
	/* Revision number*/
	UINT8 RevNum[2];//4-5
	/* Features supported*/
	UINT16 Feature;//6-7
	/* Optional commands supported*/
	UINT16 Command;//8-9
	/* reserved */
	SINT8 Reserved1[22];//10-31
	/*Device manufacturer*/
	SINT8 Manufacturer[12];//32-43
	/*Device part number */
	SINT8 Model[20];//44-63
	/* Manufacturer ID (Micron = 2Ch) */
	UINT8 JedecId;//64
	/* Date code */
	UINT16 DateCode;//65-66
	SINT8 Reserved2[13];//67-79
	/** Number of data bytes per page */
	UINT32 DataBytesPerPage;//80-83
	/** Number of spare bytes per page */
	UINT16 SpareBytesPerPage;//84-85
	/** Number of data bytes per partial page */
	UINT32 DataBytesPerPartialPage;//86–89
	/** Number of spare bytes per partial page */
	UINT16 SpareBytesPerPartialPage;//90-91
	/** Number of pages per block */
	UINT32 PagesPerBlock;//92-95
	/* Number of blocks per unit */
	UINT32 BlocksPerLun;//96-99
	/* Number of logical units (LUN) per chip enable */
	UINT8 LunsPerCe;//100
	/* Number of address cycles */
	UINT8 NumAddrCycles;//101
	/* Number of bits per cell (1 = SLC; >1= MLC) */
	UINT8 BitPerCell;//102
	/* Bad blocks maximum per unit */
	UINT16 MaxBadBlocksPerLun;//103-104
	/* Block endurance */
	UINT16 BlockEndurance;//105-106
	/** Guaranteed valid blocks at beginning of target */
	UINT8 GuarenteedValidBlocks;//107
	/** Block endurance for guaranteed valid blocks */
	UINT16 BlockEnduranceGuarenteedValidBlocks;//108-109
	/** Number of programs per page */
	UINT8 NumProgramsPerPage;//110
	/** Partial programming attributes */
	UINT8 PartialProgAttr;//111
	/** Number of bits ECC bits */
	UINT8 NumECCBitsCorrectable;//112
	/** Number of interleaved address bits */
	UINT8 NumInterleavedAddrBits;//113
	/** Interleaved operation attributes */
	UINT8 InterleavedOpAttr;//114
	SINT8 Reserved3[13];//115-127
	UINT8 CapacitancePerCe;//128
	UINT16 TimingModeSupport;//129-130
	UINT16 ProgCacheModeSupport;//131-132
	SINT8 Dummy1[18];
	UINT8 DriverStrenthSupport;//151
	SINT8 Reserved4 [12];
	UINT16 SpecificRevNum;//164-165
	SINT8 Dummy2[13];
	UINT8 OtpFeatureAddr;//179
	SINT8 Reserved5[73];
	UINT8 ParamterPageRev;//253
	UINT16 IntegrityCRC;//254–255
} __attribute__((__packed__)) ParameterPage;


//Status register definition
#define	STATUS_FAIL							0x01//coverity fix
#define	STATUS_FAILC						0x02//coverity fix
#define	STATUS_ARDY							0x20
#define	STATUS_RDY							0x40
#define	STATUS_WRITE_PROTECTED				0x80

/*
 * NAND Command set
 */
#define CMD_RESET							0xFF
#define CMD_READID							0x90
#define CMD_READ_PARAM_PAGE					0xEC
#define	CMD_READ_UNIQ_ID					0xED
#define CMD_SET_FEATURE						0xEF
#define CMD_GET_FEATURE						0xEE
#define CMD_READ_STATUS						0x70
#define CMD_READ_STATUS_ENHANCED			0x78
#define CMD_ERASE_BLOCK						0x60
#define CMD_ERASE_BLOCK_CONFIRM				0xD0
#define CMD_READ_MODE						0x00
#define CMD_READ_CONFIRM					0x30
#define CMD_READ_CONFIRM_CACHE				0x31
#define CMD_PAGE_PROGRAM					0x80
#define CMD_PAGE_PROGRAM_CONFIRM			0x10
#define CMD_PAGE_PROGRAM_CONFIRM_CACHE		0x15
#define CMD_READ_INTERNAL_DATA_MOVE			0x35
#define CMD_PROGRAM_INTERNAL_DATA_MOVE		0x85
#define CMD_LOCK							0x2A
#define CMD_BLOCK_UNLOCK_LOW				0x23
#define CMD_BLOCK_UNLOCK_HIGH				0x24
#define CMD_BLOCK_LOCK_READ_STATUS			0x7A

/*
 * NAND Address set
 */
#define 	ADDR_FEATURE_ARRAY_OPMODE			0x90
#define 	ADDR_FEATURE_OUTPUT_STRENGTH		0x80
#define 	ADDR_FEATURE_RB_STRENGTH			0x81
#define 	ADDR_FEATURE_TIMING					0x01
#define 	ADDR_PARAM_PAGE						0x00
#define 	ADDR_READ_ID						0x00
#define 	ADDR_READ_ID_ONFI					0x20
#define 	ADDR_READ_UNIQ_ID					0x00
#define 	ADDR_READ_UNIQ_ID					0x00
#define 	BLOCK_LOCKED						0x02
#define 	BLOCK_LOCKED_TIGHT					0x01
#define 	BLOCK_UNLOCKED_DEV_LOCKED			0x05
#define 	BLOCK_UNLOCKED_DEV_NOT_LOCKED		0x06
#define 	CLOCKS_PER_SEC						1000


#define 	FEATURE_ARRAY_DISABLE_ECC			0x00
#define 	FEATURE_ARRAY_ENABLE_ECC			0x08
#define 	FEATURE_ARRAY_NORMAL				0x00
#define 	FEATURE_ARRAY_OTP_OPERATION			0x01
#define 	FEATURE_ARRAY_OTP_PROTECTION		0x03
#define 	FEATURE_OUTPUT_STRENGH_100			0x00
#define 	FEATURE_OUTPUT_STRENGH_25			0x03
#define 	FEATURE_OUTPUT_STRENGH_50			0x02
#define 	FEATURE_OUTPUT_STRENGH_75			0x01
#define 	FEATURE_RB_STRENGH_100				0x00
#define 	FEATURE_RB_STRENGH_25				0x03
#define 	FEATURE_RB_STRENGH_50				0x02
#define 	FEATURE_RB_STRENGH_75				0x01
#define 	FEATURE_TIMING_MODE0				0x00
#define 	FEATURE_TIMING_MODE1				0x01
#define 	FEATURE_TIMING_MODE2				0x02
#define 	FEATURE_TIMING_MODE3				0x03
#define 	FEATURE_TIMING_MODE4				0x04
#define 	FEATURE_TIMING_MODE5				0x05

#define 	NAND_BAD_PARAMETER_PAGE				0x20
#define 	NAND_ERASE_FAILED					0x40
#define 	NAND_ERASE_FAILED_WRITE_PROTECT		0x41
#define 	NAND_GENERIC_FAIL					0x10
#define 	NAND_INVALID_LENGTH					0x31
#define 	NAND_INVALID_NAND_ADDRESS			0x30
#define 	NAND_PROGRAM_FAILED					0x50
#define 	NAND_PROGRAM_FAILED_WRITE_PROTECT   0x51
#define 	NAND_READ_FAILED					0x60
#define 	NAND_SUCCESS						0x00
#define 	NAND_TIMEOUT						0xFE
#define 	NAND_UNIMPLEMENTED					0xFF
#define 	NAND_UNSUPPORTED					0xFD
#define 	NAND_NOTINITIALIZED					0xFF

#define 	NUM_OF_ADDR_CYCLE					5
#define 	NUM_OF_PPAGE_BYTES					129
#define 	NUM_OF_READID_BYTES					5
#define 	NUM_OF_READIDONFI_BYTES				4
#define 	NUM_OF_READUNIQUEID_BYTES			16
#define 	NUM_OF_UNIQUEID_BYTES				32
#define 	ONFI_SIGNATURE_LENGTH			4
#define 	OPTIONAL_CMD_CHANGE_READ_COLUMN_ENHANCED		0x0040
#define 	OPTIONAL_CMD_CHANGE_ROW_ADDRESS					0x0080
#define 	OPTIONAL_CMD_COPYBACK							0x0010
#define 	OPTIONAL_CMD_GET_FEATURES_AND_SET_FEATURES		0x0004
#define 	OPTIONAL_CMD_ODT_CONFIGURE						0x0800
#define 	OPTIONAL_CMD_PAGE_CACHE_PROGRAM_COMMAND			0x0001
#define 	OPTIONAL_CMD_READ_CACHE_COMMANDS				0x0002
#define 	OPTIONAL_CMD_READ_STATUS_ENHANCED				0x0008
#define 	OPTIONAL_CMD_READ_UNIQUE_ID						0x0020
#define 	OPTIONAL_CMD_RESET_LUN							0x0200
#define 	OPTIONAL_CMD_SMALL_DATA_MOVE					0x0100
#define 	OPTIONAL_CMD_VOLUME_SELECT						0x0400

#define 	SUPPORTED_16_BIT_DATA_BUS_WIDTH					0x0001
#define 	SUPPORTED_EXTENDED_PARAMETER_PAGE				0x0080
#define 	SUPPORTED_EXTERNAL_VPP							0x1000
#define 	SUPPORTED_EZ_NAND								0x0200
#define 	SUPPORTED_MULTIPLANE_PROGRAM_AND_ERASE_OPERATIONS		0x0008
#define 	SUPPORTED_MULTIPLANE_READ_OPERATIONS					0x0040
#define 	SUPPORTED_MULTIPLE_LUN_OPERATIONS						0x0002
#define 	SUPPORTED_NON_SEQUENTIAL_PAGE_PROGRAMMING				0x0004
#define 	SUPPORTED_NV_DDR										0x0020
#define 	SUPPORTED_NV_DDR2										0x0400
#define 	SUPPORTED_ODD_TO_EVEN_PAGE_COPYBACK						0x0010
#define 	SUPPORTED_PROGRAM_PAGE_REGISTER_CLEAR_ENHANCEMENT		0x0100
#define 	SUPPORTED_VOLUME_ADDRESSING								0x0800
#define 	TIME_ADL												70
#define 	TIME_OUT_SECOND											2
#define 	TIME_WB													100
#define 	TIME_WHR												60
#define  	NUM_OF_TICKS_TO_TIMEOUT                                 2 * 1000


//Below information should go into FRAM to keep track of Weld results, events and user information
//to be save in Nand Flash
struct FlashInfoFRAM
{
   UINT8   FlahInfoReserved1[256];
   UINT8   FlashInforRes[228];
   UINT8   FlahInfoReserved2[256];
};

struct BlockPresetMap
{
	UINT16 Block;
};

class NandFlash
{
public:
	NandFlash();
	void NandFlashTest();
    static NandFlash * Init();
   	UINT8 ReadPreset(void * FlashObjPtr, UINT32 Preset_No, UINT32 Length = sizeof(Ver1200Setups));
	UINT8 WritePreset(void * FlashObjPtr, UINT32 Preset_No, UINT32 Length = sizeof(Ver1200Setups));
	static NandFlash * NandPtr;
protected:
  	BOOLEAN Identify();
	virtual UINT8 ReadIDONFI(UINT8 * Buf);
	virtual UINT8 NANDReset(void);
	UINT8 WaitForReady(void);
	void  Wait(SINT32 Nanoseconds);
	UINT8 ReadParamPage(ParameterPage * Ppage);
	UINT8 BlockErase(NandAddress Addr);
	UINT8 PageProgram(NandAddress Addr, UINT8 * Buffer, UINT32 Length, BOOLEAN SpareProg = FALSE);
	UINT8 ReadPage(NandAddress Addr, UINT8 *Buffer, UINT32 Length, BOOLEAN SpareRead = FALSE);
	void BuildCycleAddr (NandAddress Addr, UINT8 * AddrCycleStream );
	UINT8 IsValidAddr(NandAddress Addr);
	UINT8 IsValidAddrSpare(NandAddress Addr);
	UINT8 ReadStatus();
	inline void SendAddr(UINT8 Addr);
	inline void SendCmd(UINT8 Command);
	inline void WriteData(UINT8 Data);
	inline UINT8 ReadData(void);
	UINT16 ConvToUint16(UINT8 Byte0, UINT8 Byte1);
	UINT32 ConvToUint32(UINT8 Byte0, UINT8 Byte1, UINT8 Byte2, UINT8 Byte3);
	void ExtractAddress(UINT32 Address, NandAddress * Addr);
	void ExtractAddressSpare(UINT32 Address, NandAddress * Addr);
	void CheckFlashInitiallzation();
	BOOLEAN NandFlashInitDone;
	ParameterPage Parampage;
	CPLD * cpld;
	UINT8 (NandFlash::*ValidAddrCheckFun)(NandAddress Addr);
	BlockPresetMap BlockPsTable[MAX_POSSIBLE_PRESET + 1];
	Mutex NandMutex;
};

//Nand Flash Memory Organization
//Nand flash used in Sunrise project has one logical unit (LUN)
//1 LUN = 2 Planes
//1 Plane = 1024 Blocks
//1 Block = 128 pages
//1 page = 4320 bytes
//First 128 Blocks (Block number 0 to 127 having total bytes 128 * 128 * 4320 and Range 0x00000000 to 0x0437FFFF) are
//reserved for weld result. Should be enough for 100000 weld results.
//Block 128 is reserved for future for weld results
//Next 128 blocks for event log
//Next 128 Blocks for user information


#define NUM_LUN		   		1
#define PLANES_PER_LUN 		2
#define BLOCKS_PER_PLANE 	1024
#define BLOCKS_PER_LUN		2048
#define PAGE_PER_BLOCK 		128
#define SPAREBYTES_PER_PAGE 224

#define BYTES_PER_PAGE_SPARE   (4320)
#define BYTES_PER_PAGE    (4096)

#define BYTES_PER_BLOCK_SPARE    (PAGE_PER_BLOCK * BYTES_PER_PAGE_SPARE)
#define BYTES_PER_BLOCK    (PAGE_PER_BLOCK * BYTES_PER_PAGE)


#define BLOCK_START_ADDR(Block) ((Block) * BYTES_PER_BLOCK)
#define BLOCK_END_ADDRESS(Block) ((((Block) + 1) * BYTES_PER_BLOCK) - 1)
#define BLOCK_START_ADDR_SPARE(Block) 		((Block) * BYTES_PER_BLOCK_SPARE)
#define BLOCK_END_ADDRESS_SPARE(Block) 		((((Block) + 1) * BYTES_PER_BLOCK_SPARE) - 1)
#define PLANE_FOR_BLOCK(Block)  ((Block) % 2)

//TODO:Not needed
#define PAGE_START_ADDR(Page)  ((page) * BYTES_PER_PAGE)
#define PAGE_END_ADDR(Page)  ((((page) + 1) * BYTES_PER_PAGE) - 1)

#define ADDR_TO_BLOCK(Addr) ((Addr) /  BYTES_PER_BLOCK)
#define ADDR_TO_PAGE(Addr)  (((Addr) /  BYTES_PER_PAGE) % PAGE_PER_BLOCK)
#define ADDR_TO_PLANE(Addr)  (PLANE_FOR_BLOCK(ADDR_TO_BLOCK((Addr))))
#define ADDR_TO_COLUMN(Addr) ((Addr) % BYTES_PER_PAGE)
#define ADDR_TO_LUN(Addr)   ((Addr) * 0)

#define ADDR_TO_BLOCK_SPARE(Addr) 			((Addr) /  BYTES_PER_BLOCK_SPARE)
#define ADDR_TO_PAGE_SPARE(Addr)  			(((Addr) /  BYTES_PER_PAGE_SPARE) % PAGE_PER_BLOCK)
#define ADDR_TO_PLANE_SPARE(Addr)  			(PLANE_FOR_BLOCK(ADDR_TO_BLOCK_SPARE((Addr))))
#define ADDR_TO_COLUMN_SPARE(Addr) 			((Addr) % BYTES_PER_PAGE_SPARE)
#define ADDR_TO_LUN_SPARE(Addr)   			((Addr) * 0)
extern struct FlashInfoFRAM FlashInfo;
void InitPresetNameBuffers();
#endif /* NANDFLASHMICRON_H_ */
