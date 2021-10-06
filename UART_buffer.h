/* 
 * File:   UARTBuffer.h
 * MIT License
 * created 2021
 * Author: Tsvetan Petrushinov
 * e-mail: petrushinov@gmail.com
 * version 1.0
 */

#ifndef UARTBUFFER_H
#define	UARTBUFFER_H

#include <xc.h>
#include <stdio.h>
#include <stdbool.h>

#define OUTPUT_UART_BUFF_SIZE 256
#define INPUT_WIFI_BUFF_SIZE 256
#define INPUT_SERVICE_BUFF_SIZE 200

extern char inputServiceBuff [];
extern char inputWIFIBuff [];
extern char buffOut [];
extern char quote[2]; // ascii = (")

void WIFI_input_buff(void);
/*
 * @Description 
 * This function write every received byte in "inputWIFIBuff" and copy  
 * received byte in UART1 (service port) output register. if the buffer is full,
 * the function will start writing to the buffer from the beginning without 
 * deleting all elements in it. This is a queue that after overflow does not 
 * stop but continues to record as long as there is incoming data.
 * 
  @Param
 * N/A
 * @Returns 
 * N/A
 */

void WIFI_read_input_buff(void);
/*
 * @Description 
 * This function read "inputWIFIBuff[]" and print data to UART1 (service port). 
 * After reading every element is deleted. This function is directly related to 
 * "WIFI_input_buff()". The function prints the entire queue "inputWIFIBuff[]".
 * 
  @Param
 * N/A
 * @Returns 
 * N/A
 */

void clear_buff_out(void);
/*
 * @Description 
 * The function deletes all "buffOut[]" elements.
 * 
  @Param
 * N/A
 * @Returns 
 * N/A
 */

char *find_word_WIFI_input_buff(char *string);
/*
 * @Description 
 * The function finding the keyword in the queue "inputWIFIBuff[]" and return 
 * a pointer after the end keyword.
 * 
  @Param
 * Search keyword
 * @Returns 
 * Pointer after the end keyword.
 */

void WIFI_clear_input_buff(void);
/*
 * @Description 
 * The function deletes all "inputWIFIBuff[]" elements.
 * 
  @Param
 * N/A
 * @Returns 
 * N/A
 */

void SERVICE_PORT_input_buff(void);
/*
 * @Description 
 * This function write every received byte via UART1 (service port) in 
 * "inputServiceBuff[]". if the buffer is full, the function will start writing 
 * to the buffer from the beginning without deleting all elements in it. 
 * This is a queue that after overflow does not stop but continues to record as 
 * long as there is incoming data.
 * 
  @Param
 * N/A
 * @Returns 
 * N/A
 */

void SERVICE_PORT_read_input_buff(void);
/*
 * @Description 
 * This function read "inputServiceBuff[]" and print data to UART2. 
 * After reading every element is deleted. This function is directly related to 
 * "SERVICE_PORT_input_buff()". The function prints the entire queue
 * "inputServiceBuff[]".
 * 
  @Param
 * N/A
 * @Returns 
 * N/A
 */

void SERVICE_PORT_clear_input_buff(void);
/*
 * @Description 
 * The function deletes all "inputServiceBuff[]" elements.
 * 
  @Param
 * N/A
 * @Returns 
 * N/A
 */
#endif	/* UARTBUFFER_H */
