/* $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/iotest332.h_v   1.6   18 Aug 2014 01:50:32   rjamloki  $ */
/*************************                         **************************/
/*--------------------------- MODULE DESCRIPTION ---------------------------*/
/*                                                                          */
/*                                                                          */
/*   Module name:   On board Diagnostics                                    */
/*                                                                          */
/*   Filename:      iotest332.h                                             */
/*                                                                          */
/*                                                                          */
/*                                                                          */
/*------------------------------ REVISIONS ---------------------------------*/
/*****************************************************************************
$Log:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/2000XWC/Inc/iotest332.h_v  $
 * 
 *    Rev 1.6   18 Aug 2014 01:50:32   rjamloki
 * Cleaned up for Sunrise
*/ 

/*----------------------------- DESCRIPTION --------------------------------*/




/*---------------------------- INCLUDE FILES -------------------------------*/  



/*------------------------- Function Prototypes ----------------------------*/  

void DiagnosticInput(UINT8 ByteReceived, BOOLEAN EchoChar);
void DiagnosticsCmd(void);
void Read32(void);                   
void Read16(void);
void Read8(void);
void MyReadNVR(void);
void EraseNVR(void);
void TestFram(void);
void TurnOnBeep(void);
void TurnOffBeep(void);
void WritePrinterData(void);
void WritePrinterControl(void);
void WriteBargraph(void);
void WritePortA(void);
void WritePortB(void);
void WritePortC(void);
void ReadPortA(void);
void ReadPortB(void);
void ReadPortC(void);
void ReadKeypad(void);
void DiagFreqOffset(void);
void DiagAmplitude(void);
void DiagDigTune(void);
void EraseVFScreen(void);
void WriteLeds(void);
void ReadTPU(void);
void WriteTPU(void);
void DiagReady(void);
void ShutOffFT(void);
void RestoreUserIO(void);
void RestoreUserIO(void);
void DisableBeepers(void);
void EnableBeepers(void);
void SetTime(void);
void SetDate(void);
void DumpCalibrationData(void);
void DumpAllCalibrationData(void);
void ReadMemory(void);
void WriteMemory(void);
void StartDUPS(void);
void CheckDUPS(void);
UINT32 Numin(UINT16, STR Bufferpointer[]);
void CheckIOTest(void);
void DisplayHelp(void);



/*-------------------------------- DEFINES ---------------------------------*/


