#ifndef _HAL_GPIO_H
#define _HAL_GPIO_H

#include <avr/io.h>
#include <stdint.h>
#include <avr/sfr_defs.h>

typedef enum {
    GPIO_INPUT = 0,
    GPIO_OUTPUT
} HAL_GPIO_DirectTypeDef;

typedef enum {
    GPIO_DRIVE_HIGH = 0,
    GPIO_DRIVE_LOW,
	GPIO_DRIVE_TOGGLE
} HAL_GPIO_PortStateTypeDef;

typedef enum {
    GPIO_PIN_LOW = 0,
    GPIO_PIN_HIGH
} HAL_GPIO_PinLevelTypeDef;

typedef struct HAL_GPIO_HandlerStruct {
    volatile uint8_t*           u8GPIO_AddrReg;
    uint8_t                     u8GPIO_PinNum;
} HAL_GPIO_HandlerTypeDef;

void HAL_GPIO_ConfDataRegister(HAL_GPIO_HandlerTypeDef		*hHAL_GPIO,
                               HAL_GPIO_PortStateTypeDef	eGPIO_PortState);
void HAL_GPIO_ConfDirectionRegister(HAL_GPIO_HandlerTypeDef	*hHAL_GPIO,
                                    HAL_GPIO_DirectTypeDef	eGPIO_Direct);
HAL_GPIO_PinLevelTypeDef HAL_GPIO_AccessPinAddress(HAL_GPIO_HandlerTypeDef *hHAL_GPIO);

#endif
