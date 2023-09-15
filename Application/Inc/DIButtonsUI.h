#ifndef INC_DIBUTTONSUI_H_
#define INC_DIBUTTONSUI_H_

#include "portable.h"
#define WC_TO_SBC_OFFSET 10

struct __attribute__((__packed__)) ETHERNETOPTIONS
{
	BOOLEAN Host;
	BOOLEAN WebSrv;
	BOOLEAN Gateway;

};

struct __attribute__((__packed__)) RECORDOPTIONS
{
	BOOLEAN SysConfig;
	BOOLEAN WeldRes1;
	BOOLEAN WeldRes2;
	BOOLEAN Preset1;
	BOOLEAN Preset2;
};

extern ETHERNETOPTIONS EthernetOptions;
extern RECORDOPTIONS RecordOptions;

#endif /* INC_DIBUTTONSUI_H_ */
