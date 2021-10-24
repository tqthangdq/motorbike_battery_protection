#ifndef APP_ADC2BEEP_H_
#define APP_ADC2BEEP_H_

#include <stdint.h>
#include "../CPN/cpn_adc.h"
#include "../CPN/cpn_btn.h"
#include "app_led2beep.h"

#ifndef APP_ADC2BEEP_TIMEOUT
#define APP_ADC2BEEP_TIMEOUT	5
#endif

#ifndef APP_ADC2BEEP_REPEAT
#define APP_ADC2BEEP_REPEAT		5
#endif

#ifndef APP_ADC2BEEP_ADCLEVEL
#define APP_ADC2BEEP_ADCLEVEL	765 //((12V*1000)/157)*10)
#endif

typedef enum {
    APP_ADC2BEEP_STATE_INIT = 0,
    APP_ADC2BEEP_STATE_WAIT,
    APP_ADC2BEEP_STATE_ALARM,
    APP_ADC2BEEP_STATE_HOLD,
    APP_ADC2BEEP_STATE_DONTCARE
} APP_ADC2BEEP_StateTypeDef;

typedef struct APP_ADC2BEEP_HandlerStruct {
    APP_ADC2BEEP_StateTypeDef	eADC2BEEP_State;
    uint8_t						u8ADC2BEEP_Counter;
    uint8_t						u8ADC2BEEP_Repeat;
} APP_ADC2BEEP_HandlerTypeDef;

void APP_ADC2BEEP_Init(APP_ADC2BEEP_HandlerTypeDef	*hAPP_ADC2BEEP);
void APP_ADC2BEEP_Task(APP_ADC2BEEP_HandlerTypeDef	*hAPP_ADC2BEEP,
                       APP_LED2BEEP_HandlerTypeDef *hAPP_LED2BEEP,
                       CPN_ADC_HandlerTypeDef *hCPN_ADC,
                       CPN_BTN_HandlerTypeDef *hCPN_BTN);

#endif