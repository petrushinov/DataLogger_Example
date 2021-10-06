/* 
 * File:   measurement.c
 * MIT License
 * created 2021
 * Author: Tsvetan Petrushinov
 * e-mail: petrushinov@gmail.com
 * version 1.0
 */
#define FCY 1000000UL

#include <libpic30.h> 
#include "mcc_generated_files/adc1.h"
#include "measurement.h"

int16_t ADC1_get_value(uint8_t channel){
    ADC1_ChannelSelect(channel);
    
    __delay_ms(1); // waiting for the channel selection to take effect
    
    ADC1_Start();
    ADC1_Stop();
    
    while (!ADC1_IsConversionComplete())
    {
    }
       
    return ADC1_ConversionResultGet();
}


