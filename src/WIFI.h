/* 
 * File:   WIFI.h
 * MIT License
 * created 2021
 * Author: Tsvetan Petrushinov
 * e-mail: petrushinov@gmail.com
 * version 1.0
 */

#ifndef WIFI_H
#define	WIFI_H

uint8_t _connect_to_AP(uint16_t delay_milliseconds);
/*
 * @Description 
 * This function makes the connection between wroom-02 (WIFI module)
 * and Access Point. If the connection has no error, the wroom-02 will 
 * respond "OK" and it is will be write in "WIFI input buffer". If the function 
 * finds "OK" in the "WIFI input buffer", the function return "zero". If "OK" 
 * missing in "WIFI input buffer", the function will start a new attempt to 
 * connect to the Access Point. In this moment into UART1 (service port) will 
 * write "WIFI CONNECTION ERROR". 
 * 
 * @Param
 * "delay_milliseconds" - It is the time offset between sending the 
 * connection command to the wroom-02 and the response from the wroom-02. 
 * 
 * @Returns 
 * return number of error or zero if no error
 */

uint8_t _set_WIFI_mode(uint16_t delay_milliseconds);
/*
 * @Description 
 * This function makes wroom-02 (WIFI module) work as a client.
 * The wroom-02 will respond "OK" and it is will be written in "WIFI input buffer".
 * If the function finds "OK" in the "WIFI input buffer", the function return "zero".
 * If "OK" missing in "WIFI input buffer", the function will start a new attempt to 
 * set working mode. In this moment into UART1 (service port) will 
 * write "WIFI MODULE ERROR". 
 * 
 * @Param
 * "delay_milliseconds" - It is the time offset between sending the 
 * AT command to the wroom-02 and the response from the wroom-02. 
 * 
 * @Returns 
 * return number of error or zero if no error
 */

uint8_t start_WIFI_connection(void);
/*
 * @Description 
 * This function call successively "_set_WIFI_mode()" and 
 * "_connect_to_AP()". In this function, you must set the delay 
 * time between the sent command to the wroom-02 (WIFI module) and the response 
 * from the wroom-2.  
 * 
  @Param
 * N/A
 * 
 * @Returns 
 * This function retransmit returned value from "_set_WIFI_mode()" 
 * and "_connect_to_AP()" functions  
 */

bool is_WIFI_connected(void);


#endif	/* WIFI_H */
