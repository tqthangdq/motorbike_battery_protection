#ifndef CPN_ADC_H_
#define CPN_ADC_H_

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include "../DRV/drv_adc.h"

#ifndef CPN_ADC_ARRAY_SIZE
/* Maximum is 256 */
#define CPN_ADC_ARRAY_SIZE		16
#endif

#ifndef CPN_ADC_ARRAY_MASK
/* Maximum is 0xFF */
#define CPN_ADC_ARRAY_MASK		0x0F
#endif

typedef enum {
    CPN_ADC_STATE_INIT = 0,
    CPN_ADC_STATE_ADC3,
    CPN_ADC_STATE_ADC4
} CPN_ADC_StateTypeDef;

typedef struct CPN_ADC_ChannelStruct {
    uint16_t					*u16ADC_Queue;
    uint8_t						u8ADC_Index;
    uint16_t					u16ADC_Sum;
	uint16_t					u16ADC_Average;
} CPN_ADC_ChannelTypeDef;

typedef struct CPN_ADC_HandlerStruct {
    DRV_ADC_HandlerTypeDef		hDRV_ADC;
    CPN_ADC_ChannelTypeDef		sADC3;
    CPN_ADC_ChannelTypeDef		sADC4;
	CPN_ADC_StateTypeDef		eADC_State;
} CPN_ADC_HandlerTypeDef;

void CPN_ADC_Init(CPN_ADC_HandlerTypeDef *hCPN_ADC);
void CPN_ADC_Task(CPN_ADC_HandlerTypeDef *hCPN_ADC);
#endif /* CPN_ADC_H_ */