/* 
 * File:   AT_command.h
 * MIT License
 * created 2021
 * Author: Tsvetan Petrushinov
 * e-mail: petrushinov@gmail.com
 * version 1.0
 */

#ifndef AT_COMMAND_H
#define	AT_COMMAND_H

#define nlcr "\r\n"
// Basic AT Commands************************************************************
#define WIFI_STATUS "AT+CIPSTATUS" //Gets the connection status
#define TEST "AT"
#define RESTART "AT+RST"
#define TRANSMITER_POWER "AT+RFPOWER"
// WIFI Commands****************************************************************
#define WIFI_MODE "AT+CWMODE_CUR=1" //Sets the Wi-Fi mode (Station/AP/Station+AP); configuration not saved in the flash.
#define CONNECT_TO_AP "AT+CWJAP=" //Connects to an AP; configuration not saved in the flash.
#define LIST_AP "AT+CWLAP" // Lists available APs.
#define DISCCONECT_FROM_AP "AT+CWQAP" //Disconnects from an AP.
#define CONFIG_SOFT_AP "AT+CWSAP_CUR" //Configures the ESP8266 SoftAP; Configuration Not Saved in the Flash
#define EN_DHSP "AT+CWDHCP_CUR" //Enables/Disables DHCP; configuration not saved in the flash.
#define IP_RANGE "AT+CWDHCPS_CUR"//Sets the IP range of the DHCP server; configuration not saved in the flash.
#define SET_MAC_SOFT_AP "AT+CIPAPMAC_CUR" //Sets the MAC address of the ESP8266 SoftAP; configuration not saved in the flash.
#define SET_IP_SOFT_AP "AT+CIPAP_CUR" //Sets the IP address of ESP8266 SoftAP; configuration not saved in the flash.
#define SET_HOST_NAME_STATION "AT+CWHOSTNAME" //Sets the host name of the ESP8266 Station.
#define SEND_DATA_LENGTH "AT+CIPSEND=" //to configure the data length in normal transmission mode.
#define SEND_DATA "AT+CIPCLOSE" //Closes the TCP/UDP/SSL Connection
#define COMMA ","


#endif	/* AT_COMMAND_H */

