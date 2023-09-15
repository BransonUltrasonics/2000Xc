/* $Header:   D:/databases/VMdb/archives/Sunrise/SBC/UserID.h_v   1.13   26 May 2016 14:57:40   RJamloki  $ */
/*
$Log:   D:/databases/VMdb/archives/Sunrise/SBC/UserID.h_v  $
 * 
 *    Rev 1.13   26 May 2016 14:57:40   RJamloki
 * Added a login response EXECUTIVE_PASSWORD_CHANGE
 * 
 *    Rev 1.12   17 Nov 2015 16:53:42   RJamloki
 * Added an extra item for operation authority
 * “Reset Horn Clamp Alarm”
 * 
 *    Rev 1.11   11 Mar 2015 09:27:52   amaurya
 * PASSWORD_CANNOT_BE_SAME added to display error message if user enter same old and new password.
 * 
 *    Rev 1.10   10 Nov 2014 02:51:28   rjamloki
 * ALREADY_LOGGED_IN_THROUGH_WEBSERVICES member added to enum LOGIN_RESPONSE.
 * 
 *    Rev 1.9   25 Sep 2014 12:09:02   AnPawar
 * OpAuth and max wrong login attempts related changes
 * 
 *    Rev 1.8   18 Aug 2014 07:58:08   rjamloki
 * Removed user name from user id structure.
 * 
 *    Rev 1.7   09 Jul 2014 07:09:30   akaushal
 * Changed enum UserLvl
 * 
 *    Rev 1.6   09 Jun 2014 11:56:16   rjamloki
 * Unused defines removed.
 * 
 *    Rev 1.5   27 May 2014 06:44:26   amaurya
 * Updated Macro for User ID per UDP packet 
 * 
 *    Rev 1.4   07 May 2014 13:12:28   akaushal
 * Login information added
 * 
 *    Rev 1.3   21 Apr 2014 13:47:56   akaushal
 * Removed unused varaibles and function from UserID class. 
 * 
 *    Rev 1.2   28 Mar 2014 14:33:14   rjamloki
 * Removed old header comments and cleanup
 *
 *    Rev 1.1     26 Mar 2014 14:25:18 rjamloki  
 * added function declaration
 *
 *    Rev 1.0     05 Mar 2014 14:43:16 rjamloki      
 * Initial Revision.
*/

#if !defined(AFX_USERID_H__7BD87008_2610_4356_BD58_7FE321375B3C__INCLUDED_)
#define AFX_USERID_H__7BD87008_2610_4356_BD58_7FE321375B3C__INCLUDED_

#include "ScreenKeypad.h"


/* Bit definitions for Values in OpAuthority Enum*/
#define BIT0    0x1
#define BIT1    0x2
#define BIT2    0x4
#define BIT3    0x8
#define BIT4    0x10
#define BIT5    0x20
#define BIT6    0x40





#define DATAINONEPACKET 72
#define MAXSERIALNUMBER_LEN 13


class UserID  
{
public:
	CString UserName;
		CString UserId;
		CString Password;
		enum  UserLvl   UserLevel;
		enum  ActiveStatus  Status;
		//enum  OpAuth   OpAuth;
		UINT32  PassExpTime;
		int CurrentDataCount;
		CString Time_String;
		CString Date_String;
};

struct RTCTime
{
	UINT8 Second; //<seconds 00 to 59 coded in BCD>
	UINT8 Minute; //<minutes 00 to 59 coded in BCD>
	UINT8 Hour;	  //<hours 00 to 23 coded in BCD>
	UINT8 Day;	  //<days 01 to 31 coded in BCD>
	UINT8 Weekdays; //<weekdays 0 to 6 > Not in BCD
	UINT8 Century_Month; //<months 01 to 12 coded in BCD>,Month or century
	UINT8 Years; //<years 00 to 99 coded in BCD>
};

enum UserLvl { 
    USER_OPERATOR,
	USER_TECHNICIAN,
	USER_SUPERVISOR,
	USER_EXECUTIVE,
	USER_MAINTENANCE,
	USER_BRANSON,
	USER_NO_USER
};

enum ActiveStatus {
   Disabled = 0x00,
   Enabled,
};
enum OpAuth {
   ResetAlarm = BIT0,
   RunUnvalidatedPreset = BIT1,
   RecalPreset = BIT2,
   Calibratiion = BIT3,
   RstBatchCount = BIT4,
   RstHornClampAlarm = BIT5
};

enum 
{
	ACK = 0x06,
	NAK = 0x15
};

enum 
{
	ACCEPTED,
	INVALID_PASSWORD=11,
	PASSWORD_DOESNOTMATCH,
	INVALID_USERNAME,
	PASSWORD_CANNOT_BE_SAME,
};

enum LOGIN_RESPONSE
{
	CORRECT_NAME_PASSWORD = 1,
	WRONG_NAME_PASSWORD = 2,
	FIRST_TIME_LOGIN = 10,
	PASSWORD_EXPIRED = 11,
	LOW_AUTHORITY_EORROR = 12,
	MAX_WRONG_ATTEMPTS = 13,
	ALREADY_LOGGED_IN_THROUGH_WEBSERVICES = 14,
	EXECUTIVE_PASSWORD_CHANGE = 15 
};

#pragma pack(push, 1)
struct UserIDStruct {
   char  UserId[6];
   char  Password[11];
   enum	 UserLvl  UserLevel;
   enum  ActiveStatus  Status;
   UINT32  PassExpTime;
   UINT8 IsFirstTimeLogin;
   UINT8 UnSuccessFullAttempts;
   RTCTime CreateModifyTime;
};
#pragma pack(pop)
extern void GetRTCTime(RTCTime * CreateModifyTime,char * Buff);
extern void GetRTCDate(RTCTime * CreateModifyTime,char * Buff);
int unicode2UTF(int unicode,int *length);
int unicodeToUTF8(int unicode ,unsigned char *UTF8);

#endif // !defined(AFX_USERID_H__7BD87008_2610_4356_BD58_7FE321375B3C__INCLUDED_)
