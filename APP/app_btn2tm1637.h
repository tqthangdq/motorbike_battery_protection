#ifndef BTN2TM1637_H_
#define BTN2TM1637_H_

#include <stdint.h>
#include "../CPN/cpn_tm1637.h"
#include "../CPN/cpn_btn.h"
#include "../CPN/cpn_adc.h"

#ifndef APP_BTN2TM1637_TIMEOUT
#define APP_BTN2TM1637_TIMEOUT	10
#endif

#ifndef APP_BTN2TM1637_BUFFER_SIZE
#define APP_BTN2TM1637_BUFFER_SIZE	8
#endif

typedef enum {
    APP_BTN2TM1637_STATE_INIT = 0,
    APP_BTN2TM1637_STATE_WAIT,
    APP_BTN2TM1637_STATE_UPDATE,
    APP_BTN2TM1637_STATE_HOLD
} APP_BTN2TM1637_StateTypeDef;

typedef enum {
    APP_BTN2TM1637_WAIT_RELEASE = 0,
    APP_BTN2TM1637_WAIT_PRESS
} APP_BTN2TM1637_BntReactTypeDef;

typedef struct APP_BTN2TM1637_HandlerStruct {
    APP_BTN2TM1637_StateTypeDef		eBTN2TM1637_State;
    APP_BTN2TM1637_BntReactTypeDef	eBTN2TM1637_BtnReact;
    uint8_t							u8BTN2TM1637_TimeOut;
	uint16_t						u16BTN2TM1637_Mapping;
	char							*cBTN2TM1637_Buffer;
} APP_BTN2TM1637_HandlerTypeDef;

void APP_BTN2TM1637_Init(APP_BTN2TM1637_HandlerTypeDef	*hAPP_BTN2TM1637);
void APP_BTN2TM1637_Task(APP_BTN2TM1637_HandlerTypeDef	*hAPP_BTN2TM1637,
                         CPN_ADC_HandlerTypeDef			*hCPN_ADC,
                         CPN_BTN_HandlerTypeDef			*hCPN_BTN,
                         CPN_TM1637_HandlerTypeDef		*hCPN_TM1637);

#endif