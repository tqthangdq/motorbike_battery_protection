/**
 * @file hal_usart.c
 * @brief Hardware Abstraction Layer for USART0 - ATMEGE328P
 *
 * @author Thang Q. Tran - thang.tran@radsense.vn
 * @version   2.0
 * @date      Oct-2021
 * @copyright All rights reserved
 */

#include "hal_usart.h"

static inline void HAL_USART_ModeConfig(HAL_USART_HandlerTypeDef *hHAL_USART);
static inline void HAL_USART_DataLengthConfig(HAL_USART_HandlerTypeDef *hHAL_USART);
static inline void HAL_USART_StopBitConfig(HAL_USART_HandlerTypeDef *hHAL_USART);
static inline void HAL_USART_ParityConfig(HAL_USART_HandlerTypeDef *hHAL_USART);
static inline void HAL_USART_InterruptConfig(HAL_USART_HandlerTypeDef *hHAL_USART);
static inline void HAL_USART_BaudRateConfig(HAL_USART_HandlerTypeDef *hHAL_USART);
static inline void HAL_USART_TXRXEnable(HAL_USART_HandlerTypeDef *hHAL_USART);

/**
 *	@brief <b> HAL USART Methods</b>
 *	@details
 *	- Initialize the USART Module
 *
 *	@param *hHAL_USART - HAL USART Handler Pointer
 */
void HAL_USART_Init(HAL_USART_HandlerTypeDef *hHAL_USART)
{
	HAL_USART_ModeConfig(hHAL_USART);
	HAL_USART_DataLengthConfig(hHAL_USART);
	HAL_USART_StopBitConfig(hHAL_USART);
	HAL_USART_ParityConfig(hHAL_USART);
	HAL_USART_InterruptConfig(hHAL_USART);
	HAL_USART_BaudRateConfig(hHAL_USART);
	HAL_USART_TXRXEnable(hHAL_USART);
}

static inline void HAL_USART_ModeConfig(HAL_USART_HandlerTypeDef *hHAL_USART)
{
	switch(hHAL_USART->eUSART_Mode) {
		case USART_ASYN_MODE:
			/* Bits 7:6 – UMSELn1:0 USART Mode Select */
			UCSR0C &= ~(_BV(UMSEL01) | _BV(UMSEL00));	//Asynchronous USART
			/* Bit 0 – UCPOLn: Clock Polarity */
			UCSR0C &= ~(_BV(UCPOL0));					//Disable on Asynchronous USART
			break;
		case USART_SYNC_MODE:
			break;
		case USART_MSPI_MODE:
			break;
		default:
			break;
	}
}

static inline void HAL_USART_DataLengthConfig(HAL_USART_HandlerTypeDef *hHAL_USART)
{
	switch(hHAL_USART->eUSART_DataLength) {
		case USART_DATA_5_BIT:
			break;
		case USART_DATA_6_BIT:
			break;
		case USART_DATA_7_BIT:
			break;
		case USART_DATA_8_BIT:
			/* Bit 2:1 – UCSZn1:0: Character Size */
			UCSR0C |= _BV(UCSZ01) | _BV(UCSZ00);		//8-bit data length
			/* Bit 2 – UCSZn2: Character Size n */
			UCSR0B &= ~(_BV(UCSZ02));					//8-bit data length
			break;
		case USART_DATA_9_BIT:
			break;
		default:
			break;
	}
}

static inline void HAL_USART_StopBitConfig(HAL_USART_HandlerTypeDef *hHAL_USART)
{
	switch(hHAL_USART->eUSART_StopBit) {
		case USART_STOP_1_BIT:
			/* Bit 3 – USBSn: Stop Bit Select */
			UCSR0C &= ~(_BV(USBS0));					//1-bit
			break;
		case USART_STOP_2_BIT:
			break;
		default:
			break;
	}
}

static inline void HAL_USART_ParityConfig(HAL_USART_HandlerTypeDef *hHAL_USART)
{
	switch(hHAL_USART->eUSART_Parity) {
		case USART_PARITY_DISABLE:
			/* Bits 5:4 – UPMn1:0: Parity Mode */
			UCSR0C &= ~(_BV(UPM01) | _BV(UPM00));		//Disable
			break;
		case USART_PARITY_ENABLE_EVEN:
			break;
		case USART_PARITY_ENABLE_ODD:
			break;
		default:
			break;
	}
}

static inline void HAL_USART_InterruptConfig(HAL_USART_HandlerTypeDef *hHAL_USART)
{
	switch(hHAL_USART->eUSART_Interrupt) {
		case USART_CONF_DISABLE:
			/* Bit 7 – RXCIEn: RX Complete Interrupt Enable n */
			UCSR0B &= ~(_BV(RXCIE0));					//Disable
			/* Bit 6 – TXCIEn: TX Complete Interrupt Enable n */
			UCSR0B &= ~(_BV(TXCIE0));					//Disable
			/* Bit 5 – UDRIEn: USART Data Register Empty Interrupt Enable n */
			UCSR0B &= ~(_BV(UDRIE0));					//Disable
			break;
		case USART_CONF_ENABLE:
			break;
		default:
			break;
	}
}

static inline void HAL_USART_BaudRateConfig(HAL_USART_HandlerTypeDef *hHAL_USART)
{
	uint16_t u16UBRR = (((F_CPU / 16) + (hHAL_USART->u16USART_BaudRate / 2)) / (hHAL_USART->u16USART_BaudRate)) - 1;
	/* UBRRnL and UBRRnH – USART Baud Rate Registers */
	/* Bit 11:0 – UBRR[11:0]: USART Baud Rate Register */
	UBRR0H = (unsigned char)(u16UBRR >> 8);
	UBRR0L = (unsigned char)(u16UBRR);
}

static inline void HAL_USART_TXRXEnable(HAL_USART_HandlerTypeDef *hHAL_USART)
{
	/* Bit 4 – RXENn: Receiver Enable n */
	UCSR0B |= _BV(RXEN0);						//Enable
	/* Bit 3 – TXENn: TranSSitter Enable n */
	UCSR0B |= _BV(TXEN0);						//Enable
}