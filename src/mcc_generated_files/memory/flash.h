/**
  @Company
    Microchip Technology Inc.

  @Summary
    Lower level peripheral API for the flash module using PIC24 / dsPIC33 / PIC32MM MCUs.

  @Description
    Lower level peripheral API for the flash module using PIC24 / dsPIC33 / PIC32MM MCUs.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ256GA106
        Driver Version    :  1.00
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB 	          :  MPLAB X v5.45
*/

/*
    (c) 2020 Microchip Technology Inc. and its subsidiaries. You may use this
    software and any derivatives exclusively with Microchip products.

    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED
    WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A
    PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION
    WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.

    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
    BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO THE
    FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS IN
    ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF ANY,
    THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.

    MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
    TERMS.
*/

#ifndef MEMORY_H
#define MEMORY_H

#include <xc.h>
#include <stdint.h>
#include <stdbool.h>

#define FLASH_ERASE_PAGE_SIZE_IN_INSTRUCTIONS 512U
#define FLASH_WRITE_ROW_SIZE_IN_INSTRUCTIONS 64U

#define FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS (FLASH_ERASE_PAGE_SIZE_IN_INSTRUCTIONS * 2U)
#define FLASH_WRITE_ROW_SIZE_IN_PC_UNITS (FLASH_WRITE_ROW_SIZE_IN_INSTRUCTIONS * 2U)
 
#define FLASH_UNLOCK_KEY 0x00AA0055
#define FLASH_ERASE_PAGE_MASK (~((FLASH_ERASE_PAGE_SIZE_IN_INSTRUCTIONS*2U) - 1U)) 

void     FLASH_Unlock(uint32_t  key);
void     FLASH_Lock(void);

/* FLASH_ErasePage(uint32_t adddress ):  
 *                     Address must be page aligned.  
 *                     Use the FLASH_GetErasePageAddress() function
 *                     to get the page for a specific memory address. */
bool     FLASH_ErasePage(uint32_t address);

/* The address in the Read and Write word functions below must be even */
uint32_t FLASH_ReadWord24(uint32_t address);
uint16_t FLASH_ReadWord16(uint32_t address);

bool     FLASH_WriteWord24(uint32_t address, uint32_t Data);
bool     FLASH_WriteWord16(uint32_t address, uint16_t Data);

/* Program the flash one row at a time. */

/* FLASH_WriteRow24: Writes a single row of data from the location given in *data to
 *                   the flash location in address.  Since the flash is only 24 bits wide
 *                   all data in the upper 8 bits of the source will be lost .  
 *                   The address in *data must be row aligned.
 *                   returns true if successful */
bool     FLASH_WriteRow24(uint32_t address, uint32_t *data);


/* FLASH_WriteRow16: Writes a single row of data from the location in given in *data to
 *                   to the flash location in address. Each 16 bit source data 
 *                   word is stored in the lower 16 bits of each flash entry and the 
 *                   upper 8 bits of the flash is not programmed. 
 *                   The address in *data must be row aligned.
 *                   returns true if successful */
bool     FLASH_WriteRow16(uint32_t address, uint16_t *data);

uint16_t FLASH_GetErasePageOffset(uint32_t address);
uint32_t FLASH_GetErasePageAddress(uint32_t address);

#endif	/* FLASH_H */

