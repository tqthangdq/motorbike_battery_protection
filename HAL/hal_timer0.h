/**
 * @file hal_timer0.h
 * @brief Hardware Abstraction Layer for TIMER0 - ATMEGE328P
 *
 * @author Thang Q. Tran - thang.tran@radsense.vn
 * @version   2.0
 * @date      Oct-2021
 * @copyright All rights reserved
 */

#ifndef HAL_TIMER0_H_
#define HAL_TIMER0_H_

#include <avr/io.h>
#include <stdint.h>
#include <avr/sfr_defs.h>

typedef enum {
	TIMER0_MODE_NORMAL = 0,
	TIMER0_MODE_CTC,
	TIMER0_MODE_FAST_PWM_TOP,
	TIMER0_MODE_FAST_PWM_BOT,
	TIMER0_MODE_PHASE_PWM_TOP,
	TIMER0_MODE_PHASE_PWM_BOT
} HAL_TIMER0_ModeTypeDef;

typedef enum {
	TIMER0_COMPA_DIS = 0,
	TIMER0_COMPA_TOGGLE,
	TIMER0_COMPA_CLEAR,
	TIMER0_COMPA_SET
} HAL_TIMER0_CompATypeDef;

typedef enum {
	TIMER0_COMPB_DIS = 0,
	TIMER0_COMPB_TOGGLE,
	TIMER0_COMPB_CLEAR,
	TIMER0_COMPB_SET
} HAL_TIMER0_CompBTypeDef;

typedef enum {
	TIMER0_CPOUT_DIS = 0,
	TIMER0_CPOUT_COMPA,
	TIMER0_CPOUT_COMPB,
	TIMER0_CPOUT_COMPAB
} HAL_TIMER0_CpOutTypeDef;

typedef enum {
	TIMER0_INT_OIE = 0,
	TIMER0_INT_OCIEA,
	TIMER0_INT_OCIEB
} HAL_TIMER0_IntTypeDef;

typedef enum {
	TIMER0_CLOCK_NONE = 0,
	TIMER0_CLOCK_DIV1,
	TIMER0_CLOCK_DIV8,
	TIMER0_CLOCK_DIV64,
	TIMER0_CLOCK_DIV256,
	TIMER0_CLOCK_DIV1024,
	TIMER0_CLOCK_T0_FALL,
	TIMER0_CLOCK_T0_RISE
} HAL_TIMER0_ClockTypeDef;

/**
 *  @brief <b>HAL TIMER0 Attributes</b>
 *	@details
 *	- TIMER0 Configurations
 *
 *  @param eTIMER0_Mode - see ”Modes of Operation” on page 107
 *	@param eTIMER0_Clock - select the clock source to be used by the Timer/Counter (USER INPUT)
 *	@param eTIMER0_Comp - control the Output Compare pin (OC0A) behavior
 *	@param eTIMER0_Int - enable the interrupt for the Timer/Counter
 *	@param u8TIMER0_TCNT0 - initial value for TCNT0
 *	@param u8TIMER0_OCR0A - capture value for OCR0A (USER INPUT)
 *	@param u8TIMER0_OCR0B - capture value for OCR0B
 */
typedef struct HAL_TIMER0_HandlerStruct {
	HAL_TIMER0_ModeTypeDef	eTIMER0_Mode;
	HAL_TIMER0_ClockTypeDef	eTIMER0_Clock;
	HAL_TIMER0_CompATypeDef	eTIMER0_CompA;
	HAL_TIMER0_CompBTypeDef	eTIMER0_CompB;
	HAL_TIMER0_IntTypeDef	eTIMER0_Int;
	HAL_TIMER0_CpOutTypeDef	eTIMER0_CpOut;
	uint8_t					u8TIMER0_TCNT0;
	uint8_t					u8TIMER0_OCR0A;
	uint8_t					u8TIMER0_OCR0B;
} HAL_TIMER0_HandlerTypeDef;

/**
 *	@brief <b> HAL TIMER0 Methods</b>
 *	@details
 *	- Initialize the TIMER0 Module
 *
 *	@param *hHAL_TIMER0 - HAL TIMER0 Handler Pointer
 */
void HAL_TIMER0_Init(HAL_TIMER0_HandlerTypeDef *hHAL_TIMER0);

#endif /* HAL_TIMER0_H_ */