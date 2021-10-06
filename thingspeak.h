/* 
 * File:   thingspeak.h
 * MIT License
 * created 2021
 * Author: Tsvetan Petrushinov
 * e-mail: petrushinov@gmail.com
 * version 1.0
 */

#ifndef THINGSPEAK_H
#define	THINGSPEAK_H

extern int error;

uint8_t _WIFI_connect_to_thingspeak(uint16_t delay_milliseconds);
/*
 * @Description 
 * This function making the connection between wroom-02 (WIFI module)
 * and thingspeak.com server. If the connection has no error, the server will 
 * respond "OK" and it is will be write in "WIFI input buffer". If function 
 * find "OK" in the "WIFI input buffer", the function return "zero". If "OK" 
 * missing in "WIFI input buffer", the function will start a new attempt to 
 * connect to the server. In this moment into UART1 (service port) will 
 * write "THINGSPEAK SERVER FAILURE". 
 * 
 * @Param
 * "delay_milliseconds" - It is the time offset between sending the 
 * connection command to the server and the response from the server. 
 * 
 * @Returns 
 * return number of error or zero if no error
 */

uint8_t _WIFI_send_data_to_thingspeak(uint16_t delay_milliseconds);
/*
 * @Description 
 * This function making configuration of wroom-02 (WIFI module) for sending 
 * data. After then function send to thingspeak.com  APi-KEY  and value of 
 * sensorX variable. If the sent package is delivered, the server will respond 
 * "CLOSED". The server answer will be written in "WIFI input buffer". 
 * If "CLOSED" missing in "WIFI input buffer", the function will make a new 
 * attempt to send data to the server. Into UART1 (service port) will write 
 * "SERVER DID NOT RECEIVE THE PACKAGE". 
 * 
  @Param
 * "delay_milliseconds" - It is the time offset between sending the 
 * connection command to the server and the response from the server. 
 * 
 * @Returns 
 * return number of error or zero if no error
 */

uint8_t send_data_to_server(void);
/*
 * @Description 
 * This function call successively "_WIFI_connect_to_thingspeak()" and 
 * "_WIFI_send_data_to_thingspeak()". In this function, you must set the delay 
 * time between the sent command to the server and the response from the server.  
 * 
  @Param
 * N/A
 * 
 * 
 * @Returns 
 * This function retransmit returned value from "_WIFI_connect_to_thingspeak()" 
 * and "_WIFI_send_data_to_thingspeak()" functions  
 */
#endif	/* THINGSPEAK_H */

