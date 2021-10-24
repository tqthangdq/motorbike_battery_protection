#include "app.h"

static inline
void APP_TaskAttach(CPN_SCH_HandlerTypeDef *hCPN_SCH);

void APP_Init(APP_ADC2BEEP_HandlerTypeDef *hAPP_ADC2BEEP,
              APP_ADC2RELAY_HandlerTypeDef *hAPP_ADC2RELAY,
              APP_BTN2STR_HandlerTypeDef *hAPP_BTN2STR,
              APP_BTN2TM1637_HandlerTypeDef *hAPP_BTN2TM1637,
              APP_LED2BEEP_HandlerTypeDef *hAPP_LED2BEEP,
              CPN_ADC_HandlerTypeDef *hCPN_ADC,
              CPN_BTN_HandlerTypeDef *hCPN_BTN,
              CPN_LED_HandlerTypeDef *hCPN_LED,
              CPN_SCH_HandlerTypeDef *hCPN_SCH,
              CPN_TM1637_HandlerTypeDef *hCPN_TM1637,
              CPN_USART_HandlerTypeDef *hCPN_USART)
{
    hCPN_SCH->u8SCH_TotalTask = SYSTEM_TOTAL_TASK;

	APP_ADC2BEEP_Init(hAPP_ADC2BEEP);
    APP_ADC2RELAY_Init(hAPP_ADC2RELAY);
    APP_BTN2STR_Init(hAPP_BTN2STR);
    APP_BTN2TM1637_Init(hAPP_BTN2TM1637);
    APP_LED2BEEP_Init(hAPP_LED2BEEP);

    CPN_ADC_Init(hCPN_ADC);
    CPN_BTN_Init(hCPN_BTN);
    CPN_LED_Init(hCPN_LED);
    CPN_SCH_Init(hCPN_SCH);
    CPN_TM1637_Init(hCPN_TM1637);
    CPN_USART_Init(hCPN_USART);
    /************************************************************************/
    /*					STABILIZATION TIME                                  */
    /************************************************************************/
    APP_TaskAttach(hCPN_SCH);
	
	/* Avoid the first warning */
	hCPN_SCH->u8SCH_RunTimeArray[TASK_ADC2BEEP] += (100/SYSTEM_INTERVAL);
}

void APP_Loop(APP_ADC2BEEP_HandlerTypeDef *hAPP_ADC2BEEP,
              APP_ADC2RELAY_HandlerTypeDef *hAPP_ADC2RELAY,
              APP_BTN2STR_HandlerTypeDef *hAPP_BTN2STR,
              APP_BTN2TM1637_HandlerTypeDef *hAPP_BTN2TM1637,
              APP_LED2BEEP_HandlerTypeDef *hAPP_LED2BEEP,
              CPN_ADC_HandlerTypeDef *hCPN_ADC,
              CPN_BTN_HandlerTypeDef *hCPN_BTN,
              CPN_LED_HandlerTypeDef *hCPN_LED,
              CPN_SCH_HandlerTypeDef *hCPN_SCH,
              CPN_TM1637_HandlerTypeDef *hCPN_TM1637,
              CPN_USART_HandlerTypeDef *hCPN_USART)
{
    if (g_eSCH_SCHState == DRV_SCH_RUN) {
        CPN_SCH_Task(hCPN_SCH);
        if (hCPN_SCH->eSCH_TaskArray[TASK_BTN] == DRV_SCH_RUN) {
            CPN_BTN_Task(hCPN_BTN);
        }
        if (hCPN_SCH->eSCH_TaskArray[TASK_ADC2RELAY] == DRV_SCH_RUN) {
            APP_ADC2RELAY_Task(hAPP_ADC2RELAY, hAPP_LED2BEEP, hCPN_ADC, hCPN_LED);
        }
        if (hCPN_SCH->eSCH_TaskArray[TASK_BTN2STR] == DRV_SCH_RUN) {
            APP_BTN2STR_Task(hAPP_BTN2STR, hCPN_ADC, hCPN_BTN, hCPN_USART);
        }
        if (hCPN_SCH->eSCH_TaskArray[TASK_BTN2TM1637] == DRV_SCH_RUN) {
            APP_BTN2TM1637_Task(hAPP_BTN2TM1637, hCPN_ADC, hCPN_BTN, hCPN_TM1637);
        }
        if (hCPN_SCH->eSCH_TaskArray[TASK_USART] == DRV_SCH_RUN) {
            CPN_USART_Task(hCPN_USART);
        }
		if (hCPN_SCH->eSCH_TaskArray[TASK_ADC2BEEP] == DRV_SCH_RUN) {
			APP_ADC2BEEP_Task(hAPP_ADC2BEEP, hAPP_LED2BEEP, hCPN_ADC, hCPN_BTN);
		}
        if (hCPN_SCH->eSCH_TaskArray[TASK_LED2BEEP] == DRV_SCH_RUN) {
            APP_LED2BEEP_Task(hAPP_LED2BEEP, hCPN_LED);
        }
        if (hCPN_SCH->eSCH_TaskArray[TASK_ADC] == DRV_SCH_RUN) {
            CPN_ADC_Task(hCPN_ADC);
        }
        CPN_SCH_Reset(hCPN_SCH);
    }
}

/************************************************************************/
/*					INLINE FUNCTIONS                                    */
/************************************************************************/
static inline
void APP_TaskAttach(CPN_SCH_HandlerTypeDef *hCPN_SCH)
{
    uint8_t u8_TaskArray[SYSTEM_TOTAL_TASK] = {TASK_BTN_INTERVAL,
                                               TASK_ADC2RELAY_INTERVAL,
                                               TASK_BTN2STR_INTERVAL,
                                               TASK_BTN2TM1637_INTERVAL,
                                               TASK_USART_INTERVAL,
											   TASK_ADC2BEEP_INTERVAL,
                                               TASK_LED2BEEP_INTERVAL,
                                               TASK_ADC_INTERVAL
                                              };
    for (uint8_t i = 0; i < SYSTEM_TOTAL_TASK; i++) {
        hCPN_SCH->u8SCH_IntervalArray[i] = u8_TaskArray[i];
        hCPN_SCH->u8SCH_RunTimeArray[i] = (100/SYSTEM_INTERVAL); //100ms delay for stabilizations
    }
}