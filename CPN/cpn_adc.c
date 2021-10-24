#include "cpn_adc.h"

static inline
void CPN_ADC_ReadADC(CPN_ADC_ChannelTypeDef *sADC);

void CPN_ADC_Init(CPN_ADC_HandlerTypeDef *hCPN_ADC)
{
    /************************************************************************/
    /*					ADC3 INITIALIZATION                                 */
    /************************************************************************/
    hCPN_ADC->sADC3.u16ADC_Queue = (uint16_t *)calloc(CPN_ADC_ARRAY_SIZE, sizeof(uint16_t));
    hCPN_ADC->sADC3.u16ADC_Sum = 0;
    hCPN_ADC->sADC3.u8ADC_Index = 0;
    /************************************************************************/
    /*					ADC4 INITIALIZATION                                 */
    /************************************************************************/
    hCPN_ADC->sADC4.u16ADC_Queue = (uint16_t *)calloc(CPN_ADC_ARRAY_SIZE, sizeof(uint16_t));
    hCPN_ADC->sADC4.u16ADC_Sum = 0;
    hCPN_ADC->sADC4.u8ADC_Index = 0;

    /************************************************************************/
    /*					STATE MACHINE INITIALIZATION                        */
    /************************************************************************/
    hCPN_ADC->eADC_State = CPN_ADC_STATE_INIT;

	/************************************************************************/
	/*					INITIALIZE ADC MODULE                               */
	/************************************************************************/
    hCPN_ADC->hDRV_ADC.hHAL_ADC.eADC_Ref = ADC_AREF_AVCC;
    hCPN_ADC->hDRV_ADC.hHAL_ADC.eADC_LeftAdj = ADC_LEFT_ADJ_DIS;
    hCPN_ADC->hDRV_ADC.hHAL_ADC.eADC_PresSel = ADC_PRES_DIV_128;
    hCPN_ADC->hDRV_ADC.hHAL_ADC.eADC_Mode = ADC_SINGLE_MODE;
    hCPN_ADC->hDRV_ADC.hHAL_ADC.eADC_AutoScr = ADC_FREE_MODE_TRG;
    hCPN_ADC->hDRV_ADC.hHAL_ADC.eADC_Int = ADC_INT_EN;
    hCPN_ADC->hDRV_ADC.hHAL_ADC.eADC_ChanSel = ADC_ADC3;
    hCPN_ADC->hDRV_ADC.hHAL_ADC.eADC_En = ADC_EN;
    hCPN_ADC->hDRV_ADC.hHAL_ADC.eADC_Start = ADC_START_NONE;
	DRV_ADC_Init(&hCPN_ADC->hDRV_ADC);
}

void CPN_ADC_Task(CPN_ADC_HandlerTypeDef *hCPN_ADC)
{
    switch (hCPN_ADC->eADC_State) {
        case CPN_ADC_STATE_INIT:
            hCPN_ADC->eADC_State = CPN_ADC_STATE_ADC3;
            break;
        case CPN_ADC_STATE_ADC3:
			/* Read the previous result */
			CPN_ADC_ReadADC(&hCPN_ADC->sADC3);
			
			/* Change to next state*/
            DRV_ADC_ChanSelConf(&hCPN_ADC->hDRV_ADC, ADC_ADC4);
            DRV_ADC_StartConf(&hCPN_ADC->hDRV_ADC, ADC_START_SINGLE);
			hCPN_ADC->eADC_State = CPN_ADC_STATE_ADC4;
            break;
        case CPN_ADC_STATE_ADC4:
            /* Read the previous result */
            CPN_ADC_ReadADC(&hCPN_ADC->sADC4);
            
            /* Change to next state*/
            DRV_ADC_ChanSelConf(&hCPN_ADC->hDRV_ADC, ADC_ADC3);
            DRV_ADC_StartConf(&hCPN_ADC->hDRV_ADC, ADC_START_SINGLE);
            hCPN_ADC->eADC_State = CPN_ADC_STATE_ADC3;
            break;
        default:
            break;
    }
}

/************************************************************************/
/*					INLINE FUNCTIONS                                    */
/************************************************************************/
static inline
void CPN_ADC_ReadADC(CPN_ADC_ChannelTypeDef *sADC)
{
    if (g_eADC_ConvFlag == ADC_DATA_AVAILABLE) {
        /* The total value will be added to the new value */
        sADC->u16ADC_Sum += g_u16ADC_PreviousResult;
        /* The sum value will remove the old value in the position to be replaced */
        sADC->u16ADC_Sum -= *(sADC->u16ADC_Queue + sADC->u8ADC_Index);
        /* The new value will be placed in the position that was removed */
        *(sADC->u16ADC_Queue + sADC->u8ADC_Index) = g_u16ADC_PreviousResult;
        /* Update the value of index */
        sADC->u8ADC_Index = (sADC->u8ADC_Index + 1)&CPN_ADC_ARRAY_MASK;
        sADC->u16ADC_Average = (uint16_t) sADC->u16ADC_Sum / CPN_ADC_ARRAY_SIZE;
        /* Start the next conversion */
        g_eADC_ConvFlag = ADC_WAIT_NEXT_DATA;
    }
}