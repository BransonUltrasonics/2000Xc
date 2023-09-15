// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/CyGOS/MultiBoot/SerialBootTask.h_v   1.2   14 Apr 2014 07:20:14   rjamloki  $
//
// Copyright (c) Cyber Group, Inc 2007
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3 MultiBoot loader.
//
// This module implements the serial port boot loader task.

#ifndef SERIALBOOTTASK_H_
#define SERIALBOOTTASK_H_

#include "Task.h"
#include "Flash.h"
#include "LinkedList.h"

class SerialBootTask: public Task
{
public:
	SerialBootTask();
	static unsigned short * FlashAddress(unsigned short * ramAddress);
protected:
	virtual void Run();
	void Tick();
	void Init(void * romBase);
	void SerialDownload(bool toFlash);
	void TftpDownload(int intf, bool app);
	void TftpDownloadVersioned(int intf, bool app);
	void ProgramFlash(int intf, bool app, int version = 0);
	bool SerialReceiveHexRecord(unsigned char * buf);
	void BurnImageToFlash();
	void MoveImageToSdram();
	void IdentifyFlash();
	void PrintData();
	void PrintPrompts();
	void EnterSerialNumber();
	void EnterMacAddress(unsigned char * macAddress);
	void EnterTftpServerAddr(unsigned char * TftpAddr);
	bool CheckPrompts(int ch);
	static void ExecuteFlash();
	static void EraseCallback(int offset, int length);
	static void ProgramCallback(int offset, int length);
	static unsigned int HexToInt(char * & ptr, int length);
	PtrList<Flash> list;
	Flash * flash;
	static unsigned char * bootImageBuffer;
	static unsigned int bootImageLength;
	static unsigned int bootImageFlash;
};

#endif
