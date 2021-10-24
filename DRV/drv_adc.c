#include "drv_adc.h"

void DRV_ADC_Init(DRV_ADC_HandlerTypeDef *hDRV_ADC)
{
    HAL_ADC_Init(&hDRV_ADC->hHAL_ADC);
    g_eADC_ConvFlag = ADC_WAIT_NEXT_DATA;
    g_u16ADC_PreviousResult = 0;
}

void DRV_ADC_EnConf(DRV_ADC_HandlerTypeDef *hDRV_ADC,
                    HAL_ADC_EnableTypeDef	eADC_En)
{
    hDRV_ADC->hHAL_ADC.eADC_En = eADC_En;
    HAL_ADC_EnConf(&hDRV_ADC->hHAL_ADC);
}

void DRV_ADC_StartConf(DRV_ADC_HandlerTypeDef	*hDRV_ADC,
                       HAL_ADC_StartConvTypeDef	eADC_Start)
{
    hDRV_ADC->hHAL_ADC.eADC_Start = eADC_Start;
    HAL_ADC_StartConf(&hDRV_ADC->hHAL_ADC);
}

void DRV_ADC_ChanSelConf(DRV_ADC_HandlerTypeDef		*hDRV_ADC,
                         HAL_ADC_ChannelSelTypeDef	eADC_ChanSel)
{
    hDRV_ADC->hHAL_ADC.eADC_ChanSel = eADC_ChanSel;
    HAL_ADC_ChanSelConf(&hDRV_ADC->hHAL_ADC);
}

ISR(ADC_vect)
{
    g_u16ADC_PreviousResult = (uint16_t) ADCL;
    g_u16ADC_PreviousResult |= (uint16_t)(ADCH << 8);
    g_eADC_ConvFlag = ADC_DATA_AVAILABLE;
}