#ifndef CPN_SCH_H_
#define CPN_SCH_H_

#include <stdint.h>
#include <stdlib.h>
#include "../DRV/drv_sch.h"

typedef struct CPN_SCH_HandlerStruct {
	DRV_SCH_HandlerTypeDef	hDRV_SCH;
	uint8_t					u8SCH_TotalTask;
	uint8_t					*u8SCH_RunTimeArray;
	uint8_t					*u8SCH_IntervalArray;
	DRV_SCH_StateTypeDef	*eSCH_TaskArray;
} CPN_SCH_HandlerTypeDef;

void CPN_SCH_Init(CPN_SCH_HandlerTypeDef *hCPN_SCH);

void CPN_SCH_Task(CPN_SCH_HandlerTypeDef *hCPN_SCH);

void CPN_SCH_Reset(CPN_SCH_HandlerTypeDef *hCPN_SCH);
#endif
