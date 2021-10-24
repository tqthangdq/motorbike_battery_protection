#include "app_btn2tm1637.h"

static inline
void APP_BTN2TM1637_BtnPressAndRelease(APP_BTN2TM1637_HandlerTypeDef	*hAPP_BTN2TM1637,
                                       CPN_BTN_HandlerTypeDef			*hCPN_BTN,
                                       CPN_TM1637_HandlerTypeDef		*hCPN_TM1637,
                                       APP_BTN2TM1637_StateTypeDef		eBTN2TM1637_State);

void APP_BTN2TM1637_Init(APP_BTN2TM1637_HandlerTypeDef *hAPP_BTN2TM1637)
{
    hAPP_BTN2TM1637->eBTN2TM1637_State = APP_BTN2TM1637_STATE_INIT;
    hAPP_BTN2TM1637->eBTN2TM1637_BtnReact = APP_BTN2TM1637_WAIT_PRESS;
    hAPP_BTN2TM1637->u8BTN2TM1637_TimeOut = 0;
	hAPP_BTN2TM1637->u16BTN2TM1637_Mapping = 0;
	hAPP_BTN2TM1637->cBTN2TM1637_Buffer = (char *)malloc(APP_BTN2TM1637_BUFFER_SIZE*sizeof(char));
}

void APP_BTN2TM1637_Task(APP_BTN2TM1637_HandlerTypeDef	*hAPP_BTN2TM1637,
                         CPN_ADC_HandlerTypeDef			*hCPN_ADC,
                         CPN_BTN_HandlerTypeDef			*hCPN_BTN,
                         CPN_TM1637_HandlerTypeDef		*hCPN_TM1637)
{
    switch (hAPP_BTN2TM1637->eBTN2TM1637_State) {
        case APP_BTN2TM1637_STATE_INIT:
            hAPP_BTN2TM1637->eBTN2TM1637_State = APP_BTN2TM1637_STATE_WAIT;
            break;
        case APP_BTN2TM1637_STATE_WAIT:
            APP_BTN2TM1637_BtnPressAndRelease(hAPP_BTN2TM1637, hCPN_BTN, hCPN_TM1637, APP_BTN2TM1637_STATE_UPDATE);
            break;
        case APP_BTN2TM1637_STATE_UPDATE:
			hAPP_BTN2TM1637->u16BTN2TM1637_Mapping = ((hCPN_ADC->sADC3.u16ADC_Average/10)*157)/10;
			sprintf(hAPP_BTN2TM1637->cBTN2TM1637_Buffer, "%u", hAPP_BTN2TM1637->u16BTN2TM1637_Mapping);
            CPN_TM1637_SendData(hCPN_TM1637, hAPP_BTN2TM1637->cBTN2TM1637_Buffer);
            hAPP_BTN2TM1637->eBTN2TM1637_State = APP_BTN2TM1637_STATE_HOLD;
            hAPP_BTN2TM1637->u8BTN2TM1637_TimeOut = 0;
            break;
        case APP_BTN2TM1637_STATE_HOLD:
            APP_BTN2TM1637_BtnPressAndRelease(hAPP_BTN2TM1637, hCPN_BTN, hCPN_TM1637, APP_BTN2TM1637_STATE_WAIT);
            hAPP_BTN2TM1637->u8BTN2TM1637_TimeOut++;
            if (hAPP_BTN2TM1637->u8BTN2TM1637_TimeOut == APP_BTN2TM1637_TIMEOUT) {
                hAPP_BTN2TM1637->eBTN2TM1637_State = APP_BTN2TM1637_STATE_UPDATE;
            }
            break;
        default:
            break;
    }
}

/************************************************************************/
/*					INLINE FUNCTIONS                                    */
/************************************************************************/
static inline
void APP_BTN2TM1637_BtnPressAndRelease(APP_BTN2TM1637_HandlerTypeDef	*hAPP_BTN2TM1637,
                                       CPN_BTN_HandlerTypeDef			*hCPN_BTN,
                                       CPN_TM1637_HandlerTypeDef		*hCPN_TM1637,
                                       APP_BTN2TM1637_StateTypeDef		eBTN2TM1637_State)
{
    if (hCPN_BTN->eCPN_State == CPN_BTN_STATE_PRESSED) {
        hAPP_BTN2TM1637->eBTN2TM1637_BtnReact = APP_BTN2TM1637_WAIT_RELEASE;
    } else if (hCPN_BTN->eCPN_State == CPN_BTN_STATE_RELEASED) {
        if (hAPP_BTN2TM1637->eBTN2TM1637_BtnReact == APP_BTN2TM1637_WAIT_RELEASE) {
            hAPP_BTN2TM1637->eBTN2TM1637_BtnReact = APP_BTN2TM1637_WAIT_PRESS;
            /* Only change state while the button is pressed and released */
            hAPP_BTN2TM1637->eBTN2TM1637_State = eBTN2TM1637_State;
            switch (eBTN2TM1637_State) {
                case APP_BTN2TM1637_STATE_WAIT:
                    CPN_TM1637_TurnOff(hCPN_TM1637);
                    break;
                case APP_BTN2TM1637_STATE_UPDATE:
                    CPN_TM1637_TurnOn(hCPN_TM1637);
                    break;
                default:
                    break;
            }
        }
    }
}