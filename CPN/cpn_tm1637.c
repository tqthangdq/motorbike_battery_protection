#include "cpn_tm1637.h"

static inline
uint8_t CPN_TM1637_FindPattern(char chr);

void CPN_TM1637_Init(CPN_TM1637_HandlerTypeDef *hCPN_TM1637)
{
    /************************************************************************/
    /*				INITIALIZE TM1637 CLK                                   */
    /************************************************************************/
    hCPN_TM1637->hDRV_TM1637.hHAL_GPIO_CLK.u8GPIO_AddrReg = &DDRD;
    hCPN_TM1637->hDRV_TM1637.hHAL_GPIO_CLK.u8GPIO_PinNum = 4;
    /************************************************************************/
    /*				INITIALIZE TM1637 DIO                                   */
    /************************************************************************/
    hCPN_TM1637->hDRV_TM1637.hHAL_GPIO_DIO.u8GPIO_AddrReg = &DDRD;
    hCPN_TM1637->hDRV_TM1637.hHAL_GPIO_DIO.u8GPIO_PinNum = 3;
    DRV_TM1637_Init(&(hCPN_TM1637->hDRV_TM1637));
}


void CPN_TM1637_SendData(CPN_TM1637_HandlerTypeDef *hCPN_TM1637, char* cTM1637_Buf)
{
    /* u16TM1637_Buf must be an unsigned integer in the range 0000 to 9999 */
    uint8_t u8NumberofDigits = 0;
    while (*(cTM1637_Buf + u8NumberofDigits) != '\0') {
        u8NumberofDigits++;
    }
    u8NumberofDigits--;
    switch (u8NumberofDigits) {
        case 0:
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Kilo = (uint8_t) TM1637_SPAT_BLANK;
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Hecto = (uint8_t) TM1637_SPAT_BLANK;
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Deka = (uint8_t) TM1637_SPAT_BLANK;
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Base = CPN_TM1637_FindPattern(*(cTM1637_Buf + 0));
            break;
        case 1:
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Kilo = (uint8_t) TM1637_SPAT_BLANK;
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Hecto = (uint8_t) TM1637_SPAT_BLANK;
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Deka = CPN_TM1637_FindPattern(*(cTM1637_Buf + 0));
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Base = CPN_TM1637_FindPattern(*(cTM1637_Buf + 1));
            break;
        case 2:
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Kilo = (uint8_t) TM1637_SPAT_BLANK;
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Hecto = CPN_TM1637_FindPattern(*(cTM1637_Buf + 0));
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Deka = CPN_TM1637_FindPattern(*(cTM1637_Buf + 1));
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Base = CPN_TM1637_FindPattern(*(cTM1637_Buf + 2));
            break;
        case 3:
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Kilo = CPN_TM1637_FindPattern(*(cTM1637_Buf + 0));
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Hecto = CPN_TM1637_FindPattern(*(cTM1637_Buf + 1));
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Deka = CPN_TM1637_FindPattern(*(cTM1637_Buf + 2));
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Base = CPN_TM1637_FindPattern(*(cTM1637_Buf + 3));
            break;
        default:
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Kilo = (uint8_t) TM1637_SPAT_FULL;
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Hecto = (uint8_t) TM1637_SPAT_FULL;
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Deka = (uint8_t) TM1637_SPAT_FULL;
            hCPN_TM1637->hDRV_TM1637.u8TM1637_Base = (uint8_t) TM1637_SPAT_FULL;
            break;
    }
    DRV_TM1637_SendData(&(hCPN_TM1637->hDRV_TM1637));
}

void CPN_TM1637_TurnOff(CPN_TM1637_HandlerTypeDef *hCPN_TM1637)
{
    DRV_TM1637_TurnOff(&hCPN_TM1637->hDRV_TM1637);
}

void CPN_TM1637_TurnOn(CPN_TM1637_HandlerTypeDef *hCPN_TM1637)
{
    DRV_TM1637_TurnOn(&hCPN_TM1637->hDRV_TM1637);
}

/************************************************************************/
/*					INLINE FUNCTIONS                                    */
/************************************************************************/
static inline
uint8_t CPN_TM1637_FindPattern(char chr)
{
    uint8_t u8TM1637_Ret;
    switch (chr) {
        case '0':
            u8TM1637_Ret = (uint8_t) TM1637_SPAT_0;
            break;
        case '1':
            u8TM1637_Ret = (uint8_t) TM1637_SPAT_1;
            break;
        case '2':
            u8TM1637_Ret = (uint8_t) TM1637_SPAT_2;
            break;
        case '3':
            u8TM1637_Ret = (uint8_t) TM1637_SPAT_3;
            break;
        case '4':
            u8TM1637_Ret = (uint8_t) TM1637_SPAT_4;
            break;
        case '5':
            u8TM1637_Ret = (uint8_t) TM1637_SPAT_5;
            break;
        case '6':
            u8TM1637_Ret = (uint8_t) TM1637_SPAT_6;
            break;
        case '7':
            u8TM1637_Ret = (uint8_t) TM1637_SPAT_7;
            break;
        case '8':
            u8TM1637_Ret = (uint8_t) TM1637_SPAT_8;
            break;
        case '9':
            u8TM1637_Ret = (uint8_t) TM1637_SPAT_9;
            break;
        default:
            u8TM1637_Ret = (uint8_t) TM1637_SPAT_FULL;
            break;
    }
    return u8TM1637_Ret;
}
