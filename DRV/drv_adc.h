#ifndef DRV_ADC_H_
#define DRV_ADC_H_

#include <stdint.h>
#include <avr/interrupt.h>
#include "../HAL/hal_adc.h"

typedef enum {
	ADC_DATA_AVAILABLE = 0,
	ADC_WAIT_NEXT_DATA
} DRV_ADC_ConvFlagTypeDef;

/************************************************************************/
/*                      Global Variable                                 */
/************************************************************************/
volatile DRV_ADC_ConvFlagTypeDef	g_eADC_ConvFlag;
volatile uint16_t					g_u16ADC_PreviousResult;

typedef struct DRV_ADC_HandlerStruct {
	HAL_ADC_HandlerTypeDef		hHAL_ADC;
} DRV_ADC_HandlerTypeDef;

void DRV_ADC_Init(DRV_ADC_HandlerTypeDef *hDRV_ADC);
void DRV_ADC_EnConf(DRV_ADC_HandlerTypeDef	*hDRV_ADC,
                    HAL_ADC_EnableTypeDef	eADC_En);
void DRV_ADC_StartConf(DRV_ADC_HandlerTypeDef	*hDRV_ADC,
                       HAL_ADC_StartConvTypeDef	eADC_Start);
void DRV_ADC_ChanSelConf(DRV_ADC_HandlerTypeDef		*hDRV_ADC,
                         HAL_ADC_ChannelSelTypeDef	eADC_ChanSel);


#endif