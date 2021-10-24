#include "cpn_led.h"

void CPN_LED_Init(CPN_LED_HandlerTypeDef *hCPN_LED)
{
    /************************************************************************/
    /*						INITIALIZE LED PD5                              */
    /************************************************************************/
    hCPN_LED->hLED_PD5.hHAL_GPIO.u8GPIO_AddrReg = &DDRD;
    hCPN_LED->hLED_PD5.hHAL_GPIO.u8GPIO_PinNum = 5;
    hCPN_LED->hLED_PD5.eDRV_Direct = GPIO_OUTPUT;
    hCPN_LED->hLED_PD5.eDRV_PortState = GPIO_DRIVE_LOW;
    DRV_PIN_Init(&hCPN_LED->hLED_PD5);
    /************************************************************************/
    /*						INITIALIZE LED PD7                              */
    /************************************************************************/
	hCPN_LED->hLED_PD7.hHAL_GPIO.u8GPIO_AddrReg = &DDRD;
	hCPN_LED->hLED_PD7.hHAL_GPIO.u8GPIO_PinNum = 7;
	hCPN_LED->hLED_PD7.eDRV_Direct = GPIO_OUTPUT;
	hCPN_LED->hLED_PD7.eDRV_PortState = GPIO_DRIVE_HIGH;
	DRV_PIN_Init(&hCPN_LED->hLED_PD7);
}

void CPN_LED_TurnOnRelay(CPN_LED_HandlerTypeDef *hCPN_LED)
{
	DRV_PIN_Set(&hCPN_LED->hLED_PD5);
}

void CPN_LED_TurnOffRelay(CPN_LED_HandlerTypeDef *hCPN_LED)
{
	DRV_PIN_Clear(&hCPN_LED->hLED_PD5);
}

void CPN_LED_BeepStart(CPN_LED_HandlerTypeDef *hCPN_LED)
{
	DRV_PIN_Clear(&hCPN_LED->hLED_PD7);
}

void CPN_LED_BeepStop(CPN_LED_HandlerTypeDef *hCPN_LED)
{
	DRV_PIN_Set(&hCPN_LED->hLED_PD7);
}