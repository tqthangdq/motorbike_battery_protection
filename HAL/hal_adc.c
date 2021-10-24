/**
 * @file hal_adc.c
 * @brief Hardware Abstraction Layer for ADC - ATMEGE328P
 *
 * @author Thang Q. Tran - thang.tran@radsense.vn
 * @version   2.0
 * @date      Oct-2021
 * @copyright All rights reserved
 */

#include "hal_adc.h"

static inline void HAL_ADC_RefConf(HAL_ADC_HandlerTypeDef *hHAL_ADC);
static inline void HAL_ADC_LeftAdjConf(HAL_ADC_HandlerTypeDef *hHAL_ADC);
static inline void HAL_ADC_ModeConf(HAL_ADC_HandlerTypeDef *hHAL_ADC);
static inline void HAL_ADC_IntConf(HAL_ADC_HandlerTypeDef *hHAL_ADC);
static inline void HAL_ADC_PresConf(HAL_ADC_HandlerTypeDef *hHAL_ADC);
static inline void HAL_ADC_AutoScrConf(HAL_ADC_HandlerTypeDef *hHAL_ADC);

/**
 *	@brief <b> HAL ADC Methods</b>
 *	@details
 *	- Initialize the ADC Module
 *
 *	@param *hHAL_ADC - HAL ADC Handler Pointer
 */
void HAL_ADC_Init(HAL_ADC_HandlerTypeDef *hHAL_ADC)
{
	/* Select the voltage reference for the ADC */
	HAL_ADC_RefConf(hHAL_ADC);
	/* The presentation of the ADC conversion result in
	 * the ADC Data Register */
	HAL_ADC_LeftAdjConf(hHAL_ADC);
	/* Determine the division factor between the system
	 * clock frequency and the input clock to the ADC */
	HAL_ADC_PresConf(hHAL_ADC);
	/* Choice between three main modes: Single Mode,
	 * Free Mode, and Auto Trigger Mode */
	HAL_ADC_ModeConf(hHAL_ADC);
	/* Selects which source will trigger an ADC	conversion */
	HAL_ADC_AutoScrConf(hHAL_ADC);
	/* The ADC Conversion Complete Interrupt is activated or not */
	HAL_ADC_IntConf(hHAL_ADC);
	/* Selects which analog inputs are connected to the ADC */
	HAL_ADC_ChanSelConf(hHAL_ADC);
	/* Enable/Disable the ADC */
	HAL_ADC_EnConf(hHAL_ADC);
	/* Start the ADC conversion */
	HAL_ADC_StartConf(hHAL_ADC);
}

static inline void HAL_ADC_RefConf(HAL_ADC_HandlerTypeDef *hHAL_ADC)
{
	/************************************************************************/
	/*			ADMUX – ADC Multiplexer Selection Register                                                            */
	/************************************************************************/
	/* Bit 7:6 – REFS[1:0]: Reference Selection Bits */
	switch (hHAL_ADC->eADC_Ref) {
		case ADC_AREF_EXT: //00
			ADMUX &= ~((1 << REFS1) | (1 << REFS0));
			break;
		case ADC_AREF_AVCC: //01
			ADMUX &= ~(1 << REFS1);
			ADMUX |= (1 << REFS0);
			break;
		case ADC_AREF_INTERNAL: //10
			ADMUX |= (1 << REFS1);
			ADMUX &= ~(1 << REFS0);
			break;
		default:
			break;
	}
}

static inline void HAL_ADC_LeftAdjConf(HAL_ADC_HandlerTypeDef *hHAL_ADC)
{
	/************************************************************************/
	/*			ADMUX – ADC Multiplexer Selection Register                                                            */
	/************************************************************************/
	/* Bit 5 – ADLAR: ADC Left Adjust Result */
	switch (hHAL_ADC->eADC_LeftAdj) {
		case ADC_LEFT_ADJ_DIS: //0
			ADMUX &= ~(1 << ADLAR);
			break;
		case ADC_LEFT_ADJ_EN: //1
			ADMUX |= (1 << ADLAR);
			break;
		default:
			break;
	}
}

/**
 *	@brief <b> HAL ADC Methods</b>
 *	@details
 *	- Enable/Disable the ADC
 *
 *	@param *hHAL_ADC - HAL ADC Handler Pointer
 */
void HAL_ADC_ChanSelConf(HAL_ADC_HandlerTypeDef *hHAL_ADC)
{
	/************************************************************************/
	/*			ADMUX – ADC Multiplexer Selection Register                                                            */
	/************************************************************************/
	/* Bits 3:0 – MUX[3:0]: Analog Channel Selection Bits */
	switch (hHAL_ADC->eADC_ChanSel) {
		case ADC_ADC0: //0000
			ADMUX &= ~(1 << MUX0);
			ADMUX &= ~(1 << MUX1);
			ADMUX &= ~(1 << MUX2);
			ADMUX &= ~(1 << MUX3);
			break;
		case ADC_ADC1: //0001
			ADMUX |= (1 << MUX0);
			ADMUX &= ~(1 << MUX1);
			ADMUX &= ~(1 << MUX2);
			ADMUX &= ~(1 << MUX3);
			break;
		case ADC_ADC2: //0010
			ADMUX &= ~(1 << MUX0);
			ADMUX |= (1 << MUX1);
			ADMUX &= ~(1 << MUX2);
			ADMUX &= ~(1 << MUX3);
			break;
		case ADC_ADC3: //0011
			ADMUX |= (1 << MUX0);
			ADMUX |= (1 << MUX1);
			ADMUX &= ~(1 << MUX2);
			ADMUX &= ~(1 << MUX3);
			break;
		case ADC_ADC4: //0100
			ADMUX &= ~(1 << MUX0);
			ADMUX &= ~(1 << MUX1);
			ADMUX |= (1 << MUX2);
			ADMUX &= ~(1 << MUX3);
			break;
		case ADC_ADC5: //0101
			ADMUX |= (1 << MUX0);
			ADMUX &= ~(1 << MUX1);
			ADMUX |= (1 << MUX2);
			ADMUX &= ~(1 << MUX3);
			break;
		case ADC_ADC6: //0111
			ADMUX &= ~(1 << MUX0);
			ADMUX |= (1 << MUX1);
			ADMUX |= (1 << MUX2);
			ADMUX &= ~(1 << MUX3);
			break;
		case ADC_ADC7:
			ADMUX |= (1 << MUX0);
			ADMUX |= (1 << MUX1);
			ADMUX |= (1 << MUX2);
			ADMUX &= ~(1 << MUX3);
			break;
		case ADC_TEMP: //1000
			ADMUX &= ~(1 << MUX0);
			ADMUX &= ~(1 << MUX1);
			ADMUX &= ~(1 << MUX2);
			ADMUX |= (1 << MUX3);
			break;
		default:
			break;
	}
}

/**
 *	@brief <b> HAL ADC Methods</b>
 *	@details
 *	- Start the ADC conversion
 *
 *	@param *hHAL_ADC - HAL ADC Handler Pointer
 */
void HAL_ADC_EnConf(HAL_ADC_HandlerTypeDef *hHAL_ADC)
{
	/************************************************************************/
	/*			ADCSRA – ADC Control and Status Register A                                                            */
	/************************************************************************/
	/* Bit 7 – ADEN: ADC Enable */
	switch (hHAL_ADC->eADC_En) {
		case ADC_DIS: //0
			ADCSRA &= ~(1 << ADEN);
			break;
		case ADC_EN: //1
			ADCSRA |= (1 << ADEN);
			break;
		default:
			break;
	}
}

/**
 *	@brief <b> HAL ADC Methods</b>
 *	@details
 *	- Selects which analog inputs are connected to the ADC
 *
 *	@param *hHAL_ADC - HAL ADC Handler Pointer
 */
void HAL_ADC_StartConf(HAL_ADC_HandlerTypeDef *hHAL_ADC)
{
	/************************************************************************/
	/*			ADCSRA – ADC Control and Status Register A                                                            */
	/************************************************************************/
	/* Bit 6 – ADSC: ADC Start Conversion */
	switch (hHAL_ADC->eADC_Start) {
		case ADC_START_NONE: //0 No effect
			ADCSRA &= ~(1 << ADSC);
			break;
		case ADC_START_SINGLE: //1
			ADCSRA |= (1 << ADSC);
			break;
		case ADC_START_FREEMODE: //1
			ADCSRA |= (1 << ADSC);
			break;
		case ADC_START_AUTOMODE: //0 No effect
			ADCSRA &= ~(1 << ADSC);
			break;
		default:
			break;
	}
}

static inline void HAL_ADC_ModeConf(HAL_ADC_HandlerTypeDef *hHAL_ADC)
{
	/************************************************************************/
	/*			ADCSRA – ADC Control and Status Register A                                                            */
	/************************************************************************/
	/* Bit 5 – ADATE: ADC Auto Trigger Enable */
	switch (hHAL_ADC->eADC_Mode) {
		case ADC_SINGLE_MODE:
			ADCSRA &= ~(1 << ADATE);
			break;
		case ADC_FREE_MODE:
			ADCSRA |= (1 << ADATE);
			break;
		case ADC_AUTO_MODE:
			ADCSRA |= (1 << ADATE);
			/* Need more settings in ADCSRB */
			/* Call function HAL_ADC_AutoScrConf() */
			break;
		default:
			break;
	}
}

static inline void HAL_ADC_IntConf(HAL_ADC_HandlerTypeDef *hHAL_ADC)
{
	/************************************************************************/
	/*			ADCSRA – ADC Control and Status Register A                                                            */
	/************************************************************************/
	/* Bit 3 – ADIE: ADC Interrupt Enable */
	switch (hHAL_ADC->eADC_Int) {
		case ADC_INT_DIS:
			ADCSRA &= ~(1 << ADIE);
			break;
		case ADC_INT_EN:
			ADCSRA |= (1 << ADIE);
			break;
		default:
			break;
	}
}

static inline void HAL_ADC_PresConf(HAL_ADC_HandlerTypeDef *hHAL_ADC)
{
	/************************************************************************/
	/*			ADCSRA – ADC Control and Status Register A                                                            */
	/************************************************************************/
	/* Bits 2:0 – ADPS[2:0]: ADC Prescaler Select Bits */
	switch (hHAL_ADC->eADC_PresSel) {
		case ADC_PRES_DIV_2: //001
			ADCSRA |= (1 << ADPS0);
			ADCSRA &= ~(1 << ADPS1);
			ADCSRA &= ~(1 << ADPS2);
			break;
		case ADC_PRES_DIV_4: //010
			ADCSRA &= ~(1 << ADPS0);
			ADCSRA |= (1 << ADPS1);
			ADCSRA &= ~(1 << ADPS2);
			break;
		case ADC_PRES_DIV_8: //011
			ADCSRA |= (1 << ADPS0);
			ADCSRA |= (1 << ADPS1);
			ADCSRA &= ~(1 << ADPS2);
			break;
		case ADC_PRES_DIV_16: //100
			ADCSRA &= ~(1 << ADPS0);
			ADCSRA &= ~(1 << ADPS1);
			ADCSRA |= (1 << ADPS2);
			break;
		case ADC_PRES_DIV_32: //101
			ADCSRA |= (1 << ADPS0);
			ADCSRA &= ~(1 << ADPS1);
			ADCSRA |= (1 << ADPS2);
			break;
		case ADC_PRES_DIV_64: //110
			ADCSRA &= ~(1 << ADPS0);
			ADCSRA |= (1 << ADPS1);
			ADCSRA |= (1 << ADPS2);
			break;
		case ADC_PRES_DIV_128: //111
			ADCSRA |= (1 << ADPS0);
			ADCSRA |= (1 << ADPS1);
			ADCSRA |= (1 << ADPS2);
			break;
		default:
			break;
	}
}

static inline void HAL_ADC_AutoScrConf(HAL_ADC_HandlerTypeDef * hHAL_ADC)
{
	/************************************************************************/
	/*			ADCSRB – ADC Control and Status Register B                                                            */
	/************************************************************************/
	/* Bit 2:0 – ADTS[2:0]: ADC Auto Trigger Source */
	switch (hHAL_ADC->eADC_AutoScr) {
		case ADC_FREE_MODE_TRG: //000
			ADCSRB &= ~(1 << ADTS0);
			ADCSRB &= ~(1 << ADTS1);
			ADCSRB &= ~(1 << ADTS2);
			break;
		case ADC_ANALOG_COMP: //001
			ADCSRB |= (1 << ADTS0);
			ADCSRB &= ~(1 << ADTS1);
			ADCSRB &= ~(1 << ADTS2);
			break;
		case ADC_EXT_INT: //010
			ADCSRB &= ~(1 << ADTS0);
			ADCSRB |= (1 << ADTS1);
			ADCSRB &= ~(1 << ADTS2);
			break;
		case ADC_TIMER0_COMPA: //011
			ADCSRB |= (1 << ADTS0);
			ADCSRB |= (1 << ADTS1);
			ADCSRB &= ~(1 << ADTS2);
			break;
		case ADC_TIMER0_OVE: //100
			ADCSRB &= ~(1 << ADTS0);
			ADCSRB &= ~(1 << ADTS1);
			ADCSRB |= (1 << ADTS2);
			break;
		case ADC_TIMER1_COMPB: //101
			ADCSRB |= (1 << ADTS0);
			ADCSRB &= ~(1 << ADTS1);
			ADCSRB |= (1 << ADTS2);
			break;
		case ADC_TIMER1_OVE: //110
			ADCSRB &= ~(1 << ADTS0);
			ADCSRB |= (1 << ADTS1);
			ADCSRB |= (1 << ADTS2);
			break;
		case ADC_TIMER1_CAP: //111
			ADCSRB |= (1 << ADTS0);
			ADCSRB |= (1 << ADTS1);
			ADCSRB |= (1 << ADTS2);
			break;
		default:
			break;
	}
}
