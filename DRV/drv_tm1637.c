#include "drv_tm1637.h"

/************************************************************************/
/*					FUNCTION DECLARATION                                */
/************************************************************************/
static inline
void DRV_TM1637_pullBus(HAL_GPIO_HandlerTypeDef *hHAL_GPIO_Line);
static inline
void DRV_TM1637_releaseBus(HAL_GPIO_HandlerTypeDef *hHAL_GPIO_Line);
static inline
void DRV_TM1637_startCondition(DRV_TM1637_HandlerTypeDef *hDRV_TM1637);
static inline
void DRV_TM1637_stopCondition(DRV_TM1637_HandlerTypeDef *hDRV_TM1637);
static inline
void DRV_TM1637_waitACKCondition(DRV_TM1637_HandlerTypeDef *hDRV_TM1637);
static inline
void DRV_TM1637_writeByte(DRV_TM1637_HandlerTypeDef *hDRV_TM1637, uint8_t u8TM1637_Data);
static inline
void DRV_TM1637_sendCMD(DRV_TM1637_HandlerTypeDef *hDRV_TM1637, uint8_t u8TM1637_Cmd);


/************************************************************************/
/*					OPERATION FUNCTIONS                                 */
/************************************************************************/
void DRV_TM1637_Init(DRV_TM1637_HandlerTypeDef *hDRV_TM1637)
{
    /************************************************************************/
    /*				INITIALIZE TM1637 CLK                                   */
    /************************************************************************/
    HAL_GPIO_ConfDirectionRegister(&hDRV_TM1637->hHAL_GPIO_CLK, GPIO_INPUT);
    HAL_GPIO_ConfDataRegister(&hDRV_TM1637->hHAL_GPIO_CLK, GPIO_DRIVE_LOW);
    /************************************************************************/
    /*				INITIALIZE TM1637 DIO                                   */
    /************************************************************************/
    HAL_GPIO_ConfDirectionRegister(&hDRV_TM1637->hHAL_GPIO_DIO, GPIO_INPUT);
    HAL_GPIO_ConfDataRegister(&hDRV_TM1637->hHAL_GPIO_DIO, GPIO_DRIVE_LOW);
    /************************************************************************/
    /*				INITIALIZE FIRST CHARACTERS                             */
    /************************************************************************/
    hDRV_TM1637->u8TM1637_Base = TM1637_SPAT_MINUS;
    hDRV_TM1637->u8TM1637_Deka = TM1637_SPAT_I;
    hDRV_TM1637->u8TM1637_Hecto = TM1637_SPAT_H;
    hDRV_TM1637->u8TM1637_Kilo = TM1637_SPAT_MINUS;
    _delay_us(TM1637_HALF_CLOCK_PERIOD);
    /************************************************************************/
    /*				TM1637 SEQUENCE WRITING                                 */
    /************************************************************************/
    /*
     *	- WRITE: COMMAND1 <- DATA COMMAND SETTINGS
     *	- WRITE: COMMAND2 <- DISPLAY ADDRESS COMMAND SETTINGS
     *			 THERE ARE 6 DISPLAY ADDRESSES, BUT WE ONLY USES 4
     *			 JUST NEED CALL THE FIRST ADDRESS, THEY WILL AUTOMATIC ADDING
     *	- WRITE: DATA ARRAY (MAX. 4)
     *	- WRITE: COMMAND3 <- DISPLAY CONTROL
     *
     *	- UPDATE: COMMAND2 -> DATA -> COMMAND3...
     */
    /************************************************************************/
    /*				INITIALIZE ALL SEGMENTS                                 */
    /************************************************************************/
    DRV_TM1637_sendCMD(hDRV_TM1637, TM1637_CMD_SETUP);
    DRV_TM1637_SendData(hDRV_TM1637);
    DRV_TM1637_sendCMD(hDRV_TM1637, TM1637_CMD_SHOWDATA);
}

void DRV_TM1637_SendData(DRV_TM1637_HandlerTypeDef *hDRV_TM1637)
{
    DRV_TM1637_startCondition(hDRV_TM1637);
    DRV_TM1637_writeByte(hDRV_TM1637, TM1637_CMD_WRITEDATA);
    DRV_TM1637_writeByte(hDRV_TM1637, hDRV_TM1637->u8TM1637_Kilo);
    DRV_TM1637_writeByte(hDRV_TM1637, hDRV_TM1637->u8TM1637_Hecto);
    DRV_TM1637_writeByte(hDRV_TM1637, hDRV_TM1637->u8TM1637_Deka);
    DRV_TM1637_writeByte(hDRV_TM1637, hDRV_TM1637->u8TM1637_Base);
    DRV_TM1637_stopCondition(hDRV_TM1637);
}
void DRV_TM1637_TurnOff(DRV_TM1637_HandlerTypeDef *hDRV_TM1637)
{
	DRV_TM1637_sendCMD(hDRV_TM1637, TM1637_CMD_OFFDATA);
}
void DRV_TM1637_TurnOn(DRV_TM1637_HandlerTypeDef *hDRV_TM1637)
{
	DRV_TM1637_sendCMD(hDRV_TM1637, TM1637_CMD_SHOWDATA);
}

/************************************************************************/
/*					INLINE FUNCTIONS                                    */
/************************************************************************/
static inline
void DRV_TM1637_pullBus(HAL_GPIO_HandlerTypeDef *hHAL_GPIO_Line)
{
    HAL_GPIO_ConfDirectionRegister(hHAL_GPIO_Line, GPIO_OUTPUT);
}

static inline
void DRV_TM1637_releaseBus(HAL_GPIO_HandlerTypeDef *hHAL_GPIO_Line)
{
    HAL_GPIO_ConfDirectionRegister(hHAL_GPIO_Line, GPIO_INPUT);
}

static inline
void DRV_TM1637_startCondition(DRV_TM1637_HandlerTypeDef *hDRV_TM1637)
{
    /* Set CLK is INPUT | HIGH */
    DRV_TM1637_releaseBus(&hDRV_TM1637->hHAL_GPIO_CLK);
    _delay_us(TM1637_HALF_CLOCK_PERIOD);
    /* Set DIO is OUTPUT | LOW */
    DRV_TM1637_pullBus(&hDRV_TM1637->hHAL_GPIO_DIO);
    _delay_us(TM1637_HALF_CLOCK_PERIOD);
}

static inline
void DRV_TM1637_stopCondition(DRV_TM1637_HandlerTypeDef *hDRV_TM1637)
{
    /* Pull CLK OUTPUT | LOW, to let TM1637 know that it can stop sending ACK
     * (that is, it can stop pulling DIO LOW) */
    DRV_TM1637_pullBus(&hDRV_TM1637->hHAL_GPIO_CLK);
    _delay_us(TM1637_QUARTER_CLOCK_PERIOD);
    /* Make sure DIO is LOW, because we need rising edge transition */
    DRV_TM1637_pullBus(&hDRV_TM1637->hHAL_GPIO_DIO);
    _delay_us(TM1637_QUARTER_CLOCK_PERIOD);
    /* Let the CLK be pulled HIGH by pull-up resistor */
    DRV_TM1637_releaseBus(&hDRV_TM1637->hHAL_GPIO_CLK);
    _delay_us(TM1637_HALF_CLOCK_PERIOD);
    /* Let the DIO be pulled HIGH - send STOP */
    DRV_TM1637_releaseBus(&hDRV_TM1637->hHAL_GPIO_DIO);
    _delay_us(TM1637_HALF_CLOCK_PERIOD);
}

static inline
void DRV_TM1637_waitACKCondition(DRV_TM1637_HandlerTypeDef *hDRV_TM1637)
{
    /* Pull CLK to Low to transmit the clock signal */
    DRV_TM1637_pullBus(&hDRV_TM1637->hHAL_GPIO_CLK);
    /* Release the DIO line */
    DRV_TM1637_releaseBus(&hDRV_TM1637->hHAL_GPIO_DIO);
    _delay_us(TM1637_HALF_CLOCK_PERIOD);
    /* Release the CLK for 9th clock pulse */
    DRV_TM1637_releaseBus(&hDRV_TM1637->hHAL_GPIO_CLK);
    _delay_us(TM1637_QUARTER_CLOCK_PERIOD);
    /* Where to read the acknowledgment */
    /* WE DID NOT READ THE ACKNOWDLEGMENT, JUST DON'T CARE */
    /* After reading the acknowledgment, take force the DIO to LOW */
    DRV_TM1637_pullBus(&hDRV_TM1637->hHAL_GPIO_DIO);
    _delay_us(TM1637_QUARTER_CLOCK_PERIOD);
}

static inline
void DRV_TM1637_writeByte(DRV_TM1637_HandlerTypeDef *hDRV_TM1637, uint8_t u8TM1637_Data)
{
    /************************************************************************/
    /*				`	START CONDITION                                     */
    /************************************************************************/
    /*		______
    	CLK:
    		____
    	DIO:	|_ */
    /************************************************************************/
    /*					SEND BYTE                                           */
    /************************************************************************/
    /*	   __     1_     2_     3_     4_     5_     6_     7_     8_
    	CLK: |_x_|  |_x_|  |_x_|  |_x_|  |_x_|  |_x_|  |_x_|  |_x_|

    	DIO: x is where the change occurs in DIO line. Each _ is equal a Quarter. */
    for (uint8_t i = 0; i < 8; i++) {
        /* Pull CLK to Low to transmit the clock signal */
        DRV_TM1637_pullBus(&hDRV_TM1637->hHAL_GPIO_CLK);
        _delay_us(TM1637_QUARTER_CLOCK_PERIOD);

        if (u8TM1637_Data & 0x01) {
            DRV_TM1637_releaseBus(&hDRV_TM1637->hHAL_GPIO_DIO);
        } else {
            DRV_TM1637_pullBus(&hDRV_TM1637->hHAL_GPIO_DIO);
        }
        _delay_us(TM1637_QUARTER_CLOCK_PERIOD);

        /* Release CLK to High for next bit transmission */
        DRV_TM1637_releaseBus(&hDRV_TM1637->hHAL_GPIO_CLK);
        _delay_us(TM1637_HALF_CLOCK_PERIOD);

        /* Shift data to the right */
        u8TM1637_Data = (u8TM1637_Data >> 1);
    }

    /************************************************************************/
    /*					WAIT FOR ACK                                        */
    /************************************************************************/
    /*	     8_    _o_
    	CLK:   |__|
    		o is where the micro-controller should read the acknowledgment.
    	DIO:
    		-----x----^^^^^^|_  <- Force DIO Low to end the Data transmission */
    DRV_TM1637_waitACKCondition(hDRV_TM1637);
    /************************************************************************/
    /*					STOP CONDITION                                      */
    /************************************************************************/
    /*	    _o_    _e____
    	CLK:   |__|
    		e is where the DIO is released to HIGH to end the data transmission.
    	DIO:         ___
    		^^______|    */
}

static inline
void DRV_TM1637_sendCMD(DRV_TM1637_HandlerTypeDef *hDRV_TM1637, uint8_t u8TM1637_Cmd)
{
    DRV_TM1637_startCondition(hDRV_TM1637);
    DRV_TM1637_writeByte(hDRV_TM1637, u8TM1637_Cmd);
    DRV_TM1637_stopCondition(hDRV_TM1637);
}