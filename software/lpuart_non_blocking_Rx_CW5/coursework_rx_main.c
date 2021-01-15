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

///////////////////////////////////////////////////////////////////////////////
//  Includes
///////////////////////////////////////////////////////////////////////////////

// SDK Included Files
#include "board.h"
#include "fsl_clock_manager.h"
#include "fsl_lpuart_driver.h"

const uint8_t buffStart[]    = "\r\n++++++++++++++++ LPUART Receive +++++++++++++++++\r\n";
const uint8_t bufferData1[]  = "\r\nWait for LPUART transmission from LED\r\n";

//////////////////////////////////////////////
// 	How to view received data           //
//////////////////////////////////////////////

/*  Open PuTTY, configure Serial under Connection to be:
	Baud Rate: 9600
	Data Bits: 8
	Stop Bits: 1
	Parity	 : none
	
	Now open Serial Session, choose serial line depending the port of your device (e.g COM8) 
	In windows the port can be checked within Device Manager

	Open session, and wait to receive data
*/

int main(void)
{
    uint8_t rxChar = 0, txChar = 0;
    uint32_t byteCountBuff = 0;

    lpuart_state_t lpuartStatePtr;

    // Fill in lpuart config data
    lpuart_user_config_t lpuartConfig = {
        .clockSource     = BOARD_LPUART_CLOCK_SOURCE, /*kClockLpuartSrcIrc48M*/
        .bitCountPerChar = kLpuart8BitsPerChar, /*8-bits per char */
        .parityMode      = kLpuartParityDisabled, /* None */
        .stopBitCount    = kLpuartOneStopBit, /* 1 stop bit */
        .baudRate        = BOARD_DEBUG_UART_BAUD	/*9600*/
    };

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

    // Initialize the lpuart module with instance number and config structure
    LPUART_DRV_Init(BOARD_DEBUG_UART_INSTANCE, &lpuartStatePtr, &lpuartConfig);

    // LPUART0 Receive
    byteCountBuff = sizeof(buffStart);
    LPUART_DRV_SendData(BOARD_DEBUG_UART_INSTANCE, buffStart, byteCountBuff);
    while (kStatus_LPUART_TxBusy == LPUART_DRV_GetTransmitStatus(BOARD_DEBUG_UART_INSTANCE, NULL)){}

    // Notify user of what to do
    byteCountBuff = sizeof(bufferData1);
    LPUART_DRV_SendData(BOARD_DEBUG_UART_INSTANCE, bufferData1, byteCountBuff);
    while (kStatus_LPUART_TxBusy == LPUART_DRV_GetTransmitStatus(BOARD_DEBUG_UART_INSTANCE, NULL)){}

    // Send/receive non blocking function
    while(true)
    {
        // Wait to receive data from LED
        LPUART_DRV_ReceiveData(BOARD_DEBUG_UART_INSTANCE, &rxChar, 1);
        while (kStatus_LPUART_RxBusy == LPUART_DRV_GetReceiveStatus(BOARD_DEBUG_UART_INSTANCE, NULL)){}

        txChar = rxChar;
        // Display data to PC (PuTTY Terminal)
        LPUART_DRV_SendData(BOARD_DEBUG_UART_INSTANCE, &txChar, 1);
    }
  return 0;
}

/*******************************************************************************
 * EOF
 ******************************************************************************/

