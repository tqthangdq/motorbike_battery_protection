#ifndef APP_ADC2RELAY_H_
#define APP_ADC2RELAY_H_

#include <stdint.h>
#include "app_led2beep.h"
#include "../CPN/cpn_adc.h"
#include "../CPN/cpn_led.h"

#ifndef APP_ADC2RELAY_TIMEOUT
#define APP_ADC2RELAY_TIMEOUT	1000
#endif

#ifndef APP_ADC2RELAY_SENSITIVE
#define APP_ADC2RELAY_SENSITIVE	100
#endif

typedef enum {
    APP_ADC2RELAY_INIT = 0,
    APP_ADC2RELAY_RELAYOFF,
    APP_ADC2RELAY_HOLD,
    APP_ADC2RELAY_RELAYON
} APP_ADC2RELAY_StateTypeDef;

typedef struct APP_ADC2RELAY_HandlerStruct {
    APP_ADC2RELAY_StateTypeDef	eADC2RELAY__State;
    uint16_t					u16ADC2RELAY_Counter;
} APP_ADC2RELAY_HandlerTypeDef;

void APP_ADC2RELAY_Init(APP_ADC2RELAY_HandlerTypeDef *hAPP_ADC2RELAY);
void APP_ADC2RELAY_Task(APP_ADC2RELAY_HandlerTypeDef *hAPP_ADC2RELAY,
                        APP_LED2BEEP_HandlerTypeDef *hAPP_LED2BEEP,
                        CPN_ADC_HandlerTypeDef *hCPN_ADC,
                        CPN_LED_HandlerTypeDef *hCPN_LED);

#endif