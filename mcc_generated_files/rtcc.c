
/**
  RTCC Generated Driver API Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    rtcc.c

  @Summary:
    This is the generated header file for the RTCC driver using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This header file provides APIs for driver for RTCC.
    Generation Information :
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ256GA106
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


/**
 Section: Included Files
*/

#include "rtcc.h"

/**
* Section: Function Prototype
*/
static bool rtccTimeInitialized;
static bool RTCCTimeInitialized(void);
static uint8_t ConvertHexToBCD(uint8_t hexvalue);
static uint8_t ConvertBCDToHex(uint8_t bcdvalue);

/**
* Section: Driver Interface Function Definitions
*/

void RTCC_Initialize(void)
{

   // Set the RTCWREN bit
   __builtin_write_RTCWEN();

   RCFGCALbits.RTCEN = 0;
   
   if(!RTCCTimeInitialized())
   {
       // set RTCC time 2021-09-30 11-08-23
       RCFGCALbits.RTCPTR = 3;        // start the sequence
       RTCVAL = 0x21;    // YEAR
       RTCVAL = 0x930;    // MONTH-1/DAY-1
       RTCVAL = 0x411;    // WEEKDAY/HOURS
       RTCVAL = 0x823;    // MINUTES/SECONDS
   }

   // set Alarm time 2021-09-30 11-08-23
   ALCFGRPTbits.ALRMEN = 0;
   ALCFGRPTbits.ALRMPTR = 2;
   ALRMVAL = 0x930;
   ALRMVAL = 0x411;
   ALRMVAL = 0x823;

   // ALRMPTR MIN_SEC; AMASK Every Minute; ARPT 0; CHIME enabled; ALRMEN enabled; 
   ALCFGRPT = 0xCC00;
   RCFGCALbits.RTCOE = 1; // Enable RTCC output

   // RTSECSEL Alarm Pulse; 
   PADCFG1 = 0x00;
           
   // Enable RTCC, clear RTCWREN
   RCFGCALbits.RTCEN = 1;
   RCFGCALbits.RTCWREN = 0;

   //Enable RTCC interrupt
   IEC3bits.RTCIE = 1;
}


/**
 This function implements RTCC_TimeReset.This function is used to
 used by application to reset the RTCC value and reinitialize RTCC value.
*/
void RTCC_TimeReset(bool reset)
{
    rtccTimeInitialized = reset;
}

static bool RTCCTimeInitialized(void)
{
    return(rtccTimeInitialized);
}

/**
 This function implements RTCC_TimeGet. It access the 
 registers of  RTCC and writes to them the values provided 
 in the function argument currentTime
*/

bool RTCC_TimeGet(struct tm *currentTime)
{
    uint16_t register_value;
    if(RCFGCALbits.RTCSYNC){
        return false;
    }

    RCFGCALbits.RTCPTR = 3;
    register_value = RTCVAL;
    currentTime->tm_year = ConvertBCDToHex(register_value & 0x00FF);
    register_value = RTCVAL;
    currentTime->tm_mon = ConvertBCDToHex((register_value & 0xFF00) >> 8);
    currentTime->tm_mday = ConvertBCDToHex(register_value & 0x00FF);
    register_value = RTCVAL;
    currentTime->tm_wday = ConvertBCDToHex((register_value & 0xFF00) >> 8);
    currentTime->tm_hour = ConvertBCDToHex(register_value & 0x00FF);
    register_value = RTCVAL;
    currentTime->tm_min = ConvertBCDToHex((register_value & 0xFF00) >> 8);
    currentTime->tm_sec = ConvertBCDToHex(register_value & 0x00FF);

    return true;
}

/**
 * This function sets the RTCC value and takes the input time in decimal format
*/

void RTCC_TimeSet(struct tm *initialTime)
{
   // Set the RTCWREN bit
   __builtin_write_RTCWEN();

   RCFGCALbits.RTCEN = 0;
   
   IFS3bits.RTCIF = false;
   IEC3bits.RTCIE = 0;

   // set RTCC initial time
   RCFGCALbits.RTCPTR = 3;                               // start the sequence
   RTCVAL =  ConvertHexToBCD(initialTime->tm_year);                        // YEAR
   RTCVAL = (ConvertHexToBCD(initialTime->tm_mon) << 8) | ConvertHexToBCD(initialTime->tm_mday);  // MONTH-1/DAY-1
   RTCVAL = (ConvertHexToBCD(initialTime->tm_wday) << 8) | ConvertHexToBCD(initialTime->tm_hour); // WEEKDAY/HOURS
   RTCVAL = (ConvertHexToBCD(initialTime->tm_min) << 8) | ConvertHexToBCD(initialTime->tm_sec);   // MINUTES/SECONDS
             
   // Enable RTCC, clear RTCWREN         
   RCFGCALbits.RTCEN = 1;  
   RCFGCALbits.RTCWREN = 0;
   
   IEC3bits.RTCIE = 1;

}

/**
 This function reads the RTCC time and returns the date and time in BCD format
  */
bool RTCC_BCDTimeGet(bcdTime_t *currentTime)
{
    uint16_t register_value;
    if(RCFGCALbits.RTCSYNC){
        return false;
    }

    RCFGCALbits.RTCPTR = 3;
    register_value = RTCVAL;
    currentTime->tm_year = register_value;
    register_value = RTCVAL;
    currentTime->tm_mon = (register_value & 0xFF00) >> 8;
    currentTime->tm_mday = register_value & 0x00FF;
    register_value = RTCVAL;
    currentTime->tm_wday = (register_value & 0xFF00) >> 8;
    currentTime->tm_hour = register_value & 0x00FF;
    register_value = RTCVAL;
    currentTime->tm_min = (register_value & 0xFF00) >> 8;
    currentTime->tm_sec = register_value & 0x00FF;

    return true;
}
/**
 This function takes the input date and time in BCD format and sets the RTCC
 */
void RTCC_BCDTimeSet(bcdTime_t *initialTime)
{
   // Set the RTCWREN bit
   __builtin_write_RTCWEN();

   RCFGCALbits.RTCEN = 0;

   IFS3bits.RTCIF = false;
   IEC3bits.RTCIE = 0;

   // set RTCC initial time
   RCFGCALbits.RTCPTR = 3;                               // start the sequence
   RTCVAL = initialTime->tm_year;                        // YEAR
   RTCVAL = (initialTime->tm_mon << 8) | initialTime->tm_mday;  // MONTH-1/DAY-1
   RTCVAL = (initialTime->tm_wday << 8) | initialTime->tm_hour; // WEEKDAY/HOURS
   RTCVAL = (initialTime->tm_min << 8) | initialTime->tm_sec;   // MINUTES/SECONDS

   // Enable RTCC, clear RTCWREN
   RCFGCALbits.RTCEN = 1;
   RCFGCALbits.RTCWREN = 0;

   IEC3bits.RTCIE = 1;
}

static uint8_t ConvertHexToBCD(uint8_t hexvalue)
{
    uint8_t bcdvalue;
    bcdvalue = (hexvalue / 10) << 4;
    bcdvalue = bcdvalue | (hexvalue % 10);
    return (bcdvalue);
}

static uint8_t ConvertBCDToHex(uint8_t bcdvalue)
{
    uint8_t hexvalue;
    hexvalue = (((bcdvalue & 0xF0) >> 4)* 10) + (bcdvalue & 0x0F);
    return hexvalue;
}

void __attribute__ ((weak)) RTCC_CallBack(void)
{
    // Add your custom callback code here
}

/* Function:
  void __attribute__ ( ( interrupt, no_auto_psv ) ) _ISR _RTCCInterrupt( void )

  Summary:
    Interrupt Service Routine for the RTCC Peripheral

  Description:
    This is the interrupt service routine for the RTCC peripheral. Add in code if 
    required in the ISR. 
*/
void __attribute__ ( ( interrupt, no_auto_psv ) ) _ISR _RTCCInterrupt( void )
{
	// RTCC callback function 
	RTCC_CallBack();
	
    /* TODO : Add interrupt handling code */
    IFS3bits.RTCIF = false;
}


/**
 End of File
*/
