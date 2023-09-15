/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/UploadFirmWareTask.cpp_v   1.9   16 Apr 2015 07:18:08   rjamloki  $*/
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/App/UploadFirmWareTask.cpp_v  $
 * 
 *    Rev 1.9   16 Apr 2015 07:18:08   rjamloki
 * Diagnostic code removed
 * 
 *    Rev 1.8   27 Mar 2015 14:49:18   RJamloki
 * Reenabled security check on firmware upload
 * 
 *    Rev 1.7   13 Mar 2015 06:09:26   amaurya
 * FirmWareFileGetHandler() changed to removed extra Get request. 
 * 
 *    Rev 1.5   11 Feb 2015 06:30:56   amaurya
 * Changes to debug recalibrate actuator alarm issue
 * 
 *    Rev 1.4   08 Jan 2015 03:18:28   AnPawar
 * printf removed
 * 
 *    Rev 1.3   02 Jan 2015 04:10:20   rjamloki
 * changes to secure firmware upload
 * 
 *    Rev 1.2   20 Oct 2014 06:27:32   AnPawar
 * ProgramFlash() ,FirmWareFileUploadHandler() function changed
 * 
 *    Rev 1.1   11 Sep 2014 11:10:24   rjamloki
 * Added firmware upload event
 * 
 *    Rev 1.0   28 Jul 2014 14:57:12   rjamloki
 * Initial revision.
 * 
 *
 *****************************************************************************/

#include "UploadFirmWareTask.h"
#include "stdio.h"
#include "Board.h"
#include "CPU.h"
#include "DebugNew.h"
#include "ASSERT.h"
#include "Flash.h"
#include "CyGOS.h"
#include "Board.h"
#include "qdef.h"
#include "command.h"
#include "Events.h"

//This is the global pointer to Task Object
UploadFirmware * UploadFirmware::thisPtr;
/*   Purpose :
 *	 	Constructor for UploadFirmware task called when task is created. and name.
 *
 *   Entry condition
 *
 *   Exit condition
 *   	None
 */
UploadFirmware::UploadFirmware():Task("UPLDFM", T_SIZE_1024), UpLoadQ(1, "UPLDQ")
{
	thisPtr = this;
	CyGOS::AddHttpFileUploadHandler(ETHERNET_INTERFACE_WCTOSBC, HTTP_PORT, FirmWareFileUploadHandler);
	CyGOS::AddHttpGetHandler(ETHERNET_INTERFACE_WCTOSBC, HTTP_PORT, FirmWareFileGetHandler);
	CyGOS::AddHttpPostHandler(ETHERNET_INTERFACE_WCTOSBC, HTTP_PORT, FirmWareFilePostHandler);
	memset(&Msg, 0 , sizeof(Msg));
}


/*  void UploadFirmware::Run()
 *
 *   Purpose:
 *   This function waits indefinitely for upload command to be received from HttpServer Task running
 *   as part of CyGOS .Once the command is received it performs the requires action based on received command.
 *
 *   Entry condition
 *   	None.
 *
 *   Exit condition
 *   	None.
 */
void UploadFirmware::Run(void)
{
	MsgUploadFirmware TempQ;
	for(;;){
		UpLoadQ.Read(this, TempQ, -1);
		ProgramFlash(TempQ.FileData, TempQ.FileLen, TempQ.ProgramArea);
	}//for(;;)
}


/*   void UploadFirmware::ProgramFlash(SINT8 * Data, SINT32 DataLen, FlashArea Flasharea)
 *
 *   Purpose:
 *   	This function programs the area of flash requested with received data
 *   	This function is called from the Run() function of this class.
 *
 *   Entry condition :
 *   	Data - Pointer to the data to be programmed on FLASH
 *   	DataLen - length of data to be programmed.
 *    	Flash area- Area of flash to be programmed boot loader, Application or complete bin
 *   Exit condition
 *   	None.
 */
void UploadFirmware::ProgramFlash(SINT8 * Data, SINT32 DataLen, FlashArea Flasharea)
{
	SINT32 DataLenLimit = 0;
	BOOLEAN ValidFlashArea = TRUE;
	void * FlashAreaStartAddr;
	Flash * FlashPtr = Board::GetFlash();
	SINT8 * FlashData = Data;
	ASSERT(FlashPtr);
    CyGOS::StopTimer(1);//1 Ms task , State machine and lot of things are disabled here
	if(Flasharea == FlashAreaBootloader){
	  DataLenLimit = (SINT32)__FLASH_BASE;
	  FlashAreaStartAddr = (void *)__BOOTLOADER_SIZE;
	}
	else if(Flasharea == FlashAreaApp){
	  DataLenLimit = (SINT32)__FLASH_SIZE;
	  FlashAreaStartAddr = (void *)__FLASH_ROM;
	}
	else if(Flasharea == FlashAreaComplete){
	  DataLenLimit = (SINT32)__FLASH_SIZE + (SINT32)__BOOTLOADER_SIZE + (SINT32)__TAR_SIZE;
	  FlashAreaStartAddr = (void *)0;
	}
	else
	  ValidFlashArea = FALSE;

	if(ValidFlashArea == TRUE){
	  if((DataLen > 0) && (DataLen <= DataLenLimit)){
		 CyGOS::Stop();
		 FlashPtr -> Unlock(FlashAreaStartAddr, DataLen);
		 FlashPtr -> Erase(FlashAreaStartAddr, DataLen, EraseCallback);
		 FlashPtr -> Program(FlashAreaStartAddr, FlashData, DataLen, ProgramCallback);
		 FlashPtr -> Lock(FlashAreaStartAddr, DataLen);
		 RecordEvents(EVENT_FIRMWARE_UPLOAD,"","");
		 CyGOS::Restart() ;
	  }
	}
	CyGOS::StartTimer(1);
	delete FlashPtr;
	delete Data;
}


/*   BOOLEAN UploadFirmware::ProgramFirmware(FileType Ftype, SINT8 * Data, SINT32 DataLen,SINT8 * Action)
 *
 *   Purpose
 *   	This function gets called by website module after receiving the firmware file.
 *
 *   Entry condition
 *   	Ftype: type of file
 *   	Data:  data to be programmed
 *   	DataLen: Length of data
 *		Action:URI used for upload request
 *   Exit condition
 *   	Returns TRUE if data was written into fifo else return FALSE
 */
bool UploadFirmware::ProgramFirmware(FileType Ftype, SINT8 * Data, SINT32 DataLen, FlashArea ProgramArea, SINT8 * Action)
{
	bool RetVal;
	Msg.Filetype = Ftype;
	Msg.FileLen = DataLen;
	Msg.FileData = Data;
	Msg.Action = Action;//unused
	Msg.ProgramArea = ProgramArea;
	RetVal = UpLoadQ.Write(0, Msg ,0);
	//TODO: Only Branson Personal would be uploading the code and will be aware that cycle should not run during
	//or before starting upload. If not we need to check what state machine is doing.
	return RetVal;
}


/* BOOLEAN UploadFirmware::FirmWareFileUploadHandler(SINT8 * Data, SINT32 DataLen, SINT8 * FileName, SINT8 * Action)
 *
 *  Purpose:
 *    This function handles the firmware file upload request.
 *
 *  Entry condition: Data- pointer to file data.
 *                  DataLen- The length of file data.
 *                  FileName- The file name.
 *					Action- The action URI requested by the html page.
 *  Exit condition: Returns true if file is successfully send to Upload Firmware task Q.
 */
bool UploadFirmware::FirmWareFileUploadHandler(char * Data, int DataLen,  char * FileName, char * Action)
{
	BOOLEAN RetVal = TRUE;
    FileType Ftype = FileTypeErr;
    FlashArea FArea = FlashAreaInvalid;
    unsigned long int CheckSum = 0;
    memcpy(&CheckSum,&Data[DataLen-4],4);
	SINT8 * Ext, * Ext1, *BKSlash;
	SINT8 * Buff = 0;
	BKSlash = strchr(FileName, '\\');

	while(BKSlash){
		FileName = BKSlash + 1;
		BKSlash = strchr(BKSlash + 1, '\\');
	}

	Ext = strchr(FileName, '.');
	Ext1 = Ext;
	while(Ext){
	  Ext1 = Ext;
	  Ext = strchr(Ext + 1, '.');
    }
    if(!strcmp(Ext1, ".bin")){
	   Ftype =  FileTypeBin;
    }
    else
    	RetVal = FALSE;

    if(RetVal == TRUE){//Extension is verified Verify File name
    	if(((strncmp(FileName, APP_FIRMWARE_FILE, strlen(APP_FIRMWARE_FILE))) == 0)||(CheckSum ==  APP_FIRMWARE_CHECKSUM))
    		FArea = FlashAreaApp;
    	else if(((strncmp(FileName, BOOT_FIRMWARE_FILE, strlen(BOOT_FIRMWARE_FILE))) == 0)||(CheckSum == BOOT_FIRMWARE_CHECKSUM))
    		FArea = FlashAreaBootloader;
    	else if(((strncmp(FileName, COMP_FIRMWARE_FILE, strlen(COMP_FIRMWARE_FILE))) == 0)||(CheckSum == COMP_FIRMWARE_CHECKSUM))
    		FArea = FlashAreaComplete;
    	else
    		RetVal = FALSE;
    }
    if((CurrentSetup.ControlLevel>=LEVEL_c)&&((UserLoggedIn == FALSE)||(FirmwareUploadAllowed == FALSE)))
    	RetVal = FALSE;
    if(RetVal == TRUE){//Extension is verified , File name is verified
		Buff = new SINT8[DataLen];
		memcpy(Buff, Data, DataLen);
		RetVal = UploadFirmware::thisPtr->ProgramFirmware(Ftype, Buff, DataLen, FArea, Action);
	}

    if(!RetVal && Buff)
    	delete []Buff;

    return RetVal;
}

/* BOOLEAN WebSite::FirmWareFilePostHandler(SINT8 * PostData, SINT8 * Uri, HTTPReplyHeader & Header)
 *
 *  Purpose:
 *  This post handler is used to check for file upload initiate command. It ignores all other requests.
 *  Entry condition: File Upload is initiated from Sunrise Specific Firmware download page
 *  Exit condition: Returns TRUE in case of valid request otherwise returns FALSE.
 */
bool UploadFirmware::FirmWareFilePostHandler(char * PostData, char * Uri, HTTPReplyHeader &Header)
{
	bool RetVal = FALSE;
	BOOLEAN UploadRequest = (strstr(Uri, ".sunrisefileupload") != 0);//see if its a upload request
	PostData = 0;//Ignore post Data
	static SINT8 * Res = "READY";
	if (UploadRequest) {
		Header.contentLength = strlen(Res);
		Header.data = Res;
		Header.reqType = reqFileUpload;
		RetVal = TRUE;
	}
	return RetVal;
}


/* BOOLEAN WebSite::FirmWareFileGetHandler(SINT8 * Uri, HTTPReplyHeader &Header)
 *
 *  Purpose:
 *  This function is called by HTTPServer task on receiving Get request.
 *  It only entertains a URL <IP>/SunriseFirmwareUpload32923646.html/
 *  Entry condition: Uri- The URI to open the Sunrise Specific Firmware Upload page
 *  Exit condition: Returns TRUE in case of valid request otherwise returns FALSE.
 */
bool UploadFirmware::FirmWareFileGetHandler(char * Uri, HTTPReplyHeader &Header)
{
	 bool RetVal = FALSE;
	 if(*(Uri + 1))
	 {
		 if(strncmp((Uri + 1), FIRMWARE_UPLOAD_REQUESTURI, strlen(FIRMWARE_UPLOAD_REQUESTURI)) == 0)
		 {
			 RetVal = TRUE;
			 Header.reqType = reqData;
			 if((CurrentSetup.ControlLevel>=LEVEL_c) && ((UserLoggedIn == FALSE) || (FirmwareUploadAllowed == FALSE)))
			 {
				 Header.data = (SINT8*)FirmwareUploadError;
				 Header.contentLength = strlen(FirmwareUploadError);
			 }
			 else
			 {
				 Header.data = (SINT8*)FirmwareUpload;
				 Header.contentLength = strlen(FirmwareUpload);
			 }
			 Header.statusCode = httpOk;
		 }
	 }
	 return RetVal;
}
