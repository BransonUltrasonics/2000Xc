/*
$Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/NandFlash.cpp_v   1.10   11 Mar 2015 09:17:08   amaurya  $
*/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/NandFlash.cpp_v  $
 * 
 *    Rev 1.10   11 Mar 2015 09:17:08   amaurya
 * New parameter added to ReadPreset() for Preset size in bytes default is sizeof(Ver1200Setups).
 * 
 *    Rev 1.9   08 Jan 2015 03:18:24   AnPawar
 * printf removed
 * 
 *    Rev 1.8   28 Nov 2014 07:38:26   rjamloki
 * changed to remove warning "unused variable".
 * 
 *    Rev 1.7   10 Nov 2014 04:53:58   AnPawar
 * added function header.12.F review change.
 * 
 *    Rev 1.6   26 Sep 2014 03:36:28   rjamloki
 * Some clean up and comment addition
 * 
 *    Rev 1.5   11 Sep 2014 11:01:52   rjamloki
 * Coverity fix,initialize arguments in constructor
 * 
 *    Rev 1.4   05 Sep 2014 04:58:08   rjamloki
 * Protected preset read write on flash through mutex.
 * 
 *    Rev 1.3   09 Jul 2014 13:34:44   rjamloki
 * WritePreset function fixed to get the right block for erase.
 * 
 *    Rev 1.2   27 May 2014 10:13:16   amaurya
 * Clean up for preset saving
 * 
 *    Rev 1.1   14 Apr 2014 10:20:22   rjamloki
 * Fixed chip selects as per A1025 board.
 * 
 *    Rev 1.0   05 Mar 2014 15:48:06   rjamloki
 * Initial revision.
*/


#include "NandFlash.h"
#include "assert.h"
#include "CpuDefs.h"
#include "String.h"
#include "stdio.h"
#include "CPU.h"
#include "A1025R.h"
#include "preset.h"

#define NAND_DATA_ADDR    *((volatile unsigned char *) 0x08000000)
#define NAND_ADDRESS_ADDR   *((volatile unsigned char *) 0x08000001)
#define NAND_COMMAND_ADDR  *((volatile unsigned char *) 0x08000002)
/* extract n-th bit from a value */
#define CHECK_BIT(Val, N) ((Val & (1 << N)) >> N)
/* extract from column address */
#define COL(Addr, N) 			CHECK_BIT(Addr.Column, N)
/* extract from page address */
#define PAGE(Addr, N) 		    CHECK_BIT(Addr.Page, N)
/* extract from block address */
#define BLOCK(Addr, N) 		    CHECK_BIT(Addr.Block, N)
/* extract from lun number */
#define LUN(Addr, N) 			CHECK_BIT(Addr.Lun, N)
/* build a single row of address cycle */
#define BUILD_ADDR_ROW(i_07, i_06, i_05, i_04, i_03, i_02, i_01, i_00) (\
	 ((i_07) << 7) \
   | ((i_06) << 6) \
   | ((i_05) << 5) \
   | ((i_04) << 4) \
   | ((i_03) << 3) \
   | ((i_02) << 2) \
   | ((i_01) << 1) \
   | ((i_00) << 0) \
)
#define LOW				0
#define HIGH			1


NandFlash * NandFlash::NandPtr = 0;

/** @brief NandFlash constructor
 *
 *  This function initializes the Nand flash.Sends the chip select
 *  required.Then remove the write protect.Identify the flash.
 *
 *  @param void.
 *  @return void.
 */
NandFlash::NandFlash(): NandMutex("NandMutex")
{
	cpld = CPLD::GetCPLD();
	CPU::SetupChipSelect(CHIPSELCT_PIN2, WAITSTATES_NAND_CS2, DATABUSWIDTH_NAND_CS2, (void *)NAND_BASEADDRESS);
	memset(&Parampage , 0, sizeof(Parampage));
	cpld->SetDout(NAND_WP, true);//Remove write protect.
	ValidAddrCheckFun = &NandFlash::IsValidAddr;
	memset(BlockPsTable, 0 , sizeof(BlockPsTable));
	NANDReset();
	NandFlashInitDone = Identify();
	if(NandFlashInitDone){
		CheckFlashInitiallzation();
	}
}

/** @brief NandFlash::Init
 *
 *  This function initializes the Nand flash.Sends the chip select
 *  required.Then remove the write protect.Call the function Identify().
 *
 *  @param void.
 *  @return void.
 */
NandFlash * NandFlash::Init(void)
{
	if(!NandPtr){
	    InitPresetNameBuffers(); //Allocate the memory for Preset names in RAM
		NandPtr = new NandFlash();
	}
	return NandPtr;
}


/** @brief NandFlash::Identify
 *
 *  This function identify the flash after reading the flash info.
 *  and comparing onfi signature of flash.
 *
 *  @param void.
 *  @return BOOLEAN TRUE on success FALSE otherwise.
 */
BOOLEAN NandFlash::Identify()
{
	BOOLEAN RetVal = FALSE;
	UINT8 OnfiSignature[ONFI_SIGNATURE_LENGTH];
	ReadIDONFI(OnfiSignature);
    /* verify ONFI signature in the first field of parameter page */
    if((memcmp((const char *)OnfiSignature, "ONFI", 4) == 0)
    	&& (NAND_BAD_PARAMETER_PAGE != ReadParamPage(&Parampage)))
    	RetVal = TRUE;
    return RetVal;
}

/** @brief NandFlash::NANDReset
 *
 *  This function send reset command to flash and wait for some
 *  time.
 *
 *  @param void.
 *  @return UINT8 Ret ready status of Nand Flash
 */
UINT8 NandFlash::NANDReset()
{
	 UINT8 Ret;
	 SendCmd(CMD_RESET);
	 Wait(TIME_WB);
	 Ret = WaitForReady();
	 return Ret;
}

/** @brief NandFlash::WaitForReady
 *
 *  This function send CMD_READ_STATUS and CMD_READ_MODE command
 *  to flash and wait for ready state of Flash.
 *
 *  @param void.
 *  @return UINT8 NAND_SUCCESS
 */
UINT8 NandFlash::WaitForReady()
{
#ifdef CHECK_PIN //Either check the ready pin of flash
	while (!cpld->GetDin(RB)){
		;
	}
#else//Or read the flash register
   SendCmd(CMD_READ_STATUS);
   while (STATUS_RDY != (STATUS_RDY & ReadData()))
   {}
   SendCmd(CMD_READ_MODE);
#endif
   return NAND_SUCCESS;
}

/** @brief NandFlash::ReadIDONFI
 *
 *  This function reads the ONFI info of flash in *Buf
 *
 *  @param UINT8* Buf buffer pointer
 *  @return void
 */
UINT8 NandFlash::ReadIDONFI(UINT8 * Buf)
{
	SINT32 Indx;
    SendCmd(CMD_READID);
    SendAddr(ADDR_READ_ID_ONFI);
    /* wait (see data sheet for details) */
    Wait(TIME_WHR);
    /* read output */
    for(Indx = 0; Indx < NUM_OF_READIDONFI_BYTES; Indx++)
    	Buf[Indx] = ReadData();
    return NAND_SUCCESS;
}

/** @brief NandFlash::ReadData
 *
 *  This function reads data from memory mapped data register.
 *
 *  @param void
 *  @return UINT8
 */
inline UINT8 NandFlash::ReadData(void)
{
	return NAND_DATA_ADDR;
}

/** @brief NandFlash::SendCmd
 *
 *  This function writes command on memory mapped command register.
 *
 *  @param UINT8
 *  @return void
 */
inline void NandFlash::SendCmd(UINT8 Command)
{
	NAND_COMMAND_ADDR = Command;
}

/** @brief NandFlash::SendAddr
 *
 *  This function writes address on memory mapped address register.
 *
 *  @param UINT8
 *  @return void
 */
inline void NandFlash::SendAddr(UINT8 Addr)
{
	NAND_ADDRESS_ADDR = Addr;
}

/** @brief NandFlash::WriteData
 *
 *  This function writes data on memory mapped data register.
 *
 *  @param UINT8
 *  @return void
 */
inline void NandFlash::WriteData (UINT8 Data)
{
	NAND_DATA_ADDR = Data;
}


/** @brief NandFlash::Wait
 *
 *  This function provide delay of specified nano seconds0
 *
 *  @param SINT32 delay in nanoseconds
 *  @return void
 */
void NandFlash::Wait(SINT32 Nanooseconds)
{
	for(volatile int i = 0; i < Nanooseconds; i++);//FIXME
}

/**
 *  The READ PARAMETER PAGE (ECh) command is used to read the ONFI parameter page
 *  programmed into the target. This command is accepted by the target only when all die
 *  (LUNs) on the target are idle.
 *
 *  @param[out] flash_width *ppage: a filled structure with ONFI paramter page
 *  @return Return code
 *  @retval NAND_SUCCESS
 *  @retval NAND_TIMEOUT
 *
 *  @StartSteps
 *  @Step Send parameter page command (ECh)
 *  @Step Send address for parameter page (00h)
 *  @Step Wait tWB nanoseconds before read
 *  @Step Wait for ready
 *  @Step Read the content of the parameter page
 *  @Step Parse the parameter page buffer and fill the data structure
 *  @EndSteps
 */
UINT8 NandFlash::ReadParamPage(ParameterPage * Ppage) {
	UINT8 Rbuf[sizeof(ParameterPage)];
	UINT8 Ret;
	UINT32 I;
    /* send command and/or address */
    SendCmd(CMD_READ_PARAM_PAGE);
    SendAddr(ADDR_PARAM_PAGE);
    /* wait (see datasheet for details) */
    Wait(TIME_WB);
    Ret = WaitForReady();
    /* return if timeout */
    if (NAND_SUCCESS == Ret) {
		/* read output */
		for(I = 0; I < sizeof(ParameterPage); I++)
			Rbuf[I] = ReadData();
		/*
		 * Fill the parameter page data structure in the right way
		 */
		/* Parameter page signature (ONFI) */
		memcpy(Ppage->Signature, Rbuf, 4);

		/* check if the buffer contains a valid ONFI parameter page */
		if (memcmp(Ppage->Signature, "ONFI", 4))
			Ret = NAND_BAD_PARAMETER_PAGE;

		if(Ret == NAND_SUCCESS){
			/* Manufacturer ID (Micron = 2Ch) */
			Ppage->JedecId = Rbuf[64];
			/* Date code */
			Ppage->DateCode = ConvToUint16(Rbuf[65], Rbuf[66]);
			/* Number of data bytes per page */
			Ppage->DataBytesPerPage = ConvToUint32(Rbuf[80], Rbuf[81], Rbuf[82], Rbuf[83]);
			/* Number of spare bytes per page */
			Ppage->SpareBytesPerPage = ConvToUint16(Rbuf[84], Rbuf[85]);
			/* Number of data bytes per partial page */
			Ppage->DataBytesPerPartialPage = ConvToUint32(Rbuf[86], Rbuf[87], Rbuf[88], Rbuf[89]);
			/* Number of spare bytes per partial page */
			Ppage->SpareBytesPerPartialPage = ConvToUint16(Rbuf[90], Rbuf[91]);
			/* Number of pages per block */
			Ppage->PagesPerBlock = ConvToUint32(Rbuf[92], Rbuf[93], Rbuf[94], Rbuf[95]);
			/* Number of blocks per unit */
			Ppage->BlocksPerLun = ConvToUint32(Rbuf[96], Rbuf[97], Rbuf[98], Rbuf[99]);
			/* Number of logical units (LUN) per chip enable */
			Ppage->LunsPerCe = Rbuf[100];
			/* Number of address cycles */
			Ppage->NumAddrCycles = Rbuf[101];
			/* Number of bits per cell (1 = SLC; >1= MLC) */
			Ppage->BitPerCell = Rbuf[102];
			/* Bad blocks maximum per unit */
			Ppage->MaxBadBlocksPerLun = ConvToUint16(Rbuf[103], Rbuf[104]);
		}
    }
    return Ret;
}

/**
 *  Erase operations are used to clear the contents of a block in the NAND Flash array to
 *  prepare its pages for program operations.
 *
 *  @param[in] NandAddress addr: any valid address within the block to erase (column address is ignored)
 *  @return Return code
 *  @retval NAND_SUCCESS
 *  @retval NAND_TIMEOUT
 *
 *  @StartSteps
 *  @Step Send erase block command (60h)
 *  @Step Send row address of the block
 *  @Step Send confirm command (D0h)
 *  @Step Wait tWB nanoseconds
 *  @Step Wait for ready
 *  @Step Check status register value
 *  @Read data
 *  @EndSteps
 */
UINT8 NandFlash::BlockErase(NandAddress Addr)
{
	UINT8 RowAddress[5];
	UINT8 StatusReg;
	UINT8 Ret = NAND_SUCCESS;

	/* verify if driver is initialized */
	if(NandFlashInitDone == FALSE)
	    Ret = NAND_NOTINITIALIZED;
	/* check input parameters */
	else if(NAND_SUCCESS != IsValidAddr(Addr))
		Ret = NAND_INVALID_NAND_ADDRESS;

	BuildCycleAddr(Addr, RowAddress);

	if(Ret == NAND_SUCCESS){
		/* send command  */
		SendCmd(CMD_ERASE_BLOCK);
		/* send row address (3rd, 4th, 5th cycle) */
		SendAddr(RowAddress[2]);
		SendAddr(RowAddress[3]);
		SendAddr(RowAddress[4]);
		/* send confirm command */
		SendCmd(CMD_ERASE_BLOCK_CONFIRM);
		/* wait */
		Wait(TIME_WB);
		Ret = WaitForReady();
		StatusReg = ReadStatus();
		/* check if erase is good */
		if(!(StatusReg & STATUS_WRITE_PROTECTED))
			Ret = NAND_ERASE_FAILED_WRITE_PROTECT;
		else if(StatusReg & STATUS_FAIL)
			Ret = NAND_ERASE_FAILED;
	}
	return Ret;
}

/**
    The PROGRAM PAGE (80h-10h) command enables the host to input data to a cache
    register, and moves the data from the cache register to the specified block and page
    address in the array of the selected die (LUN).
    Use this function only to program OTP area!

    @param[in] NandAddress addr: address where start reading
    @param[in] flash_width *buffer: the buffer contains the data to program into the flash
    @parma[in] MT_uint32 lenght: number of byte (or word) to program

    @return Return code
    @retval NAND_NOTINITIALIZED
    @retval NAND_INVALID_NAND_ADDRESS
    @retval NAND_PROGRAM_FAILED_WRITE_PROTECT
    @retval NAND_PROGRAM_FAILED
    @retval NAND_SUCCESS
    @retval NAND_TIMEOUT


    @StartSteps
  	@Step Send read command (00h)
  	@Step Send address (5 cycles)
  	@Step Send data
  	@Step Send confirm command (30h)
  	@Step Wait for ready
  	@Step Check status register value
  	@EndSteps
 */
UINT8 NandFlash::PageProgram(NandAddress Addr, UINT8 * Buffer, UINT32 Length, BOOLEAN SpareProg)
{
	UINT8 Address[5];
	UINT8 StatusReg, RetVal = NAND_SUCCESS;
	UINT32 Indx;
	UINT32 pageSize = Parampage.DataBytesPerPage;
	ValidAddrCheckFun = &NandFlash::IsValidAddr;
	if (SpareProg) {
		pageSize += 224;
		ValidAddrCheckFun = &NandFlash::IsValidAddrSpare;
	}
	/* verify if driver is initialized */
	if(NandFlashInitDone == FALSE)
		RetVal = NAND_NOTINITIALIZED;
	/* check input parameters */
	else if (NAND_SUCCESS != (this->*ValidAddrCheckFun)(Addr))
		RetVal = NAND_INVALID_NAND_ADDRESS;
	else if (Length > pageSize)
		RetVal = NAND_INVALID_LENGTH;

	if(RetVal == NAND_SUCCESS){
		BuildCycleAddr(Addr, Address);
		/* send command */
		SendCmd(CMD_PAGE_PROGRAM);
		/* send address */
		for (Indx = 0; Indx < NUM_OF_ADDR_CYCLE; Indx++)
			SendAddr(Address[Indx]);

		/* send data */
		for (Indx = 0; Indx < Length; Indx++)
			WriteData(Buffer[Indx]);

		/* send command */
		SendCmd(CMD_PAGE_PROGRAM_CONFIRM);
		/* wait */
		WaitForReady();
		StatusReg = ReadStatus();

		/* check if program is good */
		if(!(StatusReg & STATUS_WRITE_PROTECTED))
			RetVal = NAND_PROGRAM_FAILED_WRITE_PROTECT;
		else if(StatusReg & STATUS_FAIL)
			RetVal = NAND_PROGRAM_FAILED;
	}
	return RetVal;
}

/**
    The READ PAGE (00h–30h) command copies a page from the NAND Flash array to its
    respective cache register and enables data output. This command is accepted by the die
    (LUN) when it is ready (RDY = 1, ARDY = 1).
    Use this function only to read OTP area!

    @param[in] NandAddress addr: address where to start reading
    @param[in] UINT32 lenght: number of byte (or word if x16 device) to read
    @param[out] UINT8 *buffer: the buffer contains the data read from the flash

    @return Return code
    @retval NAND_NOTINITIALIZED
    @retval NAND_INVALID_NAND_ADDRESS
    @retval NAND_READ_FAILED
    @retval NAND_SUCCESS
    @retval NAND_TIMEOUT


    @StartSteps
  	@Step Send read command (00h)
  	@Step Send address (5 cycles)
  	@Step Send confirm command (30h)
  	@Step Wait for ready
  	@Step Check status register value
  	@EndSteps
 */
UINT8 NandFlash::ReadPage(NandAddress Addr, UINT8 *Buffer, UINT32 Length, BOOLEAN SpareRead) {

	UINT8 Address[5];
	UINT8 StatusReg;
	UINT8 Ret = NAND_SUCCESS;
	UINT32 I;
	UINT32 pageSize = Parampage.DataBytesPerPage;
	ValidAddrCheckFun = &NandFlash::IsValidAddr;
	if (SpareRead) {
		pageSize += 224;
		ValidAddrCheckFun = &NandFlash::IsValidAddrSpare;
	}
	/* verify if driver is initialized */
	if (NandFlashInitDone == FALSE)
		Ret = NAND_NOTINITIALIZED;
	/* check input parameters */
	else if (NAND_SUCCESS != (this->*ValidAddrCheckFun)(Addr))
		Ret = NAND_INVALID_NAND_ADDRESS;
	/* x8 */
	else if(Length > pageSize)
		Ret = NAND_INVALID_LENGTH;

	if(Ret == NAND_SUCCESS){
		BuildCycleAddr(Addr, Address);
		/* send command  */
		SendCmd(CMD_READ_MODE);
		/* send address */
		for(I = 0; I < NUM_OF_ADDR_CYCLE; I++)
			SendAddr(Address[I]);
		/* return to read mode */
		SendCmd(CMD_READ_CONFIRM);
		/* wait */
		Ret = WaitForReady();
		/* read data */
		for(I= 0; I< Length; I++)
			Buffer[I] = ReadData();
		/* read status register on exit */
		StatusReg = ReadStatus();
		if(StatusReg & STATUS_FAIL)
			Ret = NAND_READ_FAILED;
	}

	return Ret;
}

/** @brief BuildCycleAddr
 *
 *  @param NandAddress Addr
 *  @param UINT8 *AddrCycleStream
 *  @return void
 */
void NandFlash::BuildCycleAddr (NandAddress Addr, UINT8 *AddrCycleStream)
{
	/* build the address cycle stream (Assume 128 pages per block) */
	/* Col 1 - I cycle */
	AddrCycleStream[0] =
	(UINT8) BUILD_ADDR_ROW(COL(Addr,7), COL(Addr,6), COL(Addr,5), COL(Addr,4), COL(Addr,3), COL(Addr,2), COL(Addr,1), COL(Addr,0));
	/* Col 2 - II cycle */
	AddrCycleStream[1] =
	(UINT8) BUILD_ADDR_ROW(LOW, LOW, COL(Addr,13), COL(Addr,12), COL(Addr,11), COL(Addr,10),COL(Addr,9),COL(Addr,8));
	/* Row 1 - III cycle */
	AddrCycleStream[2] =
	(UINT8) BUILD_ADDR_ROW(BLOCK(Addr,0), PAGE(Addr,6), PAGE(Addr,5), PAGE(Addr,4), PAGE(Addr,3), PAGE(Addr,2), PAGE(Addr,1), PAGE(Addr,0));
	/* Row 2 - IV cycle */
	AddrCycleStream[3] =
	(UINT8) BUILD_ADDR_ROW(BLOCK(Addr,8), BLOCK(Addr,7), BLOCK(Addr,6), BLOCK(Addr,5), BLOCK(Addr,4), BLOCK(Addr,3), BLOCK(Addr,2), BLOCK(Addr,1));
	/* Row 3 - V cycle */
	AddrCycleStream[4] =
	(UINT8) BUILD_ADDR_ROW(LOW, LOW, LOW, LOW, LUN(Addr, 0), LOW,  BLOCK(Addr,10), BLOCK(Addr,9));

}

/** @brief ExtractAddressSpare
 *
 *  Function converts the logical Nand address to physical Nand address format needed for
 *  Erase,Program and Read. It shall be used only if the Page is considered to have 224
 *  extra spare bytes
 *
 *  @param UINT32 Address
 *  @param NandAddress * Addr
 *  @return void
 */
void NandFlash::ExtractAddressSpare(UINT32 Address, NandAddress * Addr) {
	Addr->Lun = ADDR_TO_LUN_SPARE(Address);
	Addr->Plane = ADDR_TO_PLANE_SPARE(Address);
	Addr->Block = ADDR_TO_BLOCK_SPARE(Address);
	Addr->Page = ADDR_TO_PAGE_SPARE(Address);
	Addr->Column = ADDR_TO_COLUMN_SPARE(Address);
}


/** @brief ExtractAddress.
 *
 *  Function converts the logical Nand address to physical Nand address format needed for
 *  Erase,Program and Read. It shall be used only if the Page is assumed 4096 bytes discarding the
 *  spare 224 bytes.
 *
 *  @param UINT32 Address
 *  @param NandAddress * Addr
 *  @return void
 */
void NandFlash::ExtractAddress(UINT32 Address, NandAddress * Addr)
{
	Addr->Lun = ADDR_TO_LUN(Address);
	Addr->Plane = ADDR_TO_PLANE(Address);
	Addr->Block = ADDR_TO_BLOCK(Address);
	Addr->Page = ADDR_TO_PAGE(Address);
	Addr->Column = ADDR_TO_COLUMN(Address);
}


/** @brief IsValidAddrSpare.
 *
 *  Verify that an address is valid with the current
 *  device size.
 *
 *  @param NandAddress Addr
 *  @return UINT8 NAND_SUCCESS if address is valid otherwise NAND_INVALID_NAND_ADDRESS.
 */
UINT8 NandFlash::IsValidAddr(NandAddress Addr) {
	UINT8 Ret = NAND_INVALID_NAND_ADDRESS;
	if ((Addr.Column < Parampage.DataBytesPerPage) && (Addr.Page
			< Parampage.PagesPerBlock) && (Addr.Block < Parampage.BlocksPerLun)
			&& (Addr.Lun < Parampage.LunsPerCe))
		Ret = NAND_SUCCESS;
	return Ret;
}

/** @brief IsValidAddrSpare.
 *
 *  Verify that an address is valid spare with the current
 *  device size.
 *
 *  @param NandAddress Addr
 *  @return UINT8 NAND_SUCCESS if address is valid otherwise NAND_INVALID_NAND_ADDRESS.
 */
UINT8 NandFlash::IsValidAddrSpare(NandAddress Addr) {
	UINT8 Ret = NAND_INVALID_NAND_ADDRESS;
	if ((Addr.Column < (Parampage.DataBytesPerPage + 224)) && (Addr.Page
			< Parampage.PagesPerBlock) && (Addr.Block < Parampage.BlocksPerLun)
			&& (Addr.Lun < Parampage.LunsPerCe))
		Ret = NAND_SUCCESS;
	return Ret;
}

/** @brief ConvToUint16.
 *
 *  Function makes a 16bit unsigned int from two bytes.
 *
 *  @param UINT8 Byte0
 *  @param UINT8 Byte1
 *  @return UINT16
 */
UINT16 NandFlash::ConvToUint16(UINT8 Byte0, UINT8 Byte1)
{
	return ((UINT16) ((Byte1 << 8) | Byte0));
}

/** @brief ConvToUint32.
 *
 *  Function makes a 32bit unsigned int from four bytes.
 *
 *  @param UINT8 Byte0
 *  @param UINT8 Byte1
 *  @param UINT8 Byte2
 *  @param UINT8 Byte3
 *  @return UINT32
 */
UINT32 NandFlash::ConvToUint32(UINT8 Byte0, UINT8 Byte1, UINT8 Byte2, UINT8 Byte3)
{
	return ((UINT32) ((Byte3 << 24) | (Byte2 << 16) | (Byte1 << 8) | Byte0));
}

/**
    The READ STATUS (70h) command returns the status of the last-selected die (LUN) on
    a target. This command is accepted by the last-selected die (LUN) even when it is busy
    (RDY = 0).

    @return Value of status register
    @retval flash_width: value of status register

    @StartSteps
  	@Step Send read status command (70h)
  	@Step Wait tWHR nanoseconds
  	@Step Read data
  	@EndSteps
 */
UINT8 NandFlash::ReadStatus()
{
    UINT8 Ret;
    if(NandFlashInitDone == FALSE)
    	Ret = NAND_NOTINITIALIZED;
    else{
		/* send command and/or address */
		SendCmd(CMD_READ_STATUS);
		/* wait */
		Wait(TIME_WHR);
		/* read value */
		Ret = ReadData();
    }
    return Ret;
}

/** @brief CheckFlashInitiallzation.
 *
 *  At power up this code creates a table of "Good Blocks" on flash which can be used for
 *  saving the presets.This function is called at powerup and cold start.
 *  Successful if 1000 Good Blocks are Available on Flash
 *
 *  @param void
 *  @return void
 */
void NandFlash::CheckFlashInitiallzation() {
   SINT32 I;
   NandAddress Addr;
   Addr.Column = 0;
   Addr.Lun = 0;
   Addr.Page = 0;
   Addr.Plane = 0;
	UINT8 TestBuff[2];
   SINT32 BlockPsTableIndx = 1;
   UINT32 BlockAddress;
   memset(BlockPsTable, 0xFF, sizeof(BlockPsTable));
   for (I = 0; I < BLOCKS_PER_LUN; I++) {
      BlockAddress = (I * BYTES_PER_BLOCK_SPARE) + BYTES_PER_PAGE;
      ExtractAddressSpare(BlockAddress, &Addr);
		TestBuff[0] = 0x00;
      ReadPage(Addr, TestBuff, 1, TRUE);
      if (TestBuff[0] == 0xFF) {
         BlockPsTable[BlockPsTableIndx].Block = I;
         BlockPsTableIndx++;
         if(BlockPsTableIndx > MAX_POSSIBLE_PRESET) break;
      }
   }
}

/** @brief Write a preset in Nand Flash.
 *
 *  Write a preset in Nand Flash.
 *
 *  @param void * FlashObjPtr pointer to Preset object where read preset shall be copied.
 *  @param UINT32  Preset_No Preset to be save in flash.
 *  @Length UINT32 Preset size in bytes default is sizeof(Ver1200Setups);
 *  @return UNIT8 NAND_SUCCESS if no error otherwise NAND_PROGRAM_FAILED.
 */
UINT8 NandFlash::WritePreset(void * FlashObjPtr, UINT32 Preset_No, UINT32 Length) {
	UINT8 RetVal = NAND_SUCCESS;
	UINT32 AddrToWrite;
	NandAddress Addr;
	UINT32 PageLeft = 0;
	UINT8 * DataAddr = (UINT8 *)FlashObjPtr;
	NandMutex.Lock();
	if((Preset_No > MAX_POSSIBLE_PRESET) || (BlockPsTable[Preset_No].Block == 0xFFFF))
		RetVal =  NAND_PROGRAM_FAILED;
	else
	{
		AddrToWrite = BLOCK_START_ADDR(BlockPsTable[Preset_No].Block);
		ExtractAddress(AddrToWrite, &Addr);
		Addr.Block = BlockPsTable[Preset_No].Block;
		RetVal = BlockErase(Addr);
	}
	if(RetVal == NAND_SUCCESS)
	{
		while((Length > 0) && (RetVal == NAND_SUCCESS))
		{
			//Page boundary check
			if(((AddrToWrite + Length) / BYTES_PER_PAGE) > (AddrToWrite / BYTES_PER_PAGE))
				PageLeft = (((AddrToWrite / BYTES_PER_PAGE) + 1) * BYTES_PER_PAGE) - AddrToWrite;
			else
				PageLeft = Length;

			ExtractAddress(AddrToWrite, &Addr);
			RetVal = PageProgram(Addr , DataAddr, PageLeft);
			AddrToWrite = AddrToWrite + PageLeft;
			Length -= PageLeft;
			DataAddr += PageLeft;
		}
	}

	NandMutex.Unlock();
	return RetVal;
}


/** @brief To read a preset from Nand Flash.
 *
 *  Read a preset from Nand flash
 *
 *  @param void * FlashObjPtr pointer to Preset object where read preset shall be copied.
 *  @param UINT32  Preset_No Preset to be read from flash.
 *  @Length UINT32 Preset size in bytes default is sizeof(Ver1200Setups)
 *  @return UNIT8 NAND_SUCCESS if no error otherwise NAND_READ_FAILED.
 */
UINT8 NandFlash::ReadPreset(void * FlashObjPtr, UINT32 Preset_No, UINT32 Length)
{
	UINT8 RetVal = NAND_SUCCESS;
	UINT32 AddrToRead = BLOCK_START_ADDR(BlockPsTable[Preset_No].Block);
	NandAddress Addr;
	UINT32 PageLeft = 0;
	UINT8 * DataAddr = (UINT8 *) FlashObjPtr;
	AddrToRead = BLOCK_START_ADDR(BlockPsTable[Preset_No].Block);

	if((Preset_No > MAX_POSSIBLE_PRESET) || (BlockPsTable[Preset_No].Block == 0xFFFF))
			RetVal =  NAND_READ_FAILED;
	NandMutex.Lock();
	if (RetVal == NAND_SUCCESS)
	{
		while ((Length > 0) && (RetVal == NAND_SUCCESS)) {
			if (((AddrToRead + Length) / BYTES_PER_PAGE) > (AddrToRead / BYTES_PER_PAGE))
				PageLeft = (((AddrToRead / BYTES_PER_PAGE) + 1) * BYTES_PER_PAGE) - AddrToRead;
			else
				PageLeft = Length;

			ExtractAddress(AddrToRead, &Addr);
			RetVal = ReadPage(Addr, DataAddr, PageLeft);
			AddrToRead = AddrToRead + PageLeft;
			Length -= PageLeft;
			DataAddr += PageLeft;
		}
	}
	NandMutex.Unlock();
	return RetVal;
}




