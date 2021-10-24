#ifndef SS_LED_H_
#define SS_LED_H_

#include "../DRV/drv_pin.h"

typedef struct CPN_LED_HandlerStruct {
	DRV_PIN_HandlerTypeDef		hLED_PD5;
	DRV_PIN_HandlerTypeDef		hLED_PD7;
	
} CPN_LED_HandlerTypeDef;

void CPN_LED_Init(CPN_LED_HandlerTypeDef *hCPN_LED);

void CPN_LED_TurnOnRelay (CPN_LED_HandlerTypeDef *hCPN_LED);
void CPN_LED_TurnOffRelay (CPN_LED_HandlerTypeDef *hCPN_LED);
void CPN_LED_BeepStart(CPN_LED_HandlerTypeDef *hCPN_LED);
void CPN_LED_BeepStop(CPN_LED_HandlerTypeDef *hCPN_LED);

#endif