/* 
 * File:   authorization.h
 * MIT License
 * created 2021
 * Author: Tsvetan Petrushinov
 * e-mail: petrushinov@gmail.com
 * version 1.0
 */

#ifndef AUTHORIZATION_H
#define	AUTHORIZATION_H

#include "secret.h"

#ifdef SECRETS_IN_FLASH
#define STARTING_FLASH_ADDRESS 0x2A7F0
#define END_FLASH_ADDRESS 0x2ABF7

#ifdef SECRETS_IN_FLASH
extern char authorizationBuff [];
extern char authorizationTemp [];
#endif

void FLASH_write_user_authorization (void);
/*
 * @Description 
 * This function after call deletes 1031 addresses back from the final address. 
 * After then the function unites every 3 bytes from "authorizationBuff"  in 
 * one 32 bit variable. After then the function writes the variable in the 
 * corresponding  FLASH address.
 * NOTE: in this example I chose PIC24FJ256GA106. In this MCU each FLASH memory 
 * address contains 24bit banks for the user.
 * 
  @Param
 * N/A
 * 
 * @Returns 
 * N/A
 */

void FLASH_read_user_authorization (void);
/*
 * @Description 
 * This function after call reads FLASH address which has a 24bit record 
 * or 3 bytes. Every byte is a character and every character is copied in the 
 * next element of "authorizationBuff"
 *  NOTE: in this example I chose PIC24FJ256GA106. In this MCU each FLASH memory 
 * address contains 24bit banks for the user.
 * 
  @Param
 * N/A
 * 
 * @Returns 
 * N/A
 */

void _fill_authorization_buff (char * add);
/*
 * @Description 
 *  This function expects enter button will be press, after then function added 
 * a marker/key word to the "authorizationBuff", after then the input word from the 
 * terminal is writing to the "authorizationBuff". 
 * 
  @Param
 * marker/key word
 * 
 * @Returns 
 * N/A
 */

void fill_in_authorization(void);
/*
 * @Description 
 * This function printing in UART1(service port) instruction for input 
 * authorization data (SSID, PASS, Server address, Server port and etc.)  
 * After every print this function call  "_fill_authorization_buff()".
 * 
  @Param
 * N/A
 * 
 * @Returns 
 * N/A
 */

char *find_word (char *keyWord, char *string);
/*
 * @Description 
 * Function find keyword in string.
 * 
  @Param
 * *keyWord - string to be searched
 * *string - a string in which to search
 * 
 * @Returns 
 * return pointer after the key word.
 */

void fill_authorization_temp (char *keyWord);
/*
 * @Description 
 * The function finds a keyword in "authorizationBuff" and copies the next  
 * elements in  "authorizationTemp" while element in "authorizationBuff" is 
 * different from "carriage return"
 * 
  @Param
 * *keyWord - string to be searched
 * 
 * @Returns 
 * N/A
 */

#endif
#endif	


