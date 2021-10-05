/* 
 * File:   UART_buffer.c
 * MIT License
 * created 2021
 * Author: Tsvetan Petrushinov
 * e-mail: petrushinov@gmail.com
 * version 1.0
 */

#define    FCY    10000000UL

#include "UART_buffer.h"
#include <string.h>
#include "mcc_generated_files/uart2.h"
#include "global_macros.h"
#include <libpic30.h> 


char inputWIFIBuff [INPUT_WIFI_BUFF_SIZE];
char inputServiceBuff [INPUT_SERVICE_BUFF_SIZE];
uint16_t topWIFIQueue = 0;
uint16_t topWIFIQueueLast = 0;
uint16_t endWIFIQueue = 0;
uint16_t topServiceQueue = 0;
uint16_t topServiceQueueLast = 0;
uint16_t endServiceQueue = 0;
uint8_t overflowedWIFIBuff = false;
uint8_t overflowedServiceBuff = false;
char buffOut [OUTPUT_UART_BUFF_SIZE];
char quote[2] = {34, 0}; // ascii = (")



void UART1_Write(uint8_t byte);

void SERVICE_PORT_input_buff(void) {
    uint8_t inServiceTemp = 0;
    //URXDA: Receive Buffer Data Available bit (read-only)
    while ((U1STAbits.URXDA == 1)) {
        inServiceTemp = U1RXREG;

        if (topServiceQueue < INPUT_SERVICE_BUFF_SIZE) {
            inputServiceBuff[topServiceQueue] = inServiceTemp;
            topServiceQueue++;
            inputServiceBuff[topServiceQueue] = 0;

        } else {
            topServiceQueue = 0;
            overflowedServiceBuff = true;
            inputServiceBuff[topServiceQueue] = inServiceTemp;
            topServiceQueue++;
            inputServiceBuff[topServiceQueue] = 0;
        }
    }
}

void SERVICE_PORT_read_input_buff(void) {

    if (overflowedServiceBuff == true) {
        for (endServiceQueue = topServiceQueue; endServiceQueue <= INPUT_WIFI_BUFF_SIZE; endServiceQueue++) {
            UART2_Write(inputServiceBuff[endServiceQueue]);
            inputServiceBuff[endServiceQueue] = 0;
        }
        overflowedServiceBuff = false;
    }
    if (overflowedServiceBuff == false) {
        for (endServiceQueue = 0; endServiceQueue < topServiceQueue; endServiceQueue++) {
            UART2_Write(inputServiceBuff[endServiceQueue]);
            inputServiceBuff[endServiceQueue] = 0;
        }
    }
}

// every received byte going in "inputWIFIBuff" and copy in UART output register

void WIFI_input_buff(void) {
    uint8_t inWIFITemp = 0;
    //URXDA: Receive Buffer Data Available bit (read-only)
    while ((U4STAbits.URXDA == 1)) {
        inWIFITemp = U4RXREG;
        //input data go direct to UART1 register (U1TXREG)
        U1TXREG = inWIFITemp;

        if (topWIFIQueue < INPUT_WIFI_BUFF_SIZE) {
            inputWIFIBuff[topWIFIQueue] = inWIFITemp;
            topWIFIQueue++;
            inputWIFIBuff[topWIFIQueue] = 0;
        } else {
            topWIFIQueue = 0;
            overflowedWIFIBuff = true;
            inputWIFIBuff[topWIFIQueue] = inWIFITemp;
            topWIFIQueue++;
            inputWIFIBuff[topWIFIQueue] = 0;
        }
    }
}

// after reading element is deleted

void WIFI_read_input_buff(void) {

    if (overflowedWIFIBuff == true) {
        for (endWIFIQueue = topWIFIQueue; endWIFIQueue <= INPUT_WIFI_BUFF_SIZE; endWIFIQueue++) {
            UART1_Write(inputWIFIBuff[endWIFIQueue]);
            inputWIFIBuff[endWIFIQueue] = 0;
        }
        overflowedWIFIBuff = false;
    }
    if (overflowedWIFIBuff == false) {
        for (endWIFIQueue = 0; endWIFIQueue < topWIFIQueue; endWIFIQueue++) {
            UART1_Write(inputWIFIBuff[endWIFIQueue]);
            inputWIFIBuff[endWIFIQueue] = 0;
        }
    }
}

void clear_buff_out(void) {
    uint16_t j;
    for (j = 0; j <= OUTPUT_UART_BUFF_SIZE; j++) {
        buffOut[j] = 0;
    }
}

void WIFI_clear_input_buff(void) {
    uint16_t j;
    for (j = 0; j <= INPUT_WIFI_BUFF_SIZE; j++) {
        inputWIFIBuff[j] = 0;
    }
    topWIFIQueue=0;
}

void SERVICE_PORT_clear_input_buff(void) {
    uint16_t j;
    for (j = 0; j <= INPUT_SERVICE_BUFF_SIZE; j++) {
        inputServiceBuff[j] = 0;
    }
    topServiceQueue=0;
}

// function finding the keyword in the Queue and return a pointer after the end word

char *find_word_WIFI_input_buff(char *string) {

    int t = 0;
    uint16_t length = 0;
    uint16_t tempEndQueue = 0;
    char tempBuff [20];
    uint8_t j = 0;

    for (j = 0; j < 20; j++) {
        tempBuff[j] = 0;
    }
    j = 0;

    length = strlen(string);
    t = (topWIFIQueue - length) - 2;

    if (t < 0) {

        tempEndQueue = INPUT_WIFI_BUFF_SIZE + t;

        for (; tempEndQueue < INPUT_WIFI_BUFF_SIZE; tempEndQueue++, j++) {
            tempBuff [j] = inputWIFIBuff[tempEndQueue];
        }
    } else if (t >= 0) {
        tempEndQueue = t;

        for (; tempEndQueue < topWIFIQueue - 2; tempEndQueue++, j++) {
            tempBuff [j] = inputWIFIBuff[tempEndQueue];
        }
    }

    char *ptr = 0;
    ptr = strstr(tempBuff, string);

    if (ptr == 0) {
        return ptr;
    } else {
        return ptr + length;
    }
}

