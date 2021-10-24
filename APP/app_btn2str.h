#ifndef APP_BTN2STR_H_
#define APP_BTN2STR_H_

#include "../CPN/cpn_adc.h"
#include "../CPN/cpn_btn.h"
#include "../CPN/cpn_usart.h"

#ifndef APP_BTN2STR_TIMEOUT
#define APP_BTN2STR_TIMEOUT		2
#endif

#ifndef APP_BTN2STR_BUFFER_SIZE
#define APP_BTN2STR_BUFFER_SIZE	8
#endif

typedef enum {
    APP_BTN2STR_STATE_INIT = 0,
    APP_BTN2STR_STATE_WAIT,
    APP_BTN2STR_STATE_UPDATE,
	APP_BTN2STR_STATE_HOLD
} APP_BTN2STR_StateTypeDef;

typedef struct APP_BTN2STR_HandlerStruct {
    APP_BTN2STR_StateTypeDef	eBTN2STR_State;
	uint8_t						u8BTN2STR_HoldCounter;
	char						*cBTN2STR_Buffer;
} APP_BTN2STR_HandlerTypeDef;

void APP_BTN2STR_Init(APP_BTN2STR_HandlerTypeDef	*hAPP_BTN2STR);
void APP_BTN2STR_Task(APP_BTN2STR_HandlerTypeDef	*hAPP_BTN2STR,
                      CPN_ADC_HandlerTypeDef		*hCPN_ADC,
                      CPN_BTN_HandlerTypeDef		*hCPN_BTN,
                      CPN_USART_HandlerTypeDef		*hCPN_USART);

#endif