#include "DRV_sch.h"

void DRV_SCH_Init(DRV_SCH_HandlerTypeDef *hDRV_SCH)
{
	HAL_TIMER0_Init(&hDRV_SCH->hHAL_TIMER0);
	g_u8SCH_TickCounter = 0;
	g_eSCH_SCHState = DRV_SCH_IDLE;
}

ISR(TIMER0_COMPA_vect)
{
	g_u8SCH_TickCounter++;
	g_eSCH_SCHState = DRV_SCH_RUN;
}