#ifndef CPN_USART_H_
#define CPN_USART_H_

#include "../DRV/drv_usart.h"

typedef enum {
	CPN_USART_STATE_INIT = 0,
	CPN_USART_STATE_READY,
	CPN_USART_STATE_SEND
} CPN_USART_StateTypeDef;

typedef struct CPN_USART_HandlerStruct {
	DRV_USART_HandlerTypeDef	hDRV_USART;
	CPN_USART_StateTypeDef		eUSART_State;
} CPN_USART_HandlerTypeDef;

void CPN_USART_Init(CPN_USART_HandlerTypeDef *hCPN_USART);
void CPN_USART_Task(CPN_USART_HandlerTypeDef *hCPN_USART);
void CPN_USART_Send(CPN_USART_HandlerTypeDef *hCPN_USART, char *buffer);

#endif