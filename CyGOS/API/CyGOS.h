// $Header:   D:/databases/VMdb/archives/Sunrise/Weld Controller/2000XWCProj/CyGOS/API/CyGOS.h_v   1.1.1.2   14 Apr 2014 07:46:58   rjamloki  $
//
// Copyright (c) Cyber Group, Inc 2007
// This program is the property of Cyber Group Inc
// Copying of this software is expressly forbidden, without the prior written
// consent of Cyber Group Inc
//
// This file is part of CyGOS-3.
//
// This file implements CyGOS user accessible API.

// TODO Add compression code.
// TODO I2C configuration manager.

#ifndef CYGOS_H_
#define CYGOS_H_

#include "ArchDefs.h"
#include "HttpServer.h"
#include "FileSystemManager.h"
#include "DebugNew.h"
//#include "RTOS.h"

class Task;
class BlockDevice;
class FileSystem;
class File;
class FileSystemManager;
class FileDecode;
extern char __TAR_START[];
extern char __TAR_SIZE[];
extern char __BOOTLOADER_SIZE[];
//extern int __FRAM_START;

typedef FileSystem * (*CreateFS)(BlockDevice * device, int type, int first,int length);
typedef void (*RegisterFS)(FileSystemManager * fsm, int prioMin, int prioMax);

struct DhcpServerConfiguration;

#define DEFINE_BOARD "SUNRISE"
// Syntax highlighter default settings. These defines are not used during
// compile process, but having them here helps the code analyzer to show them
// properly.
#ifndef DEFINE_BOARD
#define DEFINE_BOARD "<board>"
#endif
#ifndef DEFINE_CPU
#define DEFINE_CPU "<cpu>"
#endif
#ifndef DEFINE_ARCH
#define DEFINE_ARCH "<arch>"
#endif

typedef void (*SetLedsProc)(int slow, int fast);

/**
 * enum Priority: Task priority constants. There are N priorities, range is
 * 0...N-1. 0 is the highest priority, N-1 is the lowest. There is always a
 * task at priority N-1 that is ready to run.
 */
enum Priority
{
	/**
	 * prioTotal: Total different priorities. Current implementation uses
	 * 64 priorities.
	 */
	prioTotal = 64,
	/**
	 * prioLowest: Lowest available priority.
	 */
	prioLowest = prioTotal - 1,
	/**
	 * prioIdle: Idle task priority, same as the lowest.
	 */
	prioIdle = prioLowest,
	/**
	 * prioPrintf: Printf task priority, next to lowest.
	 */
	prioPrintf = prioLowest - 1,
};

/**
 * PrintStatusMode: RTOS::PrintStatus verbosity modes. Lower values print less.
 */
enum PrintStatusMode
{
	/** PrintTasks: Print only task names and states. */
	PrintTasks,
	/** PrintTasksWithStack: Task names, states and stack usage. */
	PrintTasksWithStack,
};

/*
 * NetworkConfiguration: Current Network Configuration *
 */
enum NetworkConfiguration
{
	configDhcpServer,
	configDhcpClient,
	configStatic,
	configBootP,
	configDefault,
};

typedef void (*BoardTestCallback)(void);
typedef void (*TaskIntLoadCallBack)(bool log);
typedef void (*LogCallback)(short eid, int data1, int data2, unsigned int data3, bool valid);
typedef void (*AppCrashCallBack)(void);
typedef void (*WatchDogCallBack)(void);
//System Events Starts from 1000
enum SystemEventID
{
	SYSTEM_EVENT_START = 1000,
	FAULT_ERROR,
	LEN_INVALID,
	CRLF_INVALID,
	CPU_RESTART,
	LINK_UP,
	LINK_DOWN,
	UPLOAD_ABORT,
	ASSERT_ERROR,
	CRASH_ERROR,
	WD_ERROR,
	STRLENGTH_ERROR,
	ALLOCATION_ERROR,
	EVENT_IPCONFIG_CHANGED,
	EVENT_NETIF,
	EVENT_TASKLOAD,
	EVENT_INTLOAD,
};

//An Application task which has to work as Task manager can use following CyGOS functions to implement task manager logic..



class CyGOS
{
public:
	static void Init();
	static void Start(int usec);
	static void Stop();
	static void CreateLedTasks(int slow, int fast, SetLedsProc slp);
	static void CreateTask(Task * task, int & priority);
	static void CreateSerialBootTask(int & priority);
	static void PrintStatus(PrintStatusMode mode);
	static void CreateTaskManager(int & priority, int stack,
			void(*TaskManCallback)());
	static const char * GetTaskName(int priority);
	static int GetTaskTime(int priority);
	static int GetIntrTime(int priority);
	static int GetTaskTimeHighest(int priority);
	static int GetIntrTimeHighest(int priority);
	static int GetIntCount(int priority);
	static int GetSystemTime(int time);
	static void CreateTcpipTasks(int & priority);
	static void AddTcpInterface(int intf, int & priority, unsigned char * macAddr = 0);
	static void SetEthernetLinkDebouncing(bool flag);
	static void SetupInterface(int intf, bool dhcpIP, bool autoIP);
	static void SetupAddress(int intf, uint32 address, uint32 netmask);
	static void CreateTftpClientTask(int intf, int & priority);
	static void CreateHttpServerTask(int intf, int serverPort, int & priority);
	static int TftpReceive(int intf, char * name, int * length, void * data);
	static void DelayMs(int ms);
	static int TftpReceive(int intf, char * name, int * length, void * data, ip_addr server_ip_addr);
	///////////////////////////////////////////////////////////////////////////
	static int TftpTransmit(int intf, char * name, int  length, void * data);
	static int TftpTransmit(int intf, char * name, int  length, void * data, ip_addr server_ip_addr);

/////////////////////////////////////////////////////////////////////////////////////////////////////////////

	static bool IsNetworkConfigured(int intf);
	static void CreateDhcpServerTask(int intf, DhcpServerConfiguration & cfg,
			int & priority);
	static void InitFileSystems(int & priority);
	static void CreateBlockDevice(BlockDevice * device, const char * letters,
			int & priority);
	static void CreateFileSystem(FileSystem * fs, int & priority);
	static int ReadSector(int drive, int sector, int count, void * buffer);
	static int WriteSector(int drive, int sector, int count, void * buffer);
	static int InitDriveImage(int drive, void * image, int length);
	static int RemoveDrive(int drive);
	//Nooor
	static void InstallTimer(int usInterval, void(*callback)(), int instance);
	static void StartTimer(int instance);
	static void StopTimer(int instance);
	//Ratnesh
	static void AddHttpGetHandler(int intf, int srvrPort, getHandler handler);
	static void AddHttpPostHandler(int intf, int srvrPort, postHandler handler);
	static void AddHttpFileUploadHandler(int intf, int srvrPort, uploadHandler handler);
	static void AddTickCallbackForWebSite(int intf, int srvrPort, TickCallback handler);
	static void AddJSONHandler(int Intf, int SrvrPort, jsonHandler handler);
	//file APIs
	static int FileOpen(const char * fileName, int mode, File ** f);
	static void FileClose(void * file);
	static int FileRead(void * file, void * buffer, int * length);
	static int FileLength(void * file);
	static int FileSeek(void * file, int offset, int mode);
	
	static void SetupHostName(int intf, char* HostName);
	static void CreateDNSServerTask(int intf, int & priority);

	static ip_addr GetIPAddress(int intf);
	static ip_addr GetSubnetMask(int intf);
	static ip_addr GetGatewayAddress(int intf);

	static char * GetIPAddressStr(int intf);
	static char * GetSubnetMaskStr(int intf);
	static char * GetGatewayAddressStr(int intf);
	static bool IsDhcpEnabled(int intf);
	static void SetGW(int intf, uint32 gateway);
	static unsigned char * GetMacAddress(int intf);
	static void Restart();
	static Ethernet * GetNetworkInterface(int intf);
	static NetworkConfiguration GetNetworkConfiguration(int intf);
	static void InitWatchDog(int Cwcr_CWT);
	static void EnableWatchDog();
	static void KickWatchDog();
	static void DisableWatchDog();
	static void RegisterBoardTestCallback(BoardTestCallback callback);
	static void DOBoardTest();
	static void RegisterSysLogCallback(LogCallback callback);
	static void WriteSystemEvent(int eid, int data1, int data2,unsigned int data3, bool valid);
	static char * GetSysEventStrigFromID(int eid);
	static void EnableDebug();
	static void DisableDebug();
	static bool EnableDebugFlag;
	static void RegisterTaskLoadLogCallback(TaskIntLoadCallBack callback);
	static void LogTaskLoad();
	static void RegisterAppCrashCallback(AppCrashCallBack callback);
	static void ApplicationCrashCallBack();
	static void RegisterWatchdogCallback(WatchDogCallBack WdCb);
	static void WatchDogCallback();
};

BlockDevice * CreateRamDisk();
BlockDevice * CreateFRAMDisk();
unsigned int ReadTarRegionFlash(int drive, unsigned char * tarStartAddress, int lengthImage);
void DecompressTarRegionFlash(int drive, unsigned char * tarStartAddress, int lengthImage);

BlockDevice * CreateSdCardSPI(int intf, int irqlevel, int irqprio, int csel);

void RegisterFatFS(int prioMin, int prioMax);
void RegisterTarFS(int prioMin, int prioMax);
void RegisterFRAMFS(int prioMin, int prioMax);

extern "C"
{
void ShowMemory();

int getcharWait(int timeout);
//void InitMemoryAllocation(int before, int after, int fill, int test);
void * MallocAlignedNoCache(size_t size, int align);
void * CallocAlignedNoCache(size_t number, size_t size, int align);
void FreeAlignedNoCache(void * ptr);
void * mallocNoInit(size_t size);
}
#endif
