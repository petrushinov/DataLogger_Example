/* 
 * File:   secret.h
 * MIT License
 * created 2021
 * Author: Tsvetan Petrushinov
 * e-mail: petrushinov@gmail.com
 * version 1.0
 */

#ifndef SECRET_H
#define	SECRET_H

#include "param.h"

#ifdef SECRETS_IN_CODE

#define SSID "......."  // ssid WIFI name
#define WIFI_PASS "......" //WIFI password
#define SERVER_ADDRESS "184.106.153.149" // server IP or link
#define WRITE_API_KEY "GET /update?api_key=..........&field1=" //Write API Key: Use this key to write data to a channel. 
#define Read_CH_STATUS "GET channels/........../status.json?api_key=............" //Read Chanel Status Updates
#define SERVER_PORT "80"

#endif

#ifdef SECRETS_IN_FLASH

#define SSID_SIZE 20  // ssid WIFI name
#define WIFI_PASS_SIZE 20 //WIFI password
#define SERVER_ADDRESS_SIZE 20 // server IP or link
#define WRITE_API_KEY_SIZE 60 //Write API Key: Use this key to write data to a channel. 
#define READ_CH_STATUS_SIZE 70 //Read Chanel Status Updates
#define SERVER_PORT_SIZE 10
#define AUTORIZATION_BUFF_SIZE (SSID_SIZE + WIFI_PASS_SIZE + SERVER_ADDRESS_SIZE + WRITE_API_KEY_SIZE + READ_CH_STATUS_SIZE + SERVER_PORT_SIZE)

#endif

#endif	/* SECRET_H */

