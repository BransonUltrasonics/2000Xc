/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/UploadFirmWareTask.h_v   1.2   02 Jan 2015 04:17:44   rjamloki  $*/
/*****************************************************************************
 $Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/UploadFirmWareTask.h_v  $
 * 
 *    Rev 1.2   02 Jan 2015 04:17:44   rjamloki
 * new html message string added for firmware upload
 * 
 *    Rev 1.1   20 Oct 2014 06:40:54   AnPawar
 * added some define for checksum
 * 
 *    Rev 1.0   28 Jul 2014 14:56:18   rjamloki
 * Initial revision.
 * 
 *
 *****************************************************************************/

#ifndef UPLOADFIRMWARETASK_H_
#define UPLOADFIRMWARETASK_H_

#include "Task.h"
#include "FIFO.h"
#include "portable.h"
#include "HttpServer.h"

#define ERR_UNKNOWNBINFILE 	   1
#define ERR_UNKNOWNFILETYPE    2
#define APP_FIRMWARE_FILE     "App_SUNRISE.bin"
#define BOOT_FIRMWARE_FILE    "BootLoad_SUNRISE.bin"
#define COMP_FIRMWARE_FILE    "Complete_SUNRISE.bin"
#define APP_FIRMWARE_CHECKSUM 3721182122uL
#define BOOT_FIRMWARE_CHECKSUM 4007513275uL
#define COMP_FIRMWARE_CHECKSUM 4293844428uL
#define FIRMWARE_UPLOAD_REQUESTURI "SunriseFirmwareUpload32923646.html"
enum FileType
{
	FileTypeErr,
	FileTypeBin,
};

enum FlashArea
{
   FlashAreaInvalid,
   FlashAreaBootloader,
   FlashAreaApp,
   FlashAreaComplete,
};

struct MsgUploadFirmware
{
	FileType Filetype;
	FlashArea ProgramArea;
	SINT32   FileLen;
	SINT8    * FileData;
	SINT8    * Action;
};



class UploadFirmware: public Task
{
	public:
		UploadFirmware();
		static bool FirmWareFileUploadHandler(char * Data, int DataLen,  char * FileName, char * Action);
		static bool FirmWareFilePostHandler(char * PostData, char * Uri, HTTPReplyHeader &Header);
		static bool FirmWareFileGetHandler(char * Uri, HTTPReplyHeader &Header);
		bool ProgramFirmware(FileType FType, SINT8 * Data, SINT32 DataLen, FlashArea ProgramArea, SINT8* Action);
		static UploadFirmware * thisPtr;
	protected:
		void Run();
		void ProgramFlash(SINT8 * Data, SINT32 DataLen, FlashArea Flasharea);
		MsgUploadFirmware Msg;
		Fifo<MsgUploadFirmware> UpLoadQ;
};

void EraseCallback(int Offset, int Length);
void ProgramCallback(int Offset, int Length);
UINT16 ByteCRC(UINT8 * Ptr, UINT32 Length);

#define HTTP_PORT 80

static const SINT8 * const FirmwareUpload =
		"<html>"
		"<script language=\"javascript\" type=\"text/javascript\">"
		"var SupportedExtensionsArr = [\"bin\"];"
		"var MaxFileNameLen = 200;"
		"var uploadInProgress = false, uploadInitiated = false;"
		"var http = null;"
        "function getXHR() {"
        "    if (window.XMLHttpRequest) {"
        "        return new XMLHttpRequest();"
        "    }"
        "    try {"
                "return new ActiveXObject('MSXML2.XMLHTTP.6.0');"
            "} catch (e) {"
            "    try {"
                    "return new ActiveXObject('MSXML2.XMLHTTP.3.0');"
                "} catch (e) {"
				"try {"
				" return new ActiveXObject('Microsoft.XMLHTTP');"
				"} catch (e) {"
                    "alert('This browser is not AJAX enabled.');"
                    "return null;"
                "}"
			  "}"
            "}"
        "}"
		"function HandleFileUploadInitiateCommand(){"
		" if(http.readyState == 4){"
		"  if (http.responseText == \"READY\")"
		"            SendFileUploadStartCommand();"
		"        else {"
		"            document.getElementById(\"btnupload\").disabled = false;"
		"            uploadInitiated = false;"
		"            alert(\"File upload not initiated\");"
		"        }"
		"    }"
		"}"
		"function SendFileUploadInitiateCommand(){"
		"    var indx;"
		"    var extMatched = false;"
		" if (uploadInitiated != true){"
		"  if (document.getElementById(\"file\").value == \"\"){"
		"   alert(\"Please select a file to upload\");"
		"  }"
		"  else{"
		"   var fileExt = document.getElementById(\"file\").value.split(\".\");"
		"   var ext = fileExt[fileExt.length - 1];"
		"   try{"
		"    for (indx = 0; indx < SupportedExtensionsArr.length && extMatched == false; indx++)"
		"     if (SupportedExtensionsArr[indx] == ext)"
		"      extMatched = true;"
		"   }"
		"   catch(err){};"
		"   if(extMatched){"
		"    var fileLen = document.getElementById(\"file\").value;"
		"    if (fileLen.length >= MaxFileNameLen)"
		"     alert(\"FileName including path should be less than 200 characters\");"
		"    else{"
		"	  if(http == null)"
		"		http = getXHR();"
		"		if(http != null) {"
		"     uploadInitiated = true;"
		"     document.getElementById(\"btnupload\").disabled = true;"
		"     var SystemInfoUrl = \"?param=.sunrisefileupload\";"
		"     http.open(\"POST\", SystemInfoUrl, true);"
		"     http.onreadystatechange = HandleFileUploadInitiateCommand;"
		"     http.send(null);"
		"	}	"
		"    }"
		"   }"
		"   else"
		"    alert(\"Only bin file is supported\");"
		"  }"
		" }"
		"}"
		"function SendFileUploadStartCommand(){"
		"    if (uploadInProgress != true){"
		"     uploadInProgress = true;"
		"     document.getElementById(\"btnupload\").disabled = true;"
		"     fileLen = document.getElementById(\"file\").value.split(\"\\\\\");"
		"     document.getElementById(\"file_upload_form\").action = fileLen[fileLen.length - 1];"
		"     document.getElementById(\"file_upload_form\").submit();"
		"  }"
		"}"
		"</script>"
		"<BODY>"
		"<div class = \"PageHeader\"> Firmware Upload </div>"
		" <div class=\"contentBoxCenter\" >"
		" <div class=\"gradientBox400\">"
		" <form id=\"file_upload_form\" method=\"post\" enctype=\"multipart/form-data\" action=\"temp\">"
		" <input name=\"file\" id=\"file\" size=\"30\" type=\"file\" /><br /><br />"
		" <input type=\"button\" name=\"submitbutton\" id=\"btnupload\" value=\"Upload\" onclick=\"SendFileUploadInitiateCommand()\" /><br />"
		" </form>"
		" </div>"
		"</div>"
		"</BODY>"
		"</HTML>";

static const SINT8 * const FirmwareUploadError =
		"<html><head><title>Firmware Upload</title></head>"
					"<body> Higher authority required";

#endif /* UPLOADFIRMWARETASK_H_ */
