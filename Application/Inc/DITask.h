/*
 * DITask.h
 *
 *  Created on: Mar 14, 2020
 *      Author: rvite
 */

#ifndef INC_DITASK_H_
#define INC_DITASK_H_

#include "task.h"
#include "portable.h"
#include "DIComm2000Xc.h"
#include "DIComm.h"

class DITask : public Task
{
public:
	DIComm2000Xc *DIComPtr;

	DITask(SINT32);
	~DITask();

protected:
	void Run();
	void Tick();
};

#endif /* INC_DITASK_H_ */
