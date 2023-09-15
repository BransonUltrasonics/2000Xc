/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Connection.cpp_v   1.13   11 Mar 2015 09:26:04   amaurya  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/MICRO_11.22-A/Connection.cpp_v  $
 * 
 *    Rev 1.13   11 Mar 2015 09:26:04   amaurya
 * PrepareBufferForWebService() changed to send parameter name with event description while user request for evend data through webservice.
 * 
 *    Rev 1.12   30 Jan 2015 08:13:16   amaurya
 * JsonDataRequest() changed to get SBC version number through webservice.
 * 
 *    Rev 1.11   11 Dec 2014 06:48:54   RJamloki
 * PrepareBufferForWebService() changed to send nonprintable characters along with welddata to WC on JSON Request from WebService client.
 * 
 *    Rev 1.10   28 Nov 2014 08:30:02   rjamloki
 * Added function headers and coverity issues
 * 
 *    Rev 1.9   10 Nov 2014 02:48:36   rjamloki
 * JsonDataRequest() and PrepareBufferForWebService() changed to add WrapAround Case functionality.
* 
*    Rev 1.8   06 Oct 2014 03:22:40   rjamloki
*  JsonDataRequest() and PrepareBufferForWebService() functions changed
* 
*    Rev 1.7   01 Oct 2014 10:47:24   AnPawar
* Changes for web services.
* 
*    Rev 1.6   28 Jul 2014 13:39:00   rjamloki
* review fixed
* 
*    Rev 1.5   09 Jun 2014 11:39:08   rjamloki
* Variable initialization in constructor.
* 
*    Rev 1.4   28 Mar 2014 14:32:58   rjamloki
* Removed old header comments and cleanup
*
*    Rev 1.3     05 Mar 2014 14:13:14 rjamloki      
* Screens and PDF working
*
*    Rev 1.2     03 Jan 2014 09:04:48 rjamloki      
* Header Fix and added command to assign ip.
*
*    Rev 1.1     05 Jun 2013 09:33:20 amaurya      
* Initial Revision 2.
*
*    Rev 1.0     03 Apr 2013 10:09:44 amaurya      
* Initial Revision.
*/


#include "stdafx.h"
#include "Application.h"
#include "Connection.h"
#include "HostCommand.h"
#include "EventLog.h"
#include "WeldingHistory.h"
#include "EventHistoryData.h"
#include "VGA.h"

#define DLE	0x10
#define SOH 0x01
#define STX 0x02
#define ETX 0x03
#define BEL 0x07
#define EOT 0x04

#define MAX_WELDDATA_BUFFLEN (80 *1024)
#define NUM_RETRIRES_AFTER_CONNECTION 5//After connection is made the number of times
//server will poll for valid data
#define MAX_EVENTLOG_PER_REPLY 100
#define LATEST_HISTORYNUM_JSON    50//The number of lates weld or event records to be sent when from and to fields are 0 from web service

#ifdef _DEBUG
#undef THIS_FILE
static char THIS_FILE[]=__FILE__;
#define new DEBUG_NEW
#endif

extern CString EventDataFileName;
extern CString HistoryDataFileName;
extern char Version[7];
extern CString GetNameFromID(int ParamID,bool InEnglish = false);

JsonEventLog * EventDatatoSend = 0;
char * WeldDatatoSend = 0;
char STR[2048];
CString PrepareDescription(int ParamID,int EventID,CString Data,bool JsonReq);
int CountOfEventSent;
int CountOfWeldSent;


CConnection::CConnection(SOCKET fd) : CClientSocket(fd)
{
   SetBufferSizes();
   request = 0;
   state = STATE_NORMAL;
   delimiter = 0;
   inbuflen = 0;
   outbuflen = 0;
   RetriesForData = NUM_RETRIRES_AFTER_CONNECTION;
}

CConnection::~CConnection()
{
   Close();
}

/*
Function is called by EtherPort thread to check for data received once the input socket set is triggered.
If not data s received up to 5 polls the connection is closed.
*/
void CConnection::ProcessInput()
{
   if (!ProcessInputEx() && (--RetriesForData <= 0))
      CloseConnection();   
}

//	EOF - return false;
//	data - return true;
/*
Function is called by ProcessInput function. It receives the data on tcp socekt and process it based on the JSON request from WC or
regular requests from outside world.
*/
bool CConnection::ProcessInputEx()
{

   char Buff[sizeof(JsonPacket)];
   bool JsonReq = false;
   JsonPacket * msg;
   for (;;) 
   {


      int ret = recv(fd, (char*)Buff, sizeof(Buff), 0);         
      if (ret == 0)		// EOF, connection closed
         break;
      if (ret < 0)		// error of some kind
      {
         int error = WSAGetLastError();
         if ((error == WSAEWOULDBLOCK) || (error == WSAEINTR))
            return true;	// ok with these errors
         // here we don't know what happened, so let's just report the error
         CString s;
         s.Format(_T("TCPSocket::read: error %d - disconnecting..."), error);
         app->Trace(s);
         break;
      }
      JsonReq = false;
      if(ret == sizeof(JsonPacket))
      {
         msg = (JsonPacket *)Buff;
         JsonReq = JsonDataRequest(msg);
      }

      if(JsonReq == false)    
      {
         for(int i =0; i < ret; i++)
            CharReceived(Buff[i]);
      }
   }
   return false;
}
/* This function close the tcp socket connection*/
void CConnection::CloseConnection()
{
   Close();
}
/*************************************************************************************************/
/* This function extract the required data from JTestPacket sent by WC Client                    */
/*  and checks if it is valid or not ,if valid then it calls PrepareBufferForWebService()        */
/*  to prepare the data buffer . on successfull data buffer preparation it calls JSonDataReply() */
/*  to send fragmented data to WC Client                                                         */
/* Entery Condition::                                                                            */
/*      Pointer to JsonPacket                                                                    */
/*   Exit Condition::                                                                            */
/*      nothing                                                                                  */                                                                                              
/*************************************************************************************************/
bool CConnection::JsonDataRequest(JsonPacket * JTestPacket)
{
   int Count;
   int RetVal = 0; 
   
   int startingpoint = 0;
   int FileCount = 0;
   size_t TotalSize;   
   bool JosnReq = true;
   int From = ntohl(JTestPacket->From) ,To = ntohl(JTestPacket->To);

   if(ntohl(JTestPacket->FieldId) == EVENTLOGFIELDID)
   {
      if((To == 0) && (From == 0))
      {
         if(CEventLog::SuccessfullyWrittenEventRecord > LATEST_HISTORYNUM_JSON){
            startingpoint = (CEventLog::SuccessfullyWrittenEventRecord % MAX_ALLOWED_EVENT_LOG) - LATEST_HISTORYNUM_JSON;
            if(startingpoint < 0)
               startingpoint = MAX_ALLOWED_EVENT_LOG + startingpoint;
            Count = LATEST_HISTORYNUM_JSON;
         }
         else
         {
            startingpoint = 0;
            Count = CEventLog::SuccessfullyWrittenEventRecord;
         }
         RetVal = PrepareBufferForWebService(EventDataFileName,startingpoint,Count,true); 
         if(RetVal > 0)
         {    
            TotalSize = CountOfEventSent * sizeof(JsonEventLog);        
            JSonDataReply((char *)EventDatatoSend, TotalSize);
         }
         else
            JSonDataReply(0, 0); 
      }
      else
      {
         if(To >= CEventLog::SuccessfullyWrittenEventRecord || From > CEventLog::SuccessfullyWrittenEventRecord
            || To >= MAX_ALLOWED_EVENT_LOG || ((To - From) < 0))
            JSonDataReply(0, 0);   
         else
         {
            Count = To-From+1;         
            //Need to calculate from value relative to latest record. 
            //First case records are less than MAX_ALLOWED_EVENT_LOG(The max allowed). From is correct in this case.
            //Second case: Memory_continue flag is true and the latest record is not at the end of file
            if(CEventLog::SuccessfullyWrittenEventRecord > MAX_ALLOWED_EVENT_LOG){
            
	            startingpoint = (CEventLog::SuccessfullyWrittenEventRecord % MAX_ALLOWED_EVENT_LOG) + From;
	            if(startingpoint > MAX_ALLOWED_EVENT_LOG)
	               startingpoint = startingpoint - MAX_ALLOWED_EVENT_LOG;
            }
            else
               startingpoint = From;

            RetVal =PrepareBufferForWebService(EventDataFileName,startingpoint,Count,true);  
            if(RetVal > 0)
            {      
               TotalSize = CountOfEventSent * sizeof(JsonEventLog);
               JSonDataReply((char *)EventDatatoSend, TotalSize);
            }
            else
               JSonDataReply(0, 0); 
         } 
      }
      if(EventDatatoSend)
      {
         delete []EventDatatoSend;
         EventDatatoSend = 0;
      }
   }
   else if(ntohl(JTestPacket->FieldId) == WELDHISTORYFIELDID)
   {
      if((To == 0) && (From == 0))
      {
         if(CWeldingHistory::thisHisPtr->TotalDataInFile > LATEST_HISTORYNUM_JSON){
            startingpoint = (CWeldingHistory::thisHisPtr->TotalDataInFile % MAX_ALLOWED_WELD_LEVEL_C) - LATEST_HISTORYNUM_JSON;
            if(startingpoint < 0)
               startingpoint = MAX_ALLOWED_WELD_LEVEL_C + startingpoint;
            Count = LATEST_HISTORYNUM_JSON;
         }
         else{
            startingpoint = 0;
            Count = CWeldingHistory::thisHisPtr->TotalDataInFile;
         }

         RetVal =PrepareBufferForWebService(HistoryDataFileName,startingpoint,Count,false); 

         if(RetVal >0 )
         {
            TotalSize = (strlen(WeldDatatoSend));
            JSonDataReply((char *)WeldDatatoSend, TotalSize);          
         }    
         else
            JSonDataReply(0, 0); 
      }
      else
      {
         if((unsigned int)To >= CWeldingHistory::thisHisPtr->TotalDataInFile || (unsigned int)From > CWeldingHistory::thisHisPtr->TotalDataInFile
            || To >= MAX_ALLOWED_WELD_LEVEL_C || ((To - From) < 0))
            JSonDataReply(0, 0);   
         else
         {
            Count = To-From+1;
	        if(CWeldingHistory::thisHisPtr->TotalDataInFile > MAX_ALLOWED_WELD_LEVEL_C){
	            startingpoint = (CWeldingHistory::thisHisPtr->TotalDataInFile % MAX_ALLOWED_WELD_LEVEL_C) + From;
	            if(startingpoint > MAX_ALLOWED_WELD_LEVEL_C)
	               startingpoint = startingpoint - MAX_ALLOWED_WELD_LEVEL_C;
            }
            else
               startingpoint  =From;
            RetVal =PrepareBufferForWebService(HistoryDataFileName,startingpoint,Count,false);  
            if(RetVal > 0)
            {
               TotalSize = (strlen(WeldDatatoSend));
               JSonDataReply((char *)WeldDatatoSend, TotalSize);           
            }
            else
               JSonDataReply(0, 0); 
         }
      }
      if(WeldDatatoSend)
      {
         delete WeldDatatoSend;
         WeldDatatoSend = 0;
      }
   }
   else if(ntohl(JTestPacket->FieldId) == REQFOREVENTLOGCOUNT)
   {
      if(CEventLog::SuccessfullyWrittenEventRecord > MAX_ALLOWED_EVENT_LOG)
         FileCount = ntohl(MAX_ALLOWED_EVENT_LOG);
      else
         FileCount = ntohl(CEventLog::SuccessfullyWrittenEventRecord);
      if(send(fd, (char*)&FileCount,sizeof(int), 0) == SOCKET_ERROR)
		  JosnReq = false;
   }
   else if(ntohl(JTestPacket->FieldId) == REQFORWELDLOGCOUNT)
   {
      if(CEventLog::SuccessfullyWrittenEventRecord > MAX_ALLOWED_WELD_LEVEL_C)
         FileCount = ntohl(MAX_ALLOWED_WELD_LEVEL_C);
      else
         FileCount = ntohl(CWeldingHistory::thisHisPtr->TotalDataInFile);
      if(send(fd, (char*)&FileCount,sizeof(int), 0) == SOCKET_ERROR)
		  JosnReq = false;
   } 
   else if(ntohl(JTestPacket->FieldId) == REQFORSBCVERSION)
   {
      if(send(fd,(char*)&Version,sizeof(Version), 0) == SOCKET_ERROR)
		  JosnReq = false;
   }
   else
      JosnReq = false;

   return 	JosnReq;
}
/******************************************************************************/
/* This function split the data into 2048 size fragments and send it over TCP */
/* Entery Condition ::                                                        */
/*    char *buff the pointer to data buffer and size_t Len as the total data  */
/* length in buffer                                                           */
/* Exit Condition ::                                                          */
/*    nothing                                                                 */     
/******************************************************************************/
void CConnection::JSonDataReply(char * buff, size_t Len)
{    
   int FragmentedSize = 2048, BuffPtr = 0;   
   JsonSBCDataHandshakepacket Lenpacket;
   Lenpacket.TotalExpectedData = ntohl(Len);
   if(send(fd, (char*)&Lenpacket, sizeof(Lenpacket), 0) != SOCKET_ERROR)
   {
	   if(Len < (size_t)FragmentedSize)
		  FragmentedSize = Len;
	   while(Len > 0)
	   {
		  if(send(fd, buff + BuffPtr,FragmentedSize, 0) != SOCKET_ERROR)
		  {
			Len -= FragmentedSize;
			BuffPtr += FragmentedSize;
		  }
		  if(Len < (size_t)FragmentedSize)
			 FragmentedSize = Len; 
		  Sleep(1);
	   }
   }
}

/*
This function is called by ProcessInputEx function. It verifies the data recived to be a valid command from logger utilities which request weld result.
It sends the command to WC to to get the weld result and then send the weld result to Logger utilities on tcp.
*/
void CConnection::CharReceived(char ch)
{
   CString s;
   int retVal = 0;
   s.Format(_T("Received '%c'"), ch);
   app->Trace(s);
   if (!request)
      request = new CHostCommand(true);
   if (request->CharRec(ch))	// got full packet?
   {
      CHostCommand * response = app->SendEnHostCommand(request);
      if (response)
      {
         app->Trace("Sending response back to ethernet");
         char ch1 = response->AckNak();
         int length =response->GetBufLength();
         if(ch1 != DLE) //Which will come in case of StartWeldData command.
            retVal = send(fd, &ch1, 1, 0);

         if(retVal == SOCKET_ERROR)
         {
            closesocket(fd);
            WSACleanup();
            delete response;
            return;
         }

         char * buf = (char *) response->GetBuffer();
         if(buf)
            retVal = send(fd, buf, length, 0);
         if(retVal == SOCKET_ERROR)
         {
            closesocket(fd);
            WSACleanup();
         }
         delete response;
      }
   }
}

/******************************************************************************************/
/*  This function reads the data from Event or Weld file and stores it into a globlal 	  */			
/*	buffer for TCP/IP	                                                                  */
/*  *Entry condition:                                                                     */
/*    Takes CString Path as file path,int as starting point from where data to be read and*/
/*   int count total data to be read and bool Event_Or_Weld to select event or weld data  */
/*  Exit condition:                                                                       */
/*    returns the length of the data added to the buffer 	                              */		
/******************************************************************************************/

int CConnection::PrepareBufferForWebService(CString Path ,int StartingPoint,int Count,bool Event_Or_Weld)
{
   unsigned long ObjectSize;
   size_t   TempLen;
   CFile f;
   CFileException e;
   unsigned int NoOfBytesRead=0;
  
   char timeBuff[32];
   CountOfEventSent = 0;
   CountOfWeldSent = 0;
   size_t TotalLen = 0;
 
   CString Data_Old = "";
   CString Data_New = "";	
   if( !f.Open( Path, CFile::modeCreate |CFile::modeNoTruncate |CFile::modeReadWrite , &e ) )
   {
#ifdef _DEBUG
      if(e.m_cause==CFileException::generic)
         TRACE(_T("\n !! GENERIC"));
      else if(e.m_cause==CFileException::badPath   )
         TRACE(_T("\n !! bad path"));
      else if(e.m_cause==CFileException::tooManyOpenFiles    )
         TRACE(_T("\n !! too many files open"));
      else if(e.m_cause==CFileException::fileNotFound )
         TRACE(_T("\n !! file not found"));
      else if(e.m_cause==CFileException::accessDenied       )
         TRACE(_T("\n !! access denied"));
      else if(e.m_cause==CFileException::diskFull      )
         TRACE(_T("\n !! disc full"));
      else if(e.m_cause==CFileException::invalidFile   )
         TRACE(_T("\n !! invalid file"));
      afxDump << "File could not be opened " << e.m_cause << "\n";
#endif
   }
   else
   {	
      if(f.GetLength()==0)
      {
         f.Close();
         return false ;
      }
      if(Event_Or_Weld)
      {
         EventDatatoSend = new JsonEventLog[MAX_EVENTLOG_PER_REPLY];
         unsigned long HeaderSize = sizeof(UINT32) + sizeof(char) + sizeof(UINT32) + sizeof(char);
         unsigned long size = sizeof(CEventHistoryData);
         ObjectSize = size + sizeof(char);			
         char Comma;	        
         UINT16 EventId;
         JsonEventLog JsonEventObj;
         CEventHistoryData FileEventObj; 
         f.Seek(StartingPoint*ObjectSize + HeaderSize,CFile::begin);
		 DisplayPosition NameDisplayPosition = DO_NOT_DISPLAY;
		 while((NoOfBytesRead<f.GetLength()) && (Count--))
         {             
            CString Description = "";
            CString ParameterID ="";
            CString EventID ="";
            UINT8 * IntID;
            ParamDescription *Pdescr = NULL;
            EventDescription *Descr = NULL;			
            memset(&JsonEventObj, 0 , sizeof(JsonEventObj));
            NoOfBytesRead+=f.Read(&FileEventObj,size);
            NoOfBytesRead+=f.Read(&Comma,sizeof(char));        
            JsonEventObj.EventNum = ntohl(FileEventObj.EventHistoryObj.EventNum);
            JsonEventObj.PresetNo = ntohs(FileEventObj.EventHistoryObj.PresetNo);
            JsonEventObj.Rev = ntohs(FileEventObj.EventHistoryObj.Rev);
            strcpy((char*)JsonEventObj.UserId,(char*)FileEventObj.EventHistoryObj.UserId);
            strcpy((char*)JsonEventObj.EventId,(char*)FileEventObj.EventHistoryObj.EventId);
            strcpy((char*)JsonEventObj.PSSerialNumber,(char*)FileEventObj.EventHistoryObj.PSSerialNumber);
            strcpy((char*)JsonEventObj.EventReason,(char*)FileEventObj.EventHistoryObj.EventReason);

            EventID = FileEventObj.EventHistoryObj.EventId;
            IntID =  FileEventObj.EventHistoryObj.EventId;

            Data_Old= CString((char*)(FileEventObj.EventHistoryObj.DataOld))  ;
            Data_New= CString((char*)(FileEventObj.EventHistoryObj.DataNew)) ;
            ParameterID.Format(_T("%d"),FileEventObj.EventHistoryObj.ParameterId);	
            theApp.eds.Lookup(EventID, Descr);
            theApp.pds.Lookup(ParameterID,Pdescr);
            if(Descr == NULL)//
            {
               EventID.Format(_T("EV%d"),900);//invalid event id
               theApp.eds.Lookup(EventID, Descr);
            }
            Description =Descr->GetEventDescription(true);	
			NameDisplayPosition = (DisplayPosition)_tstoi(Descr->DisplayPosition);
            EventId = atoi((char*)(IntID+2));	
            if(EventId == EVENT_CALIBRATION)//calibration related events
               Description = PrepareDescription(FileEventObj.EventHistoryObj.ParameterId,EventId,Data_Old,true);
            else if(EventId == EVENT_USER_MODIFIED )
            {
               if(Pdescr!=NULL)
               {
                  if(FileEventObj.EventHistoryObj.ParameterId == PASSWORD_CHANGE )
                     Description = Description + Pdescr->ParamDescEng;
                  else if(FileEventObj.EventHistoryObj.ParameterId == AUTHORITY_CHANGE)
                     Description =  Pdescr->ParamDescEng+" From "+PrepareDescription(FileEventObj.EventHistoryObj.ParameterId,EventId,Data_Old,true)+" To "+PrepareDescription(FileEventObj.EventHistoryObj.ParameterId,EventId,Data_New,true);
                  else
                     Description = Description+Pdescr->ParamDescEng+" From "+PrepareDescription(FileEventObj.EventHistoryObj.ParameterId,EventId,Data_Old,true)+" To "+ PrepareDescription(FileEventObj.EventHistoryObj.ParameterId,EventId,Data_New,true);
               }
            }
            else
            {
				if(NameDisplayPosition == BEFORE_EVENT_DESCRIPTION && (EventId == 100 ||EventId == 104||EventId == 106||EventId == 202))
						Description = GetNameFromID(FileEventObj.EventHistoryObj.ParameterId,true) + " " + Description +" From "+PrepareDescription(FileEventObj.EventHistoryObj.ParameterId,EventId,Data_Old,true)+" To "+PrepareDescription(FileEventObj.EventHistoryObj.ParameterId,EventId,Data_New,true);
				else if(NameDisplayPosition == DO_NOT_DISPLAY && (EventId == 105||EventId == 107||EventId == 108||EventId == 208||EventId == 301||EventId == 414||EventId == 415))
						Description = Description +" From "+PrepareDescription(FileEventObj.EventHistoryObj.ParameterId,EventId,Data_Old,true)+" To "+PrepareDescription(FileEventObj.EventHistoryObj.ParameterId,EventId,Data_New,true);
				else if(NameDisplayPosition == DO_NOT_DISPLAY && (EventId == 101 ||EventId == 113))
						Description = Description +"Preset#" +PrepareDescription(FileEventObj.EventHistoryObj.ParameterId,EventId,Data_Old,true) +  PrepareDescription(FileEventObj.EventHistoryObj.ParameterId,EventId,Data_New,true);
				else
						Description = Description + " "+PrepareDescription(FileEventObj.EventHistoryObj.ParameterId,EventId,Data_Old,true)+PrepareDescription(FileEventObj.EventHistoryObj.ParameterId,EventId,Data_New,true);
				
            }
            sprintf((char*)JsonEventObj.EventDescription,"%s",Description);
            JsonEventObj.TS.Century_Month = FileEventObj.EventHistoryObj.TS.Century_Month;
            JsonEventObj.TS.Day = FileEventObj.EventHistoryObj.TS.Day;
            JsonEventObj.TS.Hour = FileEventObj.EventHistoryObj.TS.Hour;
            JsonEventObj.TS.Minute = FileEventObj.EventHistoryObj.TS.Minute;
            JsonEventObj.TS.Second = FileEventObj.EventHistoryObj.TS.Second;
            JsonEventObj.TS.Weekdays = FileEventObj.EventHistoryObj.TS.Weekdays;
            JsonEventObj.TS.Years = FileEventObj.EventHistoryObj.TS.Years;
            GetRTCTime(&(JsonEventObj.TS), timeBuff);
            GetRTCDate(&(JsonEventObj.TS), timeBuff);
            memcpy(&EventDatatoSend[CountOfEventSent], &JsonEventObj, sizeof(JsonEventLog));

            CountOfEventSent++;  
            StartingPoint = (StartingPoint + 1) % MAX_ALLOWED_EVENT_LOG;
            if(StartingPoint == 0)
               f.Seek(StartingPoint*(LONGLONG)ObjectSize + HeaderSize,CFile::begin);//Seek again when wrapping around in file*/

         }
         TotalLen = CountOfEventSent * sizeof(JsonEventLog);
      }
      else
      {
         WeldDatatoSend = new char [MAX_WELDDATA_BUFFLEN];
         WeldDatatoSend[0] = 0;			
         f.SeekToBegin();
         ObjectSize =  sizeof(int) + sizeof(bool) + 3*sizeof(char)+ sizeof(CHistoryData);
         unsigned long UnitObjectSize = MAXPARAMVALUES*MAXPARAMUNITLENGTH*sizeof(TCHAR);
         unsigned long WeldHeaderSize = sizeof(UINT32) + sizeof(char) + sizeof(UINT32) + sizeof(char);
         unsigned long TotalValidHeaderSize = WeldHeaderSize + 2*UnitObjectSize + sizeof(char) ;
         CHistoryData object; 

         int  size= sizeof(CHistoryData);
         bool FirstObject = true;
         bool USBMetric;
         if(NoOfBytesRead!=f.GetLength())
         {	
            int ID;
            UINT32 TotalObjectCount,TotalHeaderCount;
            char Comma,NextComma;	
            if(FirstObject)
            {
               FirstObject = false;
               NoOfBytesRead+=f.Read(&TotalObjectCount,sizeof(UINT32));
               NoOfBytesRead+=f.Read(&NextComma,sizeof(char));
               NoOfBytesRead+=f.Read(&TotalHeaderCount,sizeof(UINT32));
               NoOfBytesRead+=f.Read(&NextComma,sizeof(char));
               NoOfBytesRead+=f.Read(&CWeldingHistory::ParameterUnitMetric[0][0],UnitObjectSize);
               NoOfBytesRead+=f.Read(&CWeldingHistory::ParameterUnitUSCS[0][0],UnitObjectSize);
               NoOfBytesRead+=f.Read(&NextComma,sizeof(char));

               f.Seek((StartingPoint)*(LONGLONG)ObjectSize + TotalValidHeaderSize,CFile::begin);
               //Go to the endof file
            }

            while((Count--) && (NoOfBytesRead!=f.GetLength()))
            {             
               AddSeparator(STR, SOH);
               NoOfBytesRead+=f.Read(&ID,sizeof(int));
               NoOfBytesRead+=f.Read(&Comma,sizeof(char));
               NoOfBytesRead+=f.Read(&USBMetric,sizeof(bool));

               NoOfBytesRead+=f.Read(&Comma,sizeof(char));
               NoOfBytesRead+=f.Read(&object,size);
               NoOfBytesRead+=f.Read(&Comma,sizeof(char));
               object.Units=USBMetric;
               object.UniqueId=ID;					
               
               for(int i = 0;i<MAXPARAMVALUES;i++)
               {
                  CString ParamValue  = object.USBAllParamValues[i];
                  if(ParamValue.Find(_T("---"))>=0)
                     ParamValue="n/a";
                  sprintf(STR+strlen(STR),"%s",ParamValue);
                  AddSeparator(STR + strlen(STR), STX);
               }
               sprintf(STR+strlen(STR),"%S",object.USBTimeStr);
               AddSeparator(STR + strlen(STR), STX);
               sprintf(STR+strlen(STR),"%S",object.USBDateStr);
               AddSeparator(STR + strlen(STR), STX);
               sprintf(STR+strlen(STR),"%S",object.USBMode_PresetString);
               AddSeparator(STR + strlen(STR), ETX);
               if(object.TextColour == Red)
               {
                  for(int k = 0;k<8;k++)
                  {
                     sprintf(STR+strlen(STR),"%d",object.AlarmString[k]);
                     AddSeparator(STR + strlen(STR), STX);
                  }
                  AddSeparator(STR + strlen(STR), BEL);                     
               }

               TempLen = strlen(STR);
               TotalLen += TempLen;
               sprintf(WeldDatatoSend + strlen(WeldDatatoSend),"%s",STR);
               CountOfWeldSent++;					
            }
         }
      }

      f.Close();     
   }
    return TotalLen;
}

/*
This function adds the Separator char and null to passed character array pointer
*/
void CConnection::AddSeparator(char * Str, int Separator)
{

   Str[0] = Separator;
   Str[1] = NULL;
}