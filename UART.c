/* 
 * File:   UART.c
 * MIT License
 * created 2021
 * Author: Tsvetan Petrushinov
 * e-mail: petrushinov@gmail.com
 * version 1.0
 */

#include "UART.h"
#include <xc.h>
#include <libpic30.h> 



uint8_t inputBufferUpdated = 0;
char inputBufer [INPUT_BUFFER_SIZE];


void UART_char_write(char *txData, uint8_t uartPort) {

    while (*txData != 0) {

        if (uartPort == 1) {
            while (!(U1STAbits.TRMT)) {
            }
            U1TXREG = *txData;
        } else if (uartPort == 2) {
            while (!(U2STAbits.TRMT)) {
            }
            U2TXREG = *txData;
        } else if (uartPort == 3) {
            while (!(U3STAbits.TRMT)) {
            }
            U3TXREG = *txData;
        } else {
            while (!(U4STAbits.TRMT)) {
            }
            U4TXREG = *txData;
        }
        txData++;
    }
}
