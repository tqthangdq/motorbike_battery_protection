#include "drv_pin.h"

void DRV_PIN_Init(DRV_PIN_HandlerTypeDef *hDRV_PIN)
{
    HAL_GPIO_ConfDirectionRegister(&hDRV_PIN->hHAL_GPIO, hDRV_PIN->eDRV_Direct);
    HAL_GPIO_ConfDataRegister(&hDRV_PIN->hHAL_GPIO, hDRV_PIN->eDRV_PortState);
}

void DRV_PIN_Set(DRV_PIN_HandlerTypeDef *hDRV_PIN)
{
    hDRV_PIN->eDRV_PortState = GPIO_DRIVE_HIGH;
    HAL_GPIO_ConfDataRegister(&hDRV_PIN->hHAL_GPIO, hDRV_PIN->eDRV_PortState);
}

void DRV_PIN_Clear(DRV_PIN_HandlerTypeDef *hDRV_PIN)
{
    hDRV_PIN->eDRV_PortState = GPIO_DRIVE_LOW;
    HAL_GPIO_ConfDataRegister(&hDRV_PIN->hHAL_GPIO, hDRV_PIN->eDRV_PortState);
}

void DRV_PIN_Toggle(DRV_PIN_HandlerTypeDef *hDRV_PIN)
{
	hDRV_PIN->eDRV_PortState = GPIO_DRIVE_TOGGLE;
	HAL_GPIO_ConfDataRegister(&hDRV_PIN->hHAL_GPIO, hDRV_PIN->eDRV_PortState);
}

void DRV_PIN_Get(DRV_PIN_HandlerTypeDef *hDRV_PIN)
{
	hDRV_PIN->eDRV_PinLevel = HAL_GPIO_AccessPinAddress(&hDRV_PIN->hHAL_GPIO);
}