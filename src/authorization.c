/* 
 * File:   authorization.c
 * MIT License
 * created 2021
 * Author: Tsvetan Petrushinov
 * e-mail: petrushinov@gmail.com
 * version 1.0
 */

#define    FCY    10000000UL

#include <libpic30.h>
#include "mcc_generated_files/memory/flash.h"
#include "authorization.h"
#include <xc.h>
#include <stdio.h>
#include <string.h>
#include "UART.h"
#include "global_macros.h"
#include "UART_buffer.h"
#include "secret.h"

#ifdef SECRETS_IN_FLASH

char authorizationBuff [AUTORIZATION_BUFF_SIZE];
char authorizationTemp [100];

void fill_in_authorization(void) {
    uint16_t j;
    for (j = 0; j <= AUTORIZATION_BUFF_SIZE; j++) {
        authorizationBuff [j] = 0;
    }

    UART_char_write("ENTER SSID\r\n", SERVICE_UART_PORT);
    _fill_authorization_buff("SSID&");

    UART_char_write("ENTER PASS\r\n", SERVICE_UART_PORT);
    _fill_authorization_buff("PASS&");

    UART_char_write("ENTER SERVER ADDRESS\r\n", SERVICE_UART_PORT);
    _fill_authorization_buff("ADDRESS&");

    UART_char_write("ENTER APY-KEY\r\n", SERVICE_UART_PORT);
    _fill_authorization_buff("APY-KEY&");

    UART_char_write("ENTER Read Chanel Status\r\n", SERVICE_UART_PORT);
    _fill_authorization_buff("CHSTATUS&");

    UART_char_write("ENTER SERVER PORT\r\n", SERVICE_UART_PORT);
    _fill_authorization_buff("PORT&");
}

void _fill_authorization_buff(char * add) {
    char enter[] = {13, 0}; // "carriage return" ascii

    while (0 == strstr(inputServiceBuff, enter)) {
        __delay_ms(50);
    }
    strcat(authorizationBuff, add);
    strcat(authorizationBuff, inputServiceBuff);
    SERVICE_PORT_clear_input_buff();
}

void FLASH_write_user_authorization(void) {
    uint16_t len = 0;
    uint16_t j = 0;
    uint32_t flashAddress = STARTING_FLASH_ADDRESS;
    uint32_t writeTemp = 0;

    _erase_flash(END_FLASH_ADDRESS); // erase 1031 addresses back

    len = strlen(authorizationBuff);

    while (j < len) {

        writeTemp = (uint8_t) authorizationBuff[j];
        j++;
        writeTemp = writeTemp << 8;
        writeTemp = writeTemp | (uint8_t) authorizationBuff[j];
        j++;
        writeTemp = writeTemp << 8;
        writeTemp = writeTemp | (uint8_t) authorizationBuff[j];
        j++;
        _write_flash_word24(flashAddress, writeTemp);
        flashAddress += 2;
    }
    if (j == len) {
        _write_flash_word24(flashAddress, 0);
    }
    flashAddress = STARTING_FLASH_ADDRESS;
}

void FLASH_read_user_authorization(void) {
    uint32_t flashAddress = STARTING_FLASH_ADDRESS;
    uint32_t readTemp = 0;
    uint16_t j = 0;
    char readBuff [100];
    uint8_t k = 0;

    for (; j <= AUTORIZATION_BUFF_SIZE; j++) {
        authorizationBuff[j] = 0;
    }

    for (; k <= 100; k++) {
        readBuff[k] = 0;
    }
    k = 0;

    readTemp = FLASH_ReadWord24(flashAddress);

    while (readTemp != 0x00FFFFFF) {
        readBuff [k] = readTemp >> 16;
        k++;
        readBuff [k] = readTemp >> 8;
        k++;
        readBuff [k] = readTemp;
        k = 0;

        strcat(authorizationBuff, readBuff);

        flashAddress += 2;
        readTemp = FLASH_ReadWord24(flashAddress);
    }
    flashAddress = STARTING_FLASH_ADDRESS;
}

char *find_word(char *keyWord, char *string) {
    char length = 0;

    length = strlen(keyWord);

    return strstr(string, keyWord) + length;
}

void fill_authorization_temp(char *keyWord) {
    char enter = 13; // "carriage return" ascii
    char *ptr = 0;
    uint8_t j = 0;

    for (; j <= 100; j++) {
        authorizationTemp [j] = 0;
    }
    j = 0;

    ptr = find_word(keyWord, authorizationBuff);

    for (; *ptr != enter; j++, ptr++) {
        authorizationTemp [j] = *ptr;
    }
}

bool is_the_FLASH_empty(void) {

    if (0xFFFFFF == FLASH_ReadWord24(STARTING_FLASH_ADDRESS)) {
        return true;
    } else {
        return false;
    }
}
#endif
