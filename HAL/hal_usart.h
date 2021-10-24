/**
 * @file hal_usart.h
 * @brief Hardware Abstraction Layer for USART0 - ATMEGE328P
 *
 * @author Thang Q. Tran - thang.tran@radsense.vn
 * @version   2.0
 * @date      Oct-2021
 * @copyright All rights reserved
 */

#ifndef HAL_USART_H_
#define HAL_USART_H_

#include <avr/io.h>
#include <stdint.h>
#include <avr/sfr_defs.h>

#ifndef F_CPU
#define F_CPU	16000000UL
#endif

typedef enum {
	USART_CONF_DISABLE = 0,
	USART_CONF_ENABLE
} HAL_USART_ConfigTypeDef;

typedef enum {
	USART_DATA_5_BIT = 0,
	USART_DATA_6_BIT,
	USART_DATA_7_BIT,
	USART_DATA_8_BIT,
	USART_DATA_9_BIT
} HAL_USART_DataLengthTypeDef;

typedef enum {
	USART_STOP_1_BIT = 0,
	USART_STOP_2_BIT
} HAL_USART_StopBitTypeDef;

typedef enum {
	USART_PARITY_DISABLE = 0,
	USART_PARITY_ENABLE_EVEN,
	USART_PARITY_ENABLE_ODD
} HAL_USART_ParityTypeDef;

typedef enum {
	USART_ASYN_MODE = 0,
	USART_SYNC_MODE,
	USART_MSPI_MODE
} HAL_USART_ModeTypeDef;

/**
 *  @brief <b>HAL USART Attributes</b>
 *	@details
 *	- USART Configurations
 *
 *  @param eUSART_Mode - The USART supports four modes of clock operation:
 *  Normal asynchronous, Double Speed asynchronous, Master synchronous and Slave synchronous mode.
 *	@param eUSART_DataLength - 5, 6, 7, 8, or 9 data bits
 *	@param eUSART_StopBit - 1 or 2 stop bits
 *	@param eUSART_Parity - no, even or odd parity bit
 *	@param eUSART_Interrupt - use Interrupt Service Routine or Not
 *	@param u16USART_BaudRate - Baud rate (in bits per second, bps)
 *
 */
typedef struct HAL_USART_HandlerStruct {
	HAL_USART_ModeTypeDef			eUSART_Mode;
	HAL_USART_DataLengthTypeDef		eUSART_DataLength;
	HAL_USART_StopBitTypeDef		eUSART_StopBit;
	HAL_USART_ParityTypeDef			eUSART_Parity;
	HAL_USART_ConfigTypeDef			eUSART_Interrupt;
	uint32_t						u16USART_BaudRate;
} HAL_USART_HandlerTypeDef;

/**
 *	@brief <b> HAL USART Methods</b>
 *	@details
 *	- Initialize the USART Module
 *
 *	@param *hHAL_USART - HAL USART Handler Pointer
 */
void HAL_USART_Init(HAL_USART_HandlerTypeDef *hHAL_USART);

#endif