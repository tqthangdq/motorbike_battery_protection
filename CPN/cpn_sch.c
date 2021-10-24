#include "cpn_sch.h"

void CPN_SCH_Init(CPN_SCH_HandlerTypeDef *hCPN_SCH)
{
    /************************************************************************/
    /*					INITIALIZE TIMER0 CTC MODE                          */
    /************************************************************************/
    hCPN_SCH->hDRV_SCH.hHAL_TIMER0.eTIMER0_Mode = TIMER0_MODE_CTC;
    hCPN_SCH->hDRV_SCH.hHAL_TIMER0.eTIMER0_CompB = TIMER0_COMPB_DIS;
    hCPN_SCH->hDRV_SCH.hHAL_TIMER0.eTIMER0_Int = TIMER0_INT_OCIEA;
    hCPN_SCH->hDRV_SCH.hHAL_TIMER0.eTIMER0_CompA = TIMER0_COMPA_TOGGLE;
    hCPN_SCH->hDRV_SCH.hHAL_TIMER0.eTIMER0_CpOut = TIMER0_CPOUT_COMPA;
    hCPN_SCH->hDRV_SCH.hHAL_TIMER0.eTIMER0_Clock = TIMER0_CLOCK_DIV1024;
    hCPN_SCH->hDRV_SCH.hHAL_TIMER0.u8TIMER0_TCNT0 = 0x00;
    hCPN_SCH->hDRV_SCH.hHAL_TIMER0.u8TIMER0_OCR0B = 0x00;
    hCPN_SCH->hDRV_SCH.hHAL_TIMER0.u8TIMER0_OCR0A = 0x9C;
    DRV_SCH_Init(&hCPN_SCH->hDRV_SCH);
    /************************************************************************/
    /*					ALLOCATE MEMORY FOR TASKING SCHEDULER                                                                     */
    /************************************************************************/
    hCPN_SCH->eSCH_TaskArray = (DRV_SCH_StateTypeDef *)
                               malloc(hCPN_SCH->u8SCH_TotalTask *
                                      sizeof(DRV_SCH_StateTypeDef));
    hCPN_SCH->u8SCH_RunTimeArray = (uint8_t *)
                                   calloc(hCPN_SCH->u8SCH_TotalTask,
                                          sizeof(uint8_t));
    hCPN_SCH->u8SCH_IntervalArray = (uint8_t *)
                                    calloc(hCPN_SCH->u8SCH_TotalTask,
                                           sizeof(uint8_t));
    /************************************************************************/
    /*					SETTING UP AT THE INITIAL STATE                     */
    /************************************************************************/
    CPN_SCH_Reset(hCPN_SCH);
}

void CPN_SCH_Task(CPN_SCH_HandlerTypeDef *hCPN_SCH)
{
    /* Conditional Statement */
    if (g_eSCH_SCHState == DRV_SCH_RUN) {
        for (uint8_t i = 0; i < (hCPN_SCH->u8SCH_TotalTask); i++) {
            if (g_u8SCH_TickCounter == hCPN_SCH->u8SCH_RunTimeArray[i]) {
                hCPN_SCH->eSCH_TaskArray[i] = DRV_SCH_RUN;
                hCPN_SCH->u8SCH_RunTimeArray[i] += (uint8_t)hCPN_SCH->u8SCH_IntervalArray[i];
            }
        }
    }
}

void CPN_SCH_Reset(CPN_SCH_HandlerTypeDef *hCPN_SCH)
{
    /* Reset State for All Task */
    for (uint8_t i = 0; i<hCPN_SCH->u8SCH_TotalTask; i++) {
        hCPN_SCH->eSCH_TaskArray[i] = DRV_SCH_IDLE;
    }
    g_eSCH_SCHState = DRV_SCH_IDLE;
}