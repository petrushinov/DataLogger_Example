/* 
 * File: UART.h 
 * MIT License
 * created 2021
 * Author: Tsvetan Petrushinov
 * e-mail: petrushinov@gmail.com
 * version 1.0
 */

#ifndef UART_H
#define	UART_H

#include <stdint.h>

#define INPUT_BUFFER_SIZE 100

extern uint8_t inputBufferUpdated;
extern char inputBufer [];

void UART_char_write(char *txData , uint8_t uartPort);
/*
 * @Description 
 * This function send the string of character to one of the four UART PORTs. 
 * NOTE: in this example I chose PIC24FJ256GA106.
 * 
  @Param
 * *txData - string to send
 * uartPort - port number (1,2,3 or 4)
 * 
 * @Returns 
 * N/A
 */
#endif	/* UART_H */

