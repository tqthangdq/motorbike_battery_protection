/**
 * @file hal_timer0.c
 * @brief Hardware Abstraction Layer for TIMER0 - ATMEGE328P
 *
 * @author Thang Q. Tran - thang.tran@radsense.vn
 * @version   2.0
 * @date      Oct-2021
 * @copyright All rights reserved
 */

#include "hal_timer0.h"

static inline void HAL_TIMER0_ModeConfig(HAL_TIMER0_HandlerTypeDef *hHAL_TIMER0);
static inline void HAL_TIMER0_CompAConfig(HAL_TIMER0_HandlerTypeDef *hHAL_TIMER0);
static inline void HAL_TIMER0_CompBConfig(HAL_TIMER0_HandlerTypeDef *hHAL_TIMER0);
static inline void HAL_TIMER0_CpOutConfig(HAL_TIMER0_HandlerTypeDef *hHAL_TIMER0);
static inline void HAL_TIMER0_IntConfig(HAL_TIMER0_HandlerTypeDef *hHAL_TIMER0);
static inline void HAL_TIMER0_InitReg(HAL_TIMER0_HandlerTypeDef *hHAL_TIMER0);
static inline void HAL_TIMER0_ClockConfig(HAL_TIMER0_HandlerTypeDef *hHAL_TIMER0);

/**
 *	@brief <b> HAL TIMER0 Methods</b>
 *	@details
 *	- Initialize the TIMER0 Module
 *
 *	@param *hHAL_TIMER0 - HAL TIMER0 Handler Pointer
 */
void HAL_TIMER0_Init(HAL_TIMER0_HandlerTypeDef *hHAL_TIMER0)
{
	HAL_TIMER0_ModeConfig(hHAL_TIMER0);
	HAL_TIMER0_CompAConfig(hHAL_TIMER0);
	HAL_TIMER0_CompBConfig(hHAL_TIMER0);
	HAL_TIMER0_CpOutConfig(hHAL_TIMER0);
	HAL_TIMER0_IntConfig(hHAL_TIMER0);
	HAL_TIMER0_InitReg(hHAL_TIMER0);
	HAL_TIMER0_ClockConfig(hHAL_TIMER0);
}

static inline void HAL_TIMER0_ModeConfig(HAL_TIMER0_HandlerTypeDef *hHAL_TIMER0)
{
	/* ---------- TCCR0A - Timer/Counter Control Register A ----------------- */
	/* Bits 1:0 - WGM01:0: Waveform Generation Mode */
	/* ---------- TCCR0B - Timer/Counter Control Register B ----------------- */
	/* Bit 3 - WGM02: Waveform Generation Mode */
	switch (hHAL_TIMER0->eTIMER0_Mode) {
		case TIMER0_MODE_NORMAL: //000
			TCCR0A &= ~(_BV(WGM00) | _BV(WGM01));
			TCCR0B &= ~(_BV(WGM02));
			break;
		case TIMER0_MODE_CTC: //010
			TCCR0A &= ~(_BV(WGM00));
			TCCR0A |= _BV(WGM01);
			TCCR0B &= ~(_BV(WGM02));
			break;
		case TIMER0_MODE_FAST_PWM_TOP: //011
			TCCR0A |= _BV(WGM00);
			TCCR0A |= _BV(WGM01);
			TCCR0B &= ~(_BV(WGM02));
			break;
		case TIMER0_MODE_FAST_PWM_BOT: //111
			TCCR0A |= _BV(WGM00);
			TCCR0A |= _BV(WGM01);
			TCCR0B |= _BV(WGM02);
			break;
		case TIMER0_MODE_PHASE_PWM_TOP: //001
			TCCR0A |= _BV(WGM00);
			TCCR0A &= ~(_BV(WGM01));
			TCCR0B &= ~(_BV(WGM02));
			break;
		case TIMER0_MODE_PHASE_PWM_BOT: //101
			TCCR0A |= _BV(WGM00);
			TCCR0A &= ~(_BV(WGM01));
			TCCR0B |= _BV(WGM02);
			break;
		default:
			break;
	}
}

static inline void HAL_TIMER0_CompAConfig(HAL_TIMER0_HandlerTypeDef *hHAL_TIMER0)
{
	/* ---------- TCCR0A - Timer/Counter Control Register A ----------------- */
	/* Bits 7:6 - COM0A1:0: Compare Match Output A Mode */
	switch (hHAL_TIMER0->eTIMER0_CompA) {
		case TIMER0_COMPA_DIS: //00
			TCCR0A &= ~(_BV(COM0A0) | _BV(COM0A1));
			break;
		case TIMER0_COMPA_TOGGLE: //01
			TCCR0A |= _BV(COM0A0);
			TCCR0A &= ~(_BV(COM0A1));
			break;
		case TIMER0_COMPA_CLEAR:  //10
			TCCR0A &= ~(_BV(COM0A0));
			TCCR0A |= _BV(COM0A1);
			break;
		case TIMER0_COMPA_SET: //11
			TCCR0A |= _BV(COM0A0);
			TCCR0A |= _BV(COM0A1);
			break;
		default:
			break;
	}
}

static inline void HAL_TIMER0_CompBConfig(HAL_TIMER0_HandlerTypeDef *hHAL_TIMER0)
{
	/* ---------- TCCR0A - Timer/Counter Control Register A ----------------- */
	/* Bits 5:4 - COM0B1:0: Compare Match Output B Mode */
	switch (hHAL_TIMER0->eTIMER0_CompB) {
		case TIMER0_COMPB_DIS: //00
			TCCR0A &= ~(_BV(COM0B0) | _BV(COM0B1));
			break;
		case TIMER0_COMPB_TOGGLE: //01
			TCCR0A |= _BV(COM0B0);
			TCCR0A &= ~(_BV(COM0B1));
			break;
		case TIMER0_COMPB_CLEAR: //10
			TCCR0A &= ~(_BV(COM0B0));
			TCCR0A |= _BV(COM0B1);
			break;
		case TIMER0_COMPB_SET: //11
			TCCR0A |= _BV(COM0B0);
			TCCR0A |= _BV(COM0B1);
			break;
		default:
			break;
	}
}

static inline void HAL_TIMER0_CpOutConfig(HAL_TIMER0_HandlerTypeDef *hHAL_TIMER0)
{
	switch (hHAL_TIMER0->eTIMER0_CpOut) {
		case TIMER0_CPOUT_DIS:
			break;
		case TIMER0_CPOUT_COMPA:
			/* ---------- GPIO - PD6 OUTPUT ----------------------------------------- */
			DDRD |= _BV(PD6);
			break;
		case TIMER0_CPOUT_COMPB:
			/* ---------- GPIO - PD7 OUTPUT ----------------------------------------- */
			DDRD |= _BV(PD7);
			break;
		case TIMER0_CPOUT_COMPAB:
			/* ---------- GPIO - PD6 OUTPUT ----------------------------------------- */
			DDRD |= _BV(PD6);
			/* ---------- GPIO - PD7 OUTPUT ----------------------------------------- */
			DDRD |= _BV(PD7);
			break;
		default:
			break;
	}
}

static inline void HAL_TIMER0_IntConfig(HAL_TIMER0_HandlerTypeDef *hHAL_TIMER0)
{
	/* ---------- TIMSK0 - Timer/Counter Interrupt Mask Register ------------ */
	switch (hHAL_TIMER0->eTIMER0_Int) {
		case TIMER0_INT_OIE:
			/* Bit 0 - TOIE0: Timer/Counter0 Overflow Interrupt Enable */
			TIMSK0 |= _BV(TOIE0);
			break;
		case TIMER0_INT_OCIEA:
			/* Bit 1 - OCIE0A: Timer/Counter0 Output Compare Match A Interrupt Enable */
			TIMSK0 |= _BV(OCIE0A);
			break;
		case TIMER0_INT_OCIEB:
			/* Bit 2 - OCIE0B: Timer/Counter Output Compare Match B Interrupt Enable  */
			TIMSK0 |= _BV(OCIE0B);
			break;
		default:
			break;
	}
}

static inline void HAL_TIMER0_InitReg(HAL_TIMER0_HandlerTypeDef *hHAL_TIMER0)
{
	/* ---------- TCNT0 - Timer/Counter Register ---------------------------- */
	TCNT0 = (uint8_t) hHAL_TIMER0->u8TIMER0_TCNT0;
	/* ---------- OCR0A - Output Compare Register A ------------------------- */
	OCR0A = (uint8_t) hHAL_TIMER0->u8TIMER0_OCR0A;
	/* ---------- OCR0B - Output Compare Register B ------------------------- */
	OCR0B = (uint8_t) hHAL_TIMER0->u8TIMER0_OCR0B;

}

static inline void HAL_TIMER0_ClockConfig(HAL_TIMER0_HandlerTypeDef *hHAL_TIMER0)
{
	/* ---------- TCCR0B - Timer/Counter Control Register B ----------------- */
	/* Bits 2:0 - CS02:0: Clock Select */
	switch (hHAL_TIMER0->eTIMER0_Clock) {
		case TIMER0_CLOCK_NONE: //000
			TCCR0B &= ~(_BV(CS00) | _BV(CS01) | _BV(CS02));
			break;
		case TIMER0_CLOCK_DIV1: //001
			TCCR0B |= _BV(CS00);
			TCCR0B &= ~(_BV(CS01));
			TCCR0B &= ~(_BV(CS02));
			break;
		case TIMER0_CLOCK_DIV8: //010
			TCCR0B &= ~(_BV(CS00));
			TCCR0B |= _BV(CS01);
			TCCR0B &= ~(_BV(CS02));
			break;
		case TIMER0_CLOCK_DIV64: //011
			TCCR0B |= _BV(CS00);
			TCCR0B |= _BV(CS01);
			TCCR0B &= ~(_BV(CS02));
			break;
		case TIMER0_CLOCK_DIV256: //100
			TCCR0B &= ~(_BV(CS00));
			TCCR0B &= ~(_BV(CS01));
			TCCR0B |= _BV(CS02);
			break;
		case TIMER0_CLOCK_DIV1024: //101
			TCCR0B |= _BV(CS00);
			TCCR0B &= ~(_BV(CS01));
			TCCR0B |= _BV(CS02);
			break;
		case TIMER0_CLOCK_T0_FALL: //110
			TCCR0B &= ~(_BV(CS00));
			TCCR0B |= _BV(CS01);
			TCCR0B |= _BV(CS02);
			break;
		case TIMER0_CLOCK_T0_RISE: //111
			TCCR0B |= _BV(CS00);
			TCCR0B |= _BV(CS01);
			TCCR0B |= _BV(CS02);
			break;
		default:
			break;
	}
}