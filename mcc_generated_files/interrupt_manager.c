/**
  System Interrupts Generated Driver File 

  @Company:
    Microchip Technology Inc.

  @File Name:
    interrupt_manager.h

  @Summary:
    This is the generated driver implementation file for setting up the
    interrupts using PIC24 / dsPIC33 / PIC32MM MCUs

  @Description:
    This source file provides implementations for PIC24 / dsPIC33 / PIC32MM MCUs interrupts.
    Generation Information : 
        Product Revision  :  PIC24 / dsPIC33 / PIC32MM MCUs - 1.170.0
        Device            :  PIC24FJ256GA106
    The generated drivers are tested against the following:
        Compiler          :  XC16 v1.61
        MPLAB             :  MPLAB X v5.45
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

/**
    void INTERRUPT_Initialize (void)
*/
void INTERRUPT_Initialize (void)
{
    //    RTCI: RTCC - Real-Time Clock and Calendar
    //    Priority: 1
        IPC15bits.RTCIP = 1;
    //    UERI: U2E - UART2 Error
    //    Priority: 1
        IPC16bits.U2ERIP = 1;
    //    UTXI: U2TX - UART2 Transmitter
    //    Priority: 1
        IPC7bits.U2TXIP = 1;
    //    URXI: U2RX - UART2 Receiver
    //    Priority: 1
        IPC7bits.U2RXIP = 1;
    //    UERI: U3E - UART3 Error
    //    Priority: 1
        IPC20bits.U3ERIP = 1;
    //    UTXI: U3TX - UART3 Transmitter
    //    Priority: 1
        IPC20bits.U3TXIP = 1;
    //    URXI: U3RX - UART3 Receiver
    //    Priority: 1
        IPC20bits.U3RXIP = 1;
    //    UERI: U4E - UART4 Error
    //    Priority: 1
        IPC21bits.U4ERIP = 1;
    //    UTXI: U4TX - UART4 Transmitter
    //    Priority: 1
        IPC22bits.U4TXIP = 1;
    //    URXI: U4RX - UART4 Receiver
    //    Priority: 1
        IPC22bits.U4RXIP = 1;
    //    UERI: U1E - UART1 Error
    //    Priority: 1
        IPC16bits.U1ERIP = 1;
    //    UTXI: U1TX - UART1 Transmitter
    //    Priority: 1
        IPC3bits.U1TXIP = 1;
    //    URXI: U1RX - UART1 Receiver
    //    Priority: 1
        IPC2bits.U1RXIP = 1;

}
