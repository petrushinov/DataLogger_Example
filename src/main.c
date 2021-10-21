

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
    /*
    #ifdef SECRETS_IN_FLASH
        fill_in_authorization();
        FLASH_write_user_authorization();
        // FLASH_read_user_authorization();
    #endif
     */

#ifdef SECRETS_IN_FLASH
    if (is_the_FLASH_empty()) {

        fill_in_authorization();
        FLASH_write_user_authorization();
        FLASH_read_user_authorization();

    } else {
        
        FLASH_read_user_authorization();
        
    }
#endif

    while (1) {

        if (is_WIFI_connected()) {
            if (NO_ERROR == send_data_to_server()) {
                // it's the time between every measurement and sending of data 
                //to the server
                __delay_ms(5000);
            }
        } else {
            
            start_WIFI_connection();
            
        }
    }
    return 1;
}

