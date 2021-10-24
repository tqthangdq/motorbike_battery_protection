#ifndef DRV_SCH_H_
#define DRV_SCH_H_

#include "../HAL/hal_timer0.h"
#include <avr/interrupt.h>

typedef enum {
    DRV_SCH_IDLE = 0,
    DRV_SCH_RUN
} DRV_SCH_StateTypeDef;
/************************************************************************/
/*                      Global Variable                                 */
/************************************************************************/
volatile DRV_SCH_StateTypeDef	g_eSCH_SCHState;
volatile uint8_t				g_u8SCH_TickCounter;

typedef struct DRV_SCH_HandlerStruct {
    HAL_TIMER0_HandlerTypeDef	hHAL_TIMER0;
} DRV_SCH_HandlerTypeDef;

void DRV_SCH_Init(DRV_SCH_HandlerTypeDef *hDRV_SCH);

#endif