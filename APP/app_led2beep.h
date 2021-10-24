#ifndef APP_LED2BEEP_H_
#define APP_LED2BEEP_H_

#include <stdint.h>
#include "../CPN/cpn_led.h"

#ifndef APP_LED2BEEP_TIMEOUT
#define APP_LED2BEEP_TIMEOUT	25
#endif

typedef enum {
    APP_LED2BEEP_DEACTIVE = 0,
    APP_LED2BEEP_ACTIVE,
    APP_LED2BEEP_HOLD
} APP_LED2BEEP_StateTypeDef;

typedef struct APP_LED2BEEP_HandlerStruct {
    APP_LED2BEEP_StateTypeDef	eLED2BEEP_State;
    uint8_t						u8LED2BEEP_Counter;
} APP_LED2BEEP_HandlerTypeDef;

void APP_LED2BEEP_Init(APP_LED2BEEP_HandlerTypeDef *hAPP_LED2BEEP);
void APP_LED2BEEP_Task(APP_LED2BEEP_HandlerTypeDef *hAPP_LED2BEEP,
                       CPN_LED_HandlerTypeDef *hCPN_LED);

#endif