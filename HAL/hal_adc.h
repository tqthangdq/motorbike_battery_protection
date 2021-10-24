/**
 * @file hal_adc.c
 * @brief Hardware Abstraction Layer for ADC - ATMEGE328P
 *
 * @author Thang Q. Tran - thang.tran@radsense.vn
 * @version   2.0
 * @date      Oct-2021
 * @copyright All rights reserved
 */

#ifndef HAL_ADC_H_
#define HAL_ADC_H_

#include <avr/io.h>

typedef enum {
	ADC_AREF_EXT = 0,
	ADC_AREF_AVCC,
	ADC_AREF_INTERNAL
} HAL_ADC_RefConfTypeDef;

typedef enum {
	ADC_LEFT_ADJ_DIS = 0,
	ADC_LEFT_ADJ_EN
} HAL_ADC_LeftAdjTypeDef;

typedef enum {
	ADC_ADC0 = 0,
	ADC_ADC1,
	ADC_ADC2,
	ADC_ADC3,
	ADC_ADC4,
	ADC_ADC5,
	ADC_ADC6,
	ADC_ADC7,
	ADC_TEMP
} HAL_ADC_ChannelSelTypeDef;

typedef enum {
	ADC_DIS = 0,
	ADC_EN
} HAL_ADC_EnableTypeDef;

typedef enum {
	ADC_SINGLE_MODE = 0,
	ADC_FREE_MODE,
	ADC_AUTO_MODE
} HAL_ADC_ModeTypeDef;

typedef enum {
	ADC_INT_DIS = 0,
	ADC_INT_EN,
} HAL_ADC_InterruptTypeDef;

typedef enum {
	ADC_PRES_DIV_2 = 0,
	ADC_PRES_DIV_4,
	ADC_PRES_DIV_8,
	ADC_PRES_DIV_16,
	ADC_PRES_DIV_32,
	ADC_PRES_DIV_64,
	ADC_PRES_DIV_128
} HAL_ADC_PrescalerTypeDef;

typedef enum {
	ADC_FREE_MODE_TRG = 0,
	ADC_ANALOG_COMP,
	ADC_EXT_INT,
	ADC_TIMER0_COMPA,
	ADC_TIMER0_OVE,
	ADC_TIMER1_COMPB,
	ADC_TIMER1_OVE,
	ADC_TIMER1_CAP
} HAL_ADC_AutoSrcTypeDef;

typedef enum {
	ADC_START_NONE = 0,
	ADC_START_SINGLE,
	ADC_START_FREEMODE,
	ADC_START_AUTOMODE
} HAL_ADC_StartConvTypeDef;

/**
 *  @brief <b>HAL ADC Attributes</b>
 *	@details
 *	- ADC Configurations
 *
 *  @param eADC_Ref - Select the voltage reference for the ADC
 *	@param eADC_LeftAdj - The presentation of the ADC conversion result in
 *	the ADC Data Register
 *	@param eADC_ChanSel - Selects which analog inputs are connected to the ADC
 *	@param eADC_En - Enable/Disable the ADC
 *	@param eADC_Mode - Choice between three main modes: Single Mode,
 *  Free Mode, and Auto Trigger Mode
 *	@param eADC_Int - The ADC Conversion Complete Interrupt is activated or not
 *	@param eADC_PresSel - Determine the division factor between the system
 *	clock frequency and the input clock to the ADC
 *	@param eADC_AutoScr - Selects which source will trigger an ADC conversion
 *	@param eADC_Start - Start the ADC conversion
 *
 */
typedef struct HAL_ADC_HandlerStruct {
	HAL_ADC_RefConfTypeDef		eADC_Ref;
	HAL_ADC_LeftAdjTypeDef		eADC_LeftAdj;
	HAL_ADC_ChannelSelTypeDef	eADC_ChanSel;
	HAL_ADC_EnableTypeDef		eADC_En;
	HAL_ADC_ModeTypeDef			eADC_Mode;
	HAL_ADC_InterruptTypeDef	eADC_Int;
	HAL_ADC_PrescalerTypeDef	eADC_PresSel;
	HAL_ADC_AutoSrcTypeDef		eADC_AutoScr;
	HAL_ADC_StartConvTypeDef	eADC_Start;
} HAL_ADC_HandlerTypeDef;

/**
 *	@brief <b> HAL ADC Methods</b>
 *	@details
 *	- Initialize the ADC Module
 *
 *	@param *hHAL_ADC - HAL ADC Handler Pointer
 */
void HAL_ADC_Init(HAL_ADC_HandlerTypeDef *hHAL_ADC);

/**
 *	@brief <b> HAL ADC Methods</b>
 *	@details
 *	- Enable/Disable the ADC
 *
 *	@param *hHAL_ADC - HAL ADC Handler Pointer
 */
void HAL_ADC_EnConf(HAL_ADC_HandlerTypeDef *hHAL_ADC);

/**
 *	@brief <b> HAL ADC Methods</b>
 *	@details
 *	- Start the ADC conversion
 *
 *	@param *hHAL_ADC - HAL ADC Handler Pointer
 */
void HAL_ADC_StartConf(HAL_ADC_HandlerTypeDef *hHAL_ADC);

/**
 *	@brief <b> HAL ADC Methods</b>
 *	@details
 *	- Selects which analog inputs are connected to the ADC
 *
 *	@param *hHAL_ADC - HAL ADC Handler Pointer
 */
void HAL_ADC_ChanSelConf(HAL_ADC_HandlerTypeDef *hHAL_ADC);

#endif /* HAL_ADC_H_ */