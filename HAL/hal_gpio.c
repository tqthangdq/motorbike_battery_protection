#include "hal_gpio.h"

void HAL_GPIO_ConfDataRegister(HAL_GPIO_HandlerTypeDef		*hHAL_GPIO,
                               HAL_GPIO_PortStateTypeDef	eGPIO_PortState)
{
    switch (eGPIO_PortState) {
        case GPIO_DRIVE_LOW:
            *(hHAL_GPIO->u8GPIO_AddrReg + 0x01) &= ~(_BV(hHAL_GPIO->u8GPIO_PinNum));
            break;
        case GPIO_DRIVE_HIGH:
            *(hHAL_GPIO->u8GPIO_AddrReg + 0x01) |= _BV(hHAL_GPIO->u8GPIO_PinNum);
            break;
        case GPIO_DRIVE_TOGGLE:
            *(hHAL_GPIO->u8GPIO_AddrReg + 0x01) ^= _BV(hHAL_GPIO->u8GPIO_PinNum);
            break;
        default:
            break;
    }
}

void HAL_GPIO_ConfDirectionRegister(HAL_GPIO_HandlerTypeDef	*hHAL_GPIO,
                                    HAL_GPIO_DirectTypeDef	eGPIO_Direct)
{
    switch (eGPIO_Direct) {
        case GPIO_INPUT:
            *(hHAL_GPIO->u8GPIO_AddrReg) &= ~(_BV(hHAL_GPIO->u8GPIO_PinNum));
            break;
        case GPIO_OUTPUT:
            *(hHAL_GPIO->u8GPIO_AddrReg) |= _BV(hHAL_GPIO->u8GPIO_PinNum);
            break;
        default:
            break;
    }
}

HAL_GPIO_PinLevelTypeDef
HAL_GPIO_AccessPinAddress(HAL_GPIO_HandlerTypeDef *hHAL_GPIO)
{
    if (bit_is_clear(*(hHAL_GPIO->u8GPIO_AddrReg - 0x01), hHAL_GPIO->u8GPIO_PinNum)) {
        return GPIO_PIN_LOW;
    } else {
        return GPIO_PIN_HIGH;
    }
}
