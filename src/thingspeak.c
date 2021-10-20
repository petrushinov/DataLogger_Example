/* 
 * File:   thingspeak.c
 * MIT License
 * created 2021
 * Author: Tsvetan Petrushinov
 * e-mail: petrushinov@gmail.com
 * version 1.0
 */

#define    FCY    10000000UL

#include "UART.h"
#include "thingspeak.h"
#include "UART_buffer.h"
#include "secret.h"
#include "AT_command.h"
#include <libpic30.h>
#include <string.h>
#include "global_macros.h"
#include "authorization.h"
#include "measurement.h"

int error = 0;

uint8_t send_data_to_server(void) {
    error = _WIFI_connect_to_thingspeak(ONE_SECOND);
    if (error != NO_ERROR) {
        return error;
    }
    return error = _WIFI_send_data_to_thingspeak(TWO_SECONDS);
}

#ifdef SECRETS_IN_CODE

uint8_t _WIFI_connect_to_thingspeak(uint16_t delay_milliseconds) {

    clear_buff_out();

    strcat(buffOut, "AT+CIPSTART=");
    strcat(buffOut, quote);
    strcat(buffOut, "TCP");
    strcat(buffOut, quote);
    strcat(buffOut, COMMA);
    strcat(buffOut, quote);
    strcat(buffOut, SERVER_ADDRESS);
    strcat(buffOut, quote);
    strcat(buffOut, COMMA);
    strcat(buffOut, SERVER_PORT);
    strcat(buffOut, nlcr);

    uint8_t j = 0;

    do {
        UART_char_write(buffOut, WIFI_PORT);
        __delay_ms(delay_milliseconds);
        j++;
    } while (false == find_word_WIFI_input_buff("OK") && j < 4);

    if (j == 4) {
        UART_char_write("THINGSPEAK SERVER FAILURE\r\n", SERVICE_UART_PORT);
        return THINGSPEAK_SERVER_FAILURE;
    }
    WIFI_clear_input_buff();
    return NO_ERROR;

}

uint8_t _WIFI_send_data_to_thingspeak(uint16_t delay_milliseconds) {

    clear_buff_out();

    char dataLength [20];
    uint16_t length;

    length = sprintf(buffOut, "%s%d\r\n", WRITE_API_KEY, ADC1_get_value(SENSOR1));

    sprintf(dataLength, "%s%d\r\n", SEND_DATA_LENGTH, length);

    uint8_t j = 0;

    do {
        UART_char_write(dataLength, WIFI_PORT);
        __delay_ms(delay_milliseconds);

        UART_char_write(buffOut, WIFI_PORT);
        __delay_ms(delay_milliseconds);

        j++;
    } while (false == find_word_WIFI_input_buff("CLOSED") && j < 4);

    if (j == 4) {
        UART_char_write("SERVER DID NOT RECEIVE THE PACKAGE\r\n", SERVICE_UART_PORT);
        return SERVER_DID_NOT_RECEIVE_THE_PACKAGE;
    }
    return NO_ERROR;
}
#endif

#ifdef SECRETS_IN_FLASH

uint8_t _WIFI_connect_to_thingspeak(uint16_t delay_milliseconds) {

    clear_buff_out();

    strcat(buffOut, "AT+CIPSTART=");
    strcat(buffOut, quote);
    strcat(buffOut, "TCP");
    strcat(buffOut, quote);
    strcat(buffOut, COMMA);
    strcat(buffOut, quote);
    fill_authorization_temp("ADDRESS&");
    strcat(buffOut, authorizationTemp);
    strcat(buffOut, quote);
    strcat(buffOut, COMMA);
    fill_authorization_temp("PORT&");
    strcat(buffOut, authorizationTemp);
    strcat(buffOut, nlcr);

    uint8_t j = 0;

    do {
        UART_char_write(buffOut, WIFI_PORT);
        __delay_ms(delay_milliseconds);
        j++;
    } while (false == find_word_WIFI_input_buff("OK") && j < 4);

    if (j == 4) {
        UART_char_write("THINGSPEAK SERVER FAILURE\r\n", SERVICE_UART_PORT);
        return THINGSPEAK_SERVER_FAILURE;
    }
    WIFI_clear_input_buff();
    return NO_ERROR;

}

uint8_t _WIFI_send_data_to_thingspeak(uint16_t delay_milliseconds) {

    clear_buff_out();

    char dataLength [20];
    uint16_t length;

    fill_authorization_temp("APY-KEY&");

    length = sprintf(buffOut, "%s%d\r\n", authorizationTemp, ADC1_get_value(SENSOR1));

    sprintf(dataLength, "%s%d\r\n", SEND_DATA_LENGTH, length);

    uint8_t j = 0;

    do {
        UART_char_write(dataLength, WIFI_PORT);
        __delay_ms(delay_milliseconds);

        UART_char_write(buffOut, WIFI_PORT);
        __delay_ms(delay_milliseconds);

        j++;
    } while (false == find_word_WIFI_input_buff("CLOSED") && j < 4);

    if (j == 4) {
        UART_char_write("SERVER DID NOT RECEIVE THE PACKAGE\r\n", SERVICE_UART_PORT);
        return SERVER_DID_NOT_RECEIVE_THE_PACKAGE;
    }
    return NO_ERROR;
}
#endif
