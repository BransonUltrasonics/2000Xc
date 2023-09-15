/*
 * DIProtocol.cpp
 *
 *  Created on: Jan 26, 2020
 *      Author: rvite
 */
#include "DIProtocol.h"
//#include "DIProtocolInclude.h"

#include <stdlib.h>

/*****************************************************************************************************************/
/*****************************************************************************************************************/
/* DIProtocol()
 * Purpose: Constructor
 */
DIProtocol::DIProtocol() : DIProtocolInterface()
{	SINT16 i;
	union
	{	UINT8 Byte[WORD_SIZE];
		UINT16 Word;
	} LoadSize;

// Little-Big Endian Detection
	LoadSize.Word= 0x0001;
	if (LoadSize.Byte[MSB] == (UINT8)(LoadSize.Word & 0x00FF))
		IsEndian= TRUE;
	else
		IsEndian= FALSE;

	// Initializes the record pointers
//	for (i= 0; i < RECORD_NUM; i++)
//		RecordInfoPtr[i]= new RECORD_INFO[RECORD_SIZE];

//	DIProtocolPtr= this;
}

/*****************************************************************************************************************/
/* DIProtocol()
 * Purpose: Destructor
 */
DIProtocol::~DIProtocol()
{
	return;
}

/*****************************************************************************************************************/
SINT16 DIProtocol::InitProtocol(SINT8 Type, SINT16 Size, SINT8 Tag[11], SINT8 *ValueAddress, SINT16 Record, SINT16 Var)
{	SINT16 i;
	// Initializes the pointers to each record

	RecordInfoPtr[Record][Var].Type= Type;
	RecordInfoPtr[Record][Var].Size= Size;
	bufcpy(RecordInfoPtr[Record][Var].Tag, Tag, CONFIG_TAG_LEN);
	RecordInfoPtr[Record][Var].ValueAddress= ValueAddress;

	return 0;
}
#if 0
/*****************************************************************************************************************/
void DIProtocol::InitProtocol(RECORD_INFO MachineInfo[RECORD_NUM][RECORD_SIZE])
{	SINT16 i;
	// Initializes the pointers to each record
	for (i= 0; i < RECORD_NUM; i++)
		RecordInfoPtr[i]= &MachineInfo[i][0];
	return;
}
#endif
/*****************************************************************************************************************/
BOOLEAN DIProtocol::IsBigEndian()
{
	return IsEndian;
}
/*****************************************************************************************************************/
void DIProtocol::bufset(SINT8 *dst, SINT8 c, SINT16 len)
{
	while (len > 0)
	{	*dst++ = c;
		len--;
	}
	return;
}

/*****************************************************************************************************************/
void DIProtocol::bufcpy(SINT8 *dst, SINT8 *src, SINT16 len)
{
	while (len > 0)
	{	*dst++ = *src++;
		len--;
	}
	return;
}

/*****************************************************************************************************************/
void DIProtocol::bufcpyrev(SINT8 *dst, SINT8 *src, SINT16 len)
{
	SINT8 *srcRev = src+len-1;

	while (len > 0)
	{	*dst= *srcRev;
		dst++;
		srcRev--;
		len--;
	}
	return;
}

/*****************************************************************************************************/
void DIProtocol::SetPreambleHeader(SINT8 *BufferPtr, LOAD_TYPE LoadType, SINT16 LoadSize, SINT16 RecordID)
{
	// Fills Preamble
	bufset(BufferPtr, FILLBLANK, PREAMBLE_SIZE);
	BufferPtr+= PREAMBLE_SIZE;
	// Fills Header
	*(BufferPtr++)= LoadType;//Fills Load Type

	if (IsBigEndian())	// Fills Load Size, if needed exchanges bytes to send little endian
		bufcpyrev(BufferPtr, (SINT8 *)&LoadSize, CONFIG_SIZE_LEN);
	else
		bufcpy(BufferPtr, (SINT8 *)&LoadSize, CONFIG_SIZE_LEN);
	BufferPtr+= CONFIG_SIZE_LEN;

	*(BufferPtr++)= RecordID + 1;//Fills RecordID = 1,2,3 .. 10

	bufset(BufferPtr, FILLZERO, RESERVED_SIZE); //Fills FILLZERO

	return;
}

/*****************************************************************************************************/
SINT16 DIProtocol::GetAliveFrame(SINT8 *BufferPtr)
{
	if (BufferPtr == NULL)
		return -1;

	SetPreambleHeader(BufferPtr, LOAD_TYPE_KEEP_ALIVE, 0, -1);

	return PREAMBLE_SIZE + HEADER_SIZE;
}

/*****************************************************************************************************/
SINT16 DIProtocol::GetConfigFrame(SINT8 *BufferPtr, SINT16 RecordID)
{	SINT16 VarIndex, RecordIndex, RecordSize, LoadSize;
	RECORD_INFO *VarInfoPtr;

	if (BufferPtr == NULL)
		return -1;

	VarInfoPtr= RecordInfoPtr[RecordID];
	for (RecordIndex= 0; (VarInfoPtr->Type != TYPE_NONE) && (RecordIndex < RECORD_SIZE); RecordIndex++)
		VarInfoPtr++;
	RecordSize= RecordIndex;

	LoadSize= RecordSize*CONFIG_SIZE;

	SetPreambleHeader(BufferPtr, LOAD_TYPE_CONFIG, LoadSize, RecordID);
	BufferPtr+= PREAMBLE_SIZE + HEADER_SIZE;

	VarInfoPtr= RecordInfoPtr[RecordID];
	for (VarIndex= 0; VarIndex < RecordSize; VarIndex++)
	{	*BufferPtr= VarInfoPtr->Type;
		BufferPtr+= CONFIG_TYPE_LEN;

		if (IsBigEndian())	// Exchange size bytes
			bufcpyrev(BufferPtr, (SINT8 *)&VarInfoPtr->Size, CONFIG_SIZE_LEN);
		else
			bufcpy(BufferPtr, (SINT8 *)&VarInfoPtr->Size, CONFIG_SIZE_LEN);
		BufferPtr+= CONFIG_SIZE_LEN;

		bufcpy(BufferPtr, (SINT8 *)&VarInfoPtr->Tag, CONFIG_TAG_LEN);
		BufferPtr+= CONFIG_TAG_LEN;

		bufset(BufferPtr, 0, CONFIG_RES_LEN);
		BufferPtr+= CONFIG_RES_LEN;

		VarInfoPtr++;
	}

	bufset(BufferPtr, 0, (20-RecordSize)*CONFIG_SIZE);
	return 500;//PREAMBLE_SIZE + HEADER_SIZE + LoadSize;
}

#if 0/*****************************************************************************************************/
SINT16 DIProtocol::GetDataFrame(SINT8 *BufferPtr, SINT16 RecordID)
{	SINT16 VarIndex, RecordSize, LoadSize= 0;
	RECORD_INFO *VarInfoPtr;
	SINT16 DataSize;

	if (BufferPtr == NULL)
		return -1;

	VarInfoPtr= RecordInfoPtr[RecordID];
	for (RecordSize= 0; (VarInfoPtr->Type != TYPE_NONE) && (RecordSize < RECORD_SIZE); RecordSize++)
	{	LoadSize+= VarInfoPtr->Size;
		VarInfoPtr++;
	}
	SetPreambleHeader(BufferPtr, LOAD_TYPE_DATA, LoadSize, RecordID);
	BufferPtr+= PREAMBLE_SIZE + HEADER_SIZE;

	VarInfoPtr= RecordInfoPtr[RecordID];
	for (VarIndex= 0; VarIndex < RecordSize; VarIndex++)
	{	DataSize= VarInfoPtr->Size;
		if (IsBigEndian() &&
				((DataSize == WORD_SIZE) || (DataSize == DWORD_SIZE) || (DataSize == QWORD_SIZE))
			)
			bufcpyrev(BufferPtr, (SINT8 *)VarInfoPtr->ValueAddress, DataSize); // Exchange data bytes
		else
			bufcpy(BufferPtr, (SINT8 *)VarInfoPtr->ValueAddress, DataSize);
		BufferPtr+= DataSize;

		VarInfoPtr++;
	}

	return PREAMBLE_SIZE + HEADER_SIZE + LoadSize;
}
#endif

SINT16 DIProtocol::GetDataFrame(SINT8 *Buffer, SINT16 RecordID)
{	SINT16 VarIndex, LoadSize= 0;
	RECORD_INFO *VarInfoPtr;
	SINT16 DataSize;
	SINT8 *BufferPtr= Buffer + PREAMBLE_SIZE + HEADER_SIZE;

	if (Buffer == NULL)
		return -1;

	VarInfoPtr= RecordInfoPtr[RecordID];
	for (VarIndex= 0; (VarInfoPtr->Type != TYPE_NONE) && (VarIndex < RECORD_SIZE); VarIndex++)
	{	DataSize= VarInfoPtr->Size;
		LoadSize+= DataSize;
		if (IsBigEndian() &&
				((DataSize == WORD_SIZE) || (DataSize == DWORD_SIZE) || (DataSize == QWORD_SIZE))
			)
			bufcpyrev(BufferPtr, (SINT8 *)VarInfoPtr->ValueAddress, DataSize); // Exchange data bytes
		else
			bufcpy(BufferPtr, (SINT8 *)VarInfoPtr->ValueAddress, DataSize);

		BufferPtr+= DataSize;

		VarInfoPtr++;
	}

	SetPreambleHeader(Buffer, LOAD_TYPE_DATA, LoadSize, RecordID);

	return PREAMBLE_SIZE + HEADER_SIZE + LoadSize;
}
