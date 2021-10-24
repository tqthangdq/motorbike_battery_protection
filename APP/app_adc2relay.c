#include "app_adc2relay.h"

void APP_ADC2RELAY_Init(APP_ADC2RELAY_HandlerTypeDef *hAPP_ADC2RELAY)
{
    hAPP_ADC2RELAY->eADC2RELAY__State = APP_ADC2RELAY_INIT;
    hAPP_ADC2RELAY->u16ADC2RELAY_Counter = 0;
}

void APP_ADC2RELAY_Task(APP_ADC2RELAY_HandlerTypeDef *hAPP_ADC2RELAY,
                        APP_LED2BEEP_HandlerTypeDef *hAPP_LED2BEEP,
                        CPN_ADC_HandlerTypeDef *hCPN_ADC,
                        CPN_LED_HandlerTypeDef *hCPN_LED)
{
    switch (hAPP_ADC2RELAY->eADC2RELAY__State) {
        case APP_ADC2RELAY_INIT:
            hAPP_ADC2RELAY->eADC2RELAY__State = APP_ADC2RELAY_RELAYOFF;
            break;
        case APP_ADC2RELAY_RELAYOFF:
            if (hCPN_ADC->sADC4.u16ADC_Sum < APP_ADC2RELAY_SENSITIVE) {
                hAPP_ADC2RELAY->eADC2RELAY__State = APP_ADC2RELAY_HOLD;
                hAPP_ADC2RELAY->u16ADC2RELAY_Counter = 0;
            }
            break;
        case APP_ADC2RELAY_HOLD:
            hAPP_ADC2RELAY->u16ADC2RELAY_Counter++;
            if (hCPN_ADC->sADC4.u16ADC_Sum >= APP_ADC2RELAY_SENSITIVE) {
                hAPP_ADC2RELAY->eADC2RELAY__State = APP_ADC2RELAY_RELAYOFF;
            }
            if (hAPP_ADC2RELAY->u16ADC2RELAY_Counter > APP_ADC2RELAY_TIMEOUT) {
                CPN_LED_TurnOnRelay(hCPN_LED);
				hAPP_LED2BEEP->eLED2BEEP_State = APP_LED2BEEP_ACTIVE;
                hAPP_ADC2RELAY->eADC2RELAY__State = APP_ADC2RELAY_RELAYON;
            }
            break;
        case APP_ADC2RELAY_RELAYON:
            if (hCPN_ADC->sADC4.u16ADC_Sum >= APP_ADC2RELAY_SENSITIVE) {
                CPN_LED_TurnOffRelay(hCPN_LED);
				hAPP_LED2BEEP->eLED2BEEP_State = APP_LED2BEEP_ACTIVE;
                hAPP_ADC2RELAY->eADC2RELAY__State = APP_ADC2RELAY_RELAYOFF;
            }
            break;
        default:
            break;
    }
}