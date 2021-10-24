#include <avr/io.h>
#include "APP/app.h"

/************************************************************************/
/*					GLOBAL VARIABLES                                    */
/************************************************************************/
APP_ADC2BEEP_HandlerTypeDef		hMX_ADC2BEEP;
APP_ADC2RELAY_HandlerTypeDef	hMX_ADC2RELAY;
APP_BTN2STR_HandlerTypeDef		hMX_BTN2SRT;
APP_BTN2TM1637_HandlerTypeDef	hMX_BTN2TM1637;
APP_LED2BEEP_HandlerTypeDef		hMX_LED2BEEP;

CPN_ADC_HandlerTypeDef			hMX_ADC;
CPN_BTN_HandlerTypeDef			hMX_BTN;
CPN_LED_HandlerTypeDef			hMX_LED;
CPN_SCH_HandlerTypeDef			hMX_SCH;
CPN_TM1637_HandlerTypeDef		hMX_TM1637;
CPN_USART_HandlerTypeDef		hMX_USART;


int main(void)
{
    cli();
    APP_Init(&hMX_ADC2BEEP,
             &hMX_ADC2RELAY,
             &hMX_BTN2SRT,
             &hMX_BTN2TM1637,
             &hMX_LED2BEEP,
             &hMX_ADC,
             &hMX_BTN,
             &hMX_LED,
             &hMX_SCH,
             &hMX_TM1637,
             &hMX_USART);
    sei();
    while (1) {
        APP_Loop(&hMX_ADC2BEEP,
                 &hMX_ADC2RELAY,
                 &hMX_BTN2SRT,
                 &hMX_BTN2TM1637,
                 &hMX_LED2BEEP,
                 &hMX_ADC,
                 &hMX_BTN,
                 &hMX_LED,
                 &hMX_SCH,
                 &hMX_TM1637,
                 &hMX_USART);
    }
}
