;/*******************************************************************************
;  Flash Memory Primitives Library
;
;  Summary:
;    Assembly language for Flash Memory Primitives Library
;
;  Description:
;    Basic firmware functions needed to use the flash
;    
;
;*******************************************************************************/
;
;/*******************************************************************************
;  Copyright (C) 2018 Microchip Technology Inc.
;
;  MICROCHIP SOFTWARE NOTICE AND DISCLAIMER:  You may use this software, and any
;  derivatives created by any person or entity by or on your behalf, exclusively
;  with Microchip's products.  Microchip and its licensors retain all ownership
;  and intellectual property rights in the accompanying software and in all
;  derivatives here to.
;
;  This software and any accompanying information is for suggestion only.  It
;  does not modify Microchip's standard warranty for its products.  You agree
;  that you are solely responsible for testing the software and determining its
;  suitability.  Microchip has no obligation to modify, test, certify, or
;  support the software.
;
;  THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER
;  EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED
;  WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A PARTICULAR
;  PURPOSE APPLY TO THIS SOFTWARE, ITS INTERACTION WITH MICROCHIP'S PRODUCTS,
;  COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.
;
;  IN NO EVENT, WILL MICROCHIP BE LIABLE, WHETHER IN CONTRACT, WARRANTY, TORT
;  (INCLUDING NEGLIGENCE OR BREACH OF STATUTORY DUTY), STRICT LIABILITY,
;  INDEMNITY, CONTRIBUTION, OR OTHERWISE, FOR ANY INDIRECT, SPECIAL, PUNITIVE,
;  EXEMPLARY, INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, FOR COST OR EXPENSE OF
;  ANY KIND WHATSOEVER RELATED TO THE SOFTWARE, HOWSOEVER CAUSED, EVEN IF
;  MICROCHIP HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.
;  TO THE FULLEST EXTENT ALLOWABLE BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
;  CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF
;  FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
;
;  MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE
;  TERMS.
;*******************************************************************************/

    .equ    WRITE_WORD_CODE,  0x4003
    .equ    ERASE_PAGE_CODE,  0x4042
    .equ    FLASH_PAGE_SIZE_IN_INSTRUCTIONS, 512
    .equ    FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS, FLASH_PAGE_SIZE_IN_INSTRUCTIONS*2
    .equ    FLASH_ROW_SIZE_IN_INSTRUCTIONS,  64
    .equ    FLASH_ERASE_WRITE_OP_MASK, 0x404F   
    .equ    FLASH_ERASE_PAGE_MASK,   (~(FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS - 1)) 

    .equ    FLASH_WRITE_ROW_MIN_CODE, 0x4001
    .data
    
_FlashKey: .long 0xFFFFFFFF

    .text
    .pushsection    .NVM_flash, code


/**
 * ;void  FLASH_Unlock(uint32_t key);
 * Used to program the flash key in memory variable located in RAM
 * the valid key is 0x00AA0055
 *
 *
 * @param key       32-bit (unsigned long) for the key
 *                      
 *   Registers used:  w0 w1 
 *                  
 * Inputs:
 *  w0,w1 = long data - Flash Key to save   (32 bits)
 *
 */    
       
    .global         _FLASH_Unlock
    .type           _FLASH_Unlock, @function
    reset
 _FLASH_Unlock:
    mov     #_FlashKey, W2
    mov     W0, [W2++]
    mov     W1, [W2]
    return;
    
/**
 * ;void  FLASH_Lock();
 * Locks the flash from programming by resetting the NVMKEY in memory
  *
 *
 * @param key       32-bit (unsigned long) for the key
 *                      
 *   Registers used:  w0 w1 
 *                  
 * Inputs:
 *  w0,w1 = long data - Flash Key to save   (32 bits)
 *
 */    
       
    .global         _FLASH_Lock
    .type           _FLASH_Lock, @function
    .extern         NVMKEY
    
    reset
 _FLASH_Lock:
    clr W0
    clr W1
    rcall _FLASH_Unlock
    clr NVMKEY    
    return;




 /**
 * ;void FLASH_SendNvmKey(uint32_t key);
 * Procedure to take the NVM key from memory and program the flash controller
 * with it.  A valid key is 0x00AA0055
  *
 *
 * @param key           32-bit (unsigned long) for the NVMKEY
 *                      W0 value will be used for the first access
 *                      W1 value will be used for the second access
 *
 *   Registers used:    w0 w1 (Preserved)
 *                  
 *   Inputs:
 *   w0,w1 = long data - Flash Key to use   (32 bits)
 *
*/    
    .type           _FLASH_SendNvmKey, @function
    .extern         NVMKEY
    .extern         TBLPAG
    
    reset
_FLASH_SendNvmKey:
    push   W0
    push   W1

    mov    #_FlashKey, w1
    disi   #6
    mov    [W1++],W0
    mov    W0, NVMKEY
    mov    [W1], W0
    mov    W0, NVMKEY
    bset   NVMCON, #15
    nop
    nop
    pop    W1
    pop    W0
    return
    


/**
 * ;uint32_t FLASH_ReadWord24(uint32_t address);
 * Reads the 24 bit instruction located at the address passed to this function.
 *
 *
 * @param address       24-bit (unsigned long) specifying a target address 
 *                      that needs to be read.  Needs to be aligned to an even
 *                      address.
 *
 *   Registers used:    w0 w1 w2
 *                      TBLPAG Preserved
 *                  
 *   Inputs:
 *   w0,w1 = long data - Address in flash to read   (24 bits)
 * 
 *  outputs:
 *   w0,w1 = 32 bit data contains the flash data read.   
 **/    
       
    .global         _FLASH_ReadWord24
    .type           _FLASH_ReadWord24, @function
    .extern         TBLPAG

    _FLASH_ReadWord24:
    mov         TBLPAG, W2
    mov         W1, TBLPAG	    ; Little endian, w1 has MSW, w0 has LSX
    tblrdh      [W0], W1	    ; read MSW of data to high latch
    tblrdl      [W0], W0	    ; read LSW of data
    mov         W2, TBLPAG      ; Data in in W1, W2
    return




/**
 * ;uint16_t FLASH_ReadWord16(uint32_t address);
 * Reads the 16 bit instruction located at the address passed to this function.
 * Address must be aligned to an even address.
 *
 *
 * @param address       24-bit (unsigned long) specifying a target address 
 *                      that needs to be read.  Needs to be aligned to an even
 *                      address.
 *
 *   Registers used:    w0 w1 w2
 *                      TBLPAG Preserved
 *                  
 *   Inputs:
 *   w0,w1 = long data - Address in flash to read   (24 bits)
 * 
 *  outputs:
 *   w0 = 16 bit data contains the flash data read.   
 *
 **/    

    
    .global         _FLASH_ReadWord16
    .type           _FLASH_ReadWord16, @function
    .extern         TBLPAG

    
   _FLASH_ReadWord16:
    mov         TBLPAG, W2
    mov         W1, TBLPAG     ; Little endian, w1 has MSW, w0 has LSX
    tblrdl      [W0], W0       ; read LSW of data
    mov         W2, TBLPAG     ; restore register
    return
   


    
/**
 * void FLASH_ErasePage(unsigned long address);
 * Erases the page containing the specified address. Be very careful if calling
 * this function as the function will erase any legal page, 
 *
 * NOTE: This function can take upwards of 45ms on some device families and 
 * target pages to complete. At frequencies appreciably slower than the maximum 
 * device frequency, even longer may be required. Therefore, you may need to 
 * issue a ClrWdt() call before calling this function, assuming the Watchdog 
 * timer is enabled. This also means that you should not configure a watchdog 
 * timeout of less than ~64ms, even when you pre-clear the timeout. This 
 * function does NOT internally clear the watchdog for you as it is packaged as 
 * a library routine where not everyone would desire such behavior.
 * 
 * @param address  24-bit (unsigned long) specifying the first address on the page
 *                      to be erased. Must be page aligned. 
 * 
 *   Registers used:    w0 w1 w2
 *                      TBLPAG Preserved
 *                  
 *   Inputs:
 *   w0,w1 = long data - Address in flash to erase   (24 bits)
 * 
 *  outputs:
 *   none
 *
 **/    
    

    .global         _FLASH_ErasePage
    .type           _FLASH_ErasePage, @function
    .extern         TBLPAG
    .extern         NVMCON
      reset
_FLASH_ErasePage:
    btsc        NVMCON, #15	           ; Loop, blocking until last NVM operation is complete (WR is clear)
    bra         _FLASH_ErasePage

    mov         #FLASH_ERASE_PAGE_SIZE_IN_PC_UNITS-1, w2     ;    get mask and validate all lower bits = 0
    and         w2, w0, w2
    bra         NZ,3f 

    mov         #ERASE_PAGE_CODE, w2 
    mov         w2, NVMCON

    mov         TBLPAG, w2            ; Save TBLPAG
 
    mov         w1, TBLPAG            ; MSB
    tblwtl      w0, [w0]              ; LS(16 bits)   

    call        _FLASH_SendNvmKey

    btsc        NVMCON, #15
    bra	        $-2

    mov         w2, TBLPAG

    mov         #1, w0               ; default return true
    btsc        NVMCON, #13          ; if error bit set, 
3:  mov         #0, w0               ;   return false

    return;

   
/**
 * ;void FLASH_WriteWord24(uint32_t address, uint32_t data);
 *  Writes a 24 bit instruction to the indicated address in flash.
 *
 *
 * @param address       value specifying a target address 
 *                      that this firmware will write to.  Address needs to be on a
 *                      even addresses.           
 *  
 *  @param data          24 bit value that will be written to the address above.
 *
 *   Registers used:    w0 w1 w2 w3 w4
 *                      TBLPAG Preserved
 *                  
 *   Inputs:
 *   w0,w1 = long data - Address in flash to write   (24 bits)
 *   w2,w3 = long data - 24 bits of data to write to flash   (24 bits)
 * 
 *  outputs:
 *   none 
 *
 **/    
    
    ;void FLASH_WriteWord24(uint32_t address, uint32_t data);
    
    .global         _FLASH_WriteWord24
    .type           _FLASH_WriteWord24, @function
    .extern         TBLPAG
    .extern         NVMCON

_FLASH_WriteWord24:
    btsc       NVMCON, #15     ; Loop, blocking until last NVM operation is complete (WR is clear)
    bra        _FLASH_WriteWord24
 
    btsc       w0, #0            ; Check for a valid address Bit 0  clear
    bra        3f
 
    mov        TBLPAG, W4      
    mov        W1, TBLPAG       ; Little endian, w1 has MSW, w0 has LSW

    mov        #WRITE_WORD_CODE, W1 
    mov        W1, NVMCON

    tblwtl     W2, [W0]         ; write LSW of data
    tblwth     W3, [W0]         ; write MSW of data to high latch
    
    call       _FLASH_SendNvmKey

    btsc       NVMCON, #15      ; wait until done.
    bra        $-2
    mov        w4, TBLPAG       ; restore
    
    mov         #1, w0               ; default return true
    btsc        NVMCON, #13          ; if error bit set, 
3:  mov         #0, w0               ;   return false

    return;


/**
 * ;void FLASH_WriteWord16(uint32_t address, uint16_t data);
 *  Writes a 24 bit instruction to the indicated address in flash.
 *
 *
 * @param address       value specifying a target address 
 *                      that this firmware will write to.  Address needs to be on a
 *                      even addresses.           
 *  
 *  @param data          16 bit value that will be written to the address above.
 *
 *   Registers used:    w0 w1 w2 w3 
 *                      TBLPAG Preserved
 *                  
 *   Inputs:
 *   w0,w1 = long data - Address in flash to write   (24 bits)
 *   w2    = 16 bit data - 16 bits of data to write to flash   (16 bits)
 * 
 *  outputs:
 *   none 
 *
 */    
    
    ;void FLASH_WriteWord16(uint32_t address, uint16_t data);
    
    .global         _FLASH_WriteWord16
    .type           _FLASH_WriteWord16, @function
    .extern         TBLPAG
    .extern         NVMCON

_FLASH_WriteWord16:
    btsc        NVMCON, #15     ; Loop, blocking until last NVM operation is complete (WR is clear)
    bra         _FLASH_WriteWord16
  
    btsc        w0, #0          ; Check for a valid address Bit 0  clear
    bra         3f
    
    mov         #WRITE_WORD_CODE, W3 
    mov         W3, NVMCON

    mov         TBLPAG, W3      ; save it
    mov         W1, TBLPAG      ; Little endian, w1 has MSW, w0 has LSW
    tblwtl      W2, [W0]        ; write 16 bits of data
    mov         #0xFF, W2
    tblwth      W2, [W0]        ; write 16 bits of data

    call        _FLASH_SendNvmKey

    btsc        NVMCON, #15     ; wait until done.
    bra         $-2
    mov         W3, TBLPAG

    mov         #1, w0               ; default return true
    btsc        NVMCON, #13          ; if error bit set, 
3:  mov         #0, w0               ;   return false

    return;


   



/**
 * ;void FLASH_WriteRow24(uint32_t flashAddress, uint16_t *data);
 *  Writes a single Row to the address flashAddress from the sourceAddress 
 *  Since this is passed as a 32 bit value
 *  and flash is only 24 bit wide, all data in the upper 8 bits will be lost.
 *
 *
 * @param flashAddress  32 bit value specifying a target address in flash 
 *                      that this firmware will write to.  It needs to be on a
 *                      addresses divisible by 4.
 *  
 *  @param sourceAddress  16 bit value of the address to read the data from.
 *
 *
 *   Registers used:    w0 w1 w2 w3 
 *                      TBLPAG Preserved
 *                  
 *   Inputs:
 *   w0,w1 = long data - Address in flash row to write   (24 bits)
 *   w2    = 16 bit address - address of data in ram to write to flash (16 bits)
 * 
 *  outputs:
 *   none 
 *
 
 */   
    
    .global         _FLASH_WriteRow24
    .type           _FLASH_WriteRow24, @function
    .extern         TBLPAG
    .extern         NVMCON
  

_FLASH_WriteRow24:
    btsc     NVMCON, #15         ; Loop, blocking until last NVM operation is complete (WR is clear)
    bra      _FLASH_WriteRow24

    mov      #((FLASH_ROW_SIZE_IN_INSTRUCTIONS*2)-1), w3     ;    get mask and validate all lower bits = 0
    and      w3, w0, w3
    bra      NZ,3f 

    mov      #FLASH_WRITE_ROW_MIN_CODE, W3 
    mov      W3, NVMCON

    mov      TBLPAG, W3	        ; save it
    mov      W1,TBLPAG

    mov      #FLASH_ROW_SIZE_IN_INSTRUCTIONS, W4
 
1: 
    tblwtl   [W2++],[W0]        ; Perform the TBLWT instructions to write the latches
    tblwth   [W2++],[W0++]
    sub      #1, W4
    bra      NZ, 1b

    call     _FLASH_SendNvmKey

    btsc     NVMCON, #15        ; wait until done.
    bra	     $-2
    mov      w3, TBLPAG

    mov         #1, w0               ; default return true
    btsc        NVMCON, #13          ; if error bit set, 
3:  mov         #0, w0               ;   return false

    return;


/**
 * ;void FLASH_WriteRow16(uint32_t flashAddress, uint16_t *data);
 *  Writes a single row to the address flashAddress  from the source address *data
 *  Each 16 bit source data word is stored in the lower 16 bits of each flash entry and the 
 *   upper 8 bits of the flash is not programmed.
 *
 *
 * @param flashAddress  32 bit value specifying a target address in flash 
 *                      that this firware will write to.  It needs to be on a
 *                      addresses divisible by 4.
 *  
 *  @param sourceAddress  16 bit value of the address to read the data from.
 *
 *
 *   Registers used:    w0 w1 w2 w3 
 *                      TBLPAG Preserved
 *                  
 *   Inputs:
 *   w0,w1 = long data - Address in flash row to write   (24 bits)
 *   w2    = 16 bit address - address of data in ram to write to flash (16 bits)
 * 
 *  outputs:
 *   none 
 *
 
 */   
    
    .global         _FLASH_WriteRow16
    .type           _FLASH_WriteRow16, @function
    .extern         TBLPAG
    .extern         NVMCON
  

_FLASH_WriteRow16:
    btsc     NVMCON, #15        ; Loop, blocking until last NVM operation is complete (WR is clear)
    bra      _FLASH_WriteRow16

    mov      #((FLASH_ROW_SIZE_IN_INSTRUCTIONS*2)-1), w3     ;    get mask and validate all lower bits = 0
    and      w3, w0, w3
    bra      NZ,3f 

    mov      #FLASH_WRITE_ROW_MIN_CODE, W3 
    mov      W3, NVMCON

    mov      TBLPAG, W3        ; save it
    mov      W1,TBLPAG

    mov      #FLASH_ROW_SIZE_IN_INSTRUCTIONS, W4
    mov      #0xFF, W1

1:
    tblwtl   [W2++],[W0]       ; Perform the TBLWT instructions to write the latches
    tblwth   W1,    [W0++]
    sub      #1, w4
    bra      NZ, 1b

    call     _FLASH_SendNvmKey

    btsc     NVMCON, #15       ; wait until done.
    bra      $-2
    mov      w3, TBLPAG

    mov         #1, w0               ; default return true
    btsc        NVMCON, #13          ; if error bit set, 
3:  mov         #0, w0               ;   return false

    return;


   
;uint16_t FLASH_GetErasePageOffset(uint32_t address)
    .global     _FLASH_GetErasePageOffset
    .type       _FLASH_GetErasePageOffset, @function

_FLASH_GetErasePageOffset:
    mov     #((~FLASH_ERASE_PAGE_MASK) & 0xFFFF), W2
    and     w2, w0, w0
    return

;uint32_t FLASH_GetErasePageAddress(uint32_t address);

    .global     _FLASH_GetErasePageAddress
    .type       _FLASH_GetErasePageAddress, @function

_FLASH_GetErasePageAddress:
    
    mov     #(FLASH_ERASE_PAGE_MASK & 0xFFFF)  , W2       ;LSW
    and     w2, w0, w0
    mov     #((FLASH_ERASE_PAGE_MASK >> 16) & 0xFFFF), W2 ; MSW
    and     w2, w1, w1

    return
   
    .popsection 
    
