#ifndef DRV_USART_H_
#define DRV_USART_H_

#include <stdint.h>
#include <stdlib.h>
#include "../HAL/hal_usart.h"

#ifndef DRV_USART_BUFFER_SIZE
#define DRV_USART_BUFFER_SIZE	64
#endif

typedef enum DRV_USART_RetEnum {
	DRV_USART_NO_BUF = 0,
	DRV_USART_NEW_BUF
} DRV_USART_RetTypeDef;

typedef struct DRV_USART_HandlerStruct {
	HAL_USART_HandlerTypeDef	hHAL_USART;
	DRV_USART_RetTypeDef		eUSART_NewBufFlag;
	char*						u8USART_Buffer;
	uint8_t						u8USART_Index;
} DRV_USART_HandlerTypeDef;

void DRV_USART_Init(DRV_USART_HandlerTypeDef *hDRV_USART);
void DRV_USART_Send(DRV_USART_HandlerTypeDef *hDRV_USART, char *buffer);
void DRV_USART_SendChar(DRV_USART_HandlerTypeDef *hDRV_USART);

#endif