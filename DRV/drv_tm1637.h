#ifndef DRV_TM1637_H_
#define DRV_TM1637_H_

#ifndef F_CPU
#define F_CPU	16000000UL
#endif

#include <util/delay.h>
#include "../HAL/hal_gpio.h"

#define TM1637_QUARTER_CLOCK_PERIOD		10
#define TM1637_HALF_CLOCK_PERIOD		20

#define TM1637_CMD_SETUP				0b01000000
#define TM1637_CMD_WRITEDATA			0b11000000
#define TM1637_CMD_SHOWDATA				0b10001010
#define TM1637_CMD_OFFDATA				0b10000010

#define TM1637_SPAT_0					0b10111111
#define TM1637_SPAT_1					0b10000110
#define TM1637_SPAT_2					0b11011011
#define TM1637_SPAT_3					0b11001111
#define TM1637_SPAT_4					0b11100110
#define TM1637_SPAT_5					0b11101101
#define TM1637_SPAT_6					0b11111101
#define TM1637_SPAT_7					0b10000111
#define TM1637_SPAT_8					0b11111111
#define TM1637_SPAT_9					0b11101111

#define TM1637_SPAT_FULL				0b01111111
#define TM1637_SPAT_BLANK				0
#define TM1637_SPAT_H					0b01110110
#define TM1637_SPAT_I					0b00110000
#define TM1637_SPAT_MINUS				0b01000000

typedef struct DRV_TM1637_HandlerStruct {
	HAL_GPIO_HandlerTypeDef		hHAL_GPIO_CLK;
	HAL_GPIO_HandlerTypeDef		hHAL_GPIO_DIO;
	uint8_t						u8TM1637_Kilo;
	uint8_t						u8TM1637_Hecto;
	uint8_t						u8TM1637_Deka;
	uint8_t						u8TM1637_Base;
} DRV_TM1637_HandlerTypeDef;

void DRV_TM1637_Init(DRV_TM1637_HandlerTypeDef *hDRV_TM1637);
void DRV_TM1637_SendData(DRV_TM1637_HandlerTypeDef *hDRV_TM1637);
void DRV_TM1637_TurnOff(DRV_TM1637_HandlerTypeDef *hDRV_TM1637);
void DRV_TM1637_TurnOn(DRV_TM1637_HandlerTypeDef *hDRV_TM1637);

#endif