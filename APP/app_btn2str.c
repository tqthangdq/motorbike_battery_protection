#include "app_btn2str.h"

void APP_BTN2STR_Init(APP_BTN2STR_HandlerTypeDef	*hAPP_BTN2STR)
{
    hAPP_BTN2STR->eBTN2STR_State = APP_BTN2STR_STATE_INIT;
    hAPP_BTN2STR->u8BTN2STR_HoldCounter = 0;
    hAPP_BTN2STR->cBTN2STR_Buffer = (char *)malloc(APP_BTN2STR_BUFFER_SIZE*sizeof(char));
}

void APP_BTN2STR_Task(APP_BTN2STR_HandlerTypeDef	*hAPP_BTN2STR,
                      CPN_ADC_HandlerTypeDef		*hCPN_ADC,
                      CPN_BTN_HandlerTypeDef		*hCPN_BTN,
                      CPN_USART_HandlerTypeDef		*hCPN_USART)
{
    switch (hAPP_BTN2STR->eBTN2STR_State) {
        case APP_BTN2STR_STATE_INIT:
            hAPP_BTN2STR->eBTN2STR_State = APP_BTN2STR_STATE_UPDATE;
            break;
        case APP_BTN2STR_STATE_UPDATE:
            sprintf(hAPP_BTN2STR->cBTN2STR_Buffer, "%u", hCPN_ADC->sADC4.u16ADC_Sum);
            CPN_USART_Send(hCPN_USART, hAPP_BTN2STR->cBTN2STR_Buffer);
            hAPP_BTN2STR->u8BTN2STR_HoldCounter = 0;
            hAPP_BTN2STR->eBTN2STR_State = APP_BTN2STR_STATE_HOLD;
        case APP_BTN2STR_STATE_HOLD:
            hAPP_BTN2STR->u8BTN2STR_HoldCounter++;
            if (hAPP_BTN2STR->u8BTN2STR_HoldCounter == APP_BTN2STR_TIMEOUT) {
                hAPP_BTN2STR->eBTN2STR_State = APP_BTN2STR_STATE_UPDATE;
            }
            break;
        default:
            break;
    }
}
