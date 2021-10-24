#include "app_adc2beep.h"

void APP_ADC2BEEP_Init(APP_ADC2BEEP_HandlerTypeDef	*hAPP_ADC2BEEP)
{
    hAPP_ADC2BEEP->eADC2BEEP_State = APP_ADC2BEEP_STATE_INIT;
    hAPP_ADC2BEEP->u8ADC2BEEP_Counter = 0;
    hAPP_ADC2BEEP->u8ADC2BEEP_Repeat = 0;
}

void APP_ADC2BEEP_Task(APP_ADC2BEEP_HandlerTypeDef	*hAPP_ADC2BEEP,
                       APP_LED2BEEP_HandlerTypeDef *hAPP_LED2BEEP,
                       CPN_ADC_HandlerTypeDef *hCPN_ADC,
					   CPN_BTN_HandlerTypeDef *hCPN_BTN)
{
    switch (hAPP_ADC2BEEP->eADC2BEEP_State) {
        case APP_ADC2BEEP_STATE_INIT:
            hAPP_ADC2BEEP->eADC2BEEP_State = APP_ADC2BEEP_STATE_WAIT;
            break;
        case APP_ADC2BEEP_STATE_WAIT:
            if (hCPN_ADC->sADC3.u16ADC_Average < APP_ADC2BEEP_ADCLEVEL) {
                hAPP_ADC2BEEP->eADC2BEEP_State = APP_ADC2BEEP_STATE_ALARM;
            }
            break;
        case APP_ADC2BEEP_STATE_ALARM:
            hAPP_LED2BEEP->eLED2BEEP_State = APP_LED2BEEP_ACTIVE;
            hAPP_ADC2BEEP->eADC2BEEP_State = APP_ADC2BEEP_STATE_HOLD;
            break;
        case APP_ADC2BEEP_STATE_HOLD:
            hAPP_ADC2BEEP->u8ADC2BEEP_Counter++;
            if (hAPP_ADC2BEEP->u8ADC2BEEP_Counter > APP_ADC2BEEP_TIMEOUT) {
                hAPP_ADC2BEEP->u8ADC2BEEP_Counter = 0;
                hAPP_ADC2BEEP->u8ADC2BEEP_Repeat++;
                if (hAPP_ADC2BEEP->u8ADC2BEEP_Repeat > APP_ADC2BEEP_REPEAT) {
                    hAPP_ADC2BEEP->u8ADC2BEEP_Repeat = 0;
                    hAPP_ADC2BEEP->eADC2BEEP_State = APP_ADC2BEEP_STATE_WAIT;
                } else {
                    hAPP_ADC2BEEP->eADC2BEEP_State = APP_ADC2BEEP_STATE_ALARM;
                }
            }
			if (hCPN_BTN->eCPN_State == CPN_BTN_STATE_PRESSED)
			{
				hAPP_ADC2BEEP->eADC2BEEP_State = APP_ADC2BEEP_STATE_DONTCARE;
			}
            break;
        case APP_ADC2BEEP_STATE_DONTCARE:
            /* In this state forever until reset the application */
            break;
        default:
            break;
    }
}