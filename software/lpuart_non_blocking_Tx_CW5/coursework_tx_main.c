/*
 * Copyright (c) 2013 - 2014, Freescale Semiconductor, Inc.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * o Redistributions of source code must retain the above copyright notice, this list
 *   of conditions and the following disclaimer.
 *
 * o Redistributions in binary form must reproduce the above copyright notice, this
 *   list of conditions and the following disclaimer in the documentation and/or
 *   other materials provided with the distribution.
 *
 * o Neither the name of Freescale Semiconductor, Inc. nor the names of its
 *   contributors may be used to endorse or promote products derived from this
 *   software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 * ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON
 * ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/* Header files used in the KSDK LPUART example */
#include "board.h"
#include "fsl_clock_manager.h"
#include "fsl_lpuart_driver.h"

/* Header files used from the Warp-firmware */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "fsl_rtc_driver.h"
#include "SEGGER_RTT.h"

const uint8_t buffStart[]    = "\r\n\n+++++LPUART Transmission+++++\r\n";
const uint8_t bufferData1[]  = "\r\nTx will send the data individually\r\n";

int main(void)
{
	uint8_t					key;
    uint8_t rxChar = 0, txChar = 0;
    uint32_t byteCountBuff = 0;
	
    lpuart_state_t lpuartStatePtr;

	/*
	 *	Enable clock for I/O PORT A and PORT B
	 */

	CLOCK_SYS_EnablePortClock(PORTA_IDX);
	CLOCK_SYS_EnablePortClock(PORTB_IDX);

	/* Init board clock */
	BOARD_ClockInit();
  
	/*
	 *	Configure uart pins
	 */
    PORT_HAL_SetMuxMode(PORTB,1u,kPortMuxAlt2);
    PORT_HAL_SetMuxMode(PORTB,2u,kPortMuxAlt2);


	/*
	 *	Initialize KSDK Operating System Abstraction layer (OSA) layer.
	 */
	OSA_Init();
	
	/*
	 *	Setup SEGGER RTT to output as much as fits in buffers.
	 *
	 *	Using SEGGER_RTT_MODE_BLOCK_IF_FIFO_FULL can lead to deadlock, since
	 *	we might have SWD disabled at time of blockage.
	 */
	SEGGER_RTT_ConfigUpBuffer(0, NULL, NULL, 0, SEGGER_RTT_MODE_NO_BLOCK_TRIM);

	SEGGER_RTT_WriteString(0, "\r\n4B25 Coursework #5	CRSID: aaans2\r\n");
	OSA_TimeDelay(200);
	
    	/*
	 *	Initialize RTC Driver
	 */
	RTC_DRV_Init(0);
	
	//Initialize MMA8451Q
	//initMMA8451Q(	0x1D	/* i2cAddress */,	&deviceMMA8451QState	);

	
	// Fill in lpuart config data
    lpuart_user_config_t lpuartConfig = {
        .clockSource     = BOARD_LPUART_CLOCK_SOURCE, /*kClockLpuartSrcIrc48M*/
        .bitCountPerChar = kLpuart8BitsPerChar,	/*8-bits per char*/
        .parityMode      = kLpuartParityDisabled, /* None */
        .stopBitCount    = kLpuartOneStopBit, /*1 stop bit */
        .baudRate        = BOARD_DEBUG_UART_BAUD	/*9600*/
    };
	
	// Initialize the lpuart module with instance number and config structure
    LPUART_DRV_Init(BOARD_DEBUG_UART_INSTANCE, &lpuartStatePtr, &lpuartConfig);


	while(1)
	{
		SEGGER_RTT_WriteString(0, "\r\nChoose the following options\r\n");
		OSA_TimeDelay(10);
		SEGGER_RTT_WriteString(0, "\r- 'a': Display LPUART Setting.\n");
		OSA_TimeDelay(10);
		SEGGER_RTT_WriteString(0, "\r- 'b': Make the LPUART Tx transmit 'Hello World.'\n");
		OSA_TimeDelay(10);
		SEGGER_RTT_WriteString(0, "\r- 'c': Make the LPUART Tx transmit '4B25: Embedded System for Internet of Things.'\n");
		OSA_TimeDelay(10);
		SEGGER_RTT_WriteString(0, "\r- 'd': Make the LPUART Tx transmit all upper caps letters 'A-Z'.\n");
		OSA_TimeDelay(10);
		SEGGER_RTT_WriteString(0, "\r- 'e': Make the LPUART Tx transmit all lower caps letters 'a-z'.\n");
		OSA_TimeDelay(10);
		SEGGER_RTT_WriteString(0, "\r- 'f': Make the LPUART Tx transmit all number '0-9'.\n");
		OSA_TimeDelay(10);
		SEGGER_RTT_WriteString(0, "\r- 'g': Make the LPUART Tx transmit all symbols.\n");
		OSA_TimeDelay(10);
		SEGGER_RTT_WriteString(0, "\r- 'h': Make the LPUART Tx transmit input from the keyboard\n");
		OSA_TimeDelay(10);
		SEGGER_RTT_WriteString(0, "\rEnter selection> ");
		OSA_TimeDelay(10);
		
		key = SEGGER_RTT_WaitKey();

		switch (key)
		{
			case 'a':
			{
				SEGGER_RTT_WriteString(0, "\r\nBaud rate: 9600\r\n");
				OSA_TimeDelay(10);
				SEGGER_RTT_WriteString(0, "\r\nBit count per char: 8-bits\r\n");
				OSA_TimeDelay(10);
				SEGGER_RTT_WriteString(0, "\r\nParity mode: None\r\n");
				OSA_TimeDelay(10);
				SEGGER_RTT_WriteString(0, "\r\nStop bit: 1\r\n");
				OSA_TimeDelay(10);
				SEGGER_RTT_WriteString(0, "\r\nLPUART clock source: kClockLpuartSrcIrc48M\r\n");
				OSA_TimeDelay(10);
				break;
			}
			
			case 'b':
			{
				const uint8_t txCharB[] = "\r\nHello World.\r\n";
				uint32_t byteCountTxCharB = sizeof(txCharB);

				// Wait for the transfer finish, OR do something else
				LPUART_DRV_SendData(BOARD_DEBUG_UART_INSTANCE, txCharB, byteCountTxCharB);
				while (kStatus_LPUART_TxBusy == LPUART_DRV_GetTransmitStatus(BOARD_DEBUG_UART_INSTANCE, NULL)){}
				break;
			}
			
			case 'c':
			{
				const uint8_t txCharC[] = "\r\n4B25: Embedded System for Internet of Things.\r\n";
				uint32_t byteCountTxCharC = sizeof(txCharC);

				// Wait for the transfer finish, OR do something else
				LPUART_DRV_SendData(BOARD_DEBUG_UART_INSTANCE, txCharC, byteCountTxCharC);
				while (kStatus_LPUART_TxBusy == LPUART_DRV_GetTransmitStatus(BOARD_DEBUG_UART_INSTANCE, NULL)){}
				break;
			}
			
			case 'd':
			{
				const uint8_t txCharD[] = "\r\nABCDEFGHIJKLMNOPQRSTUVWXYZ\r\n";
				uint32_t byteCountTxCharD = sizeof(txCharD);

				// Wait for the transfer finish, OR do something else
				LPUART_DRV_SendData(BOARD_DEBUG_UART_INSTANCE, txCharD, byteCountTxCharD);
				while (kStatus_LPUART_TxBusy == LPUART_DRV_GetTransmitStatus(BOARD_DEBUG_UART_INSTANCE, NULL)){}
				break;
			}
			
			case 'e':
			{
				const uint8_t txCharE[] = "\r\nabcdefghijklmnopqrstuvwxyz\r\n";
				uint32_t byteCountTxCharE = sizeof(txCharE);
	
				// Wait for the transfer finish, OR do something else
				LPUART_DRV_SendData(BOARD_DEBUG_UART_INSTANCE, txCharE, byteCountTxCharE);
				while (kStatus_LPUART_TxBusy == LPUART_DRV_GetTransmitStatus(BOARD_DEBUG_UART_INSTANCE, NULL)){}
				break;
			}
			
			case 'f':
			{
				const uint8_t txCharF[] = "\r\n0123456789\r\n";
				uint32_t byteCountTxCharF = sizeof(txCharF);

				// Wait for the transfer finish, OR do something else
				LPUART_DRV_SendData(BOARD_DEBUG_UART_INSTANCE, txCharF, byteCountTxCharF);
				while (kStatus_LPUART_TxBusy == LPUART_DRV_GetTransmitStatus(BOARD_DEBUG_UART_INSTANCE, NULL)){}
				break;
			}
			
			case 'g':
			{
				const uint8_t txCharG[] = "\r\n~`!?@#$%^&*()-+_={}[]<|>;:',./\\r\n";
				uint32_t byteCountTxCharG = sizeof(txCharG);

				// Wait for the transfer finish, OR do something else
				LPUART_DRV_SendData(BOARD_DEBUG_UART_INSTANCE, txCharG, byteCountTxCharG);
				while (kStatus_LPUART_TxBusy == LPUART_DRV_GetTransmitStatus(BOARD_DEBUG_UART_INSTANCE, NULL)){}
				break;
			}
			
			case 'h':
			{
				SEGGER_RTT_WriteString(0, "\r\n\n+++++LPUART Transmission+++++\r\n");
				OSA_TimeDelay(100);
				SEGGER_RTT_WriteString(0, "\r\nType characters from keyboard, the board will receive and then echo them to terminal screen (reset the board to stop)\r\n");
				OSA_TimeDelay(100);
						
				// Tx Debug
				byteCountBuff = sizeof(buffStart);
				LPUART_DRV_SendData(BOARD_DEBUG_UART_INSTANCE, buffStart, byteCountBuff);
				while (kStatus_LPUART_TxBusy == LPUART_DRV_GetTransmitStatus(BOARD_DEBUG_UART_INSTANCE, NULL)){}

				// Inform user of what to do
				byteCountBuff = sizeof(bufferData1);
				LPUART_DRV_SendData(BOARD_DEBUG_UART_INSTANCE, bufferData1, byteCountBuff);
				while (kStatus_LPUART_TxBusy == LPUART_DRV_GetTransmitStatus(BOARD_DEBUG_UART_INSTANCE, NULL)){}
				// Send/receive non blocking function
		
				while(true)
				{
					rxChar = SEGGER_RTT_WaitKey();

					txChar = rxChar;
					// Wait for the transfer finish, OR do something else
					LPUART_DRV_SendData(BOARD_DEBUG_UART_INSTANCE, &txChar, 1);
				}
				break;
			}
			
			/*
			 *	Ignore naked returns.
			 */
			case '\n':
			{
				SEGGER_RTT_WriteString(0, "\r\tLet's try that again");
				break;
			}

			default:
			{
				SEGGER_RTT_printf(0, "\r\tInvalid selection '%c' !\n", key);
			}
		}	
	}
	return 0;
}
