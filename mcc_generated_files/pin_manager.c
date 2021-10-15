/**
  PIN MANAGER Generated Driver File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.c

  @Summary:
    This is the generated manager file for the PIC24 / dsPIC33 / PIC32MM MCUs device.  This manager
    configures the pins direction, initial state, analog setting.
    The peripheral pin select, PPS, configuration is also handled by this manager.

  @Description:
    This source file provides implementations for PIN MANAGER.
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
    Section: Includes
*/

#include <xc.h>
#include <stdio.h>
#include "pin_manager.h"

/**
 Section: Driver Interface Function Definitions
*/
void PIN_MANAGER_Initialize (void)
{
    /****************************************************************************
     * Setting the Output Latch SFR(s)
     ***************************************************************************/
    LATB = 0x82A0;
    LATC = 0x0000;
    LATD = 0x0000;
    LATE = 0x0000;
    LATF = 0x0000;
    LATG = 0x0000;

    /****************************************************************************
     * Setting the GPIO Direction SFR(s)
     ***************************************************************************/
    TRISB = 0x7D5F;
    TRISC = 0x7000;
    TRISD = 0x0EFF;
    TRISE = 0x00FF;
    TRISF = 0x007F;
    TRISG = 0x03CC;

    /****************************************************************************
     * Setting the Weak Pull Up and Weak Pull Down SFR(s)
     ***************************************************************************/
    CNPD1 = 0x0000;
    CNPD2 = 0x0000;
    CNPD3 = 0x0000;
    CNPD4 = 0x0000;
    CNPD5 = 0x0000;
    CNPD6 = 0x0000;
    CNPU1 = 0x0000;
    CNPU2 = 0x0000;
    CNPU3 = 0x0000;
    CNPU4 = 0x0000;
    CNPU5 = 0x0000;
    CNPU6 = 0x0000;

    /****************************************************************************
     * Setting the Open Drain SFR(s)
     ***************************************************************************/
    ODCB = 0x0000;
    ODCC = 0x0000;
    ODCD = 0x0000;
    ODCE = 0x0000;
    ODCF = 0x0000;
    ODCG = 0x0000;

    /****************************************************************************
     * Setting the Analog/Digital Configuration SFR(s)
     ***************************************************************************/
    AD1PCFGH = 0x0000;
    AD1PCFGL = 0xC3F3;
    
    /****************************************************************************
     * Set the PPS
     ***************************************************************************/
    __builtin_write_OSCCONL(OSCCON & 0xbf); // unlock PPS

    RPOR3bits.RP7R = 0x0005;    //RB7->UART2:U2TX
    RPINR27bits.U4RXR = 0x000E;    //RB14->UART4:U4RX
    RPOR4bits.RP9R = 0x001C;    //RB9->UART3:U3TX
    RPOR9bits.RP18R = 0x0003;    //RB5->UART1:U1TX
    RPINR18bits.U1RXR = 0x001C;    //RB4->UART1:U1RX
    RPOR14bits.RP29R = 0x001E;    //RB15->UART4:U4TX
    RPINR17bits.U3RXR = 0x0008;    //RB8->UART3:U3RX
    RPINR19bits.U2RXR = 0x0006;    //RB6->UART2:U2RX

    __builtin_write_OSCCONL(OSCCON | 0x40); // lock PPS
}

