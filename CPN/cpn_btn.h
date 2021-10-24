#ifndef CPN_BTN_H_
#define CPN_BTN_H_

#include "../DRV/drv_pin.h"

typedef enum {
	CPN_BTN_STATE_INIT = 0,
	CPN_BTN_STATE_RELEASED,
	CPN_BTN_STATE_PRESSED,
	CPN_BTN_STATE_DEBOUNCE
} CPN_BTN_StateTypeDef;

typedef struct CPN_BTN_HandlerStruct {
	DRV_PIN_HandlerTypeDef		hBTN_PC0;
	CPN_BTN_StateTypeDef		eCPN_State;
} CPN_BTN_HandlerTypeDef;

void CPN_BTN_Init(CPN_BTN_HandlerTypeDef *hCPN_BTN);
void CPN_BTN_Task(CPN_BTN_HandlerTypeDef *hCPN_BTN);

#endif