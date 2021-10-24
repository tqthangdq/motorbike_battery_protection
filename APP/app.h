#ifndef APP_H_
#define APP_H_

#include "app_adc2beep.h"
#include "app_adc2relay.h"
#include "app_btn2str.h"
#include "app_btn2tm1637.h"
#include "app_led2beep.h"

#include "../CPN/cpn_adc.h"
#include "../CPN/cpn_btn.h"
#include "../CPN/cpn_led.h"
#include "../CPN/cpn_sch.h"
#include "../CPN/cpn_tm1637.h"
#include "../CPN/cpn_usart.h"

#define SYSTEM_TOTAL_TASK			8	//tasks

#define TASK_BTN					0
#define TASK_ADC2RELAY				1
#define TASK_BTN2STR				2
#define TASK_BTN2TM1637				3
#define TASK_USART					4
#define TASK_ADC2BEEP				5
#define TASK_LED2BEEP				6
#define TASK_ADC					7

/* THE INTERVAL VALUE MUST NOT EXCEED 2560ms */
#define SYSTEM_INTERVAL				10	//ms

#define TASK_BTN_INTERVAL			(10/SYSTEM_INTERVAL)
#define TASK_ADC2RELAY_INTERVAL		(10/SYSTEM_INTERVAL)
#define TASK_BTN2STR_INTERVAL		(50/SYSTEM_INTERVAL)
#define TASK_BTN2TM1637_INTERVAL	(50/SYSTEM_INTERVAL)
#define TASK_USART_INTERVAL			(10/SYSTEM_INTERVAL)
#define TASK_ADC2BEEP_INTERVAL		(100/SYSTEM_INTERVAL)
#define TASK_LED2BEEP_INTERVAL		(10/SYSTEM_INTERVAL)
#define TASK_ADC_INTERVAL			(10/SYSTEM_INTERVAL)

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
              CPN_USART_HandlerTypeDef *hCPN_USART);

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
              CPN_USART_HandlerTypeDef *hCPN_USART);
#endif