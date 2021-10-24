#ifndef DRV_PIN_H_
#define DRV_PIN_H_

#include "../HAL/hal_gpio.h"

typedef struct DRV_PIN_HandlerStruct {
    HAL_GPIO_HandlerTypeDef			hHAL_GPIO;
    HAL_GPIO_DirectTypeDef			eDRV_Direct;
    HAL_GPIO_PortStateTypeDef		eDRV_PortState;
    HAL_GPIO_PinLevelTypeDef		eDRV_PinLevel;
} DRV_PIN_HandlerTypeDef;

void DRV_PIN_Init(DRV_PIN_HandlerTypeDef *hDRV_PIN);

void DRV_PIN_Set(DRV_PIN_HandlerTypeDef *hDRV_PIN);

void DRV_PIN_Clear(DRV_PIN_HandlerTypeDef *hDRV_PIN);

void DRV_PIN_Toggle(DRV_PIN_HandlerTypeDef *hDRV_PIN);

void DRV_PIN_Get(DRV_PIN_HandlerTypeDef *hDRV_PIN);


#endif