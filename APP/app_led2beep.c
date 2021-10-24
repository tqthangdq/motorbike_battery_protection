#include "app_led2beep.h"

void APP_LED2BEEP_Init(APP_LED2BEEP_HandlerTypeDef *hAPP_LED2BEEP)
{
    hAPP_LED2BEEP->eLED2BEEP_State = APP_LED2BEEP_DEACTIVE;
	hAPP_LED2BEEP->u8LED2BEEP_Counter = 0;
}
void APP_LED2BEEP_Task(APP_LED2BEEP_HandlerTypeDef *hAPP_LED2BEEP,
                       CPN_LED_HandlerTypeDef *hCPN_LED)
{
    switch(hAPP_LED2BEEP->eLED2BEEP_State) {
        case APP_LED2BEEP_DEACTIVE:
            break;
        case APP_LED2BEEP_ACTIVE:
			CPN_LED_BeepStart(hCPN_LED);
			hAPP_LED2BEEP->eLED2BEEP_State = APP_LED2BEEP_HOLD;
			hAPP_LED2BEEP->u8LED2BEEP_Counter = 0;
            break;
        case APP_LED2BEEP_HOLD:
			hAPP_LED2BEEP->u8LED2BEEP_Counter++;
			if (hAPP_LED2BEEP->u8LED2BEEP_Counter >= APP_LED2BEEP_TIMEOUT)
			{
				CPN_LED_BeepStop(hCPN_LED);
				hAPP_LED2BEEP->eLED2BEEP_State = APP_LED2BEEP_DEACTIVE;
			}
            break;
        default:
            break;
    }
}