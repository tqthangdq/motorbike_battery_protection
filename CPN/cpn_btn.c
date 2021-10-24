#include "cpn_btn.h"

void CPN_BTN_Init(CPN_BTN_HandlerTypeDef *hCPN_BTN)
{
    /************************************************************************/
    /*					INITIALIZE BTN PC0                                  */
    /************************************************************************/
    hCPN_BTN->hBTN_PC0.hHAL_GPIO.u8GPIO_AddrReg = &DDRD;
    hCPN_BTN->hBTN_PC0.hHAL_GPIO.u8GPIO_PinNum = 2;
    hCPN_BTN->hBTN_PC0.eDRV_Direct = GPIO_INPUT;
    hCPN_BTN->hBTN_PC0.eDRV_PortState = GPIO_DRIVE_HIGH;
    DRV_PIN_Init(&hCPN_BTN->hBTN_PC0);

    /* Initialize the State Machine */
    hCPN_BTN->eCPN_State = CPN_BTN_STATE_INIT;
}

void CPN_BTN_Task(CPN_BTN_HandlerTypeDef *hCPN_BTN)
{
    DRV_PIN_Get(&hCPN_BTN->hBTN_PC0);
    switch (hCPN_BTN->eCPN_State) {
        case CPN_BTN_STATE_INIT:
            hCPN_BTN->eCPN_State = CPN_BTN_STATE_DEBOUNCE;
            break;
        case CPN_BTN_STATE_RELEASED:
            if (hCPN_BTN->hBTN_PC0.eDRV_PinLevel == GPIO_PIN_LOW) {
                hCPN_BTN->eCPN_State = CPN_BTN_STATE_DEBOUNCE;
            }
            break;
        case CPN_BTN_STATE_DEBOUNCE:
            if (hCPN_BTN->hBTN_PC0.eDRV_PinLevel == GPIO_PIN_LOW) {
                hCPN_BTN->eCPN_State = CPN_BTN_STATE_PRESSED;
            } else {
                hCPN_BTN->eCPN_State = CPN_BTN_STATE_RELEASED;
            }
            break;
        case CPN_BTN_STATE_PRESSED:
            if (hCPN_BTN->hBTN_PC0.eDRV_PinLevel == GPIO_PIN_HIGH) {
                hCPN_BTN->eCPN_State = CPN_BTN_STATE_DEBOUNCE;
            }
            break;
        default:
            break;
    }
}