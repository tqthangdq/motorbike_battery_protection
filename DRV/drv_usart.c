#include "drv_usart.h"

void DRV_USART_Init(DRV_USART_HandlerTypeDef *hDRV_USART)
{
    HAL_USART_Init(&hDRV_USART->hHAL_USART);
	hDRV_USART->eUSART_NewBufFlag = DRV_USART_NO_BUF;
	hDRV_USART->u8USART_Buffer = (char*)malloc(DRV_USART_BUFFER_SIZE*sizeof(char));
	hDRV_USART->u8USART_Index = 0;
}

void DRV_USART_Send(DRV_USART_HandlerTypeDef *hDRV_USART, char *newStr)
{
    hDRV_USART->u8USART_Buffer = newStr;
    hDRV_USART->u8USART_Index = 0;
    hDRV_USART->eUSART_NewBufFlag = DRV_USART_NEW_BUF;
}

void DRV_USART_SendChar(DRV_USART_HandlerTypeDef *hDRV_USART)
{
    while (!(UCSR0A & _BV(UDRE0)));
    UDR0 = *(hDRV_USART->u8USART_Buffer + hDRV_USART->u8USART_Index);
    if (*(hDRV_USART->u8USART_Buffer + hDRV_USART->u8USART_Index) == '\0') {
		while (!(UCSR0A & _BV(UDRE0)));
		UDR0 = '\r';
		while (!(UCSR0A & _BV(UDRE0)));
		UDR0 = '\n';
        hDRV_USART->u8USART_Index = 0;
        hDRV_USART->eUSART_NewBufFlag = DRV_USART_NO_BUF;
    } else {
        hDRV_USART->u8USART_Index++;
    }
}