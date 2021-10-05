/* 
 * File:   WIFI.c
 * MIT License
 * created 2021
 * Author: Tsvetan Petrushinov
 * e-mail: petrushinov@gmail.com
 * version 1.0
 */

#define    FCY    10000000UL

#include "UART_buffer.h"
#include <libpic30.h>
#include "UART.h"
#include "secret.h"
#include <string.h>
#include "AT_command.h"
#include "WIFI.h"
#include "global_macros.h"
#include "authorization.h"
#include "thingspeak.h"

uint8_t start_WIFI_connection(void) {

    error = _set_WIFI_mode(ONE_SECOND);
    if (NO_ERROR != error) {
        return error;
    }
    return error = _connect_to_AP(FOUR_SECONDS);
}

uint8_t _set_WIFI_mode(uint16_t delay_milliseconds) {
    uint8_t j = 0;

    do {
        UART_char_write(WIFI_MODE nlcr, WIFI_PORT);
        __delay_ms(delay_milliseconds);
        j++;
    } while (false == find_word_WIFI_input_buff("OK") && j < 3);

    if (j == 3) {
        UART_char_write("WIFI MODULE ERROR\r\n", SERVICE_UART_PORT);
        return WIFI_MODULE_ERROR;
    }
    return NO_ERROR;
}

#ifdef SECRETS_IN_CODE

uint8_t _connect_to_AP(uint16_t delay_milliseconds) {

    clear_buff_out();

    strcat(buffOut, CONNECT_TO_AP);
    strcat(buffOut, quote);
    strcat(buffOut, SSID);
    strcat(buffOut, quote);
    strcat(buffOut, COMMA);
    strcat(buffOut, quote);
    strcat(buffOut, WIFI_PASS);
    strcat(buffOut, quote);
    strcat(buffOut, nlcr);

    uint8_t j = 0;

    do {
        UART_char_write(buffOut, WIFI_PORT);
        __delay_ms(delay_milliseconds);
        j++;
    } while (false == find_word_WIFI_input_buff("OK") && j < 3);

    if (j == 3) {
        UART_char_write("WIFI CONNECTION ERROR\r\n", SERVICE_UART_PORT);
        return WIFI_CONNECTION_ERROR;
    }
    WIFI_clear_input_buff();
    return NO_ERROR;
}
#endif

#ifdef SECRETS_IN_FLASH

uint8_t _connect_to_AP(uint16_t delay_milliseconds) {

      __C30_UART = 2;
    
    clear_buff_out();

    strcat(buffOut, CONNECT_TO_AP);
    strcat(buffOut, quote);
    fill_authorization_temp("SSID&");
    strcat(buffOut, authorizationTemp);
    strcat(buffOut, quote);
    strcat(buffOut, COMMA);
    strcat(buffOut, quote);
    fill_authorization_temp("PASS&");
    strcat(buffOut, authorizationTemp);
    strcat(buffOut, quote);
    strcat(buffOut, nlcr);

    
    
    uint8_t j = 0;

    do {
        UART_char_write(buffOut, WIFI_PORT);
        __delay_ms(delay_milliseconds);
        j++;
    } while (false == find_word_WIFI_input_buff("OK") && j < 3);

    if (j == 3) {
        UART_char_write("WIFI CONNECTION ERROR\r\n", SERVICE_UART_PORT);
        return WIFI_CONNECTION_ERROR;
    }
    WIFI_clear_input_buff();
    return NO_ERROR;
}

#endif
