#define    FCY    10000000UL

#include "mcc_generated_files/system.h"
#include <xc.h>
#include <libpic30.h> 
#include <stdio.h>
#include "UART.h"
#include "UART_buffer.h"
#include <stdbool.h>
#include <string.h>
#include "AT_command.h"
#include "secret.h"
#include <stdlib.h>
#include "WIFI.h"
#include "thingspeak.h"
#include "mcc_generated_files/memory/flash.h"
#include "authorization.h"
#include "global_macros.h"
#include "measurement.h"

int main(void) {

    // initialize the device
    SYSTEM_Initialize();

   
    
#ifdef SECRETS_IN_FLASH
    fill_in_authorization();
    start_WIFI_connection();
    send_data_to_server();
#endif

#ifdef SECRETS_IN_CODE
    start_WIFI_connection();
    //send_data_to_server();
#endif

    while (1) {
        
        send_data_to_server();

        __delay_ms(10000);
    }
    return 1;
}

