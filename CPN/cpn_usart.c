#include "cpn_usart.h"

void CPN_USART_Init(CPN_USART_HandlerTypeDef *hCPN_USART)
{
	/************************************************************************/
	/*					INITIALIZE UART0                                    */
	/************************************************************************/
	hCPN_USART->hDRV_USART.hHAL_USART.eUSART_Mode = USART_ASYN_MODE;
	hCPN_USART->hDRV_USART.hHAL_USART.eUSART_DataLength = USART_DATA_8_BIT;
	hCPN_USART->hDRV_USART.hHAL_USART.eUSART_StopBit = USART_STOP_1_BIT;
	hCPN_USART->hDRV_USART.hHAL_USART.eUSART_Parity = USART_PARITY_DISABLE;
	hCPN_USART->hDRV_USART.hHAL_USART.eUSART_Interrupt = USART_CONF_DISABLE;
	hCPN_USART->hDRV_USART.hHAL_USART.u16USART_BaudRate = 9600;
	DRV_USART_Init(&hCPN_USART->hDRV_USART);
	
	/* Initialize the State Machine */
	hCPN_USART->eUSART_State = CPN_USART_STATE_INIT;
}

void CPN_USART_Task(CPN_USART_HandlerTypeDef *hCPN_USART)
{
	switch (hCPN_USART->eUSART_State) {
		case CPN_USART_STATE_INIT:
			hCPN_USART->eUSART_State = CPN_USART_STATE_READY;
			break;
		case CPN_USART_STATE_READY:
			if (hCPN_USART->hDRV_USART.eUSART_NewBufFlag == DRV_USART_NEW_BUF) {
				hCPN_USART->eUSART_State = CPN_USART_STATE_SEND;
			}
			break;
		case CPN_USART_STATE_SEND:
			DRV_USART_SendChar(&hCPN_USART->hDRV_USART);
			if (hCPN_USART->hDRV_USART.eUSART_NewBufFlag == DRV_USART_NO_BUF) {
				hCPN_USART->eUSART_State = CPN_USART_STATE_READY;
			}
			break;
		default:
			break;
	}
}

void CPN_USART_Send(CPN_USART_HandlerTypeDef *hCPN_USART, char *buffer)
{
	if ((hCPN_USART->eUSART_State == CPN_USART_STATE_READY) ||
	    (hCPN_USART->eUSART_State == CPN_USART_STATE_INIT)) {
		DRV_USART_Send(&hCPN_USART->hDRV_USART, buffer);
	}
}